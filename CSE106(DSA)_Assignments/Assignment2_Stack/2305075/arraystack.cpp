#include "stack.h"
#include <iostream>
using namespace std;

// Constructor implementation
ArrayStack::ArrayStack(int initial_capacity) {
    if(initial_capacity>=10){
        capacity = initial_capacity;
    }
    else{
        capacity = 10;
    }
    data = new int[capacity];
    current_size = 0;
    // TODO: Initialize data members (data, capacity, current_size)
    // TODO: Allocate memory for the array with the specified initial capacity
}

// Destructor implementation
ArrayStack::~ArrayStack() {
    delete[] data;
    // TODO: Free the dynamically allocated memory for the array
}

// Push implementation
void ArrayStack::push(int item) {
    if(current_size >= capacity/2){
        resize(capacity*2);
    }
    data[current_size] = item;
    current_size++;
    // TODO: Check if the array is 50% full (current_size >= capacity/2)
    // TODO: If 50% full, resize the array to double its current capacity
    // TODO: Add the new element to the top of the stack and increment current_size
}

// Pop implementation
int ArrayStack::pop() {
    if(current_size==0){
        cout << "EMPTY Stack cannot pop element" << endl;
        return -1;
    }
    int del = data[current_size-1];
    current_size--;
    if(current_size < capacity * 0.25){
        if(capacity/2 < 10){
            resize(10);
        }
        else{
            resize(capacity/2);
        }
    }
    return del;
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the top of the stack
    // TODO: If the array is less than 25% full, resize it to half its current capacity
    // TODO: Return the popped element
}

// Clear implementation
void ArrayStack::clear() {
    // for(int i=0;i<current_size;i++){
    //     data[i] = 0;
    // }
    current_size = 0;
    // TODO: Reset the stack to be empty (set current_size to 0)
    // TODO: No need to free memory, just logically clear the stack
}

// Size implementation
int ArrayStack::size() const {
    return current_size;
    // TODO: Return the number of elements currently in the stack (current_size)
}

// Top implementation
int ArrayStack::top() const {
    if(current_size==0){
        cout << "EMPTY Stack" << endl;
        return -1;
    }
    int top = data[current_size-1];
    return top;
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the element at the top of the stack without removing it
}

// Empty implementation
bool ArrayStack::empty() const {
    if(current_size==0){
        return true;
    }
    else{
        return false;
    }
    // TODO: Return whether the stack is empty (current_size == 0)
}

// Print implementation
void ArrayStack::print() const {
    if(current_size==0){
        cout << "|>" << endl;
    }
    else{
        cout << "|";
        for(int i=current_size-1;i>0;i--){
            cout << data[i] << ", ";
        }
        cout << data[0];
        cout << ">" << endl;
    }
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
}

// Resize implementation
void ArrayStack::resize(int new_capacity) {
    
    int* newData = new int[new_capacity];
    for(int i=0;i<current_size;i++){
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = new_capacity;
    
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
}

