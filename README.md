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

### 4.  Now add one more bit of tracing, to show the status of each CPU cache for each job, with the -C flag. For each job, each cache will either show a blank space (if the cache is cold for that job) or a ’w’ (if the cache is warm for that job). At what point does the cache become warm for job ’a’ in this simple example? What happens as you change the warmup time parameter (-w) to lower or higher values than the default?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 1 -L a:30:200 -M 300 -c -t -T -C
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
ARG trace_cache True
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']

   0   a [ 29] cache[ ]
   1   a [ 28] cache[ ]
   2   a [ 27] cache[ ]
   3   a [ 26] cache[ ]
   4   a [ 25] cache[ ]
   5   a [ 24] cache[ ]
   6   a [ 23] cache[ ]
   7   a [ 22] cache[ ]
   8   a [ 21] cache[ ]
   9   a [ 20] cache[w]
-------------------------
  10   a [ 18] cache[w]
  11   a [ 16] cache[w]
  12   a [ 14] cache[w]
  13   a [ 12] cache[w]
  14   a [ 10] cache[w]
  15   a [  8] cache[w]
  16   a [  6] cache[w]
  17   a [  4] cache[w]
  18   a [  2] cache[w]
  19   a [  0] cache[w]

Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]

```

### 5.  At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t this a multi-processor CPU scheduling chapter? Oh yeah! So let’s start working with multiple jobs. Specifically, let’s run the following three jobs on a two-CPU system (i.e., type ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50) Can you predict how long this will take, given a round-robin centralized scheduler? Use -c to see if you were right, and then dive down into details with -t to see a step-by-step and then -C to see whether caches got warmed effectively for these jobs. What do you notice?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -c -t -T -C
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:50,c:100:50
ARG affinity 
ARG per_cpu_queues False
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace True
ARG trace_time True
ARG trace_cache True
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:50
Job name:c run_time:100 working_set_size:50

Scheduler central queue: ['a', 'b', 'c']

   0   a [ 99] cache[   ]     b [ 99] cache[   ]     
   1   a [ 98] cache[   ]     b [ 98] cache[   ]     
   2   a [ 97] cache[   ]     b [ 97] cache[   ]     
   3   a [ 96] cache[   ]     b [ 96] cache[   ]     
   4   a [ 95] cache[   ]     b [ 95] cache[   ]     
   5   a [ 94] cache[   ]     b [ 94] cache[   ]     
   6   a [ 93] cache[   ]     b [ 93] cache[   ]     
   7   a [ 92] cache[   ]     b [ 92] cache[   ]     
   8   a [ 91] cache[   ]     b [ 91] cache[   ]     
   9   a [ 90] cache[w  ]     b [ 90] cache[ w ]     
---------------------------------------------------
  10   c [ 99] cache[w  ]     a [ 89] cache[ w ]     
  11   c [ 98] cache[w  ]     a [ 88] cache[ w ]     
  12   c [ 97] cache[w  ]     a [ 87] cache[ w ]
  13   c [ 96] cache[w  ]     a [ 86] cache[ w ]
  14   c [ 95] cache[w  ]     a [ 85] cache[ w ]
  15   c [ 94] cache[w  ]     a [ 84] cache[ w ]
  16   c [ 93] cache[w  ]     a [ 83] cache[ w ]
  17   c [ 92] cache[w  ]     a [ 82] cache[ w ]
  18   c [ 91] cache[w  ]     a [ 81] cache[ w ]
  19   c [ 90] cache[  w]     a [ 80] cache[w  ]
---------------------------------------------------
  20   b [ 89] cache[  w]     c [ 89] cache[w  ]
  21   b [ 88] cache[  w]     c [ 88] cache[w  ]
  22   b [ 87] cache[  w]     c [ 87] cache[w  ]
  23   b [ 86] cache[  w]     c [ 86] cache[w  ]
  24   b [ 85] cache[  w]     c [ 85] cache[w  ]
  25   b [ 84] cache[  w]     c [ 84] cache[w  ]
  26   b [ 83] cache[  w]     c [ 83] cache[w  ]
  27   b [ 82] cache[  w]     c [ 82] cache[w  ]
  28   b [ 81] cache[  w]     c [ 81] cache[w  ]
  29   b [ 80] cache[ ww]     c [ 80] cache[  w]
---------------------------------------------------
  30   a [ 79] cache[ ww]     b [ 79] cache[  w]
  31   a [ 78] cache[ ww]     b [ 78] cache[  w]
  32   a [ 77] cache[ ww]     b [ 77] cache[  w]
  33   a [ 76] cache[ ww]     b [ 76] cache[  w]
  34   a [ 75] cache[ ww]     b [ 75] cache[  w]
  35   a [ 74] cache[ ww]     b [ 74] cache[  w]
  36   a [ 73] cache[ ww]     b [ 73] cache[  w]
  37   a [ 72] cache[ ww]     b [ 72] cache[  w]
  38   a [ 71] cache[ ww]     b [ 71] cache[  w]
  39   a [ 70] cache[w  ]     b [ 70] cache[ ww]
---------------------------------------------------
  40   c [ 79] cache[w  ]     a [ 69] cache[ ww]
  41   c [ 78] cache[w  ]     a [ 68] cache[ ww]
  42   c [ 77] cache[w  ]     a [ 67] cache[ ww]
  43   c [ 76] cache[w  ]     a [ 66] cache[ ww]
  44   c [ 75] cache[w  ]     a [ 65] cache[ ww]
  45   c [ 74] cache[w  ]     a [ 64] cache[ ww]
  46   c [ 73] cache[w  ]     a [ 63] cache[ ww]
  47   c [ 72] cache[w  ]     a [ 62] cache[ ww]
  48   c [ 71] cache[w  ]     a [ 61] cache[ ww]
  49   c [ 70] cache[  w]     a [ 60] cache[w  ]
---------------------------------------------------
  50   b [ 69] cache[  w]     c [ 69] cache[w  ]
  51   b [ 68] cache[  w]     c [ 68] cache[w  ]
  52   b [ 67] cache[  w]     c [ 67] cache[w  ]
  53   b [ 66] cache[  w]     c [ 66] cache[w  ]
  54   b [ 65] cache[  w]     c [ 65] cache[w  ]
  55   b [ 64] cache[  w]     c [ 64] cache[w  ]
  56   b [ 63] cache[  w]     c [ 63] cache[w  ]
  57   b [ 62] cache[  w]     c [ 62] cache[w  ]
  58   b [ 61] cache[  w]     c [ 61] cache[w  ]
  59   b [ 60] cache[ ww]     c [ 60] cache[  w]
---------------------------------------------------
  60   a [ 59] cache[ ww]     b [ 59] cache[  w]
  61   a [ 58] cache[ ww]     b [ 58] cache[  w]
  62   a [ 57] cache[ ww]     b [ 57] cache[  w]
  63   a [ 56] cache[ ww]     b [ 56] cache[  w]
  64   a [ 55] cache[ ww]     b [ 55] cache[  w]
  65   a [ 54] cache[ ww]     b [ 54] cache[  w]
  66   a [ 53] cache[ ww]     b [ 53] cache[  w]
  67   a [ 52] cache[ ww]     b [ 52] cache[  w]
  68   a [ 51] cache[ ww]     b [ 51] cache[  w]
  69   a [ 50] cache[w  ]     b [ 50] cache[ ww]
---------------------------------------------------
  70   c [ 59] cache[w  ]     a [ 49] cache[ ww]
  71   c [ 58] cache[w  ]     a [ 48] cache[ ww]
  72   c [ 57] cache[w  ]     a [ 47] cache[ ww]
  73   c [ 56] cache[w  ]     a [ 46] cache[ ww]
  74   c [ 55] cache[w  ]     a [ 45] cache[ ww]
  75   c [ 54] cache[w  ]     a [ 44] cache[ ww]
  76   c [ 53] cache[w  ]     a [ 43] cache[ ww]
  77   c [ 52] cache[w  ]     a [ 42] cache[ ww]
  78   c [ 51] cache[w  ]     a [ 41] cache[ ww]
  79   c [ 50] cache[  w]     a [ 40] cache[w  ]
---------------------------------------------------
  80   b [ 49] cache[  w]     c [ 49] cache[w  ]
  81   b [ 48] cache[  w]     c [ 48] cache[w  ]
  82   b [ 47] cache[  w]     c [ 47] cache[w  ]
  83   b [ 46] cache[  w]     c [ 46] cache[w  ]     
  84   b [ 45] cache[  w]     c [ 45] cache[w  ]
  85   b [ 44] cache[  w]     c [ 44] cache[w  ]
  86   b [ 43] cache[  w]     c [ 43] cache[w  ]
  87   b [ 42] cache[  w]     c [ 42] cache[w  ]
  88   b [ 41] cache[  w]     c [ 41] cache[w  ]
  89   b [ 40] cache[ ww]     c [ 40] cache[  w]
---------------------------------------------------
  90   a [ 39] cache[ ww]     b [ 39] cache[  w]
  91   a [ 38] cache[ ww]     b [ 38] cache[  w]
  92   a [ 37] cache[ ww]     b [ 37] cache[  w]
  93   a [ 36] cache[ ww]     b [ 36] cache[  w]
  94   a [ 35] cache[ ww]     b [ 35] cache[  w]
  95   a [ 34] cache[ ww]     b [ 34] cache[  w]
  96   a [ 33] cache[ ww]     b [ 33] cache[  w]
  97   a [ 32] cache[ ww]     b [ 32] cache[  w]
  98   a [ 31] cache[ ww]     b [ 31] cache[  w]
  99   a [ 30] cache[w  ]     b [ 30] cache[ ww]
---------------------------------------------------
 100   c [ 39] cache[w  ]     a [ 29] cache[ ww]
 101   c [ 38] cache[w  ]     a [ 28] cache[ ww]
 102   c [ 37] cache[w  ]     a [ 27] cache[ ww]
 103   c [ 36] cache[w  ]     a [ 26] cache[ ww]
 104   c [ 35] cache[w  ]     a [ 25] cache[ ww]
 105   c [ 34] cache[w  ]     a [ 24] cache[ ww]
 106   c [ 33] cache[w  ]     a [ 23] cache[ ww]
 107   c [ 32] cache[w  ]     a [ 22] cache[ ww]
 108   c [ 31] cache[w  ]     a [ 21] cache[ ww]
 109   c [ 30] cache[  w]     a [ 20] cache[w  ]
---------------------------------------------------
 110   b [ 29] cache[  w]     c [ 29] cache[w  ]
 111   b [ 28] cache[  w]     c [ 28] cache[w  ]
 112   b [ 27] cache[  w]     c [ 27] cache[w  ]
 113   b [ 26] cache[  w]     c [ 26] cache[w  ]
 114   b [ 25] cache[  w]     c [ 25] cache[w  ]
 115   b [ 24] cache[  w]     c [ 24] cache[w  ]
 116   b [ 23] cache[  w]     c [ 23] cache[w  ]
 117   b [ 22] cache[  w]     c [ 22] cache[w  ]
 118   b [ 21] cache[  w]     c [ 21] cache[w  ]
 119   b [ 20] cache[ ww]     c [ 20] cache[  w]
---------------------------------------------------
 120   a [ 19] cache[ ww]     b [ 19] cache[  w]
 121   a [ 18] cache[ ww]     b [ 18] cache[  w]
 122   a [ 17] cache[ ww]     b [ 17] cache[  w]
 123   a [ 16] cache[ ww]     b [ 16] cache[  w]
 124   a [ 15] cache[ ww]     b [ 15] cache[  w]
 125   a [ 14] cache[ ww]     b [ 14] cache[  w]
 126   a [ 13] cache[ ww]     b [ 13] cache[  w]
 127   a [ 12] cache[ ww]     b [ 12] cache[  w]
 128   a [ 11] cache[ ww]     b [ 11] cache[  w]
 129   a [ 10] cache[w  ]     b [ 10] cache[ ww]
---------------------------------------------------
 130   c [ 19] cache[w  ]     a [  9] cache[ ww]
 131   c [ 18] cache[w  ]     a [  8] cache[ ww]
 132   c [ 17] cache[w  ]     a [  7] cache[ ww]
 133   c [ 16] cache[w  ]     a [  6] cache[ ww]
 134   c [ 15] cache[w  ]     a [  5] cache[ ww]
 135   c [ 14] cache[w  ]     a [  4] cache[ ww]
 136   c [ 13] cache[w  ]     a [  3] cache[ ww]
 137   c [ 12] cache[w  ]     a [  2] cache[ ww]
 138   c [ 11] cache[w  ]     a [  1] cache[ ww]
 139   c [ 10] cache[  w]     a [  0] cache[w  ]
---------------------------------------------------
 140   b [  9] cache[  w]     c [  9] cache[w  ]
 141   b [  8] cache[  w]     c [  8] cache[w  ]
 142   b [  7] cache[  w]     c [  7] cache[w  ]
 143   b [  6] cache[  w]     c [  6] cache[w  ]
 144   b [  5] cache[  w]     c [  5] cache[w  ]
 145   b [  4] cache[  w]     c [  4] cache[w  ]
 146   b [  3] cache[  w]     c [  3] cache[w  ]
 147   b [  2] cache[  w]     c [  2] cache[w  ]
 148   b [  1] cache[  w]     c [  1] cache[w  ]
 149   b [  0] cache[ ww]     c [  0] cache[  w]

Finished time 150

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
```

