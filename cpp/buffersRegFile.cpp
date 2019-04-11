#include "buffersRegFile.h"
#include <cstdlib>
#include <exception>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
using namespace SEP;

void buffersRegFile::writeDescription() {
	std::cerr<<"iwjhere  descripotion"<<std::endl;
  std::shared_ptr<hypercube> hyper = getHyper();
	std::cerr<<"if1write descripotion"<<std::endl;
  std::vector<axis> axes = hyper->returnAxes(hyper->getNdim());
	std::cerr<<"ia1write descripotion"<<std::endl;
  for (int i = 1; i <= axes.size(); i++) {
    putInt(std::string("n") + std::to_string(i), axes[i - 1].n);
    putFloat(std::string("o") + std::to_string(i), axes[i - 1].o);
    putFloat(std::string("d") + std::to_string(i), axes[i - 1].d);
    putString(std::string("label") + std::to_string(i), axes[i - 1].label);
  }
	std::cerr<<"in2write descripotion"<<std::endl;
  jsonArgs["bufferInfo"] = _bufs->getDescription();
  jsonArgs["dataType"] = getTypeString(getDataType());
	std::cerr<<"in3write descripotion"<<std::endl;
}
