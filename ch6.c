#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>

int main(int argc,char* argv[]){
    printf("Hello, this is to test system call time\n");
    printf("***************************************\n");

    int f = open("./ch6.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    int i=0;
    for(i=0;i<1000000;i++){
        //write(f, "hello world!\n", strlen("hello world!\n"));
        write(f, NULL, 0);
    }
    gettimeofday(&end, NULL);
    printf("system call time cost is : %f microseconds\n", (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / 1000000);
    
    printf("\n");
    printf("Hello, this is to test contect switch time\n");
    printf("***************************************\n");

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    int p1[2];
    int p2[2];

    if(pipe(p1)<0){
        fprintf(stderr, "pipe creation failed\n");
        exit(1);
    }
    if(pipe(p2)<0){
        fprintf(stderr, "pipe creation failed\n");
        exit(1);
    }

    int pid1=fork();
    if (pid1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if(pid1==0){
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            fprintf(stderr, "set single cpu failed\n");
            exit(1);
        }
        i=0;
        for (i = 0; i < 1000000; i++) {
            read(p1[0], NULL, 0);
            write(p2[1], NULL, 0);
        }
    }
    if(pid1>0){
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            fprintf(stderr, "set single cpu failed\n");
            exit(1);
        }
        i=0;

        gettimeofday(&start, NULL);
        
        for (i = 0; i < 1000000; i++) {
            write(p1[1], NULL, 0);
            read(p2[0], NULL, 0);
        }
        gettimeofday(&end, NULL);
        printf("context switch time cost is : %f microseconds\n", (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / 1000000);


    }

    return 0;


}