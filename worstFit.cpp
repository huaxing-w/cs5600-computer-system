#include "bits/stdc++.h"
using namespace std;

struct memoryBlock{
    int address;
    int size;
    memoryBlock* next;
    memoryBlock(int add,int s):address(add),size(s),next(nullptr){}
};

class worstFit{
    public:
    memoryBlock* head;
    worstFit(int s){
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
        int diff=0;
        while(cur){
            if(cur->size>=size && diff<(cur->size-size)){
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
    worstFit wf=worstFit(1000);
    wf.printMemory();
    memoryBlock* block1=wf.allocate(100);
    wf.printMemory();
    memoryBlock* block2=wf.allocate(200);
    wf.printMemory();
    memoryBlock* block3=wf.allocate(50);
    wf.printMemory();
    memoryBlock* block4=wf.allocate(300);
    wf.printMemory();
    
    wf.freeMemory(block1);
    wf.freeMemory(block3);

    wf.printMemory();

    memoryBlock* block5=wf.allocate(49);
    wf.printMemory();

    

    return 0;
}


