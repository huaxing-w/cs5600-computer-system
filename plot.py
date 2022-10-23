import subprocess
import matplotlib.pyplot as plt
import collections


x=[1,2,3,4,5,6,7,8]
y=[1500,1528,1575,1558,1600,1600,1600,1600]


plt.plot(x, y)
plt.xlabel('allocated size')
plt.ylabel('bandwidth')
plt.title('q5')
plt.show()