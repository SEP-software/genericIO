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
    sx=np.zeros((10,),dtype=np.float32)
    for i in range(sx.shape[0]):
        sx[i]=i
        sy[i]=10 
    headers.addKey("s_x",vals=sx)
    headers.addKey("s_y",vals=sy)
    return SepIrregVector.sepIrregVector(traces,headers)

class TestIrreg(unittest.TestCase):
    def testSimpleIrregTraces(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        try:
            fle.getIrregFile("/tmp/junk.H",dat)
            fle.writeFloatTraces()
            fle.close()
        except:
            self.asert(1==2)
        fle2=getIrregFile("/tmp/junk.H")
        dat2=fle2.readFloatTraces()
        d1=data.getNdArray()
        d2=dat2.getNdArray()
        for i2 in range(10):
            for i1 in range(10):
                if self.assertEqual(d2[i2,i1],d1[i2,i1])
            if self.asertEqual(dat._header.s_x[i],dat2_header.s_x[i])
            if self.asertEqual(dat._header.s_y[i],dat2_header.s_y[i])





if __name__ == '__main__':
    unittest.main()
