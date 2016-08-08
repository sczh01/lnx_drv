#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>

extern void A_print_jiffies(void);

static int __init B_init(void)
{
        printk("B_func module init!\n");
        A_print_jiffies();
        return 0;
}

static void __exit B_exit(void)
{
        printk("B_func module exit!\n");
        return;
}

module_init(B_init);
module_exit(B_exit);

MODULE_AUTHOR("XuHongzhi@MacroSAN");
MODULE_DESCRIPTION("Module B!");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
