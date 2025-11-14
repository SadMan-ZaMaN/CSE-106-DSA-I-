#include<iostream>
using namespace std;

int main(){
    int n,b;
    cin >> n >> b;
    
    if(n<=0 || b<=0){
        cout << "false" << endl;
        return 0;
    }
    
    if(b==0 || n%b!=0){
        cout << "false" << endl;
        return 0;
    }
    
    int person_per_bench = n/b;
    int* arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
        if (arr[i]<0 || arr[i]>2){
        cout << "Invalid input.Only 0, 1 or 2 are allowed" << endl;
        return 0;
        }
    }
    
    int m;
    cin >> m;
    
    if(n==1){
        if(arr[0]==0 && m==1){
            cout << "true" << endl;
        }
        else{
            cout << "false" << endl;
        }
        free(arr);
        return 0;
    }
    
    int person = 0;
    for(int i=0;i<n;i++){
        
        if(i==0){
            if(arr[i]==0 && person_per_bench==1){
                person++;
            }
            else if(arr[i]==0 && arr[i+1]==0 ){
                person++;
            }
        }
        
        else if(i==n-1){
            if(arr[i]==0 && person_per_bench==1){
                person++;
            }
            else if(arr[i]==0 && arr[i-1]==0){
                person++;
            }
        }
        
        else if(arr[i]==0){
            if((i%person_per_bench)==0 && arr[i+1]!=2){
                person++;
            }
            else if((i%person_per_bench)==(person_per_bench-1) && (arr[i-1]==0)){
                person++;
            }
            else if((i%person_per_bench)!=0 && (i%person_per_bench)!=(person_per_bench-1)){
                if(arr[i-1]!=1 && arr[i-1]!=2 && arr[i+1]!=2){
                    person++;
                }
            }
        }
    }
    
    bool ans;
    if(person<m){
        cout << "false" << endl;
    }
    else{
        cout << "true" << endl;
    }
    free(arr);
    return 0;
}


/*

for(int i=0;i<n;i++){
    int first = (i/person_per_bench)*person_per_bench;
    int last = first + person_per_bench - 1;
    if(arr[i]==2){
        if(i>first && (arr[i-1]==1 || arr[i-1]==2)){
            cout << "Invalid sitting arrangement" << endl;
            return 0;
        }
        if(i<last && (arr[i+1]==1 || arr[i+1]==2)){
            cout << "Invalid sitting arrangement" << endl;
            return 0;
        }
    }

    if(arr[i]==1){
        if(i<last && (arr[i+1]==1 || arr[i+1]==2)){
            cout << "Invalid sitting arrangement" << endl;
            return 0;
        }
    }
}

*/
