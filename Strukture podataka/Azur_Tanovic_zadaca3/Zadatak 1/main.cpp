#include <iostream>
#include "mojaLista.hpp"
#include "ToDoTask.hpp"
#include <initializer_list>

void menu() {
    std::cout << "Choose one of the options:" << std::endl;
    std::cout << std::string(40,'*') << std::endl;
    std::cout << "1. Display the current list of ToDoTask" << std::endl;
    std::cout << "2. Enter a new ToDoTask" << std::endl;
    std::cout << "3. Mark ToDoTask as done" << std::endl;
    std::cout << "Enter your choice: ";
}


int main() {
    mojaLista<ToDoTask> list;
    int choice = -1, choiceId;
    while(choice != 0) {
        menu();
        std::cin >> choice;
        std::cout << std::string(40,'*') << std::endl;

        if(choice == 1) {
            if(list.empty()) {
                std::cout << "Your list is empty." << std::endl;
            }
            else {
                std::cout << list;
            }

        }else if (choice == 2) {
            ToDoTask temp;
            temp.createTask();
            list.add(std::move(temp));
        }
        else if (choice == 3) {
            if(list.empty()) {
                std::cout << "Your list is empty." << std::endl;
            }
            else {
                std::cout << std::string(40, '*') << std::endl;
                for (auto it=list.begin(); it!=list.end(); ++it) {
                    it -> printWithId();
                    std::cout << std::endl;
                }
                std::cout << std::string(40, '*') << std::endl;
                std::cout << "Enter id of the task which you want to mark as done: ";
                std::cin >> choiceId;
                auto predicate = [choiceId](const ToDoTask& task) {return task.id == choiceId;};
                auto taskToRemove = list.find(predicate);
                if(taskToRemove == list.end()) {
                    std::cout << "Task with id = " << choiceId << " does not exist." << std::endl;
                }
                else {
                    list.remove(taskToRemove);
                }
            }

        }
        std::cout << "Enter number 0 to exit program, or something else to continue: ";
        std::cin >> choice;
        std::cout << std::endl;
    }
}
