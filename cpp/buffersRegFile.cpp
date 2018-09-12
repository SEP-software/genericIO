#include "buffersRegFile.h"
#include <cstdlib>
#include <exception>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
using namespace SEP;
buffersRegFile::buffersRegFile(const Json::Value &arg, const usage_code usage,
                               const std::string &tag,
                               const std::string &progName) {
  std::cerr << "in buf reg file" << std::endl;
  setUsage(usage);
  std::cerr << "" setupJson(arg, tag, std::string("/des.dat"));

  if (!_newFile) {
    readDescription();

    if (jsonArgs["bufferInfo"].isNull())
      error(std::string("bufferInfo not provided in JSON file"));
    _bufs.reset(new SEP::IO::buffers(getHyper(), tag, jsonArgs["bufferInfo"]));
  }

  jsonArgs["progName"] = progName;
  jsonArgs["directory"] = tag;
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
  jsonArgs["dataType"] = getTypeString(getDataType());
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
    _bufs->changeState(SEP::IO::ON_DISK);
  }
}
void buffersRegFile::createBuffers() {
  if (_bufs) return;
  if (!_hyper) error("Must set hypercube before blocking");
  if (getDataType() == SEP::DATA_UNKNOWN)
    error("Must set dataType before setting blocks");
  _bufs.reset(
      new SEP::IO::buffers(getHyper(), getDataType(), _comp, _block, _mem));
  _bufs->setDirectory(jsonArgs["directory"].asString(), true);
}