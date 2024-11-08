#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/spinlock.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/uaccess.h> /* for copy_to_user and copy_from_user */
#include <linux/random.h> /* for random number generator */
#include <linux/miscdevice.h> /* for misc devices */
#include <linux/pid.h> /* for pid_task */
#include "lexus.h"

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mario Torres");
MODULE_DESCRIPTION("CS452 Lexus");

// #define DEBUG 1

/* this integers tracks how many number of tickets we have in total */
unsigned long nTickets = 0;

/* this variable is the timer, which helps us to call your lexus_schedule() every 200 millisecond. 
 * you don't need to use this variable in the four functions you implement. */
static struct timer_list dispatch_timer;

/* each lexus_task_struct represents one process in the lottery scheduling system */
struct lexus_task_struct {
        struct list_head list; /* Kernel's list structure */
        struct task_struct* task;
        unsigned long pid;
        unsigned long tickets;
        task_state state;
};

/* use this global variable to track all registered tasks, by adding into its list */
static struct lexus_task_struct lexus_task_struct;

/* the currently running lexus task */
static struct lexus_task_struct *lexus_current;

/* spinlock to protect the linked list, and the global variables defined in this kernel module */
static spinlock_t lexus_lock;

/* dispatch kernel thread */
static struct task_struct *dispatch_kthread;

/* given a pid, returns its task_struct */
struct task_struct* find_task_by_pid(unsigned int pid)
{
   struct task_struct* task;
   rcu_read_lock();
   task=pid_task(find_vpid(pid), PIDTYPE_PID);
   rcu_read_unlock();

   return task;
}

/* free all the lexus_task_struct instances: delete its list, 
 * and free its memory allocated via kmalloc().
 * this function is called in lexus_exit(), you won't use this function. */
void free_lexus_list(void) {
    struct list_head *p, *n;
    struct lexus_task_struct *tmp;
    unsigned long flags;
    spin_lock_irqsave(&lexus_lock, flags);
    /* You can just treat this list_for_each_safe() as a for loop:
     * for (p = lexus_task_struct.list->next; p != lexus_task_struct.list; p = p->next), 
     * you can ignore n, it's a temporary pointer used inside the loop. */
    list_for_each_safe(p, n, &lexus_task_struct.list) {
        tmp = list_entry(p, struct lexus_task_struct, list);
        list_del(p);
        kfree(tmp);
    }
    spin_unlock_irqrestore(&lexus_lock, flags);
}

/* register a process into the lottery scheduling system */
void lexus_register(struct lottery_struct lottery){
  
  // Allocate memory
  struct lexus_task_struct *node = kmalloc(sizeof(lexus_task_struct), GFP_KERNEL);

  // Need to change global variables and list
  unsigned long flags;
  spin_lock_irqsave(&lexus_lock, flags);

  // Update variables
  nTickets += lottery.tickets;
  node->task = find_task_by_pid(lottery.pid);
  node->pid = lottery.pid;
  node->tickets = lottery.tickets;
  node->state = READY;

  // Add to list
  list_add(&(node->list), &(lexus_task_struct.list));
  spin_unlock_irqrestore(&lexus_lock, flags);
}

/* unregister a process from the lottery scheduling system */
void lexus_unregister(struct lottery_struct lottery){

  // Code given in README
  struct list_head *p, *n;
  struct lexus_task_struct *node;
  
  list_for_each_safe(p, n, &lexus_task_struct.list) {
    node = list_entry(p, struct lexus_task_struct, list);

    // Added code so we don't delete every node
    // Verifying that the pid are the same
    if(node->pid == lottery.pid) {
      // Update global variabes and list
      unsigned long flags;
      spin_lock_irqsave(&lexus_lock, flags);
      // Delete from listhttp://gogole.com/
      list_del(p);
      // Free memory
      kfree(node);
      // Update current node to be NULL
      lexus_current = NULL;
      // Update nTickets, break
      nTickets -= node->tickets;
      spin_unlock_irqrestore(&lexus_lock, flags);
      break;
    }
  }
}

/* executes a context switch: pick a task and dispatch it to the Linux CFS scheduler */
int lexus_schedule(void *data)
{
  while(!kthread_should_stop()) {
    
    // Struct variables to use
    struct list_head *p, *n;
    struct lexus_task_struct *node = NULL;
    struct sched_param sparam;

    // Variables used in function
    int counter = 0;
    unsigned long flags;
    int randval = 0;
    unsigned long winner = 0;
		
    // Verify nTickets isn't 0
    if (nTickets == 0) {
      set_current_state(TASK_INTERRUPTIBLE);
      schedule();
      continue;
    }

    // Producing a random number as the lottery winning number
    get_random_bytes(&randval, sizeof(int)-1);
    winner = (randval & 0x7FFFFFFF) % nTickets;

    // Giving me ability to manipulate data / list
    spin_lock_irqsave(&lexus_lock, flags);

    // Pick lottery winner
    list_for_each_safe(p, n, &lexus_task_struct.list) {
      node = list_entry(p, struct lexus_task_struct, list);
      counter += node->tickets;
      if (counter > winner) {
	//break out of loop when winner found
	break;
      }
    }

    // Old
    if (lexus_current != NULL) {
      sparam.sched_priority = 0;
      sched_setscheduler(lexus_current->task, SCHED_NORMAL, &sparam);
      lexus_current->state = READY;
    }

    // Set winner to current
    lexus_current = node;

    // New
    wake_up_process(lexus_current->task);
    sparam.sched_priority=99;
    sched_setscheduler(lexus_current->task, SCHED_FIFO, &sparam);
    lexus_current->state = RUNNING;

    spin_unlock_irqrestore(&lexus_lock, flags);

    // Sleep the process
    set_current_state(TASK_INTERRUPTIBLE);
    schedule();
		
  }
  return 0;

}

