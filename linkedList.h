#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    node* head;
    node* tail;
    node* cur;
    int size;
    // declare head, tail, cur and other variables you need
} linkedList;

void init(linkedList* list)
{
    // empty list banate hobe
    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    list->size = 0;
    // implement initialization
}

void free_list(linkedList* list)
{
    node* temp = list->head;
    while(temp!=NULL){
        node* nextt = temp->next;
        free(temp);
        temp = nextt;
    }

    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    list->size = 0;
    // implement destruction of list
}

void print(linkedList* list)
{
    if(list->head==NULL){           // list->size = 0
        printf("[.]");
    }
    else{
        int count = 0;
        printf("[");
        node* temp = list->head;
        while(temp!=NULL){
            printf("%d",temp->element);

            if(temp == list->cur){
                printf("|");
            }

            if(temp->next != NULL){
                printf(" ");
            }
            temp = temp->next;
            //count++;
        }
        if(list->cur == NULL){
            printf("|");
        }
        printf("]\n");
    }
    // implement list printing
}

void insert(int item, linkedList* list)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->element = item;

    if(list->cur == NULL){
        list->cur = newNode;
        list->head = newNode;
        list->tail = newNode;
        list->cur->prev = NULL;
        list->cur->next = NULL;
        // list->cur->element = item;
    }
    else{
        newNode->next = list->cur->next;
        newNode->prev = list->cur;

        if(list->cur->next!=NULL){
            list->cur->next->prev = newNode;
        }
        else{
            list->tail = newNode;           // ekdom last node ta hobe insert kora node
        }
        list->cur->next = newNode;
    }
    list->cur = newNode; 
    list->size++;
    print(list);
    // implement insert function
}

int delete_cur(linkedList* list)
{   
    if(list->cur==NULL){
        printf("EMPTY!! Cannot delete\n");
        return -1;
    }

    int deletedElement = list->cur->element;
    node* temp = list->cur;

    if(list->head==list->tail){
        list->head = NULL;
        list->tail = NULL;
        //free(list->cur);
        list->cur = NULL;
        //list->size--;
    }

    else if(list->cur == list->head){
        list->head = list->cur->next;
        list->head->prev = NULL;
        //free(list->cur);
        list->cur = list->head;
    }

    else if(list->cur == list->tail){
        list->tail = list->cur->prev;
        list->tail->next = NULL;
        //free(list->cur);
        list->cur = list->tail;
    }
    else{
        list->cur->prev->next = list->cur->next;
        list->cur->next->prev = list->cur->prev;
        //free(list->cur);
        list->cur = list->cur->next;
    } 

    free(temp);
    list->size--;
    print(list);

    return deletedElement;

    // implement deletion of current index function
}

void append(int item, linkedList* list)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->element = item;

    if(list->head== NULL && list->tail==NULL){       // khali list
        list->head = newNode;
        list->tail = newNode;
        list->cur = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else{
        list->tail->next = newNode;
        newNode->prev = list->tail;
        newNode->next = NULL;
        list->tail = newNode;
    }

    list->size++;
    print(list);
    // implement append function
}

int size(linkedList* list)
{
    return list->size;
    // implement size function
}

void prev(int n, linkedList* list)
{
    for(int i=0;i<n;i++){
        if(list->cur==NULL){
            printf("EMPTY\n");
            return;
        }

        if(list->cur->prev==NULL){              // IS THIS NECESSARY????
            break;
        }
        list->cur = list->cur->prev;

    }

    print(list);
    // implement prev function
}

void next(int n, linkedList* list)
{
    if(list->cur == NULL){
        printf("EMPTY\n");
        return;
    }
    for(int i=0;i<n;i++){
        if(list->cur->next == NULL){
            break;
        }
        list->cur = list->cur->next;
    }
    print(list);
    // implement next function
}

int is_present(int n, linkedList* list)
{
    node* temp = list->head;
    while(temp!=NULL){
        if(temp->element==n){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
    // implement presence checking function
}

void clear(linkedList* list)
{
    free_list(list);
    print(list);
    // implement list clearing function
}

void delete_item(int item, linkedList* list)
{
    node* temp = list->head;
    int flag = 0;
    while(temp!=NULL){
        if(temp->element == item){

            flag = 1;

            if(temp == list->head){
                list->head = temp->next;
                if(list->head!=NULL){
                    list->head->prev = NULL;
                }
            }

            else if(temp==list->tail){
                list->tail = temp->prev;
                if(list->tail!=NULL){
                    list->tail->next = NULL;
                }
            }

            else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            if(list->cur == temp){      //  | shift koranor jonno
                list->cur = temp->next;
            }

            free(temp);
            list->size--;
            break;                 // ekbar delete kora lagbe
        }
        temp = temp->next;
    }
    if(flag==0){
        printf("%d was not Found",item);
    }

    print(list);
    // implement item deletion function
    
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    if(ind1>=list->size || ind2>=list->size || ind1 == ind2){
        return;
    }
    node* temp1 = list->head;
    node* temp2 = list->head;
    for(int i=0;i<ind1;i++){
        temp1 = temp1->next;
    }

    for(int i=0;i<ind2;i++){
        temp2 = temp2->next;
    }

    int val1 = temp1->element;
    int val2 = temp2->element;

    temp1->element = val2;
    temp2->element = val1;

    print(list);
    // implement swap function
}




