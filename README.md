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

### 1.  Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?  

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int num=100;
    printf("hello I am parent pid:%d, the num is %d\n",(int)getpid(),num);
    //create a fork
    int rc=fork();
    if(rc<0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    if(rc==0){
        num+=1;
        printf("hello, I am child pid:%d, the num is %d\n",(int)getpid(),num);
    }
    if(rc>0){
        num+=2;
        printf("hello I am parent pid:%d, the num is %d\n",(int)getpid(),num);
    }
    return 0;
}
```
result:  
```
bash-4.2$ ./ch5-q1 
hello I am parent pid:217574, the num is 100
hello I am parent pid:217574, the num is 102
hello, I am child pid:217575, the num is 101
```

Once we fork a new process, the num for parent and child are isolated to each other, thus I increase the num by 2 in parent, it would be 102. For child, it would be 101. 

### 2.  Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    printf("hello, I am parent pid:%d\n",(int)getpid());
    int f = open("ch5-q2.txt", O_RDWR | O_CREAT | O_EXCL,S_IRWXU);
    int rc=fork();
    if(rc<0){
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if(rc==0){
        if (f < 0) { 
            fprintf(stderr, "file open failed\n");
            exit(1);
        }
        printf("hello, I am child pid:%d, I am writing to the file\n",(int)getpid()); 
        write(f, "this is from child process\n", strlen("this is from child process\n"));   
    }
    if(rc>0){
        if (f < 0) { 
            fprintf(stderr, "file open failed\n");
            exit(1);
        }
        printf("hello, I am parent pid:%d,I am writing to the file\n",(int)getpid()); 
        write(f, "this is from parent process\n", strlen("this is from parent process\n"));
        
    }
    close(f);
    return 0;
}
```  
they can access the file descriptor from open(), when they writing file concurrently, the order can not be determined unless we use wait().  

result:
```
bash-4.2$ ./ch5-q2 
hello, I am parent pid:236752
hello, I am parent pid:236752,I am writing to the file
hello, I am child pid:236753, I am writing to the file
```

### 3.  Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int rc = fork();
    if(rc<0){
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if(rc==0){
        printf("hello!\n"); 
    }
    if(rc>0){
        //wait(NULL);
        sleep(1);
        printf("goodbye!\n");
    }
    return 0;
}
```
we could use sleep instead to let child process run first, and then the parent.

### 4.  Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?

execl() receives the location of the executable file as its first argument. The next arguments will be available to the file when it’s executed. The last argument has to be NULL.  
```int execl(const char *pathname, const char *arg, ..., NULL)```  

execlp() is very similar to execl(). However, execlp() uses the PATH environment variable to look for the file. Therefore, the path to the executable file is not needed.  
```int execlp(const char *file, const char *arg, ..., NULL)```  

If we use execle(), we can pass environment variables to the function, and it’ll use them.  
```int execle(const char *pathname, const char *arg, ..., NULL, char *const envp[])```  

execv(), unlike execl(), receives a vector of arguments that will be available to the executable file. In addition, the last element of the vector has to be NULL.  
```int execv(const char *pathname, char *const argv[])```  

execvp() looks for the program in the PATH environment variable.  
```int execvp(const char *file, char *const argv[])```  

We can pass environment variables to execve(). In addition, the arguments need to be inside a NULL-terminated vector.  
```int execve(const char *pathname, char *const argv[], char *const envp[])```  

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){

        char * const argv[] = {"ls", NULL};
        char * const envp[] = {NULL};
        execvp("ls", argv);

        //execl("/bin/ls", "ls", NULL);
        //execlp("ls", "ls", NULL);
        //execle("/bin/ls", "ls", NULL, envp);
        //execv("/bin/ls", argv);
        //execvpe("ls", argv, envp); 
    }
    if (rc > 0){
        wait(NULL);
    }
    return 0;
}
```  

### 5.  Now write a program that uses wait() to wait for the child proces to finish in the parent. What does wait() return? What happens if you use wait() in the child?
the wc value is the pid of the child process.
```
bash-4.2$ ./ch5-q5 
I am child process pid:46271
I am parent process pid:46270, wc value is 46271
```
 
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){
        printf("I am child process pid:%d\n",(int)getpid());

    }
    if (rc > 0){
        int wc=wait(NULL);
        printf("I am parent process pid:%d, wc value is %d\n",(int)getpid(),wc);

    }
    return 0;
}
```

if we call wait in child process, it will return -1, as there is no child process of childprocess.
```
bash-4.2$ ./ch5-q5 
I am child process pid:46744, the wc value is -1
I am parent process pid:46743, wc value is 46744
```
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){
        int wc=wait(NULL);
        printf("I am child process pid:%d, the wc value is %d\n",(int)getpid(),wc);

    }
    if (rc > 0){
        int wc=wait(NULL);
        printf("I am parent process pid:%d, wc value is %d\n",(int)getpid(),wc);
    }
    return 0;
}
```
### 6.  Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?  

