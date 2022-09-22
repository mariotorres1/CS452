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
'$make'

Then we can run the buddy-unit-test files:
'$buddy-unit-test [s | t | v | i]'

Finally, we can run the buddy-test and malloc tests:
'$buddy-test <num of tests> [random seed] [s | t | v | i]'
'$malloc-test <num of tests> [random seed] [s | t | v | i]'
  
We can also time those tests by using:
``` console
  $time buddy-test <num of tests> [random seed] [s | t | v | i]
  $time malloc-test <num of tests> [random seed] [s | t | v | i]
```

## Features and usage

Summarize the main features of your program. It is also appropriate to
instruct the user how to use your program.

## Testing

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs to
be detailed here.

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
