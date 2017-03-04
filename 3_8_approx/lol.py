import hpview3D as hp3d

f = open("3dfolds.txt","r")
d = open("3Ddata.txt","r")
wstats = open("3DFoldstats.txt","w")

st = f.readline().split(" ")
dat = d.readline().split(" ")

while(len(st)==2):

    #print st[0],st[1]

    seq = hp3d.HPFold(st[0])
    b3dfold = hp3d.make_absfold(st[1])
    if len(b3dfold) == len(seq) - 1:
        seq.SetAbsFold(b3dfold)
    else:
        print
        print "The folding has wrong length."
    b3dscore = seq.PrintFold(False)
    wstats.write(str(dat[0]) + " " + str(dat[1]) + " " + str(b3dscore) + " " + str(dat[2]))
    st = f.readline().split(" ")
    dat = d.readline().split(" ")

wstats.close()
print()

