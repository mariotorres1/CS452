## Project 4

* Author: Mario Torres
* Class: CS452/CS552 [Operating Systems]

## Overview

This is an implementation of a page fault handler for a 64-bit x86 system

## Manifest

* user - Folder holding the test files
* Makefile - Makes all the files to be run
* fault.c - Main source file where we implement our two functions
* fault.h - Header file for our source file
* infiniti.h - Header file for main file
* infiniti_main.c - Main file that runs 
* README.orig - Original readme that has the project details
* README.md - This file

## Building the project

We need to run make in our main folder: 
``` console
$ make
```   

We then implement our module:
``` console 
$ sudo insmod infiniti.ko
```   

Then we open our user folder and run make in that folder:
``` console
$ cd user
$ make
```   

From here, we run each of our test files:

``` console 
$ ./infiniti-test1
```   

## Features and usage

For this project, we implemented two functions. They were infiniti_do_page_fault(), 
and infiniti_free_pa(). The first function, infiniti_do_page_fault() is the function 
that is called when the application triggers a page fault. We update the page tables 
at a given mermory location in the kernel. The other function we implemented was 
infiniti_free_pa(). In this function we update and free the tables in a memory 
address in the kernel. 

## Testing

For testing, I used the test files that were given with the project and matched  
my results with the expected results. This was my main source for testing and I used  
those files a lot, especially infiniti-test2 because I was struggling to get it  
right. I was finally able to fix the issue which I will discuss later in my reflection  
and selft assessment portion. I will attach a photo of my results working here though:  

![Capture](https://user-images.githubusercontent.com/85824580/194459003-abc9d9f7-d51f-4f0a-9450-ccda20f7f451.jpg)

## Known Bugs

N/A

## Reflection and Self Assessment

This project was a little weird for me, I originally struggled with the concept of what  
we needed to do but once I was able to wrap my head around the concept, it went fairly  
smooth. I feel I'm getting better at these types of programs and starting to enjoy them  
more and more as we continue on in this semester. The one thing I did struggle with was  
with infiniti-test2, I was getting Hello Boise! printed twice instead of a seg fault on  
the second one. I couldn't figure it out after looking at it for a couple hours, so I  
actually went and redid the entire funtion. I went through the process like I was creating  
it for the first time and was able to find my mistake this way. I had a number that was wrong  
and it through it off. I really enjoyed the accomplishment I felt figuring out that bug after  
not being able to do so and my previous project. I think it shows that I'm not only getting  
better at these types of programming assignments but also at figuring out small bugs that  
are causing issues in my programs. Overall, I think I'm getting better every week and  
from project to project. 

## Sources Used

* Lecture Notes
* Whiteboard Notes
* Discussions with other students
* Discord 
* Slack 
