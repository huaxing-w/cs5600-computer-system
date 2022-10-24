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
only tlb miss will perform the lookup, so it is faster.


```



# Homework (Measurement)

### 1.  First, open two separate terminal connections to the same machine, so that you can easily run something in one window and the other. Now, in one window, run vmstat 1, which shows statistics about machine usage every second. Read the man page, the associated README, and any other information you need so that you can understand its output. Leave this window running vmstat for the rest of the exercises below. Now, we will run the program mem.c but with very little memory usage. This can be accomplished by typing ./mem 1 (which uses only 1 MB of memory). How do the CPU usage statistics change when running mem? Do the numbers in the user time column make sense? How does this change when running more than one instance of mem at once?


```
https://phoenixnap.com/kb/vmstat-command#:~:text=The%20vmstat%20command%20(short%20for,by%20specifying%20a%20sampling%20period.

vmstat man

us user time col increase
id idle time decrease

if you run more than two mem.c, the user time will X2.
```

### 2.  Let’s now start looking at some of the memory statistics while running mem. We’ll focus on two columns: swpd (the amount of virtual memory used) and free (the amount of idle memory). Run ./mem 1024 (which allocates 1024 MB) and watch how these values change. Then kill the running program (by typing control-c) and watch again how the values change. What do you notice about the values? In particular, how does the free column change when the program exits? Does the amount of free memory increase by the expected amount when mem exits?

```
when we start to run mem 1024, the free col increased
when we stop the mem, the free col decreased.

```
### 3.  We’ll next look at the swap columns (si and so), which indicate how much swapping is taking place to and from the disk. Of course, to activate these, you’ll need to run mem with large amounts of memory. First, examine how much free memory is on your Linux system (for example, by typing cat /proc/meminfo; type man proc for details on the /proc file system and the types of information you can find there). One of the first entries in /proc/meminfo is the total amount of memory in your system. Let’s assume it’s something like 8 GB of memory; if so, start by running mem 4000 (about 4 GB) and watching the swap in/out columns. Do they ever give non-zero values? Then, try with 5000, 6000, etc. What happens to these values as the program enters the second loop (and beyond), as compared to the first loop? How much data (total) are swapped in and out during the second, third, and subsequent loops? (do the numbers make sense?)
```
khoury server has too much memory, it's hardly to see the non-zero si and so

but swap should be increase in the first loop, and then decrease in the second.

