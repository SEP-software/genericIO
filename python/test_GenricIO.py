import genericIO
import pytest


def testPythonParamsInt():
    par = genericIO.pythonParams({"tint": 2})
    assert(genericIO.defaultIO.getInt("tint") == 2)


def testPythonParamsIntDef():
    par = genericIO.pythonParams({"tint": 2})
    assert(genericIO.defaultIO.getInt("tint2", 3) == 3)
