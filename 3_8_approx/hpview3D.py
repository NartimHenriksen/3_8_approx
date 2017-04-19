#! /usr/bin/python
# -*- coding: utf-8 -*-
#
#  hpview3D.py
#
#  Displays a 3D HP folding
#
#  Usage:
#
#  hpview.py <seq> <fold>
#
#  where <seq> is a string over the alphabet {h,p} and <fold> is a
#  folding of the string in either relative or absolute format.
#
#
#  A folding in absolute format is a sequence over {U,D,L,R,F,B}, which
#  describes the fold as a sequence of steps going
#  up, down, left or right, or forwards and backwards
#  If an 'H' or 'h' s(cores) with an H-monomer in the layer "before it" (the one printed before),
#  it is instead denoted with 'S' or 's'. If it neighbours an element in it, it is marked with q, w or W.
#
#  Originially conceived by Christian Storm, and extended to 3D by Martin Henriksen
#

import sys

#####################################################################
# Functions
#####################################################################

class HPFold:

    def __init__ (self, s):
        legal = {'h':'h', 'p':'p', 'H':'h', 'P':'p','1':'h','0':'p'}
        self.seq = []
        i = 1
        for c in s:
            if legal.has_key(c):
                if legal[c] == 'h' and i % 2 == 0:
                    self.seq.append('H')
                else:
                    self.seq.append(legal[c])
                i = i + 1

    def __len__ (self):
        return len(self.seq)

    def SetAbsFold (self, absfold):
        """
        Fold seq according to a description in absolute format, i.e.
        s sequence of {n,s,e,w}'s which describe each step as (n)orth,
        (s)outh, (e)ast, or (w)est.
        """
        self.legal_fold = (True, 0)
        self.grid = {}
        self.grid[0,0,0] = [0]
        i = j = l = self.min_i= self.max_i = self.min_j = self.max_j = self.min_l = self.max_l = 0
        k = 1
        for step in absfold:
            if step == 'u':
                i = i - 1
            elif step == 'd':
                i = i + 1
            elif step == 'r':
                j = j + 1
            elif step == 'l':
                j = j - 1
            elif step == 'f':
                l = l - 1
            elif step == 'b':
                l = l + 1
            if self.grid.has_key((i,j,l)):
                self.legal_fold = (False, k)
                self.grid[i,j,l].append(k)
            else:
                self.grid[i,j,l] = [k]
            k = k + 1
            self.min_i = min(i, self.min_i)
            self.max_i = max(i, self.max_i)
            self.min_j = min(j, self.min_j)
            self.max_j = max(j, self.max_j)     
            self.min_l = min(l, self.min_l)
            self.max_l = max(l, self.max_l)                      
        return self.legal_fold[0]

    def ContainNeighbors(self, l1, l2):
        """
        Returns true if there exists k1 in l1 and k2 in l2 such that
        abs(k1-k2) is 1, i.e. if the indices in l1 and l2 contain a
        pair of neighbors in seq.
        """
        res = False
        for k1 in l1:
            for k2 in l2:
                if abs(k1-k2) == 1:
                    res = True
        return res

    def ContainHHs(self, l1, l2):
        """
        Returns true if there exists k1 in l1 and k2 in l2 where there
        is a 'h' at position k1 and k2 in seq, i.e. if the indices in
        l1 and l2 contain a pair which can make a h-h bond.
        """
        res = False
        for k1 in l1:
            for k2 in l2:
                if (self.seq[k1] == "h" or self.seq[k1] == "H") and (self.seq[k2] == "h" or self.seq[k2] == "H"):
                    res = True
        return res
        
    def PrintFold (self,visual=True):
        """
        Print fold and output its score
        """
        score = 0
        if visual:
            print

        for l in xrange(self.max_l,self.min_l-1,-1):
            for i in xrange(self.min_i, self.max_i+1):
                for j in xrange(self.min_j, self.max_j+1):
                    if self.grid.has_key((i,j,l)):
                        l1 = self.grid[i,j,l]

                        neighborsAbove=False
                        scoresAbove=False
                        if self.grid.has_key((i,j,l+1)):
                            l3 = self.grid[i,j,l+1]
                            if self.ContainNeighbors(l1,l3):
                                neighborsAbove=True
                            elif self.ContainHHs(l1, l3):
                                scoresAbove=True
                                score = score + 1
                        if visual:#dont even enter here unless visual
                            if len(l1) == 1:
                                if neighborsAbove:
                                    if self.seq[l1[0]]=="h":
                                        print "w", #"\xc4\xa5",

                                    elif self.seq[l1[0]]=="H":
                                        print "W",#"\xc4\xa4",
                                    else:
                                        print "q",
                                elif scoresAbove:
                                    if self.seq[l1[0]]=="h":
                                        print "s",
                                    else:
                                        print "S",
                                else:
                                    print self.seq[l1[0]],

                            else:
                                print "X",


                        if self.grid.has_key((i,j+1,l)):
                            l2 = self.grid[i,j+1,l]
                            if self.ContainNeighbors(l1,l2):
                                if visual:
                                    print "-",
                            elif self.ContainHHs(l1, l2):
                                if visual:
                                    print "*",
                                score = score + 1
                            else:
                                if visual:
                                    print " ",
                        else:
                            if visual:
                                print " ",
                    else:
                        if visual:
                            print ".",
                            print " ",
                if visual:
                    print

                for j in xrange(self.min_j, self.max_j+1):
                    if self.grid.has_key((i,j,l)) and self.grid.has_key((i+1,j,l)):
                        l1 = self.grid[i,j,l]
                        l2 = self.grid[i+1,j,l]
                        if self.ContainNeighbors(l1,l2):
                            if visual:
                                print "|",
                        elif self.ContainHHs(l1,l2):

                            if visual:
                                print "*",
                            score = score + 1
                        else:

                            if visual:
                                print " ",
                    else:

                        if visual:
                            print " ",

                    if visual:
                        print " ",

                if visual:
                    print

            if visual:
                print '----'*((self.max_j+1)-self.min_j)
		
        if self.legal_fold[0]:
            if visual:
                print "Score: %d" % (score)
        else:
            print "Illegal fold after %d steps" % (self.legal_fold[1]) 
        return score##

