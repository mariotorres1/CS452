## Project 1 Tesla

* Author: Mario 
* Class: CS452/CS552 [Operating Systems]

## Overview

We create a new getdents() function that we run and it will hide all files 
with the name tesla in it. This can be used with other file names if changed
in the code. We're essentially hiding files when we run the ls command.

## Manifest

Makefile - Used to set everything up to run our program  
tesla.h - Header file  
tesla.c - File where our main code is at  
test1 - first set of tests  
test2 - second set of tests  
test3 - third set of tests  
test4 - fourth set of tests  
README.orig - File going through the project and what we need to do  
README.md - This file  

## Building the project

To build the project, we use the command:

$make

This will give us our .ko file which we will use later. This just gives us 
the files to run to hide the tesla files, if we do ls right now, all the 
tesla files will still be there.  

To hide the tesla files, and use our new tesla_getdents function, we run:

$sudo insmod tesla.ko

this will prompt us for a password, once that is entered, the tesla files
will now be hidden when we run the ls, ls -l, and ls -la commands as well
as when we run the ls test1, ls test2, ls test3, and ls test4 commands.

To remove the module, and go back to running the original getdents function,
we run:

$sudo rmmod tesla

This will get everything back to normal like before

## Features and usage

The main usage and features of this program is to use the ls, ls -l, and 
ls -la commands in the terminal. As mentioned above, we also use ls test1, 
ls test2, ls test3, and ls test4 to use the tests provided for us.

## Testing

I used a lot of printk lines to test and debug the code because I couldn't 
get my kgbd to work properly. Something I plan to figure out over the weekend,
but as far as test cases, I just used the given test files that were provided 
when we were assigned this project. Majority of my 'testing' was done following 
what my code was actually doing with printk statements. 

## Known Bugs

I didn't notice any major bugs, some of the file's sizes are a little different 
but I don't think that is a bug. the test one's match at all times so that is 
mainly what I was paying attention to.

## Reflection and Self Assessment

Coming into this class and project, I hadn't done much work or programs like this 
so I had a pretty big learning curve to start. I tried to take as much from class 
lecture as well as any research I could find about hiding files, getdents, and the 
kernel overall online. I'm glad that I was able to complete the assignment 
and not have any major bugs that I could find. The more I studied about this 
topic and work I did in the project, the more fun I had in this type of
programming assignment. At first, I wasn't too thrilled to be doing these type 
of projects but I turned out to really enjoy this project in the end.

I think the hardest part for me was just understanding pointers and the different 
functions that the Linux system uses and how everything works. It was all pretty 
foreign to me so I really struggled with understanding and piecing everything 
together. I'm thankful for slack channel and having you explain it pretty 
well in class. I also had a bug with running the ls test1 command where the VM would 
just hang and I'd have to restart. I think I was hitting an infinite loop in my while 
statement so I ended up adding more variables and changing my while loop condition and 
this seemed to fix everything which I was happy about when it happened. Other 
than those couple things, I didn't have too much hang up, but I do look forward 
to the remaining projects after diving into this one. 

## Sources Used

Slack channel
Stackoverflow, information about getdents and the Linux system as a whole
man pages for getdents, memcpy
Stackoverflow on pointers and trying to learn more about pointers
