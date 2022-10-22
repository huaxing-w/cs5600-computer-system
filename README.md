# Homework (Simulation)

### 1.  With a linear page table, you need a single register to locate the page table, assuming that hardware does the lookup upon a TLB miss. How many registers do you need to locate a two-level page table? A three-level table?
```
same, just one top level page directory. 
```

### 2.  Use the simulator to perform translations given random seeds 0, 1, and 2, and check your answers using the -c flag. How many memory references are needed to perform each lookup?

```
3

virtual address 0x611c is 11000 01000 11100
11000 
 24     
 PDE   
       01000 
        8
       PTE   
             11100
             offset
```




### 3.   Given your understanding of how cache memory works, how do you think memory references to the page table will behave in the cache? Will they lead to lots of cache hits (and thus fast accesses?) Or lots of misses (and thus slow accesses)?

```
upon a hit, the physical address is formed directly without accessing the page
table at all, as before. Only upon a TLB miss does the hardware need to
perform the full multi-level lookup. On this path, you can see the cost of
our traditional two-level page table: two additional memory accesses to
look up a valid translation.

so it is faster.

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
        printf("error: ");                                                      \
        perror(msg);                                                            \
        exit(0);                                                                \
    } while (0)

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("wrong agrc number\n");
        exit(0);
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
        fprintf(stderr, "please check input again\n");
        exit(0);
    }
    int *nums = (int*)calloc(pages, PAGESIZE);
    struct timespec start;
    struct timespec end;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1){
        handle_error("clock_gettime");
    }
        

    for (int j = 0; j < trials; j++) {
        for (int i = 0; i < pages*jump; i += jump){
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

### 4.  Next, graph the results, making a graph that looks similar to the one above. Use a good tool like ploticus or even zplot. Visualization usually makes the data much easier to digest; why do you think that is?

![q4](https://github.com/huaxing-w/cs5600-computer-system/blob/homework6/q4.png)


### 5.  One thing to watch out for is compiler optimization. Compilers do all sorts of clever things, including removing loops which increment values that no other part of the program subsequently uses. How can you ensure the compiler does not remove the main loop above from your TLB size estimator?
```
disable the optimization function.

```

### 6.  Another thing to watch out for is the fact that most systems today ship with multiple CPUs, and each CPU, of course, has its own TLB hierarchy. To really get good measurements, you have to run your code on just one CPU, instead of letting the scheduler bounce it from one CPU to the next. How can you do that? (hint: look up “pinning a thread” on Google for some clues) What will happen if you don’t do this, and the code moves from one CPU to the other?
```
for windows user, set process affinity

start /affinity 1 tlb2.exe 
```

### 7.  Another issue that might arise relates to initialization. If you don’t initialize the array a above before accessing it, the first time you access it will be very expensive, due to initial access costs such as demand zeroing. Will this affect your code and its timing? What can you do to counterbalance these potential costs?
```
use calloc instead of malloc
```



