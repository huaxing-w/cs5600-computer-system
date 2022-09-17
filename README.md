# Chapter 5 - Homework(Simulation)  
### Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.

![q1](https://github.com/huaxing-w/cs5600-computer-system/blob/homework2/pic/hw2/q1.png)  
<br/>

### 2. One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c. 
```-a 100 is too much to display, use -a 10 instead```  

```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -a 10 -f 0.1 -c 

ARG seed -1
ARG fork_percentage 0.1
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
Action: f forks g
                               a
                               └── f
                                   └── g
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

### 4. One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: ./fork.py -A a+b,b+c,c+d,c+e,c-. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.

```without using -R flag```
```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -A a+b,b+c,c+d,c+e,c- -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
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
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```  

```use -R flag```  
```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -A a+b,b+c,c+d,c+e,c- -c -R

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent True
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
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```
<br/>

### 5. One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times. 
```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -A a+b,b+c,c+d,c+e,c- -F -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: b forks c
Action: c forks d
Action: c forks e
Action: c EXITS

                        Final Process Tree:
                               a
                               ├── b
                               ├── d
                               └── e
```

<br/>

### 6.  Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.
 

can not always tell what happened, there are differnt ways for children process to attach back to parent process.  
```md
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\fork.py -A a+b,b+c,c+d,c+e,c- -F -t

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action?
Action?
Action?
Action?
Action?

                        Final Process Tree:
                               a
                               ├── b
                               ├── d
                               └── e
```
<br/>
# Chapter 5 - Homework(code) 













