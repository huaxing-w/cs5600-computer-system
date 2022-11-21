# Homework (Code)

### 1.   First build main-race.c. Examine the code so you can see the (hopefully obvious) data race in the code. Now run helgrind (by typing valgrind --tool=helgrind main-race) to see how it reports the race. Does it point to the right lines of code? What other information does it give to you?
```
bash-4.2$ valgrind --tool=helgrind ./main-race
==243742== Helgrind, a thread error detector
==243742== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==243742== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==243742== Command: ./main-race
==243742== 
==243742== ---Thread-Announcement------------------------------------------
==243742== 
==243742== Thread #1 is the program's root thread
==243742== 
==243742== ---Thread-Announcement------------------------------------------
==243742== 
==243742== Thread #2 was created
==243742==    at 0x5156ACE: clone (in /usr/lib64/libc-2.17.so)
==243742==    by 0x4E43059: do_clone.constprop.4 (in /usr/lib64/libpthread-2.17.so)
==243742==    by 0x4E44569: pthread_create@@GLIBC_2.2.5 (in /usr/lib64/libpthread-2.17.so)
==243742==    by 0x4C30CEA: pthread_create_WRK (hg_intercepts.c:427)
==243742==    by 0x4C31DC8: pthread_create@* (hg_intercepts.c:460)
==243742==    by 0x400654: main (in /home/huaxing/cs5600/week11/main-race)
==243742== 
==243742== ----------------------------------------------------------------
==243742== 
==243742== Possible data race during read of size 4 at 0x601048 by thread #1
==243742== Locks held: none
==243742==    at 0x400672: main (in /home/huaxing/cs5600/week11/main-race)
==243742== 
==243742== This conflicts with a previous write of size 4 by thread #2
==243742== Locks held: none
==243742==    at 0x40061E: worker (in /home/huaxing/cs5600/week11/main-race)
==243742==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==243742==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==243742==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==243742==  Address 0x601048 is 0 bytes inside data symbol "balance"
==243742== 
==243742== ----------------------------------------------------------------
==243742== 
==243742== Possible data race during write of size 4 at 0x601048 by thread #1
==243742== Locks held: none
==243742==    at 0x40067B: main (in /home/huaxing/cs5600/week11/main-race)
==243742== 
==243742== This conflicts with a previous write of size 4 by thread #2
==243742== Locks held: none
==243742==    at 0x40061E: worker (in /home/huaxing/cs5600/week11/main-race)
==243742==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==243742==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==243742==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==243742==  Address 0x601048 is 0 bytes inside data symbol "balance"
==243742== 
==243742== 
==243742== Use --history-level=approx or =none to gain increased speed, at
==243742== the cost of reduced accuracy of conflicting-access information
==243742== For lists of detected and suppressed errors, rerun with: -s
==243742== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

```
### 2.   What happens when you remove one of the offending lines of code? Now add a lock around one of the updates to the shared variable, and then around both. What does helgrind report in each of these cases?
```
remove the balance++

bash-4.2$ valgrind --tool=helgrind ./main-race
==245240== Helgrind, a thread error detector
==245240== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==245240== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==245240== Command: ./main-race
==245240== 
==245240== 
==245240== Use --history-level=approx or =none to gain increased speed, at
==245240== the cost of reduced accuracy of conflicting-access information
==245240== For lists of detected and suppressed errors, rerun with: -s
==245240== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
add lock in the worker

bash-4.2$ valgrind --tool=helgrind ./main-race
==245844== Helgrind, a thread error detector
==245844== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==245844== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==245844== Command: ./main-race
==245844== 
==245844== ---Thread-Announcement------------------------------------------
==245844== 
==245844== Thread #1 is the program's root thread
==245844== 
==245844== ---Thread-Announcement------------------------------------------
==245844== 
==245844== Thread #2 was created
==245844==    at 0x5156ACE: clone (in /usr/lib64/libc-2.17.so)
==245844==    by 0x4E43059: do_clone.constprop.4 (in /usr/lib64/libpthread-2.17.so)
==245844==    by 0x4E44569: pthread_create@@GLIBC_2.2.5 (in /usr/lib64/libpthread-2.17.so)
==245844==    by 0x4C30CEA: pthread_create_WRK (hg_intercepts.c:427)
==245844==    by 0x4C31DC8: pthread_create@* (hg_intercepts.c:460)
==245844==    by 0x400756: main (in /home/huaxing/cs5600/week11/main-race)
==245844== 
==245844== ----------------------------------------------------------------
==245844== 
==245844==  Lock at 0x6010A0 was first observed
==245844==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==245844==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==245844==    by 0x4006D2: worker (in /home/huaxing/cs5600/week11/main-race)
==245844==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==245844==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==245844==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==245844==  Address 0x6010a0 is 0 bytes inside data symbol "m1"
==245844== 
==245844== Possible data race during read of size 4 at 0x601080 by thread #1
==245844== Locks held: none
==245844==    at 0x400774: main (in /home/huaxing/cs5600/week11/main-race)
==245844== 
==245844== This conflicts with a previous write of size 4 by thread #2
==245844== Locks held: 1, at address 0x6010A0
==245844==    at 0x4006F9: worker (in /home/huaxing/cs5600/week11/main-race)
==245844==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==245844==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==245844==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==245844==  Address 0x601080 is 0 bytes inside data symbol "balance"
==245844== 
==245844== ----------------------------------------------------------------
==245844== 
==245844==  Lock at 0x6010A0 was first observed
==245844==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==245844==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==245844==    by 0x4006D2: worker (in /home/huaxing/cs5600/week11/main-race)
==245844==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==245844==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==245844==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==245844==  Address 0x6010a0 is 0 bytes inside data symbol "m1"
==245844== 
==245844== Possible data race during write of size 4 at 0x601080 by thread #1
==245844== Locks held: none
==245844==    at 0x40077D: main (in /home/huaxing/cs5600/week11/main-race)
==245844== 
==245844== This conflicts with a previous write of size 4 by thread #2
==245844== Locks held: 1, at address 0x6010A0
==245844==    at 0x4006F9: worker (in /home/huaxing/cs5600/week11/main-race)
==245844==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==245844==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==245844==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==245844==  Address 0x601080 is 0 bytes inside data symbol "balance"
==245844== 
==245844== 
==245844== Use --history-level=approx or =none to gain increased speed, at
==245844== the cost of reduced accuracy of conflicting-access information
==245844== For lists of detected and suppressed errors, rerun with: -s
==245844== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)

```


```
add lock in both variable 

bash-4.2$ valgrind --tool=helgrind ./main-race
==248850== Helgrind, a thread error detector
==248850== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==248850== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==248850== Command: ./main-race
==248850== 
20000
==248850== 
==248850== Use --history-level=approx or =none to gain increased speed, at
==248850== the cost of reduced accuracy of conflicting-access information
==248850== For lists of detected and suppressed errors, rerun with: -s
==248850== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 30003 from 6)
```

### 3.   Now let’s look at main-deadlock.c. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). Can you see what problem it might have?
```
one thread is trying to acquire m1 and then m2
another thread is trying to acquire m2 and then m1

but when second thread tried to acquire m1, it is in the thread1's hand.

```