#####################################################################
# Functions
#####################################################################

def make_absfold(f):

    absfold = []
    for c in f.lower():
        if c == 'u' or c == 'd' or c == 'l' or c == 'r' or c=='f' or c=='b':
            absfold.append(c)
    return absfold




def print_usage():
    print """
Usage:

hpview.py <seq> <fold>


  where <seq> is a string over the alphabet {h,p} and <fold> is a
  folding of the string in either relative or absolute format.


  A folding in absolute format is a sequence over {U,D,L,R,F,B}, which
  describes the fold as a sequence of steps going
  up, down, left, right, forwards or backwards.
  If an 'H' or 'h' s(cores) with an H-monomer in the layer "before it" (the one printed before),
  it is instead denoted with 'S' or 's'. If it neighbours an element in it, it is marked with q,w or W.
"""
    
#####################################################################
# Main
#####################################################################
    
if __name__ == "__main__":

    if len(sys.argv) < 3:
        print
        print "Wrong number of arguments."
        print_usage()
        sys.exit(1)

    seq = HPFold(sys.argv[1])

    if len(seq) != len(sys.argv[1]):
        print
        print "The sequence %s contains illegal characters." % (sys.argv[1])
        print_usage()
        sys.exit(1)
        
    absfold = make_absfold(sys.argv[2])
    if len(absfold) != len(sys.argv[2]):
        print
        print "The folding %s contains illegal characters." % (sys.argv[2])
        sys.exit(1)
        
    if len(absfold) == len(seq) - 1:
        seq.SetAbsFold(absfold)
    else:
        print
        print "The folding %s has wrong length." % (sys.argv[2])
        print_usage()
        sys.exit(1)

    seq.PrintFold()
