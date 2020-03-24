#!/usr/bin/env python3
import argparse
import genericIO

parser = argparse.ArgumentParser(description='Print info about files')
parser.add_argument('files', metavar='Files', type=str, nargs='+',
                    help='A list of files to give more info')
args = parser.parse_args()
print(args.files)




