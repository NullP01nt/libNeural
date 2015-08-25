#!/usr/bin/env python

import random

class TrainingSampleGenerator():
    def __init__(self):
        pass
    def process(self,topology, numsamples, func,fname):
        with open(fname,"w") as sf:
            sf.write("topo: "+" ".join( [ str(x) for x in topology ] )+"\n")
            numinputs=topology[0]
            for i in range(numsamples):
                inputs=[]
                outputs=[]
                for j in range(numinputs):
                    inputs.append(int(random.getrandbits(1)))
                outputs = func(inputs)
                instr = "i: "+" ".join([ str(x) for x in inputs ])+"\n"
                outstr = "o: "+" ".join([ str(x) for x in outputs ])+"\n"
                sf.write(instr)
                sf.write(outstr)
            sf.close()

def bool_and(inputs):
    return [ float(inputs[0]&inputs[1]) ]

def bool_or(inputs):
    return [ float(inputs[0]|inputs[1]) ]

def bool_nand(inputs):
    return [ float( not inputs[0]&inputs[1] ) ]

def bool_nor(inputs):
    return [ float(not inputs[0]|inputs[1]) ]

def bool_xor(inputs):
    return [ float(inputs[0]^inputs[1]) ]

def bool_xnor(inputs):
    return [ float(not inputs[0]^inputs[1]) ]

def printtable(head,func):
    print "---"+head+"---\n"
    for A in range(2):
        for B in range(2):
            print str(A)+"\t"+str(B)+"\t"+str(func( [A,B] )[0])+"\n"
    print "\n\n"

if __name__=="__main__":
    topo=[2,4,1]
    smps=2000
    tsg = TrainingSampleGenerator()
    tsg.process(topo,smps,bool_and,"DS_AND.txt")
    tsg.process(topo,smps,bool_or,"DS_OR.txt")
    tsg.process(topo,smps,bool_nand,"DS_NAND.txt")
    tsg.process(topo,smps,bool_nor,"DS_NOR.txt")
    tsg.process(topo,smps,bool_xor,"DS_XOR.txt")
    tsg.process(topo,smps,bool_xnor,"DS_XNOR.txt")
