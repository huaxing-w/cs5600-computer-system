#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){
        printf("I am child process pid:%d\n",(int)getpid());

    }
    if (rc > 0){
        int wc=wait(NULL);
        printf("I am parent process pid:%d, wc value is %d\n",(int)getpid(),wc);

    }
    return 0;
}