### 6.  Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. To do this, you’ll need the -A flag. This flag can be used to limit which CPUs the scheduler can place a particular job upon. In this case, let’s use it to place jobs ’b’ and ’c’ on CPU 1, while restricting ’a’ to CPU 0. This magic is accomplished by typing this ./multi.py -n 2 -L a:100:100,b:100:50, c:100:50 -A a:0,b:1,c:1 ; don’t forget to turn on various tracing options to see what is really happening! Can you predict how fast this version will run? Why does it do better? Will other combinations of ’a’, ’b’, and ’c’ onto the two processors run faster or slower?

```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -c -t -C -T
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:50,c:100:50
ARG affinity a:0,b:1,c:1
ARG per_cpu_queues False
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace True
ARG trace_time True
ARG trace_cache True
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:50
Job name:c run_time:100 working_set_size:50

Scheduler central queue: ['a', 'b', 'c']

   0   a [ 99] cache[   ]     b [ 99] cache[   ]     
   1   a [ 98] cache[   ]     b [ 98] cache[   ]
   2   a [ 97] cache[   ]     b [ 97] cache[   ]
   3   a [ 96] cache[   ]     b [ 96] cache[   ]
   4   a [ 95] cache[   ]     b [ 95] cache[   ]
   5   a [ 94] cache[   ]     b [ 94] cache[   ]
   6   a [ 93] cache[   ]     b [ 93] cache[   ]
   7   a [ 92] cache[   ]     b [ 92] cache[   ]
   8   a [ 91] cache[   ]     b [ 91] cache[   ]
   9   a [ 90] cache[w  ]     b [ 90] cache[ w ]
---------------------------------------------------
  10   a [ 88] cache[w  ]     c [ 99] cache[ w ]
  11   a [ 86] cache[w  ]     c [ 98] cache[ w ]
  12   a [ 84] cache[w  ]     c [ 97] cache[ w ]
  13   a [ 82] cache[w  ]     c [ 96] cache[ w ]
  14   a [ 80] cache[w  ]     c [ 95] cache[ w ]
  15   a [ 78] cache[w  ]     c [ 94] cache[ w ]
  16   a [ 76] cache[w  ]     c [ 93] cache[ w ]
  17   a [ 74] cache[w  ]     c [ 92] cache[ w ]
  18   a [ 72] cache[w  ]     c [ 91] cache[ w ]
  19   a [ 70] cache[w  ]     c [ 90] cache[ ww]
---------------------------------------------------
  20   a [ 68] cache[w  ]     b [ 88] cache[ ww]
  21   a [ 66] cache[w  ]     b [ 86] cache[ ww]
  22   a [ 64] cache[w  ]     b [ 84] cache[ ww]
  23   a [ 62] cache[w  ]     b [ 82] cache[ ww]
  24   a [ 60] cache[w  ]     b [ 80] cache[ ww]
  25   a [ 58] cache[w  ]     b [ 78] cache[ ww]
  26   a [ 56] cache[w  ]     b [ 76] cache[ ww]
  27   a [ 54] cache[w  ]     b [ 74] cache[ ww]
  28   a [ 52] cache[w  ]     b [ 72] cache[ ww]
  29   a [ 50] cache[w  ]     b [ 70] cache[ ww]
---------------------------------------------------
  30   a [ 48] cache[w  ]     c [ 88] cache[ ww]
  31   a [ 46] cache[w  ]     c [ 86] cache[ ww]
  32   a [ 44] cache[w  ]     c [ 84] cache[ ww]
  33   a [ 42] cache[w  ]     c [ 82] cache[ ww]
  34   a [ 40] cache[w  ]     c [ 80] cache[ ww]
  35   a [ 38] cache[w  ]     c [ 78] cache[ ww]
  36   a [ 36] cache[w  ]     c [ 76] cache[ ww]
  37   a [ 34] cache[w  ]     c [ 74] cache[ ww]
  38   a [ 32] cache[w  ]     c [ 72] cache[ ww]
  39   a [ 30] cache[w  ]     c [ 70] cache[ ww]
---------------------------------------------------
  40   a [ 28] cache[w  ]     b [ 68] cache[ ww]
  41   a [ 26] cache[w  ]     b [ 66] cache[ ww]
  42   a [ 24] cache[w  ]     b [ 64] cache[ ww]
  43   a [ 22] cache[w  ]     b [ 62] cache[ ww]
  44   a [ 20] cache[w  ]     b [ 60] cache[ ww]
  45   a [ 18] cache[w  ]     b [ 58] cache[ ww]
  46   a [ 16] cache[w  ]     b [ 56] cache[ ww]
  47   a [ 14] cache[w  ]     b [ 54] cache[ ww]
  48   a [ 12] cache[w  ]     b [ 52] cache[ ww]
  49   a [ 10] cache[w  ]     b [ 50] cache[ ww]
---------------------------------------------------
  50   a [  8] cache[w  ]     c [ 68] cache[ ww]
  51   a [  6] cache[w  ]     c [ 66] cache[ ww]
  52   a [  4] cache[w  ]     c [ 64] cache[ ww]
  53   a [  2] cache[w  ]     c [ 62] cache[ ww]
  54   a [  0] cache[w  ]     c [ 60] cache[ ww]
  55   - [   ] cache[w  ]     c [ 58] cache[ ww]
  56   - [   ] cache[w  ]     c [ 56] cache[ ww]
  57   - [   ] cache[w  ]     c [ 54] cache[ ww]
  58   - [   ] cache[w  ]     c [ 52] cache[ ww]
  59   - [   ] cache[w  ]     c [ 50] cache[ ww]
---------------------------------------------------
  60   - [   ] cache[w  ]     b [ 48] cache[ ww]
  61   - [   ] cache[w  ]     b [ 46] cache[ ww]
  62   - [   ] cache[w  ]     b [ 44] cache[ ww]
  63   - [   ] cache[w  ]     b [ 42] cache[ ww]
  64   - [   ] cache[w  ]     b [ 40] cache[ ww]
  65   - [   ] cache[w  ]     b [ 38] cache[ ww]
  66   - [   ] cache[w  ]     b [ 36] cache[ ww]
  67   - [   ] cache[w  ]     b [ 34] cache[ ww]
  68   - [   ] cache[w  ]     b [ 32] cache[ ww]
  69   - [   ] cache[w  ]     b [ 30] cache[ ww]
---------------------------------------------------
  70   - [   ] cache[w  ]     c [ 48] cache[ ww]
  71   - [   ] cache[w  ]     c [ 46] cache[ ww]
  72   - [   ] cache[w  ]     c [ 44] cache[ ww]
  73   - [   ] cache[w  ]     c [ 42] cache[ ww]
  74   - [   ] cache[w  ]     c [ 40] cache[ ww]
  75   - [   ] cache[w  ]     c [ 38] cache[ ww]
  76   - [   ] cache[w  ]     c [ 36] cache[ ww]
  77   - [   ] cache[w  ]     c [ 34] cache[ ww]
  78   - [   ] cache[w  ]     c [ 32] cache[ ww]
  79   - [   ] cache[w  ]     c [ 30] cache[ ww]
---------------------------------------------------
  80   - [   ] cache[w  ]     b [ 28] cache[ ww]
  81   - [   ] cache[w  ]     b [ 26] cache[ ww]
  82   - [   ] cache[w  ]     b [ 24] cache[ ww]
  83   - [   ] cache[w  ]     b [ 22] cache[ ww]
  84   - [   ] cache[w  ]     b [ 20] cache[ ww]
  85   - [   ] cache[w  ]     b [ 18] cache[ ww]
  86   - [   ] cache[w  ]     b [ 16] cache[ ww]
  87   - [   ] cache[w  ]     b [ 14] cache[ ww]
  88   - [   ] cache[w  ]     b [ 12] cache[ ww]
  89   - [   ] cache[w  ]     b [ 10] cache[ ww]
---------------------------------------------------
  90   - [   ] cache[w  ]     c [ 28] cache[ ww]
  91   - [   ] cache[w  ]     c [ 26] cache[ ww]
  92   - [   ] cache[w  ]     c [ 24] cache[ ww]
  93   - [   ] cache[w  ]     c [ 22] cache[ ww]
  94   - [   ] cache[w  ]     c [ 20] cache[ ww]
  95   - [   ] cache[w  ]     c [ 18] cache[ ww]
  96   - [   ] cache[w  ]     c [ 16] cache[ ww]
  97   - [   ] cache[w  ]     c [ 14] cache[ ww]
  98   - [   ] cache[w  ]     c [ 12] cache[ ww]
  99   - [   ] cache[w  ]     c [ 10] cache[ ww]
---------------------------------------------------
 100   - [   ] cache[w  ]     b [  8] cache[ ww]
 101   - [   ] cache[w  ]     b [  6] cache[ ww]
 102   - [   ] cache[w  ]     b [  4] cache[ ww]
 103   - [   ] cache[w  ]     b [  2] cache[ ww]
 104   - [   ] cache[w  ]     b [  0] cache[ ww]
 105   - [   ] cache[w  ]     c [  8] cache[ ww]
 106   - [   ] cache[w  ]     c [  6] cache[ ww]
 107   - [   ] cache[w  ]     c [  4] cache[ ww]
 108   - [   ] cache[w  ]     c [  2] cache[ ww]     
 109   - [   ] cache[w  ]     c [  0] cache[ ww]

Finished time 110

Per-CPU stats
  CPU 0  utilization 50.00 [ warm 40.91 ]
  CPU 1  utilization 100.00 [ warm 81.82 ]

```
### 7.  One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) as compared to running jobs on a single processor. Specifically, when you run on N CPUs, sometimes you can speed up by more than a factor of N, a situation entitled super-linear speedup. To experiment with this, use the job description here (-L a:100:100,b:100:100,c:100:100) with a small cache (-M 50) to create three jobs. Run this on systems with 1, 2, and 3 CPUs (-n 1, -n 2, -n 3). Now, do the same, but with a larger per-CPU cache of size 100. What do you notice about performance as the number of CPUs scales? Use -c to confirm your guesses, and other tracing flags to dive even deeper.
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -M 100  -c -t -C -T   
Finished time 300

PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -M 100  -c -t -C -T
Finished time 150

PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 100  -c -t -C -T
Finished time 55

```

### 8.  One other aspect of the simulator worth studying is the per-CPU scheduling option, the -p flag. Run with two CPUs again, and this three job configuration (-L a: 100 : 100,b : 100 : 50,c: 100 : 50). How does this option do, as opposed to the hand-controlled affinity limits you put in place above? How does performance change as you alter the ’peek interval’ (-P) to lower or higher values? How does this per-CPU approach work as the number of CPUs scales?
```
PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -p -c -t -T -C
Finished time 100

PS C:\Users\huaxi\Desktop\cs5600-computer-system> python .\multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -p -c -t -T -C -P 50
Finished time 130
```

# Homework (Code)
### 1.   The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!
```
FREE(1)                                                 User Commands                                                 FREE(1)

NAME
       free - Display amount of free and used memory in the system

SYNOPSIS
       free [options]

DESCRIPTION
       free  displays  the  total  amount of free and used physical and swap memory in the system, as well as the buffers and
       caches used by the kernel. The information is gathered by parsing /proc/meminfo. The displayed columns are:

       total  Total installed memory (MemTotal and SwapTotal in /proc/meminfo)

       used   Used memory (calculated as total - free - buffers - cache)

       free   Unused memory (MemFree and SwapFree in /proc/meminfo)

       shared Memory used (mostly) by tmpfs (Shmem in /proc/meminfo, available on kernels 2.6.32, displayed as  zero  if  not
              available)

       buffers
              Memory used by kernel buffers (Buffers in /proc/meminfo)

       cache  Memory used by the page cache and slabs (Cached and SReclaimable in /proc/meminfo)

       buff/cache
              Sum of buffers and cache

       available
              Estimation  of  how  much  memory is available for starting new applications, without swapping. Unlike the data
              provided by the cache or free fields, this  field  takes  into  account  page  cache  and  also  that  not  all
              reclaimable  memory slabs will be reclaimed due to items being in use (MemAvailable in /proc/meminfo, available
              on kernels 3.14, emulated on kernels 2.6.27+, otherwise the same as free)
              OPTIONS
       -b, --bytes
              Display the amount of memory in bytes.

       -k, --kilo
              Display the amount of memory in kilobytes.  This is the default.

       -m, --mega
              Display the amount of memory in megabytes.

       -g, --giga
              Display the amount of memory in gigabytes.

       --tera Display the amount of memory in terabytes.

       --peta Display the amount of memory in petabytes.

       -h, --human
              Show all output fields automatically scaled to shortest three digit unit and display the units  of  print  out.
              Following units are used.

                B = bytes
                K = kilos
                M = megas
                G = gigas
                T = teras
                P = petas

              If  unit  is  missing, and you have exabyte of RAM or swap, the number is in terabytes and columns might not be
              aligned with header.

       -w, --wide
              Switch to the wide mode. The wide mode produces lines longer than 80 characters. In this mode buffers and cache
              are reported in two separate columns.

       -c, --count count
              Display the result count times.  Requires the -s option.

       -l, --lohi
              Show detailed low and high memory statistics.

       -s, --seconds seconds
              Continuously  display  the  result delay seconds apart.  You may actually specify any floating point number for
              delay, usleep(3) is used for microsecond resolution delay times.

       --si   Use power of 1000 not 1024.

       -t, --total
              Display a line showing the column totals.

       --help Print help.

       -V, --version
              Display version information.

