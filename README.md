# Homework (Simulation)

### 1.   Let’s examine a simple program, “loop.s”. First, just read and understand it. Then, run it with these arguments (./x86.py -p loop.s -t 1 -i 100 -R dx) This specifies a single thread, an interrupt every 100 instructions, and tracing of register %dx. What will %dx be during the run? Use the -c flag to check your answers; the answers, on the left, show the value of the register (or memory value) after the instruction on the right has run.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p loop.s -t 1 -i 100 -R dx -c        
ARG seed 0
ARG numthreads 1
ARG program loop.s
ARG interrupt frequency 100
ARG interrupt randomness False
ARG argv
ARG load address 1000
ARG memsize 128
ARG memtrace
ARG regtrace dx
ARG cctrace False
ARG printstats False
ARG verbose False

   dx          Thread 0
    0
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
```
### 2.   Same code, different flags: (./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx) This specifies two threads, and initializes each %dx to 3. What values will %dx see? Run with -c to check. Does the presence of multiple threads affect your calculations? Is there a race in this code?
```
no,no
```
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx -c -C
ARG seed 0
ARG numthreads 2
ARG program loop.s
ARG interrupt frequency 100
ARG interrupt randomness False
ARG argv dx=3,dx=3
ARG load address 1000
ARG memsize 128
ARG memtrace
ARG regtrace dx
ARG cctrace True
ARG printstats False
ARG verbose False

   dx   >= >  <= <  != ==        Thread 0                Thread 1
    3   0  0  0  0  0  0
    2   0  0  0  0  0  0  1000 sub  $1,%dx
    2   1  1  0  0  1  0  1001 test $0,%dx
    2   1  1  0  0  1  0  1002 jgte .top
    1   1  1  0  0  1  0  1000 sub  $1,%dx
    1   1  1  0  0  1  0  1001 test $0,%dx
    1   1  1  0  0  1  0  1002 jgte .top
    0   1  1  0  0  1  0  1000 sub  $1,%dx
    0   1  0  1  0  0  1  1001 test $0,%dx
    0   1  0  1  0  0  1  1002 jgte .top
   -1   1  0  1  0  0  1  1000 sub  $1,%dx
   -1   0  0  1  1  1  0  1001 test $0,%dx
   -1   0  0  1  1  1  0  1002 jgte .top
   -1   0  0  1  1  1  0  1003 halt
    3   0  0  0  0  0  0  ----- Halt;Switch -----  ----- Halt;Switch -----  
    2   0  0  0  0  0  0                           1000 sub  $1,%dx
    2   1  1  0  0  1  0                           1001 test $0,%dx
    2   1  1  0  0  1  0                           1002 jgte .top
    1   1  1  0  0  1  0                           1000 sub  $1,%dx
    1   1  1  0  0  1  0                           1001 test $0,%dx
    1   1  1  0  0  1  0                           1002 jgte .top
    0   1  1  0  0  1  0                           1000 sub  $1,%dx
    0   1  0  1  0  0  1                           1001 test $0,%dx
    0   1  0  1  0  0  1                           1002 jgte .top
   -1   1  0  1  0  0  1                           1000 sub  $1,%dx
   -1   0  0  1  1  1  0                           1001 test $0,%dx
   -1   0  0  1  1  1  0                           1002 jgte .top
   -1   0  0  1  1  1  0                           1003 halt
```
### 3.   Run this: ./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx This makes the interrupt interval small/random; use different seeds (-s) to see different interleavings. Does the interrupt frequency change anything?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -c -C
ARG seed 0
ARG numthreads 2
ARG program loop.s
ARG interrupt frequency 3
ARG interrupt randomness True
ARG argv dx=3,dx=3
ARG load address 1000
ARG memsize 128
ARG memtrace 
ARG regtrace dx
ARG cctrace True
ARG printstats False
ARG verbose False

   dx   >= >  <= <  != ==        Thread 0                Thread 1
    3   0  0  0  0  0  0
    2   0  0  0  0  0  0  1000 sub  $1,%dx
    2   1  1  0  0  1  0  1001 test $0,%dx
    2   1  1  0  0  1  0  1002 jgte .top
    3   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    2   0  0  0  0  0  0                           1000 sub  $1,%dx
    2   1  1  0  0  1  0                           1001 test $0,%dx
    2   1  1  0  0  1  0                           1002 jgte .top
    2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  1  0  0  1  0  1000 sub  $1,%dx
    1   1  1  0  0  1  0  1001 test $0,%dx
    2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  1  0  0  1  0                           1000 sub  $1,%dx
    1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  1  0  0  1  0  1002 jgte .top
    0   1  1  0  0  1  0  1000 sub  $1,%dx
   -1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
   -1   0  0  1  1  1  0  1001 test $0,%dx
   -1   0  0  1  1  1  0  1002 jgte .top
    0   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0   1  0  1  0  0  1                           1001 test $0,%dx
    0   1  0  1  0  0  1                           1002 jgte .top
   -1   0  0  1  1  1  0  ------ Interrupt ------  ------ Interrupt ------
   -1   0  0  1  1  1  0  1003 halt
    0   1  0  1  0  0  1  ----- Halt;Switch -----  ----- Halt;Switch -----
   -1   1  0  1  0  0  1                           1000 sub  $1,%dx
   -1   0  0  1  1  1  0                           1001 test $0,%dx
   -1   0  0  1  1  1  0  ------ Interrupt ------  ------ Interrupt ------
   -1   0  0  1  1  1  0                           1002 jgte .top
   -1   0  0  1  1  1  0                           1003 halt

