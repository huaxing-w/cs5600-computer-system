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


