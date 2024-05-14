/**
* Author: Parnell Thrower III
* Description: Changed the member functions to template type.
* Due Date: 5/13/2024
*/

#include <iostream>
#include <string>
#include <vector>
#include "menu.h"

using namespace std;

/**
* Initial menu name
*/
template <typename T >
Menu<T>::Menu(T name) {
    this->name = name;
}

/**
* Add menu open name
*/
template <typename T >
void Menu<T>::addOption(T option) {
    options.push_back(option);
}

/**
* Dipslay option nam
*/
template <typename T >
void Menu<T>::display() const {
    cout << "***** " << name << " *****" << endl;
    for (int i = 0; i < (int)options.size(); i++) {
        cout << options[i] << endl;
    }
    cout << "\nEnter choice: ";
}

/**
* Display ordered index and option name
*/
template <typename T >
void Menu<T>::displayPrefixIndex() const {
    cout << "***** " << name << " *****" << endl;
    for (int i = 0; i < (int)options.size(); i++) {
        cout << i + 1 << ") " << options[i] << endl;
    }
    cout << "\nEnter choice: ";
}
/**
* Display option menu, option name; and ask users to select a choice by index
*/
template <typename T >
int Menu<T>::doMenuIndex() const {
    char ch;
    int input = 0;
    do {
        displayPrefixIndex();
        cin >> ch;
        input = static_cast<int>(ch) - 48;
    } while (input < 1 || input >(int)options.size());
    return input;
}

/**
* Display option menu, option name; and ask users to select a choice
*/
template <typename T >
int Menu<T>::doMenu() const {
    int input = 0;
    do {
        display();
        cin >> input;
    } while (input < 1 || input >(int)options.size());
    return input;
}

/**
* Display option menu, option name; and ask users to select a choice
*/
template <typename T >
char Menu<T>::doMenuOption() const {
    char input;
    display();
    cin >> input;
    return input;
}