FILES
       /proc/meminfo
              memory information

SEE ALSO
       ps(1), slabtop(1), top(1), vmstat(8).
       AUTHORS
       Written by Brian Edmonds.

REPORTING BUGS
       Please send bug reports to ⟨procps@freelists.org⟩

```

### 2.   Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?
```
bash-4.2$ free -m
              total        used        free      shared  buff/cache   available
Mem:         385388       10181      340515         337       34691      373757
Swap:          4095         857        3238

```
### 3.   Next, create a little program that uses a certain amount of memory, called memory-user.c. This program should take one commandline argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int runningTime=atoi(argv[2]);
    printf("the running time is %d\n",runningTime);
    //convert the input int to bytes
    int memory=atoi(argv[1])*1024*1024;
    int* nums=(int*)malloc(memory);
    int n= (int) (memory/sizeof(int));
    int i;
    clock_t start = clock();
    for(i=0;i<n;i++){
        printf("this is %d\n",i);
        clock_t end=clock();
        if((double)(end-start)/CLOCKS_PER_SEC > runningTime){
            printf("time's up\n");
            break;
        }
    }
    free(nums);
    return 0;
}
```
### 4.   Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?
```
bash-4.2$ ./memory-user 100 1000


bash-4.2$ free -m
              total        used        free      shared  buff/cache   available
Mem:         385388       10765      340002         338       34619      373172
Swap:          4095         857        3238
bash-4.2$ free -m
              total        used        free      shared  buff/cache   available
Mem:         385388       10860      339908         338       34619      373078
Swap:          4095         857        3238
```
### 5.   Let’s try one more tool, known as pmap. Spend some time, and read the pmap manual page in detail.
```
The pmap command in Linux is used to display the memory map of a process. A memory map indicates how memory is spread out.

https://www.geeksforgeeks.org/pmap-command-in-linux-with-examples/
```
### 6.   To use pmap, you have to know the process ID of the process you’re interested in. Thus, first run ps auxw to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int runningTime=atoi(argv[2]);
    printf("the running time is %d\n",runningTime);
    printf("the current process id is %d\n",getpid());
    //convert the input int to bytes
    int memory=atoi(argv[1])*1024*1024;
    int* nums=(int*)malloc(memory);
    int n= (int) (memory/sizeof(int));
    int i;
    clock_t start = clock();
    while (1){
        for(i=0;i<n;i++){
            nums[i]+=1;
        }

        clock_t end=clock();
        if((double)(end-start)/CLOCKS_PER_SEC > runningTime){
            printf("time's up\n");
            break;
        }
    }
    
    free(nums);
    return 0;
}
```

### 7.   Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?
```
bash-4.2$ ./memory-user 100 1000


