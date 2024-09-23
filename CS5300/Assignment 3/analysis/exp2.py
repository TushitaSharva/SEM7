# Throughput Analysis with varying k: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


K = [5, 10, 15, 20, 25]
B = [avg(1.38,1.00,1.11,0.95,1.38), avg(1.19,1.50,1.67,0.71,1.19), avg(1.22,1.01,1.17,1.28,1.66), avg(1.30,1.52,0.89,1.46,0.85), avg(1.32,1.36,1.13,1.09,1.03)]
F = [avg(1.03,1.21,1.31,1.29,1.11), avg(1.19,1.10,0.75,1.05,1.08), avg(1.45,1.51,1.48,1.54,1.41), avg(1.13,1.21,1.33,1.34,1.45), avg(1.37,1.32,1.32,1.19,1.10)]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(K, B, label='Bakery', color='purple')
plt.plot(K, F, label='Filter', color='green')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(K, B, color='purple')
plt.scatter(K, F, color='green')

plt.xlabel('K (Number of times entering critical section)')
plt.ylabel('Throughput')
plt.title('Throughput Analysis with varying times entering critical section')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()