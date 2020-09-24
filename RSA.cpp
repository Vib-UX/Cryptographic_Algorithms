#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

// Key generation

long long inv(long long a, long long ph){

    for(long long i=0; i<ph;i++){
        if((a*i)%ph==1){
            return i;
        }
    }
}

long long gcd(long long num1, long long num2){

    if(num2==0){
        return num1;
    }

    return gcd(num2, num1%num2);



}

int main(){

    cout<<"Enter the values of 'p' and 'q' for key generation "<<endl;
    long long p,q;
    cin>>p>>q;

    long long n=p*q;
    long long phi = (p-1)*(q-1);

    long long e;
    for(long long i=2;i<phi;i++){
        if(gcd(phi,i)==1){
            e=i;
            break;
        }
    }

    long long d = inv(e,phi);



    cout<<"Public Key : ("<<e<<","<<n<<") "<<endl;
    cout<<"Private Key : ("<<d<<","<<n<<") "<<endl;

    cout<<"Enter the pln text : < "<<n<<endl;
    string s;
    cin>>s;
    /*long long s;
    cin>>s;

    s = (pow(s,e));
    long long output = s%n;
    cout<<"encrypted : "<<output<<endl;

    long long l = pow(output,d);
    long long decrypt = l%n;

    cout<<"decrypted : "<<decrypt;*/


    string cypher;

    for(long long i=0;i<s.size();i++){
        long long p = s[i]-97;
        long long C = pow(p,e);
        C=C%n;
        cypher+=C%26+97;

    }

    cout<<"Encrypted Message is : "<<cypher<<endl;


    string decrypt;

    for(long long i=0;i<cypher.size();i++){
        long long count=26;
        if(cypher[i]-97<2){
            count=0;
        }
        long long p = cypher[i]-97+count;
        long long M = pow(p,d);
        M=M%n;
        decrypt+=M+97;
    }

    cout<<"Decrypted message : "<<decrypt<<endl;





}
