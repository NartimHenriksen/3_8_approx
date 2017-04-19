import hpview3D as hp3d
import numpy as np
import matplotlib.pyplot as plt


x1=np.array([])
y1=np.array([])
y2=np.array([])
y3=np.array([])

replot=False ##change if u want
if(replot):##plot the scores we have stored
    fin = open("scores.csv", "r")
    fin.readline()#skips header line
    line = fin.readline().split(" ")

    while(len(line)==4):
        x1 = np.append(x1,line[0])
        y1 = np.append(y1,line[1])
        y2 = np.append(y2,line[2])
        y3 = np.append(y3,line[3])
        line = fin.readline().split(" ")

    fin.close()
else:##calc score from foldout.txt and store it and then plot
    fin = open("foldout.txt", "r")
    fout = open("scores.csv", "w")

    ##delete content of fout
    fout.seek(0)
    fout.truncate()
    ##
    fout.write("Length Algorithm1 Algorithm2 Algorithm3\n")
    args = fin.readline().split(" ")
    while(len(args)==5):
        print args[0]
        length=args[0]
        seq = hp3d.HPFold(args[1])

        seq.SetAbsFold(hp3d.make_absfold(args[2]))
        simplescore = seq.PrintFold(False)
        seq.SetAbsFold(hp3d.make_absfold(args[3]))
        blockscore = seq.PrintFold(False)
        seq.SetAbsFold(hp3d.make_absfold(args[4]))
        threedscore = seq.PrintFold(False)
        fout.write(str(length) + " " + str(simplescore) + " " + str(blockscore)+" " + str(threedscore) + "\n")
        x1 = np.append(x1,length)
        y1 = np.append(y1,simplescore)
        y2 = np.append(y2,blockscore)
        y3 = np.append(y3,threedscore)
        #wstats.write(str(b3dscore)+"\n")


        args = fin.readline().split(" ")

    fin.close()
    fout.close()

##Plot stuff below

alg1_line, = plt.plot(x1, y1, 'b+',label='Inline label') #markersize
alg1_line.set_label('Algorithm 1')

alg2_line, = plt.plot(x1, y2, 'rs', markerfacecolor='None',label='Inline label')
alg2_line.set_label('Algorithm 2')

alg3_line, = plt.plot(x1, y3, 'g^', markerfacecolor='None', label='Inline label')
alg3_line.set_label('Algorithm 3')

plt.xlabel('Length')
plt.ylabel('Score')
plt.legend()
plt.grid(b=True, which='major', color='0.65',linestyle=':')



plt.show()
fig=plt.figure();
fig.savefig('foo.pdf')#doesnt work yet