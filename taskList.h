#pragma once
#include <string>
#include "task.h"
#include "hashTable.h"

using namespace std;

class TaskList : public HashTable<Task> {

public:
	TaskList();
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
};