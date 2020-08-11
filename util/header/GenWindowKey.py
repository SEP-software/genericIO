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
        self._print=True
        self._last=last
        self._keys=copy.deepcopy(keys)
        self._done=0
    def printInfo(self,ina,dummy):
        """Convert a buffer from one type to another

        ina - Input vector
        dummy - Dummy argument
        """
        f2=self._done

        for i in range(ina._header._nh):
            if f2 +i >= self._first and f2+i < self._last:
                if i%20==0 of self._print:
                    self._print=False
                    line="Number       "
                    for k in self._keys:
                            x=str(k)
                            if len(x)>10:
                                x=x[0:10]+" "
                            line+=x+" "*(11-len(x))
                    print(line)
                line=str(f2+i)
                line+=" "*(13-len(line))   
                for k in self._keys:
                    x=str(ina._header.getKey(k)[i])
                    line+=x+" "*(11-len(x))
                print(line)
        self._done+=ina._header._nh
                    
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
    
 

    job=windowJob(inFile.getStorageType(),mins,maxs)
    job.setCompleteHyperOut(inFile.getHyper())
    job.setInputFile(inFile)
    if args.synch:
        split=GenSplit.serialIrregSpace(job, args.memory)
    else:
        split=GenSplit.serialIrregHeaderSpace(job, args.memory)

    split.loop(args.print_pct)



