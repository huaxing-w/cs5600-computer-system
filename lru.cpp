#include "bits/stdc++.h"
using namespace std;


struct Node{
    int key;
    Node* next;
    Node* perv;
    Node(int val){
        this->key=val;
        this->next=nullptr;
        this->perv=nullptr;
    }
};

class lru{
    public:
    Node* head;
    Node* tail;
    int size;
    int capacity;
    unordered_map<int,Node*>dic;
    int hitCount;
    int missCount;

    lru(int total){
        this->head=new Node(-1);
        this->tail=new Node(-1);
        head->next=tail;
        tail->perv=head;
        this->size=0;
        this->capacity=total;
        this->hitCount=0;
        this->missCount=0;
    }

    void access(int key){
        if(dic.find(key)!=dic.end()){
            cout<<" hit ";
            hitCount+=1;
            Node* cur=dic[key];
            moveToHead(cur);
            printList();
        }
        else{
            cout<<" miss ";
            missCount+=1;
            Node* cur=new Node(key);
            dic[cur->key]=cur;
            addToHead(cur);
            size+=1;
            if(size>capacity){
                Node* pop=popTail();
                dic.erase(pop->key);
                printList();
                cout<<" MRU put "<<cur->key<<" ";
                cout<<" MRU poped "<<pop->key<<" ";
                size-=1;
            }
            else{
                printList();
                cout<<" MRU put "<<cur->key<<" ";
            }
            
        }
        cout<<" [Hits: "<<hitCount<<" Misses: "<<missCount<<"] ";
    }

    void deleteNode(Node* cur){
        Node* p=cur->perv;
        Node* nxt=cur->next;
        p->next=nxt;
        nxt->perv=p;
    }
    void addToHead(Node* cur){
        Node* nxt=head->next;
        head->next=cur;
        cur->next=nxt;
        nxt->perv=cur;
        cur->perv=head;
    }
    void moveToHead(Node* cur){
        deleteNode(cur);
        addToHead(cur);
    }

    Node* popTail(){
        Node* last=tail->perv;
        deleteNode(last);
        return last;
    }

    void printList(){
        Node* itr=head->next;
        cout<<"lruHead->";
        while(itr!=tail){
            cout<<"["<<itr->key<<"]";
            if(itr->next!=tail){
                cout<<"->";
            }
            itr=itr->next;
        }
        cout<<"<-lruTail";

    }

    void run(vector<int>& address){
        for(auto& i:address){
            cout<<"Access: "<<i;
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
    lru cache(5);
    vector<int>temp={1,2,3,4,5,4,3,2,312,3,12,3,123,2,45,3215,34,15,4325,43,25,23,1423,14,231,4,231,453,25,432};
    cache.run(temp);
    return 0;
}