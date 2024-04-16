/*
 * Name: Parnell Thrower
 * Description: Manage Tasks using Map, HashTable, and Try-Catch
 * Date: 4/20/2024
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

using namespace std;

/**
   Computes the hash code for a string.
   @param str a string
   @return the hash code
*/
int hash_code(const string& str);

template<typename T>
class HashTable;
template<typename T>
class Iterator;

template<typename T>
class Node
{
private:
    T data;
    Node<T>* next;

    friend class HashTable<T>;
    friend class Iterator<T>;
};

template<typename T>
class Iterator
{
public:
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
       Compares two iterators.
       @param other the iterator to compare with this iterator
       @return true if this iterator and other are equal
    */
    bool equals(const Iterator<T>& other) const;
private:
    const HashTable<T>* container;
    int bucket_index;
    Node<T>* current;

    friend class HashTable<T>;
};

/**
   This class implements a hash table using separate chaining.
*/
template<typename T>
class HashTable
{
public:
    /**
       Constructs a hash table.
       @param nbuckets the number of buckets
    */
    HashTable(int nbuckets);

    /**
       Tests for set membership.
       @param x the potential element to test
       @return 1 if x is an element of this set, 0 otherwise
    */
    int count(const T& x);

    /**
       Adds an element to this hash table if it is not already present.
       @param x the element to add
    */
    void insert(const T& x);

    /**
       Removes an element from this hash table if it is present.
       @param x the potential element to remove
    */
    void erase(const T& x);

    /**
       Returns an iterator to the beginning of this hash table.
       @return a hash table iterator to the beginning
    */
    Iterator<T> begin() const;

    /**
       Returns an iterator past the end of this hash table.
       @return a hash table iterator past the end
    */
    Iterator<T> end() const;

    /**
       Gets the number of elements in this set.
       @return the number of elements
    */
    int size() const;

private:
    vector<Node<T>*> buckets;
    int current_size;

    friend class Iterator<T>;
};




int hash_code(const string& str)
{
    int h = 0;
    for (int i = 0; i < str.length(); i++)
    {
        h = 31 * h + str[i];
    }
    return h;
}

template<typename T>
HashTable<T>::HashTable(int nbuckets)
{
    for (int i = 0; i < nbuckets; i++)
    {
        buckets.push_back(nullptr);
    }
    current_size = 0;
}

template<typename T>
int HashTable<T>::count(const T& x)
{
    int h = hash_code(x);
    h = h % buckets.size();
    if (h < 0) { h = -h; }

    Node<T>* current = buckets[h];
    while (current != nullptr)
    {
        if (current->data == x) { return 1; }
        current = current->next;
    }
    return 0;
}

template<typename T>
void HashTable<T>::insert(const T& x)
{
    int h = hash_code(x.name);
    h = h % buckets.size();
    if (h < 0) { h = -h; }

    Node<T>* current = buckets[h];
    while (current != nullptr)
    {
        if (current->data == x) { return; }
        // Already in the set
        current = current->next;
    }
    Node<T>* new_node = new Node<T>;
    new_node->data = x;
    new_node->next = buckets[h];
    buckets[h] = new_node;
    current_size++;
}

template<typename T>
void HashTable<T>::erase(const T& x)
{
    int h = hash_code(x);
    h = h % buckets.size();
    if (h < 0) {
        h = -h;
    }

    Node<T>* current = buckets[h];
    Node<T>* previous = nullptr;
    while (current != nullptr)
    {
        if (current->data == x)
        {
            if (previous == nullptr)
            {
                buckets[h] = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            current_size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template<typename T>
int HashTable<T>::size() const
{
    return current_size;
}

template<typename T>
Iterator<T> HashTable<T>::begin() const
{
    Iterator<T> iter;
    iter.current = nullptr;
    iter.bucket_index = -1;
    iter.container = this;
    iter.next();
    return iter;
}

template<typename T>
Iterator<T> HashTable<T>::end() const
{
    Iterator<T> iter;
    iter.current = nullptr;
    iter.bucket_index = (int) buckets.size();
    iter.container = this;
    return iter;
}

template<typename T>
T Iterator<T>::get() const
{
    return current->data;
}

template<typename T>
bool Iterator<T>::equals(const Iterator<T>& other) const
{
    return current == other.current;
}

template<typename T>
void Iterator<T>::next()
{
    if (bucket_index >= 0 && current->next != nullptr)
    {
        // Advance in the same bucket
        current = current->next;
    }
    else
    {
        // Move to the next bucket
        do
        {
            bucket_index++;
        }
        while (bucket_index < container->buckets.size()
               && container->buckets[bucket_index] == nullptr);
        if (bucket_index < container->buckets.size())
        {
            // Start of next bucket
            current = container->buckets[bucket_index];
        }
        else
        {
            // No more buckets
            current = nullptr;
        }
    }
}




#endif // HASHTABLE_H