### 4.    Now run helgrind on this code. What does helgrind report?
```
bash-4.2$ valgrind --tool=helgrind ./main-deadlock
==15800== Helgrind, a thread error detector
==15800== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==15800== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==15800== Command: ./main-deadlock
==15800== 
==15800== ---Thread-Announcement------------------------------------------
==15800== 
==15800== Thread #3 was created
==15800==    at 0x5156ACE: clone (in /usr/lib64/libc-2.17.so)
==15800==    by 0x4E43059: do_clone.constprop.4 (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x4E44569: pthread_create@@GLIBC_2.2.5 (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x4C30CEA: pthread_create_WRK (hg_intercepts.c:427)
==15800==    by 0x4C31DC8: pthread_create@* (hg_intercepts.c:460)
==15800==    by 0x400824: main (in /home/huaxing/cs5600/week11/main-deadlock)
==15800== 
==15800== ----------------------------------------------------------------
==15800== 
==15800== Thread #3: lock order "0x601080 before 0x6010C0" violated
==15800== 
==15800== Observed (incorrect) order is: acquisition of lock at 0x6010C0
==15800==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==15800==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==15800==    by 0x400729: worker (in /home/huaxing/cs5600/week11/main-deadlock)
==15800==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==15800==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==15800== 
==15800==  followed by a later acquisition of lock at 0x601080
==15800==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==15800==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==15800==    by 0x400750: worker (in /home/huaxing/cs5600/week11/main-deadlock)
==15800==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==15800==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==15800== 
==15800== Required order was established by acquisition of lock at 0x601080
==15800==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==15800==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==15800==    by 0x4006DB: worker (in /home/huaxing/cs5600/week11/main-deadlock)
==15800==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==15800==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==15800== 
==15800==  followed by a later acquisition of lock at 0x6010C0
==15800==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==15800==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==15800==    by 0x400702: worker (in /home/huaxing/cs5600/week11/main-deadlock)
==15800==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==15800==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==15800== 
==15800==  Lock at 0x601080 was first observed
==15800==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==15800==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==15800==    by 0x4006DB: worker (in /home/huaxing/cs5600/week11/main-deadlock)
==15800==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==15800==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==15800==  Address 0x601080 is 0 bytes inside data symbol "m1"
==15800== 
==15800==  Lock at 0x6010C0 was first observed
==15800==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==15800==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==15800==    by 0x400702: worker (in /home/huaxing/cs5600/week11/main-deadlock)
==15800==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==15800==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==15800==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==15800==  Address 0x6010c0 is 0 bytes inside data symbol "m2"
==15800== 
==15800== 
==15800== 
==15800== Use --history-level=approx or =none to gain increased speed, at
==15800== the cost of reduced accuracy of conflicting-access information
==15800== For lists of detected and suppressed errors, rerun with: -s
==15800== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 8 from 8)

```
### 5.     Now run helgrind on main-deadlock-global.c. Examine the code; does it have the same problem that main-deadlock.c has? Should helgrind be reporting the same error? What does this tell you about tools like helgrind?
```
bash-4.2$ valgrind --tool=helgrind ./main-deadlock-global
==16945== Helgrind, a thread error detector
==16945== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==16945== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==16945== Command: ./main-deadlock-global
==16945== 
==16945== ---Thread-Announcement------------------------------------------
==16945== 
==16945== Thread #3 was created
==16945==    at 0x5156ACE: clone (in /usr/lib64/libc-2.17.so)
==16945==    by 0x4E43059: do_clone.constprop.4 (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x4E44569: pthread_create@@GLIBC_2.2.5 (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x4C30CEA: pthread_create_WRK (hg_intercepts.c:427)
==16945==    by 0x4C31DC8: pthread_create@* (hg_intercepts.c:460)
==16945==    by 0x400872: main (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945== 
==16945== ----------------------------------------------------------------
==16945== 
==16945== Thread #3: lock order "0x6010C0 before 0x601100" violated
==16945== 
==16945== Observed (incorrect) order is: acquisition of lock at 0x601100
==16945==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==16945==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==16945==    by 0x400750: worker (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==16945==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==16945== 
==16945==  followed by a later acquisition of lock at 0x6010C0
==16945==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==16945==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==16945==    by 0x400777: worker (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==16945==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==16945== 
==16945== Required order was established by acquisition of lock at 0x6010C0
==16945==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==16945==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==16945==    by 0x400702: worker (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==16945==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==16945== 
==16945==  followed by a later acquisition of lock at 0x601100
==16945==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==16945==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==16945==    by 0x400729: worker (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==16945==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==16945== 
==16945==  Lock at 0x6010C0 was first observed
==16945==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==16945==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==16945==    by 0x400702: worker (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==16945==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==16945==  Address 0x6010c0 is 0 bytes inside data symbol "m1"
==16945== 
==16945==  Lock at 0x601100 was first observed
==16945==    at 0x4C2E350: mutex_lock_WRK (hg_intercepts.c:909)
==16945==    by 0x4C321AD: pthread_mutex_lock (hg_intercepts.c:925)
==16945==    by 0x400729: worker (in /home/huaxing/cs5600/week11/main-deadlock-global)
==16945==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==16945==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==16945==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==16945==  Address 0x601100 is 0 bytes inside data symbol "m2"
==16945== 
==16945== 
==16945== 
==16945== Use --history-level=approx or =none to gain increased speed, at
==16945== the cost of reduced accuracy of conflicting-access information
==16945== For lists of detected and suppressed errors, rerun with: -s
==16945== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 8 from 8)

```

### 6.      Let’s next look at main-signal.c. This code uses a variable (done) to signal that the child is done and that the parent can now continue. Why is this code inefficient? (what does the parent end up spending its time doing, particularly if the child thread takes a long time to complete?)
```
keep looping
```

### 7.      Now run helgrind on this program. What does it report? Is the code correct?
```
bash-4.2$ valgrind --tool=helgrind ./main-signal
==19177== Helgrind, a thread error detector
==19177== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==19177== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==19177== Command: ./main-signal
==19177== 
this should print first
==19177== ---Thread-Announcement------------------------------------------
==19177== 
==19177== Thread #1 is the program's root thread
==19177== 
==19177== ---Thread-Announcement------------------------------------------
==19177== 
==19177== Thread #2 was created
==19177==    at 0x5156ACE: clone (in /usr/lib64/libc-2.17.so)
==19177==    by 0x4E43059: do_clone.constprop.4 (in /usr/lib64/libpthread-2.17.so)
==19177==    by 0x4E44569: pthread_create@@GLIBC_2.2.5 (in /usr/lib64/libpthread-2.17.so)
==19177==    by 0x4C30CEA: pthread_create_WRK (hg_intercepts.c:427)
==19177==    by 0x4C31DC8: pthread_create@* (hg_intercepts.c:460)
==19177==    by 0x40064D: main (in /home/huaxing/cs5600/week11/main-signal)
==19177== 
==19177== ----------------------------------------------------------------
==19177== 
==19177== Possible data race during read of size 4 at 0x601048 by thread #1
==19177== Locks held: none
==19177==    at 0x40066C: main (in /home/huaxing/cs5600/week11/main-signal)
==19177== 
==19177== This conflicts with a previous write of size 4 by thread #2
==19177== Locks held: none
==19177==    at 0x400613: worker (in /home/huaxing/cs5600/week11/main-signal)
==19177==    by 0x4C30EDE: mythread_wrapper (hg_intercepts.c:389)
==19177==    by 0x4E43EA4: start_thread (in /usr/lib64/libpthread-2.17.so)
==19177==    by 0x5156B0C: clone (in /usr/lib64/libc-2.17.so)
==19177==  Address 0x601048 is 0 bytes inside data symbol "done"
==19177== 
this should print last
==19177== 
==19177== Use --history-level=approx or =none to gain increased speed, at
==19177== the cost of reduced accuracy of conflicting-access information
==19177== For lists of detected and suppressed errors, rerun with: -s
==19177== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 66 from 45)
```
### 8.      Now look at a slightly modified version of the code, which is found in main-signal-cv.c. This version uses a condition variable to do the signaling (and associated lock). Why is this code preferred to the previous version? Is it correctness, or performance, or both?
```
it's using Condition Variables

```
### 9.      Once again run helgrind on main-signal-cv. Does it report any errors?
```
bash-4.2$ gcc -o main-signal-cv main-signal-cv.c -Wall -pthread
bash-4.2$ valgrind --tool=helgrind ./main-signal-cv
==23188== Helgrind, a thread error detector
==23188== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==23188== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==23188== Command: ./main-signal-cv
==23188== 
this should print first
this should print last
==23188== 
==23188== Use --history-level=approx or =none to gain increased speed, at
==23188== the cost of reduced accuracy of conflicting-access information
==23188== For lists of detected and suppressed errors, rerun with: -s
==23188== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 6 from 6)
```

# Homework (Simulation)

### 1.    Examine flag.s. This code “implements” locking with a single memory flag. Can you understand the assembly?
```
yes
```

