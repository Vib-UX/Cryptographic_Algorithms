#include<bits/stdc++.h>
// #include<string.h>
// #include<vector>
// #include<unordered_map>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#include<pthread.h>
#include<thread>
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

string decryption(vector<string> &output, string input, unordered_map<char,char>& map){

    unordered_map<char, char> inverted = inverse_map(map);

    string decrypt;
    for(int i=0;i<input.size();i++){
        decrypt+=inverted[input[i]];
    }

    return decrypt;

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


void init_code(){
    fast_io;
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
}

int main(){

    init_code();

    const auto processor_count = thread::hardware_concurrency();
    unsigned int n = thread::hardware_concurrency();
    cout << n << " concurrent threads are supported.\n";
    //cout<<processor_count<<endl;

    string input;
    string key;
    cout<<"Enter the message : "<<endl;
    getline(cin,input);
    cout<<"Enter the Key : "<<endl;
    getline(cin,key);
    clock_t time_req;
    time_req=clock();
    auto start = high_resolution_clock::now();
    removeSpecialCharacter(input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    //cout<<input<<endl;


    key = removeDuplicates(key);
    removeSpecialCharacter(key);
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    //cout<<key<<endl;

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


    /*vector<string> output(2);

    thread t1(encryption,ref(output[0]),ref(input),ref(map),0,input.size()/2);
    thread t2(encryption,ref(output[1]),ref(input),ref(map),input.size()/2,input.size());



    t1.join();
    t2.join();*/


    //int number = input.size();




    int num_threads = 2;
    int steps = input.size()/num_threads+1;
    vector<thread> threads;
    vector<string> output(num_threads);

    for(int i=0;i<num_threads;i++){
        threads.push_back(thread(encryption,ref(output[i]),ref(input),ref(map),i*steps,(i+1)*steps));
    }
    for (std::thread &t : threads) {
        if (t.joinable()) {
        t.join();
        }
    }
    /*for(int i=0;i<output.size();i++){
        cout<<output[i];
    }*/
    //cout<<output[0]+output[1]+output[2]+output[3]+output[4]+output[5]+output[6]+output[7]+output[8];
    cout<<output[0]+output[1];
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"\nTime taken: "<<duration.count()<<" us"<<endl;

    time_req = clock() - time_req;
    cout << "\nMultithreading " << (float)time_req/CLOCKS_PER_SEC << " seconds\n";


    /*string encrypted = ecryption(input,map);

    cout<<"Encypted Text : "<<encrypted<<endl;


    string decrypted = decryption(encrypted,map);

    cout<<"Decrypted Text : "<<decrypted<<endl;

    time_req = clock() - time_req;
    cout << "Linear " << (float)time_req/CLOCKS_PER_SEC << " seconds" << endl;


    /*time_req = clock() - time_req;
    cout << "Linear " << (float)time_req/CLOCKS_PER_SEC << " seconds" << endl;*/

    


}


