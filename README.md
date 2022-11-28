# Homework (Simulation)

### 1.    Compute the seek, rotation, and transfer times for the following sets of requests: -a 0, -a 6, -a 30, -a 7,30,8, and finally -a 10,11,12,13.
```
Block:   0  Seek:  0  Rotate:165  Transfer: 30  Total: 195

TOTALS      Seek:  0  Rotate:165  Transfer: 30  Total: 195

Block:   6  Seek:  0  Rotate:345  Transfer: 30  Total: 375

TOTALS      Seek:  0  Rotate:345  Transfer: 30  Total: 375

Block:  30  Seek: 80  Rotate:265  Transfer: 30  Total: 375

TOTALS      Seek: 80  Rotate:265  Transfer: 30  Total: 375


Block:  10  Seek:  0  Rotate:105  Transfer: 30  Total: 135
Block:  11  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
Block:  12  Seek: 40  Rotate:320  Transfer: 30  Total: 390
Block:  13  Seek:  0  Rotate:  0  Transfer: 30  Total:  30

TOTALS      Seek: 40  Rotate:425  Transfer:120  Total: 585

Block:   7  Seek:  0  Rotate: 15  Transfer: 30  Total:  45
Block:  30  Seek: 80  Rotate:220  Transfer: 30  Total: 330
Block:   8  Seek: 80  Rotate:310  Transfer: 30  Total: 420

TOTALS      Seek:160  Rotate:545  Transfer: 90  Total: 795


```
### 2.    Do the same requests above, but change the seek rate to different values: -S 2,-S 4,-S 8,-S 10,-S 40,-S 0.1. How do the times change?
```
python disk.py -a 10,11,12,13 -S 40  -G

Seek time is shorter. 
```
### 3.    Do the same requests above, but change the rotation rate: -R 0.1,-R 0.5,-R 0.01. How do the times change?
```
Rotate time and transfer time are longer.

```

### 4.    Do the same requests above, but change the rotation rate: -R 0.1,-R 0.5,-R 0.01. How do the times change?
```
Block:   7  Seek:  0  Rotate: 15  Transfer: 30  Total:  45
Block:  30  Seek: 80  Rotate:220  Transfer: 30  Total: 330
Block:   8  Seek: 80  Rotate:310  Transfer: 30  Total: 420

TOTALS      Seek:160  Rotate:545  Transfer: 90  Total: 795


Block:   7  Seek:  0  Rotate: 15  Transfer: 30  Total:  45
Block:   8  Seek:  0  Rotate:  0  Transfer: 30  Total:  30
Block:  30  Seek: 80  Rotate:190  Transfer: 30  Total: 300

TOTALS      Seek: 80  Rotate:205  Transfer: 90  Total: 375
```

### 5.    Now use the shortest access-time first(SATF) scheduler(-p SATF). Does it make any difference for -a 7,30,8 workload? Find a set of requests where SATF outperforms SSTF; more generally, when is SATF better than SSTF?
```
no.
When seek time is shorter then rotate time.

```
### 6.    Here is a request stream to try: -a 10,11,12,13. What goes poorly when it runs? Try adding track skew to address this problem (-o skew). Given the default seek rate, what should the skew be to maximize performance? What about for different seek rates (e.g., -S 2, -S 4)? In general, could you write a formula to figure out the skew?
```
skew = (track-distance(40) / seek-speed) * rotation-speed / rotational-space-degrees(360 / 12) = math.ceil((40 / 1) * 1 / 30) = 2
```
### 7.    Specify a disk with different density per zone, e.g., -z 10,20,30, which specifies the angular difference between blocks on the outer, middle, and inner tracks. Run some random requests (e.g., -a -1 -A 5,-1,0, which specifies that random requests should be used via the -a -1 flag and that five requests ranging from 0 to the max be generated), and compute the seek, rotation, and transfer times. Use different random seeds. What is the bandwidth (in sectors per unit time) on the outer, middle, and inner tracks?
```
python disk.py -z 10,20,30 -a -1 -A 5,-1,0 -c


```

### 8.    A scheduling window determines how many requests the disk can examine at once. Generate random workloads (e.g., -A 1000,-1,0, with different seeds) and see how long the SATF scheduler takes when the scheduling window is changed from 1 up to the number of requests. How big of a window is needed to maximize performance? Hint: use the -c flag and don’t turn on graphics (-G) to run these quickly. When the scheduling window is set to 1, does it matter which policy you are using?
```
python disk.py -A 1000,-1,0 -p SATF -w 1000 -c

```

### 9.    Create a series of requests to starve a particular request, assuming an SATF policy. Given that sequence, how does it perform if you use a bounded SATF (BSATF) scheduling approach? In this approach, you specify the scheduling window (e.g., -w 4); the scheduler only moves onto the next window of requests when all requests in the current window have been serviced. Does this solve starvation? How does it perform, as compared to SATF? In general, how should a disk make this trade-off between performance and starvation avoidance?
```
python disk.py -a 12,7,8,9,10,11 -p SATF -c          
python disk.py -a 12,7,8,9,10,11 -p BSATF -w 4 -c    

```

