# Throughput Analysis with varying threads [WORST CASE]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [2, 4, 8, 16, 32, 64]
B = [avg(5,6,1,2,5), avg(5,9,8,8,10), avg(26,26,32,35,44), avg(99,70,146,123,106), avg(1068,1100,1080,973,1075), avg(4936,4964,5050,4943,5265)]
F = [avg(4,2,0,4,4), avg(6,10,17,11,16), avg(29,36,26,36,35), avg(92,58,85,175,104), avg(736,635,860,702,664), avg(3759,3224,3645,3628,3419)]

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