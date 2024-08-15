# Time vs. Size, N: PLot a graph with X values being 1000, 2000, .. 5000 and the Y values being the values provided by arrays. There are 3 Ys, Y1, Y2, Y3, plot each of them in same graph with different colors and legends.

import matplotlib.pyplot as plt

N = [1000, 2000, 3000, 4000, 5000]
Y1 = [(5+17+15)/3, (10+10+10)/3, (15+15+16)/3, (20+20+20)/3, (26+25+26)/3] # chunk
Y2 = [(17+16+5)/3, (10+10+12)/3, (16+15+15)/3, (21+21+20)/3, (26+26+43)/3] # mixed
Y3 = [(18+5+17)/3, (10+10+12)/3, (15+18+15)/3, (20+22+20)/3, (25+25+26)/3] # dynamic
Y4 = [(14+10+8)/3, (7+7+7)/3, (11+12+11)/3, (14+15+15)/3, (19+19+19)/3] # guided

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

plt.xlabel('N (Number of rows of matrix)')
plt.ylabel('Time')
plt.title('Time vs. Matrix Size')
plt.legend()
plt.show()