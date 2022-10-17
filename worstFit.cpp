#include "bits/stdc++.h"
using namespace std;

struct memoryBlock{
    int address;
    int size;
    memoryBlock* next;
    memoryBlock(int add,int s):address(add),size(s),next(nullptr){}
};

