import hpview

f = open("folds.txt","r")

w = open("SCORES.SCO", "w")

while(f.readline()):
    st = f.readline().split(" ")
    print st[0],st[1]

    seq = hpview.HPFold(st[0])
    simplefold = hpview.make_absfold(st[1])
    blockfold = hpview.make_absfold(st[2])
    if len(simplefold) == len(seq) - 1:
        seq.SetAbsFold(simplefold)
    else:
        print
        print "The folding has wrong length."
    simplescore = seq.PrintFold()


    if len(blockfold) == len(seq) - 1:
        seq.SetAbsFold(blockfold)

    blockscore = seq.PrintFold()

    w.write("%d %d\n"%(simplescore,blockscore))

w.close()
print()

