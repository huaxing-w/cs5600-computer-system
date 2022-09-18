#include <stdio.h>
#include <unistd.h>
#define MSGSIZE 16

char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main(){
    char inbuf[MSGSIZE];
    int p[2];
    int pid1;
    int pid2;
    int nbytes;
    if(pipe(p)<0){
        fprintf(stderr, "pipe creation failed\n");
        exit(1);
    }
    pid1=fork();
    if (pid1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    
    if(pid1==0){
        close(p[0]);
        write(p[1],msg1,MSGSIZE);
        write(p[1],msg2,MSGSIZE);
        write(p[1],msg3,MSGSIZE);
        close(p[1]);
    }
    if(pid1>0){
        wait(NULL);
        pid2=fork();
        if(pid2==0){
            close(p[1]);
            while((nbytes = read(p[0], inbuf, MSGSIZE)) > 0){
                printf("%s\n",inbuf);
            }
            printf("finished!\n");
            close(p[0]);
        }
        
    }
    return 0;
}