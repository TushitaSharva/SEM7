# Throughput Analysis with varying threads: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [1, 2, 4, 8, 16, 32]
DYNAMIC = [86250, 45024, 26454, 19024, 20402, 23557]
CHUNK = [86860, 51797, 34509, 21895, 18275, 19123]
SEQUENTIAL = [85465, 85905, 86118, 86830, 86424, 89056]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, DYNAMIC, label='Dynamic', color='purple')
plt.plot(N, CHUNK, label='Chunk', color='green')
plt.plot(N, SEQUENTIAL, label='Sequential', color='navy')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, DYNAMIC, color='purple')
plt.scatter(N, CHUNK, color='green')
plt.scatter(N, SEQUENTIAL, color='navy')

plt.xlabel('N (Number of threads)')
plt.ylabel('Time taken')
plt.title('Number of threads vs Time taken for 50000 vertices graph')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()