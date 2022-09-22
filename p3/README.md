## Project 3

* Author: Mario Torres
* Class: CS452/CS552 [Operating Systems]

## Overview

We implement the buddy-system. We create our own malloc and free functions 
using the buddy-system.

## Manifest

* Makefile - Creates the executibles
* buddy.c - File we implement our new functions
* buddy.h - Header file
* malloc-test.c - Uses the original malloc and free functions to test data
* buddy-test.c - Uses our new buddy_malloc and buddy_free functions to test data
* buddy-unit-test.c - Mainly tests our new malloc function
* README.orig - Original README with project instructions
* README.md - This file

## Building the project

We first need to build all the files by running make: 
``` console
  $make
```

Then we can run the buddy-unit-test files:
``` console
  $buddy-unit-test [s | t | v | i]
```

Finally, we can run the buddy-test and malloc tests:
``` console
  $buddy-test <num of tests> [random seed] [s | t | v | i]
  $malloc-test <num of tests> [random seed] [s | t | v | i]
```
  
We can also time those tests by using:
``` console
  $time buddy-test <num of tests> [random seed] [s | t | v | i]
  $time malloc-test <num of tests> [random seed] [s | t | v | i]
```

## Features and usage

There are 4 main features to this project, we have the buddy_init(), 
buddy_malloc(), buddy_free(), and printBuddyList() functions. The buddy_init() 
function does all the initialization and returns true on success, this function
is expected to be called before buddy_malloc(). The next function to implement 
would be buddy_malloc() that allocates size bytes and returns a pointer to the 
allocated memory, The third function would be buddy_free() which takes a pointer 
to the memory and frees the memory space. Finally, the last function is 
printBuddyLists which we used mainly for debugging. It printed each list and the 
nodes that were attached to the lists. 

## Testing

I used the given files, buddy-unit-test, buddy-test, and malloc-test a lot 
during the implementation of this project. I also used gdb to try to single step 
through my code when I was seg faulting and that was pretty difficult to really 
put my finger on what the problem was but it was valuable tool for testing.

## Known Bugs

Right now, I have a bug when running the buddy-test file with any number of tests 
greater than 38. My buddy_malloc() function seems to be the problem here and I 
tried to debug it using gdb, but couldn't really pinpoint the problem. I tried the 
majority of Thursday before finally finishing up my project to be turned in and 
couldn't fix the issue. It's something that I hope to receive feedback on and return 
later on to fix thte issue so I can see where my mistake was.

## Reflection and Self Assessment

This was definitely the most difficult project for me thus far in the class. It also 
happened to be the one that I feel made the most sense conceptually in my mind which 
is kind of weird that I struggled the most on it. Even though I struggled quite a bit, 
I enjoyed the challenge and look forward to the feedback that I receive so that I can 
hopefully return to this project and fix the issue and understand where I was going 
wrong and what I could have done differently. I also feel like this project has 
taught me the most so far in this class having struggled and tried many different 
things to try and fix the issue. I also feel like the issue is probably something 
simple that I'm completely overlooking. I look forward to the next project.

## Sources Used

* Stackoverflow
* Whiteboard / lecture notes
* Slack channel
* Textbook
* Youtube
