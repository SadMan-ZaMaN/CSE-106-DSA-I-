#include "stack.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListStack::ListStack() {
    head = nullptr;
    current_size = 0;
    
    // TODO: Initialize head to nullptr
    // TODO: Initialize current_size to 0
}

// Destructor implementation
ListStack::~ListStack() {
    clear();
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
}

// Push implementation
void ListStack::push(int item) {
    if(head==nullptr){
        head = new Node(item);
        head->next = nullptr;
    }
    else{
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
    }
    current_size++;
    // TODO: Create a new node with the given item
    // TODO: Make the new node point to the current head
    // TODO: Update head to point to the new node
    // TODO: Increment current_size
}

// Pop implementation
int ListStack::pop() {
    if(current_size==0){
        cout << "Empty Stack. Cannot pop element" << endl;
        return -1;
    }
    else{
        int del = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        current_size--;
        return del;
    }
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Store the data from the head node
    // TODO: Update head to point to the next node
    // TODO: Delete the old head node
    // TODO: Decrement current_size
    // TODO: Return the stored data
}

// Clear implementation
void ListStack::clear() {
    while(head!=nullptr){
        Node* clr = head;
        head = head->next;
        delete clr;
    }
    head = nullptr;
    current_size = 0;
    // TODO: Traverse the linked list, deleting each node
    // TODO: Reset head to nullptr
    // TODO: Reset current_size to 0
}

// Size implementation
int ListStack::size() const {
    return current_size;
    // TODO: Return the current size (current_size)
}

// Top implementation
int ListStack::top() const {
    if(current_size==0){
        cout << "EMPTY Stack " << endl;
        return -1;
    }
    else{
        int topVal = head->data;
        return topVal;
    }
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the data from the head node without removing it
}

// Empty implementation
bool ListStack::empty() const {
    if(head==nullptr){
        return true;
    }
    else{
        return false;
    }
    // TODO: Return whether head is nullptr
}

// Print implementation
void ListStack::print() const {
    if(head==nullptr){
        cout << "|>" << endl; 
    }
    else{
        Node* temp = head;
        cout << "|";
        while(temp->next!=nullptr){
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << temp->data;
        cout << ">" << endl;
    }
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    // TODO: Traverse the linked list from head, printing each node's data
}
