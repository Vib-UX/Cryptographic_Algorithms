#include<iostream>
#include<cstring>
using namespace std;

int main(){

    string s;
    cout<<"Enter the message : "<<endl;
    cin>>s;

    int key;
    cout<<"Enter the key : "<<endl;
    cin>>key;


    string output;



    //cout<<s[0]+0;


    int choice;
    cout<<"Choice: ";
    cin>>choice;

    if(choice==1){
    for(int i=0;i<s.size();i++){
            if(isupper(s[i])){
                output+=char((s[i]+key-65)%26+65);
            }
            else{
            if(s[i]+key>122){
                int t=(s[i]+key)-122+96;                //122 is the ascii_value of z
                output+=char(t);

            }else{
            output+=char(s[i]+key);
            }
        }
    }

    cout<<"Encrypted message: "<<output<<endl;
    }
    else{
        for(int i=0;i<s.size();i++){
            if(isupper(s[i])){
                output+=char((s[i]-65-key)%26+65);
            }
            else{
                    if(s[i]-key<97){
                        int t = (s[i]-key)-97+123;          // 97 is the ascii value of 'a'
                        output+=char(t);
                    }
                    else{
                        output+=char(s[i]-key);
                }
            }
        }
        cout<<"Decrypted Message: "<<output<<endl;
    }


}