```
### 4.   Now, a different program, looping-race-nolock.s, which accesses a shared variable located at address 2000; we’ll call this variable value. Run it with a single thread to confirm your understanding: ./x86.py -p looping-race-nolock.s -t 1 -M 2000 What is value (i.e., at memory address 2000) throughout the run? Use -c to check.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p looping-race-nolock.s -t 1 -M 2000 -c -C     
ARG seed 0
ARG numthreads 1
ARG program looping-race-nolock.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace
ARG cctrace True
ARG printstats False
ARG verbose False

 2000   >= >  <= <  != ==        Thread 0
    0   0  0  0  0  0  0
    0   0  0  0  0  0  0  1000 mov 2000, %ax
    0   0  0  0  0  0  0  1001 add $1, %ax
    1   0  0  0  0  0  0  1002 mov %ax, 2000
    1   0  0  0  0  0  0  1003 sub  $1, %bx
    1   0  0  1  1  1  0  1004 test $0, %bx
    1   0  0  1  1  1  0  1005 jgt .top
    1   0  0  1  1  1  0  1006 halt
```
### 5.    Run with multiple iterations/threads: ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000 Why does each thread loop three times? What is final value of value?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000 -c -C
ARG seed 0
ARG numthreads 2
ARG program looping-race-nolock.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv bx=3
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace 
ARG cctrace True
ARG printstats False
ARG verbose False

 2000   >= >  <= <  != ==        Thread 0                Thread 1
    0   0  0  0  0  0  0  
    0   0  0  0  0  0  0  1000 mov 2000, %ax
    0   0  0  0  0  0  0  1001 add $1, %ax
    1   0  0  0  0  0  0  1002 mov %ax, 2000
    1   0  0  0  0  0  0  1003 sub  $1, %bx
    1   1  1  0  0  1  0  1004 test $0, %bx
    1   1  1  0  0  1  0  1005 jgt .top
    1   1  1  0  0  1  0  1000 mov 2000, %ax
    1   1  1  0  0  1  0  1001 add $1, %ax
    2   1  1  0  0  1  0  1002 mov %ax, 2000
    2   1  1  0  0  1  0  1003 sub  $1, %bx
    2   1  1  0  0  1  0  1004 test $0, %bx
    2   1  1  0  0  1  0  1005 jgt .top
    2   1  1  0  0  1  0  1000 mov 2000, %ax
    2   1  1  0  0  1  0  1001 add $1, %ax
    3   1  1  0  0  1  0  1002 mov %ax, 2000
    3   1  1  0  0  1  0  1003 sub  $1, %bx
    3   1  0  1  0  0  1  1004 test $0, %bx
    3   1  0  1  0  0  1  1005 jgt .top
    3   1  0  1  0  0  1  1006 halt
    3   0  0  0  0  0  0  ----- Halt;Switch -----  ----- Halt;Switch -----
    3   0  0  0  0  0  0                           1000 mov 2000, %ax
    3   0  0  0  0  0  0                           1001 add $1, %ax
    4   0  0  0  0  0  0                           1002 mov %ax, 2000
    4   0  0  0  0  0  0                           1003 sub  $1, %bx
    4   1  1  0  0  1  0                           1004 test $0, %bx
    4   1  1  0  0  1  0                           1005 jgt .top
    4   1  1  0  0  1  0                           1000 mov 2000, %ax
    4   1  1  0  0  1  0                           1001 add $1, %ax
    5   1  1  0  0  1  0                           1002 mov %ax, 2000
    5   1  1  0  0  1  0                           1003 sub  $1, %bx
    5   1  1  0  0  1  0                           1004 test $0, %bx
    5   1  1  0  0  1  0                           1005 jgt .top
    5   1  1  0  0  1  0                           1000 mov 2000, %ax
    5   1  1  0  0  1  0                           1001 add $1, %ax
    6   1  1  0  0  1  0                           1002 mov %ax, 2000
    6   1  1  0  0  1  0                           1003 sub  $1, %bx
    6   1  0  1  0  0  1                           1004 test $0, %bx
    6   1  0  1  0  0  1                           1005 jgt .top
    6   1  0  1  0  0  1                           1006 halt
