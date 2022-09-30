#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(100*sizeof(int));
    nums[100]=0;
    free(nums);

    return 0;
}