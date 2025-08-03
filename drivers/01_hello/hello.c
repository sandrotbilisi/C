#include <linux/module.h>
#include <linux/init.h>

int init_kernel(void){
	printk("hello - Hello to kernel\n");
	return 0;
}

void exit_kernel(void){
	printk("hello - bye kernel\n");
}

module_init(init_kernel);
module_exit(exit_kernel);

MODULE_LICENSE("GPL");
