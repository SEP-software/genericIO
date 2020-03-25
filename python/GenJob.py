import Hypercube

esizeFromType={"dataFloat":4,"dataDouble":8,"dataInt":4,"dataComplex":8,"dataShort":2,"dataComplexDouble":16,"dataByte":1} 


class regSpace:
    """Base class for regular sampled datasets"""
    def __init__(self,process,mem,minOutputDim,inputJob=None,inputType="dataFloat",outputType="dataFloat"):
        """Initialization of the regspace job
            mem - Memory in megabytes needed by the job
            minOutputDim - Minimum output dimensions
            inputJob - Input job 
            inputType - Input data type
            outputType - Output data Type
            process - Function to process data

        """

        self.process=process
        self._mem=mem
        self._minDim=minOutputDim
        self._inputType=inputType
        self._outputType=outputType
        self._ein=esizeFromType[inputType]
        self._eout=esizeFromType[outputType]
        self._hyperOut=None
        if inputJob:
            if not isinstance(regSpace,inputJob):
                raise Exception("Expecting genericJob.regSpace instance to be passed in")
        self._inputJob=inputJob
        self._nw=[]
        self._fw=[]
        self._jw=[]
        self._inputFile=None
        self._outputFile=None
        self._inputBuffer=None
        self._outputBuffer=None

    
    def allocateBuffer(self,hyperOut,iwind):
        """Allocate buffer needed for this window
            hyperOut - Output hypercube
            iwind    - Block number
        """
        hyperIn=self._hyperIn.subHyper(self._nw[iwind],self._fw[iwind],self._jw[iwind])
        self.outputBuffer=reallocBuffer(self.outputBuffer,hyperOut)
        if not self._inputJob:
            self._inputBuffer=reallocBuffer(self.inputBuffer,hyperIn,self._outputType)
        else:
            self._inputJob.allocateBuffer(hyperIn,iwind,self._inputType)


    def reallocBuffer(self,buf,hyper,typ):
        alloc=False
        if not buf:
            alloc=True 
        else:
            nc=buf.getHyper().getNs()
            nn=hyper.getNs()
            for i in range(len(nn)):
                if nn[i] != nc[i]:
                    alloc=True 
        if alloc:
           return SepVector.getSepVector(hyper,storage=typ)
        else:
            buf.adjustHyper(hyper)

    def deallocateBuffers(self):
        """Deallocate buffers"""
        self._outputBuffer=None
        self._inputBuffer=None

    
    def processBuffer(self,iwind,nw,fw,jw ):

        if self._inputFile:
            ndim=self._inputFile.getHyper().getNdims()
            self._inputFile.readWindow(self._inputBuffer,nw=self._nw[iwind][:ndim],fw=self._fw[iwind][:ndim],jw=self._jw[iwind][:ndim])
        else:
            self._inputJob.processBuffer(iwind,self._nw[iwind],self._fw[iwind],self._jw[iwind])
    
        self.process(self._inputBuffer,self._outputBuffer)

        if self._outputFile:
            self._outputFile.getHyper().getNdims()
            self._inputFile.readWindow(self._inputBuffer,nw=nw[:ndim],fw=fw[:ndim],jw=jw[:ndim])



    def setOutputFile(self,outputFile):
        """Set the output file"""
        self._outputFile=outputFile
    
    def setInputFile(self,inputFile):
        """Set input file"""
        self._inputFile=inputFile

    def checkLogic(self):
        if first:
            if not self._outputFile:
                raise Exception("Output file must exist at the end of the chain")
            if self._outputFile.getStorageType()!=self._outputType:
                raise Exception("Output file type and and outputType set must match")
        if not self._inputJob:
            if not self._inputFile:
                raise Exception("Input file must exist at the end of the chain")
            if self._inputFile.getStorageType()!=self._inputType:
                raise Exception("Input file type and and outputType set must match") 
        else:
            if self._inType != self._inputJob.outType:
                raise Exception("Output/Input type mismatch in pipe")
            self._inputJob.checkLogic()

    def returnBaseMemory(self):
        """Return base memory needed by job"""
        x=0
        if self._inputJob:
            x= self._inputJob.returnBaseMemory()
        return x+self._mem

    def calcInputWindow(self,nw,fw,jw):
        """Calculate input window size from output window size

           nw,fw,jw - Standard window parameters"""
        self._nw.append(nw)
        self._fw.append(fw)
        self._jw.append(jw)
        if self._inputJob:
            self._inputJob.calcInputWindow(nw,fw,jw)

    def getOutputDomain(self):
        """Return output domain for job. 
        If self._hyperOut is not set returns error"""
        if not self._hyperOut:
            return None
        return self._hyperOut

    def setHyperOut(self,hyper):
        """Set output hypercube"""
        self._hyperOut=hyper
        self._hyperIn=self.getHyperIn()
        if self._inputJob:
            self._inputJob.setHyperOut(self._hyperIn)


    def getHyperOut(self,hyperIn):
        """Return hypercube out given hypercube in.
        Defaults to same hypercube"""
        return hyperIn

    def getHyperIn(self,hyperOut):
        """Return hypercube in given hypercube out.
            Defaults to same hypercube"""
        return hyperOut
        

    def returnMinDim(self,minDimOut):
        """
            Return the minimum dimension needed in output space.
            Asumes input and ouput same size. Override if not true.   
        """
        dimOut=minDimOut
        if self._inputJob:
            dimOut=max(self._inputJob.returnMinDim(),dimOut)
        return dimOut
            

    def returnSize(self,ns):
        """Return the input dimension given output dimension.
        
            ns - Output size

            Assumes same size

            @return inDim, nbytes
        """
        nbytes=self._eout
        for n in ns:
            nbytes*=n

        if self._inputJob:
           nbytes+=self.returnSize(ns)
        else:
            nb=self._ein
            for n in ns:
                nb=nb*n
            nbytes+=nb
        return nbytes

