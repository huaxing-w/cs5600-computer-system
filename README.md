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
