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

# firstFit
```
1. use linked list to implement memory management policy.
2. when allocate new memory block, use the first available free memory block.
3. when free memory block, insert the the freed memory block to the head of the linked list.
4. after inserting, sort the linked list based on the address and merge the memory block if they are continuious.
```

# segregatedList
```
1. on the top of firstfit policy system, we add another hashtop to track popular memoryblock.
2. in our case, let assume it is 10, 20, 30 and starting at 0, 10, 30 address.
3. when requesting new block, we first check if it is the popular size, if it is the, return the block from the hashtable.
4. when freeing the block, we check if it is the popular used size, if it is we release it to the hashtable.
```