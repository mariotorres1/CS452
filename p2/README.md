## Project 2 

* Author: Mario Torres
* Class: CS452/CS552 [Operating Systems] 

## Overview

We wrote a Linux kernel module called lexus that implemented a lottery scheduler.

## Manifest

* Makefile - Builds the project
* lexus.c - Main file in project, has lottery schedule implementation
* lexus.h - Header file
* lexus-test1.sh - First test file
* lexus-test2.sh - Second test file
* lexus-test3.sh - Third test file
* lexus-test.sh - Tests register / unregister functions
* README.orig - Original README that had project instructions
* README.md - This file

## Building the project

Run make to build the project: 
``` console
$make
```

Import the module we created:
``` console
$sudo insmod lexus.ko
```

Test:
``` console
$./lexus-test[1-3].sh
```

Remove the module:
``` console
$sudo rmmod lexus
```

## Features and usage

The main features of the project were the lexus_dev_ioctl(), 
lexus_register(), lexus_unregister(), and lexus_schedule() functions. Each
function was implemented by me based on lectures and the textbook for the 
class. The lexus_dev_ioctl() function handles the calling of either the 
lexus_register() function or the lexus_unregister() function depending on 
what is passed. The lexus_register() function handles processes that want to 
be registered and added into the lottery scheduling that I created. The lexus_unregister 
does the opposite and removes a process from the lottery scheduling. Finally, 
the lexus_schedule() function does the main work of the lottery scheduling. 

## Testing

Most of the testing I did with this project was running the given tests that 
were provided when we were assigned this project. From there, I had issues with 
it crashing a couple times and I would comment code and slowly uncomment the code 
to see where the crash was happening and I would fix the issue. I also used the debug 
possibilities that were also provided within the code and that really helped with 
the register, unregister and ioctl functions.

Here are my results from the tests:

Test1:  
![test1](https://user-images.githubusercontent.com/85824580/189268217-f7c18a1e-36e7-4bd1-83b2-87d79e756c56.jpg)

Test2:  
![test2](https://user-images.githubusercontent.com/85824580/189268323-bbf3ae4e-a7b8-41ba-88c1-ef9a702b394e.PNG)

Test3:  
![test3](https://user-images.githubusercontent.com/85824580/189268343-4cc9b915-cef3-48f1-bb92-7b69a561be3f.PNG)


## Known Bugs

No bugs that were noticeable to my eyes.

## Reflection and Self Assessment

This project really challenged me in my ability to see where my issue was and be able 
to fix that issue. Before this class, I've debugged but nothing to the level of debugging 
that I've done in the first two projects and I think that it's challenging me quite a 
bit but I wouldn't say it's a bad thing at all. I enjoy the challenge and hope that it 
will make me a better programmer from being able to learn this skills/techniques that I 
really haven't used before hand. I'm really enjoying that aspect of the class thus far.  

As far as things that hindered me or took me quite some time to figure out, I'd say the 
first three functions, lexus_dev_ioctl(), lexus_register(), and lexus_unregister() weren't 
too difficult. The main issues I had were self inflicted like typos and missing brackets 
and small things like that. Now, the lexus_schedule() function was a little different 
story. I was crashing a couple times and that really took me some time to figure out and 
like I said above, that was my biggest issue, being able to find the problem and knowing 
how to fix it. I think the slack channel was a very big help here and the lecture material 
was also a big help. Once, I was able to fix the crashing, I just had touch up issues like 
I mentioned earlier of typos and missing brackets. I finally figured out how to turn on 
the ability to highlight matches brackets in emacs and that really helped me. I feel that 
I'm progressing better than I thought I would at the beginning of the semester and that is 
something that I'm pretty pumped about.

## Sources Used

* Slack channel 
* Textbook: https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-lottery.pdf
* Lecture notes
