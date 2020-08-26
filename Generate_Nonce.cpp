#include<iostream>
#include<stdlib.h>
using namespace std;

int main(){


    int n;
    cin>>n;

    int *arr = new int[n];


    for(int i=0;i<n;i++){
        arr[i]=rand()%10000+1;
    }

    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }


}
