#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(10*sizeof(int));
    int i;
    for(i=0;i<10;i++){
        nums[i]=i;
    }
    nums=(int*)realloc(nums,20*sizeof(int));
    for(;i<20;i++){
        nums[i]=i;
    }
    int j;
    for(j=0;j<20;j++){
        printf("this is %d\n",nums[j]);
    }
    return 0;
}