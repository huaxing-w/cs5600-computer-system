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

### 5.  What fraction of randomly-generated virtual addresses are valid, as a function of the value of the bounds register? Make a graph from running with different random seeds, with limit values ranging from 0 up to the maximum size of the address space.
![q5](https://github.com/huaxing-w/cs5600-computer-system/blob/homework5/q5.png)


