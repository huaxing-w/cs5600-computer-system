import subprocess
import matplotlib.pyplot as plt
import collections


x = []
y = []

for limit in range(100, 2000,20):
    x.append(limit)
    

    process = subprocess.run(['python', './relocation.py','-s', '1', '-n', '100', '-l', str(limit), '-c'], 
                            stdout=subprocess.PIPE, 
                            universal_newlines=True)
    
    counter=collections.Counter(process.stdout.split(' '))

    
    

    y.append(counter['VALID:']/100)
    
plt.plot(x, y)
plt.xlabel('address limit')
plt.ylabel('valid fraction')
plt.title('q5')
plt.show()