#include"linkedList.h"

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
    cur = NULL;
    sizee = 0;
}

LinkedList::LinkedList(const LinkedList& o){
    head = nullptr;
    tail = nullptr;
    cur = nullptr;
    sizee = 0;

    node* temp = o.head;
        while(temp != NULL){
            node* newNode = new node(temp->element);
                if(head == NULL) {
                    head = tail = newNode;
                } 
                else{
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
            temp = temp->next;
        }
}


LinkedList& LinkedList::operator=(const LinkedList& o){
    if(this==&o){
        return *this;
    }

    free_list();
    node* temp = o.head;
    while(temp!=NULL){
        node* newNode = new node(temp->element);
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        temp = temp->next;
    }
    return *this;
}

LinkedList::~LinkedList(){
    free_list();
}

void LinkedList::insert_at_head(int item){
    node* newNode = new node(item);
    if(head == NULL){
        head = newNode;
        tail = newNode;
        cur = newNode;
    }
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    sizee++;
}

void LinkedList::insert(int item){
    node* newNode = new node(item);
    if(cur==NULL){
        cur = newNode;
        head = newNode;
        tail = newNode;
        cur->prev = NULL;
        cur->next = NULL;
    }
    else{
        newNode->next = cur->next;
        newNode->prev = cur;

        if(cur->next != NULL){
            cur->next->prev = newNode;
        }
        else{
            tail = newNode;           // ekdom last node ta hobe insert kora node
        }
        cur->next = newNode;
    }
    cur = newNode;
    sizee++;

}

void LinkedList::append(int item){
    node* newNode = new node(item);
    if(head==NULL && tail==NULL){
        head = newNode;
        tail = newNode;
        cur = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else{
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = NULL;
        tail = newNode;
    }
    sizee++;
}

void LinkedList::delete_head(){
    if(head==NULL){
        return;
    }
    node* temp = head;
    if(head==tail){
        head = NULL;
        tail = NULL;
        cur = NULL;
    }
    else{
        head = head->next;
        head->prev = NULL;
        if(cur == temp){
            cur = head;  
        }
    }
    delete temp;
    sizee--;
}

void LinkedList::delete_end(){
    if(tail==NULL){
        return;
    }
    node* temp = tail;
    if(head==tail){
        head = NULL;
        tail = NULL;
        cur = NULL;
    }
    else{
        tail = tail->prev;
        tail->next = NULL;
        if(cur == temp){
            cur = tail;  
        }
    }
    delete temp;
    sizee--;
}

void LinkedList::delete_elem(int item){
    node* temp = head;
    while(temp!=NULL){
        if(temp->element==item){
            if(temp == head){
                delete_head();
            }
            else if(temp == tail){
                delete_end();
            }
            else{
                temp->prev->next = temp->next;
                if(temp->next!=NULL){
                    temp->next->prev = temp->prev;
                }
                if(cur==temp){
                    cur=temp->next;
                }
                delete temp;
                sizee--;
            }
            return;  
        }
        temp = temp->next;
    }
}

int LinkedList::delete_cur(){
    if(cur==NULL){
        //printf("EMPTY!! Cannot delete\n");
        return -1;
    }
    int deletedElement = cur->element;
    node* temp = cur;
    if(head==tail){
        head = NULL;
        tail = NULL;
        cur = NULL;
    }
    else if(cur==head){
        head = cur->next;
        head->prev = NULL;
        cur = head;
    }
    else if(cur==tail){
        tail = cur->prev;
        tail->next = NULL;
        cur = tail;
    }
    else{
        cur->prev->next = cur->next;
        if(cur->next != NULL){
            cur->next->prev = cur->prev;
        }
        cur = cur->next;
    }
    delete temp;
    sizee--;
    return deletedElement;
}


void LinkedList::free_list(){
    node* temp = head;
    while(temp!=NULL){
        node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = NULL;
    tail = NULL;
    cur = NULL;
    sizee = 0;

}

void LinkedList::clear(){
    free_list();
}

int LinkedList::size() const {
    return sizee;
}

void LinkedList::printlist() const{
    node* temp = head;
    while(temp!=NULL){
        std::cout << temp->element << " ";
        temp = temp->next;
    }
    std::cout<<std::endl;
}

void LinkedList::next(int n){
    if(cur==NULL){
        //printf("EMPTY\n");
        return;
    }
    for(int i=0;i<n;i++){
        if(cur->next == NULL){
            break;
        }
        cur = cur->next;
    }
}

void LinkedList::prev(int n){
    for(int i=0;i<n;i++){
        if(cur==NULL){
            //printf("EMPTY\n");
            return;
        }
        if(cur->prev==NULL){              // IS THIS NECESSARY????
            break;
        }
        cur = cur->prev;
    }
}

int LinkedList::is_present(int n) const {
    node* temp = head;
    while(temp!=NULL){
        if(temp->element==n){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


void LinkedList::swap_ind(int ind1, int ind2){
    if(ind1 >= sizee || ind2 >= sizee || ind1 == ind2){
        return;
    }
    node* temp1 = head;
    node* temp2 = head;
    for(int i=0; i<ind1; i++){
        temp1 = temp1->next;
    }
    for(int i=0; i<ind2; i++){
        temp2 = temp2->next;
    }
    int val1 = temp1->element;
    int val2 = temp2->element;

    temp1->element = val2;
    temp2->element = val1;
}

void LinkedList::reverse(){
    node* temp = head;
    node* prevNode = NULL;
    tail = head;  
    while(temp != NULL){
        node* nextNode = temp->next;
        temp->next = prevNode;
        temp->prev = nextNode;  
        prevNode = temp;
        temp = nextNode;
    }
    head = prevNode; 
}


