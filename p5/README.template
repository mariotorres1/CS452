## Project 5

* Author: Mario Torres
* Class: CS452/CS552 [Operating Systems]

## Overview

In this program, we implemented a multi-threaded version of the merge sort algorithm. 
We did this using the pthread library. 

## Manifest

This project includes these files: 
* Makefile - Builds the executible files
* example.png - Example picture of mergesort
* flow.png - picture showing pthread_create and pthread_join
* mergesort.c - Source code file
* mergesort.h - Header file
* runval.sh - Script to test for memory leaks
* test-mergesort.c - Test file 
* README.orig - Original readme explaining the project 
* README.md - This file

## Building the project

Run make:
``` console
$make
```

To run test for memory leaks:
``` console
$./runval.sh
```

To run the test file:
``` console
$./test-mergesort <input size> <cutoff level> <seed>
```

## Features and usage

In this project, we had to implement four functions: mergesort(), merge(), 
parallel_mergesort, and buildArgs(). mergesort() and merge() are the basic 
mergesort algorithm functions. parallel_mergesort() is similar to the original 
mergesort() function but this function runs on multiple threads. The final 
function we implemented was buildArgs() which we only create because pthread_create() 
only accepts a void * type pointer as one of it's parameters and this function takes 
care of that issue. 

## Testing

To test this project, I used the two test files that were provided, runval.sh and 
test-mergesort.c. Using these two files, I was able to test the project pretty 
easy and I felt pretty confident in my program from these tests.

## Known Bugs

N/A

## Reflection and Self Assessment

This project was pretty simple compared to the recent projects we've been working 
on in this class. It was a nice little change of speed and gave me some time to 
recharge for the final stretch coming up. I've implemented the mergesort algorithm 
a couple times in the past couple years which helped me a lot for this project as 
well. I didn't have to really struggle through any issues implementing this one like 
I have in the previous projects. It think it was pretty cool to see mergesort run 
multi threaded, it's the first time I've created anything multi threaded. I've 
heard of this topic quite a bit the past year or so and to finally be able to work 
with it was something I enjoyed and hope to be able to work with again in the future. 
Overall, I enjoyed the project and think I'm getting better as a coder the further 
we move along this semester. 

## Sources Used

* Class notes 
* Class whiteboard code 
* Previous mergesort code I've created
* Stackoverflow
