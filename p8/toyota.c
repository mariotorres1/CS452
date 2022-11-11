/*
 * the toyota char device driver.
 */

#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* for kmalloc() */
#include <linux/version.h> /* for kmalloc() */
#include <linux/fs.h>     /* everything... */
#include <linux/file.h>     /* everything... */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/fcntl.h>        /* O_ACCMODE */
#include <linux/kmod.h>        /* for request_module */
#include <linux/init.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,12)
#include <linux/sched/signal.h>
#else
#include <linux/signal.h>
#endif
#include <linux/sched.h>
#include <linux/uaccess.h>

#include "toyota.h"        /* local definitions */

MODULE_AUTHOR("Mario Torres"); /* change this line to your name */
MODULE_LICENSE("GPL");

// Variables
int d;
char *kb = NULL;
size_t kbSize;

static int toyota_open (struct inode *inode, struct file *filp);
static int toyota_release (struct inode *inode, struct file *filp);
static ssize_t toyota_read (struct file *filp, char *buf, size_t count, loff_t *f_pos);
static ssize_t toyota_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos);

/* The different file operations.
 * Any member of this structure which we don't explicitly assign will be initialized to NULL by gcc. */
static struct file_operations toyota_fops = {
    .owner =      THIS_MODULE,
    .read =       toyota_read,
    .write =      toyota_write,
    .open =       toyota_open,
    .release =    toyota_release,
};

/*
 * open. if successful, return 0.
 */

static int toyota_open (struct inode *inode, struct file *filp) {
	
    // Getting number
    int mn = NUM(inode->i_rdev);
    
    // Verifying mn
    if (mn >= 4 || mn < 0) {
        return -ENODEV;
    }
	
    // storing mn as a global variable
    d = mn;
	
    // Incrementing the use count
    try_module_get(THIS_MODULE);
	
    // return 0 on success
    return 0;
}

/*
 * close. if successful, return 0.
 */

static int toyota_release (struct inode *inode, struct file *filp) {
	
    // Decrement the use count
    module_put(THIS_MODULE);
	
    // return 0 on success
    return 0;
}

/* write the string to the internal buffer for minor number 0;
 * pretends to ignore writes (like /dev/null) for minor numbers 1,2;
 * kill the calling process for minor number 3;
 * we assume applications will access our device sequentially, i.e., they do not access multiple devices concurrently.
 * if successful, return count - user wants to write "count" bytes into this device.
 */
static ssize_t toyota_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos) {
    // Variables
    kb = kmalloc(count, GFP_KERNEL);
    memset(kb, 0, count);
    kbSize = 0;
	
    // Checking if our global variable is 0
    if (d == 0) {
	// Copying buffer if device number is 0
        if (copy_from_user(kb, buf, count) != 0) {
		
 	    // Free memory and return error
	    kfree(kb);
	    return -EACCES;
	}
	    
	// Update our buffer size
	kbSize = count;
    } else if (d == 3) { // Checking if device number is 3
	// Killing the process
        kill_pid(task_pid(current), SIGTERM, 1);
    }
	
    // Return if d is 1 or 2
    return count;
}

/* Helper method for toyota_read
   Removes duplicate letters while keeping order */
static char *toyota_read_healper(char *s, size_t slen) {
	
	// Variables
	size_t i, outlen = 0;

	int alphabet[26] = {0};
	int inStack[26] = {0};

	// Creating our output buffer
	char *out = (char *)kmalloc(sizeof(char) * (slen + 1), GFP_KERNEL);
	memset(out, 0, sizeof(char) * (slen + 1));

	// Looping through to count the occurance of letters
	for (i = 0; i < slen; i++) {
		alphabet[s[i] - 'a']++;
	}

	// Looping through to see if occurance is in stack
	for (i = 0; i < slen; i++) {
		// If in stack, skip and decrement occurance
		if (inStack[s[i] - 'a']) {
			alphabet[s[i] - 'a']--;
			continue;
		}
		
		// Loop to remove head until it's false
		while (outlen > 0 && s[i] < out[outlen - 1] && alphabet[out[outlen - 1] - 'a'] > 0) {
			inStack[out[outlen - 1] - 'a'] = 0;
			outlen--;
		}

		// Adding to output stack
		out[outlen++] = s[i];
		// Decrement occurance
		alphabet[s[i] - 'a']--;
		// Setting true
		inStack[s[i] - 'a'] = 1;
	}

	// Adding terminator character
	out[outlen] = '\0';
	
	// Returning output stack
	return out;
}

/* when read, we do not care the device minor number,
 * we process whatever is in the internal buffer, and return the processed string (maybe multiple times, as a stream) to user.
 * we assume applications will access our device sequentially, i.e., they do not access multiple devices concurrently.
 * if successful, return count - user wants to read "count" bytes from this device.
 */
static ssize_t toyota_read (struct file *filp, char *buf, size_t count, loff_t *f_pos) {
	// Variables
   	int i;
	size_t len;
	char *out, *result;

	// Checking if our kernel buffer is NULL
	if (kb == NULL) {
		return -1;
	}

	// Creating memory for out and calling our helper function 
	out = (char *)kmalloc(count, GFP_KERNEL);
	result = toyota_read_helper(kb, kbSize);

	// Setting first byte to be terminator character
	out[0] = '\0';

	// Free our memory and set to null
	kfree(kb);
	kb = NULL;

	// Getting the lenth of our result
	len = strlen(result);

	// Checking if length is greater than one
	if (len > 0) {
		// Looping through and creating stream to be returned
		for (i = 0; i < (int)(count / len); i++) {
			strcat(out, result);
		}

		if ((count % len) > 0) {
			strncat(out, result, (count % len));
		}
	}

	len = strlen(out);

	// Return stream
	if (copy_to_user(buf, out, len) != 0) {
		kfree(out);
		return -EACCES;
	}

	// Free memory
	kfree(out
	      
	// Returning length 
	return len;
}

/*
 * module initialization. if successful, return 0.
 */

static int __init toyota_init(void) {
	/*
	 * register your major, and accept a dynamic number.
	 */
    register_chrdev(0, "toyota", &toyota_fops);
    return 0;
}

/*
 * module exit. if successful, does not return anything.
 */

static void __exit toyota_exit(void) {
    unregister_chrdev(register_chrdev(0, "toyota", &toyota_fops), "toyota");
}

module_init(toyota_init);
module_exit(toyota_exit);

/* vim: set ts=4: */
