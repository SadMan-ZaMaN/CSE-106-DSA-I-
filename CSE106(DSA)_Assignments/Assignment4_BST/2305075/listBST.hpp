#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here

    void delete_all(Node* node){
        if(node){
            delete_all(node->left);
            delete_all(node->right);
            delete node;
        }
        else{
            return;
        }
    }

    void print_preorder(Node* node)const{
        if(node!=NULL){
            std::cout << "(" << node->key << ":" << node->value << ") ";
            print_preorder(node->left);
            print_preorder(node->right);
        }
        else{
            return;
        }
    }

    void print_inorder(Node* node)const{
        if(node!=NULL){
            print_inorder(node->left);
            std::cout << "(" << node->key << ":" << node->value << ") ";
            print_inorder(node->right);
        }
        else{
            return;
        }
    }

    void print_postorder(Node* node)const{
        if(node!=NULL){
            print_postorder(node->left);
            print_postorder(node->right);
            std::cout << "(" << node->key << ":" << node->value << ") ";
        }
        else{
            return;
        }
    }

    void print_default(Node* node)const{
        if(node!=NULL){
            std::cout << "(" << node->key << ":" << node->value;
            if(node->left!= NULL || node->right!= NULL){
                std::cout << " ";
                if(node->left!=NULL){
                    print_default(node->left);
                }
                else{
                    std::cout << "()";
                }
                if(node->right!=NULL){
                    std::cout << " ";
                    print_default(node->right);
                }
            }
            std::cout << ")";
        }
        else{
            return;
        }
    }

    Node* inOrderSuccessor(Node* node){
        node = node->right;
        while(node && node->left!=nullptr){
            node = node->left;
        }
        return node;
    }

    Node* Deletion(Node* root,Key key,bool &Found){
        if(root==nullptr){
            Found = false;                  //debug
            return nullptr;
        }
        if(key>root->key){
            root->right = Deletion(root->right,key,Found);
        }
        else if(key<root->key){
            root->left = Deletion(root->left,key,Found);
        }
        else{
            Found = true;
            if(root->left==nullptr && root->right==nullptr){
                delete root;
                return nullptr;
            }

            if(!root->right){
                Node* temp = root->left;
                delete root;
                return temp;
            }

            if(!root->left){
                Node* temp = root->right;
                delete root;
                return temp;
            }

            Node* iSuc = inOrderSuccessor(root);
            root->key = iSuc->key;
            root->value = iSuc->value;
            root->right = Deletion(root->right,iSuc->key,Found);
        }
        return root;
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() {
        delete_all(root);
        // TODO: Implement destructor to free memory
    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        if(root==nullptr){
            root = new Node(key,value);
            ++node_count;
            return true;
        }
        Node* temp = root;
        Node* prev = nullptr;
        while(temp!=nullptr){
            prev = temp;
            if(key==temp->key){
                return false; // key already ache
            }
            else if(key<temp->key){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        Node* new_node = new Node(key,value);
        if(key<prev->key){
            prev->left = new_node;
        }
        else{
            prev->right = new_node;
        }
        ++node_count;
        return true;
        // TODO: Implement insertion logic

    }
    
    /**
     * Remove a key-value pair from the BST
     */

    bool remove(Key key) override {
        bool Found = false;
        root = Deletion(root,key,Found);
        if(Found){
            --node_count;
            return true;
        }
        else{
            return false;
        }
        // TODO: Implement removal logic

    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override {
        Node* temp = root;
        while(temp!=nullptr){
            if(key<temp->key){
                temp = temp->left;
            }
            else if(key>temp->key){
                temp = temp->right;
            }
            else{
                return true;
            }
        }
        return false;
        // TODO: Implement find logic

    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override {
        Node* temp = root;
        while(temp!=nullptr){
            if(key<temp->key){
                temp = temp->left;
            }
            else if(key>temp->key){
                temp = temp->right;
            }
            else{
                return temp->value;
            }
        }
        throw std::runtime_error("Key not found");
        // TODO: Implement get logic

    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override {
        Node* temp = root;
        while(temp!=nullptr){
            if(key<temp->key){
                temp = temp->left;
            }
            else if(key>temp->key){
                temp = temp->right;
            }
            else{
                temp->value = value;
                return;
            }
        }
        throw std::runtime_error("Key not found");
        // TODO: Implement update logic

    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        delete_all(root);
        root = nullptr;
        node_count = 0;
        // TODO: Implement clear logic

    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        return node_count;
        // TODO: Implement size logic

    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        if(node_count==0){
            return true;
        }
        else{
            return false;
        }
        // TODO: Implement empty check logic

    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        if(root!=nullptr){
            Node* temp = root;
            while(temp->left!=nullptr){
                temp = temp->left;
            }
            return temp->key;
        }
        else{
            throw std::runtime_error("The BST is empty, no minimum key found.");
        }
        // TODO: Implement find_min logic

    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        if(root!=nullptr){
            Node* temp = root;
            while(temp->right!=nullptr){
                temp = temp->right;
            }
            return temp->key;
        }
        else{
            throw std::runtime_error("The BST is empty, no maximum key found.");
        }
        // TODO: Implement find_max logic

    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override {
        if(root==nullptr){
            std::cout << "Empty" << std::endl;
            return;
        }
        else{
            if(traversal_type=='D' || traversal_type=='d'){
                print_default(root);
            }
            else if(traversal_type=='I'|| traversal_type=='i'){
                std::cout << "BST (In-order): ";
                print_inorder(root);
            }
            else if(traversal_type=='P'||traversal_type=='p'){
                std::cout << "BST (Pre-order): ";
                print_preorder(root);
            }
            else if(traversal_type=='O'||traversal_type=='o'){
                std::cout << "BST (Post-order): ";
                print_postorder(root);
            }
            else{
                throw std::invalid_argument("Invalid traversal type");
            }
        }
        std::cout << std::endl;
        // TODO: Implement print logic
        
    }
    
};

#endif // LISTBST_H
