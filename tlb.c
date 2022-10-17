#include <stdio.h>  // printf, fprintf
#include <stdlib.h> // exit, calloc, free
#include <time.h>   // clock_gettime
#include <unistd.h> // sysconf

int main(){
    struct timeval time1;
    struct timeval time2;

    mingw_gettimeofday(&time1,NULL);
    sleep(2);
    mingw_gettimeofday(&time2,NULL);
    printf("time1: %ld, time2: %ld\n",time1.tv_usec,time2.tv_usec);

    

    return 0;
}

