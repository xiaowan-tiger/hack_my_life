#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/sched/signal.h>

struct task_struct {
    struct work_struct work;
}

void tasklet_function(struct work_struct *work) {
    struct task_struct *task;
    struct pid *pid_struct;
    char task_state[64];

    task = current;

    pid_strcut = task->pids[PIDTYPE_PID].pid;

}
