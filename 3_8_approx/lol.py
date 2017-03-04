import hpview3D as hp3d

f = open("3dfolds.txt","r")

w = open("3DSCORES.SCO", "w")

st = f.readline().split(" ")
while(len(st)==2):

    print st[0],st[1]

    seq = hp3d.HPFold(st[0])
    b3dfold = hp3d.make_absfold(st[1])
    if len(b3dfold) == len(seq) - 1:
        seq.SetAbsFold(b3dfold)
    else:
        print
        print "The folding has wrong length."
    b3dscore = seq.PrintFold(False)
    w.write(str(b3dscore)+"\n")
    st = f.readline().split(" ")

w.close()
print()

