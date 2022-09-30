#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(10*sizeof(int));
    int i;
    for(i=0;i<10;i++){
        nums[i]=100;
    }
    for(i=0;i<10;i++){
        printf("this is %d\n",nums[i]);
    }
    free(nums);
    i=0;
    for(i=0;i<10;i++){
        printf("this is %d\n",nums[i]);
    }

    return 0;
}