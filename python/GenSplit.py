from numba import jit 
import copy
import  Hypercube
import genJob
import threading

class regSpace:
    """Split dataset into portions"""
    def __init__(self,job,mem):
        """
        Keyword arguments:
            mem - Maximum memory per job (40 GB)
            job - Job to split up
        """
        self._mem=mem
        self._job=job

        if not isinstance(self._job,genJob.regSpace):
            raise Exception("Expecting job to be dervied from GenJob.regSpace")
        
        self._nw=[]
        self._fw=[]
        self._jw=[]
        self.makeParts()

    
    def makeParts(self):
        """ Make loops through the dataset"""

        mem=self._mem
        mem-=self._job.returnBaseMemory()

        if mem < 0:
            raise Exception("Out of memory due to job base requirements")

        hyperOut=self._job.getCompleteHyperOut()
        self._hyperOut=hyperOut
        ns=hyperOut.getNs()
        for i in range(8-len(ns)):
            ns.append(1)
        ndimLoop=None
        mem=mem*1000*1000*500 #Allow buffering
        minDim=self._job.returnMinDim(0)
        
        nc=ns[0:minDim]
        sz=self._job.returnSize(nc)
        if sz > mem:
            raise Exception("Out of memory: Memory allowed=%f baseMemory=%f minDim=%f Memory blocks=%f"%(self._mem,self._job.returnBaseMemory(),minDim,sz/1000/1000/1000))
            
        found=False
        idim=minDim
        while not found and idim < 7:
            nc=ns[0:idim+1]
            sz=self._job.returnSize(nc)
            if sz >mem:
                found=True 
            else:
                idim+=1

        
        nc=ns[0:idim]
        nc.append(1)
        found=False
        nb=mem/self._job.returnSize(nc)

        if nb <1:
            raise Exception("Error in job description. Adding a 1 to size should produce same size")

        nb=int(nb)
        while not found:
            nc[idim]=nb
            if mem>= self._job.returnSize(nc):
                found= True 
            else:
                nb-=1
    
        nc[idim]=min(nc[idim],ns[idim])
        #NC now should contain maximum chunk size
        #Construct outer and inner loops

     
        j_w=[1]*8
        f_w=[0]*8
        n_w=[1]*8
        ndone=[0]*8
        nblock=[1]*8
        for i in range(len(nc)):
            nblock[i]=nc[i]
        while ndone[7]< ns[7]:
            f_w[7]=ndone[7]
            n_w[7]=min(ns[7]-f_w[7],nblock[7])
            ndone[6]=0            
            while ndone[6]< ns[6]:
                f_w[6]=ndone[6]
                n_w[6]=min(ns[6]-f_w[6],nblock[6])
                ndone[5]=0        
                while ndone[5]< ns[5]:
                    f_w[5]=ndone[5]
                    n_w[5]=min(ns[5]-f_w[5],nblock[5])
                    ndone[4]=0       
                    while ndone[4]< ns[4]:
                        f_w[4]=ndone[4]
                        n_w[4]=min(ns[4]-f_w[4],nblock[4])
                        ndone[3]=0       
                        while ndone[3]< ns[3]:
                            f_w[3]=ndone[3]
                            n_w[3]=min(ns[3]-f_w[3],nblock[3])
                            ndone[2]=0            
                            while ndone[1]< ns[2]:
                                f_w[2]=ndone[2]
                                n_w[2]=min(ns[2]-f_w[2],nblock[2])
                                ndone[1]=0        
                                while ndone[1]< ns[1]:
                                    f_w[1]=ndone[1]
                                    n_w[1]=min(ns[1]-f_w[1],nblock[1])
                                    ndone[0]=0       
                                    while ndone[0]< ns[0]:
                                        f_w[0]=ndone[0]
                                        n_w[0]=min(ns[0]-f_w[0],nblock[0])
                                        self._nw.append(n_w)
                                        self._fw.append(f_w)
                                        self._jw.append(j_w)
                                        self._job.calcInputWindow(n_w,f_w,j_w)
                                        ndone[0]+=n_w[0]
                                    ndone[1]+=n_w[1]
                                ndone[2]+=n_w[2]
                            ndone[3]+=n_w[3]
                        ndone[4]+=n_w[4]
                    ndone[5]+=n_w[5]
                ndone[6]+=n_w[6]
            ndone[7]+=n_w[7]


def readFunc(file,buffer,nw,fw,jw):
    ndim=len(file,getHyper().axes)
    file.readWindow(buffer,nw[iwind][:ndim],fw=fw[iwind][:ndim],jw=jw[iwind][:ndim])


def writeFunc(file,buffer,nw,fw,jw):
    ndim=len(file,getHyper().axes)
    file.readWindow(buffer,nw[iwind][:ndim],fw=fw[iwind][:ndim],jw=jw[iwind][:ndim])
    
class serialRegSpace(regSpace):
    """Class for serially going through a dataset"""
    def __init__(self,job,mem):
        """
        Initialize looping through dataset serially

        job - Job 
        mem - Memory
        """

        super().__init__(job,mem)

    
    def loop(self,printPct=101):
        """Loop through dataset applying chain
        
        printPct - Print status approximately every printPct 
        """

        self._job.checkLogic()
        if printPct>0:
           printNext=printPct
        #GET INPUT BUFFER
        
        inputVec,inputFile,nw,fw,jw=self._job.allocateIOBufferIn(self._hyperOut.subCube(self._nw[0],self._fw[0],self._jw[0]),0)
        outputVec,outputFile=self._job.allocateIOBufferOut(self._hyperOut.subCube(self._nw[0],self._fw[0],self._jw[0]),0)
        readThread=threading.Thread(target=read_func, args=(inputFile,inputVec,nw,fw,jw))
        readThread.start()
    

        for i in range(len(self._nw)):
            self._job.allocateBuffer(self._hyperOut.subCube(self._nw[i],self._fw[i],self._jw[i]),i)
            readThread.join()
            if i!= len(self._nw)-1:
                self._job.swapIOBufferPtrsIn()
                inputVec,inputFile,nw,fw,jw=self._job.allocateIOBufferIn(self._hyperOut.subCube(self._nw[i+1],self._fw[i+1],self._jw[i+1]),1)
                readThread=threading.Thread(target=read_func, args=(inputFile,inputVec,nw,fw,jw))
                readThread.start()           
            self._job.processBuffer(i,self._nw[i],self._fw[i],self._jw[i])
            if i!=0:
                writeThread.join()
            self._job.swapIOBufferPtrsOut()
            writeThread=threading.thread(target=write_func,args=(outputFile,outputVec,self._nw[i],self._fw[i],self._jw[i]))
            pct=int(i*10000/len(self._nw))/100.
            if pct>printNext:
                print("Finished %f pct  %d of %d"%(pct,i,len(self._nw[i])))
                printNext+=printPct
        writeThread.join()
        self._job.deallocateBuffers()

