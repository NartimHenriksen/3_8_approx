##Makes 4 lines plot from files 3dfolds.txt and 3Ddata.txt outputs to 3DFoldstats.txt
import hpview3D as hp3d

f = open("3dfolds.txt","r")
d = open("3Ddata.txt","r")
w = open("3DFoldstats.txt","w")

w.write("Length LowerBound LowerBound_sim Matched Algorithm_3 UpperBound\n")
st = f.readline().split(" ")
dat = d.readline().split(" ")
while(len(st)==3):
    print st[0]

    seq = hp3d.HPFold(st[1])
    b3dfold = hp3d.make_absfold(st[2])
    if len(b3dfold) == len(seq) - 1:
        seq.SetAbsFold(b3dfold)
    else:
        print
        print "The folding has wrong length."
    b3dscore = seq.PrintFold(False)
    w.write(str(st[0]) + " " + str(dat[1]) + " " + str(dat[2])+ " "  + str(dat[3])+ " " + str(b3dscore) + " "+ str(dat[4]))
    st = f.readline().split(" ")
    dat = d.readline().split(" ")

w.close()
f.close()
d.close()
print()