```

### 4.  Do the same experiments as above, but now watch the other statistics (such as CPU utilization, and block I/O statistics). How do they change when mem is running?
```
user time increased.
bo increased.
```

### 5.  Now let’s examine performance. Pick an input for mem that comfortably fits in memory (say 4000 if the amount of memory on the system is 8 GB). How long does loop 0 take (and subsequent loops 1, 2, etc.)? Now pick a size comfortably beyond the size of memory (say 12000 again assuming 8 GB of memory). How long do the loops take here? How do the bandwidth numbers compare? How different is performance when constantly swapping versus fitting everything comfortably in memory? Can you make a graph, with the size of memory used by mem on the x-axis, and the bandwidth of accessing said memory on the y-axis? Finally, how does the performance of the first loop compare to that of subsequent loops, for both the case where everything fits in memory and where it doesn’t?
![q5](https://github.com/huaxing-w/cs5600-computer-system/blob/homework7/q5.png)
khoury server has 300G memory, it is not good idea to do this homework with school's server.
```
the first loop is smaller, the rest of the loop is bigger.
```
### 6.  Swap space isn’t infinite. You can use the tool swapon with the -s flag to see how much swap space is available. What happens if you try to run mem with increasingly large values, beyond what seems to be available in swap? At what point does the memory allocation fail?

```
near the max of the memory.
```

### 7.  Finally, if you’re advanced, you can configure your system to use different swap devices using swapon and swapoff. Read the man pages for details. If you have access to different hardware, see how the performance of swapping changes when swapping to a classic hard drive, a flash-based SSD, and even a RAID array. How much can swapping performance be improved via newer devices? How close can you get to in-memory performance?

```
can not do this on Khoury server.
```

# Homework (Simulation)

### 1.  Generate random addresses with the following arguments: -s 0 -n 10, -s 1 -n 10, and -s 2 -n 10. Change the policy from FIFO, to LRU, to OPT. Compute whether each access in said address traces are hits or misses.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py -s 0 -n 10 -c              
ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 8  MISS FirstIn ->          [8] <- Lastin  Replaced:- [Hits:0 Misses:1]
Access: 7  MISS FirstIn ->       [8, 7] <- Lastin  Replaced:- [Hits:0 Misses:2]
Access: 4  MISS FirstIn ->    [8, 7, 4] <- Lastin  Replaced:- [Hits:0 Misses:3]
Access: 2  MISS FirstIn ->    [7, 4, 2] <- Lastin  Replaced:8 [Hits:0 Misses:4]
Access: 5  MISS FirstIn ->    [4, 2, 5] <- Lastin  Replaced:7 [Hits:0 Misses:5]
Access: 4  HIT  FirstIn ->    [4, 2, 5] <- Lastin  Replaced:- [Hits:1 Misses:5]
Access: 7  MISS FirstIn ->    [2, 5, 7] <- Lastin  Replaced:4 [Hits:1 Misses:6]
Access: 3  MISS FirstIn ->    [5, 7, 3] <- Lastin  Replaced:2 [Hits:1 Misses:7]
Access: 4  MISS FirstIn ->    [7, 3, 4] <- Lastin  Replaced:5 [Hits:1 Misses:8]
Access: 5  MISS FirstIn ->    [3, 4, 5] <- Lastin  Replaced:7 [Hits:1 Misses:9]

FINALSTATS hits 1   misses 9   hitrate 10.00



PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py -s 0 -n 10 -c --policy=LRU
ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 8  MISS LRU ->          [8] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 7  MISS LRU ->       [8, 7] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 4  MISS LRU ->    [8, 7, 4] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 2  MISS LRU ->    [7, 4, 2] <- MRU Replaced:8 [Hits:0 Misses:4]
Access: 5  MISS LRU ->    [4, 2, 5] <- MRU Replaced:7 [Hits:0 Misses:5]
Access: 4  HIT  LRU ->    [2, 5, 4] <- MRU Replaced:- [Hits:1 Misses:5]
Access: 7  MISS LRU ->    [5, 4, 7] <- MRU Replaced:2 [Hits:1 Misses:6]
Access: 3  MISS LRU ->    [4, 7, 3] <- MRU Replaced:5 [Hits:1 Misses:7]
Access: 4  HIT  LRU ->    [7, 3, 4] <- MRU Replaced:- [Hits:2 Misses:7]
Access: 5  MISS LRU ->    [3, 4, 5] <- MRU Replaced:7 [Hits:2 Misses:8]

FINALSTATS hits 2   misses 8   hitrate 20.00


PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py -s 0 -n 10 -c --policy=OPT
ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy OPT
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 8  MISS Left  ->          [8] <- Right Replaced:- [Hits:0 Misses:1]
Access: 7  MISS Left  ->       [8, 7] <- Right Replaced:- [Hits:0 Misses:2]
Access: 4  MISS Left  ->    [8, 7, 4] <- Right Replaced:- [Hits:0 Misses:3]
Access: 2  MISS Left  ->    [7, 4, 2] <- Right Replaced:8 [Hits:0 Misses:4]
Access: 5  MISS Left  ->    [7, 4, 5] <- Right Replaced:2 [Hits:0 Misses:5]
Access: 4  HIT  Left  ->    [7, 4, 5] <- Right Replaced:- [Hits:1 Misses:5]
Access: 7  HIT  Left  ->    [7, 4, 5] <- Right Replaced:- [Hits:2 Misses:5]
Access: 3  MISS Left  ->    [4, 5, 3] <- Right Replaced:7 [Hits:2 Misses:6]
Access: 4  HIT  Left  ->    [4, 5, 3] <- Right Replaced:- [Hits:3 Misses:6]
Access: 5  HIT  Left  ->    [4, 5, 3] <- Right Replaced:- [Hits:4 Misses:6]

FINALSTATS hits 4   misses 6   hitrate 40.00

```
### 2.   For a cache of size 5, generate worst-case address reference streams for each of the following policies: FIFO, LRU, and MRU (worst-case reference streams cause the most misses possible. For the worst case reference streams, how much bigger of a cache is needed to improve performance dramatically and approach OPT?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=FIFO --cachesize=5 -c
ARG addresses 0,1,2,3,4,5,0,1,2,3,4,5
ARG addressfile 
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 5
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 0  MISS FirstIn ->          [0] <- Lastin  Replaced:- [Hits:0 Misses:1]
Access: 1  MISS FirstIn ->       [0, 1] <- Lastin  Replaced:- [Hits:0 Misses:2]
Access: 2  MISS FirstIn ->    [0, 1, 2] <- Lastin  Replaced:- [Hits:0 Misses:3]
Access: 3  MISS FirstIn -> [0, 1, 2, 3] <- Lastin  Replaced:- [Hits:0 Misses:4]
Access: 4  MISS FirstIn -> [0, 1, 2, 3, 4] <- Lastin  Replaced:- [Hits:0 Misses:5]
Access: 5  MISS FirstIn -> [1, 2, 3, 4, 5] <- Lastin  Replaced:0 [Hits:0 Misses:6]
Access: 0  MISS FirstIn -> [2, 3, 4, 5, 0] <- Lastin  Replaced:1 [Hits:0 Misses:7]
Access: 1  MISS FirstIn -> [3, 4, 5, 0, 1] <- Lastin  Replaced:2 [Hits:0 Misses:8]
Access: 2  MISS FirstIn -> [4, 5, 0, 1, 2] <- Lastin  Replaced:3 [Hits:0 Misses:9]
Access: 3  MISS FirstIn -> [5, 0, 1, 2, 3] <- Lastin  Replaced:4 [Hits:0 Misses:10]
Access: 4  MISS FirstIn -> [0, 1, 2, 3, 4] <- Lastin  Replaced:5 [Hits:0 Misses:11]
Access: 5  MISS FirstIn -> [1, 2, 3, 4, 5] <- Lastin  Replaced:0 [Hits:0 Misses:12]

