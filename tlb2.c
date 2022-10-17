#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   
#include <unistd.h> 
#include <windows.h>

#define handle_error(msg)                                                       \
    do {                                                                        \
        perror(msg);                                                            \
        exit(EXIT_FAILURE);                                                     \
    } while (0)

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s pages trials\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    //for the windows user use system_info to get the page size
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    long PAGESIZE = si.dwPageSize;

    long jump = PAGESIZE / sizeof(int);    // 4096/4 = 1024
    // the page input
    int pages = atoi(argv[1]);
    // the number of trials
    int trials = atoi(argv[2]);
    if (pages <= 0 || trials <= 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    int *nums = (int*)calloc(pages, PAGESIZE);
    struct timespec start, end;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1){
        handle_error("clock_gettime");
    }
        

    for (int j = 0; j < trials; j++) {
        for (int i = 0; i < pages * jump; i += jump){
            nums[i] += 1;
        }
    }

    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) == -1){
        handle_error("clock_gettime");
    }
        

    printf("%f\n",((end.tv_sec - start.tv_sec) * 1e9+end.tv_nsec-start.tv_nsec)/(trials * pages));
    free(nums);
    return 0;
}