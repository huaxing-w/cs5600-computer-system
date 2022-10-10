#include "bits/stdc++.h"
using namespace std;

 struct memoryBlock {
    int address;
    int size;
    memoryBlock* next;
    memoryBlock(int address, int size): address(address), size(size), next(NULL) {}
};

class segregatedList{
    public:
    memoryBlock* head;
    map<int, memoryBlock*>popularMemory;
    
    segregatedList(int size) {
        head = new memoryBlock(60, size);
        memoryBlock* popular1=new memoryBlock(0,10);
        memoryBlock* popular2=new memoryBlock(10,20);
        memoryBlock* popular3=new memoryBlock(30,30);
        popularMemory[10]=popular1;
        popularMemory[20]=popular2;
        popularMemory[30]=popular3;

    }
    memoryBlock* allocate(int size) {
        if(popularMemory.find(size)!=popularMemory.end()){
            memoryBlock* newBlock=popularMemory[size];
            popularMemory.erase(size);
            return newBlock;
        }
        memoryBlock* cur=head;
        while(cur){
            if(cur->size>=size){
                memoryBlock* newBlock = new memoryBlock(cur->address, size);
                cur->address+=size;
                cur->size-=size;
                return newBlock;
            }
            cur=cur->next;
        }
        return NULL;
    }
    void freeMemory(memoryBlock* block) {
        if(block->size==10 && block->address==0){
            popularMemory[10]=block;
            return;
        }
        if(block->size==20 && block->address==10){
            popularMemory[20]=block;
            return;
        }
        if(block->size==30 && block->address==30){
            popularMemory[30]=block;
            return;
        }
        block->next=head;
        head=block;
        sortMemory();
        mergeMemory();

    }
    void printMemory() {
        memoryBlock* cur=head;
        while(cur){
            cout<<"[address:"<<cur->address<<" size:"<<cur->size<<"]";
            if(cur->next) cout<<"->";
            cur=cur->next;
        }
        cout<<endl;
    }
    void mergeMemory(){
        memoryBlock* dummy=new memoryBlock(-1,-1);
        memoryBlock* perv=dummy;
        memoryBlock* cur=head;
        perv->next=cur;
        while(cur->next){
            memoryBlock* next=cur->next;
            if(perv->address==-1){
                perv=cur;
                cur=next;
                continue;
            }
            if(perv->address+perv->size==cur->address){
                perv->size+=cur->size;
                cur=next;
                perv->next=cur;
            }
            else{
                perv=cur;
                cur=next;
            }
        }
        if(perv->address+perv->size==cur->address){
                perv->size+=cur->size;
                perv->next=nullptr;
            }
        head=dummy->next;

    }
    void sortMemory() {
        function<memoryBlock*(memoryBlock*,memoryBlock*)>merge=[&](memoryBlock* a, memoryBlock* b){
            if(!a) return b;
            if(!b) return a;
            if(a->address<b->address){
                a->next=merge(a->next,b);
                return a;
            }
            b->next=merge(a,b->next);
            return b;
        };

        function<memoryBlock*(memoryBlock*,memoryBlock*)>sortFunc=[&](memoryBlock* head,memoryBlock* tail)->memoryBlock*{
            if(!head){
                return nullptr;
            }
            if(head->next==tail){
                head->next=nullptr;
                return head;
            }
            memoryBlock* slow=head;
            memoryBlock* fast=head;
            while(fast!=tail && fast->next!=tail){
                slow=slow->next;
                fast=fast->next->next;
            }
            memoryBlock* mid=slow;
            return merge(sortFunc(head,mid),sortFunc(mid,tail));
        };
        head=sortFunc(head,NULL);
    }
};

int main(){
    segregatedList ff=segregatedList(120);
    ff.printMemory();
    memoryBlock* block1=ff.allocate(10);
    ff.printMemory();
    memoryBlock* block2=ff.allocate(20);
    ff.printMemory();
    memoryBlock* block3=ff.allocate(30);
    ff.printMemory();
    memoryBlock* block4=ff.allocate(10);
    ff.printMemory();
    memoryBlock* block5=ff.allocate(20);
    ff.printMemory();
    memoryBlock* block6=ff.allocate(30);
    ff.printMemory();
    ff.freeMemory(block1);
    ff.printMemory();
    ff.freeMemory(block3);
    ff.printMemory();
    ff.freeMemory(block2);
    ff.printMemory();
    ff.freeMemory(block4);
    ff.printMemory();
    ff.freeMemory(block5);
    ff.printMemory();
    ff.freeMemory(block6);
    ff.printMemory();
    
    return 0;
}