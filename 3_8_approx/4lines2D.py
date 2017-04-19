##Makes 4 lines plot from files 3dfolds.txt and 3Ddata.txt outputs to 3DFoldstats.txt
import hpview3D as hp3d

r = open("SAB2D.csv","r")
w = open("4lines2D.csv","w")

w.write("Length 1/4*UpperBound UpperBound Algorithm_1 Algorithm_2\n")
vars = r.readline().strip("\n").split(" ")
while(len(vars)==6):
    print vars[0]

    seq = hp3d.HPFold(vars[1])

    sfold = hp3d.make_absfold(vars[2])
    seq.SetAbsFold(sfold)
    sscore = seq.PrintFold(False)

    bfold = hp3d.make_absfold(vars[3])
    seq.SetAbsFold(bfold)
    bscore = seq.PrintFold(False)


    w.write(str(vars[0]) + " " + str(vars[4]) + " " + str(vars[5])+ " "  + str(sscore)+ " " + str(bscore)+ "\n")
    vars = r.readline().strip("\n").split(" ")

w.close()
r.close()
print()

