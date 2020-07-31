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


class disJob(GenJob.irregSpace):
    def __init__(self,inputType,first,last,keys):
        """Intialize object

            inputType - Input type
            first - First key to print
            last - Last key to print
            keys  - List of keys to print
        """
        super().__init__(self.printInfo,0,0,inputType=inputType,hasOutput=False)
        self._lock=threading.Lock() 
        self._first=first
        self._last=last
        self._keys=copy.deepcopy(keys)
        print("XXXX")
    def printInfo(self,ina,dummy):
        """Convert a buffer from one type to another

        ina - Input vector
        dummy - Dummy argument
        """
        print("YY")
        f2=int(ina.getHyper().axes[1].o)
        print(f2,self._first,self._last,"RANGE")
        for i in range(ina._header._nh):
            if f2 +i >= self._first and f2+i < self._last:
                line=str(f2+i)
                line+=" "*(13-len(line))                    
                for k in self._keys:
                    x=str(ina._header.getKey(k)[i])
                    line+=x+" "*(11-len(x))
            print(line)
                    
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
    last=inFile.getHyperHeader().axes[1].n


    first=0
    if args.first != None:
        first=args.first
    if args.last !=None:
        last=args.last


    first=0
    if args.first != None:
        first=args.first
    if args.last !=None:
        last=args.last

    fileKeys=inFile.getHeaderKeys()
    keys=[]
    if not args.keyList==None:
        keys=args.keyList.split(":")
        for k in keys:
            if not k in fileKeys:
                raise Exception("Key %s does not exist "%k)
    else:
        keys=fileKeys

    job=disJob(inFile.getStorageType(),first,last,keys)






