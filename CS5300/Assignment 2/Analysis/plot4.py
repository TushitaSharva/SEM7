# Time vs RowIncrement, N
import matplotlib.pyplot as plt
def avg(a,b,c,d,e):
    return (a+b+c+d+e)/5

N = [10, 20, 30, 40, 50]
Y1 = [avg(22,18,18,18,18), avg(18,24,18,18,22), avg(18,18,18,18,19), avg(18,18,18,18,19), avg(18,20,19,19,19)]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, Y1, label='Dynamic', color='purple')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, Y1, color='purple')

plt.xlabel('RowIncrement')
plt.ylabel('Time')
plt.yticks(range(17, 30))
plt.title('Time vs. RowIncrement')
plt.legend()
plt.show()