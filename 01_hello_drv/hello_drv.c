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

static int major = 0;
static char kernel_buf[1024];
static ssize_t (*hello_read) (struct file *file, char __user *buf, size_t size, loff_t *offset){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
}
static ssize_t (*hello_write) (struct file *file, char __user *buf, size_t size, loff_t *offset){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__,__LINE);
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

static const struct file_operations hello_fops = {
	.owner	= THIS_MODULE,
	.open	= hello_open,
	.read 	= hello_read,
	.write 	= hello_write,
	.release = hello_release,
};

