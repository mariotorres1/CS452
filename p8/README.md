## Project 8

* Author: Mario Torres
* Class: CS452/CS552 [Operating Systems]

## Overview

This program converts serves as a simple character device driver.

## Manifest

This project includes these files: 
* toyota_load - Loads the module
* toyota_unload - Removes the module
* toyota.h - Header file
* toyota.c - Source code file
* toyota-test1.c - First test file
* toyota-test2.c - Second test file
* toyota-test3.c - Third test file
* toyota-test4.c - Fourth test file
* README.orig - Readme that walks through the program and what we need to do
* README.md - This file

## Building the project

Run make:
``` console
$make
```

Upload the module:
``` console
$sudo ./toyota_load
```

To run the tests for the project (1 can be replaced with the other test files):
``` console
$time ./toyota-test1
```

To remove the module
``` console
$sudo ./toyota_unload
```

## Features and usage

For this project, we had to implement 6 functions: toyota_open(), toyota_release(), 
toyota_read(), toyota_write(), toyota_init(), and toyota_exit(). I also added a 
helper function for toyota_read() called toyota_read_helper(). The toyota_init() and 
toyota_exit() functions do as they sound, we initalize and exit in those functions. 
The toyota_open() and toyota_release() functions were also pretty simple to implement 
as the first two. The majority of my work was in the toyota_write() and toyota_read() 
functions which brought in the added function as well. These functions wrote the 
characters and read them as well. The toyota_read_helper function() removed duplicates 
when we are reading the characters, it also kept the order the same while doing this. 

## Testing

To test my program, I used the test files that were given with the project along with 
the debugger for any issues that came up during my implementation. I compared the results 
that my code gave with the expected results in the README.orig file.

## Known Bugs

I don't know if this is a bug or not but for the first test, the README.orig has the read 
function returning read failed: . While my results just come back with 0 characters were read. 
To me that is the same result, just different way of showing that but I don't know if that 
could be considered wrong and a bug. 

## Reflection and Self Assessment

After the last couple projects being pretty tough and me completely skipping the one before 
this, it was nice to have a litter easier project that I understood better. It's always nice 
to be challenged because that is what make us better but it's hard to always be challenged 
and struggling to figure something out. Sometimes we need a nice little project to reboot or 
get a little recharge and I think this project did just that. As a senior, I've actually been 
seeing a lot of embedded software engineer positions open and this class has helped me a lot 
in regards to feeling more confident in that area of programming. I feel like I could 
interview for those jobs now and for that, I'm grateful for the things I've learn thus far 
in this course. I look forward to getting better and getting back after those challenging '
projects.

## Sources Used

* Class notes 
* Class whiteboard code 
* Stackoverflow
