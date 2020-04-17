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


    def testOutOfOrderTraces(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        #write out test dataset
        fle=io.getIrregFile("/tmp/junka.H",fromVector=dat)
        fle.writeDataWindow(dat)
        fle.close()
        #Make another dataset where we've switched two headers
        datM=dat.clone()
        datM._header._drn=SepVector.getSepVector(ns=[10],storage="dataInt")
        drn=datM._header._drn.getNdArray()
        for i in range(10):
            drn[i]=i        
        datM._header.s_x[0]=9
        datM._header.s_y[0]=1
        datM._header.s_x[9]=0
        datM._header.s_y[9]=10
        drn[0]=9
        drn[9]=0
        fle2=io.getIrregFile("/tmp/junkb.H",fromHeader=datM._header,dataIn=fle)
        fle2.writeHeaderWindow(datM._header)
        fle2.close()

        fle3=io.getIrregFile("/tmp/junkb.H")
        dat3=fle3.readDataWindow()
        d1=dat.getNdArray()
        d2=dat3.getNdArray()
        for i2 in range(10):
            for i1 in range(10):
                self.assertEqual(d2[i2,i1],d1[i2,i1])
            self.assertEqual(dat._header.s_x[i2],dat3._header.s_x[i2])
            self.assertEqual(dat._header.s_y[i2],dat3._header.s_y[i2])
     #   fle2.remove()
     #   fle.remove()  



if __name__ == '__main__':
    unittest.main()