bash-4.2$ pmap -x 157708
157708:   ./memory-user 100 1000
Address           Kbytes     RSS   Dirty Mode  Mapping
0000000000400000       4       4       0 r-x-- memory-user
0000000000600000       4       4       4 r---- memory-user
0000000000601000       4       4       4 rw--- memory-user
00007fe9b7929000  102404  102404  102404 rw---   [ anon ]
00007fe9bdd2a000    1808     320       0 r-x-- libc-2.17.so
00007fe9bdeee000    2044       0       0 ----- libc-2.17.so
00007fe9be0ed000      16      16      16 r---- libc-2.17.so
00007fe9be0f1000       8       8       8 rw--- libc-2.17.so
00007fe9be0f3000      20      12      12 rw---   [ anon ]
00007fe9be0f8000     136     108       0 r-x-- ld-2.17.so
00007fe9be2f8000      12      12      12 rw---   [ anon ]
00007fe9be317000       8       8       8 rw---   [ anon ]
00007fe9be319000       4       4       4 r---- ld-2.17.so
00007fe9be31a000       4       4       4 rw--- ld-2.17.so
00007fe9be31b000       4       4       4 rw---   [ anon ]
00007ffdd94e8000     132      16      16 rw---   [ stack ]
00007ffdd9540000       8       4       0 r-x--   [ anon ]
ffffffffff600000       4       0       0 r-x--   [ anon ]
---------------- ------- ------- ------- 
total kB          106624  102932  102496
```

### 8.   Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?
```
bash-4.2$ ./memory-user 50 1000


