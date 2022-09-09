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
![](C:\Users\mario\Documents\Fall Semester 2022\CS452\p2\test1.PNG)

## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

If you used any sources outside of the text book you should list them here. If you looked something up on
stackoverflow.com and fail to cite it in this section it will be considered plagiarism and be dealt with accordingly. So be safe CITE!
