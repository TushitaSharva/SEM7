# Time vs Sparsity
import matplotlib.pyplot as plt

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5

N = [20, 40, 60, 80]
Y1 = [avg(14,13,17,12,12), avg(19,19,19,19,40), avg(24,19,26,20,18), avg(21,20,20,20,20)]
Y2 = [avg(13,12,15,12,12), avg(19,19,19,19,19), avg(19,19,22,19,40), avg(20,21,21,20,21)]
Y3 = [avg(13,13,13,18,14), avg(20,25,19,19,19), avg(20,20,20,24,20), avg(20,21,21,20,21)]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, Y1, label='chunk', color='maroon')
plt.plot(N, Y2, label='mixed', color='green')
plt.plot(N, Y3, label='dynamic', color='purple')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, Y1, color='maroon')
plt.scatter(N, Y2, color='green')
plt.scatter(N, Y3, color='purple')

plt.xlabel('S (Sparsity)')
plt.ylabel('Time')
plt.title('Sparsity vs. Time')
plt.legend()
plt.show()