bash-4.2$ pmap -x 158717
158717:   ./memory-user 50 1000
Address           Kbytes     RSS   Dirty Mode  Mapping
0000000000400000       4       4       0 r-x-- memory-user
0000000000600000       4       4       4 r---- memory-user
0000000000601000       4       4       4 rw--- memory-user
00007f19f741f000   51204   51204   51204 rw---   [ anon ]
00007f19fa620000    1808     320       0 r-x-- libc-2.17.so
00007f19fa7e4000    2044       0       0 ----- libc-2.17.so
00007f19fa9e3000      16      16      16 r---- libc-2.17.so
00007f19fa9e7000       8       8       8 rw--- libc-2.17.so
00007f19fa9e9000      20      12      12 rw---   [ anon ]
00007f19fa9ee000     136     108       0 r-x-- ld-2.17.so
00007f19fabee000      12      12      12 rw---   [ anon ]
00007f19fac0d000       8       8       8 rw---   [ anon ]
00007f19fac0f000       4       4       4 r---- ld-2.17.so
00007f19fac10000       4       4       4 rw--- ld-2.17.so
00007f19fac11000       4       4       4 rw---   [ anon ]
00007ffda20e0000     132      16      16 rw---   [ stack ]
00007ffda213e000       8       4       0 r-x--   [ anon ]
ffffffffff600000       4       0       0 r-x--   [ anon ]
---------------- ------- ------- ------- 
total kB           55424   51732   51296
```

# Homework (Code)
### 1.   First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?
```
bash-4.2$ gcc -o null null.c -Wall
bash-4.2$ ./null 
Segmentation fault
```

### 2.    Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?
```
bash-4.2$ gcc -o null null.c -Wall -g
bash-4.2$ gdb null
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-120.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/huaxing/cs5600/week4/null...done.
(gdb) run
Starting program: /home/huaxing/cs5600/week4/null 

