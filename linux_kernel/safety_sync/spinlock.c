#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static int shared_resource = 0;
static spinlock_t my_spinlock;
static struct task_struct *thread1, *thread2;

int thread_function(void *data) {
    int i;
    unsigned long flags;

    for (i = 0; i < 10; i++) {
        spin_lock_irqsave(&my_spinlock, flags);
        shared_resource++;
        printk(KERN_INFO "Thread %s incremented shared resource to %d\n", (char *)data, shared_resource);
        spin_unlock_irqrestore(&my_spinlock, flags);
        msleep(100);
    }

    return 0;
}

static int __init my_module_init(void) {
    printk(KERN_INFO "Initializing module with spinlock\n");

    spin_lock_init(&my_spinlock);

    thread1 = kthread_run(thread_function, "Thread 1", "thread1");
    thread2 = kthread_run(thread_function, "Thread 2", "thread2");

    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Exiting module\n");

    if (thread1)
        kthread_stop(thread1);
    if (thread2)
        kthread_stop(thread2);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple spinlock example with shared resource");
MODULE_AUTHOR("Your Name");
