/**
* Author: Parnell Thrower
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 4/20/2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "taskMenu.h"
#include "menu.h"
#include "dateTime.h"
#include "taskList.h"

using namespace std;

TaskMenu::TaskMenu(unordered_map<string, Task>& tasks) : tasks(tasks), Menu("Main Menu") {
	addOption("a) Add task");
	addOption("e) Edit task");
	addOption("d) Delete task");
	addOption("p) List pending tasks");
	addOption("c) List completed tasks");
	addOption("x) Exit");

	list = new TaskList();
	init();
}
TaskMenu::~TaskMenu() {	
	delete list;
	inFile.close();
}

void TaskMenu::init() {
    inFile.open(TASK_DATA);

    string text;
    string line = "";
    bool firstRow = true;
    while (getline(inFile, line)) {
        // Skip the first row
        if (firstRow) {
            firstRow = false;
            continue;
        }
        stringstream ss(line);
        Task task;
        getline(ss, text, ',');
        task.setTerm(text);
        getline(ss, text, ',');
        task.setName(text);
        getline(ss, text, ',');
        task.setStartDate(text);
        getline(ss, text, ',');
        task.setEndDate(text);
        getline(ss, text, ',');
        task.setStatus(stoi(text));    // value =1 means DONE! and value = 0 is pending

        // Add the task to the map
        tasks.insert({task.getName(), task});
    }
    inFile.close();
}

/*void TaskMenu::init() {
	inFile.open(TASK_DATA);

	string text;
	string line = "";
	bool firstRow = true;
	while (getline(inFile, line)) {
		// Skip the first row
		if (firstRow) {
			firstRow = false;
			continue;
		}
		stringstream ss(line);		
		Task task;
		getline(ss, text, ',');
		task.setTerm(text);
		getline(ss, text, ',');
		task.setName(text);
		getline(ss, text, ',');
		task.setStartDate(text);
		getline(ss, text, ',');
		task.setEndDate(text);
		getline(ss, text, ',');
		task.setStatus(stoi(text));	// value =1 means DONE! and value = 0 is pending
		list->push(task);
	}
	inFile.close();
}*/

void TaskMenu::viewPendingTasks() {
	showOption(getName(3).substr(3));
	list->printTable(false);
}

void TaskMenu::viewCompletedTasks() {
	showOption(getName(4).substr(3));
	list->printTable(true);
}

void TaskMenu::addNewTask() {
	showOption(getName(0).substr(3));
	list->addNew();
	cout << endl;
}

void TaskMenu::editTask() {
	showOption(getName(1).substr(3));
	list->editTask();
	cout << endl;
}

void TaskMenu::deleteTask() {
	showOption(getName(2).substr(3));	
	list->deleteTask();
	cout << endl;
}

void TaskMenu::activate() {
	char command = COMMAND::ADD;
	while (command != EXIT) {
		command = doMenuOption();
		switch (command) {		
		case ADD:
			addNewTask();
			break;
		case EDIT:
			editTask();
			break;
		case DELETE:
			deleteTask();
			break;
		case PENDING:
			viewPendingTasks();
			break;
		case DONE:
			viewCompletedTasks();
			break;
		case EXIT:
			cout << "Bye!" << endl;
			break;
		default:
			cout << "Not a valid command. Please try again." << endl << endl;
			break;
		}
	}	
}

void TaskMenu::showOption(const string title) {
	cout << "***** " << title << " *****" << endl;
}