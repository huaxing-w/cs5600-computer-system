#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int runningTime=atoi(argv[2]);
    printf("the running time is %d\n",runningTime);
    //convert the input int to bytes
    int memory=atoi(argv[1])*1024*1024;
    int* nums=(int*)malloc(memory);
    int n= (int) (memory/sizeof(int));
    int i;
    clock_t start = clock();
    for(i=0;i<n;i++){
        printf("this is %d\n",i);
        clock_t end=clock();
        if((double)(end-start)/CLOCKS_PER_SEC > runningTime){
            printf("time's up\n");
            break;
        }
    }
    free(nums);
    return 0;
}