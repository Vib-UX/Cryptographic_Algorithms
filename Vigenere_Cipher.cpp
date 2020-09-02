#include<iostream>
#include<cstring>
using namespace std;

int main(){

    string plntxt;
    cout<<"Enter the Text : "<<endl;
    cin>>plntxt;

    string key;
    cout<<"Enter the key : "<<endl;
    cin>>key;

    string new_key;
    int val=0;

    int i=0;
    while(i<key.size()){
        new_key+=key[i];
        val++;
        if(val==plntxt.size()){
            break;
        }
        if(i==key.size()-1){
            i=0;
            continue;
        }
        i++;
    }


    cout<<new_key;

    string cypher;
    int choice;
    cout<<"Enter 1 for encryption , 2 for decryption "<<endl;
    cin>>choice;

    if(choice ==1){
    for(int i=0;i<plntxt.size();i++){
        cypher += ((new_key[i]-97 + plntxt[i]-97)%26+97);
    }

    cout<<"Encrypted Text : "<<cypher<<endl;

    }
    else{
        for(int i=0;i<plntxt.size();i++){
            int count=0;
            if((plntxt[i]-new_key[i])<0){
                count=26;
            }
            cypher+=((count+(plntxt[i]-97)-(new_key[i]-97))%26+97);
        }
    cout<<"Decrypted Text : "<<cypher<<endl;
    }


}
