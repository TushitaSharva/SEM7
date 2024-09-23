# Average Entry Time with varying threads [AVG]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [2, 4, 8, 16, 32, 64]
B = [avg(0.25,0.80,0.15,0.10,0.35), avg(1.20,0.73,0.37,0.77,0.70), avg(1.93,1.85,2.42,2.26,1.48), avg(7.79,9.82,9.08,9.90,10.68), avg(104.01,88.83,99.20,96.34,95.76), avg(407.35,458.88,455.78,441.78,452.15)]
F = [avg(0.00,0.05,0.05,0.30,0.05), avg(0.20,1.10,0.75,0.38,0.33), avg(2.01,2.50,1.91,1.75,2.36), avg(8.96,9.63,7.52,12.25,9.13), avg(067.26,70.12,63.99,68.85,56.12), avg(309.36,343.41,342.22,303.57,312.70)]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, B, label='Bakery', color='purple')
plt.plot(N, F, label='Filter', color='green')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, B, color='purple')
plt.scatter(N, F, color='green')

plt.xlabel('N (Number of threads)')
plt.ylabel('Throughput')
plt.title('Throughput Analysis with varying threads')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()