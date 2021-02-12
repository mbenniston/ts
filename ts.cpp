#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "config.h"
#include "TaskList.hpp"

// Function to encapsulate execption thrown by std::stoi 
static bool stringToInt(const std::string& str, int& out)
{
    try {
        out = std::stoi(str);
    } catch(const std::invalid_argument& invArg) {
        return false;
    } 

    return true;
}

int popCommand(TaskList& taskList);
int popCommand(TaskList& taskList, const std::string& arg);
void listCommand(const TaskList& taskList);

int main(int argc, char** argv)
{
    /*
        Commands are add, pop, pop n, list and clear
        always requires at least one argument, the command
    */
    
    // Check if command is present
    if(argc < 2) {
        std::cout << "Please provide a command: [add, pop, pop n, list, clear]" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    // Load task list
    TaskList taskList;

    // Process command
    if(command == "add")
    { 
        if(argc >= 3) {
            taskList.add(argv[2]);
        } else {
            std::cout << "Please provide a message!" << std::endl;
            return 1;
        }
    } 
    else if(command == "pop")
    { 
        // Check for 'n' parameter for the pop command
        if(argc == 3) { 
            return popCommand(taskList, argv[2]);
        } else if(argc == 2) { 
            return popCommand(taskList);
        } else {
            std::cout << "Too many arguments!" << std::endl; 
            return 1;
        }
    } 
    else if(command == "list")
    { 
        listCommand(taskList);
    } 
    else if(command == "clear")
    { 
        taskList.clear();
    } 
    else
    {
        std::cout << "Unknown command: " << command << "!" << std::endl;
        return 1;
    }

    return 0;
}

int popCommand(TaskList& taskList)
{
    // Check if the tasklist is not empty  
    if(taskList.getTaskCount() != 0) { 

        // Pop the task
        std::string task = taskList.pop();
        
        // Print the popped task
        std::cout << task << std::endl;
    } else {
        std::cout << "No tasks to pop!" << std::endl;
        return 1;
    }	

    return 0;	
}

// Try to process argument as a number then pop that many tasks off of the stack
// the number is clamped between zero and number of tasks.  
int popCommand(TaskList& taskList, const std::string& arg)
{
    int numToPop = 0;

    // Try to parse argument
    bool successful = stringToInt(arg, numToPop);

    if(!successful) {
        std::cout << "Argument given was not a number!" << std::endl;
        return 1;
    }

    // Clamp the number of tasks 
    numToPop = std::max(0, numToPop);
    numToPop = std::min(numToPop, (int)taskList.getTaskCount());

    // Pop the tasks
    std::vector<std::string> tasks = taskList.pop(numToPop);

    // Print the popped tasks
    for(const std::string& task : tasks) {
        std::cout << task << std::endl;
    }

    return 0;
}

void listCommand(const TaskList& taskList)
{
    // Get the tasks
    std::vector<std::string> tasks = taskList.getTasks();

    // Print the tasks with the task index prefixed to the output
    for(size_t i = 0; i < tasks.size(); i++) { 
        std::cout << i << ":" << tasks[i] << std::endl;
    }
}