# Time vs Number of threads
import matplotlib.pyplot as plt

N = [1, 2, 4, 8, 16, 32]
Y1 = [(178+184+210)/3, (150+164+134)/3, (116+120+74)/3, (33+34+34)/3, (25+26+27)/3, (26+27+26)/3]
Y2 = [(196+190+193)/3, (97+168+188)/3, (121+119+99)/3, (35+34+34)/3, (26+26+26)/3, (28+31+28)/3]
Y3 = [(190+184+182)/3, (187+99+125)/3, (114+118+53)/3, (29+64+32)/3, (25+25+27)/3, (27+27+26)/3]
Y4 = [(105+104+120)/3, (105+104+120)/3, (105+104+120)/3, (28+28+31)/3, (19+21+20)/3, (21+21+21)/3]

# make a big plot
plt.figure(figsize=(16, 9))

plt.plot(N, Y1, label='chunk', color='maroon')
plt.plot(N, Y2, label='mixed', color='green')
plt.plot(N, Y3, label='dynamic', color='purple')
plt.plot(N, Y4, label='Extra Credit', color='navy')

# show grid lines
plt.grid(True)

# show markers
plt.scatter(N, Y1, color='maroon')
plt.scatter(N, Y2, color='green')
plt.scatter(N, Y3, color='purple')
plt.scatter(N, Y4, color='navy')

plt.xlabel('K (Number of threads)')
plt.ylabel('Time')
plt.title('Time vs. Number of Threads')
plt.legend()
plt.show()