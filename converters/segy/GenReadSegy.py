#!/usr/bin/env python3
import argparse
import genericIO
import GenJob
import GenSplit
import Hypercube
import segyio
import math
import numpy as np
from numba import jit,prange

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


    args = parser.parse_args()
    ioOut=genericIO.defaultIO

    if args.io:
        ioOut=genericIO.io(args.io)

    trTypes={}
    for k in segyio.tracefield.keys();
        trType[i]=False
    with segyio.open(args.input, ignore_geometry=True) as segyfile:
        ntraces=len(segyfile.trace)
        nbuf=min(ntraces,args.nbuf)
        head=f.header[0:nbuf]
        for k in trTypes.keys():
            if head[k]        

    headers=[]
    


    outFile=genericIO.regFile(ioOut,args.output,storage=args.storage,fromHyper=hyper)
    job=spikeJob(outFile.getStorageType(),events)
    job.setOutputFile(outFile)
    job.setCompleteHyperOut(outFile.getHyper())
    split=GenSplit.serialIrregDataSpace(job, args.memory)
    split.loop(args.print_pct)









