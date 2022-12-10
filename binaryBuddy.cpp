#include "bits/stdc++.h"
using namespace std;

struct memoryBlock {
    int index;
    int size;
    int start;
    int end;
    bool isFree;
    int memoryLeft;
};

class binaryBuddy{
    public:
    
    vector<shared_ptr<memoryBlock>> tree;
    
    binaryBuddy(int size){
        tree.resize(2*size-1);
        buildTree(size,0,0);
    }

    shared_ptr<memoryBlock> allocate(int size){
        int inputSize=1;
        while(inputSize<size){
            inputSize=inputSize<<1;
        }
        int index=0;
        shared_ptr<memoryBlock> block=findMemoryBlock(inputSize,index);
        if(block==nullptr){
            return nullptr;
        }
        populateAllocate(block->index);
        return block;
    }

    void freeMemory(shared_ptr<memoryBlock> block){
        block->isFree=true;
        populateFree(block->index);
    }
    private:
    void populateFree(int index){
        tree[index]->isFree=true;
        tree[index]->memoryLeft=tree[index]->size;
        if(index==0){
            return;
        }
        
        if(index%2==0){
            if(tree[index-1]->isFree){
                int parentIndex=(index-1)/2;
                tree[parentIndex]->isFree=true;
                populateFree(parentIndex);
            }
        }
        else{
            if(tree[index+1]->isFree){
                int parentIndex=(index)/2;
                tree[parentIndex]->isFree=true;
                populateFree(parentIndex);
            }
        }
        
    }
    void populateAllocate(int index){
        if(index==0){
            return;
        }

        if(index%2==0){
            if(!tree[index-1]->isFree){
                int parentIndex=(index-1)/2;
                tree[parentIndex]->isFree=false;
                populateAllocate(parentIndex);
            }
        }
        else{
            if(!tree[index+1]->isFree){
                int parentIndex=(index)/2;
                tree[parentIndex]->isFree=false;
                populateAllocate(parentIndex);
            }
        }
    }
    shared_ptr<memoryBlock> findMemoryBlock(int size,int index){
        if(tree[index]->size<size){
            return nullptr;
        }
        tree[index]->memoryLeft-=size;
        if(tree[index]->size == size){
            tree[index]->isFree=false;
            return tree[index];
        }
        if(tree[index]->size>size){
            if(tree[2*index+1]->isFree && tree[2*index+1]->memoryLeft>=size){
                return findMemoryBlock(size,2*index+1);
            }
            else if(tree[2*index+2]->isFree && tree[2*index+2]->memoryLeft>=size){
                return findMemoryBlock(size,2*index+2);
            }
            else{
                return nullptr;
            }
        }
    }


    void buildTree(int size,int index,int start){
        auto memory=make_shared<memoryBlock>();
        memory->index=index;
        memory->size=size;
        memory->start=start;
        memory->end=start+size-1;
        memory->isFree=true;
        memory->memoryLeft=size;
        tree[index]=memory;

        if(size==4){
            return;
        }
        buildTree(size/2,2*index+1,start);
        buildTree(size/2,2*index+2,start+size/2);
    }

};





int main(){
    binaryBuddy buddy(64);
    cout<<buddy.tree.size()<<endl;
    
    auto block1=buddy.allocate(5);
    cout<<block1->start<<" "<<block1->end<<endl;
    auto block2=buddy.allocate(16);
    cout<<block2->start<<" "<<block2->end<<endl;
    auto block3=buddy.allocate(32);
    cout<<block3->start<<" "<<block3->end<<endl;

    for(auto& i:buddy.tree){
        if(i==nullptr){
            break;
        }
        cout<<i->index<<" "<<i->size<<" "<<i->start<<" "<<i->end<<" "<<i->isFree<<" "<<i->memoryLeft<<endl;
    }

    // cout<<"=========================="<<endl;

    // buddy.freeMemory(block1);
    // buddy.freeMemory(block2);
    // buddy.freeMemory(block3);
    // for(auto& i:buddy.tree){
    //     if(i==nullptr){
    //         break;
    //     }
    //     cout<<i->index<<" "<<i->size<<" "<<i->start<<" "<<i->end<<" "<<i->isFree<<" "<<i->memoryLeft<<endl;
    // }
    return 0;
}