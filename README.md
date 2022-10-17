# Homework (Simulation)

### 1.  Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags: -P 1k -a 1m -p 512m -v -n 0 -P 1k -a 2m -p 512m -v -n 0 -P 1k -a 4m -p 512m -v -n 0 Then, to understand how linear page table size changes as page size grows: -P 1k -a 1m -p 512m -v -n 0 -P 2k -a 1m -p 512m -v -n 0 -P 4k -a 1m -p 512m -v -n 0 Before running any of these, try to think about the expected trends. How should page-table size change as the address space grows? As the page size grows? Why not use big pages in general?

```
page table size is address space size / page size  
if we use a big page size, say 1G, and we just want to allocate 3kb memory, then we will have to give user 1G page, and most of the memory is wasted.  
```






### 2.  Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example: -P 1k -a 16k -p 32k -v -u 0 -P 1k -a 16k -p 32k -v -u 25 -P 1k -a 16k -p 32k -v -u 50 -P 1k -a 16k -p 32k -v -u 75 -P 1k -a 16k -p 32k -v -u 100 What happens as you increase the percentage of pages that are allocated in each address space?
```
more and more page are valid right now. 

```




### 3.   Now let’s try some different random seeds, and some different (and sometimes quite crazy) address-space parameters, for variety: -P 8 -a 32 -p 1024 -v -s 1 -P 8k -a 32k -p 1m -v -s 2 -P 1m -a 256m -p 512m -v -s 3 Which of these parameter combinations are unrealistic? Why?

```
the first one, page size is 8, address is 32, physical is 1024, they are too small.
similiarly, the third one, too big.


```
### 4.  Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?
```
set address space, or physical to 0.  
set physical < address space. 
set address space % page size !=0.  
```

# Homework (Measurement)

### 1.  For timing, you’ll need to use a timer (e.g., gettimeofday()). How precise is such a timer? How long does an operation have to take in order for you to time it precisely? (this will help determine how many times, in a loop, you’ll have to repeat a page access in order to time it successfully)

```
gettimeofday() has two members

struct timeval  {
  time_t tv_sec ;   
  suseconds_t tv_usec ;   
};

tv_sec is seconds.
tv_usec is microseconds.

```

```
clock_gettime also has two members

struct timespec {
  time_t tv_sec;    
  long tv_nsec;      
};

tv_sec is to the seconds.
tv_nsec is to the nanoseconds

hence, we will be using clock_gettime as it is more precise.

```

### 2.  Write the program, called tlb.c, that can roughly measure the cost of accessing each page. Inputs to the program should be: the number of pages to touch and the number of trials.
```c
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
```
### 3.  Now write a script in your favorite scripting language (bash?) to run this program, while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration. Run the script on different machines and gather some data. How many trials are needed to get reliable measurements?
```
use python to do this work.

10000 trials should be good enough.
```