### 2.    When you run with the defaults, does flag.s work? Use the -M and -R flags to trace variables and registers (and turn on -c to see their values). Can you predict what value will end up in flag?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p flag.s -M flag -R ax,bx -c -C
ARG seed 0
ARG numthreads 2
ARG program flag.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched
ARG argv
ARG load address 1000
ARG memsize 128
ARG memtrace flag
ARG regtrace ax,bx
ARG cctrace True
ARG printstats False
ARG verbose False


 flag      ax    bx   >= >  <= <  != ==        Thread 0                Thread 1

    0       0     0   0  0  0  0  0  0
    0       0     0   0  0  0  0  0  0  1000 mov  flag, %ax
    0       0     0   1  0  1  0  0  1  1001 test $0, %ax
    0       0     0   1  0  1  0  0  1  1002 jne  .acquire
    1       0     0   1  0  1  0  0  1  1003 mov  $1, flag
    1       0     0   1  0  1  0  0  1  1004 mov  count, %ax
    1       1     0   1  0  1  0  0  1  1005 add  $1, %ax
    1       1     0   1  0  1  0  0  1  1006 mov  %ax, count
    0       1     0   1  0  1  0  0  1  1007 mov  $0, flag
    0       1    -1   1  0  1  0  0  1  1008 sub  $1, %bx
    0       1    -1   0  0  1  1  1  0  1009 test $0, %bx
    0       1    -1   0  0  1  1  1  0  1010 jgt .top
    0       1    -1   0  0  1  1  1  0  1011 halt
    0       0     0   0  0  0  0  0  0  ----- Halt;Switch -----  ----- Halt;Switch -----
    0       0     0   0  0  0  0  0  0                           1000 mov  flag, %ax
    0       0     0   1  0  1  0  0  1                           1001 test $0, %ax
    0       0     0   1  0  1  0  0  1                           1002 jne  .acquire
    1       0     0   1  0  1  0  0  1                           1003 mov  $1, flag
    1       1     0   1  0  1  0  0  1                           1004 mov  count, %ax
    1       2     0   1  0  1  0  0  1                           1005 add  $1, %ax
    1       2     0   1  0  1  0  0  1                           1006 mov  %ax, count
    0       2     0   1  0  1  0  0  1                           1007 mov  $0, flag
    0       2    -1   1  0  1  0  0  1                           1008 sub  $1, %bx
    0       2    -1   0  0  1  1  1  0                           1009 test $0, %bx
    0       2    -1   0  0  1  1  1  0                           1010 jgt .top
    0       2    -1   0  0  1  1  1  0                           1011 halt

```
### 3.    Change the value of the register %bx with the -a flag (e.g., -a bx=2,bx=2 if you are running just two threads). What does the code do? How does it change your answer for the question above?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p flag.s -a bx=2,bx=2 -M flag -R ax,bx -c -C
ARG seed 0
ARG numthreads 2
ARG program flag.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched
ARG argv bx=2,bx=2
ARG load address 1000
ARG memsize 128
ARG memtrace flag
ARG regtrace ax,bx
ARG cctrace True
ARG printstats False
ARG verbose False


 flag      ax    bx   >= >  <= <  != ==        Thread 0                Thread 1

    0       0     2   0  0  0  0  0  0
    0       0     2   0  0  0  0  0  0  1000 mov  flag, %ax
    0       0     2   1  0  1  0  0  1  1001 test $0, %ax
    0       0     2   1  0  1  0  0  1  1002 jne  .acquire
    1       0     2   1  0  1  0  0  1  1003 mov  $1, flag
    1       0     2   1  0  1  0  0  1  1004 mov  count, %ax
    1       1     2   1  0  1  0  0  1  1005 add  $1, %ax
    1       1     2   1  0  1  0  0  1  1006 mov  %ax, count
    0       1     2   1  0  1  0  0  1  1007 mov  $0, flag
    0       1     1   1  0  1  0  0  1  1008 sub  $1, %bx
    0       1     1   1  1  0  0  1  0  1009 test $0, %bx
    0       1     1   1  1  0  0  1  0  1010 jgt .top
    0       0     1   1  1  0  0  1  0  1000 mov  flag, %ax
    0       0     1   1  0  1  0  0  1  1001 test $0, %ax
    0       0     1   1  0  1  0  0  1  1002 jne  .acquire
    1       0     1   1  0  1  0  0  1  1003 mov  $1, flag
    1       1     1   1  0  1  0  0  1  1004 mov  count, %ax
    1       2     1   1  0  1  0  0  1  1005 add  $1, %ax
    1       2     1   1  0  1  0  0  1  1006 mov  %ax, count
    0       2     1   1  0  1  0  0  1  1007 mov  $0, flag
    0       2     0   1  0  1  0  0  1  1008 sub  $1, %bx
    0       2     0   1  0  1  0  0  1  1009 test $0, %bx
    0       2     0   1  0  1  0  0  1  1010 jgt .top
    0       2     0   1  0  1  0  0  1  1011 halt
    0       0     2   0  0  0  0  0  0  ----- Halt;Switch -----  ----- Halt;Switch -----
    0       0     2   0  0  0  0  0  0                           1000 mov  flag, %ax
    0       0     2   1  0  1  0  0  1                           1001 test $0, %ax
    0       0     2   1  0  1  0  0  1                           1002 jne  .acquire
    1       0     2   1  0  1  0  0  1                           1003 mov  $1, flag
    1       2     2   1  0  1  0  0  1                           1004 mov  count, %ax
    1       3     2   1  0  1  0  0  1                           1005 add  $1, %ax
    1       3     2   1  0  1  0  0  1                           1006 mov  %ax, count
    0       3     2   1  0  1  0  0  1                           1007 mov  $0, flag
    0       3     1   1  0  1  0  0  1                           1008 sub  $1, %bx
    0       3     1   1  1  0  0  1  0                           1009 test $0, %bx
    0       3     1   1  1  0  0  1  0                           1010 jgt .top
    0       0     1   1  1  0  0  1  0                           1000 mov  flag, %ax
    0       0     1   1  0  1  0  0  1                           1001 test $0, %ax
    0       0     1   1  0  1  0  0  1                           1002 jne  .acquire
    1       0     1   1  0  1  0  0  1                           1003 mov  $1, flag
    1       3     1   1  0  1  0  0  1                           1004 mov  count, %ax
    1       4     1   1  0  1  0  0  1                           1005 add  $1, %ax
    1       4     1   1  0  1  0  0  1                           1006 mov  %ax, count
    0       4     1   1  0  1  0  0  1                           1007 mov  $0, flag
    0       4     0   1  0  1  0  0  1                           1008 sub  $1, %bx
    0       4     0   1  0  1  0  0  1                           1009 test $0, %bx
    0       4     0   1  0  1  0  0  1                           1010 jgt .top
    0       4     0   1  0  1  0  0  1                           1011 halt
```

### 4.    Set bx to a high value for each thread, and then use the -i flag to generate different interrupt frequencies; what values lead to a bad outcomes? Which lead to good outcomes?
```
less than 10 will generate the bad result, two thread all get lock
```

### 5.    Now let’s look at the program test-and-set.s. First, try to understand the code, which uses the xchg instruction to build a simple locking primitive. How is the lock acquire written? How about lock release?
```
test and set in one line
```

### 6.    Now run the code, changing the value of the interrupt interval (-i) again, and making sure to loop for a number of times. Does the code always work as expected? Does it sometimes lead to an inefficient use of the CPU? How could you quantify that?
```
yes
```

### 7.    Use the -P flag to generate specific tests of the locking code. For example, run a schedule that grabs the lock in the first thread, but then tries to acquire it in the second. Does the right thing happen? What else should you test?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p test-and-set.s -M mutex,count -R ax,bx -c -a bx=10,bx=10 -P 0011 -C
ARG seed 0
ARG numthreads 2
ARG program test-and-set.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched 0011
ARG argv bx=10,bx=10
ARG load address 1000
ARG memsize 128
ARG memtrace mutex,count
ARG regtrace ax,bx
ARG cctrace True
ARG printstats False
ARG verbose False


