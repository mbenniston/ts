#pragma once

#include <vector>
#include <string>

class TaskList
{
private:
    std::vector<std::string> m_tasks;

    // Flag used to indicate that the task list has been modified and should be written back to the file
    bool m_writeBack = false;

    void load();
    void write();

public:

    // Returns the number of tasks 
    size_t getTaskCount() const;

    // Adds a single task to the list
    void add(const std::string& message);
    
    // Removes a single task from the end of the list and returns it
    std::string pop();

    // Removes a specified number of tasks from the list and returns them
    std::vector<std::string> pop(size_t n);
    
    // Returns the list of tasks
    const std::vector<std::string>& getTasks() const;

    // Clears the task list
    void clear();

    // Loads the task list from the file path set in config.h
    TaskList();

    // Writes the tasks list if it was modified to the file path set in config.h
    ~TaskList();
};
