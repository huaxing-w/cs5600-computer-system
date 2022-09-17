# Homework(Simulation)  
### Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.

![q1](https://github.com/huaxing-w/cs5600-computer-system/blob/homework2/pic/hw2/q1.png)  
<br/>

### 2. One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c. 
```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -a 100 -f 0.1 -c

ARG seed -1
ARG fork_percentage 0.1
ARG actions 100
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b EXITS
                               a
Action: a forks c
                               a
                               └── c
Action: c EXITS
                               a
Action: a forks d
                               a
                               └── d
Action: d EXITS
                               a
Action: a forks e
                               a
                               └── e
Action: e EXITS
                               a
Action: a forks f
                               a
                               └── f
Action: f EXITS
                               a
Action: a forks g
                               a
                               └── g
Action: g EXITS
                               a
Action: a forks h
                               a
                               └── h
Action: h EXITS
                               a
Action: a forks i
                               a
                               └── i
Action: i EXITS
                               a
Action: a forks j
                               a
                               └── j
Action: j EXITS
                               a
Action: a forks k
                               a
                               └── k
Action: k EXITS
                               a
Action: a forks l
                               a
                               └── l
Action: l forks m
                               a
                               └── l
                                   └── m
Action: l EXITS
                               a
                               └── m
Action: m EXITS
                               a
Action: a forks n
                               a
                               └── n
Action: a forks o
                               a
                               ├── n
                               └── o
Action: o EXITS
                               a
                               └── n
Action: n EXITS
                               a
Action: a forks p
                               a
                               └── p
Action: a forks q
                               a
                               ├── p
                               └── q
Action: p EXITS
                               a
                               └── q
Action: q EXITS
                               a
Action: a forks r
                               a
                               └── r
Action: r EXITS
                               a
Action: a forks s
                               a
                               └── s
Action: s EXITS
                               a
Action: a forks t
                               a
                               └── t
Action: t EXITS
                               a
Action: a forks u
                               a
                               └── u
Action: u EXITS
                               a
Action: a forks v
                               a
                               └── v
Action: v EXITS
                               a
Action: a forks w
                               a
                               └── w
Action: w EXITS
                               a
Action: a forks x
                               a
                               └── x
Action: x EXITS
                               a
Action: a forks y
                               a
                               └── y
Action: y EXITS
                               a
Action: a forks z
                               a
                               └── z
Action: a forks A
                               a
                               ├── z
                               └── A
Action: z EXITS
                               a
                               └── A
Action: A EXITS
                               a
Action: a forks B
                               a
                               └── B
Action: B EXITS
                               a
Action: a forks C
                               a
                               └── C
Action: C EXITS
                               a
Action: a forks D
                               a
                               └── D
Action: D EXITS
                               a
Action: a forks E
                               a
                               └── E
Action: E forks F
                               a
                               └── E
                                   └── F
Action: E EXITS
                               a
                               └── F
Action: F EXITS
                               a
Action: a forks G
                               a
                               └── G
Action: G EXITS
                               a
Action: a forks H
                               a
                               └── H
Action: H EXITS
                               a
Action: a forks I
                               a
                               └── I
Action: I EXITS
                               a
Action: a forks J
                               a
                               └── J
Action: J EXITS
                               a
Action: a forks K
                               a
                               └── K
Action: K EXITS
                               a
Action: a forks L
                               a
                               └── L
Action: L EXITS
                               a
Action: a forks M
                               a
                               └── M
Action: M EXITS
                               a
Action: a forks N
                               a
                               └── N
Action: N EXITS
                               a
Action: a forks O
                               a
                               └── O
Action: O EXITS
                               a
Action: a forks P
                               a
                               └── P
Action: P EXITS
                               a
Action: a forks Q
                               a
                               └── Q
Action: Q EXITS
                               a
Action: a forks R
                               a
                               └── R
Action: R EXITS
                               a
Action: a forks S
                               a
                               └── S
Action: S EXITS
                               a
Action: a forks T
                               a
                               └── T
Action: T EXITS
                               a
Action: a forks U
                               a
                               └── U
Action: U EXITS
                               a
Action: a forks V
                               a
                               └── V
Action: V EXITS
                               a
Action: a forks W
                               a
                               └── W
Action: W EXITS
                               a
Action: a forks X
                               a
                               └── X
Action: X forks Y
                               a
                               └── X
                                   └── Y
Action: Y EXITS
                               a
                               └── X
Action: X EXITS
                               a
```  

```-a 100 is too big to display, use -a 10 instead```  

```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -a 10 -f 0.9 -c 

ARG seed -1
ARG fork_percentage 0.9
ARG actions 10
ARG action_list
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: b forks d
                               a
                               └── b
                                   ├── c
                                   └── d
Action: d forks e
                               a
                               └── b
                                   ├── c
                                   └── d
                                       └── e
Action: a forks f
                               a
                               ├── b
                               │   ├── c
                               │   └── d
                               │       └── e
                               └── f
Action: d forks g
                               a
                               ├── b
                               │   ├── c
                               │   └── d
                               │       ├── e
                               │       └── g
                               └── f
Action: g forks h
                               a
                               ├── b
                               │   ├── c
                               │   └── d
                               │       ├── e
                               │       └── g
                               │           └── h
                               └── f
Action: d forks i
                               a
                               ├── b
                               │   ├── c
                               │   └── d
                               │       ├── e
                               │       ├── g
                               │       │   └── h
                               │       └── i
                               └── f
Action: i forks j
                               a
                               ├── b
                               │   ├── c
                               │   └── d
                               │       ├── e
                               │       ├── g
                               │       │   └── h
                               │       └── i
                               │           └── j
                               └── f
Action: g forks k
                               a
                               ├── b
                               │   ├── c
                               │   └── d
                               │       ├── e
                               │       ├── g
                               │       │   ├── h
                               │       │   └── k
                               │       └── i
                               │           └── j
                               └── f
```
<br/>

### 3. Now, switch the output by using the -t flag (e.g., run ./fork.py -t). Given a set of process trees, can you tell which actions were taken?

```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -a 5 -f 0.9 -t -c

ARG seed -1
ARG fork_percentage 0.9
ARG actions 5
ARG action_list
ARG show_tree True
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b EXITS
                               a
Action: a forks c
                               a
                               └── c
Action: c EXITS
                               a
Action: a forks d
                               a
                               └── d
```  
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
Run IO_RUN_IMMEDIATE will run the io once the pervious IO finished.  
result for flag -I IO_RUN_IMMEDIATE  
![q83](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q83.png)  
<br/>
Run IO_RUN_LATER will first run the non IO process, for the pid0, since we only have 3 instructions, and the first one is non IO, the rest two will run after the first one.  
result for flag -I IO_RUN_LATER
![q84](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q84.png)  
<br/>
Run SWITCH_ON_IO will allow us to switch the cpu to other process while this process is under IO work, the result shows that cpu run pid1 when pid0 is under IO waiting.  
result for flag -S SWITCH_ON_IO
![q85](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q85.png)  
<br/>
Run SWITCH_ON_END will trun off the switch cpu mechanism, so the result shows that we first finish the task in PID0, although there are some idle time for wait pid0 IO work, after pid0 is done, we start to do pid1.  
result for flag -S SWITCH_ON_END
![q86](https://github.com/huaxing-w/cs5600-computer-system/blob/homework1/pic/q86.png)  
<br/>