mutex count      ax    bx   >= >  <= <  != ==        Thread 0                Thread 1

    0     0       0    10   0  0  0  0  0  0
    0     0       1    10   0  0  0  0  0  0  1000 mov  $1, %ax
    1     0       0    10   0  0  0  0  0  0  1001 xchg %ax, mutex
    1     0       0    10   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------  
    1     0       1    10   0  0  0  0  0  0                           1000 mov  $1, %ax
    1     0       1    10   0  0  0  0  0  0                           1001 xchg %ax, mutex
    1     0       0    10   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1     0       0    10   1  0  1  0  0  1  1002 test $0, %ax
    1     0       0    10   1  0  1  0  0  1  1003 jne  .acquire
    1     0       1    10   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    1     0       1    10   1  1  0  0  1  0                           1002 test $0, %ax
    1     0       1    10   1  1  0  0  1  0                           1003 jne  .acquire
    1     0       0    10   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     0       0    10   1  0  1  0  0  1  1004 mov  count, %ax
    1     0       1    10   1  0  1  0  0  1  1005 add  $1, %ax
    1     0       1    10   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     0       1    10   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     0       1    10   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     0       1    10   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     1       1    10   1  0  1  0  0  1  1006 mov  %ax, count
    0     1       1    10   1  0  1  0  0  1  1007 mov  $0, mutex
    0     1       1    10   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     1       1    10   1  1  0  0  1  0                           1002 test $0, %ax
    0     1       1    10   1  1  0  0  1  0                           1003 jne  .acquire
    0     1       1    10   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     1       1     9   1  0  1  0  0  1  1008 sub  $1, %bx
    0     1       1     9   1  1  0  0  1  0  1009 test $0, %bx
    0     1       1    10   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     1       1    10   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     1       0    10   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     1       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     1       1     9   1  1  0  0  1  0  1010 jgt .top
    1     1       1     9   1  1  0  0  1  0  1000 mov  $1, %ax
    1     1       0    10   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     1       0    10   1  0  1  0  0  1                           1002 test $0, %ax
    1     1       0    10   1  0  1  0  0  1                           1003 jne  .acquire
    1     1       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     1       1     9   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     1       1     9   1  1  0  0  1  0  1002 test $0, %ax
    1     1       0    10   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     1       1    10   1  0  1  0  0  1                           1004 mov  count, %ax
    1     1       2    10   1  0  1  0  0  1                           1005 add  $1, %ax
    1     1       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     1       1     9   1  1  0  0  1  0  1003 jne  .acquire
    1     1       1     9   1  1  0  0  1  0  1000 mov  $1, %ax
    1     1       2    10   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     2       2    10   1  0  1  0  0  1                           1006 mov  %ax, count
    0     2       2    10   1  0  1  0  0  1                           1007 mov  $0, mutex
    0     2       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     2       0     9   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     2       0     9   1  0  1  0  0  1  1002 test $0, %ax
    1     2       2    10   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     2       2     9   1  0  1  0  0  1                           1008 sub  $1, %bx
    1     2       2     9   1  1  0  0  1  0                           1009 test $0, %bx
    1     2       0     9   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     2       0     9   1  0  1  0  0  1  1003 jne  .acquire
    1     2       2     9   1  0  1  0  0  1  1004 mov  count, %ax
    1     2       2     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     2       2     9   1  1  0  0  1  0                           1010 jgt .top
    1     2       1     9   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     2       2     9   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     2       3     9   1  0  1  0  0  1  1005 add  $1, %ax
    1     3       3     9   1  0  1  0  0  1  1006 mov  %ax, count
    1     3       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     3       1     9   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     3       1     9   1  1  0  0  1  0                           1002 test $0, %ax
    1     3       3     9   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     3       3     9   1  0  1  0  0  1  1007 mov  $0, mutex
    0     3       3     8   1  0  1  0  0  1  1008 sub  $1, %bx
    0     3       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     3       1     9   1  1  0  0  1  0                           1003 jne  .acquire
    0     3       1     9   1  1  0  0  1  0                           1000 mov  $1, %ax
    0     3       3     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     3       3     8   1  1  0  0  1  0  1009 test $0, %bx
    0     3       3     8   1  1  0  0  1  0  1010 jgt .top
    0     3       1     9   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     3       0     9   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     3       0     9   1  0  1  0  0  1                           1002 test $0, %ax
    1     3       3     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------  
    1     3       1     8   1  1  0  0  1  0  1000 mov  $1, %ax
    1     3       1     8   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     3       0     9   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     3       0     9   1  0  1  0  0  1                           1003 jne  .acquire
    1     3       3     9   1  0  1  0  0  1                           1004 mov  count, %ax
    1     3       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     3       1     8   1  1  0  0  1  0  1002 test $0, %ax
    1     3       1     8   1  1  0  0  1  0  1003 jne  .acquire
    1     3       3     9   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     3       4     9   1  0  1  0  0  1                           1005 add  $1, %ax
    1     4       4     9   1  0  1  0  0  1                           1006 mov  %ax, count
    1     4       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     4       1     8   1  1  0  0  1  0  1000 mov  $1, %ax
    1     4       1     8   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     4       4     9   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     4       4     9   1  0  1  0  0  1                           1007 mov  $0, mutex
    0     4       4     8   1  0  1  0  0  1                           1008 sub  $1, %bx
    0     4       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     4       1     8   1  1  0  0  1  0  1002 test $0, %ax
    0     4       1     8   1  1  0  0  1  0  1003 jne  .acquire
    0     4       4     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     4       4     8   1  1  0  0  1  0                           1009 test $0, %bx
    0     4       4     8   1  1  0  0  1  0                           1010 jgt .top
    0     4       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     4       1     8   1  1  0  0  1  0  1000 mov  $1, %ax
    1     4       0     8   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     4       4     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     4       1     8   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     4       1     8   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     4       0     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     4       0     8   1  0  1  0  0  1  1002 test $0, %ax
    1     4       0     8   1  0  1  0  0  1  1003 jne  .acquire
    1     4       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     4       1     8   1  1  0  0  1  0                           1002 test $0, %ax
    1     4       1     8   1  1  0  0  1  0                           1003 jne  .acquire
    1     4       0     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     4       4     8   1  0  1  0  0  1  1004 mov  count, %ax
    1     4       5     8   1  0  1  0  0  1  1005 add  $1, %ax
    1     4       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     4       1     8   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     4       1     8   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     4       5     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     5       5     8   1  0  1  0  0  1  1006 mov  %ax, count
    0     5       5     8   1  0  1  0  0  1  1007 mov  $0, mutex
    0     5       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     5       1     8   1  1  0  0  1  0                           1002 test $0, %ax
    0     5       1     8   1  1  0  0  1  0                           1003 jne  .acquire
    0     5       5     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     5       5     7   1  0  1  0  0  1  1008 sub  $1, %bx
    0     5       5     7   1  1  0  0  1  0  1009 test $0, %bx
    0     5       1     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     5       1     8   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     5       0     8   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     5       5     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     5       5     7   1  1  0  0  1  0  1010 jgt .top
    1     5       1     7   1  1  0  0  1  0  1000 mov  $1, %ax
    1     5       0     8   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     5       0     8   1  0  1  0  0  1                           1002 test $0, %ax
    1     5       0     8   1  0  1  0  0  1                           1003 jne  .acquire
    1     5       1     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     5       1     7   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     5       1     7   1  1  0  0  1  0  1002 test $0, %ax
    1     5       0     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     5       5     8   1  0  1  0  0  1                           1004 mov  count, %ax
    1     5       6     8   1  0  1  0  0  1                           1005 add  $1, %ax
    1     5       1     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     5       1     7   1  1  0  0  1  0  1003 jne  .acquire
    1     5       1     7   1  1  0  0  1  0  1000 mov  $1, %ax
    1     5       6     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     6       6     8   1  0  1  0  0  1                           1006 mov  %ax, count
    0     6       6     8   1  0  1  0  0  1                           1007 mov  $0, mutex
    0     6       1     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     6       0     7   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     6       0     7   1  0  1  0  0  1  1002 test $0, %ax
    1     6       6     8   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     6       6     7   1  0  1  0  0  1                           1008 sub  $1, %bx
    1     6       6     7   1  1  0  0  1  0                           1009 test $0, %bx
    1     6       0     7   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     6       0     7   1  0  1  0  0  1  1003 jne  .acquire
    1     6       6     7   1  0  1  0  0  1  1004 mov  count, %ax
    1     6       6     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     6       6     7   1  1  0  0  1  0                           1010 jgt .top
    1     6       1     7   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     6       6     7   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     6       7     7   1  0  1  0  0  1  1005 add  $1, %ax
    1     7       7     7   1  0  1  0  0  1  1006 mov  %ax, count
    1     7       1     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     7       1     7   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     7       1     7   1  1  0  0  1  0                           1002 test $0, %ax
    1     7       7     7   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     7       7     7   1  0  1  0  0  1  1007 mov  $0, mutex
    0     7       7     6   1  0  1  0  0  1  1008 sub  $1, %bx
    0     7       1     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     7       1     7   1  1  0  0  1  0                           1003 jne  .acquire
    0     7       1     7   1  1  0  0  1  0                           1000 mov  $1, %ax
    0     7       7     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     7       7     6   1  1  0  0  1  0  1009 test $0, %bx
    0     7       7     6   1  1  0  0  1  0  1010 jgt .top
    0     7       1     7   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     7       0     7   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     7       0     7   1  0  1  0  0  1                           1002 test $0, %ax
    1     7       7     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     7       1     6   1  1  0  0  1  0  1000 mov  $1, %ax
    1     7       1     6   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     7       0     7   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     7       0     7   1  0  1  0  0  1                           1003 jne  .acquire
    1     7       7     7   1  0  1  0  0  1                           1004 mov  count, %ax
    1     7       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     7       1     6   1  1  0  0  1  0  1002 test $0, %ax
    1     7       1     6   1  1  0  0  1  0  1003 jne  .acquire
    1     7       7     7   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     7       8     7   1  0  1  0  0  1                           1005 add  $1, %ax
    1     8       8     7   1  0  1  0  0  1                           1006 mov  %ax, count
    1     8       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     8       1     6   1  1  0  0  1  0  1000 mov  $1, %ax
    1     8       1     6   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     8       8     7   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     8       8     7   1  0  1  0  0  1                           1007 mov  $0, mutex
    0     8       8     6   1  0  1  0  0  1                           1008 sub  $1, %bx
    0     8       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     8       1     6   1  1  0  0  1  0  1002 test $0, %ax
    0     8       1     6   1  1  0  0  1  0  1003 jne  .acquire
    0     8       8     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     8       8     6   1  1  0  0  1  0                           1009 test $0, %bx
    0     8       8     6   1  1  0  0  1  0                           1010 jgt .top
    0     8       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     8       1     6   1  1  0  0  1  0  1000 mov  $1, %ax
    1     8       0     6   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     8       8     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     8       1     6   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     8       1     6   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     8       0     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     8       0     6   1  0  1  0  0  1  1002 test $0, %ax
    1     8       0     6   1  0  1  0  0  1  1003 jne  .acquire
    1     8       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     8       1     6   1  1  0  0  1  0                           1002 test $0, %ax
    1     8       1     6   1  1  0  0  1  0                           1003 jne  .acquire
    1     8       0     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     8       8     6   1  0  1  0  0  1  1004 mov  count, %ax
    1     8       9     6   1  0  1  0  0  1  1005 add  $1, %ax
    1     8       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     8       1     6   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     8       1     6   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     8       9     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     9       9     6   1  0  1  0  0  1  1006 mov  %ax, count
    0     9       9     6   1  0  1  0  0  1  1007 mov  $0, mutex
    0     9       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     9       1     6   1  1  0  0  1  0                           1002 test $0, %ax
    0     9       1     6   1  1  0  0  1  0                           1003 jne  .acquire
    0     9       9     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     9       9     5   1  0  1  0  0  1  1008 sub  $1, %bx
    0     9       9     5   1  1  0  0  1  0  1009 test $0, %bx
    0     9       1     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0     9       1     6   1  1  0  0  1  0                           1000 mov  $1, %ax
    1     9       0     6   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1     9       9     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     9       9     5   1  1  0  0  1  0  1010 jgt .top
    1     9       1     5   1  1  0  0  1  0  1000 mov  $1, %ax
    1     9       0     6   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     9       0     6   1  0  1  0  0  1                           1002 test $0, %ax
    1     9       0     6   1  0  1  0  0  1                           1003 jne  .acquire
    1     9       1     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     9       1     5   1  1  0  0  1  0  1001 xchg %ax, mutex
    1     9       1     5   1  1  0  0  1  0  1002 test $0, %ax
    1     9       0     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1     9       9     6   1  0  1  0  0  1                           1004 mov  count, %ax
    1     9      10     6   1  0  1  0  0  1                           1005 add  $1, %ax
    1     9       1     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     9       1     5   1  1  0  0  1  0  1003 jne  .acquire
    1     9       1     5   1  1  0  0  1  0  1000 mov  $1, %ax
    1     9      10     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    10      10     6   1  0  1  0  0  1                           1006 mov  %ax, count
    0    10      10     6   1  0  1  0  0  1                           1007 mov  $0, mutex
    0    10       1     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    10       0     5   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    10       0     5   1  0  1  0  0  1  1002 test $0, %ax
    1    10      10     6   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    10      10     5   1  0  1  0  0  1                           1008 sub  $1, %bx
    1    10      10     5   1  1  0  0  1  0                           1009 test $0, %bx
    1    10       0     5   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    10       0     5   1  0  1  0  0  1  1003 jne  .acquire
    1    10      10     5   1  0  1  0  0  1  1004 mov  count, %ax
    1    10      10     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    10      10     5   1  1  0  0  1  0                           1010 jgt .top
    1    10       1     5   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    10      10     5   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    10      11     5   1  0  1  0  0  1  1005 add  $1, %ax
    1    11      11     5   1  0  1  0  0  1  1006 mov  %ax, count
    1    11       1     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    11       1     5   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    11       1     5   1  1  0  0  1  0                           1002 test $0, %ax
    1    11      11     5   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    11      11     5   1  0  1  0  0  1  1007 mov  $0, mutex
    0    11      11     4   1  0  1  0  0  1  1008 sub  $1, %bx
    0    11       1     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    11       1     5   1  1  0  0  1  0                           1003 jne  .acquire
    0    11       1     5   1  1  0  0  1  0                           1000 mov  $1, %ax
    0    11      11     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------  
    0    11      11     4   1  1  0  0  1  0  1009 test $0, %bx
    0    11      11     4   1  1  0  0  1  0  1010 jgt .top
    0    11       1     5   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    11       0     5   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    11       0     5   1  0  1  0  0  1                           1002 test $0, %ax
    1    11      11     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    11       1     4   1  1  0  0  1  0  1000 mov  $1, %ax
    1    11       1     4   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    11       0     5   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    11       0     5   1  0  1  0  0  1                           1003 jne  .acquire
    1    11      11     5   1  0  1  0  0  1                           1004 mov  count, %ax
    1    11       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    11       1     4   1  1  0  0  1  0  1002 test $0, %ax
    1    11       1     4   1  1  0  0  1  0  1003 jne  .acquire
    1    11      11     5   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    11      12     5   1  0  1  0  0  1                           1005 add  $1, %ax
    1    12      12     5   1  0  1  0  0  1                           1006 mov  %ax, count
    1    12       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    12       1     4   1  1  0  0  1  0  1000 mov  $1, %ax
    1    12       1     4   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    12      12     5   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    12      12     5   1  0  1  0  0  1                           1007 mov  $0, mutex
    0    12      12     4   1  0  1  0  0  1                           1008 sub  $1, %bx
    0    12       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    12       1     4   1  1  0  0  1  0  1002 test $0, %ax
    0    12       1     4   1  1  0  0  1  0  1003 jne  .acquire
    0    12      12     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    12      12     4   1  1  0  0  1  0                           1009 test $0, %bx
    0    12      12     4   1  1  0  0  1  0                           1010 jgt .top
    0    12       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    12       1     4   1  1  0  0  1  0  1000 mov  $1, %ax
    1    12       0     4   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    12      12     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    12       1     4   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    12       1     4   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    12       0     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    12       0     4   1  0  1  0  0  1  1002 test $0, %ax
    1    12       0     4   1  0  1  0  0  1  1003 jne  .acquire
    1    12       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    12       1     4   1  1  0  0  1  0                           1002 test $0, %ax
    1    12       1     4   1  1  0  0  1  0                           1003 jne  .acquire
    1    12       0     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    12      12     4   1  0  1  0  0  1  1004 mov  count, %ax
    1    12      13     4   1  0  1  0  0  1  1005 add  $1, %ax
    1    12       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    12       1     4   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    12       1     4   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    12      13     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    13      13     4   1  0  1  0  0  1  1006 mov  %ax, count
    0    13      13     4   1  0  1  0  0  1  1007 mov  $0, mutex
    0    13       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    13       1     4   1  1  0  0  1  0                           1002 test $0, %ax
    0    13       1     4   1  1  0  0  1  0                           1003 jne  .acquire
    0    13      13     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    13      13     3   1  0  1  0  0  1  1008 sub  $1, %bx
    0    13      13     3   1  1  0  0  1  0  1009 test $0, %bx
    0    13       1     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    13       1     4   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    13       0     4   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    13      13     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    13      13     3   1  1  0  0  1  0  1010 jgt .top
    1    13       1     3   1  1  0  0  1  0  1000 mov  $1, %ax
    1    13       0     4   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    13       0     4   1  0  1  0  0  1                           1002 test $0, %ax
    1    13       0     4   1  0  1  0  0  1                           1003 jne  .acquire
    1    13       1     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    13       1     3   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    13       1     3   1  1  0  0  1  0  1002 test $0, %ax
    1    13       0     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    13      13     4   1  0  1  0  0  1                           1004 mov  count, %ax
    1    13      14     4   1  0  1  0  0  1                           1005 add  $1, %ax
    1    13       1     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------  
    1    13       1     3   1  1  0  0  1  0  1003 jne  .acquire
    1    13       1     3   1  1  0  0  1  0  1000 mov  $1, %ax
    1    13      14     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    14      14     4   1  0  1  0  0  1                           1006 mov  %ax, count
    0    14      14     4   1  0  1  0  0  1                           1007 mov  $0, mutex
    0    14       1     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    14       0     3   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    14       0     3   1  0  1  0  0  1  1002 test $0, %ax
    1    14      14     4   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    14      14     3   1  0  1  0  0  1                           1008 sub  $1, %bx
    1    14      14     3   1  1  0  0  1  0                           1009 test $0, %bx
    1    14       0     3   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    14       0     3   1  0  1  0  0  1  1003 jne  .acquire
    1    14      14     3   1  0  1  0  0  1  1004 mov  count, %ax
    1    14      14     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    14      14     3   1  1  0  0  1  0                           1010 jgt .top
    1    14       1     3   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    14      14     3   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    14      15     3   1  0  1  0  0  1  1005 add  $1, %ax
    1    15      15     3   1  0  1  0  0  1  1006 mov  %ax, count
    1    15       1     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    15       1     3   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    15       1     3   1  1  0  0  1  0                           1002 test $0, %ax
    1    15      15     3   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    15      15     3   1  0  1  0  0  1  1007 mov  $0, mutex
    0    15      15     2   1  0  1  0  0  1  1008 sub  $1, %bx
    0    15       1     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    15       1     3   1  1  0  0  1  0                           1003 jne  .acquire
    0    15       1     3   1  1  0  0  1  0                           1000 mov  $1, %ax
    0    15      15     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    15      15     2   1  1  0  0  1  0  1009 test $0, %bx
    0    15      15     2   1  1  0  0  1  0  1010 jgt .top
    0    15       1     3   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    15       0     3   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    15       0     3   1  0  1  0  0  1                           1002 test $0, %ax
    1    15      15     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    15       1     2   1  1  0  0  1  0  1000 mov  $1, %ax
    1    15       1     2   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    15       0     3   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    15       0     3   1  0  1  0  0  1                           1003 jne  .acquire
    1    15      15     3   1  0  1  0  0  1                           1004 mov  count, %ax
    1    15       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    15       1     2   1  1  0  0  1  0  1002 test $0, %ax
    1    15       1     2   1  1  0  0  1  0  1003 jne  .acquire
    1    15      15     3   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    15      16     3   1  0  1  0  0  1                           1005 add  $1, %ax
    1    16      16     3   1  0  1  0  0  1                           1006 mov  %ax, count
    1    16       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    16       1     2   1  1  0  0  1  0  1000 mov  $1, %ax
    1    16       1     2   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    16      16     3   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    16      16     3   1  0  1  0  0  1                           1007 mov  $0, mutex
    0    16      16     2   1  0  1  0  0  1                           1008 sub  $1, %bx
    0    16       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    16       1     2   1  1  0  0  1  0  1002 test $0, %ax
    0    16       1     2   1  1  0  0  1  0  1003 jne  .acquire
    0    16      16     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    16      16     2   1  1  0  0  1  0                           1009 test $0, %bx
    0    16      16     2   1  1  0  0  1  0                           1010 jgt .top
    0    16       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    16       1     2   1  1  0  0  1  0  1000 mov  $1, %ax
    1    16       0     2   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    16      16     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    16       1     2   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    16       1     2   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    16       0     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    16       0     2   1  0  1  0  0  1  1002 test $0, %ax
    1    16       0     2   1  0  1  0  0  1  1003 jne  .acquire
    1    16       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    16       1     2   1  1  0  0  1  0                           1002 test $0, %ax
    1    16       1     2   1  1  0  0  1  0                           1003 jne  .acquire
    1    16       0     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    16      16     2   1  0  1  0  0  1  1004 mov  count, %ax
    1    16      17     2   1  0  1  0  0  1  1005 add  $1, %ax
    1    16       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    16       1     2   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    16       1     2   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    16      17     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    17      17     2   1  0  1  0  0  1  1006 mov  %ax, count
    0    17      17     2   1  0  1  0  0  1  1007 mov  $0, mutex
    0    17       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    17       1     2   1  1  0  0  1  0                           1002 test $0, %ax
    0    17       1     2   1  1  0  0  1  0                           1003 jne  .acquire
    0    17      17     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    17      17     1   1  0  1  0  0  1  1008 sub  $1, %bx
    0    17      17     1   1  1  0  0  1  0  1009 test $0, %bx
    0    17       1     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    17       1     2   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    17       0     2   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    17      17     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    17      17     1   1  1  0  0  1  0  1010 jgt .top
    1    17       1     1   1  1  0  0  1  0  1000 mov  $1, %ax
    1    17       0     2   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    17       0     2   1  0  1  0  0  1                           1002 test $0, %ax
    1    17       0     2   1  0  1  0  0  1                           1003 jne  .acquire
    1    17       1     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    17       1     1   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    17       1     1   1  1  0  0  1  0  1002 test $0, %ax
    1    17       0     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    17      17     2   1  0  1  0  0  1                           1004 mov  count, %ax
    1    17      18     2   1  0  1  0  0  1                           1005 add  $1, %ax
    1    17       1     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    17       1     1   1  1  0  0  1  0  1003 jne  .acquire
    1    17       1     1   1  1  0  0  1  0  1000 mov  $1, %ax
    1    17      18     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    18      18     2   1  0  1  0  0  1                           1006 mov  %ax, count
    0    18      18     2   1  0  1  0  0  1                           1007 mov  $0, mutex
    0    18       1     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    18       0     1   1  1  0  0  1  0  1001 xchg %ax, mutex
    1    18       0     1   1  0  1  0  0  1  1002 test $0, %ax
    1    18      18     2   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    18      18     1   1  0  1  0  0  1                           1008 sub  $1, %bx
    1    18      18     1   1  1  0  0  1  0                           1009 test $0, %bx
    1    18       0     1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    18       0     1   1  0  1  0  0  1  1003 jne  .acquire
    1    18      18     1   1  0  1  0  0  1  1004 mov  count, %ax
    1    18      18     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    18      18     1   1  1  0  0  1  0                           1010 jgt .top
    1    18       1     1   1  1  0  0  1  0                           1000 mov  $1, %ax
    1    18      18     1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    18      19     1   1  0  1  0  0  1  1005 add  $1, %ax
    1    19      19     1   1  0  1  0  0  1  1006 mov  %ax, count
    1    19       1     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    19       1     1   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    19       1     1   1  1  0  0  1  0                           1002 test $0, %ax
    1    19      19     1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    19      19     1   1  0  1  0  0  1  1007 mov  $0, mutex
    0    19      19     0   1  0  1  0  0  1  1008 sub  $1, %bx
    0    19       1     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    0    19       1     1   1  1  0  0  1  0                           1003 jne  .acquire
    0    19       1     1   1  1  0  0  1  0                           1000 mov  $1, %ax
    0    19      19     0   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0    19      19     0   1  0  1  0  0  1  1009 test $0, %bx
    0    19      19     0   1  0  1  0  0  1  1010 jgt .top
    0    19       1     1   1  1  0  0  1  0  ------ Interrupt ------  ------ Interrupt ------
    1    19       0     1   1  1  0  0  1  0                           1001 xchg %ax, mutex
    1    19       0     1   1  0  1  0  0  1                           1002 test $0, %ax
    1    19      19     0   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    1    19      19     0   1  0  1  0  0  1  1011 halt
    1    19       0     1   1  0  1  0  0  1  ----- Halt;Switch -----  ----- Halt;Switch -----
    1    19       0     1   1  0  1  0  0  1                           1003 jne  .acquire
    1    19      19     1   1  0  1  0  0  1                           1004 mov  count, %ax
    1    19      20     1   1  0  1  0  0  1                           1005 add  $1, %ax
    1    20      20     1   1  0  1  0  0  1                           1006 mov  %ax, count
    0    20      20     1   1  0  1  0  0  1                           1007 mov  $0, mutex
    0    20      20     0   1  0  1  0  0  1                           1008 sub  $1, %bx
    0    20      20     0   1  0  1  0  0  1                           1009 test $0, %bx
    0    20      20     0   1  0  1  0  0  1                           1010 jgt .top
    0    20      20     0   1  0  1  0  0  1                           1011 halt

