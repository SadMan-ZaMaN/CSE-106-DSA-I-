#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    freopen("test_input_1.txt", "r", stdin); // Test Case 1
    //freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        static int timestampArray[10001] = {0};
        static bool MergedQueue = false;
        int OperationType;
        cin >> OperationType;

        if(OperationType==1){
            int id,timestamp;
            cin >> id >> timestamp;
            timestampArray[id] = timestamp;
            cout << "Operation " << i << " (Arrival " << id << " " << timestamp << "): ";
            if(!MergedQueue){
                if(Q1->empty() && Q2->empty()){
                    int rand = randomQueue();
                    if(rand==1){
                        Q1->enqueue(id);
                    }
                    else{
                        Q2->enqueue(id);
                    }
                }
                else if(Q1->empty()){
                    Q1->enqueue(id);
                }
                else if(Q2->empty()){
                    Q2->enqueue(id);
                }
                else{
                    int b1 = Q1->back();
                    int b2 = Q2->back();
                    int t1 = timestampArray[b1];
                    int t2 = timestampArray[b2];
                    if(t1<t2){
                        Q1->enqueue(id);
                    }
                    else{
                        Q2->enqueue(id);
                    }
                }
            }
            else{
                Q->enqueue(id);
            }
        }

        else if(OperationType==2){              // value na pawa gele error handling DEBUGG
            int id,timestamp;
            cin >> id >> timestamp;
            cout << "Operation " << i << " (Leave " << id << " " << timestamp << "): ";
           
            if(!MergedQueue){
                int size1 = Q1->size();
                bool leave = false;
                for(int j=0;j<size1;j++){
                    int val = Q1->dequeue();
                    if(!leave && val==id){
                        leave = true;
                        continue;
                    }
                    Q1->enqueue(val);
                }

                if(leave == false){
                    int size2 = Q2->size();
                    for(int j=0;j<size2;j++){
                        int val = Q2->dequeue();
                        if(!leave && val==id){
                            leave = true;
                            continue;
                        }
                        Q2->enqueue(val);
                    }
                }
            }
            else{
                int size = Q->size();
                for(int j=0;j<size;j++){
                    int val = Q->dequeue();
                    if(val==id){
                        continue;
                    }
                    Q->enqueue(val);
                }
            }
        }

        else if(OperationType==3){
            cout << "Operation " << i << " (Merge): ";
            if(!MergedQueue){
                while(Q1->empty()== false || Q2->empty() == false){
                    if(Q1->empty()){
                        int val = Q2->dequeue();
                        Q->enqueue(val);
                    }
                    else if(Q2->empty()){
                        int val = Q1->dequeue();
                        Q->enqueue(val);
                    }
                    else{
                        int val1 = Q1->front();
                        int val2 = Q2->front();
                        int t1 = timestampArray[val1];
                        int t2 = timestampArray[val2];
                        if(t1 < t2){
                            int val = Q1->dequeue();
                            Q->enqueue(val);
                        }
                        else{
                            int val = Q2->dequeue();
                            Q->enqueue(val);
                        }
                    }
                }
                MergedQueue = true;
            }
            else{
                cout << "Already Merged" << endl;
            }
        }

        else if(OperationType==4){
            if(MergedQueue){
                cout << "Operation " << i << " (Split): ";
                int i=0;
                while(Q->empty()==false){
                    int val = Q->dequeue();
                    if(i%2==0){
                        Q1->enqueue(val);
                    }
                    else{
                        Q2->enqueue(val);
                    }
                    i++;
                }
                MergedQueue = false;
            }
            else{
                cout << "Already Splitted" << endl;
            }
        }

        else if(OperationType==5){
            cout << "Operation " << i << " (Departure): ";
            if(MergedQueue){
                if(Q->empty()){
                    cout << "Empty Queue" << endl;
                }
                else{
                    Q->dequeue();
                }
            }
            else{
                if(Q1->empty() && Q2->empty()){
                    cout << "Empty Queue" << endl;
                }
                else if(Q2->empty()){
                    Q1->dequeue();
                }
                else if(Q1->empty()){
                    Q2->empty();
                }
                else{
                    int rand = randomQueue();
                    if(rand==1){
                        Q1->dequeue();
                    }
                    else{
                        Q2->dequeue();
                    }
                }
            }
        }

        cout << endl;
        cout << "Q1: " << Q1->toString() << endl;
        cout << "Q2: " << Q2->toString() << endl;
        cout << "Q : " << Q->toString() << endl;


        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    delete Q1;
    delete Q2;
    delete Q;
    return 0;
}
// g++ main.cpp arrayqueue.cpp listqueue.cpp -o main
// .\main.exe









