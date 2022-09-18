#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    printf("hello, I am parent pid:%d\n",(int)getpid());
    int f = open("ch5-q2.txt", O_RDWR | O_CREAT | O_EXCL,S_IRWXU);
    int rc=fork();
    if(rc<0){
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if(rc==0){
        if (f < 0) { 
            fprintf(stderr, "file open failed\n");
            exit(1);
        }
        printf("hello, I am child pid:%d, I am writing to the file\n",(int)getpid()); 
        write(f, "this is from child process\n", strlen("this is from child process\n"));   
    }
    if(rc>0){
        if (f < 0) { 
            fprintf(stderr, "file open failed\n");
            exit(1);
        }
        printf("hello, I am parent pid:%d,I am writing to the file\n",(int)getpid()); 
        write(f, "this is from parent process\n", strlen("this is from parent process\n"));
        
    }
    close(f);
    return 0;
}