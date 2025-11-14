#include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        if(c=='F'){
            int val;
            in_file >> val;
            if(bst->find(val)){
                cout << "Key " << val << " found in BST." << endl;
            }
            else{
                cout << "Key " << val << " not found in BST." << endl;
            }
        }
        else if(c=='E'){
            if(bst->empty()){
                cout << "Empty" << endl;
            }
            else{
                cout << "Not empty" << endl;
            }
        }
        else if(c=='I'){
            int val;
            in_file >> val;
            if(bst->insert(val,val)){
                cout << "Key " << val << " inserted into BST, BST (Default): ";
                bst->print('D');
            }
            else{
                cout << "Insertion failed! Key " << val << " already exists in BST, BST (Default): ";
                bst->print('D');
            }
        }
        else if(c=='D'){
            int val;
            in_file >> val;
            if (bst->remove(val)){
                cout << "Key " << val << " removed from BST, BST (Default): ";
                bst->print('D');
            } else {
                cout << "Removal failed! Key " << val << " not found in BST, BST (Default): ";
                bst->print('D');
            }
        }
        else if(c=='S'){
            cout << "Size: " << bst->size() << endl;
        }
        else if(c=='M'){
            string st;
            in_file >> st;
            if(st=="Min"){
                try {
                    cout << "Minimum value: " << bst->find_min() << endl;
                } catch (...) {
                    cout << "Empty BST" << endl;
                }
            }
            else if(st=="Max"){
                try {
                    cout << "Maximum value: " << bst->find_max() << endl;
                } catch (...) {
                    cout << "Empty BST" << endl;
                }
            }
        }
        else if(c=='T'){
            string trav;
            in_file >> trav;
            if(trav=="In"){
                bst->print('I');
            }
            else if(trav=="Pre"){
                bst->print('P');
            }
            else if(trav=="Post"){
                bst->print('O');
            }
        }
        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}

/*
g++ task1.cpp -o task1
./task1 in_task1.txt > myout_task1.txt
*/
