#include<bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include<pthread.h>
#include<thread>
#include<omp.h>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
using namespace std:: chrono;





unordered_map<char,char> inverse_map(unordered_map<char,char> &map)
{
    unordered_map<char,char> inv;
    for_each(map.begin(), map.end(),
                [&inv] (const std::pair<char,char> &p)
                {
                    inv.insert(make_pair(p.second, p.first));
                });
    return inv;
}

void decryption(string &str, string &input, unordered_map<char,char>& map_1, int si, int ei){



    string decrypt;
    for(int i=0;i<input.size();i++){
        decrypt+=map_1[input[i]];
    }

    str = decrypt;

}

void encryption(string &str, string &input, unordered_map<char,char> &map, int si, int ei){

    string encrypt;

    for(int i=si;i<ei;i++){
        encrypt+=map[input[i]];
    }

    //return encrypt;
    str = encrypt;

}

void removeSpecialCharacter(string &s)
{
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < 'A' || s[i] > 'Z' &&
            s[i] < 'a' || s[i] > 'z')
        {
            s.erase(i, 1);
            i--;
        }
    }
}
string removeDuplicates(string s){
  unordered_map<char,bool> exists;
  string output;
  for(int i=0;i<s.size();i++){
    exists[s[i]]=true;
  }

  for(int i=0;i<s.size();i++){
    if(exists[s[i]]==true){
        output+=s[i];
        exists[s[i]]=false;
    }
  }

  return output;
}

void task_1(vector<string> &for_encrypt, vector<string> &subsample, int si, int ei, unordered_map<char,char> &map){
    #pragma omp parallel for num_threads(MAX)
    //int iterat=si;
    //while(iterat<ei){
    for(int iterat = si; iterat<ei;iterat++){
        transform(subsample.at(iterat).begin(), subsample.at(iterat).end(), subsample.at(iterat).begin(), ::tolower);


        /*vector<string> output(2);

        thread t1(encryption,ref(output[0]),ref(input),ref(map),0,input.size()/2);
        thread t2(encryption,ref(output[1]),ref(input),ref(map),input.size()/2,input.size());



        t1.join();
        t2.join();*/

        //int number = input.size();

        int num_threads = 2;
        int steps = subsample.at(iterat).size()/num_threads+1;
        vector<thread> threads;
        vector<string> output(num_threads);

        for(int i=0;i<num_threads;i++){
            threads.push_back(thread(encryption,ref(output[i]),ref(subsample.at(iterat)),ref(map),i*steps,(i+1)*steps));
        }


        for (thread &t : threads) {
            if (t.joinable()) {
                t.join();
            }

        }



        /*for(int i=0;i<output.size();i++){
            cout<<output[i];
        }*/
        //cout<<output[0]+output[1]+output[2]+output[3]+output[4]+output[5]+output[6]+output[7]+output[8];
        //cout<<output[0]+output[1]<<endl;

        string str = output[0]+output[1];
        for_encrypt.push_back(str);
        //iterat++;



    }
}


void task_2(vector<string> &for_decrypt, vector<string> &subsample, int si, int ei, unordered_map<char,char> &map){

    //int iterat=si;
    //while(iterat<ei){
    #pragma omp parallel for num_threads(MAX)
    for(int iterat = si; iterat<ei;iterat++){

        transform(subsample.at(iterat).begin(), subsample.at(iterat).end(), subsample.at(iterat).begin(), ::tolower);


        vector<string> output(2);

        thread t5(encryption,ref(output[0]),ref(subsample.at(iterat)),ref(map),0,subsample.at(iterat).size()/2);
        thread t6(encryption,ref(output[1]),ref(subsample.at(iterat)),ref(map),subsample.at(iterat).size()/2,subsample.at(iterat).size());



        t5.join();
        t6.join();

        //int number = input.size();

        /*int num_threads = 2;
        int steps = subsample.at(iterat).size()/num_threads+1;
        vector<thread> threads;
        vector<string> output(num_threads);

        for(int i=0;i<num_threads;i++){
            threads.push_back(thread(decryption,ref(output[i]),ref(subsample.at(iterat)),ref(map),i*steps,(i+1)*steps));
        }


        for (thread &t : threads) {
            if (t.joinable()) {
                t.join();
            }

        }*/



        /*for(int i=0;i<output.size();i++){
            cout<<output[i];
        }*/
        //cout<<output[0]+output[1]+output[2]+output[3]+output[4]+output[5]+output[6]+output[7]+output[8];
        //cout<<output[0]+output[1]<<endl;

        string str1 = output[0]+output[1];
        for_decrypt.push_back(str1);
        //iterat++;



    }
}

void init_code(){
    fast_io;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
}


int main(){

    init_code();
    vector<string> s1;
    fstream file;
    string word,t,q,filename;
     filename = "dataset.txt";
     file.open(filename.c_str());
      while (file >> word)
    {

        s1.push_back(word);

    }

    /*for(int i=0;i<s1.size();i++){
        cout<<s1[i]<<endl;
    }*/

    cout<<"Total Dataset Size : "<<s1.size()<<" number of words"<<endl;

    vector<string> subsample;

    int i=0;

    while(i<s1.size()){

        subsample.push_back(s1.at(i));

        i+=;
    }

    cout<<subsample.size()<<" Words \n";  //Around 240 words
    //cout<<"Dictionary Words : "<<endl;
    cout<<endl;
    /*for(int i=0;i<subsample.size()/2;i++){
        cout<<subsample.at(i)<<"                        "<<subsample.at(i+subsample.size()/2)<<endl;
    }*/
    const auto processor_count = thread::hardware_concurrency();
    unsigned int n = thread::hardware_concurrency();
    cout << n << " concurrent threads are supported.\n";



    //cout<<processor_count<<endl;


    string key;
    cout<<"Enter the Key : "<<endl;
    getline(cin,key);
    clock_t time_req;
    time_req=clock();

    key = removeDuplicates(key);
    removeSpecialCharacter(key);
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto start = high_resolution_clock::now();
    unordered_map<char,char> map;

    string string_difference;



    string all_char ="abcdefghijklmnopqrstuvwxyz";

    string temp = key;
    sort(temp.begin(),temp.end());

    set_difference(all_char.begin(), all_char.end(), temp.begin(), temp.end(), back_inserter(string_difference));
    //cout << "In string1 but not string2: " << string_difference << std::endl;

    string final_key_used = key+string_difference;
    //cout<<final_key_used<<endl;
    //cout<<all_char<<endl;
    for(int i=0;i<all_char.size();i++){
        map[all_char[i]]=final_key_used[i];
    }
    unordered_map<char, char> inverted = inverse_map(map);

    //cout<<final_key_used<<endl;




    vector<string> for_encrypt;
    vector<string> for_decrypt;



    thread t1(task_1,ref(for_encrypt),ref(subsample), 0, subsample.size()/2,ref(map));
    thread t2(task_2,ref(for_decrypt),ref(subsample),subsample.size()/2,subsample.size(),ref(inverted));

    t1.join();
    t2.join();

    /*cout<<"\nEncrypted Text :            Decrypted Text : \n";
    for(int i=0;i<for_encrypt.size();i++){
        cout<<for_encrypt.at(i)<<"                      "<<for_decrypt.at(i)<<endl;;
    }

    /*for(int i=0;i<for_decrypt.size();i++){
        cout<<for_decrypt.at(i)<<endl;
    }*/






    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop-start);
    cout<<"\nTime taken: "<<duration.count()<<" s "<<endl;








}
