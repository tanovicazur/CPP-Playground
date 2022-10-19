#pragma once
#include <string>

#include <iostream>

struct ToDoTask {
    int id;
    std::string title;
    std::string description;
    int priority;

    ToDoTask(): id{0}, title{""}, description{""}, priority{0} {};

    ToDoTask& createTask() {
        std::cout << "Enter a new ToDoTask:" << std::endl;
        std::cout << "Enter the title of the task: ";
        std::cin >> title;
        std::cout << "Enter the description of the task: ";
        std::cin >> description;
        std::cout << "Enter a priority (>0): ";
        std::cin >> priority;
        id = generateId();
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const ToDoTask& task) {
        out << std::string(8, '*') << std::endl;
        out << "* Task *" << std::endl;
        out << std::string(8, '*') << std::endl;
        out << "Title: " << task.title << std::endl;
        out << "Description: " << task.description << std::endl;
        out << "Priority: " << task.priority <<std::endl;
        return out << std::endl;
    }

    void printWithId() {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Priority: " << priority <<std::endl;
        std::cout << "Id: " << id <<std::endl;
    }

    bool operator<(const ToDoTask& other) {
        return priority < other.priority;
    }

    int generateId() {
        static int counter = 0;
        return ++counter;
    }
};
