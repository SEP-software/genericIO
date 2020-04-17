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


    def testGrid(self):
        io=genericIO.io("SEP")
        dat=makeDataset()
        ax=[]
        ax.append(Hypercube.axis(n=10,o=1,d=1,label="s_y"))
        ax.append(Hypercube.axis(n=10,o=0,d=1,label="s_x"))
        dat2=dat.clone()
        dat3=dat2.gridData(ax)
        fle=io.getIrregFile("/tmp/junk5.H",fromVector=dat3)
        fle.writeDataWindow(dat3)
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
