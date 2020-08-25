#!/usr/bin/env python3
import argparse
import genericIO
import GenJob
import GenSplit
import numpy as np
import numba
import copy
import math
import threading

mins={}
maxs={}
class windowKey(GenJob.irregSpace):
    def __init__(self,inputType,synch, mins,maxs):
        """Intialize object

            inputType - Input type
            synch - Whether or not we are synching headers and data
            mins - Dictionary containing the minimum for each key
            maxs - Dictionary containing the maximim for each key
        """
        super().__init__(self.windowIt,0,0,inputType=inputType,hasOutput=False)
        self._lock=threading.Lock() 
        self._mins=copy.deepcopy(mins)
        self._maxs=copy.deepcopy(maxs)
        self._synch=synch
        self._done=0
        self._typ=inputType
        
    def windowIt(self,ina,outa):
        """Window a buffer

        ina - Input vector
        outa - Output vector
        """
        keep = np.ones((ina._header._nh,), dtype=bool)
        for k,v in self._mins.items():
            keep,nc=parseIt(ina._header.getKey(k)._vals,keep,v,self._maxs[k])
        if nc>0:
            outa.noGrid()
            outa.shrinkZero(nc)
            head=SepIrregVector.headerBlock(nc,drn=ina._drn,keyOrder=ina._keyOrder)
            parseKey(keep,ina._header.getKey(k)._vals,head.getkey(k)._vals)
            if self._synch:
                parseTraces(keep,ina._traces,outa._traces)
        

                


 

@numba.jit(nopython=True)
def parseIt(vals,keep,mn,mx):
    """
      Return whether or not a trace is within window
      """
    nc=0
    for i in range(vals.shape[0]):
        if vals[i] < mn:
            keep[i]=False
        else if vals[i] > mx:
            keep[i]=False
        if keep[i]:
            nc=nc+1
    return keep,nc

@numba.jit(nopython=True)
def parseKey(keep,inA,outA):
    """
     Put subset of inA (controled by keep) into outA
      """
    nc=0
    for i in range(inA.shape[0]):
        if keep[i]:
            outA[nc]=inA[i]
            nc+=1

@numba.jit(nopython=True)
def parseTraces(keep,inA,outA):
    """
     Put subset of inA (controled by keep) into outA
      """
    nc=0
    for i in range(inA.shape[0]):
        if keep[i]:
            outA[nc,:]=inA[i,:]
            nc+=1

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Print header attributes')
    parser.add_argument('input', metavar='Input', type=str,
                        help='Input file')                 
    parser.add_argument("--io", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    parser.add_argument("--memory",type=int,help="Memory in terms of GB",default=2)
    parser.add_argument("--synch",type=bool,help="Synchornize headers and data",default=False)

    parser.add_argument("--print_pct",type=float,help="Print progress every X pct (above 100 means no printing)",default=101)
    parser.add_argument("--keyList",type=str,help="List of keys separated by :, defaults to all keys",default=None)
    parser.add_argument("--key",help="Key name minimum maximum",nargs=3, action='append')
    args = parser.parse_args()

    ioIn=genericIO.defaultIO

    if args.io:
        ioIn=genericIO.io(args.io)
    
    if "irregularFile" !=ioIn.getFileType(args.input):
        raise "File is not an irregular file"

    inFile=ioIn.getIrregFile(args.input)

    fileKeys=inFile.getHeaderKeys()
    keys=args.key
    for k in keys:
        if not k[0] in fileKeys:
            raise Exception("key %s does not exist"%k)
        mins[k]=k[1]
        maxs[k]=k[2]
    
 

    job=windowJob(inFile.getStorageType(),args.synch,mins,maxs)
    job.setCompleteHyperOut(inFile.getHyper())
    job.setInputFile(inFile)
    if args.synch:
        split=GenSplit.serialIrregSpace(job, args.memory)
    else:
        split=GenSplit.serialIrregHeaderSpace(job, args.memory)

    split.loop(args.print_pct)



