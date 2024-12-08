# Throughput Analysis with varying k: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


t = [5, 10, 15, 20, 25]
P10 = [1426/29, 4264/42, 3733/29, 8068/57, 8873/41]
P50 = [1426/42, 4265/104, 8067/105, 11070/115, 16497/236]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(t, P10, label='P = 50', color='purple')
plt.plot(t, P50, label='P = 10', color='green')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(t, P10, color='purple')
plt.scatter(t, P50, color='green')

plt.xlabel('t')
plt.ylabel('latency')
plt.title('t vs latency')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()