FINALSTATS hits 0   misses 12   hitrate 0.00


PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=LRU --cachesize=5 -c 
ARG addresses 0,1,2,3,4,5,0,1,2,3,4,5
ARG addressfile
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 5
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 0  MISS LRU ->          [0] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 1  MISS LRU ->       [0, 1] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 2  MISS LRU ->    [0, 1, 2] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 3  MISS LRU -> [0, 1, 2, 3] <- MRU Replaced:- [Hits:0 Misses:4]
Access: 4  MISS LRU -> [0, 1, 2, 3, 4] <- MRU Replaced:- [Hits:0 Misses:5]
Access: 5  MISS LRU -> [1, 2, 3, 4, 5] <- MRU Replaced:0 [Hits:0 Misses:6]
Access: 0  MISS LRU -> [2, 3, 4, 5, 0] <- MRU Replaced:1 [Hits:0 Misses:7]
Access: 1  MISS LRU -> [3, 4, 5, 0, 1] <- MRU Replaced:2 [Hits:0 Misses:8]
Access: 2  MISS LRU -> [4, 5, 0, 1, 2] <- MRU Replaced:3 [Hits:0 Misses:9]
Access: 3  MISS LRU -> [5, 0, 1, 2, 3] <- MRU Replaced:4 [Hits:0 Misses:10]
Access: 4  MISS LRU -> [0, 1, 2, 3, 4] <- MRU Replaced:5 [Hits:0 Misses:11]
Access: 5  MISS LRU -> [1, 2, 3, 4, 5] <- MRU Replaced:0 [Hits:0 Misses:12]

FINALSTATS hits 0   misses 12   hitrate 0.00


PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=0,1,2,3,4,5,4,5,4,5,4,5 --policy=MRU --cachesize=5 -c
ARG addresses 0,1,2,3,4,5,4,5,4,5,4,5
ARG addressfile
ARG numaddrs 10
ARG policy MRU
ARG clockbits 2
ARG cachesize 5
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 0  MISS LRU ->          [0] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 1  MISS LRU ->       [0, 1] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 2  MISS LRU ->    [0, 1, 2] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 3  MISS LRU -> [0, 1, 2, 3] <- MRU Replaced:- [Hits:0 Misses:4]
Access: 4  MISS LRU -> [0, 1, 2, 3, 4] <- MRU Replaced:- [Hits:0 Misses:5]
Access: 5  MISS LRU -> [0, 1, 2, 3, 5] <- MRU Replaced:4 [Hits:0 Misses:6]
Access: 4  MISS LRU -> [0, 1, 2, 3, 4] <- MRU Replaced:5 [Hits:0 Misses:7]
Access: 5  MISS LRU -> [0, 1, 2, 3, 5] <- MRU Replaced:4 [Hits:0 Misses:8]
Access: 4  MISS LRU -> [0, 1, 2, 3, 4] <- MRU Replaced:5 [Hits:0 Misses:9]
Access: 5  MISS LRU -> [0, 1, 2, 3, 5] <- MRU Replaced:4 [Hits:0 Misses:10]
Access: 4  MISS LRU -> [0, 1, 2, 3, 4] <- MRU Replaced:5 [Hits:0 Misses:11]
Access: 5  MISS LRU -> [0, 1, 2, 3, 5] <- MRU Replaced:4 [Hits:0 Misses:12]

FINALSTATS hits 0   misses 12   hitrate 0.00

