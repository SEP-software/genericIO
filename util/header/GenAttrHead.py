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


import copy

class headerStats:
    def __init__(self,typ):
        self._mn=1e99
        self._mx=-1e99
        self._sm=0
        self._nzero=0
        self._typ=typ
    def update(self,mn,mx,sm,nzero):
        self._min=min(self._mn,mn)
        self._max=max(self._mx,mx)
        self._sm+=sm
        self._nzero+=nzero



class attrJob(GenJob.irregSpace):
    def __init__(self,inputType):
        """Intialize object

            inputType - Input type
        """
        super().__init__(self.calcStats,0,0,inputType=inputType,hasOutput=False)
        self._lock=threading.Lock() 
        self._first=True
        self._stats={}
        self._types={}
    def calcStats(self,ina,dummy):
        """Convert a buffer from one type to another

        ina - Input vector
        dummy - Dummy argument
        """

        if self._first:
            self._types=ina._header.getKeyTypes()
            self._first=False
            for k in ina._header._keys.keys():
                self._stats[k]=headerStats(self._types[k])
        
        for k,typ in self._types.items():  
            if k == "CDP":
                print(ina._header.getKey(k)._vals[1:50],"SSS")  
                if typ == "dataInt":
                    mn,mx,sm,nzero=calcIntStats(ina._header.getKey(k)._vals)
                elif typ == "dataFloat":
                    mn,mx,sm,nzero=calcRealStats(ina._header.getKey(k)._vals)
                else:
                    raise Exception("key=%s type=%s"%(k,typ))
                print(k,"before update")
                self._stats[k].update(mn,mx,sm,nzero)
                print("after update")
       # self._lock.release()

        
@numba.jit(nopython=True, locals={'sm': numba.float64,"sqs":numba.float64,"nzero":numba.int64})
def calcRealStats(inA):
    """
      Return min,max,sum,sumsq,nzeros
      """
    nzero=0
    sm=inA[0]
    sqs=inA[0]
    mn=inA[0]
    mx=inA[0]
    imin=0
    imax=0
    if inA[0]!=0: 
        nzero+=1
    for i in range(1,inA.shape[0]):
        if inA[i]  < mn:
            mn=inA[i]
        if inA[i] >mx:
            mx=inA[i]
        sm+=inA[i]
        if inA[i] !=0:
            nzero+=1
    return mn,mx,sm,nzero

@numba.jit(nopython=True, locals={'sm': numba.int64,"sqs":numba.int64,"nzero":numba.int64})
def calcIntStats(inA):
    """
      Return min,max,sum,sumsq,nzeros
      """
    nzero=0
    sm=inA[0]
    sqs=inA[0]
    mn=inA[0]
    mx=inA[0]
    imin=0
    imax=0
    if inA[0]!=0: 
        nzero+=1
    for i in range(1,inA.shape[0]):
        if inA[i]  < mn:
            mn=inA[i]
        if inA[i] >mx:
            mx=inA[i]
        sm+=inA[i]
        if inA[i] !=0:
            nzero+=1
    return mn,mx,sm,nzero
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Print header attributes')
    parser.add_argument('input', metavar='Input', type=str,
                        help='Input file')                 
    parser.add_argument("--io", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    parser.add_argument("--memory",type=int,help="Memory in terms of GB",default=2)
    parser.add_argument("--print_pct",type=float,help="Print progress every X pct (above 100 means no printing)",default=101)
    parser.add_argument("--keyList",type=str,help="List of keys separated by :, defaults to all keys",default=None)

    args = parser.parse_args()

    ioIn=genericIO.defaultIO

    if args.io:
        ioIn=genericIO.io(args.io)
    

    inFile=ioIn.getIrregFile(args.input)
    job=attrJob(inFile.getStorageType())
    job.setCompleteHyperOut(inFile.getHyper())
    job.setInputFile(inFile)
    split=GenSplit.serialIrregHeaderSpace(job, args.memory)
    split.loop(args.print_pct)

    nmax=0
    keys=[]
    if not args.keyList==None:
        keys=args.keyList.split(":")
        kk=1
    else:
        kk=None

    for k in job._stats.keys():
        nmax=max(len(k),nmax)  
        if not kk:
            keys.append(k)

    for k,v in job._stats.items():
        sp=" "*(nmax-len(k)+1)
        if k in keys:
            mn=str(v._mn)
            mnS=" "*(10-len(mn))
            mx=str(v._mx)
            mxS=" "*(10-len(mx))
            nz=str(v._nzero)
            print("%s %s %s %s %s %s %s"%(k,sp,mn,mnS,mx,mxS,nz))









