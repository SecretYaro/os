#include <linux/kernel.h>

asmlinkage long sys_hello(void)
{
        printk("v.4");
        printk("Hello world\n");
        return 0;
}