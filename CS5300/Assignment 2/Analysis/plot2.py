# Time vs Number of threads
import matplotlib.pyplot as plt

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5

N = [2, 4, 8, 16, 32]
Y1 = [avg(84,85,96,90,99), avg(55,50,51,51,54), avg(30,30,30,30,35), avg(19,31,19,38,19), avg(25,21,21,36,25)]
Y2 = [avg(86,86,99,88,86), avg(54,52,51,53,51), avg(34,29,30,30,31), avg(19,19,20,32,19), avg(28,25,22,23,22)]
Y3 = [avg(81,91,82,82,86), avg(54,51,49,49,50), avg(30,30,29,30,30), avg(20,19,19,20,19), avg(22,19,19,20,21)]

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

plt.xlabel('K (Number of threads)')
plt.ylabel('Time')
plt.title('Time vs. Number of Threads')
plt.legend()
plt.show()