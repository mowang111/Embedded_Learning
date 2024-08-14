#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/ipmi.h>
#include <linux/mutex.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/compat.h>
#include "led_opr.h"

#define LED_NUM 2

static int major;
static struct class *led_class;
static struct led_opration* p_ledopr;

/* register */
/* IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 0x2290014 */
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
/* GPIO5_GDIR 0x020AC000 + 0x4 */
static volatile unsigned int *GPIO5_GDIR;
/* GPIO5_DR 0x020AC000 + 0 */
static volatile unsigned int *GPIO5_DR;

struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
};

static int led_open(struct inode *inode, struct file *file)
{
    int minor = iminor(inode);

    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);

    p_ledopr->init(minor);
    return 0;
}

static size_t led_write(struct file *file, const char __user *buf,
			  size_t len, loff_t *ppos) 
{
    char status;
    struct inode *inode = file_inode(file);
    int minor = iminor(inode);

    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    
    /* copy from user */
    copy_from_user(&status, buf, 1);

    p_ledopr->ctl(minor, status);

    return 0;
}

static int __init led_init(void)
{
    int i;

    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    major = register_chrdev(0, "led_drv", &led_fops);
    if (major < 0)
    {
        printk("register_chrdev failed with %d\n", major);
        return major;
    }

    led_class = class_create(THIS_MODULE, "myled");
    for(i = 0; i < LED_NUM; i++)
    {
        device_create(led_class, NULL, MKDEV(major, i), NULL, "myled%d", i); /*/dev/myled0*/
    }

    p_ledopr = get_board_led_opr();

    /*ioremap*/
    IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x2290014, 4);
    GPIO5_GDIR = ioremap(0x020AC000 + 0x4, 4);
    GPIO5_DR = ioremap(0x020AC000 + 0, 4);

    return 0;
}

static int __exit led_exit(void)
{
    int i;
    for(i = 0; i < LED_NUM; i++)
    {
        device_destroy(led_class, MKDEV(major, i));
    }
    class_destroy(led_class);
    unregister_chrdev(major, "led_drv");
    return 0;
}

MODULE_LICENSE("GPL");
module_init(led_init)
module_exit(led_exit);