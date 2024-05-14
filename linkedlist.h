#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>

using namespace std;

template <typename T>
class LinkedList;
template <typename T>
class Iterator;

template <typename T>
class Node {
public:
    /**
        Constructs a node with a given data value.
        @param element the data to store in this node
    */
    Node(T element);

private:
    T data;
    Node *previous;
    Node *next;
    friend class LinkedList<T>;
    friend class Iterator<T>;
};

template <typename T>
class LinkedList {
public:
    /**
        Constructs an empty list.
    */
    LinkedList();
    /**
        Appends an element to the list.
        @param element the value to append
    */
    void push_back(T element);
    /**
        Inserts an element into the list.
        @param iter the position before which to insert
        @param element the value to insert
    */
    void insert(Iterator<T> iter, T element);
    /**
        Retrieves the k'th element of the list
        @param k the position to be retrieved (zero-based)
        @return the element at position k, error if no such position
    */
    T get(int k);
    /**
        Removes an element from the list.
        @param iter the position to remove
        @return an iterator pointing to the element after the
        erased element
    */
    Iterator<T> erase(Iterator<T> iter);
    /**
        Gets the beginning position of the list.
        @return an iterator pointing to the beginning of the list
    */
    Iterator<T> begin();
    /**
        Gets the past-the-end position of the list.
        @return an iterator pointing past the end of the list
    */
    Iterator<T> end();

private:
    Node<T> *first;
    Node<T> *last;
    Node<T> *last_node;
    int last_index;
    friend class Iterator<T>;
};

template <typename T>
class Iterator {
public:
    /**
        Constructs an iterator that does not point into any list.
    */
    Iterator();
    /**
        Looks up the value at a position.
        @return the value of the node to which the iterator points
    */
    T get() const;
    /**
        Advances the iterator to the next node.
    */
    void next();
    /**
        Moves the iterator to the previous node.
    */
    void previous();
    /**
        Compares two iterators.
        @param other the iterator to compare with this iterator
        @return true if this iterator and other are equal
    */
    bool equals(Iterator other) const;

private:
    Node<T> *position;
    LinkedList<T> *container;
    friend class LinkedList<T>;
};

template <typename T>
Node<T>::Node(T element) {
    data = element;
    previous = nullptr;
    next = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList() {
    first = nullptr;
    last = nullptr;
    last_node = nullptr;
    last_index = -1;
}

template <typename T>
void LinkedList<T>::push_back(T element) {
    Node<T>* new_node = new Node<T>(element);
    if (last == nullptr) // List is empty
    {
        first = new_node;
        last = new_node;
    }
    else {
        new_node->previous = last;
        last->next = new_node;
        last = new_node;
    }
}
template <typename T>
void LinkedList<T>::insert(Iterator<T> iter, T element) {
    if (iter.position == nullptr) {
        push_back(element);
        return;
    }

    Node<T>* after = iter.position;
    Node<T>* before = after->previous;
    Node<T>* new_node = new Node<T>(element);
    new_node->previous = before;
    new_node->next = after;
    after->previous = new_node;
    if (before == nullptr) // Insert at beginning
    {
        first = new_node;
    }
    else {
        // Invalidate last access
        last_node = nullptr;
        last_index = -1;
        before->next = new_node;
    }
}

template <typename T>
T LinkedList<T>::get(int k) {
    Node<T>* n;
    if (last_node != nullptr && k >= last_index) {
        n = last_node;
        int t = k;
        k = k - last_index;
        last_index = t;
    }
    else {
        n = first;
        last_index = 0;
    }
    k--;
    while (k >= 0 && n != nullptr) {
        n = n->next;
        k--;
    }
    last_node = n;
    return n->data;
}

template <typename T>
Iterator<T> LinkedList<T>::erase(Iterator<T> iter) {
    Node<T>* remove = iter.position;
    Node<T>* before = remove->previous;
    Node<T>* after = remove->next;
    if (remove == first) {
        first = after;
    }
    else {
        before->next = after;
    }
    if (remove == last) {
        last = before;
    }
    else {
        after->previous = before;
    }
    delete remove;
    Iterator<T> r;
    r.position = after;
    r.container = this;
    // Invalid last access
    last_node = nullptr;
    last_index = -1;
    return r;
}

template <typename T>
Iterator<T> LinkedList<T>::begin() {
    Iterator<T> iter;
    iter.position = first;
    iter.container = this;
    return iter;
}

template <typename T>
Iterator<T> LinkedList<T>::end() {
    Iterator<T> iter;
    iter.position = nullptr;
    iter.container = this;
    return iter;
}

template <typename T>
Iterator<T>::Iterator() {
    position = nullptr;
    container = nullptr;
}

template <typename T>
T Iterator<T>::get() const {
    return position->data;
}

template <typename T>
void Iterator<T>::next() {
    position = position->next;
}

template <typename T>
void Iterator<T>::previous() {
    if (position == nullptr) {
        position = container->last;
    }
    else {
        position = position->previous;
    }
}

template <typename T>
bool Iterator<T>::equals(Iterator<T> other) const {
    return position == other.position;
}

#endif