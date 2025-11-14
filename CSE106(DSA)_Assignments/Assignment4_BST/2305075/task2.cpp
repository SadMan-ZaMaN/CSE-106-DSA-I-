#include <iostream>
#include <fstream>
#include <string>
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
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1) {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2) {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Phil's words
        // Start your code here
        string PhilWord;
        in_file >> PhilWord;
        if(bst1->find(PhilWord)==false){
            bst1->insert(PhilWord,1);
        }
        else{
            int n = bst1->get(PhilWord);
            n = n+1;
            bst1->update(PhilWord,n);
        }
        // End your code here
    }
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        string ClairWord;
        in_file >> ClairWord;
        if(bst2->find(ClairWord)==false){
            bst2->insert(ClairWord,1);
        }
        else{
            int n = bst2->get(ClairWord);
            n = n+1;
            bst2->update(ClairWord,n); 
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here
        cout << "Phil's words:" << endl;
        bst1->print('I');               // output file e inorder e print korte bolse
        cout << endl;
        cout << "Claire's words:" << endl;
        bst2->print('I');
        //cout << endl;
    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true) {
        string word;
        in_file >> word;
        
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here
        //if(!bst1->empty() && !bst2->empty()){
            if(bst1->find(word)){
                cout << "Phil has " << word << "!" << endl;
                int n = bst1->get(word);
                if(n==1){
                    bst1->remove(word);
                    n = 0;
                }
                else{
                    n = n-1;
                    bst1->update(word,n);
                }
            }
            if(bst2->find(word)){
                cout << "Claire has " << word << "!" << endl;
                int n = bst2->get(word);
                if(n==1){
                    bst2->remove(word);
                    n = 0;
                }
                else{
                    n = n-1;
                    bst2->update(word,n);
                }
            }
            if(!bst1->empty() && !bst2->empty()){
                cout << endl;
                cout << "Phil's remaining words:" << endl;
                bst1->print('I');
                cout << endl;

                cout << "Claire's remaining words:" << endl;
                bst2->print('I');
                cout << endl;
            }
        //}
        else if(bst1->empty() && !bst2->empty()){
            cout << "Phil wins!" << endl;
            break;
        }
        else if(bst2->empty() && !bst1->empty()){
            cout << "Claire wins!" << endl;
            break;
        }
        else if(bst1->empty() && bst2->empty()){
            cout << "It's a tie!" << endl;
            break;
        }
        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}

/*
g++ task2.cpp -o task2
./task2 in_task2.txt > myout_task2.txt
*/
