/**
* Author: Parnell Thrower
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 4/20/2024
*/

#include <iostream>
#include <iomanip>
#include "taskMenu.h"

using namespace std;

void showBanner();

int main() {
	showBanner();
	TaskMenu menu;
	menu.activate();

	return 0;
}

/**
 * showBanner - print me first
 **/
void showBanner() {
	const char originalFill = cout.fill();
	cout << setfill('*') << setw(50) << "*" << endl << endl;
	cout << "\tApplication to Manage Tasks" << endl;
	cout << "\t===========================" << endl;
	cout << "\tProgram written by: John Doe"<< endl;
	cout << "\tCourse info: CS-124-03" << endl;
	cout << "\tDue date: 4/20/2024"<< endl << endl;
	cout << setfill('*') << setw(50) << "*" << endl << endl;
	cout.fill(originalFill);
}