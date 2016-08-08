#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>

// Print jiffies
void A_print_jiffies(void)
{
        printk("jiffies is : %llu\n", (u64)jiffies);
        return;
}
EXPORT_SYMBOL(A_print_jiffies);

static int __init A_init(void)
{
        printk("A_func module init!\n");
        return 0;
}

static void __exit A_exit(void)
{
        printk("A_func module exit!\n");
        return;
}

module_init(A_init);
module_exit(A_exit);

MODULE_AUTHOR("XuHongzhi@MacroSAN");
MODULE_DESCRIPTION("Module A");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
