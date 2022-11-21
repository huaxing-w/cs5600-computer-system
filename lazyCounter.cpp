#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;

struct counter{
    int globle;
    mutex glock;
    vector<int>local;
    mutex llock;
    int threshold;
    counter(int threshold){
        this->globle=0;
        local=vector<int>(4,0);
        this->threshold=threshold;
    }
};

void increment(counter* c,int index){
    for(int i=0;i<1000000;i++){
        //lock_guard<mutex> myLock(c->llock);
        c->local[index]+=1;
        if(c->local[index] >= c->threshold){
            lock_guard<mutex> myLock(c->glock);
            c->globle+=c->local[index];
            c->local[index]=0;
        }
    }
    
    if(c->local[index]>0){
        lock_guard<mutex> myLock(c->glock);
        c->globle+=c->local[index];
        c->local[index]=0;

    }
}



int main(){
    counter* c1=new counter(999999);
    auto start1 = high_resolution_clock::now();
    thread t0(increment,c1,0);
    thread t1(increment,c1,1);
    thread t2(increment,c1,2);
    thread t3(increment,c1,3);

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    cout<<"the time spend is "<<duration1.count()<<" microseconds" << endl;
    cout<<"the counter now is "<<c1->globle<<endl;


    counter* c2=new counter(10);
    auto start2 = high_resolution_clock::now();
    for(int i=0;i<4000000;i++){
        c2->globle+=1;
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"the time spend is "<<duration2.count()<<" microseconds" << endl;
    cout<<"the counter now is "<<c2->globle<<endl;

    return 0;
}