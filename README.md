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
![uml](https://github.com/huaxing-w/cs5600-computer-system/blob/MLFQ/mlfq.png)


### 3. Design
- create class job, feedBackQueue and MLFQ as shown above.  
- when program runs, ask user how many jobs are there, how many level of feedbackqueue do they want to have.  
- ask user to set the boost time interval.  
- start to run the program and cout the current situation.  
- Inorder to increase the response time, when a job finishes the IO, send to the back of the queue.  
- After finished all the jobs, print the final result for each job.  











