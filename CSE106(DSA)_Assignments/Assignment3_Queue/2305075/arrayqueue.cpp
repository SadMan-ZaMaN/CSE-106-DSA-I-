#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    data = new int[initial_capacity];
    if(data == nullptr){
        cout << "ERROR!! Could not allocate memory!" << endl;
        exit(-1);
    }
    capacity = initial_capacity;
    front_idx = 0;
    rear_idx = 0;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    if((rear_idx+1)%capacity == front_idx) {
        resize(capacity * 2);
    }
    data[rear_idx] = item;
    rear_idx = (rear_idx + 1) % capacity;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element
    if(empty()){
        cout << "Cannot dequeue. Queue is Already Empty!" << endl;
        return -1;
    }
    int val;
    val = data[front_idx];
    front_idx = (front_idx+1) % capacity;

    if(capacity/4 >= size()){
        if(capacity>=4){
            resize(capacity / 2);
        }
        else{
            resize(2);
        }
    }
    return val;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    delete[] data; 
    capacity = 2;
    front_idx = 0;
    rear_idx = 0;
    data = new int[capacity];
    if(data == nullptr){
        cout << "ERROR!! Could not allocate memory!" << endl;
        exit(-1);
    }
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    int size = (rear_idx-front_idx+capacity)%capacity;
    return size;
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    if(empty()){
        cout << "ERROR!! Cannot get front element.Queue is EMPTY!" << endl;
        return -1;
    }
    else{
        int front_elem = data[front_idx];
        return front_elem;
    }
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    if(empty()){
        cout << "ERROR!! Cannot get back element.Queue is EMPTY!" << endl;
        return -1;
    }
    else{
        int back = (rear_idx-1+capacity)%capacity;
        int back_elem = data[back];
        return back_elem;
    }
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    if(front_idx == rear_idx){
        return true;
    }
    else{
        return false;
    }
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    string result = "<";
    int TheSize = size();

    for(int i=0;i<TheSize;i++){
        int num = data[(front_idx+i)%capacity];

        if(num == 0){
            result+= "0";
        }
        else{
            string str = "";
            bool isNegative = false;
            if(num < 0) {
                isNegative = true;
                num = -num;
            }

            while(num>0){
                char D = (num%10)+'0';
                str = D + str;                  // str+=D or str = str+D kora jabe na 
                num = num/10;
            }
            if(isNegative){
                str = "-"+str;
            }
            result += str;
        }
        if(i<TheSize-1){
            result += ", ";
        }       
    }
    result += "|";
    return result; 
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
    int *arr = new int[new_capacity];
    if(arr == nullptr){
        cout << "ERROR!! Could not allocate memory!" << endl;
        exit(-1);
    }

    int asize = size();
    for(int i=0;i<asize;i++){
        arr[i] = data[(front_idx+i)%capacity];
    }

    delete[] data;
    data = arr;
    capacity = new_capacity;
    front_idx = 0;
    rear_idx = asize;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}
