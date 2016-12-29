#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/io.h>

char* module_name = "exyons4412_led";

static volatile unsigned int *GPM4CON = NULL;
static volatile unsigned int *GPM4DAT = NULL;

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        printk("%s open successful!\n", module_name);

        *GPM4CON &= ~(0xf << 0 * 4);
        *GPM4CON |= (1 << 0 * 4);

        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        printk("%s release successful!\n", module_name);

        *GPM4DAT &= ~(1 << 0);

        return 0;
}

static ssize_t tiny4412_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        printk("%s read successful!\n", module_name);

        *GPM4DAT |= (1 << 0);

        return 0;
}

static ssize_t tiny4412_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk("%s write successful!\n", module_name);

        *GPM4DAT &= ~(1 << 0);

        return 0;
}

static struct file_operations tiny4412_fops =
{       .open = tiny4412_open, .release = tiny4412_release, .read =
        tiny4412_read, .write = tiny4412_write,};

static struct miscdevice misc =
{       .minor = 255, .name = "exyons4412_led", .fops = &tiny4412_fops,};

static int __init led_init(void)
{
        /* 注册杂项字符设备 */
        misc_register(&misc);

        /* 映射地址 */
        GPM4CON = ioremap(0x110002E0, 4);
        GPM4DAT = ioremap(0x110002E4, 4);

        printk("%s install successful!\n", module_name);

        return 0;
}

static void __exit led_exit(void)
{
        /* 注销杂项字符设备 */
        misc_deregister(&misc);

        /* 释放映射的地址 */
        iounmap(GPM4CON);
        iounmap(GPM4DAT);

        printk("remove %s successful!\n", module_name);
}

module_init (led_init);
module_exit (led_exit);

MODULE_LICENSE("GPL");
