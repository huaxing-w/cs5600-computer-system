# Homework (Simulation)

### 1.  To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a run-time of 30, and a working-set size of 200. Run this job (called job ’a’ here) on one simulated CPU as follows: ./multi.py -n 1 -L a:30:200. How long will it take to complete? Turn on the -c flag to see a final answer, and the -t flag to see a tick-by-tick trace of the job and how it is scheduled.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 1 -L a:30:200 -c -t
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace True
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']

   0   a
   1   a
   2   a
   3   a
   4   a
   5   a
   6   a
   7   a
   8   a
   9   a
----------
  10   a
  11   a
  12   a
  13   a
  14   a
  15   a
  16   a
  17   a
  18   a
  19   a
----------
  20   a
  21   a
  22   a
  23   a
  24   a
  25   a
  26   a
  27   a
  28   a
  29   a

Finished time 30

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
```  

### 2.  Now increase the cache size so as to make the job’s working set (size=200) fit into the cache (which, by default, is size=100); for example, run ./multi.py -n 1 -L a:30:200 -M 300. Can you predict how fast the job will run once it fits in cache? (hint: remember the key parameter of the warm rate, which is set by the -r flag) Check your answer by running with the solve flag (-c) enabled.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 1 -L a:30:200 -M 300 -c -t
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 300
ARG random_order False
ARG trace True
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']

   0   a
   1   a
   2   a
   3   a
   4   a
   5   a
   6   a
   7   a
   8   a
   9   a
----------
  10   a
  11   a
  12   a
  13   a
  14   a
  15   a
  16   a
  17   a
  18   a
  19   a

Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]
```

### 3.  One cool thing about multi.py is that you can see more detail about what is going on with different tracing flags. Run the same simulation as above, but this time with time left tracing enabled (-T). This flag shows both the job that was scheduled on a CPU at each time step, as well as how much run-time that job has left after each tick has run. What do you notice about how that second column decreases?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 1 -L a:30:200 -M 300 -c -t -T
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 300
ARG random_order False
ARG trace True
ARG trace_time True
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']

   0   a [ 29]
   1   a [ 28]
   2   a [ 27]
   3   a [ 26]
   4   a [ 25]
   5   a [ 24]
   6   a [ 23]
   7   a [ 22]
   8   a [ 21]
   9   a [ 20]
----------------
  10   a [ 18]
  11   a [ 16]
  12   a [ 14]
  13   a [ 12]
  14   a [ 10]
  15   a [  8]
  16   a [  6]
  17   a [  4]
  18   a [  2]
  19   a [  0]

Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]
```
speed is 2X when using cache  











