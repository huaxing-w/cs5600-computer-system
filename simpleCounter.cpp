#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;

struct counter{
    int count;
    mutex myMutex;
    counter(){
        count=0;
    }
};

void increment(counter* c){
    for(int i=0;i<1000000;i++){
        lock_guard<mutex> myLock(c->myMutex);
        c->count+=1;
    }

}

int main(){
    const auto cpus = std::thread::hardware_concurrency();
    for(int i=1;i<=cpus;i++){
        counter* c=new counter();
        vector<thread>lst;
        
        auto start = high_resolution_clock::now();
        for(int j=0;j<i;j++){
            lst.push_back(thread(increment,c));
        }
        for(int j=0;j<i;j++){
            lst[j].join();
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout<<"with "<<i<<" cpu in use, the time spend is "<<duration.count()<<" microseconds" << endl;
        cout<<"the counter now is "<<c->count<<endl;
        delete c;  
    }
    return 0;
}