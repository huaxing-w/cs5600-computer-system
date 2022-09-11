# Questions  
## 1.Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.
CPU utilization should be 100%.  
We have two processes, pid0 and pid1, each will 100% use cpu, so cpu will run pid0 first and then pid1, the utilization will be 100%, cpu will not be idle.  
![q1](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q1.png)  


