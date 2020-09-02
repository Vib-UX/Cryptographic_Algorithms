#include<iostream>
#include<stdlib.h>
using namespace std;
#include<cstring>


int main(){

    string s;
    cout<<"Enter the Message : "<<endl;
    cin>>s;

    int n = s.size();
    int * arr = new int[n];

    for(int i=0;i<n;i++){
        arr[i]=s[i]-48;
    }

    /*for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }*/

    int *key = new int[n];
    for(int i=0;i<n;i++){
        key[i]=rand()%2;
    }

    cout<<"Key generated for you : ";
    for(int i=0;i<n;i++){
        cout<<key[i];
    }

    cout<<" of length : "<<n<<endl;

    for(int i=0;i<n;i++){
        arr[i]=arr[i]^key[i];
    }


    int choice;
    cout<<"Enter 1 for encryption , 2 for decryption "<<endl;
    cin>>choice;
    if(choice ==1){
    cout<<"Encrypted Message : ";
    for(int i=0;i<n;i++){
        cout<<arr[i];
    }

    }
    else{
    cout<<"Decrypted Message : ";
    for(int i=0;i<n;i++){
        cout<<arr[i];
        }
    }


}
