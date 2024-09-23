# Throughput Analysis with varying threads: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [2, 4, 8, 16, 32, 64]
B = [avg(1.03,0.85,0.64,0.6,0.66), avg(0.97,1.34,1.05,1.09,1.11), avg(1.36,1.46,1.64,1.17,1.36), avg(1.5,1.24,1.24,1.21,1.11), avg(0.28,0.28,0.29,0.30,0.29), avg(0.13,0.13,0.12,0.13,0.12)]
F = [avg(0.79,0.88,0.67,0.61,0.67), avg(1.13,1.11,1.01,1.13,1.18), avg(1.24,1.45,1.35,1.6,1.67), avg(1.04,0.84,1.13,1.08,1.10), avg(0.39,0.44,0.43,0.44,0.45), avg(0.19,0.17,0.18,0.17,0.18)]

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