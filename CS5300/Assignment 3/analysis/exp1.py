# Throughput Analysis with varying threads: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [2, 4, 8, 16, 32, 64]
B = [avg(0.50,0.77,0.64,0.51,0.81), avg(1.11,1.22,1.13,1.11,1.01), avg(1.20,1.34,1.22,1.42,1.20), avg(1.34,1.20,1.04,1.42,1.18), avg(0.30,0.31,0.27,0.28,0.30), avg(0.13, 0.12,0.13,0.12,0.12)]
F = [avg(0.97,0.53,0.68,1.20,0.79), avg(1.17,1.05,1.11,1.07,0.92), avg(1.71,1.52,1.54,1.58,1.29), avg(1.11,1.34,1.24,1.37,1.21), avg(0.45,0.46,0.48,0.40,0.43), avg(0.18,0.17,0.17,0.17,0.17)]

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