#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>

/*确定主设备号*/
static int major = 0;
static char kernel_buf[1024];

/*实现对应的drv函数*/
static ssize_t (*hello_read) (struct file *file, char __user *buf, size_t size, loff_t *offset){
	int err;	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
	err = copy_to_user(buf, kernel_buf, MIN(1024, size));
	return MIN(1024, size);
}
static ssize_t (*hello_write) (struct file *file, char __user *buf, size_t size, loff_t *offset){
	int err;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
	err = copy_from_user(kernel_buf, buf, MIN(1024, size));
	return MIN(1024, size);
}
static int (*hello_open) (struct inode *node, struct file *file){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
	return 0;
}
static int (*hello_release) (struct inode *node, struct file *file){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
	return 0;
}

static struct class *hello_class;

/*定义file_operationgs结构体*/
static const struct file_operations hello_fops = {
	.owner	= THIS_MODULE,
	.open	= hello_open,
	.read 	= hello_read,
	.write 	= hello_write,
	.release = hello_release,
};

/*入口函数*/
static int __init hello_init(void)
{
	int err;

	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
	hello_class = class_create(THIS_MODULE, "hello");
	err = PTR_ERR(hello_class);
	major = register_chrdev(MISC_MAJOR, "hello", &misc_fops);
	
	device_create(hello_class, NULL, MKDEV(major, 0), NULL, "hello");
	return 0;
}


/*出口函数*/
static void __exit hello_exit(void)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
	device_destroy(device_create, MKDEV(major, 0));
	class_destroy(hello_class);
	unregister_chrdev(major, "helllo");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");