```
### 8.    Now let’s look at the code in peterson.s, which implements Peterson’s algorithm (mentioned in a sidebar in the text). Study the code and see if you can make sense of it.
```
yes
```

### 9.     Now run the code with different values of -i. What kinds of different behavior do you see? Make sure to set the thread IDs appropriately (using -a bx=0,bx=1 for example) as the code assumes it.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p peterson.s -c -C                                                   
ARG seed 0
ARG numthreads 2
ARG program peterson.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched
ARG argv
ARG load address 1000
ARG memsize 128
ARG memtrace
ARG regtrace
ARG cctrace True
ARG printstats False
ARG verbose False


>= >  <= <  != ==        Thread 0                Thread 1

0  0  0  0  0  0
0  0  0  0  0  0  1000 lea flag, %fx
0  0  0  0  0  0  1001 mov %bx, %cx
0  0  0  0  0  0  1002 neg %cx
0  0  0  0  0  0  1003 add $1, %cx
0  0  0  0  0  0  1004 mov $1, 0(%fx,%bx,4)
0  0  0  0  0  0  1005 mov %cx, turn
0  0  0  0  0  0  1006 mov 0(%fx,%cx,4), %ax
0  0  1  1  1  0  1007 test $1, %ax
0  0  1  1  1  0  1008 jne .fini
0  0  1  1  1  0  1012 mov count, %ax
0  0  1  1  1  0  1013 add $1, %ax
0  0  1  1  1  0  1014 mov %ax, count
0  0  1  1  1  0  1015 mov $0, 0(%fx,%bx,4)
0  0  1  1  1  0  1016 mov %cx, turn
0  0  1  1  1  0  1017 halt
0  0  0  0  0  0  ----- Halt;Switch -----  ----- Halt;Switch -----
0  0  0  0  0  0                           1000 lea flag, %fx
0  0  0  0  0  0                           1001 mov %bx, %cx
0  0  0  0  0  0                           1002 neg %cx
0  0  0  0  0  0                           1003 add $1, %cx
0  0  0  0  0  0                           1004 mov $1, 0(%fx,%bx,4)
0  0  0  0  0  0                           1005 mov %cx, turn
0  0  0  0  0  0                           1006 mov 0(%fx,%cx,4), %ax
0  0  1  1  1  0                           1007 test $1, %ax
0  0  1  1  1  0                           1008 jne .fini
0  0  1  1  1  0                           1012 mov count, %ax
0  0  1  1  1  0                           1013 add $1, %ax
0  0  1  1  1  0                           1014 mov %ax, count
0  0  1  1  1  0                           1015 mov $0, 0(%fx,%bx,4)
0  0  1  1  1  0                           1016 mov %cx, turn
0  0  1  1  1  0                           1017 halt
```

