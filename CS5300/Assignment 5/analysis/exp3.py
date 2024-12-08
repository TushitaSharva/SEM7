# Throughput Analysis with varying k: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


p = [10, 20, 30, 40, 50]
time = [11071/202, 11071/111, 6862/45, 9864/76, 8864/41]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(p, time, label='P = 10', color='purple')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(p, time, color='purple')

plt.xlabel('p')
plt.ylabel('time taken')
plt.title('p vs time taken')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()