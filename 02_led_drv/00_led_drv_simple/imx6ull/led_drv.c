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

static int major;
static struct class *led_class;

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
    /* enable gpio: ccm clock 
     * configure pin as gpio: iomux
     * configure gpio as output: input/output
     */
    *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 &= ~0xf;
    *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 |= 0x05;
    *GPIO5_GDIR |= 1 << 3;

    return 0;
}

static size_t led_write(struct file *file, const char __user *buf,
			  size_t len, loff_t *ppos) 
{
    int val;
    /* copy from user */
    copy_from_user(&val, buf, 1);
    /* set gpio register: 1/0 */
    if (val)
    {
        /* let led on */
        *GPIO5_DR &= ~(1 << 3);
    }
    else
    {
        /* let led off */
        *GPIO5_DR |= 1 << 3;
    }
}
static int __init led_init(void)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    major = register_chrdev(0, "led_drv", &led_fops);
    if (major < 0)
    {
        printk("register_chrdev failed with %d\n", major);
        return major;
    }

    led_class = class_create(THIS_MODULE, "myled"); 
    device_create(led_class, NULL, MKDEV(major, 0), NULL, "myled"); /*/dev/myled*/

    /*ioremap*/
    IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x2290014, 4);
    GPIO5_GDIR = ioremap(0x020AC000 + 0x4, 4);
    GPIO5_DR = ioremap(0x020AC000 + 0, 4);

    return 0;
}

static int __exit led_exit(void)
{
    device_destroy(led_class, MKDEV(major, 0));
    class_destroy(led_class);
    unregister_chrdev(major, "led_drv");
    return 0;
}

MODULE_LICENSE("GPL");
module_init(led_init)
module_exit(led_exit);