### 10.     Can you control the scheduling (with the -P flag) to “prove” that the code works? What are the different cases you should show hold? Think about mutual exclusion and deadlock avoidance.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python x86.py -p peterson.s -M count,flag,turn -R ax,cx -a bx=0,bx=1 -c -P 0000011111 -C
ARG seed 0
ARG numthreads 2
ARG program peterson.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched 0000011111
ARG argv bx=0,bx=1
ARG load address 1000
ARG memsize 128
ARG memtrace count,flag,turn
ARG regtrace ax,cx
ARG cctrace True
ARG printstats False
ARG verbose False


count  flag  turn      ax    cx   >= >  <= <  != ==        Thread 0                Thread 1

    0     0     0       0     0   0  0  0  0  0  0
    0     0     0       0     0   0  0  0  0  0  0  1000 lea flag, %fx
    0     0     0       0     0   0  0  0  0  0  0  1001 mov %bx, %cx
    0     0     0       0     0   0  0  0  0  0  0  1002 neg %cx
    0     0     0       0     1   0  0  0  0  0  0  1003 add $1, %cx
    0     1     0       0     1   0  0  0  0  0  0  1004 mov $1, 0(%fx,%bx,4)
    0     1     0       0     0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0     1     0       0     0   0  0  0  0  0  0                           1000 lea flag, %fx
    0     1     0       0     1   0  0  0  0  0  0                           1001 mov %bx, %cx
    0     1     0       0    -1   0  0  0  0  0  0                           1002 neg %cx
    0     1     0       0     0   0  0  0  0  0  0                           1003 add $1, %cx
    0     1     0       0     0   0  0  0  0  0  0                           1004 mov $1, 0(%fx,%bx,4)
    0     1     0       0     1   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0     1     1       0     1   0  0  0  0  0  0  1005 mov %cx, turn
    0     1     1       1     1   0  0  0  0  0  0  1006 mov 0(%fx,%cx,4), %ax
    0     1     1       1     1   1  0  1  0  0  1  1007 test $1, %ax
    0     1     1       1     1   1  0  1  0  0  1  1008 jne .fini
    0     1     1       1     1   1  0  1  0  0  1  1009 mov turn, %ax
    0     1     1       0     0   0  0  0  0  0  0  ------ Interrupt ------  ------ Interrupt ------
    0     1     0       0     0   0  0  0  0  0  0                           1005 mov %cx, turn
    0     1     0       1     0   0  0  0  0  0  0                           1006 mov 0(%fx,%cx,4), %ax
    0     1     0       1     0   1  0  1  0  0  1                           1007 test $1, %ax
    0     1     0       1     0   1  0  1  0  0  1                           1008 jne .fini
    0     1     0       0     0   1  0  1  0  0  1                           1009 mov turn, %ax
    0     1     0       1     1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     1     0       1     1   1  0  1  0  0  1  1010 test %cx, %ax
    0     1     0       1     1   1  0  1  0  0  1  1011 je .spin1
    0     1     0       1     1   1  0  1  0  0  1  1006 mov 0(%fx,%cx,4), %ax
    0     1     0       1     1   1  0  1  0  0  1  1007 test $1, %ax
    0     1     0       1     1   1  0  1  0  0  1  1008 jne .fini
    0     1     0       0     0   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     1     0       0     0   1  0  1  0  0  1                           1010 test %cx, %ax
    0     1     0       0     0   1  0  1  0  0  1                           1011 je .spin1
    0     1     0       1     0   1  0  1  0  0  1                           1006 mov 0(%fx,%cx,4), %ax
    0     1     0       1     0   1  0  1  0  0  1                           1007 test $1, %ax
    0     1     0       1     0   1  0  1  0  0  1                           1008 jne .fini
    0     1     0       1     1   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     1     0       0     1   1  0  1  0  0  1  1009 mov turn, %ax
    0     1     0       0     1   0  0  1  1  1  0  1010 test %cx, %ax
    0     1     0       0     1   0  0  1  1  1  0  1011 je .spin1
    0     1     0       0     1   0  0  1  1  1  0  1012 mov count, %ax
    0     1     0       1     1   0  0  1  1  1  0  1013 add $1, %ax
    0     1     0       1     0   1  0  1  0  0  1  ------ Interrupt ------  ------ Interrupt ------
    0     1     0       0     0   1  0  1  0  0  1                           1009 mov turn, %ax
    0     1     0       0     0   1  0  1  0  0  1                           1010 test %cx, %ax
    0     1     0       0     0   1  0  1  0  0  1                           1011 je .spin1
    0     1     0       1     0   1  0  1  0  0  1                           1006 mov 0(%fx,%cx,4), %ax
    0     1     0       1     0   1  0  1  0  0  1                           1007 test $1, %ax
    0     1     0       1     1   0  0  1  1  1  0  ------ Interrupt ------  ------ Interrupt ------
    1     1     0       1     1   0  0  1  1  1  0  1014 mov %ax, count
    1     0     0       1     1   0  0  1  1  1  0  1015 mov $0, 0(%fx,%bx,4)
    1     0     1       1     1   0  0  1  1  1  0  1016 mov %cx, turn
    1     0     1       1     1   0  0  1  1  1  0  1017 halt
    1     0     1       1     0   1  0  1  0  0  1  ----- Halt;Switch -----  ----- Halt;Switch -----
    1     0     1       1     0   1  0  1  0  0  1                           1008 jne .fini
    1     0     1       1     0   1  0  1  0  0  1                           1009 mov turn, %ax
    1     0     1       1     0   1  1  0  0  1  0                           1010 test %cx, %ax
    1     0     1       1     0   1  1  0  0  1  0                           1011 je .spin1
    1     0     1       1     0   1  1  0  0  1  0                           1012 mov count, %ax
    1     0     1       2     0   1  1  0  0  1  0                           1013 add $1, %ax
    2     0     1       2     0   1  1  0  0  1  0                           1014 mov %ax, count
    2     0     1       2     0   1  1  0  0  1  0                           1015 mov $0, 0(%fx,%bx,4)
    2     0     0       2     0   1  1  0  0  1  0                           1016 mov %cx, turn
    2     0     0       2     0   1  1  0  0  1  0                           1017 halt

