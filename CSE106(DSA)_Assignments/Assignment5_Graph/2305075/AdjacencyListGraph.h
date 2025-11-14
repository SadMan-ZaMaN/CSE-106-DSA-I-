#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include "linkedList.h"
#include "queue.h"
#include"stack.h"
#include<vector>
#include<algorithm>

class AdjacencyListGraph : public GraphADT
{
private:
    LinkedList* list;
    int maxSize;
    int newMaxSize;

    void changeSize(){
        int max = newMaxSize;
        LinkedList* newList = new LinkedList[max];
        for(int i = 0; i < maxSize; i++){
            newList[i] = list[i];
        }
        delete[] list;
        maxSize = max;
        list = newList;       
    }

    int resized_capacity(int v)const{
        int new_size = maxSize*2;
        if (v+1>new_size){
            new_size = v+1;
        }
        return new_size;     
    }
    // TODO: Take necessary private members

public:
    void AddNode(int v) override
    {
        if(v>=maxSize){
            newMaxSize = resized_capacity(v);
            changeSize();
        }
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.

    }

    void AddEdge(int u, int v) override
    {
        if(u>=maxSize || v>=maxSize){
            int big;
            if(u>=v){
                big = u;
            }
            else{
                big = v;
            }
            newMaxSize = resized_capacity(big);
            changeSize();
        }
        //list[u].append(v);
        //list[v].append(u);
        if(list[u].is_present(v)==0){
            list[u].append(v);
        }
        if(list[v].is_present(u)==0){
            list[v].append(u);
        }
        //TODO: Add a new edge between the nodes u and v

    }

    bool CheckEdge(int u, int v) const override
    {
        if(u>=maxSize || v>=maxSize){
            return false;
        }
        if(u<0 || v<0){
            return false;
        }
        if(list[u].is_present(v)==1){
            return true;
        }
        else{
            return false;
        }
        //TODO: Check whether there is an edge between two nodes u and v

    }

    void RemoveNode(int v) override
    {
        if(v>=maxSize || v<0){
            return;
        }
        for(int i=0;i<maxSize;i++){
            if(i!=v){
                list[i].delete_elem(v);
            }
        }
        list[v].clear();

        //TODO: Remove a node.

    }

    void RemoveEdge(int u, int v) override
    {
        if(u>=maxSize || v>=maxSize){
            return;
        }
        if(u<0 || v<0){
            return;
        }

        if(list[u].is_present(v)==1){
            list[u].delete_elem(v);
        }
        if(list[v].is_present(u)==1){
            list[v].delete_elem(u);
        }
        //TODO: remove an edge

    }

    bool CheckPath(int u, int v) const override
    {
        if(u>=maxSize || v>=maxSize){
            return false;
        }
        if(u<0 || v<0){
            return false;
        }

        ListQueue* q = new ListQueue();
        int visited[maxSize];
        for(int i=0;i<maxSize;i++){
            visited[i] = 0;
        }
        q->enqueue(u);
        visited[u] = 1;

        while(q->empty()==false){
            int node = q->dequeue();
            if(node==v){
                delete q;
                return true;
            }
            for(LinkedList::iterator it = list[node].begin();it!=list[node].end();++it){
                int i = *it;
                if(visited[i]==0){
                    q->enqueue(i);
                    visited[i] = 1;
                }
            }
        }
        delete q;
        return false;
        
                //TODO: Return true if there is a path between nodes u and v. Otherwise return false

    }

    void FindShortestPath(int u, int v) const override
    {
        if(u>=maxSize || v>=maxSize){

            std::cout << "No path exists" << std::endl;
            return;
        }
        if(u<0 || v<0){
            std::cout << "No path exists" << std::endl;
            return;
        }

        if(!CheckPath(u, v)){
            std::cout << "No path exists between " << u << " and " << v << std::endl;
            return;
        }

        if(u == v) {
            std::cout << "Shortest Path: " << u << std::endl;
            return;
        }

        int* visited = new int[maxSize];
        int* pred = new int[maxSize];
        for(int i=0;i<maxSize;i++){
            visited[i] = 0;
            pred[i] = -1;
        }

        Queue* q = new ListQueue();
        visited[u] = 1;
        q->enqueue(u);

        bool flag = false;

        while(!q->empty() && !flag){
            int node = q->dequeue();
            for(LinkedList::iterator it = list[node].begin(); it != list[node].end(); ++it){
                int i = *it;
                if(visited[i] == 0){
                    visited[i] = 1;
                    pred[i] = node;
                    q->enqueue(i);
                    if(i==v){
                        flag = true;
                        break;
                    }
                }
            }
        }

        if(flag== true){
            std::vector<int> arr;
            int traceB = v;
            while(traceB!=-1){
                arr.push_back(traceB);
                traceB = pred[traceB];
            }
            int n = arr.size();
            for(int i=0;i<n/2;i++){
                int tempo = arr[i];
                arr[i]= arr[n-i-1];
                arr[n-i-1] = tempo;
            }

            std::cout << "Shortest path: ";
            for(int i=0;i<n;i++){
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
        else{
            std::cout << "No path exists" << std::endl;
        }
        delete[] visited;
        delete[] pred;
        delete q;
        
                //TODO: Find the shortest path between the nodes u and v and print it.

    }

    int FindShortestPathLength(int u, int v) const override
    {
        if(u>=maxSize || v>=maxSize){
            return -1;
        }
        if(u<0 || v<0){
            return -1;
        }
        if(u == v) {
            return 0;
        }
        if(!CheckPath(u, v)) {
            return -1; 
        }

        int* distance = new int[maxSize];
        int* visited = new int[maxSize];

        for(int i=0;i<maxSize;i++) {
            distance[i] = -1; 
            visited[i] = 0; 
        }

        ListQueue* q = new ListQueue();
        q->enqueue(u);
        visited[u] = 1;
        distance[u] = 0;
        while(!q->empty()){
            int node = q->dequeue();
            if(node==v){
                int shortest_len = distance[node];
                delete[] distance;
                delete[] visited;
                delete q;
                return shortest_len;
            }

            for(LinkedList::iterator it = list[node].begin(); it != list[node].end(); ++it){
                int i = *it;
                if(!visited[i]){
                    visited[i] = 1;
                    distance[i] = distance[node] + 1;
                    q->enqueue(i);
                }
            }
        }
        delete[] distance;
        delete[] visited;
        delete q;
        return -1;
                //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.

    }

    LinkedList GetNeighbors(int u) const override
    {
        return list[u];
                //TODO: Return the list of neighbors.
    }

};

#endif // ADJACENCY_LIST_GRAPH_H
