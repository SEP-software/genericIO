#!/usr/bin/env python3
import argparse
import genericIO
import genJob
import genSplit

class ddJob(GenJob.regSpace):
    def __init__(self,fileIn,fileOut):
        """Intialize object

            fileIn - Input file
            fileOut - Output file
        """
        ein=fileIn.getEsize()
        eout=fileOut.getEsize()
        super().__init__(0,0,ein=ein,eout=eout)
        self._hyperOut=fileOut.getHyper()

    

 


parser = argparse.ArgumentParser(description='Print info about files')
parser.add_argument('input', metavar='Files', type=str,
                    help='Input file')
 parser.add_argument('output', metavar='Files', type=str,
                    help='Output file')                   
parser.add_argument("--ioIn", type=str,choices=["SEP","JSON"], help='IO type. Defaults to defaultIO')
parser.add_argument("--ioOut", type=str,choices=["SEP","JSON"], help='IO type. Defaults to defaultIO')
parser.add_argument("memory",type=int,help="Memory in terms of GB",default=20)
args = parser.parse_args()

ioIn=genericIO.defaultIO;
ioOut=ioIn

if args.ioIn:
    ioIn=genericIO.io(args.ioIn)

if args.ioOut:
    ioIn=genericIO.io(args.ioOut)

inFile=genericIO.defaultIO.getRegFile(f))
outFile.genericIO.defaultIO.getRegFile(f)

job=ddJob(inFile,outFile)

split=GenSplit.serialRegSpace(job, args.memory)





