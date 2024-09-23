# Throughput Analysis with varying k [WORST]: 

import matplotlib.pyplot as plt
import os

def avg(a,b,c,d,e):
    return (a+b+c+d+e)


# ===================================================
# Experiment: ./inputs/4/k-05.txt
# [Bakery] Throughput, Average, Worst: [1.09589, 9.6875, 11.6]
# [Bakery] Throughput, Average, Worst: [0.851064, 14.05, 15.8]
# [Bakery] Throughput, Average, Worst: [1.05263, 11.8, 13.2]
# [Bakery] Throughput, Average, Worst: [1.45455, 5.5625, 7]
# [Bakery] Throughput, Average, Worst: [1.56863, 6.125, 7]
# ---------------------------------------------------
# [Filter] Throughput, Average, Worst: [1.19403, 9.125, 10.4]
# [Filter] Throughput, Average, Worst: [0.952381, 12.375, 14]
# [Filter] Throughput, Average, Worst: [1.40351, 6.95, 8]
# [Filter] Throughput, Average, Worst: [0.869565, 14.0875, 16.4]
# [Filter] Throughput, Average, Worst: [1.25, 6.7875, 7.8]
# ===================================================
# Experiment: ./inputs/4/k-10.txt
# [Bakery] Throughput, Average, Worst: [1.18519, 8.9875, 10.4]
# [Bakery] Throughput, Average, Worst: [0.833333, 15.4312, 16.6]
# [Bakery] Throughput, Average, Worst: [0.909091, 13.3562, 14.1]
# [Bakery] Throughput, Average, Worst: [1.15942, 9.93125, 10.9]
# [Bakery] Throughput, Average, Worst: [0.883978, 12.925, 13.7]
# ---------------------------------------------------
# [Filter] Throughput, Average, Worst: [0.903955, 13.175, 14]
# [Filter] Throughput, Average, Worst: [1.24031, 8.625, 9.3]
# [Filter] Throughput, Average, Worst: [1.25984, 8.95625, 9.9]
# [Filter] Throughput, Average, Worst: [1.00629, 11.3313, 12.3]
# [Filter] Throughput, Average, Worst: [1.05263, 11.6375, 12.7]
# ===================================================
# Experiment: ./inputs/4/k-15.txt
# [Bakery] Throughput, Average, Worst: [1.15942, 10.3083, 10.9333]
# [Bakery] Throughput, Average, Worst: [1.05727, 10.875, 11.8]
# [Bakery] Throughput, Average, Worst: [1.21827, 9.56667, 10.1333]
# [Bakery] Throughput, Average, Worst: [1.53846, 5.79167, 6.66667]
# [Bakery] Throughput, Average, Worst: [0.808081, 15.6083, 16.5333]
# ---------------------------------------------------
# [Filter] Throughput, Average, Worst: [1.16505, 9.99583, 11]
# [Filter] Throughput, Average, Worst: [1.21827, 9.63333, 10.6]
# [Filter] Throughput, Average, Worst: [0.991736, 12.5708, 13.1333]
# [Filter] Throughput, Average, Worst: [1.5, 7.25833, 7.86667]
# [Filter] Throughput, Average, Worst: [1.5, 7.25417, 7.73333]
# ===================================================
# Experiment: ./inputs/4/k-20.txt
# [Bakery] Throughput, Average, Worst: [1.01587, 12.0406, 12.5]
# [Bakery] Throughput, Average, Worst: [1.35021, 8.64375, 9.25]
# [Bakery] Throughput, Average, Worst: [1.0596, 11.6562, 12.8]
# [Bakery] Throughput, Average, Worst: [1.34454, 8.34062, 8.95]
# [Bakery] Throughput, Average, Worst: [1.70213, 6.26875, 6.65]
# ---------------------------------------------------
# [Filter] Throughput, Average, Worst: [1.44796, 7.70312, 8.45]
# [Filter] Throughput, Average, Worst: [1.19403, 9.60625, 10.3]
# [Filter] Throughput, Average, Worst: [1.49533, 7.29063, 8.05]
# [Filter] Throughput, Average, Worst: [1.07383, 10.9125, 11.65]
# [Filter] Throughput, Average, Worst: [1.40351, 8.18437, 8.75]
# ===================================================
# Experiment: ./inputs/4/k-25.txt
# [Bakery] Throughput, Average, Worst: [1.25392, 9.3325, 10]
# [Bakery] Throughput, Average, Worst: [1.41844, 8.1175, 8.44]
# [Bakery] Throughput, Average, Worst: [1.3468, 8.6425, 9.2]
# [Bakery] Throughput, Average, Worst: [1.12676, 10.6425, 11.32]
# [Bakery] Throughput, Average, Worst: [1.35593, 8.195, 8.68]
# ---------------------------------------------------
# [Filter] Throughput, Average, Worst: [1.17302, 9.635, 10.28]
# [Filter] Throughput, Average, Worst: [1.26183, 8.92, 9.4]
# [Filter] Throughput, Average, Worst: [1.35135, 8.4825, 8.96]
# [Filter] Throughput, Average, Worst: [1.13636, 10.7925, 11.72]
# [Filter] Throughput, Average, Worst: [1.28617, 8.905, 9.2]
# ===================================================

K = [5, 10, 15, 20, 25]
B = [avg(11.6,15.8,13.2,7,7), avg(10.4,16.6,14.1,10.9,13.7), avg(10.93,11.8,10.13,6.67,16.53), avg(12.5,9.25,12.8,8.95,6.65), avg(10,8.44,9.2,11.32,8.68)]
F = [avg(10.4,14,8,16.4,7.8), avg(14,9.3,9.9,12.3,12.7), avg(11,10.6,13.13,7.86,7.73), avg(8.45,10.3,8.05,11.65,8.75), avg(10.28,9.4,8.96,11.72,9.2)]

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