#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    int size;
    int maxsize;
    int idx;
    // declare variables you need
} arrayList;

void init(arrayList* list)
{
    list->idx = 0;
    list->maxsize = 2;          // surute 2 max size rakha lagbe
    list->size = 0;
    int max = list->maxsize;
    list->array = (int*)malloc(sizeof(int)*max);

    if(list->array==NULL){
        printf("Memory was not allocated ERROR!!1 \n");
        exit(1);
    }
    // implement initialization
}

void free_list(arrayList* list)
{
    //delete[] list->array;
    free(list->array);
    // implement destruction of list
}

void increase_capacity(arrayList* list)
{
    int prevmax = list->maxsize;
    list->maxsize = 2*list->maxsize;
    int newLen = list->maxsize;

    int* BigArr = (int*)malloc(sizeof(int)*newLen);
    for(int i=0;i<list->size ;i++){
        BigArr[i] = list->array[i];
    }
    free(list->array);
    list->array = BigArr;

    printf("Capacity increased from %d to %d\n",prevmax,newLen);
    // implement capacity increase
}

void decrease_capacity(arrayList* list)
{
    int prevmax = list->maxsize;
    list->maxsize = 0.5*list->maxsize;
    int newLen = list->maxsize;

    if(newLen<2){
        newLen = 2;
        list->maxsize = 2;
    }

    int* SmlArr = (int*)malloc(sizeof(int)*newLen);
    for(int i=0;i<list->size;i++){
        SmlArr[i] = list->array[i];
    }
    free(list->array);
    list->array = SmlArr;

    printf("Capacity decreased from %d to %d\n",prevmax,newLen);
    // implement capacity decrease
}

void print(arrayList* list)
{
    if(list->size==0){
        printf("[.]\n");
    }
    else{
        printf("[");
        for(int i=0;i<list->size;i++){
            printf(" %d",list->array[i]);
            if(i==list->idx-1 && list->idx != list->size){          // DEBUGG
                printf("|");
            }
        }
        if(list->idx == list->size){
            printf("|");
        }

        printf("]\n");
    }
    // implement list printing
}

void insert(int item, arrayList* list)
{
    if(list->size>=0.5*list->maxsize){
        increase_capacity(list);
    }

    for(int i=list->size-1;i>=list->idx;i--){
        list->array[i+1] = list->array[i];
    }
    list->array[list->idx] = item;
    list->size++;
    list->idx++;

    print(list);
    // implement insert function
}

int delete_cur(arrayList* list)             // eikhane problem
{
    if(list->size==0){
        printf("EMPTY LIST\n");
        return -1;
    }

    int deletedValue = list->array[list->idx-1];

    for(int i=list->idx-1;i<list->size-1;i++){
        list->array[i] = list->array[i+1];
    }
    //list->idx++;        //DEBUGG
    list->size--;
    if(list->idx>list->size){
        list->idx = list->size;
    }

    if(list->size<list->maxsize/4){
        decrease_capacity(list);
    }

    print(list);
    return deletedValue;
    // implement deletion of current index function
}

void append(int item, arrayList* list)
{
    if(list->size>=0.5*list->maxsize){
        increase_capacity(list);
    }

    if(list->size==0){
        list->idx = 1;             // LAST DEBUGG
    }

    list->array[list->size] = item;
    list->size++;
    //list->idx = list->size;

    print(list);
    // implement append function
}

int size(arrayList* list)
{
    return list->size;
    // implement size function
}

void prev(int n, arrayList* list)
{
    if(list->size==0){
        printf("EMPTY\n");
        return;
    }

    int curr_idx = list->idx;
    if(curr_idx-n<0){
        list->idx = 0;
    }
    else{
        list->idx = list->idx - n;
    }

    print(list);
    // implement prev function
}

void next(int n, arrayList* list)
{
    if(list->size==0){
        printf("EMPTY");
        return;
    }

    int curr_idx = list->idx;
    if(list->idx+n > list->size){         // if(list->idx+n >= list->size){}
        list->idx = list->size;           // list->idx = list->size-1;
    }
    else{
        list->idx = list->idx + n;
    }

    print(list);
    // implement next function
}

int is_present(int n, arrayList* list)
{
    for(int i=0;i<list->size;i++){
        if(list->array[i]==n){
            return 1;
        }
    }
    return 0;
    // implement presence checking function
}

void clear(arrayList* list)
{
    list->size = 0;
    list->idx = 0;
    list->maxsize = 2;
    free(list->array);
    list->array = (int*)malloc(sizeof(int)*2);

    print(list);
    // implement list clearing function
}

void delete_item(int item, arrayList* list)
{
    if(list->size==0){
        printf("EMPTY LIST\n");
        return;
    }

    int flag = 0;

    for(int i=0;i<list->size;i++){
        if(item==list->array[i]){
            for(int j=i;j<list->size-1;j++){
                list->array[j] = list->array[j+1];
            }
            flag = 1;
            list->size--;
            break;  // jate kore ekbar delete hoy
        }
    }
    if(flag==0){
        printf("%d not found\n", item);
    }

    if(list->size <= list->idx && list->size!=0){
        list->idx = list->size - 1;
    }

    list->idx++;            // DEBUGG
    if(list->size < list->maxsize /4){
        decrease_capacity(list);
    }

    print(list);
    // implement item deletion function
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    if (ind1 < 0 || ind1 >= list->size || ind2 < 0 || ind2 >= list->size){
        return;
    }

    int val1 = list->array[ind1];
    int val2 = list->array[ind2];

    list->array[ind1] = val2;
    list->array[ind2] = val1;

    print(list);
    // implement swap function
}

// you can define helper functions you need
