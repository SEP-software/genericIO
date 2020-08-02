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
        self._mn=math.pow(10,80)
        self._mx=-math.pow(10,80)
        self._sm=0
        self._nzero=0
        self._typ=typ
    def update(self,mn,mx,sm,nzero):
        self._mn=min(self._mn,mn)
        self._mx=max(self._mx,mx)
        self._sm+=sm
        self._nzero+=nzero



class attrJob(GenJob.irregSpace):
    def __init__(self,inputType,first,last,keyT):
        """Intialize object

            inputType - Input type
            first - First header to gather statistics on
            last - Last header to gather statistics on
            keyT - Key type dictionary
        """
        super().__init__(self.calcStats,0,0,inputType=inputType,hasOutput=False)
        self._lock=threading.Lock() 
        self._first=first
        self._last=last
        self._types=keyT
        self._stats={}
        for k in self._types.keys():
            self._stats[k]=headerStats(self._types[k])
        self._f2=0
    def calcStats(self,ina,dummy):
        """Convert a buffer from one type to another

        ina - Input vector
        dummy - Dummy argument
        """
        b=max(0,self._first-self._f2)
        e=min(self._last-self._f2,ina._header._nh)
        if b>=0 and e <= ina._header._nh  and e>0:
            for k,typ in self._types.items():  
                if typ == "dataInt":
                    mn,mx,sm,nzero=calcIntStats(ina._header.getKey(k)[b:e])
                elif typ == "dataFloat":
                    mn,mx,sm,nzero=calcRealStats(ina._header.getKey(k)[b:e])
                else:
                    raise Exception("key=%s type=%s"%(k,typ))
                self._stats[k].update(mn,mx,sm,nzero)
        self._f2+=ina._header._nh
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
    parser.add_argument("--first",type=int,help="First key to print",default=None)
    parser.add_argument("--last",type=int,help="Last key to print",default=None)

    args = parser.parse_args()

    ioIn=genericIO.defaultIO

    if args.io:
        ioIn=genericIO.io(args.io)

    inFile=ioIn.getIrregFile(args.input)

    nh=inFile.getHyperHeader().axes[1].n
    last=nh
    first=0
    if args.first != None:
        first=args.first
    if args.last !=None:
        last=args.last

    fileTypes=inFile.getHeaderKeyTypes()


    nmax=0
    if not args.keyList==None:
        keys=args.keyList.split(":")
        keyTypes={}
        for k in keys:
            if not k in fileTypes:
                raise Exception("Key %s does not exist "%k)
            keyTypes[k]=fileTypes[k]
    else:
        keyTypes=fileTypes
        

    job=attrJob(inFile.getStorageType(),first,last,keyTypes)
    job.setCompleteHyperOut(inFile.getHyper())
    job.setInputFile(inFile)
    split=GenSplit.serialIrregHeaderSpace(job, args.memory)
    split.loop(args.print_pct)



    for k in job._stats.keys():
        nmax=max(len(k),nmax)  
 
    print("Key"+" "*(nmax-2)+"  Minimum     Maximum     PctZero     Average")
    nh=last-first
    for k,v in job._stats.items():
        sp=" "*(nmax-len(k)+1)
        if k in keyTypes:
            mn=str(v._mn)
            mnS=" "*(10-len(mn))
            mx=str(v._mx)
            mxS=" "*(10-len(mx))
            print(v._nzero)
            pct=str(float(int(10000-v._nzero/nh*10000)/100))
            avg=v._sm/nh
            pN=" "*(10-len(pct))
            print("%s %s %s %s %s %s %s %s %s"%(k,sp,mn,mnS,mx,mxS,pct,pN,avg))









