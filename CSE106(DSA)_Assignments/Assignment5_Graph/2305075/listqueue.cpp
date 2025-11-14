#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0
    front_node = nullptr;
    rear_node = nullptr;
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size
    Node *new_node = new Node(item);
    if(rear_node==nullptr){
        front_node = new_node;
        rear_node = new_node;
    }
    else{
        rear_node->next = new_node;
        rear_node = new_node;
    }
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    if(empty()){
        cout << "ERROR!! Cannot dequeue. Queue os Empty!" << endl;
        return -1;
    }
    Node* deq = front_node;
    int Dequeueddata = deq->data;
    front_node = front_node->next;
    if(front_node == nullptr) {
        rear_node = nullptr;
    }

    delete deq;
    current_size--;
    return Dequeueddata;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    Node* del = front_node;
    while(del!=nullptr){
        Node* next_del = del->next;
        delete del;
        del = next_del;
    }
    front_node = nullptr;
    rear_node = nullptr;
    current_size = 0;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
    if(empty()){
        cout << "ERROR!! Cannot get front element. Queue is Empty!" << endl;
        return -1;
    }
    else{
        int front_val = front_node->data;
        return front_val;
    }
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
    if(empty()){
        cout << "ERROR!! Cannot get back element. Queue is Empty!" << endl;
        return -1;
    }
    else{
        int back_val = rear_node->data;
        return back_val;
    }
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    if(front_node == nullptr){
        return true;
    }
    else{
        return false;
    }
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
        string result = "<";
    int TheSize = size();

    Node* temp = front_node;
    
    if(TheSize == 0){
        result += "|";
        return result;
    }

    int i=0;
    while(temp!=nullptr){
        int num = temp->data;
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
                str = D + str;
                num = num/10;
            }
            if(isNegative){
                str = "-"+str;
            }
            result += str;
        }
        if(temp->next!=nullptr){
            result += ", ";
        }
        temp = temp->next;
        i++;       
    }
    result += "|";
    return result; 
}
