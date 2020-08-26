#include<iostream>
#include<stdlib.h>
using namespace std;

int inv(int a){

    for(int i=0; i<26;i++){
        if((a*i)%26==1){
            return i;
        }
    }
}

int main(){

    string pln_txt;
    int a,b;
    cout<<"Enter the values of a & b : "<<endl;
    cin>>a>>b;
    cout<<"Enter the Text : ";
    cin>>pln_txt;
    string cyp_txt;
    int n = pln_txt.size();

    int choice;
    cout<<"Enter 1 for encryption , 2 for decryption "<<endl;
    cin>>choice;

    if(choice==1){

    for(int i=0;i<n;i++){
        cyp_txt+=(((a*(pln_txt[i]-97))+b)%26+97);
    }

    cout<<"Encrypted Message is : "<<cyp_txt;

    }
    else if(choice == 2){

    int p = inv(a);
    for(int i=0;i<n;i++){
            int count=0;
        if((pln_txt[i]-97-b)<0){
            count=26;
        }
        //cyp_txt+=((p*(abs((pln_txt[i]-97)-b)))%26+97);
        int t= (p*(abs((pln_txt[i]-97)-b)))%26;
        int l = abs(count-t);

       cyp_txt+=l+97;
    }

    cout<<"Decrypted Message is : "<<cyp_txt;
    }
}
