import numpy as np
import matplotlib.pyplot as plt





x1=np.array([])
y1=np.array([])
y2=np.array([])
y3=np.array([])
y4=np.array([])
y5=np.array([])
y6=np.array([])


fin = open("cat.csv", "r")
fin.readline()#skips header line
line = fin.readline().split(" ")

while(len(line)==8):
    x1 = np.append(x1,line[0])
    y1 = np.append(y1,int(line[1]))
    y2 = np.append(y2,line[2])
    y3 = np.append(y3,line[3])
    y4 = np.append(y4,line[5])
    y5 = np.append(y5,line[6])
    y6 = np.append(y6,line[7])
    line = fin.readline().split(" ")

fin.close()

print(line)
print(x1)
print(y5)
##Plot stuff below
fig, ax1 = plt.subplots()
ax2 = ax1.twinx()
alg1_line, = ax1.plot(x1, y1, 'b+',label='Inline label') #markersize
alg1_line.set_label('Algorithm 1_50%')

alg2_line, = ax1.plot(x1, y2, 'rs', markerfacecolor='None',label='Inline label')
alg2_line.set_label('Algorithm 2_50%')

alg3_line, = ax1.plot(x1, y3, 'g^', markerfacecolor='None', label='Inline label')
alg3_line.set_label('Algorithm 3_50%')
alg4_line, = ax2.plot(x1, y4, markerfacecolor='None', label='Inline label')
alg4_line.set_label('Algorithm 1_10%')
alg5_line, = ax2.plot(x1, y5,  color='green', label='Inline label')
alg5_line.set_label('Algorithm 2_10%')
alg6_line, = ax2.plot(x1, y6, color='red', label='Inline label')
alg6_line.set_label('Algorithm 3_10%')

plt.xlabel('Length')
plt.ylabel('Score')
plt.legend()
plt.grid(b=True, which='major', color='0.65',linestyle=':')



plt.show()
fig=plt.figure();
fig.savefig('foo.pdf')#doesnt work yet