#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>
#include<algorithm>
#include <iostream>

using namespace std;

class Heap{
    private:

    vector <int> myHeap;
    int capacity;

    int Left(int i){
        int l = 2*i;
        return l;
    }
    int Right(int i){
        int r = 2*i+1;
        return r;
    }

    void MaxHeapify(int i){
        int largest = i;
        int l = Left(i);
        int r = Right(i);
        int heap_size = myHeap.size() - 1;
        if(l<=heap_size && myHeap[l]>myHeap[i]){
            largest = l;
        }
        else{
            largest = i;
        }
        if(r<=heap_size && myHeap[r]>myHeap[largest]){
            largest = r;
        }
        if(largest!=i){
            swap(myHeap[i], myHeap[largest]);
            MaxHeapify(largest);
        }
    }

    public:
    Heap(int maximumS){
        capacity = maximumS;
        myHeap.push_back(0);
    }

    Heap(vector<int> v){
        capacity = v.size();
        myHeap.push_back(0);
        for(int i=0;i<v.size();i++){
            int num = v[i];
            myHeap.push_back(num);
        }
        int sizee = (myHeap.size()-1)/2;
        for(int i=sizee;i>=1;i--){
            MaxHeapify(i);
        }
    }

    void insert(int val){
        if(myHeap.size()-1>=capacity){
            throw overflow_error("Heap is full");
        }
        myHeap.push_back(val);
        int idx = myHeap.size() - 1;

        int parent = idx/2;
        while(idx>1 && myHeap[idx]>myHeap[parent]){
            swap(myHeap[idx],myHeap[parent]);
            idx = parent;
            parent = idx/2;
        }
    }

    int size() const{
        int sizee = myHeap.size()-1;
        return sizee;
    }

    int getMax() const{
        if(myHeap.size()<=1){
            throw underflow_error("Heap is empty");
        }
        int max = myHeap[1];
        return max;
    }

    void deleteKey(){
        if(myHeap.size()<=1){
            throw underflow_error("Heap is empty");
        }
        int val = myHeap[1];
        myHeap[1] = myHeap.back();
        myHeap.pop_back();
        MaxHeapify(1);
    }
};

void heapsort(vector<int>& v){
    Heap newheap(v);
    v.clear();
    while(newheap.size()){
        int val = newheap.getMax();
        v.push_back(val);
        newheap.deleteKey();
    }
}

#endif