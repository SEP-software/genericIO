#!/usr/bin/env python3
import argparse
import genericIO
import GenJob
import GenSplit
import SepVector
import Hypercube
import segyio
import segyio.tracefield
import SepIrregVector
import math
import numpy as np
from numba import jit,prange
import ast

class fromSEGY(GenJob.irregSpace):
    def __init__(self,outputType,keys,segyfile):
        """Intialize object

            outputType - Output type
            events - List of events
        """
        super().__init__(self.convertBuf,0,0,outputType=outputType,hasInput=False)
        self._keys=keys
        self._segyfile=segyfile

    
    def makeOutputBuffer(self,inbuf,hyperOut):
        """Make the output buffer given the output hypercube"""
        buf=SepIrregVector.vector(hyper=hyperOut,dataType=self._outputType)
        for k in self._keys.keys():
            buf._header.addKey(k,typ="dataInt")
        return buf

    def convertBuf(self,ina,outa):
        """Convert a buffer from one type to another

        ina - Input vector
        outa - Output vector
        """
        ax=outa.getHyper().getAxis(2)
        bufsS={}
        bufsN={}
        for k in self._keys.keys():
            bufsS[k]=SepVector.getSepVector(ns=[ax.n],typ="dataInt")
            bufsN[k]=bufsS[k].getNdArray()
        outN=outa._traces.getNdArray()
        for i2 in range(ax.n):
            for k,v in self._keys.items():
                i=i2+self._fw[self._iwind][1]
                bufsN[k][i2]=self._segyfile.header[i].get(v)
            outN[i2,:]=self._segyfile.trace[i2]
        for k in self._keys.keys():
            outa._header.setKey(k,bufsS[k])
        return outa



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
    args = parser.parse_args()
    ioOut=genericIO.defaultIO
    if args.additional:
        keyList=keyMapping(segyio.tracefield.keys,ast.literal_eval(args.additional))
    else:
        keyList=segyio.tracefield.keys

    if args.io:
        ioOut=genericIO.io(args.io)

    headerKeep={}
    for k in segyio.tracefield.keys.keys():
        headerKeep[k]=False
    with segyio.open(args.input, ignore_geometry=True,endian=args.endian) as segyfile:
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
                    x=segyfile.header[i].get(segyio.tracefield.keys[j])
                    if x !=0 and not x is  None:
                        headerKeep[j]=True
        x=segyfile.trace[0]
        aT=Hypercube.axis(n=segyfile.header[0].get(segyio.tracefield.keys["TRACE_SAMPLE_COUNT"]),
         d=float(segyfile.header[0].get(float(segyio.tracefield.keys["TRACE_SAMPLE_INTERVAL"]))/1000000.))
        aN=Hypercube.axis(n=ntraces)
        hyper=Hypercube.hypercube(axes=[aT,aN])
        headerKeep["TRACE_SAMPLE_COUNT"]=False
        headerKeep["TRACE_SAMPLE_INTERVAL"]=False

        keys={}
        keysT={}
        for k,v in headerKeep.items():
            if v:
                keys[k]=segyio.tracefield.keys[k]
                keysT[k]="dataInt"
        outFile=ioOut.getIrregFile(args.output,storage=SepVector.dtypeToSepVecType[str(x.dtype)],
         fromDataHyper=hyper,headerHyper=hyper,keys=keysT)
        job=fromSEGY(outFile.getStorageType(),keys,segyfile)
        job.setOutputFile(outFile)
        job.setCompleteHyperOut(outFile.getHyper())
        split=GenSplit.serialIrregDataSpace(job, args.memory)
        split.loop(args.print_pct)









