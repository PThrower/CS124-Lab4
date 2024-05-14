#pragma once
#include <string>
#include "task.h"
#include "linkedStack.h"

using namespace std;

class TaskList : public LinkedStack<Task> {

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