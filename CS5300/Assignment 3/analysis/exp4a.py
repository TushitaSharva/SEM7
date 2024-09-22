# Throughput Analysis with varying k [AVG]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [5, 10, 15, 20, 25]
B = [avg(37,41,35,47,72), avg(87,59,93,102,74), avg(115,111,177,152,137), avg(278,225,244,212,205), avg(258,205,361,240,240)]
F = [avg(40,44,28,46,33), avg(91,83,149,92,85), avg(123,148,152,105,143), avg(184,198,244,183,182), avg(277,253,296,190,267)]

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