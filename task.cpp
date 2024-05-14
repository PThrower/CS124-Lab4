/**
* Author: John Doe
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 10/24/2024
*/

#include <string>
#include "task.h"

using namespace std;

// Constructor
Task::Task() : status(0) {}

// Destructor
Task::~Task() {}

void Task::setStartDate(string date) {
	startDate.setDate(date);
}

void Task::setEndDate(string date) {
	endDate.setDate(date);
}

DateTime Task::getStartDate() const {
	return startDate;
}

DateTime Task::getEndDate() const {
	return endDate;
}

bool Task::isCompleted() const {
	return status == 1;
}

bool Task::operator >= (const Task& task) const {
	return (name >= task.name);
}

bool Task::operator == (const Task& task) const {
	return (name == task.name);
}

Task& Task::operator=(const Task& task) {
	if (this != &task) {
		this->term = task.getTerm();
		this->name = task.getName();
		status = task.isCompleted();
		startDate.setDate(task.getStartDate().toString());
		endDate.setDate(task.getEndDate().toString());
	}
	return *this;
}

istream& operator>>(istream& in, Task& task) {
	string term, name, sdate, edate, status;	
	string s = task.getTerm() != "" ? "(" + task.getTerm() + ")" : "";
	cout << "Enter term " << s << ": ";
	in.ignore();
	getline(in, term);
	if (!term.empty()) {
		task.setTerm(term);
	}

	s = task.getName() != "" ? "(" + task.getName() + ")" : "";
	cout << "Enter name " << s << ": ";		
	getline(in, name);
	if (!name.empty()) {
		task.setName(name);
	}

	s = !task.getStartDate().toString().empty() ? task.getStartDate().toString() : "MM-DD-YYYY";
	s = "(" + s + ")";
	cout << "Enter start date " << s << ": ";	
	getline(in, sdate);
	if (!sdate.empty()) {
		task.setStartDate(sdate + " 00:00:00");
	}

	s = !task.getEndDate().toString().empty() ? task.getEndDate().toString() : "MM-DD-YYYY";
	s = "(" + s + ")";
	cout << "Enter end date " << s << ": ";	
	getline(in, edate);
	if (!edate.empty()) {
		task.setEndDate(edate + " 00:00:00");
	}

	cout << "Enter status" << " (0=Pending; 1=DONE): ";
	getline(in, status);
	if (!status.empty()) {
		task.setStatus(stoi(status));
	}

	return in;
}

// friend function to allow ostream << operator to work with Task object
ostream& operator<<(ostream& out, const Task& task) {
	string s = task.getTerm();
	s += "," + task.getName();
	s += "," + task.getStartDate().toString();
	s += "," + task.getEndDate().toString();
	s += "," + task.isCompleted();	
	out << s;
	return out;
}