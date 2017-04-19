fin = open("yay 4 lines.txt","r")
fout = open("mod.txt","w")


fout.write("Length LowerBound Matched Score UpperBound\n")
n = fin.readline()
i=100
fout.write(str(i)+ " " + n)
i =int(i*1.1)
while(len(n)!=0):
    n = fin.readline()
    fout.write(str(i) +" "+ n)
    i = int(i * 1.1)

fout.close()
fin.close()
print()

