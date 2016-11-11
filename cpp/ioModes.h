#ifndef IOMODES
#define IOMODES 1
#include "genericIO.h"
#include "jsonGenericIO.h"
#include<mutex>
class ioModes{
  public:
    ioModes(){;}
    ioModes(int argc,  char **argv){ setup(argc,argv);}
    void setup(int argc, char**argv);
   std::shared_ptr<genericIO> getDefaultIO();
   std::shared_ptr<genericIO> getIO(std::string def);
   std::shared_ptr<genericRegFile> getRegFile(const std::string def,std::string name,const usage_code usage);
   std::shared_ptr<genericRegFile> getGenericRegFile(const std::string name,const usage_code usage);
   std::string getDefaultType(){ return _defaultType;}
  private:
    std::shared_ptr<genericIO> _defaultIO;
    std::map<std::string,std::shared_ptr<genericIO>> _ios;

    std::shared_ptr<paramObj> _par;
    std::string _defaultType;

};

class ioModesFortran{
  private:

 
    ioModesFortran();
    ioModesFortran(const ioModesFortran& rs);
    ioModesFortran& operator = (const ioModesFortran& rs);
 
  public:
    ~ioModesFortran();
    static std::shared_ptr<ioModes> getIO(){
       static std::shared_ptr<ioModes> _io(new ioModes());
       return _io;
    }
    static void setup( int argc, char **argv);
        static std::shared_ptr<ioModes> _io;

 
  static std::shared_ptr<ioModesFortran>& getInstance()
  {
    static std::shared_ptr<ioModesFortran> instance = nullptr;
 
    if (!instance)
    {

 
      if (!instance) {
      instance.reset(new ioModesFortran());
      }
    }
 
  return instance;
  }
 
};


#endif