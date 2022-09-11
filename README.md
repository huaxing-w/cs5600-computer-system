# Questions  
### 1. Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
CPU utilization should be 100%.  
We have two processes, pid0 and pid1, each will 100% use cpu, so cpu will run pid0 first and then pid1, the utilization will be 100%, cpu will not be idle.  
![q1](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q1.png)  
<br/>

### 2. Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p to find out if you were right.  
The total time to finish both processes is 11.  
The first process does not have IO, which takes 4 time intervals.  
The second process has 1 instruction and takes 5 time intervals (default value) to finish the IO, another two time intervals to run IO and finish IO.  
The total time would be 4+1+5+1=11.  
![q2](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q2.png)  
<br/>

### 3. Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)  
The running time becomes to 7.  
 We start to run IO process first, and while pid0 is waiting for finish, pid1 start to run, cpu does not have to wait for IO process. Efficiency gets increased.  
![q3](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q3.png)  
<br/>

### 4. We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH_ON_END), one doing I/O and the other doing CPU work?  
CPU will first run the IO process and wait until it finished, and then start to run the second one.  
Since switch is off, so we will have to wait until the first one finished.  
![q4](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q4.png)  
<br/>

### 5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH_ON_IO). What happens now? Use -c and -p to confirm that you are right.  
CPU will schedule the two process so that when the IO process is running, it starts to run the other one to increase the efficiency so that we do not have to wait unit the IO process finished.  
CPU switch to the second process when it find the first one is under IO work.  
![q5](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q5.png)  
<br/>

### 6. One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p) Are system resources being effectively utilized?  
No, it is not being effectively utilized.  
When CPU starts to run the first IO process, while it is waiting, the other process is being runnning.  
However, after the first IO process finished, we need to run all rest of the non-IO process first, and then start to run the IO process.  
Since we have 3 IO processes, first one is being used effectively, the rest two are not, cpu is idle and waiting IO to finish.  
![q6](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q6.png)  
<br/>


### 7. Now run the same processes, but with -I IO_RUN_IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?  
This is better than the last one, since we start to run another IO process right away, while it's waiting, CPU could run the non IO process, which increase the efficiency.  
![q7](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q7.png)  
<br/>

### 8. Now run with some randomly generated processes: -s 1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50,3:50. See if you can predict how the trace will turn out. What happens when you use the flag -I IO_RUN_IMMEDIATE vs. -I IO_RUN_LATER? What happens when you use -S SWITCH_ON_IO vs. -S SWITCH_ON_END?  
When we run -s 1 -l 3:50,3:50, pid0 will have 2 IO work, 1 regular work, pid1 will have 1 IO work and 2 regular work.  
![q81](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q81.png)  
<br/>
When we run -s 2 -l 3:50,3:50, pid0 will have 2 IO work, 1 regular work, pid1 will have 2 IO work and 1 regular work.  
![q82](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q82.png)  
<br/>
result for flag -I IO_RUN_IMMEDIATE  
![q83](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q83.png)  
<br/>
result for flag -I IO_RUN_LATER
![q84](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q84.png)  
<br/>
result for flag -S SWITCH_ON_IO
![q85](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q85.png)  
<br/>
result for flag -S SWITCH_ON_END
![q86](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q86.png)  
<br/>










