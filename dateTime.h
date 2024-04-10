/**
* Author: Parnell Thrower
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 4/20/2024
*/

#pragma once
#include "dateType.h"

using namespace std;

class DateTime : public DateType {
public:
	DateTime(int h = 0, int mi = 0, int s = 0, int mo = 0, int d = 0, int y = 0);
	~DateTime() {};

	//Mutator functions
	void setHour(int h) {
		hr = h; 
	};
	void setMinute(int m) { 
		min = m; 
	};
	void setSecond(int s) {
		sec = s; 
	};

	//Sets the time by passing in a string in mm/dd/yyyy hr:min:sec
	void setDateTime(string);

	//Accessor functions
	int getHour() const { return hr; };
	int getMinute() const { return min; };
	int getSecond() const { return sec; };

	string toString(); // return mm/dd/yyyy hh:mm:ss

	bool isEmpty() const {
		return hr == 0 && min == 0 && sec == 0;
	};

private:
	int hr;  //variable to store the hours
	int min; //variable to store the minutes
	int sec; //variable to store the seconds
};