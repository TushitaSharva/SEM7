# Throughput Analysis with varying k: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [5, 10, 15, 20, 25]
B = [avg(1.57,1.16,1.38,1.03,1.07), avg(0.92,0.88,1.34,1.32,1.30), avg(0.99,1.22,1.01,0.94,1.40), avg(1.40,0.98,1.08,1.34,1.24), avg(1.34,1.05,1.34,1.00,1.43)]
F = [avg(0.88,1.36,1.19,1.01,1.19), avg(1.06,1.27,1.86,1.37,1.45), avg(1.03,1.34,1.28,1.07,1.04), avg(1.26,0.98,1.33,1.16,1.32), avg(1.03,1.43,1.32,1.03,1.30)]

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