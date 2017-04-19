##Makes 4 lines plot from files 3dfolds.txt and 3Ddata.txt outputs to 3DFoldstats.txt
import hpview3D as hp3d

r = open("SAB3D.csv","r")
w = open("4lines3D.csv","w")

w.write("Length 3/8*UpperBound UpperBound Algorithm_3\n")
vars = r.readline().strip("\n").split(" ")
while(len(vars)==5):
    print vars[0]

    seq = hp3d.HPFold(vars[1])

    sfold = hp3d.make_absfold(vars[2])
    seq.SetAbsFold(sfold)
    sscore = seq.PrintFold(False)


    w.write(str(vars[0]) + " " + str(vars[3]) + " " + str(vars[4])+ " "  + str(sscore)+ "\n")
    vars = r.readline().strip("\n").split(" ")

w.close()
r.close()
print()

