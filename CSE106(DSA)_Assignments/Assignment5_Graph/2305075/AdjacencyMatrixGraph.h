#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"
#include "queue.h"
#include "linkedList.h" 
#include<vector>
#include<algorithm>

class AdjacencyMatrixGraph : public GraphADT
{
private:
    int** mat;
    int maxSize;
    int newMaxSize;
    //TODO: Consider necessary private members as per your discretion

    void resizeMatrix()
    {
        int newSize = newMaxSize;
        int** newMat = new int*[newSize];
        for(int i=0;i<newSize;i++){
            newMat[i] = new int[newSize];
            for(int j=0;j<newSize;j++){
                if(i<maxSize && j<maxSize){
                    newMat[i][j] = mat[i][j];
                } 
                else{
                    newMat[i][j] = 0; 
                }
            }
        }
        for(int i=0;i<maxSize;i++){
            delete[] mat[i];
        }
        delete[] mat;
        mat = newMat;
        maxSize = newSize;
        //TODO: you need to resize your matrix when you will less data or more data
    }

    int resized_capacity(int v) const{
        int new_size = maxSize * 2;
        if (v + 1 > new_size) {
            new_size = v + 1;
        }
        return new_size;
    }

public:
    void AddNode(int v) override
    {
        if(v >= maxSize){
            newMaxSize = resized_capacity(v);
            resizeMatrix();
        }
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        //resizeMatrix();
    }

    void AddEdge(int u, int v) override
    {
        if(u<0 || v<0){
            return;
        }

        if(u>=maxSize || v>=maxSize){
            int big;
            if(u>=v){
                big = u;
            }
            else{
                big = v;
            }
            newMaxSize = resized_capacity(big);
            resizeMatrix();
        }
        
        mat[u][v] = 1;
        mat[v][u] = 1; 

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
        if(mat[u][v]==1 && mat[v][u]==1){
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
            mat[i][v] = 0;
            mat[v][i] = 0;
        }
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
        mat[u][v] = 0;
        mat[v][u] = 0;
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
            for(int i=0;i<maxSize;i++){
                if(mat[node][i]==1 && visited[i]==0){
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
            return;
        }
        if(u<0 || v<0){
            return;
        }
        if(!CheckPath(u, v)){
            std::cout << "No path exists between " << u << " and " << v << std::endl;
            return;
        }
        if (u == v) {
            std::cout << "Shortest Path: " << u << std::endl;
            return;
        }

        int* pred = new int[maxSize];
        int* visited = new int[maxSize];
        for(int i=0;i<maxSize;i++) {
            pred[i] = -1; 
            visited[i] = 0; 
        }

        ListQueue* q = new ListQueue();
        q->enqueue(u);
        visited[u] = 1;
        bool flag = false;

        while(q->empty()==false && flag==false){
            int node = q->dequeue();
            for(int i=0;i<maxSize;i++){
                if(mat[node][i]==1 && visited[i]==0){
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

        if(flag==true){
            std::vector<int> arr;
            int traceB = v;
            while(traceB != -1){
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

        while (!q->empty()) {
            int node = q->dequeue();
            if (node == v) {
                int shortest_len = distance[node];
                delete[] distance;
                delete[] visited;
                delete q;
                return shortest_len;
            }
            for (int i = 0; i < maxSize; i++) {
                if (mat[node][i] == 1 && !visited[i]) {
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
        LinkedList neighbors;
        for(int i=0;i<maxSize;i++){
            if(mat[u][i]==1){
                neighbors.append(i);
            }
        }
        return neighbors;
        //TODO return a list of neighbors of node u

    }

};

#endif // ADJACENCY_MATRIX_GRAPH_H