### 10.    Create a series of requests to starve a particular request, assuming an SATF policy. Given that sequence, how does it perform if you use a bounded SATF (BSATF) scheduling approach? In this approach, you specify the scheduling window (e.g., -w 4); the scheduler only moves onto the next window of requests when all requests in the current window have been serviced. Does this solve starvation? How does it perform, as compared to SATF? In general, how should a disk make this trade-off between performance and starvation avoidance?
```
python disk.py -a 9,20 -c            
python disk.py -a 9,20 -c -p SATF   
```

# Homework (Simulation)
### 1.    Use the simulator to perform some basic RAID mapping tests. Run with different levels (0, 1, 4, 5) and see if you can figure out the mappings of a set of requests. For RAID-5, see if you can figure out the difference between left-symmetric and left-asymmetric layouts. Use some different random seeds to generate different problems than above.
```
python raid.py -L 5 -5 LS -c -W seq
python raid.py -L 5 -5 LA -c -W seq

left-symmetric    left-asymmetric
0 1 2 P           0 1 2 P
4 5 P 3           3 4 P 5
8 P 6 7           6 P 7 8
```

### 2.    Do the same as the first problem, but this time vary the chunk size with -C. How does chunk size change the mappings?
```
python raid.py -L 5 -5 LS -c -W seq -C 8K -n 12

0  2  4  P
1  3  5  P
8 10  P  6
9 11  P  7
```

### 3.    Do the same as above, but use the -r flag to reverse the nature of each problem?
```
python raid.py -L 5 -5 LS -W seq -C 8K -n 12 -r
```

### 4.    Now use the reverse flag but increase the size of each request with the -S flag. Try specifying sizes of 8k, 12k, and 16k, while varying the RAID level. What happens to the underlying I/O pattern when the size of the request increases? Make sure to try this with the sequential workload too (-W sequential); for what request sizes are RAID-4 and RAID-5 much more I/O efficient?
```
python raid.py -L 4 -S 16k -c -W seq
```

### 5.    Use the timing mode of the simulator (-t) to estimate the performance of 100 random reads to the RAID, while varying the RAID levels, using 4 disks?
```
python raid.py -L 0 -t -n 100 -c    // 275.7
python raid.py -L 1 -t -n 100 -c    // 278.7
python raid.py -L 4 -t -n 100 -c    // 386.1
python raid.py -L 5 -t -n 100 -c    // 276.5
```

### 6.    Do the same as above, but increase the number of disks. How does the performance of each RAID level scale as the number of disks increases?
```
python raid.py -L 0 -t -n 100 -c -D 8   // 275.7 / 156.5 = 1.76
python raid.py -L 1 -t -n 100 -c -D 8   // 278.7 / 167.8 = 1.66
python raid.py -L 4 -t -n 100 -c -D 8   // 386.1 / 165.0 = 2.34
python raid.py -L 5 -t -n 100 -c -D 8   // 276.5 / 158.6 = 1.74
```

### 7.    Do the same as above, but use all writes (-w 100) instead of reads. How does the performance of each RAID level scale now? Can you do a rough estimate of the time it will take to complete the workload of 100 random writes?
```
python raid.py -L 0 -t -n 100 -c -w 100       // 275.7    100 * 10 / 4
python raid.py -L 1 -t -n 100 -c -w 100       // 509.8    100 * 10 / (4 / 2)
python raid.py -L 4 -t -n 100 -c -w 100       // 982.5
python raid.py -L 5 -t -n 100 -c -w 100       // 497.4
python raid.py -L 0 -t -n 100 -c -D 8 -w 100  // 275.7 / 156.5 = 1.76    100 * 10 / 8
python raid.py -L 1 -t -n 100 -c -D 8 -w 100  // 509.8 / 275.7 = 1.85    100 * 10 / (8 / 2)
python raid.py -L 4 -t -n 100 -c -D 8 -w 100  // 982.5 / 937.8 = 1.05
python raid.py -L 5 -t -n 100 -c -D 8 -w 100  // 497.4 / 290.9 = 1.71
```

### 8.    Run the timing mode one last time, but this time with a sequential workload(-W sequential). How does the performance vary with RAID level, and when doing reads versus writes? How about when varying the size of each request? What size should you write to a RAID when using RAID-4 or RAID-5?
```
12k
python raid.py -L 0 -t -n 100 -c -w 100 -W seq    // 275.7 / 12.5 = 22
python raid.py -L 1 -t -n 100 -c -w 100 -W seq    // 509.8 / 15 = 34
python raid.py -L 4 -t -n 100 -c -w 100 -W seq    // 982.5 / 13.4 = 73
python raid.py -L 5 -t -n 100 -c -w 100 -W seq    // 497.4 / 13.4 = 37
```
