#include<iostream>
using namespace std;

int main(){
    int n,k;
    cin >> n >> k;
    int* arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    
    if(k<=0 || n<=0){
        cout << -1 << endl;
        return 0;
    }
    
    if(k>n){
        cout << -1 << endl;
        return 0;
    }
    
    long long low = arr[0];
    long long high = arr[0];
    long long min_maxWorkload = 0;
    
    for(int i=1;i<n;i++){
        if(arr[i]>low){
            low = arr[i]; 
        }
        high += arr[i];
    }
    
    while(low<=high){
        long long mid = (low+high)/2;
        int people = 1;
        int flag = 1;
        long long sum = 0;
        for(int i=0;i<n;i++){
            int temp = sum + arr[i];
            if(arr[i]>mid){
                flag = 0;
                break;
            }
            if(temp>mid){
                sum = arr[i];
                people++;
            }
            else{
                sum+=arr[i];
            }
        }
        if(flag==1 && people<=k){
            min_maxWorkload = mid;
            high = mid-1;
        }
        else{
            low = mid+1;
        }
        
    }
    
    cout << min_maxWorkload << endl;
    free(arr);
    return 0;
}
