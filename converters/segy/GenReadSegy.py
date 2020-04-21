#!/usr/bin/env python3
import argparse
import genericIO
import GenJob
import GenSplit
import Hypercube
import segyio
import segyio.tracefield
import math
import numpy as np
from numba import jit,prange
import ast

class spikeJob(GenJob.regSpace):
    def __init__(self,outputType,events):
        """Intialize object

            outputType - Output type
            events - List of events
        """
        super().__init__(self.spikeBuf,0,0,outputType=outputType,hasInput=False)
        self._events=events
    
    def spikeBuf(self,ina,outa):
        """Convert a buffer from one type to another

        ina - Input vector
        outa - Output vector
        """
    
        f=[0]*6
        n=[1]*6

        axesVec=outa.getHyper().axes
        axesOut=self.getCompleteHyperOut().axes
        for i in range(len(axesOut)):
            f[i]=int(round((axesVec[i].o-axesOut[i].o)/axesOut[i].d))
            n[i]=axesVec[i].n 
        outa.scale(0.)
        outN=np.reshape(outa.getNdArray(),(n[5],n[4],n[3],n[2],n[1],n[0]))
        for ev in self._events:
            fill(outN,ev._mag,f[0],f[1],f[2],f[3],f[4],f[5],ev._k1,ev._k2,ev._k3,ev._k4,ev._k5,ev._k6)

def keyMapping(defs,additonal):
    """Keymapping for read"""
    keyNum=copy.deepcopy()
    numKey = dict(map(reversed, keyNum.items()))
    if not isinstance(additional,dict):
        raise Exception("E")

    


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Make delta functions and impulsive plane waves ')
    parser.add_argument('input', metavar='input', type=str,
                        help="SEG-Y file to read")   
    parser.add_argument('output', metavar='Output', type=str,
                        help='Output file')                   
    parser.add_argument("--io", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    parser.add_argument("--memory",type=float,help="Memory in terms of GB",default=.2)
    parser.add_argument("--print_pct",type=float,help="Print progress every X pct (above 100 means no printing)",default=101)
    parser.add_argument("--nbuf", type=str,default=10000, help='Number of traces to search for non-zero keywords')
    parser.add_argument("--endian",type=str,default="big", choices=["big","little"],help="File endianness, big/msb (default) or little/lsb")
    parser.add_argument("--additional",type=str,default=None,help="Additional keys in the form of a dictionary with value as a tuple ({s_x:('int',200)})")
    parser.add_argument("--keepKeys",type=str,help="List of keys to save 'SourceX,CDP_TRACE")
    parser.add_argument("--writeBinaryHeader",type=str,help="File to write binary to")
    parser.add_argument("--writeTextHeader", type=str,help="File to write text header to")
    )
    args = parser.parse_args()
    ioOut=genericIO.defaultIO
#    if args.additional:
#        keyList=keyMapping(segyio.tracefield.keys,ast.literal_eval(args.additional))
#    else:
#        keyList=segyio.tracefield.keys

    if args.io:
        ioOut=genericIO.io(args.io)

    headerKeep={}
    for k in segyio.tracefield.keys.keys():
        headerKeep[k]=False
    with segyio.open(args.input, ignore_geometry=True) as segyfile:
        ntraces=len(segyfile.trace)
        if args.writeTextHeader:
            try:
                f=open(args.writeTextHeader,"w+")
                f.write(segyfile.text)
                f.close()
            except:
                raise Exception("Trouble writing text header to %s"%args.writeTextHeader)
        if args.writeBinaryHeader:
            try:
                f=open(args.writeBinaryHeader,"w+")
                f.write(segyfile.bin)
                f.close()
            except:
                raise Exception("Trouble writing binary header to %s"%args.writeBinaryHeader)
        if args.keepKeys:
            lst=args.keepKeys.split(",")
            for k in lst:
                if k not in headerKeep:
                    raise Exception("Asked to keep key ",k," which is not a valid header")
                headerKeep[k]=True
        else:
            nbuf=min(ntraces,args.nbuf)
            head=segyfile.header[0:nbuf]
            for i in range(nbuf):
                for j in headerKeep.keys():
                    x=segyfile.header[0].get(segyio.tracefield.keys[j])
                    if x !=0 and not x is  None:
                        headerKeep[j]=True
        outFile=genericIO.irregFile(ioOut,args.output,storage=args.storage,fromHyper=hyper)

        print(segyfile.text)
        print(segyfile.header[0].get(237),segyfile.header[0].get(197),"SDSDSA")


if 1==3:
    outFile=genericIO.regFile(ioOut,args.output,storage=args.storage,fromHyper=hyper)
    job=spikeJob(outFile.getStorageType(),events)
    job.setOutputFile(outFile)
    job.setCompleteHyperOut(outFile.getHyper())
    split=GenSplit.serialIrregDataSpace(job, args.memory)
    split.loop(args.print_pct)









