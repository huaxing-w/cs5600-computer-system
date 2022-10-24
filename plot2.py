import subprocess
import matplotlib.pyplot as plt
import collections


x=[1,2,3,4]
policy=["FIFO", "LRU", "OPT","CLOCK"]
y=[[57.33, 88.85, 92.84, 95.00],
    [69.33, 89.48, 91.80, 94.94],
    [49.33, 74.43, 86.11, 92.69],
    [40, 40, 40, 40]]



for i in range(4):
    plt.plot(x, y[i], label=policy[i])
plt.legend(policy)
plt.xlabel('cache size')
plt.ylabel('hit')
plt.title('q5')
plt.show()