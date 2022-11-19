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


