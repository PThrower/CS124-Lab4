/**
* Author: John Doe
* Description: Manage Tasks using Map, HashTable, and Try-Catch
* Due Date: 10/24/2024
*/
#ifndef H_STACK_Type
#define H_STACK_Type

#include <iostream> 
#include <cassert>

#include "stack.h"

using namespace std;

//Definition of the node
template <typename T>
class Node {
public:
	T info;
	Node<T>* link = nullptr;
};

template <typename T>
class LinkedStack : public Stack<T> {
public:

	//Default constructor
	//Postcondition: stackTop = nullptr;
	LinkedStack();

	//Copy constructor
	LinkedStack(const LinkedStack<T>& otherStack);

	//Destructor
	//Postcondition: All the elements of the stack are 
	//               removed from the stack.
	~LinkedStack();

	//Function to determine whether the stack is empty.
	//Postcondition: Returns true if the stack is empty;
	//               otherwise returns false.
	bool isEmpty() const;

	//Function to determine whether the stack is full.
	//Postcondition: Returns false.
	bool isFull() const;

	//Function to initialize the stack to an empty state. 
	//Postcondition: The stack elements are removed; 
	//               stackTop = nullptr;
	void initialize();

	//Function to add newItem to the stack.
	//Precondition: The stack exists and is not full.
	//Postcondition: The stack is changed and newItem 
	//               is added to the top of the stack.
	void push(const T& newItem);

	//Function to return the top element of the stack.
	//Precondition: The stack exists and is not empty.
	//Postcondition: If the stack is empty, the program 
	//               terminates; otherwise, the top 
	//               element of the stack is returned.
	T& top() const;

	//Function to remove the top element of the stack.
	//Precondition: The stack exists and is not empty.
	//Postcondition: The stack is changed and the top 
	//               element is removed from the stack.
	void pop();

	void reverseStack(LinkedStack<T>& otherStack);

	//Overload the assignment operator.
	const LinkedStack<T>& operator=(const LinkedStack<T>&);

private:
	Node<T>* stackTop; //pointer to the stack

	void copyStack(const LinkedStack<T>& otherStack);
	//Function to make a copy of otherStack.
	//Postcondition: A copy of otherStack is created and
	//               assigned to this stack.
};


//Default constructor
template <typename T>
LinkedStack<T>::LinkedStack() {
	stackTop = nullptr;
}
//copy constructor
template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& otherStack) {
	stackTop = nullptr;
	copyStack(otherStack);
}//end copy constructor

//destructor
template <typename T>
LinkedStack<T>::~LinkedStack() {
	initialize();
}//end destructor


template <typename T>
bool LinkedStack<T>::isEmpty() const {
	return(stackTop == nullptr);
} //end isEmptyStack

template <typename T>
bool LinkedStack<T>::isFull() const {
	return false;
} //end isFullStack

template <typename T>
void LinkedStack<T>::initialize() {
	Node<T>* temp; //pointer to delete the node

	while (stackTop != nullptr)  //while there are elements in the stack
	{
		temp = stackTop;    //set temp to point to the 
		//current node
		stackTop = stackTop->link;  //advance stackTop to the
		//next node
		delete temp;    //deallocate memory occupied by temp
	}
} //end initializeStack


template <typename T>
void LinkedStack<T>::push(const T& newElement) {
	Node<T>* newNode;  //pointer to create the new node

	newNode = new Node<T>; //create the node

	newNode->info = newElement; //store newElement in the node
	newNode->link = stackTop; //insert newNode before stackTop
	stackTop = newNode;       //set stackTop to point to the 
	//top node
} //end push


template <typename T>
T& LinkedStack<T>::top() const {
	assert(stackTop != nullptr); //if stack is empty,
	//terminate the program
	return stackTop->info;    //return the top element 
}//end top

template <typename T>
void LinkedStack<T>::pop() {
	Node<T>* temp;   //pointer to deallocate memory

	if (stackTop != nullptr) {
		temp = stackTop;  //set temp to point to the top node

		stackTop = stackTop->link;  //advance stackTop to the 
		//next node
		delete temp;    //delete the top node
	}
	else {
		cout << "Cannot remove from an empty stack." << endl;
	}
}//end pop

template <typename T>
void LinkedStack<T>::copyStack (const LinkedStack<T>& otherStack) {
	Node<T>* newNode, * current, * last;

	if (stackTop != nullptr) { //if stack is nonempty, make it empty
		initialize();
	}

	if (otherStack.stackTop == nullptr) {
		stackTop = nullptr;
	}
	else {
		current = otherStack.stackTop;  //set current to point
		//to the stack to be copied

		//copy the stackTop element of the stack 
		stackTop = new Node<T>;  //create the node

		stackTop->info = current->info; //copy the info
		stackTop->link = nullptr;  //set the link field of the
		//node to nullptr
		last = stackTop;        //set last to point to the node
		current = current->link;    //set current to point to
		//the next node

		//copy the remaining stack
		while (current != nullptr) {
			newNode = new Node<T>;

			newNode->info = current->info;
			newNode->link = nullptr;
			last->link = newNode;
			last = newNode;
			current = current->link;
		}//end while
	}//end else
} //end copyStack

template<typename T>
void LinkedStack<T>::reverseStack(LinkedStack<T>& otherStack) {
	Node<T>* current = stackTop;

	if (otherStack.stackTop != nullptr) {
		otherStack.initialize();
	}

	while (current != nullptr) {
		otherStack.push(current->info);
		current = current->link;
	}
}

//overloading the assignment operator
template <typename T>
const LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& otherStack) {
	if (this != &otherStack) { //avoid self-copy
		copyStack(otherStack);
	}
	return *this;
}//end operator=

#endif