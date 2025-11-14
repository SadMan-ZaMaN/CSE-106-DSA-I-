#ifndef linkedList_H
#define linkedList_H

#include <iostream>

class node{
    public:
        int element;
        node* next;
        node* prev;

        node(int val){
            element = val;
            next = NULL;
            prev = NULL;
        }
};

class LinkedList{
    private:
        node* head;
        node* tail;
        node* cur;
        int sizee;

    public:
        LinkedList();
        LinkedList(const LinkedList& o);
        LinkedList& operator=(const LinkedList& o);

        ~LinkedList();

        void insert(int item);
        void append(int item);
        int delete_cur();
        void delete_elem(int item);
        void free_list();
        void init();
        void clear();
        void printlist() const;
        int size() const;
        void next(int n);
        void prev(int n);
        int is_present(int n) const;
        void swap_ind(int ind1,int ind2);
        void delete_head();
        void delete_end();
        void insert_at_head(int item);
        void reverse();


        class iterator{
            node* current_node;
            public:
                iterator(node* n){
                    current_node = n;
                }
                int operator*() const {
                    return current_node->element;
                }
                iterator& operator++() {
                    current_node = current_node->next;
                    return *this;  
                } 
                bool operator!=(const iterator& o) const {
                    return current_node!=o.current_node;
                }
        };

        iterator begin() const{
            return iterator(head);
        }
        iterator end() const{
            return iterator(NULL);
        }

};


#endif

