#!/usr/bin/env python

import random

def XORGenerator():
    with open("/tmp/trainingData.txt","w") as f:
        f.write("topo: 2 4 1\n")
        for i in range(2000):
            n1 = int(random.getrandbits(1))
            n2 = int(random.getrandbits(1))
            t = float(n1^n2)
            instr = 'i: '+str(float(n1))+" "+str(float(n2))+'\n'
            outstr = 'o: '+str(t)+'\n'
            f.write(instr)
            f.write(outstr)
        f.close()

if __name__=="__main__":
    XORGenerator()
