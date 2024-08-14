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

struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,
};

static int led_open(struct inode *inode, struct file *file)
{
    /* enable gpio: ccm clock 
     * configure pin as gpio: iomux
     * configure gpio as output: input/output
     */
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
        
    }
    else
    {
        /* let led off */
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