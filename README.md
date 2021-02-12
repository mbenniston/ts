
# TS: Task Stacking

Super simple task management application using a single list of tasks. 

## Operations

### push
``` ts add "My task description" ```

### pop
``` ts pop ```
Removes the latest task from the list and prints it.

### pop n
``` ts pop 3 ```
Removes a certain task from the list and prints it. 

### list
``` ts list ```
Lists all the tasks currently on the stack

### clear
``` ts clear ```
Removes all the tasks from the list

## Building

Run ``` make``` in the directory to build the program. For building on Windows use WSL, mingw32 etc.   

## Installation

Add the program to the your path or someplace that is already pointed to by the path (such as /usr/local/bin)