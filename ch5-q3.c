#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int rc = fork();
    if(rc<0){
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if(rc==0){
        printf("hello!\n"); 
    }
    if(rc>0){
        //wait(NULL);
        sleep(1);
        printf("goodbye!\n");
    }
    return 0;
}