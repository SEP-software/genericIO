#include "buffersRegFile.h"
#include <cstdlib>
#include <exception>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
using namespace SEP;
buffersRegFile::buffersRegFile(std::shared_ptr<Json::Value> arg,
                               const usage_code usage, const std::string &tag) {
  setUsage(usage);
  setupJson(arg, tag, std::string("/des.dat"));

  if (!_newFile) {
    if (jsonArgs["bufferInfo"].isNull())
      error(std::string("bufferInfo not provided in JSON file"));
    _bufs.reset(new SEP::IO::buffers(getHyper(), jsonArgs["bufferInfo"]));
  }
}

void buffersRegFile::writeDescription() {
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<axis> axes = hyper->returnAxes(hyper->getNdim());
  for (int i = 1; i <= axes.size(); i++) {
    putInt(std::string("n") + std::to_string(i), axes[i - 1].n);
    putFloat(std::string("o") + std::to_string(i), axes[i - 1].o);
    putFloat(std::string("d") + std::to_string(i), axes[i - 1].d);
    putString(std::string("label") + std::to_string(i), axes[i - 1].label);
  }
  jsonArgs["bufferInfo"] = _bufs->getDescription();
}

void buffersRegFile::close() {
  if (getUsage() == usageOut || getUsage() == usageInOut) {
    std::ofstream outps;
    outps.open(getJSONFileName(), std::ofstream::out);
    if (!outps) {
      std::cerr << std::string("Trouble opening for write") + getJSONFileName()
                << std::endl;
      throw std::exception();
    }
    try {
      outps << jsonArgs;
    } catch (int x) {
      std::cerr << std::string("Trouble writing JSON file ") + getJSONFileName()
                << std::endl;
      throw std::exception();
    }
    _bufs.changeState(SEP::IO::ON_DISK);
  }
}