```

### 11.      Now study the code for the ticket lock in ticket.s. Does it match the code in the chapter? Then run with the following flags: -a bx=1000,bx=1000 (causing each thread to loop through the critical section 1000 times). Watch what happens; do the threads spend much time spin-waiting for the lock?
```
python x86.py -p ticket.s -M count,ticket,turn -R ax,bx,cx -a bx=1000,bx=1000 -c -C
```

### 12.      How does the code behave as you add more threads?
```
spin in tryagain loop
```

### 13.       Now examine yield.s, in which a yield instruction enables one thread to yield control of the CPU (realistically, this would be an OS primitive, but for the simplicity, we assume an instruction does the task). Find a scenario where test-and-set.s wastes cycles spinning, but yield.s does not. How many instructions are saved? In what scenarios do these savings arise?
```
python x86.py -p test-and-set.s -M count,mutex -R ax,bx -a bx=5,bx=5 -i 7 -c -C
python x86.py -p yield.s -M count,mutex -R ax,bx -a bx=5,bx=5 -i 7 -c -C
```

### 14.       Finally, examine test-and-test-and-set.s. What does this lock do? What kind of savings does it introduce as compared to test-and-set.s?
```
mutex is set to 1 only if lock is free

```
# Homework (Code)

### 1.   We’ll start by redoing the measurements within this chapter. Use the call gettimeofday() to measure time within your program. How accurate is this timer? What is the smallest interval it can measure? Gain confidence in its workings, as we will need it in all subsequent questions. You can also look into other timers, such as the cycle counter available on x86 via the rdtsc instruction.
```
#include "bits/stdc++.h"

