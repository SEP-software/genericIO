#include "buffersRegFile.h"
#include <cstdlib>
#include <exception>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
using namespace SEP;

void buffersRegFile::writeDescription() {
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<axis> axes = hyper->returnAxes(hyper->getNdim());
  std::cerr << "what is going on " << std::endl;
  for (int i = 1; i <= axes.size(); i++) {
    putInt(std::string("n") + std::to_string(i), axes[i - 1].n);
    putFloat(std::string("o") + std::to_string(i), axes[i - 1].o);
    putFloat(std::string("d") + std::to_string(i), axes[i - 1].d);
    putString(std::string("label") + std::to_string(i), axes[i - 1].label);
  }

  if (_bufs)
    throw SEPException("buffer info not setup");
  else
    std::cerr << "bufs is setup " << _bufs << std::endl;
  jsonArgs["bufferInfo"] = _bufs->getDescription();
  std::cerr << "what is going on " << std::endl;
  jsonArgs["dataType"] = getTypeString(getDataType());
}
