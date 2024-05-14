#include <iostream>

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
    LinkedSet<T> *container;
    friend class LinkedList<T>;
};

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
    friend class LinkedSet<T>;
    friend class Iterator<T>;
};

template <typename T>
class LinkedSet {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& newData) : data(newData), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    LinkedSet() : head(nullptr), size(0) {}

    ~LinkedSet() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    bool contains(const T& element) const {
        Node* current = head;
        while (current) {
            if (current->data == element)
                return true;
            current = current->next;
        }
        return false;
    }

    void add(const T& element) {
        if (contains(element))
            return; // Element already exists

        Node* newNode = new Node(element);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void remove(const T& element) {
        if (isEmpty())
            return;

        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->data == element) {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next;

                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Iterator<T>  erase(Iterator<T> iter);

    Iterator<T>  begin();

    Iterator<T>  end();
};

template <typename T>
Node<T>::Node(T element) {
    data = element;
    previous = nullptr;
    next = nullptr;
}

template <typename T>
Iterator<T> LinkedSet<T>::erase(Iterator<T> iter) {
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
Iterator<T> LinkedSet<T>::begin() {
    Iterator<T> iter;
    iter.position = first;
    iter.container = this;
    return iter;
}

template <typename T>
Iterator<T> LinkedSet<T>::end() {
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