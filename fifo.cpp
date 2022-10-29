#include "bits/stdc++.h"
using namespace std;

class fifo{
    public:
    int size;
    int capacity;
    queue<int>q;
    set<int>seen;
    int hitCount;
    int missCount;
    fifo(int total){
        this->capacity=total;
        size=0;
        capacity=total;
        hitCount=0;
        missCount=0;
    }
    void access(int key){
        cout<<"Access: ";
        cout<<key<<" ";
        if(seen.find(key)!=seen.end()){
            cout<<"hit ";
            hitCount+=1;
            printQueue();

        }
        else{
            cout<<"miss ";
            missCount+=1;
            q.push(key);
            
            seen.insert(key);
            size+=1;
            
            
            if(size>capacity){
                int front=q.front();
                q.pop();
                printQueue();
                cout<<"enqueue "<<key<<" ";
                cout<<"poped "<<front<<" ";
                seen.erase(front);
                size-=1;
            }
            else{
                printQueue();
                cout<<"enqueue "<<key<<" ";
            }

        }
        cout<<"[Hits: "<<hitCount<<" Misses: "<<missCount<<"]";
        
    }
    void printQueue(){
        cout<<"QueueFront->[";
        queue<int>copy=q;
        while(!copy.empty()){
            int f=copy.front();
            cout<<f;

            copy.pop();
            if(!copy.empty()){
                cout<<" ";
            }
        }
        cout<<"]<-QueueBack ";
    }

    void run(vector<int>& temp){
        for(auto& i:temp){
            access(i);
            
            cout<<endl;
        }
        float hitrate=hitCount*1.0/(hitCount+missCount);
        cout.setf(ios::fixed);
        cout<<setprecision(2);
        cout<<"FINALSTATS: "<<"hits: "<<hitCount<<" misses: "<<missCount<<" hitrate: "<<hitrate<<endl;

    }


};

int main(){
    fifo f(3);
    vector<int>temp={1,2,3,4,5,4,3,2,312,3,12,3,123,2,45,3215,34,15,4325,43,25,23,1423,14,231,4,231,453,25,432};
    f.run(temp);

    return 0;
}