Program received signal SIGSEGV, Segmentation fault.
0x00000000004005e6 in main (argc=1, argv=0x7fffffffe468) at null.c:9
9           printf("this is %d\n",*num);
Missing separate debuginfos, use: debuginfo-install glibc-2.17-326.el7_9.x86_64
```

### 3.    Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?
```
bash-4.2$ valgrind --leak-check=yes ./null
==241822== Memcheck, a memory error detector
==241822== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==241822== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==241822== Command: ./null
==241822== 
==241822== Invalid read of size 4
==241822==    at 0x4005E6: main (null.c:9)
==241822==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==241822== 
==241822== 
==241822== Process terminating with default action of signal 11 (SIGSEGV)
==241822==  Access not within mapped region at address 0x0
==241822==    at 0x4005E6: main (null.c:9)
==241822==  If you believe this happened as a result of a stack
==241822==  overflow in your program's main thread (unlikely but
==241822==  possible), you can try to increase the size of the
==241822==  main thread stack using the --main-stacksize= flag.
==241822==  The main thread stack size used in this run was 8388608.
==241822== 
==241822== HEAP SUMMARY:
==241822==     in use at exit: 4 bytes in 1 blocks
==241822==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==241822== 
==241822== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==241822==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==241822==    by 0x4005D5: main (null.c:7)
==241822== 
==241822== LEAK SUMMARY:
==241822==    definitely lost: 4 bytes in 1 blocks
==241822==    indirectly lost: 0 bytes in 0 blocks
==241822==      possibly lost: 0 bytes in 0 blocks
==241822==    still reachable: 0 bytes in 0 blocks
==241822==         suppressed: 0 bytes in 0 blocks
==241822== 
==241822== For lists of detected and suppressed errors, rerun with: -s
==241822== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
Segmentation fault

```
### 4.    Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?
program runs successfully.  

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(10*sizeof(int));
    int i;
    for(i=0;i<10;i++){
        nums[i]=i;
    }
    i=0;
    for(i=0;i<10;i++){
        printf("this is %d\n",nums[i]);
    }
    return 0;
}

```

```
bash-4.2$ gcc -o ch14-q4 ch14-q4.c -Wall -g
bash-4.2$ gdb ch14-q4
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-120.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/huaxing/cs5600/week4/ch14-q4...done.
(gdb) run
Starting program: /home/huaxing/cs5600/week4/ch14-q4 
this is 0
this is 1
this is 2
this is 3
this is 4
this is 5
this is 6
this is 7
this is 8
this is 9
[Inferior 1 (process 243821) exited normally]
Missing separate debuginfos, use: debuginfo-install glibc-2.17-326.el7_9.x86_64
```
```
bash-4.2$ valgrind --leak-check=yes ./ch14-q4
==244033== Memcheck, a memory error detector
==244033== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==244033== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==244033== Command: ./ch14-q4
==244033== 
this is 0
this is 1
this is 2
this is 3
this is 4
this is 5
this is 6
this is 7
this is 8
this is 9
==244033== 
==244033== HEAP SUMMARY:
==244033==     in use at exit: 40 bytes in 1 blocks
==244033==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==244033== 
==244033== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==244033==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==244033==    by 0x400595: main (ch14-q4.c:7)
==244033== 
==244033== LEAK SUMMARY:
==244033==    definitely lost: 40 bytes in 1 blocks
==244033==    indirectly lost: 0 bytes in 0 blocks
==244033==      possibly lost: 0 bytes in 0 blocks
==244033==    still reachable: 0 bytes in 0 blocks
==244033==         suppressed: 0 bytes in 0 blocks
==244033== 
==244033== For lists of detected and suppressed errors, rerun with: -s
==244033== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### 5.    Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(100*sizeof(int));
    nums[100]=0;
    free(nums);

    return 0;
}
```
program runs successfully.  
```
bash-4.2$ valgrind ./ch14-q5
==244871== Memcheck, a memory error detector
==244871== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==244871== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==244871== Command: ./ch14-q5
==244871== 
==244871== Invalid write of size 4
==244871==    at 0x4005A4: main (in /home/huaxing/cs5600/week4/ch14-q5)
==244871==  Address 0x52051d0 is 0 bytes after a block of size 400 alloc'd
==244871==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==244871==    by 0x400595: main (in /home/huaxing/cs5600/week4/ch14-q5)
==244871== 
==244871== 
==244871== HEAP SUMMARY:
==244871==     in use at exit: 0 bytes in 0 blocks
==244871==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==244871== 
==244871== All heap blocks were freed -- no leaks are possible
==244871== 
==244871== For lists of detected and suppressed errors, rerun with: -s
==244871== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
### 6.    Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(10*sizeof(int));
    int i;
    for(i=0;i<10;i++){
        nums[i]=100;
    }
    for(i=0;i<10;i++){
        printf("this is %d\n",nums[i]);
    }
    free(nums);
    i=0;
    for(i=0;i<10;i++){
        printf("this is %d\n",nums[i]);
    }

    return 0;
}
```
```
bash-4.2$ ./ch14-q6
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 0
this is 0
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
```

