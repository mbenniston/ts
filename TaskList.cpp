#include "TaskList.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "config.h"

// Helper function to strip whitespace from the end of loaded lines
static void rstrip(std::string& str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), 
        [](unsigned char c) { return !std::isspace(c); }).base(), str.end());
}

void TaskList::load() 
{
    std::ifstream stream(TASKS_FILE_PATH);
    if(!stream) { 
        std::cout << "Could not open file: " << TASKS_FILE_PATH << std::endl;
    }

    // Read each line adding it as seperate task
    std::string line;
    while(std::getline(stream, line)) {
        rstrip(line);
        if(!line.empty()) {
            m_tasks.push_back(line);
        }
    }
}

void TaskList::write()
{
    std::ofstream stream(TASKS_FILE_PATH);
    if(!stream) {
        std::cout << "Could not write to file: " << TASKS_FILE_PATH << std::endl;
    }

    // Write each task to a seperate line
    for(const std::string& task : m_tasks) {
        stream << task << std::endl;
    }

    m_writeBack = false;
}

size_t TaskList::getTaskCount() const 
{ 
    return m_tasks.size(); 
}

void TaskList::add(const std::string& message) 
{ 
    m_tasks.push_back(message); 
    m_writeBack = true; 
} 

std::string TaskList::pop() 
{
    if(m_tasks.empty())
        return std::string();

    std::string task = m_tasks.back();
    m_tasks.pop_back();
    m_writeBack = true;

    return task;
}

std::vector<std::string> TaskList::pop(size_t n)
{
    std::vector<std::string> outTasks;

    while(n != 0) {
        outTasks.push_back(pop());
        n--;
    }

    return outTasks;
}

const std::vector<std::string>& TaskList::getTasks() const 
{
    return m_tasks;
}

void TaskList::clear() 
{
    m_tasks.clear(); 
    m_writeBack = true; 
}

TaskList::TaskList()
{
    load();
}

TaskList::~TaskList()
{
    if(m_writeBack) 
        write();
}
