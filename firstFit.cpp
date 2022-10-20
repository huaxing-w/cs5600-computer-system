#include "bits/stdc++.h"
using namespace std;

 struct memoryBlock {
    int address;
    int size;
    memoryBlock* next;
    memoryBlock(int address, int size): address(address), size(size), next(NULL) {}
};

class firstFit{
    public:
    memoryBlock* head;
    firstFit(int size) {
        head = new memoryBlock(0, size);
    }

    void clearUp(){
        memoryBlock* dummy=new memoryBlock(-1,-1);
        dummy->next=head;
        memoryBlock* cur=head;
        memoryBlock* perv=dummy;
        while(cur){
            memoryBlock* nxt=cur->next;
            if(cur->size==0){
                perv->next=nxt;
                cur=nxt;
            }
            else{
                perv=cur;
                cur=nxt;
            }
        }
        head=dummy->next;
    }



    memoryBlock* allocate(int size) {
        memoryBlock* cur=head;
        while(cur){
            if(cur->size>=size){
                memoryBlock* newBlock = new memoryBlock(cur->address, size);
                cur->address+=size;
                cur->size-=size;
                clearUp();
                return newBlock;
            }
            cur=cur->next;
        }
        return NULL;
    }
    void freeMemory(memoryBlock* block) {
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
    firstFit ff=firstFit(1000);
    ff.printMemory();
    memoryBlock* block1=ff.allocate(100);
    ff.printMemory();
    memoryBlock* block2=ff.allocate(200);
    ff.printMemory();
    memoryBlock* block3=ff.allocate(50);
    ff.printMemory();
    memoryBlock* block4=ff.allocate(300);
    ff.printMemory();
    
    ff.freeMemory(block1);
    ff.freeMemory(block3);
    ff.printMemory();

    memoryBlock* block5=ff.allocate(49);
    ff.printMemory();

    
    return 0;
}