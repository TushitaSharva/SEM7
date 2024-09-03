# Time vs RowIncrement, N
import matplotlib.pyplot as plt

N = [10, 20, 30, 40, 50]
Y1 = [(27+27+32)/3, (25+31+25)/3, (27+25+26)/3, (25+25+25)/3, (26+25+25)/3]
Y2 = [(21+23+22)/3, (20+20+21)/3, (19+19+19)/3, (29+20+19)/3, (19+19+19)/3]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, Y1, label='Dynamic', color='purple')
plt.plot(N, Y2, label='Extra Credit', color='navy')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, Y1, color='purple')
plt.scatter(N, Y2, color='navy')

plt.xlabel('RowIncrement')
plt.ylabel('Time')
plt.title('Time vs. RowIncrement')
plt.legend()
plt.show()