/* handle ioctl system calls */
static long lexus_dev_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)
{
  // using struct so I don't have to allocate memory here
  struct lottery_struct lottery_info;
  
  // verifying copy_from_user
  if (copy_from_user(&lottery_info, (void *)arg, sizeof(struct lottery_struct)) != 0) {
    return -EACCES;
  }

  // calling either lexus_register or lexus_unregister based on lotter_info
  if (ioctl == LEXUS_REGISTER) {
    lexus_register(lottery_info);
  } else {
    lexus_unregister(lottery_info);
  }

  return 0;
}

/* gets called when the timer goes off, we then reset the timer so as to make sure
 * this function gets called periodically - every 200 milliseconds. */
void dispatch_timer_callback(unsigned long data)
{
    #ifdef DEBUG
    printk("Timer\n" );
    #endif

    /* setup timer interval to 200 msecs */
    mod_timer(&dispatch_timer, jiffies + msecs_to_jiffies(200));
    if(nTickets == 0) // nTickets being zero suggests there is no registered processes.
        return;

    #ifdef DEBUG
    printk("wake up dispatch kthread...\n" );
    #endif

    /* wake up the lottery scheduling kthread */
    wake_up_process(dispatch_kthread);
}

static const struct file_operations lexus_chardev_ops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl = lexus_dev_ioctl,
	.compat_ioctl   = lexus_dev_ioctl,
	.llseek         = noop_llseek,
};

/* once we call misc_reigster(lexus_dev), a file called /dev/lexus will be created.
 * any ioctl commands sent to this device will be handled by lexus_dev.fops.unlocked_ioctl, 
 * which is lexus_dev_ioctl(). */
static struct miscdevice lexus_dev = {
	.minor = LEXUS_MINOR,
	.name = "lexus",
	.fops = &lexus_chardev_ops,
	.mode = 0666,
};

/* called when module is loaded */
int __init lexus_init(void)
{
	int r;

	#ifdef DEBUG
	printk("<1> lexus: loading.\n");
	#endif

	/* creating the device file /dev/lexus */
	r = misc_register(&lexus_dev);
	if (r) {
		printk(KERN_ERR "lexus: misc device register failed\n");
		return r;
	}

	/* the lexus version of "current" - in Linux kernel, the global variable "current" points to the currently running process - its task_struct */
	lexus_current = NULL;

	/* initialize the list_head to be empty */
	INIT_LIST_HEAD(&lexus_task_struct.list);

	/* a kernel thread named lexus_dispatch will be running at the background, which calls lexus_schedule().
 	 * We don't need to pass any parameter lexus_schedule(), thus here the 2nd parameter is NULL. */
	dispatch_kthread = kthread_create(lexus_schedule, NULL, "lexus_dispatch");

	/* initialize the spin lock */
	spin_lock_init(&lexus_lock);

	/* setup your timer to call dispatch_timer_callback */
	setup_timer(&dispatch_timer, dispatch_timer_callback, 0);
	/* setup timer interval to 200 msecs */
	mod_timer(&dispatch_timer, jiffies + msecs_to_jiffies(200));

	#ifdef DEBUG
	printk("<1> lexus: loaded.\n");
	#endif

	return 0;
}

/* called when module is unloaded */
void __exit lexus_exit(void)
{
	#ifdef DEBUG
	printk("<1> lexus: unloading.\n");
	#endif

	/* now it's time to exit the dispatch kthread, we wake it up so that it runs and checks the stop flag at the beginning of the while loop */
	wake_up_process(dispatch_kthread);
	kthread_stop(dispatch_kthread);

	/* remove kernel timer when unloading module */
	del_timer(&dispatch_timer);

	/* free the memory allocated for each lexus_task_struct */
	free_lexus_list();

	/* removing the device file /dev/lexus */
	misc_deregister(&lexus_dev);

	#ifdef DEBUG
	printk("<1> lexus: unloaded.\n");
	#endif
}

// register init and exit funtions
module_init(lexus_init);
module_exit(lexus_exit);

/* vim: set ts=4: */
