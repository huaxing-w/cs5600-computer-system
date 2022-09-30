#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* num=(int*)malloc(sizeof(int));
    num=NULL;
    printf("this is %d\n",*num);
    free(num);
    return 0;
}