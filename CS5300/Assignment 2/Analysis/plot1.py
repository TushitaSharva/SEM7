# Time vs. Size, N: PLot a graph with X values being 1000, 2000, .. 5000 and the Y values being the values provided by arrays. There are 3 Ys, Y1, Y2, Y3, plot each of them in same graph with different colors and legends.

import matplotlib.pyplot as plt

def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5


N = [1000, 2000, 3000, 4000, 5000]
Y1 = [avg(1,4,1,1,1), avg(3,3,12,10,9), avg(8,9,7,7,17), avg(12,12,12,27,12), avg(19,19,19,19,19)] # chunk
Y2 = [avg(1,1,2,1,1), avg(4,3,3,3,3), avg(8,7,7,7,7), avg(12,12,12,12,12), avg(19,19,27,19,19)] # mixed
Y3 = [avg(2,2,2,8,1), avg(3,4,4,3,4), avg(7,7,7,7,7), avg(17,12,12,12,12), avg(19,20,24,19,19)] # dynamic

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

plt.xlabel('N (Number of rows of matrix)')
plt.ylabel('Time')
plt.title('Time vs. Matrix Size')
plt.legend()
plt.show()