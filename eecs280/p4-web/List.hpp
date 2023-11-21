#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template<typename T>
class List {
    //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

    List();

//EFFECTS:  returns true if the list is empty
    bool empty() const;

    //EFFECTS: returns the number of elements in this List
    //HINT:    Traversing a list is really slow.  Instead, keep track of the size
    //         with a private member variable.  That's how std::list does it.
    int size() const;

    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T &front();

    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T &back();

    //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum);

    //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum);

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list
    void pop_front();

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back();

    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all items from the list
    void clear();

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Lists

    List(const List& from);

    List<T> &operator=(const List<T> &from);

    virtual ~List();

private:
    //a private type
    struct Node {
        Node *next;
        Node *prev;
        T datum;
    };

    //REQUIRES: list is empty
    //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T> &other);

    Node *first;   // points to first Node in list, or nullptr if list is empty
    Node *last;    // points to last Node in list, or nullptr if list is empty

    int length;

public:
    ////////////////////////////////////////
    class Iterator {
        //OVERVIEW: Iterator interface to List

        // You should add in a default constructor, destructor, copy constructor,
        // and overloaded assignment operator, if appropriate. If these operations
        // will work correctly without defining these, you can omit them. A user
        // of the class must be able to create, copy, assign, and destroy Iterators.

        // Your iterator should implement the following public operators: *,
        // ++ (prefix), default constructor, == and !=.
    public:
        // This operator will be used to test your code. Do not modify it.
        // Requires that the current element is dereferenceable.
        Iterator &operator--() {
            assert(node_ptr);
            node_ptr = node_ptr->prev;
            return *this;
        }

        typename List<T>::Iterator &operator++();

        bool operator==(Iterator it2) const;

        bool operator!=(Iterator it2) const;

        T &operator*() const;

    private:
        Node *node_ptr; //current Iterator position is a List node
        // add any additional necessary member variables here
        static bool Node_equal(Node *n1, Node *n2) {
            return (n1 == nullptr || n2 == nullptr)
            ? n1 == n2
            : (n1->next == n2->next && n1->prev == n2->prev &&
                    n1->datum == n2->datum);
        }

        // add any friend declarations here
        friend class List;

        // construct an Iterator at a specific position
        Iterator(Node *p);

    };//List::Iterator
    ////////////////////////////////////////

    // return an Iterator pointing to the first element
    Iterator begin() const {
        return Iterator(first);
    }

    // return an Iterator pointing to "past the end"
    Iterator end() const;

    //REQUIRES: i is a valid, dereferenceable iterator associated with this list
    //MODIFIES: may invalidate other list iterators
    //EFFECTS: Removes a single element from the list container
    void erase(Iterator i);

    //REQUIRES: i is a valid iterator associated with this list
    //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum);

};

//List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.
template<typename T>
bool List<T>::empty() const {
    return first == nullptr;
}

template<typename T>
int List<T>::size() const {
    return length;
}

template<typename T>
T &List<T>::front() {
    return first->datum;
}

template<typename T>
T &List<T>::back() {
    return last->datum;
}

template<typename T>
void List<T>::push_front(const T &datum) {
    Node *n = new Node{first, nullptr, datum};
    if (first == nullptr) {
        last = n;
    } else {
        n->next->prev = n;
    }
    first = n;
    ++length;
}

template<typename T>
void List<T>::push_back(const T &datum) {
    Node *n = new Node{nullptr, last, datum};
    if (last == nullptr) {
        first = n;
    } else {
        n->prev->next = n;
    }
    last = n;
    ++length;
}

template<typename T>
void List<T>::pop_front() {
    Node *temp = first;
    first = first->next;
    if (first == nullptr) {
        last = temp->prev;
    } else {
        first->prev = temp->prev;
    }
    delete temp;
    --length;
}

template<typename T>
void List<T>::pop_back() {
    Node *temp = last;
    last = last->prev;
    if (last == nullptr) {
        first = temp->next;
    } else {
        last->next = temp->next;
    }
    delete temp;
    --length;
}

template<typename T>
void List<T>::clear() {
    last = nullptr;
    while (first != nullptr) {
        auto *temp = first;
        first = first->next;
        delete temp;
    }
    length = 0;
}

template<typename T>
void List<T>::copy_all(const List<T> &other) {
    List<T>::Iterator i = other.begin();
    for (; i != other.end(); ++i) {
        this->push_back(*i);
    }
    length = other.length;
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return nullptr;
}

template<typename T>
void List<T>::erase(List::Iterator i) {
    if (i.node_ptr == first) {
        pop_front();
        return;
    }
    if (i.node_ptr == last) {
        pop_back();
        return;
    }
    i.node_ptr->next->prev = i.node_ptr->prev;
    i.node_ptr->prev->next = i.node_ptr->next;
    delete i.node_ptr;
    --length;
}

template<typename T>
void List<T>::insert(List::Iterator i, const T &datum) {
    //Todo: make better if possible
    if (i.node_ptr == nullptr) {
        push_back(datum);
        return;
    }
    if (i.node_ptr == first) {
        push_front(datum);
        return;
    }
    Node *n = new Node{i.node_ptr, i.node_ptr->prev, datum};
    i.node_ptr->prev->next = n;
    i.node_ptr->prev = n;
    ++length;
}

template<typename T>
List<T>::Iterator::Iterator(List::Node *p) : node_ptr(p) {

}

template<typename T>
List<T>::List() : first(nullptr), last(nullptr), length(0) {

}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
    node_ptr = node_ptr->next;
    return *this;
}

template<typename T>
bool List<T>::Iterator::operator==(List::Iterator it2) const {
    return Node_equal(node_ptr, it2.node_ptr);
}

template<typename T>
bool List<T>::Iterator::operator!=(List::Iterator it2) const {
    return !Node_equal(node_ptr, it2.node_ptr);
}

template<typename T>
T &List<T>::Iterator::operator*() const {
    return node_ptr->datum;
}

// list big 3
template<typename T>
List<T>::List(const List &from) : first(nullptr), last(nullptr), length(0) {
    copy_all(from);
}

template<typename T>
List<T> &List<T>::operator=(const List &from) {
    first = nullptr;
    last = nullptr;
    length = 0;
    copy_all(from);
    return *this;
}

template<typename T>
List<T>::~List() {
    clear();
}

#endif // Do not remove this. Write all your code above this line.
