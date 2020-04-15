import genericIO
import pytest
import SepVector
import Hypercube
import unittest

class TestIrreg(unittest.TestCase):
    def testPythonParamsInt():
        par = genericIO.pythonParams({"tint": 2})
        self.assert(genericIO.defaultIO.getInt("tint") == 2)


    def testPythonParamsIntDef(self):
        par = genericIO.pythonParams({"tint": 2})
        self.assert(genericIO.defaultIO.getInt("tint2", 3) == 3)


    def testPythonWrite(self):
        x=SepVector.getSepVector(ns=[10,10,10])
        io=genericIO.defaultIO
        hyper7=Hypercube.hypercube(ns=[10,10,10,1,1,1,1])
        try:
            fle=io.getRegFile("/tmp/junk.H",fromHyper=hyper7)
            fle.writeWindow(x)
            return True
        except:
            self.assert(1==2)
            raise Exception("Failed")

    def testPythonDoubleComplex(self):
        x=SepVector.getSepVector(ns=[10,10],storage="dataComplexDouble")
        io=genericIO.defaultIO
        y=x.getNdArray()
        for i2 in range(10):
            for i1 in range(10):
                y[i2][i1]=i1+i2*100
        hyper2=Hypercube.hypercube(ns=[10,10])
        try:
            fle=io.getRegFile("/tmp/junk2",fromHyper=hyper2)
            fle.writeWindow(x)
        except:
            self.assert(1==2)
            raise Exception("Failed")

if __name__ == '__main__':
    unittest.main()
