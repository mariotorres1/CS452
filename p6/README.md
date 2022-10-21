## Project 6

* Author: Mario Torres
* Class: CS452/CS552 [Operating Systems]

## Overview

This program converts an existing single-threaded web server into 
a multi=threaded web server or at least attempts to do so.

## Manifest

This project includes these files: 
* list - File that holds doubly linked list files
* item.c - Source file for our item struct / helper methods
* item.h - Helper file for item
* Makefile - Creates the executible files
* client.c - Source file that acts as the client
* server.c - Single-threaded server source file
* concurrent_server.c - Multi-threaded server source file
* spin.c - Generates a cgi script
* README.orig - Readme that walks through the program and what we need to do
* README.md - This file

## Building the project

Run make:
``` console
$make
```

To run with single-threaded web server, we need to start the server up:
``` console
$./server -p 8080
```

To run the client side (Can change the 4 in the second example to something different 
based on how many http requests you want to send):
``` console
$time ./client localhost 8080 /spin.cgi?5
$time seq 4 | xargs -n 1 -P 4 -I{} ./client localhost 8080 /spin.cgi?5
```

To run with multi-threaded web server, we need to start the server up (can change the thread 
value by changing the value 4): 
``` console
$./concurrent_server -p 8080 -t 4
```

To run the client side (Can change the 4 in the second example to something different 
based on how many http requests you want to send):
``` console
$time ./client localhost 8080 /spin.cgi?5
$time seq 4 | xargs -n 1 -P 4 -I{} ./client localhost 8080 /spin.cgi?5
```

## Features and usage

The two main functions we had to create in this project was the producer() and 
consumer() functions as well as mess with the main function some in concurrent_server.c. 
The producer() function would establish a special pipe between the client and the 
server everytime the client attempted to send an http request to the server. The 
consumer would handle these requests that are being sent to the server. 

## Testing

To test my program, I followed the project readme and used the same commands and 
checked to see if my program was responding the way it should have. I was having 
some weird results while testing my program, it would work for a little and then 
wouldn't work. I was basing this off the time it took to run the program and compared 
it to those outlined in the project readme. Here is a screenshot I got of it working:

4 threads and 2 http requests:
![4_2_working](https://user-images.githubusercontent.com/85824580/197112454-9a9bb6a0-059a-4abd-8477-a9aa659cdb5b.PNG)

## Known Bugs

By the end of me messing around with the program trying to fix why it was working at 
some points and not at others, it pretty much wasn't working at all with the changes 
I made. Having put myself in a hole with time, I didn't do much changes after that. I 
did have weird stuff like it outputting half the results on the server terminal and the 
other half on the client terminal like:

4 thread and 4 http requests server terminal:
![4_4_postinghalftoserver](https://user-images.githubusercontent.com/85824580/197112814-0ea3035e-805f-4347-b4d6-c635a00c568f.PNG)

4 thread and 4 http requests client terminal: 
![4_4_postinghalftoclient](https://user-images.githubusercontent.com/85824580/197112739-43886545-b235-4845-a419-9c279fc566a5.PNG)

## Reflection and Self Assessment

I put myself in a hole with this project because I didn't really start it until the day it 
was due. I had poor time management and a lot of other work to do so that combination really 
hurt me here. Even though I didn't perform like I wanted to with this program, I enjoyed the 
struggles I had and my attempts to fix the issues I was having. The project doesn't seem that 
hard and I feel I wasn't too far off so I should be able to fix my issues with the feedback 
I receive more that likely. I thought about just skipping the project as a whole but decided 
some points are better than none and I'm glad I decided to do that because the material was 
something I found interesting and it really captured my attention the whole day I was trying 
to finish the project. The multi=threaded concept is something I still find fascinating and 
will continue to dive deeper into even after this class is over with. I also didn't get a 
chance to properly comment my code because of the time crunch I was in, so I apologize for 
that.

## Sources Used

* Class notes 
* Class whiteboard code 
* Youtube
* Stackoverflow
