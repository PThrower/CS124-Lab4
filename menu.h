/*Changes made on lines 16 and 56. Line 16 allows for HashTable<T> options 
to exist and be used in this class. On line 56 I change the variable from a vector of strings to a
HashTable object.
*/

#pragma once

#include <iostream>
#include <string>
#include "hashTable.h"

using namespace std;

/**
   General purpose class menu
*/

template <typename T>
class Menu : public HashTable<Task> {
public:
    Menu() {};

    /**
       Constructs a menu with no options.
    */
    Menu(T name);

    void setName(T name) {
        this->name = name;
    }

    string getName(T index) const {
        return options.at(index);
    }

    /**
       Adds an option to the end of this menu.
       @param option the option to add
    */
    void addOption(T option);
    /**
       Displays the menu, with options numbered starting with 1,
       and prompts the user for input. Repeats until a valid input
       is supplied.
       @return the number that the user supplied
    */
    int doMenu() const;
    int doMenuIndex() const;
    char doMenuOption() const;

    bool hasOption() const {
        return options.size() > 0;
    };
private:
    void display() const;
    void displayPrefixIndex() const;

    string name;
    HashTable<T> options;
};