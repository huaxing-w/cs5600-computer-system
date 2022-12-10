#include "bits/stdc++.h"
using namespace std;

struct memoryBlockL{
    int address;
    int size;
    memoryBlockL* next;
    memoryBlockL(int add,int s):address(add),size(s),next(nullptr){}
};


class bestFit{
    public:
    memoryBlockL* head;
    bestFit(int s){
        head=new memoryBlockL(0,s);
    }

    void clearUp(){
        memoryBlockL* dummy=new memoryBlockL(-1,-1);
        dummy->next=head;
        memoryBlockL* cur=head;
        memoryBlockL* perv=dummy;
        while(cur){
            memoryBlockL* nxt=cur->next;
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

    memoryBlockL* allocate(int size){
        memoryBlockL* cur=head;
        memoryBlockL* selectedMemory=nullptr;
        int diff=1e9;
        while(cur){
            if(cur->size>=size && diff>(cur->size-size)){
                selectedMemory=cur;
                diff=cur->size-size;
            }
            cur=cur->next;
        }
        if(selectedMemory){
            memoryBlockL* newBlock=new memoryBlockL(selectedMemory->address,size);
            selectedMemory->address+=size;
            selectedMemory->size-=size;
            clearUp();
            return newBlock;
        }
        return nullptr;
    }

    void printMemory() {
        memoryBlockL* cur=head;
        while(cur){
            cout<<"[address:"<<cur->address<<" size:"<<cur->size<<"]";
            if(cur->next) cout<<"->";
            cur=cur->next;
        }
        cout<<endl;
    }

    void freeMemory(memoryBlockL* block) {
        block->next=head;
        head=block;
        sortMemory();
        mergeMemory();

    }
    void mergeMemory(){
        memoryBlockL* dummy=new memoryBlockL(-1,-1);
        memoryBlockL* perv=dummy;
        memoryBlockL* cur=head;
        perv->next=cur;
        while(cur->next){
            memoryBlockL* next=cur->next;
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
        function<memoryBlockL*(memoryBlockL*,memoryBlockL*)>merge=[&](memoryBlockL* a, memoryBlockL* b){
            if(!a) return b;
            if(!b) return a;
            if(a->address<b->address){
                a->next=merge(a->next,b);
                return a;
            }
            b->next=merge(a,b->next);
            return b;
        };

        function<memoryBlockL*(memoryBlockL*,memoryBlockL*)>sortFunc=[&](memoryBlockL* head,memoryBlockL* tail)->memoryBlockL*{
            if(!head){
                return nullptr;
            }
            if(head->next==tail){
                head->next=nullptr;
                return head;
            }
            memoryBlockL* slow=head;
            memoryBlockL* fast=head;
            while(fast!=tail && fast->next!=tail){
                slow=slow->next;
                fast=fast->next->next;
            }
            memoryBlockL* mid=slow;
            return merge(sortFunc(head,mid),sortFunc(mid,tail));
        };
        head=sortFunc(head,NULL);
    }

};




int main(){
    bestFit bf=bestFit(1000);
    bf.printMemory();
    memoryBlockL* block1=bf.allocate(100);
    bf.printMemory();
    memoryBlockL* block2=bf.allocate(200);
    bf.printMemory();
    memoryBlockL* block3=bf.allocate(50);
    bf.printMemory();
    memoryBlockL* block4=bf.allocate(300);
    bf.printMemory();

    bf.freeMemory(block1);
    bf.freeMemory(block3);
    bf.printMemory();

    memoryBlockL* block5=bf.allocate(49);
    bf.printMemory();

    



    
    

    return 0;
}