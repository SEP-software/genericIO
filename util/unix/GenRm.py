#!/usr/bin/env python3
import argparse
import genericIO
import GenJob
import GenSplit
import numpy as np

       
        
if __name__ == "__main__":



    parser = argparse.ArgumentParser(description='Remove files')
    parser.add_argument('files', metavar='Files', type=str, nargs='+',
                        help='A list of files to give more info')
    parser.add_argument("--io", type=str,choices=[@GEN_IO_TYPES@], help='IO type. Defaults to defaultIO')
    args = parser.parse_args()

    io=genericIO.defaultIO

    if args.io:
        io=genericIO.io(args.io)  


for f in args.files:  
    fileType=ioIn.getFileType(f)

    if fileType == "invalidFile":
        raise Exception("Invalid file of selected IO") 
    elif fileType == "regFile":     
        inFile=io.getRegFile(f)
    else:
        inFIle=io.getIrregFile(f)
    inFile.remove()







