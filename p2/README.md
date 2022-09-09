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

```console
$make
```

``` console
$sudo insmod lexus.ko
```

``` console
$./lexus-test[1-3].sh
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
