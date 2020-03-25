#!/usr/bin/env python3
import argparse
import genericIO
import genJob
import genSplit
import numpy as np
from numba import jit

class ddJob(genJob.regSpace):
    def __init__(self,inputType,outputType,real):
        """Intialize object

            inputType - Input type
            outputType - Output type
            real - Convert real (rather than imaginary) of complex number to/from 
        """
        super().__init__(self.convertBuf,0,0,inputType=inputType,outputType=outputType)
        self._real=real

    
    def convertBuf(self,ina,outa):
        """Convert a buffer from one type to another

        ina - Input vector
        outa - Output vector
        """

        n123=ina.getHyper().getN123()
        inN=np.reshape(ina.getNdArray(),(n123,))
        outN=np.reshape(outa.getNdArray(),(n123,))

        if self.inputType=="dataComplex" or self.inputType=="dataComplexDouble":
            if self.outputType=="dataShort":
                complex2Short(inN,outN,self._real)
            elif self.outputType=="dataInt":
                complex2Int(inN,outN,self._real)
            elif self.outputType=="dataFloat" or self.outputType=="dataDouble":
                complex2Real(inN,outN,self._real)
            elif self.outputType=="dataComplex" or self.outputType=="dataComplexDouble":
                complex2Complex(inN,outN)
        else:
            if self.outputType=="dataShort":
                real2Short(inN,outN)
            elif self.outputType=="dataInt":
                real2Int(inN,outN)
            elif self.outputType=="dataFloat" or self.outputType=="dataDouble":
                real2Real(inN,outN)
            elif self.outputType=="dataComplex" or self.dataType=="dataComplexDouble":
                real2Complex(inN,outN,self_real)

@jit(nopython=True, parallel=True)
def complex2Int(inA,outA,realFlag):
    if realFlag:
        for i in prange(outA.shape[0]):
            outA[i]=min(32567,max(-32567, int(.5+real(inA[i]))))
    else:
        for i in prange(outA.shape[0]):
            outA[i]=min(32567,max(-32567, int(.5+imag(inA[i]))))

@jit(nopython=True, parallel=True)
def complex2Int(inA,outA,realFlag):
    if realFlag:
        for i in prange(outA.shape[0]):
            outA[i]=min(2147483647,max(-2147483647, int(.5+real(inA[i]))))
    else:
        for i in prange(outA.shape[0]):
            outA[i]=min(2147483647,max(-2147483647, int(.5+imag(inA[i]))))


@jit(nopython=True, parallel=True)
def complex2Real(inA,outA,realFlag):
    if realFlag:
        for i in prange(outA.shape[0]):
            outA[i]=real(inA[i])
    else:
        for i in prange(outA.shape[0]):
            outA[i]=imag(inA[i])


@jit(nopython=True, parallel=True)
def complex2Complex(inA,outA):
    for i in prange(outA.shape[0]):
        outA[i]=inA[i]

@jit(nopython=True, parallel=True)
def real2Int(inA,outA):
    for i in prange(outA.shape[0]):
        outA[i]=min(32567,max(-32567, int(.5+inA[i])))

@jit(nopython=True, parallel=True)
def real2Int(inA,outA):
    for i in prange(outA.shape[0]):
        outA[i]=min(2147483647,max(-2147483647, int(.5+inA[i])))

@jit(nopython=True, parallel=True)
def real2Real(inA,outA):
    for i in prange(outA.shape[0]):
        outA[i]=inA[i]


@jit(nopython=True, parallel=True)
def real2Complex(inA,outA,realFlag):
    if realFlag:
        for i in prange(outA.shape[0]):
            outA[i]=inA[i]
    else:
        for i in prange(outA.shape[0]):
            outA[i]=complex(0,inA[i])



        
if __name__ == "__main__":
    print("in main")
    parser = argparse.ArgumentParser(description='Print info about files')
    parser.add_argument('input', metavar='Files', type=str,
                        help='Input file')
    parser.add_argument('output', metavar='Files', type=str,
                        help='Output file')                   
    parser.add_argument("--ioIn", type=str,choices=["SEP","JSON"], help='IO type. Defaults to defaultIO')
    parser.add_argument("--ioOut", type=str,choices=["SEP","JSON"], help='IO type. Defaults to defaultIO')
    parser.add_argument("--storage",type=str,choices=["dataByte","dataInt","dataFloat","dataComplex","dataShort",
    "dataComplexDouble","dataDouble"],default="dataFloat")
    parser.add_argument("memory",type=int,help="Memory in terms of GB",default=20)
    parser.add_argument("--real",type=bool, help="Convert float to real portion of complex")
    args = parser.parse_args()

    ioIn=genericIO.defaultIO
    ioOut=ioIn

    if args.ioIn:
        ioIn=genericIO.io(args.ioIn)

    if args.ioOut:
        ioIn=genericIO.io(args.ioOut)

    inFile=ioIn.getRegFile(args.input)
    outFile=genericIO.regFile(ioOut,args.output,storage=args.storage,fromHyper=inFile.getHyper())
    job=ddJob(inFile.getStorage(),outFile.getStorage(),args.real)
    job.setOutputFile(outFile)
    job.setInputFile(inFile)
    split=GenSplit.serialRegSpace(job, args.memory)
else:
    print("not in main")








