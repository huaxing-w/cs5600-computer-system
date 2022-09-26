# Design Multi-Level Feedback Queue

### 1.  MLFQ principal
```
Rule 1: If Priority(A) > Priority(B), A runs (B doesn’t).
Rule 2: If Priority(A) = Priority(B), A & B run in round-robin fashion using the time slice (quantum length) of the given queue.
Rule 3: When a job enters the system, it is placed at the highest
priority (the topmost queue).
Rule 4: Once a job uses up its time allotment at a given level (regardless of how many times it has given up the CPU), its priority is
reduced (i.e., it moves down one queue).
Rule 5: After some time period S, move all the jobs in the system
to the topmost queue.
```  

### 2. UML
![uml](image.jpg)













