#!/usr/bin/env python3
import argparse
import genericIO
import genJob
import genSplit
import numpy as np
from numba import jit,prange

class cpJob(genJob.regSpace):
    def __init__(self,fileType):
        """Intialize object

        
        """
        super().__init__(self.cpBuf,0,0,inputType=fileType,outputType=fileType)
 
    
    def cpBuf(self,ina,outa):
        """Convert a buffer from one type to another

        ina - Input vector
        outa - Output vector
        """
        outa.scaleAdd(ina,0.,1.)
       
        
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Copy file')
    parser.add_argument('input', metavar='Input', type=str,
                        help='Input file')
    parser.add_argument('output', metavar='Output', type=str,
                        help='Output file')                   
    parser.add_argument("--ioIn", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    parser.add_argument("--ioOut", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    parser.add_argument("--memory",type=int,help="Memory in terms of GB",default=20)
    args = parser.parse_args()

    ioIn=genericIO.defaultIO
    ioOut=ioIn

    if args.ioIn:
        ioIn=genericIO.io(args.ioIn)

    if args.ioOut:
        ioOut=genericIO.io(args.ioOut)

    inFile=ioIn.getRegFile(args.input)
    outFile=genericIO.regFile(ioOut,args.output,storage=inFile.getStorageType(),fromHyper=inFile.getHyper())
    job=cpJob(inFile.getStorageType(),outFile.getStorageType(),args.real)
    job.setOutputFile(outFile)
    job.setCompleteHyperOut(outFile.getHyper())
    job.setInputFile(inFile)
    split=genSplit.serialRegSpace(job, args.memory)
    split.loop()