using namespace std;
using namespace std::chrono;
int main(){
    vector<int> values(10000);
    auto f = []() -> int { return rand() % 10000; };
    generate(values.begin(), values.end(), f);
    auto start = high_resolution_clock::now();
    sort(values.begin(), values.end());
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    return 0;
}
```
### 2.   Now, build a simple concurrent counter and measure how long it takes to increment the counter many times as the number of threads increases. How many CPUs are available on the system you are using? Does this number impact your measurements at all?
```
#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;

struct counter{
    int count;
    mutex myMutex;
    counter(){
        count=0;
    }
};

void increment(counter* c){
    for(int i=0;i<1000000;i++){
        lock_guard<mutex> myLock(c->myMutex);
        c->count+=1;
    }

}

int main(){
    const auto cpus = std::thread::hardware_concurrency();
    for(int i=1;i<=cpus;i++){
        counter* c=new counter();
        vector<thread>lst;
        
        auto start = high_resolution_clock::now();
        for(int j=0;j<i;j++){
            lst.push_back(thread(increment,c));
        }
        for(int j=0;j<i;j++){
            lst[j].join();
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout<<"with "<<i<<" cpu in use, the time spend is "<<duration.count()<<" microseconds" << endl;
        cout<<"the counter now is "<<c->count<<endl;
        delete c;  
    }
    return 0;
}
```
### 3.    Next, build a version of the sloppy counter. Once again, measure its performance as the number of threads varies, as well as the threshold. Do the numbers match what you see in the chapter?
```
#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;

struct counter{
    int globle;
    mutex glock;
    vector<int>local;
    mutex llock;
    int threshold;
    counter(int threshold){
        this->globle=0;
        local=vector<int>(4,0);
        this->threshold=threshold;
    }
};

void increment(counter* c,int index){
    for(int i=0;i<1000000;i++){
        //lock_guard<mutex> myLock(c->llock);
        c->local[index]+=1;
        if(c->local[index] >= c->threshold){
            lock_guard<mutex> myLock(c->glock);
            c->globle+=c->local[index];
            c->local[index]=0;
        }
    }
    
    if(c->local[index]>0){
        lock_guard<mutex> myLock(c->glock);
        c->globle+=c->local[index];
        c->local[index]=0;

    }
}



int main(){
    counter* c1=new counter(999999);
    auto start1 = high_resolution_clock::now();
    thread t0(increment,c1,0);
    thread t1(increment,c1,1);
    thread t2(increment,c1,2);
    thread t3(increment,c1,3);

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    cout<<"the time spend is "<<duration1.count()<<" microseconds" << endl;
    cout<<"the counter now is "<<c1->globle<<endl;


    counter* c2=new counter(10);
    auto start2 = high_resolution_clock::now();
    for(int i=0;i<4000000;i++){
        c2->globle+=1;
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"the time spend is "<<duration2.count()<<" microseconds" << endl;
    cout<<"the counter now is "<<c2->globle<<endl;

    return 0;
}
```
### 4.     Build a version of a linked list that uses hand-over-hand locking [MS04], as cited in the chapter. You should read the paper first to understand how it works, and then implement it. Measure its performance. When does a hand-over-hand list work better than a standard list as shown in the chapter?
```

```