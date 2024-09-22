# Average Entry Time with varying threads [AVG]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [2, 4, 8, 16, 32, 64]
B = [avg(5,3,1,1,2), avg(2,4,5,6,9), avg(19,23,27,29,35), avg(87,60,136,109,96), avg(1041,1067,1050,947,1046), avg(4839,4862,4935,4846,5152)]
F = [avg(2,1,0,4,5), avg(4,9,15,6,11), avg(25,31,21,29,24), avg(81,52,77,154,92), avg(691,594,807,654,615), avg(3575,2026,3469,3486,3225)]

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