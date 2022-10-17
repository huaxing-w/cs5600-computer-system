#include "bits/stdc++.h"
using namespace std;

struct memoryBlock{
    int address;
    int size;
    memoryBlock* next;
    memoryBlock(int add,int s):address(add),size(s),next(nullptr){}
};


class bestFit{
    public:
    memoryBlock* head;
    bestFit(int s){
        head=new memoryBlock(0,s);
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

    memoryBlock* allocate(int size){
        memoryBlock* cur=head;
        memoryBlock* selectedMemory=nullptr;
        int diff=1e9;
        while(cur){
            if(cur->size>=size && diff>(cur->size-size)){
                selectedMemory=cur;
                diff=cur->size-size;
            }
            cur=cur->next;
        }
        if(selectedMemory){
            memoryBlock* newBlock=new memoryBlock(selectedMemory->address,size);
            selectedMemory->address+=size;
            selectedMemory->size-=size;
            clearUp();
            return newBlock;
        }
        return nullptr;
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

    void freeMemory(memoryBlock* block) {
        block->next=head;
        head=block;
        sortMemory();
        mergeMemory();

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
    bestFit bf=bestFit(100);
    bf.printMemory();
    memoryBlock* block1=bf.allocate(5);
    bf.printMemory();
    memoryBlock* block2=bf.allocate(18);
    bf.printMemory();
    memoryBlock* block3=bf.allocate(26);
    bf.printMemory();
    memoryBlock* block4=bf.allocate(4);
    bf.printMemory();
    memoryBlock* block5=bf.allocate(7);
    bf.printMemory();
    memoryBlock* block6=bf.allocate(2);
    bf.printMemory();



    bf.freeMemory(block2);
    bf.printMemory();
    bf.freeMemory(block4);
    bf.printMemory();

    memoryBlock* block7=bf.allocate(4);
    bf.printMemory();
    memoryBlock* block8=bf.allocate(18);
    bf.printMemory();
    

    return 0;
}