when we don't child process to fully finished, but rather changing the state, the parent process starts to work.  

```
bash-4.2$ gcc -o ch5-q6 ch5-q6.c -Wall
bash-4.2$ ./ch5-q6
I am child process pid:47348
I am parent process pid:47347, wc value is 47348
```

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){
        
        printf("I am child process pid:%d\n",(int)getpid());

    }
    if (rc > 0){
        int wc=waitpid(rc,NULL,0);
        printf("I am parent process pid:%d, wc value is %d\n",(int)getpid(),wc);
    }
    return 0;
}
```

### 7.  Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?  
since we close the stdout, the child process can not print anything.
```
bash-4.2$ gcc -o ch5-q7 ch5-q7.c -Wall
bash-4.2$ ./ch5-q7 
I am parent process pid:48283, wc value is 48284
```
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){

        close(STDOUT_FILENO);
        
        printf("I am child process pid:%d\n",(int)getpid());

    }
    if (rc > 0){
        int wc=waitpid(rc,NULL,0);
        printf("I am parent process pid:%d, wc value is %d\n",(int)getpid(),wc);
    }
    return 0;
}
```
### 8.  Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.  
result:  
```
bash-4.2$ ./ch5-q8 
hello, world #1
hello, world #2
hello, world #3
finished!
```
```c
#include <stdio.h>
#include <unistd.h>
#define MSGSIZE 16

char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main(){
    char inbuf[MSGSIZE];
    int p[2];
    int pid1;
    int pid2;
    int nbytes;
    if(pipe(p)<0){
        fprintf(stderr, "pipe creation failed\n");
        exit(1);
    }
    pid1=fork();
    if (pid1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    
    if(pid1==0){
        close(p[0]);
        write(p[1],msg1,MSGSIZE);
        write(p[1],msg2,MSGSIZE);
        write(p[1],msg3,MSGSIZE);
        close(p[1]);
    }
    if(pid1>0){
        wait(NULL);
        pid2=fork();
        if(pid2==0){
            close(p[1]);
            while((nbytes = read(p[0], inbuf, MSGSIZE)) > 0){
                printf("%s\n",inbuf);
            }
            printf("finished!\n");
            close(p[0]);
        }
        
    }
    return 0;
}
```
<br/>

# Chapter 6  - Homework(Measurement)  

result:
```
bash-4.2$ ./ch6 
Hello, this is to test system call time
***************************************
system call time cost is : 0.464728 microseconds

Hello, this is to test contect switch time
***************************************
context switch time cost is : 1.543710 microseconds
```  


```c
#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>

int main(int argc,char* argv[]){
    printf("Hello, this is to test system call time\n");
    printf("***************************************\n");

    int f = open("./ch6.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    int i=0;
    for(i=0;i<1000000;i++){
        //write(f, "hello world!\n", strlen("hello world!\n"));
        write(f, NULL, 0);
    }
    gettimeofday(&end, NULL);
    printf("system call time cost is : %f microseconds\n", (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / 1000000);
    
    printf("\n");
    printf("Hello, this is to test contect switch time\n");
    printf("***************************************\n");

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    int p1[2];
    int p2[2];

    if(pipe(p1)<0){
        fprintf(stderr, "pipe creation failed\n");
        exit(1);
    }
    if(pipe(p2)<0){
        fprintf(stderr, "pipe creation failed\n");
        exit(1);
    }

    int pid1=fork();
    if (pid1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if(pid1==0){
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            fprintf(stderr, "set single cpu failed\n");
            exit(1);
        }
        i=0;
        for (i = 0; i < 1000000; i++) {
            read(p1[0], NULL, 0);
            write(p2[1], NULL, 0);
        }
    }
    if(pid1>0){
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            fprintf(stderr, "set single cpu failed\n");
            exit(1);
        }
        i=0;

        gettimeofday(&start, NULL);
        
        for (i = 0; i < 1000000; i++) {
            write(p1[1], NULL, 0);
            read(p2[0], NULL, 0);
        }
        gettimeofday(&end, NULL);
        printf("context switch time cost is : %f microseconds\n", (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / 1000000);


    }

    return 0;
}
```
<br/>

# Chapter 7  - Homework (Simulation)

### 1.  Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers. 
SJF  

```
Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```
FIFO
```
Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```









