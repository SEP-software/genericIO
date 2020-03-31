#!/usr/bin/env python3
import argparse
import genericIO
import genJob
import genSplit
import numpy as np
import numba
import threading

class attrJob(genJob.regSpace):
    def __init__(self,inputType):
        """Intialize object

            inputType - Input type
        """
        super().__init__(self.convertBuf,0,0,outputType=outputType)
        self._thr=threading.thread() 
        self._lock=self._thr.Lock() 
        self._mn=1e99
        self._max=-1e99
        self._imin=-1
        self._imax=-1
        self._sm=0
        self._sqs=0
        self._nzero=0
    def calcStats(self,ina):
        """Convert a buffer from one type to another

        ina - Input vector
        """

        n123=ina.getHyper().getN123()
        inN=np.reshape(ina.getNdArray(),(n123,))

        if self._inputType=="dataComplex" or self._inputType=="dataComplexDouble":
            mn,imin,mx,imax,sm,sqs,nzero=calcComplexStats(inN)
        else:
           mn,imin,mx,imax,sm,sqs,nzero= calcRealStats(inN)
        self._lock.acquire()
        if mn< self._mn:
            self._mn=mn
            self._imin=imin
        if mx > self._mx:
            self._mx=mx
            self._imax=imax 
        self._sm+=sm
        self._sqs+=sqs
        self._nzero+=nzero
        self._lock.release()

        
@numba.jit(nopython=True, parallel=True,locals={'sm': numba.float64,"sqs":numba.float64,"nzero":numba.int64})
def calcRealStats(inA):
    """
      Return min,max,sum,sumsq,nzeros
      """
    nzero=0
    sm=inA[0]
    sqs=inA[0]
    mn=ina[0]
    mx=inA[0]
    imin=0
    imax=0
    if inA[0]!=0: 
        nzero+=1
    for i in range(1,outA.shape[0]):
        if inA[i]  < mn:
            mn=inA[i]
            imin=i
        if inA[i] >mx:
            mx=inA[i]
            imax=i
        sm+=inA[i]
        sqs[i]+=inA[i]*inA[i]
        if inA[i] !=0:
            nzero+=1
    return mn,imin,mx,imax,sm,sqs,nzero

@numba.jit(nopython=True,locals={'amp':numba.float64,'sm': numba.float64,"sqs":numba.float64,"nzero":numba.int64})
def calcRealStats(inA):
    """
      Return min,max,sum,sumsq,nzeros
      """
    nzero=0
    amplitude=numpy.absolute(inA[0])
    sm=amplitude
    sqs=amplitude
    mn=amplitude
    mx=amplitude
    imin=0
    imax=0
    if amplitude !=0: 
        nzero+=1
    for i in range(1,outA.shape[0]):
        amplitude=numpy.absolutde(inA[0])
        if amplitude  < mn:
            mn=amplitude
            imin=i
        if amplitude >mx:
            mx=amplitude
            imax=i
        sm+=amplitude
        sqs[i]+=amplitude*amplitude
        if amplitude !=0:
            nzero+=1
    return mn,imin,mx,imax,sm,sqs,nzero
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Print info about files')
    parser.add_argument('input', metavar='Input', type=str,
                        help='Input file')                 
    parser.add_argument("--io", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    parser.add_argument("--memory",type=int,help="Memory in terms of GB",default=20)
    parser.add_argument("--want",type=str,choices=["all","min","max","mean","rms","norm","short"],
    default="all")
    args = parser.parse_args()

    ioIn=genericIO.defaultIO
    ioOut=ioIn

    if args.ioIn:
        ioIn=genericIO.io(args.ioIn)



    inFile=ioIn.getRegFile(args.input)
    job=attrJob(inFile.getStorageType(),outFile.getStorageType(),args.real)
    job.setCompleteHyperOut(inFile.getHyper())
    split=genSplit.serialRegSpace(job, args.memory)
    split.loop()