```
bash-4.2$ valgrind -s ./ch14-q6 
==246985== Memcheck, a memory error detector
==246985== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==246985== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==246985== Command: ./ch14-q6
==246985== 
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
==246985== Invalid read of size 4
==246985==    at 0x400671: main (in /home/huaxing/cs5600/week4/ch14-q6)
==246985==  Address 0x5205040 is 0 bytes inside a block of size 40 free'd
==246985==    at 0x4C2B06D: free (vg_replace_malloc.c:540)
==246985==    by 0x40064C: main (in /home/huaxing/cs5600/week4/ch14-q6)
==246985==  Block was alloc'd at
==246985==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==246985==    by 0x4005D5: main (in /home/huaxing/cs5600/week4/ch14-q6)
==246985== 
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
this is 100
==246985== 
==246985== HEAP SUMMARY:
==246985==     in use at exit: 0 bytes in 0 blocks
==246985==   total heap usage: 1 allocs, 1 frees, 40 bytes allocated
==246985== 
==246985== All heap blocks were freed -- no leaks are possible
==246985== 
==246985== ERROR SUMMARY: 10 errors from 1 contexts (suppressed: 0 from 0)
==246985== 
==246985== 10 errors in context 1 of 1:
==246985== Invalid read of size 4
==246985==    at 0x400671: main (in /home/huaxing/cs5600/week4/ch14-q6)
==246985==  Address 0x5205040 is 0 bytes inside a block of size 40 free'd
==246985==    at 0x4C2B06D: free (vg_replace_malloc.c:540)
==246985==    by 0x40064C: main (in /home/huaxing/cs5600/week4/ch14-q6)
==246985==  Block was alloc'd at
==246985==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==246985==    by 0x4005D5: main (in /home/huaxing/cs5600/week4/ch14-q6)
==246985== 
==246985== ERROR SUMMARY: 10 errors from 1 contexts (suppressed: 0 from 0)

```
### 7.    Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(10*sizeof(int));
    int i;
    for(i=0;i<10;i++){
        nums[i]=i;
    }
    free(&nums[4]);    
    for(i=0;i<10;i++){
        printf("this is %d\n",nums[i]);
    }

    return 0;
}
```
```
bash-4.2$ ./ch14-q7
*** Error in `./ch14-q7': munmap_chunk(): invalid pointer: 0x00000000021bc020 ***
======= Backtrace: =========
/lib64/libc.so.6(+0x7f474)[0x7fb880443474]
./ch14-q7[0x400616]
/lib64/libc.so.6(__libc_start_main+0xf5)[0x7fb8803e6555]
./ch14-q7[0x4004f9]
======= Memory map: ========
00400000-00401000 r-xp 00000000 00:30 26866146                           /home/huaxing/cs5600/week4/ch14-q7
00600000-00601000 r--p 00000000 00:30 26866146                           /home/huaxing/cs5600/week4/ch14-q7
00601000-00602000 rw-p 00001000 00:30 26866146                           /home/huaxing/cs5600/week4/ch14-q7
021bc000-021dd000 rw-p 00000000 00:00 0                                  [heap]
7fb8801ae000-7fb8801c3000 r-xp 00000000 fd:00 50331749                   /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fb8801c3000-7fb8803c2000 ---p 00015000 fd:00 50331749                   /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fb8803c2000-7fb8803c3000 r--p 00014000 fd:00 50331749                   /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fb8803c3000-7fb8803c4000 rw-p 00015000 fd:00 50331749                   /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fb8803c4000-7fb880588000 r-xp 00000000 fd:00 50332326                   /usr/lib64/libc-2.17.so
7fb880588000-7fb880787000 ---p 001c4000 fd:00 50332326                   /usr/lib64/libc-2.17.so
7fb880787000-7fb88078b000 r--p 001c3000 fd:00 50332326                   /usr/lib64/libc-2.17.so
7fb88078b000-7fb88078d000 rw-p 001c7000 fd:00 50332326                   /usr/lib64/libc-2.17.so
7fb88078d000-7fb880792000 rw-p 00000000 00:00 0 
7fb880792000-7fb8807b4000 r-xp 00000000 fd:00 50332319                   /usr/lib64/ld-2.17.so
7fb880992000-7fb880995000 rw-p 00000000 00:00 0 
7fb8809b1000-7fb8809b3000 rw-p 00000000 00:00 0 
7fb8809b3000-7fb8809b4000 r--p 00021000 fd:00 50332319                   /usr/lib64/ld-2.17.so
7fb8809b4000-7fb8809b5000 rw-p 00022000 fd:00 50332319                   /usr/lib64/ld-2.17.so
7fb8809b5000-7fb8809b6000 rw-p 00000000 00:00 0 
7fff84453000-7fff84474000 rw-p 00000000 00:00 0                          [stack]
7fff844b2000-7fff844b4000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
Aborted
```
```
bash-4.2$ valgrind --leak-check=full ./ch14-q7
==250977== Memcheck, a memory error detector
==250977== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==250977== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==250977== Command: ./ch14-q7
==250977== 
==250977== Invalid free() / delete / delete[] / realloc()
==250977==    at 0x4C2B06D: free (vg_replace_malloc.c:540)
==250977==    by 0x400615: main (in /home/huaxing/cs5600/week4/ch14-q7)
==250977==  Address 0x5205050 is 16 bytes inside a block of size 40 alloc'd
==250977==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==250977==    by 0x4005D5: main (in /home/huaxing/cs5600/week4/ch14-q7)
==250977== 
this is 0
this is 1
this is 2
this is 3
this is 4
this is 5
this is 6
this is 7
this is 8
this is 9
==250977== 
==250977== HEAP SUMMARY:
==250977==     in use at exit: 40 bytes in 1 blocks
==250977==   total heap usage: 1 allocs, 1 frees, 40 bytes allocated
==250977== 
==250977== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==250977==    at 0x4C29F73: malloc (vg_replace_malloc.c:309)
==250977==    by 0x4005D5: main (in /home/huaxing/cs5600/week4/ch14-q7)
==250977== 
==250977== LEAK SUMMARY:
==250977==    definitely lost: 40 bytes in 1 blocks
==250977==    indirectly lost: 0 bytes in 0 blocks
==250977==      possibly lost: 0 bytes in 0 blocks
==250977==    still reachable: 0 bytes in 0 blocks
==250977==         suppressed: 0 bytes in 0 blocks
==250977== 
==250977== For lists of detected and suppressed errors, rerun with: -s
==250977== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```


### 8.    Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.
```
https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/#:~:text=%E2%80%9Ccalloc%E2%80%9D%20or%20%E2%80%9Ccontiguous%20allocation,memory%20of%20the%20specified%20type.
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int* nums=(int*)malloc(10*sizeof(int));
    int i;
    for(i=0;i<10;i++){
        nums[i]=i;
    }
    nums=(int*)realloc(nums,20*sizeof(int));
    for(;i<20;i++){
        nums[i]=i;
    }
    int j;
    for(j=0;j<20;j++){
        printf("this is %d\n",nums[j]);
    }
    return 0;
}
```
### 9.     Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.