```

### 6.    Run with random interrupt intervals: ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0 with different seeds (-s 1, -s 2, etc.) Can you tell by looking at the thread interleaving what the final value of value will be? Does the timing of the interrupt matter? Where can it safely occur? Where not? In other words, where is the critical section exactly?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0 -c -C
ARG seed 0
ARG numthreads 2
ARG program looping-race-nolock.s
ARG interrupt frequency 4
ARG interrupt randomness True
ARG argv 
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace 
ARG cctrace True
ARG printstats False
ARG verbose False

 2000   >= >  <= <  != ==        Thread 0                Thread 1
    0   0  0  0  0  0  0  
    0   0  0  0  0  0  0  1000 mov 2000, %ax
    0   0  0  0  0  0  0  1001 add $1, %ax
    1   0  0  0  0  0  0  1002 mov %ax, 2000
    1   0  0  0  0  0  0  1003 sub  $1, %bx
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------  
    1   0  0  0  0  0  0                           1000 mov 2000, %ax
    1   0  0  0  0  0  0                           1001 add $1, %ax
    2   0  0  0  0  0  0                           1002 mov %ax, 2000
    2   0  0  0  0  0  0                           1003 sub  $1, %bx
    2   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    2   0  0  1  1  1  0  1004 test $0, %bx
    2   0  0  1  1  1  0  1005 jgt .top
    2   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    2   0  0  1  1  1  0                           1004 test $0, %bx
    2   0  0  1  1  1  0                           1005 jgt .top
    2   0  0  1  1  1  0  ------ Interrupt ------  ------ Interrupt ------
    2   0  0  1  1  1  0  1006 halt
    2   0  0  1  1  1  0  ----- Halt;Switch -----  ----- Halt;Switch -----
    2   0  0  1  1  1  0                           1006 halt

```

### 7.     Now examine fixed interrupt intervals: ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 What will the final value of the shared variable value be? What about when you change -i 2, -i 3, etc.? For which interrupt intervals does the program give the “correct” answer?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 -c -C
ARG seed 0
ARG numthreads 2
ARG program looping-race-nolock.s
ARG interrupt frequency 1
ARG interrupt randomness False
ARG argv bx=1
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace
ARG cctrace True
ARG printstats False
ARG verbose False

 2000   >= >  <= <  != ==        Thread 0                Thread 1
    0   0  0  0  0  0  0
    0   0  0  0  0  0  0  1000 mov 2000, %ax
    0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0   0  0  0  0  0  0                           1000 mov 2000, %ax
    0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0   0  0  0  0  0  0  1001 add $1, %ax
    0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0   0  0  0  0  0  0                           1001 add $1, %ax
    0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0  1002 mov %ax, 2000
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0                           1002 mov %ax, 2000
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0  1003 sub  $1, %bx
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0                           1003 sub  $1, %bx
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1  1004 test $0, %bx
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1                           1004 test $0, %bx
    1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1  1005 jgt .top
    1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1                           1005 jgt .top
    1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1  1006 halt
    1   1  0  1  0  0  1  ----- Halt;Switch -----  ----- Halt;Switch -----
    1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1                           1006 halt

```

```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 2 -c -C
ARG seed 0
ARG numthreads 2
ARG program looping-race-nolock.s
ARG interrupt frequency 2
ARG interrupt randomness False
ARG argv bx=1
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace
ARG cctrace True
ARG printstats False
ARG verbose False

 2000   >= >  <= <  != ==        Thread 0                Thread 1
    0   0  0  0  0  0  0
    0   0  0  0  0  0  0  1000 mov 2000, %ax
    0   0  0  0  0  0  0  1001 add $1, %ax
    0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0   0  0  0  0  0  0                           1000 mov 2000, %ax
    0   0  0  0  0  0  0                           1001 add $1, %ax
    0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0  1002 mov %ax, 2000
    1   0  0  0  0  0  0  1003 sub  $1, %bx
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0                           1002 mov %ax, 2000
    1   0  0  0  0  0  0                           1003 sub  $1, %bx
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1  1004 test $0, %bx
    1   1  0  1  0  0  1  1005 jgt .top
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1                           1004 test $0, %bx
    1   1  0  1  0  0  1                           1005 jgt .top
    1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1   1  0  1  0  0  1  1006 halt
    1   1  0  1  0  0  1  ----- Halt;Switch -----  ----- Halt;Switch -----
    1   1  0  1  0  0  1                           1006 halt

