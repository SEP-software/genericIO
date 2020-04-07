import genericIO
import pytest
import SepVector
import Hypercube
import unittest
import GenInterp
class TestStringMethods(unittest.TestCase):
    def testSinc(self):
        try:
            s=GenInterp.sincTable(100,10)
        except:
            assert(1==2)
            raise Exception("failed making sinc table")
        self.assertTrue(abs(s._tab[0,0]) < .00001)
        self.assertTrue(abs(s._tab[0,1]) < .00001)
        self.assertTrue(abs(s._tab[0,2] )< .00001)
        self.assertTrue(abs(s._tab[0,3]) < .00001)
        self.assertTrue(abs(s._tab[0,4]-1.) < .00001)
        self.assertTrue(abs(s._tab[0,5]) < .00001)
        self.assertTrue(abs(s._tab[0,6]) < .00001)
        self.assertTrue(abs(s._tab[0,7]) < .00001)
        self.assertTrue(abs(s._tab[0,8])< .00001)
        self.assertTrue(abs(s._tab[0,9]) < .00001)

    def testNear1D(self):
        io=genericIO.io("memory")
        hyperIn=Hypercube.hypercube(ns=[5],os=[0.],ds=[1.])
        hyperOut=Hypercube.hypercube(ns=[10],os=[0.],ds=[.499])

        inFile=io.getRegFile("in",fromHyper=hyperIn)
        outFile=io.getRegFile("out",fromHyper=hyperOut)
        op=GenInterp.interpJob(inFile,outFile,0)
        
        inVec=SepVector.getSepVector(hyperIn)
        outVec=SepVector.getSepVector(hyperOut)
        inV=inVec.getNdArray()
        outV=outVec.getNdArray()
        inV[0]=0
        inV[1]=1
        inV[2]=2
        inV[3]=3
        inV[4]=4
        op.interpOp(inVec,outVec)
        self.assertTrue(abs(outV[0]-0.) < .00001)
        self.assertTrue(abs(outV[1]-0.) < .00001)
        self.assertTrue(abs(outV[2]-1.) < .00001)
        self.assertTrue(abs(outV[3]-1.) < .00001)
        self.assertTrue(abs(outV[4]-2.) < .00001)
        self.assertTrue(abs(outV[5]-2.) < .00001)
        self.assertTrue(abs(outV[6]-3.) < .00001)
        self.assertTrue(abs(outV[7]-3.) < .00001)
        self.assertTrue(abs(outV[8]-4.) < .00001)
        self.assertTrue(abs(outV[9]-4.) < .00001)

    def testLinear1D(self):
        io=genericIO.io("memory")
        hyperIn=Hypercube.hypercube(ns=[5],os=[0.],ds=[1.])
        hyperOut=Hypercube.hypercube(ns=[10],os=[0.],ds=[.5])

        inFile=io.getRegFile("in",fromHyper=hyperIn)
        outFile=io.getRegFile("out",fromHyper=hyperOut)
        op=GenInterp.interpJob(inFile,outFile,1)
        
        inVec=SepVector.getSepVector(hyperIn)
        outVec=SepVector.getSepVector(hyperOut)
        inV=inVec.getNdArray()
        outV=outVec.getNdArray()
        inV[0]=0
        inV[1]=1
        inV[2]=2
        inV[3]=3
        inV[4]=4
        op.interpOp(inVec,outVec)
        self.assertTrue(abs(outV[0]-0.) < .00001)
        self.assertTrue(abs(outV[1]-0.5) < .00001)
        self.assertTrue(abs(outV[2]-1.) < .00001)
        self.assertTrue(abs(outV[3]-1.5) < .00001)
        self.assertTrue(abs(outV[4]-2.) < .00001)
        self.assertTrue(abs(outV[5]-2.5) < .00001)
        self.assertTrue(abs(outV[6]-3.) < .00001)
        self.assertTrue(abs(outV[7]-3.5) < .00001)
        self.assertTrue(abs(outV[8]-4.) < .00001)
        self.assertTrue(abs(outV[9]-4.) < .00001)

    def testSinc1D(self):
        io=genericIO.io("memory")
        hyperIn=Hypercube.hypercube(ns=[5],os=[0.],ds=[1.])
        hyperOut=Hypercube.hypercube(ns=[10],os=[0.],ds=[.5])

        inFile=io.getRegFile("in",fromHyper=hyperIn)
        outFile=io.getRegFile("out",fromHyper=hyperOut)
        op=GenInterp.interpJob(inFile,outFile,2)
        
        inVec=SepVector.getSepVector(hyperIn)
        outVec=SepVector.getSepVector(hyperOut)
        inV=inVec.getNdArray()
        outV=outVec.getNdArray()
        inV[0]=0
        inV[1]=1
        inV[2]=2
        inV[3]=3
        inV[4]=4
        op.interpOp(inVec,outVec)
        self.assertTrue(abs(outV[0]-0.) < .00001)
        self.assertTrue(abs(outV[1]-0.4102939) < .00001)
        self.assertTrue(abs(outV[2]-1.) < .00001)
        self.assertTrue(abs(outV[3]-1.55304) < .00001)
        self.assertTrue(abs(outV[4]-2.) < .00001)
        self.assertTrue(abs(outV[5]-2.4520125) < .00001)
        self.assertTrue(abs(outV[6]-3.) < .00001)
        self.assertTrue(abs(outV[7]-3.5947628) < .00001)
        self.assertTrue(abs(outV[8]-4.) < .00001)
        self.assertTrue(abs(outV[9]-4.0884557) < .00001)
if __name__ == '__main__':
    unittest.main()
