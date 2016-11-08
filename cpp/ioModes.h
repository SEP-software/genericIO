#ifndef IOMODES
#define IOMODES 1
#include "genericIO.h"
#include "jsonGenericIO.h"

class ioModes{
  public:
    ioModes( int argc,  char **argv);


   std::shared_ptr<genericIO> getDefaultIO(){ return _defaultIO;}
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
  public:
     static void setup( int argc, char **argv);
     static ioModes *getIO(){ return _io;}

  
  private:

    ioModesFortran(){;}
    ~ioModesFortran(){;}
    static ioModes *_io;


};

#endif