this need another one
```

### 3.   Generate a random trace (use python or perl). How would you expect the different policies to perform on such a trace?
```
opt should have the most hit rate, next is lru
```

### 4.   Now generate a trace with some locality. How can you generate such a trace? How does LRU perform on it? How much better than RAND is LRU? How does CLOCK do? How about CLOCK with different numbers of clock bits?
```
say [1,0,2,2,2,3,0,2,2]
--addresses=1,0,2,2,2,3,0,2,2 --policy=LRU -c
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=LRU -c                    
ARG addresses 1,0,2,2,2,3,0,2,2
ARG addressfile
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS LRU ->          [1] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 0  MISS LRU ->       [1, 0] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 2  MISS LRU ->    [1, 0, 2] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 2  HIT  LRU ->    [1, 0, 2] <- MRU Replaced:- [Hits:1 Misses:3]
Access: 2  HIT  LRU ->    [1, 0, 2] <- MRU Replaced:- [Hits:2 Misses:3]
Access: 3  MISS LRU ->    [0, 2, 3] <- MRU Replaced:1 [Hits:2 Misses:4]
Access: 0  HIT  LRU ->    [2, 3, 0] <- MRU Replaced:- [Hits:3 Misses:4]
Access: 2  HIT  LRU ->    [3, 0, 2] <- MRU Replaced:- [Hits:4 Misses:4]
Access: 2  HIT  LRU ->    [3, 0, 2] <- MRU Replaced:- [Hits:5 Misses:4]

FINALSTATS hits 5   misses 4   hitrate 55.56


python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=RAND -c   
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=RAND -c  
ARG addresses 1,0,2,2,2,3,0,2,2
ARG addressfile
ARG numaddrs 10
ARG policy RAND
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS Left  ->          [1] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [1, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 2  MISS Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:0 Misses:3]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:1 Misses:3]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:2 Misses:3]
Access: 3  MISS Left  ->    [1, 0, 3] <- Right Replaced:2 [Hits:2 Misses:4]
Access: 0  HIT  Left  ->    [1, 0, 3] <- Right Replaced:- [Hits:3 Misses:4]
Access: 2  MISS Left  ->    [1, 0, 2] <- Right Replaced:3 [Hits:3 Misses:5]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:4 Misses:5]

FINALSTATS hits 4   misses 5   hitrate 44.44


python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=CLOCK -c -b 0

PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=CLOCK -c -b 0
ARG addresses 1,0,2,2,2,3,0,2,2
ARG addressfile
ARG numaddrs 10
ARG policy CLOCK
ARG clockbits 0
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS Left  ->          [1] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [1, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 2  MISS Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:0 Misses:3]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:1 Misses:3]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:2 Misses:3]
Access: 3  MISS Left  ->    [1, 0, 3] <- Right Replaced:2 [Hits:2 Misses:4]
Access: 0  HIT  Left  ->    [1, 0, 3] <- Right Replaced:- [Hits:3 Misses:4]
Access: 2  MISS Left  ->    [1, 3, 2] <- Right Replaced:0 [Hits:3 Misses:5]
Access: 2  HIT  Left  ->    [1, 3, 2] <- Right Replaced:- [Hits:4 Misses:5]

FINALSTATS hits 4   misses 5   hitrate 44.44

python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=CLOCK -c -b 2
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\paging-policy.py --addresses=1,0,2,2,2,3,0,2,2 --policy=CLOCK -c -b 2
ARG addresses 1,0,2,2,2,3,0,2,2
ARG addressfile
ARG numaddrs 10
ARG policy CLOCK
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 1  MISS Left  ->          [1] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [1, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 2  MISS Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:0 Misses:3]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:1 Misses:3]
Access: 2  HIT  Left  ->    [1, 0, 2] <- Right Replaced:- [Hits:2 Misses:3]
Access: 3  MISS Left  ->    [1, 2, 3] <- Right Replaced:0 [Hits:2 Misses:4]
Access: 0  MISS Left  ->    [1, 3, 0] <- Right Replaced:2 [Hits:2 Misses:5]
Access: 2  MISS Left  ->    [3, 0, 2] <- Right Replaced:1 [Hits:2 Misses:6]
Access: 2  HIT  Left  ->    [3, 0, 2] <- Right Replaced:- [Hits:3 Misses:6]

FINALSTATS hits 3   misses 6   hitrate 33.33
```
### 5.   Now generate a trace with some locality. How can you generate such a trace? How does LRU perform on it? How much better than RAND is LRU? How does CLOCK do? How about CLOCK with different numbers of clock bits?

![q5](https://github.com/huaxing-w/cs5600-computer-system/blob/homework7/q55.png)
