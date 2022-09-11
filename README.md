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
CPU will first run the IO process and wait unit it finished, and then start to run the second one.  
![q4](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q4.png)  
<br/>








