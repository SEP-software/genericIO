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
        sy[i]=10-i
    headers.addKey("s_x",vals=sx)
    headers.addKey("s_y",vals=sy)
    return SepIrregVector.vector(traces=traces,header=headers)

class TestIrregSimple(unittest.TestCase):
    
    def testGrid(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        ax=[]
        ax.append(Hypercube.axis(n=10,o=1,d=1,label="s_y"))
        ax.append(Hypercube.axis(n=10,o=0,d=1,label="s_x"))
        dat2=dat.clone()
        print("WHAT 1")
        dat3=dat2.gridData(ax)
        print("WHAT 2")
        fle=io.getIrregFile("/tmp/junk5.H",fromVector=dat3)
        print("WHAT 3",dat3._traces,dat3._header)
        fle.writeDataWindow(dat3)
        print("what 4")
        fle.close()
        fle2=io.getIrregFile("/tmp/junk5.H")
        dat2=fle2.readDataWindow()
        d1=dat.getNdArray()
        d2=dat2.getNdArray()
        for i2 in range(10):
            for i1 in range(10):
                self.assertEqual(d2[i2,i1],d1[i2,i1])
            self.assertEqual(dat._header.s_x[i2],dat2._header.s_x[i2])
            self.assertEqual(dat._header.s_y[i2],dat2._header.s_y[i2])

        fle.remove() 
if __name__ == '__main__':
    unittest.main()
