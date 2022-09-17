#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    int num=100;
    printf("hello I am parent pid:%d, the num is %d\n",(int)getpid(),num);
    //create a fork
    int rc=fork();
    if(rc<0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    if(rc==0){
        num+=1;
        printf("hello, I am child pid:%d, the num is %d\n",(int)getpid(),num);
    }
    if(rc>0){
        num+=2;
        printf("hello I am parent pid:%d, the num is %d\n",(int)getpid(),num);
    }
    return 0;
}