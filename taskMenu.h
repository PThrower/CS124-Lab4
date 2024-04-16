/**
* Author: Parnell Thrower
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 4/20/2024
*/

#pragma once
#include <fstream>
#include "menu.h"
#include "task.h"
#include "hashTable.h"

using namespace std;

const string TASK_DATA = "task_data.csv";
enum COMMAND { ADD='a', EDIT='e', DELETE='d', PENDING = 'p', DONE = 'c', EXIT = 'x' };

template <typename T>
class TaskMenu :public Menu {
public:
    TaskMenu();
    ~TaskMenu();

    void viewPendingTasks();
    void viewCompletedTasks();
    void addNewTask();
    void editTask();
    void deleteTask();
    void activate();

protected:
    void init();
    void showOption(string title);

private:
    fstream inFile;
    HashTable<T>* list;
};
