# Throughput Analysis with varying threads: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [10000, 20000, 30000, 40000, 50000]
DYNAMIC = [2824, 7972, 15267, 23430, 29074]
CHUNK = [1834, 5610, 10922, 17614, 17858]
SEQUENTIAL = [5726, 20820, 45535, 78103, 86485]

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

plt.xlabel('V (Vertices)')
plt.ylabel('Time taken')
plt.title('Vertices vs Time taken for constant density 5')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()