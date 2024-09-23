# Throughput Analysis with varying threads [WORST CASE]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [2, 4, 8, 16, 32, 64]
B = [avg(0.3,1.2,0.2,0.1,0.5), avg(1.6,1.2,0.5,1.1,1.3), avg(2.4,2.4,3,2.9,2.2), avg(8.9,10.7,10.1,11.1,11.5), avg(106.8,91.7,103.2,98.6,98.6), avg(415.2,468.2,465.1,451.4,462.6)]
F = [avg(0,0.1,0.1,0.6,0.1), avg(0.3,1.3,1,0.5,0.5), avg(2.4,3.1,2.2,2.3,2.8), avg(9.9,11.1,8.5,13.2,10.5), avg(71,75.4,68.5,74,60.1), avg(322.8,355.3,356.8,317.4,327.7)]

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