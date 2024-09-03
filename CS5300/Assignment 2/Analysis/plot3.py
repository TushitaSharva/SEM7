# Time vs Sparsity
import matplotlib.pyplot as plt

N = [20, 40, 60, 80]
Y1 = [(14+13+15)/3, (21+19+21)/3, (24+19+28)/3, (14+13+14)/3]
Y2 = [(13+13+13)/3, (22+27+18)/3, (19+20+19)/3, (13+14+14)/3]
Y3 = [(14+13+13)/3, (22+19+20)/3, (20+20+20)/3, (14+14+15)/3]
Y4 = [(14+14+14)/3, (20+20+20)/3, (20+20+24)/3, (15+15+16)/3]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, Y1, label='chunk', color='maroon')
plt.plot(N, Y2, label='mixed', color='green')
plt.plot(N, Y3, label='dynamic', color='purple')
plt.plot(N, Y4, label='extra credit', color='navy')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, Y1, color='maroon')
plt.scatter(N, Y2, color='green')
plt.scatter(N, Y3, color='purple')
plt.scatter(N, Y4, color='navy')

plt.xlabel('S (Sparsity)')
plt.ylabel('Time')
plt.title('Time vs. Sparsity')
plt.legend()
plt.show()