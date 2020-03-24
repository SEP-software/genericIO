#!/usr/bin/env @Python3_EXECUTABLE@
import argparse
import genericIO

parser = argparse.ArgumentParser(description='Print info about files')
parser.add_argument('strings', metavar='N', type=string, nargs='+',
                    help='A list of files to give more info')
args = parser.parse_args()




