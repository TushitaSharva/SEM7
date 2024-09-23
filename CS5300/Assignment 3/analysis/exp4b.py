# Throughput Analysis with varying k [WORST]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)


K = [5, 10, 15, 20, 25]
B = [avg(42,47,39,51,79), avg(93,67,101,112,83), avg(124,123,184,163,150), avg(292,239,254,226,222), avg(274,229,376,259,260)]
F = [avg(46,53,32,51,43), avg(100,96,159,102,98), avg(136,154,169,117,155), avg(196,212,261,193,196), avg(295,263,314,198,281)]

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