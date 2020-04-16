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
    def testSimpleIrregTraces(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        try:
            fle=io.getIrregFile("/tmp/junk.H",fromVector=dat)
            fle.writeDataWindow(dat)
            fle.close()
        except:
            self.assertTrue((1==2))
        fle2=io.getIrregFile("/tmp/junk.H")
        dat2=fle2.readDataWindow()
        d1=dat.getNdArray()
        d2=dat2.getNdArray()
        for i2 in range(10):
            for i1 in range(10):
                self.assertEqual(d2[i2,i1],d1[i2,i1])
            self.assertEqual(dat._header.s_x[i2],dat2._header.s_x[i2])
            self.assertEqual(dat._header.s_y[i2],dat2._header.s_y[i2])
        fle3=io.getIrregFile("/tmp/junk2.H",fromHeader=dat._header,dataIn=fle2)
        fle3.writeHeaderWindow(dat2._header)
        fle3.close()
        fle4=io.getIrregFile("/tmp/junk2.H")
        head2=fle4.readHeaderWindow()
        for i2 in range(10):
            self.assertEqual(dat._header.s_x[i2],head2.s_x[i2])
            self.assertEqual(dat._header.s_y[i2],head2.s_y[i2])    
        fle3.remove()
        fle.remove()   

    def testOutOfOrderTraces(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        datM=dat.clone()
        datM._drn=SepVector.getSepVector(ns=[10])
        drn=datM._drn.getNdArray()
        for i in range(10):
            drn[i]=i
        tr=datM._traces.getNdArray()
        for i in range(10):
            tr[0,i]=90+i
            tr[9,i]=i
        datM._header.s_x[0]=9
        datM._header.s_y[0]=1
        datM._header.s_x[9]=0
        datM._header.s_y[9]=10

        fle=io.getIrregFile("/tmp/junk3.H",fromVector=datM)
        fle.writeDataWindow(dat)
        fle.close()
        fle2=io.getIrregFile("/tmp/junk3.H")
        dat2=fle2.readDataWindow()
        d1=dat.getNdArray()
        d2=dat2.getNdArray()
        for i2 in range(10):
            for i1 in range(10):
                self.assertEqual(d2[i2,i1],d1[i2,i1])
            self.assertEqual(dat._header.s_x[i2],dat2._header.s_x[i2])
            self.assertEqual(dat._header.s_y[i2],dat2._header.s_y[i2])

        fle3=io.getIrregFile("/tmp/junk4.H",fromHeader=datM._header,dataIn=fle2)
        fle3.writeHeaderWindow(dat2._header)
        fle3.close()

        fle4=io.getIrregFile("/tmp/junk4.H")
        dat5=fle4.readDataWindow()
        d1=dat.getNdArray()
        d2=dat5.getNdArray()
        for i2 in range(10):
            self.assertEqual(dat._header.s_x[i2],dat5._header.s_x[i2])
            self.assertEqual(dat._header.s_y[i2],dat5._header.s_y[i2]) 
            for i1 in range(10):
                self.assertEqual(d2[i2,i1],d1[i2,i1])  
        fle3.remove()
        fle.remove()  
    def testGrid(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        ax=[]
        ax.append(Hypercube.axis(n=10,o=1,d=1,label="s_y"))
        ax.append(Hypercube.axis(n=10,o=1,d=1,label="s_x"))
        dat2=dat.clone()
        dat2.gridData(ax)
        fle=io.getIrregFile("/tmp/junk5.H",fromVector=dat2)
        fle.writeDataWindow(dat)
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
