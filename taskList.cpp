/**
* Author: Parnell Thrower
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 4/20/2024
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "taskList.h"
#include "task.h"
#include "taskMenu.h"

using namespace std;

TaskList::TaskList() {}

TaskList::~TaskList() {}

void TaskList::addNew() {
    Task task;
    cin >> task;
	tasks.insert(make_pair(task.getName(), task));
}

/*void TaskList::addNew() {	
	Task task;
	cin >> task;
	push(task);
}*/


void TaskList::editTask() {
    string name;
    cout << "Edit task name: ";
    cin.ignore();
    getline(cin, name);

    auto it = tasks.find(name);
    if (it != tasks.end()) {
        cin >> it->second; // Assuming operator>> is overloaded for Task class
        cout << "Task edited successfully." << endl;
    } else {
        cout << "Task not found." << endl;
    }
}

/*void TaskList::editTask() {
	TaskList tmpList = *this;
	TaskList newList;
	string name;
	cout << "Edit task name: ";
	cin.ignore();
	getline(cin, name);
	while (!tmpList.isEmpty()) {
		if (tmpList.top().getName() == name) {
			// edit - top is actually a task
			cin >> tmpList.top();
		}
		newList.push(tmpList.top());
		tmpList.pop();
	}
	this->initialize();
	newList.reverseStack(*this);
}*/

void TaskList::deleteTask() {
    string name;
    cout << "Delete task name: ";
    cin.ignore();
    getline(cin, name);

    auto it = tasks.find(name);
    if (it != tasks.end()) {
        tasks.erase(it);
        cout << "Task deleted successfully." << endl;
    } else {
        cout << "Task not found." << endl;
    }
}

/*void TaskList::deleteTask() {
	TaskList tmpList = *this;
	TaskList newList;
	string name;
	cout << "Delete task name: ";
	cin.ignore();
	getline(cin, name);
	bool deleteMe = false;
	while (!tmpList.isEmpty()) {
		if (tmpList.top().getName() == name) {
			deleteMe = true;
		}
		if (!deleteMe) {
			newList.push(tmpList.top());
		}
		tmpList.pop();
		deleteMe = false;
	}
	this->initialize();
	newList.reverseStack(*this);
}*/

void TaskList::printTable(bool complete) {
    // Show header
    printHeader();

    // Iterate through the map
    for (const auto& pair : tasks) {
        const Task& task = pair.second;
        if (task.isCompleted() == complete) {
            printRow(task);
        }
    }
    cout << endl;
}

/*void TaskList::printTable(bool complete) {
	// assignment operator
	TaskList tmpList = *this;

	// reverse the list
	TaskList reverseList;
	tmpList.reverseStack(reverseList);

	// Show pending tasks
	printHeader();
	while (!reverseList.isEmpty()) {
		if (reverseList.top().isCompleted() == complete) {
			printRow(reverseList.top());
		}
		reverseList.pop();
	}	
	cout << endl;
}*/

void TaskList::printHeader() {
	const char originalFill = cout.fill();
	cout << left << setw(10) << "Term"
		<< left << setw(30) << "Name"
		<< left << setw(15) << "Start Date"
		<< left << setw(15) << "End Date"
		<< left << setw(10) << "Status"
		<< endl;
	cout << setfill('=') << setw(80) << "=" << endl;
	cout.fill(originalFill);
}

void TaskList::printRow(const Task task) {
	const char originalFill = cout.fill();
	cout << left << setw(10) << task.getTerm()
		<< left << setw(30) << task.getName()
		<< left << setw(15) << task.getStartDate().toString()
		<< left << setw(15) << task.getEndDate().toString()
		<< left << setw(10) << (task.isCompleted() ? "Done" : "Pending")
		<< endl;
	cout.fill(originalFill);
}

void TaskList::printRaw(bool complete) {
    // Iterate through the map
    for (const auto& pair : tasks) {
        const Task& task = pair.second;
        if (task.isCompleted() == complete) {
            cout << task << endl;
        }
    }
    cout << endl;
}

/*void TaskList::printRaw(bool complete) {
	// assignment operator
	TaskList tmpList = *this;	

	// reverse the list
	TaskList reverseList;
	tmpList.reverseStack(reverseList);

	// Show pending tasks
	while (!reverseList.isEmpty()) {
		if (reverseList.top().isCompleted() == complete) {
			cout << reverseList.top() << endl;
		}
		reverseList.pop();
	}
	cout << endl;
}*/