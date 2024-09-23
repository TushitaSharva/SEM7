# Throughput Analysis with varying k [AVG]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


K = [5, 10, 15, 20, 25]
B = [avg(9.68,14.05,11.80,5.56,6.12), avg(8.98,15.43,13.35,9.93,12.92), avg(10.30,10.87,9.57,5.80,15.61), avg(12.04,8.64,11.65,8.34,6.26), avg(9.33,8.11,8.64,10.64,8.19)]
F = [avg(9.12,12.38,6.95,14.08,6.78), avg(13.18,8.62,8.95,11.33,11.63), avg(9.99,9.63,12.57,7.25,7.25), avg(7.70,9.60,7.30,10.91,8.18), avg(9.635,8.92,8.4825,10.7925,8.905)]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(K, B, label='Bakery', color='purple')
plt.plot(K, F, label='Filter', color='green')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(K, B, color='purple')
plt.scatter(K, F, color='green')

plt.xlabel('N (Number of times entering critical section)')
plt.ylabel('Throughput')
plt.title('Throughput Analysis with varying times entering critical section')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()