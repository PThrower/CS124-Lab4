#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include "task.h"
#include "hashTable.h"

using namespace std;

class TaskList : public HashTable<Task> {

public:
	TaskList() : HashTable<Task>() {}
	~TaskList();

	void addNew();
	void editTask();
	void deleteTask();	
	void printTable(bool complete = true);

protected:
	void printRaw(bool complete = true);
	void printRow(const Task task);

private:
	void printHeader();
	unordered_map<string, Task> pendingTasks; // Change HashTable to unordered_map
    unordered_map<string, Task> tasks;
    map<string, Task> completedTasks; // Change HashTable to unordered_map
};