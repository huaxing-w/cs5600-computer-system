# evaluation
```
use the same memory allocation case to run three different policies.
Assume we have a free memory block starting from address 0, size of 1000.

we will allocation 4 block of memory, size of 100,200,50,300.
now the free list should be [address:650 size:350] as the first 650 has been allocated.

if we free the block of 100, and 50

we will see the free list as this
[address:0 size:100]->[address:300 size:50]->[address:650 size:350]

the implementation I have here when freeing the memory is that,I will put the freed memory into the front of the list, and then sort the free list based on its address, then check if there are some memory blocks are there can be merged.

Here comes to the difference when using different policy.

now if when want to allocate another 49 size of memory.

for the worstFit policy, it will allocate the memory block at 650, the free list looks like this:
[address:0 size:100]->[address:300 size:50]->[address:699 size:301]

for the firstFit policy, it will allocate the memory block at 0, the free list looks like this:
[address:49 size:51]->[address:300 size:50]->[address:650 size:350]

for the bestFit policy, it will allocate the memory block at 300, the free list looks like this:
[address:0 size:100]->[address:349 size:1]->[address:650 size:350]

```
|             |        Best Fit        |
| ----------- | -----------------------|
| pros        | reduce space waste     |
| cons        | it takes O(n) to search the best block      |





# firstFit
```
1. use linked list to implement memory management policy.
2. when allocate new memory block, use the first available free memory block.
3. when free memory block, insert the the freed memory block to the head of the linked list.
4. after inserting, sort the linked list based on the address and merge the memory block if they are continuious.
```

# bestFit
```
1. use linked list to implement memory management policy.
2. search through the free list and find chunks that are bigger than the requested one.
3. return the one that is the smallest in that group of candidates
```

# worstFit
```
1. use linked list to implement memory management policy.
2. search through the free list and find chunks that are bigger than the requested one.
3. return the one that is the biggest free chunk in the free list
```

# nextFit
```
1. use linked list to implement memory management policy.
2. create an extra pointer to the location to memorize the last search point
3. next search will start from the extra pointer location to spread the search scope.
```
# binaryBuddy

```
Assumption:
1. the tree is full tree.
2. internal fragmentation is allowed.
3. the min memory block is 4.
4. the segment tree starts from 0, the left child is 2*i+1, the right child is 2*i+2.
5. find and free memory block recursively.
6. if index is odd, check the next even index, if it is free. if it is even, check the pervious odd index if it is free. If both are free, recursively push up the free info.

              64
          /       \
        32         32
      /    \     /    \
     16    16   16     16
    /  \
  ...   ...

```

# segregatedList
```
1. on the top of firstfit policy system, we add another hashtop to track popular memoryblock.
2. in our case, let assume it is 10, 20, 30 and starting at 0, 10, 30 address.
3. when requesting new block, we first check if it is the popular size, if it is the, return the block from the hashtable.
4. when freeing the block, we check if it is the popular used size, if it is we release it to the hashtable.
```