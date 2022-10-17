import subprocess
import matplotlib.pyplot as plt
import collections


x=[]
y=[]

page=1
while page<=(1<<14):
    x.append(page)
    process = subprocess.run(['./tlb2.exe',str(page), '10000'], 
                        stdout=subprocess.PIPE, 
                        universal_newlines=True)
    y.append(float(process.stdout))
    page*=2



plt.plot(x, y)
plt.xlabel('page number')
plt.ylabel('average per access time')
plt.title('q4')
plt.show()