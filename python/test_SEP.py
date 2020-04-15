import genericIO
import pytest
import SepVector
import SepIrregVector
import Hypercube
import unittest
import numpy as np
def makeDataset():
    traces=SepVector.getSepVector(ns=[10,10])
    headers=SepIrregVector.headerBlock(nh=10)
    tr=traces.getNdArray()
    for i2 in range(10):
        for i1 in range(10):
            tr[i2,i1]=10*i2+i1
    sx=np.zeros((10,),dtype=np.float32)
    sy=np.zeros((10,),dtype=np.float32)
    for i in range(sx.shape[0]):
        sx[i]=i
        sy[i]=10 
    headers.addKey("s_x",vals=sx)
    headers.addKey("s_y",vals=sy)
    return SepIrregVector.vector(traces=traces,header=headers)

class TestIrreg(unittest.TestCase):
    def testSimpleIrregTraces(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        try:
            fle=io.getIrregFile("/tmp/junk.H",fromVector=dat)
   #         fle.writeDataWindow(dat)
    #        fle.close()
        except:
            self.assertTrue((1==2))
   




if __name__ == '__main__':
    unittest.main()
