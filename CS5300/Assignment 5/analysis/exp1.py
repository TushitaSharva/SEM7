# Throughput Analysis with varying k: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


t = [5, 10, 15, 20, 25]
P50 = [325/11071, 46/669, 53/5083, 80/10129, 167/11078]
P10 = [0.035, 0.024, 0.022, 0.019, 0.015]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(t, P10, label='P = 10', color='purple')
plt.plot(t, P50, label='P = 50', color='green')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(t, P10, color='purple')
plt.scatter(t, P50, color='green')

plt.xlabel('n')
plt.ylabel('throughput')
plt.title('n vs throughput')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()