```

```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 3 -c -C
ARG seed 0
ARG numthreads 2
ARG program looping-race-nolock.s
ARG interrupt frequency 3
ARG interrupt randomness False
ARG argv bx=1
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace
ARG cctrace True
ARG printstats False
ARG verbose False

 2000   >= >  <= <  != ==        Thread 0                Thread 1
    0   0  0  0  0  0  0
    0   0  0  0  0  0  0  1000 mov 2000, %ax
    0   0  0  0  0  0  0  1001 add $1, %ax
    1   0  0  0  0  0  0  1002 mov %ax, 2000
    1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1   0  0  0  0  0  0                           1000 mov 2000, %ax
    1   0  0  0  0  0  0                           1001 add $1, %ax
    2   0  0  0  0  0  0                           1002 mov %ax, 2000
    2   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    2   0  0  0  0  0  0  1003 sub  $1, %bx
    2   1  0  1  0  0  1  1004 test $0, %bx
    2   1  0  1  0  0  1  1005 jgt .top
    2   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    2   0  0  0  0  0  0                           1003 sub  $1, %bx
    2   1  0  1  0  0  1                           1004 test $0, %bx
    2   1  0  1  0  0  1                           1005 jgt .top
    2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    2   1  0  1  0  0  1  1006 halt
    2   1  0  1  0  0  1  ----- Halt;Switch -----  ----- Halt;Switch -----
    2   1  0  1  0  0  1                           1006 halt

```

### 8.     Run the same for more loops (e.g., set -a bx=100). What interrupt intervals (-i) lead to a correct outcome? Which intervals are surprising?
```
-i 597
```

### 9.     One last program: wait-for-me.s. Run: ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000 This sets the %ax register to 1 for thread 0, and 0 for thread 1, and watches %ax and memory location 2000. How should the code behave? How is the value at location 2000 being used by the threads? What will its final value be?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000 -c -C
ARG seed 0                                 
ARG numthreads 2
ARG program wait-for-me.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv ax=1,ax=0
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace ax
ARG cctrace True
ARG printstats False
ARG verbose False

 2000      ax   >= >  <= <  != ==        Thread 0                Thread 1
    0       1   0  0  0  0  0  0  
    0       1   1  0  1  0  0  1  1000 test $1, %ax
    0       1   1  0  1  0  0  1  1001 je .signaller
    1       1   1  0  1  0  0  1  1006 mov  $1, 2000
    1       1   1  0  1  0  0  1  1007 halt
    1       0   0  0  0  0  0  0  ----- Halt;Switch -----  ----- Halt;Switch -----  
    1       0   0  0  1  1  1  0                           1000 test $1, %ax
    1       0   0  0  1  1  1  0                           1001 je .signaller
    1       0   0  0  1  1  1  0                           1002 mov  2000, %cx
    1       0   1  0  1  0  0  1                           1003 test $1, %cx
    1       0   1  0  1  0  0  1                           1004 jne .waiter
    1       0   1  0  1  0  0  1                           1005 halt

```
### 10.     Now switch the inputs: ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000 How do the threads behave? What is thread 0 doing? How would changing the interrupt interval (e.g., -i 1000, or perhaps to use random intervals) change the trace outcome? Is the program efficiently using the CPU?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000 -c -C
ARG seed 0
ARG numthreads 2
ARG program wait-for-me.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv ax=0,ax=1
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace ax
ARG cctrace True
ARG printstats False
ARG verbose False

 2000      ax   >= >  <= <  != ==        Thread 0                Thread 1
    0       0   0  0  0  0  0  0
    0       0   0  0  1  1  1  0  1000 test $1, %ax
    0       0   0  0  1  1  1  0  1001 je .signaller
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       0   0  0  1  1  1  0  1002 mov  2000, %cx
    0       0   0  0  1  1  1  0  1003 test $1, %cx
    0       0   0  0  1  1  1  0  1004 jne .waiter
    0       1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0       1   1  0  1  0  0  1                           1000 test $1, %ax
    0       1   1  0  1  0  0  1                           1001 je .signaller
    1       1   1  0  1  0  0  1                           1006 mov  $1, 2000
    1       1   1  0  1  0  0  1                           1007 halt
    1       0   0  0  1  1  1  0  ----- Halt;Switch -----  ----- Halt;Switch -----
    1       0   0  0  1  1  1  0  1002 mov  2000, %cx
    1       0   1  0  1  0  0  1  1003 test $1, %cx
    1       0   1  0  1  0  0  1  1004 jne .waiter
    1       0   1  0  1  0  0  1  1005 halt

```
