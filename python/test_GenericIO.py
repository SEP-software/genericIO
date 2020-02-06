import genericIO
import pytest
import SepVector
import Hypercube


def testPythonParamsInt():
    par = genericIO.pythonParams({"tint": 2})
    assert(genericIO.defaultIO.getInt("tint") == 2)


def testPythonParamsIntDef():
    par = genericIO.pythonParams({"tint": 2})
    assert(genericIO.defaultIO.getInt("tint2", 3) == 3)

def testPythonWrite():
    x=SepVector.getSepVector(ns=[10,10,10])
    io=genericIO.defaultIO
    hyper7=Hypercube.hypercube(ns=[10,10,10,1,1,1,1])
    print(len(hyper7.axes),"AXES")
    try:
        fle=io.getRegFile("/tmp/junk.H",fromHyper=hyper7)
        fle.writeWindow(x)
    except:
        raise Exception("Failed")
