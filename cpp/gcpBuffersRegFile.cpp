#include "gcpBuffersRegFile.h"
#include <cstdlib>
#include <exception>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include "gcpBuffers.h"
#include "google/cloud/storage/client.h"
#include "google/cloud/storage/oauth2/google_credentials.h"
using namespace SEP;
gcpBuffersRegFile::gcpBuffersRegFile(const Json::Value &arg,
                                     const usage_code usage,
                                     const std::string &tag,
                                     const std::string &progName) {
  setUsage(usage);
  setupGCP(arg, tag);
  if (!_newFile) {
    readDescription();

    if (jsonArgs["bufferInfo"].isNull())
      error(std::string("bufferInfo not provided in JSON file"));
    _bufs.reset(
        new SEP::IO::fileBuffers(getHyper(), tag, jsonArgs["bufferInfo"]));
  }

  jsonArgs["progName"] = progName;
  jsonArgs["name"] = tag;
}

void gcpBuffersRegFile::setupGCP(const Json::Value &arg,
                                 const std::string &tag) {
  _tag = tag;

  if (arg[tag].isNull()) {
    _jsonFile = _tag;
  } else {
    _jsonFile = arg[tag].asString();
  }
  _newFile = true;
  if (_usage == usageIn)
    _newFile = false;
  else if (_usage == usageInOut) {
    try {
      namespace gcs = google::cloud::storage;
      [](gcs::Client client, std::string bucket_name, std::string object_name) {
        gcs::ObjectMetadata meta =
            client.GetObjectMetadata(_jsonFile, std::string("desc"));
      }
    } catch (std::exception const &ex) {
      _newFile = true;
    }

    std::ifstream f(getJSONFileName());
    _newFile = !f.good();
    f.close();
  }

  if (_usage == usageIn || !_newFile) {
    try {
      namespace gcs = google::cloud::storage;
      [](gcs::Client client, std::string bucket_name, std::string object_name) {
        gcs::ObjectReadStream stream =
            client.ReadObject(bucket_name, object_name);
        stream >> jsonArgs;
      }
      //! [read object] [END storage_download_file]
      (std::move(client), _jsonFile, desc);
    } catch (std::exception const &ex) {
      error(std::string("can not open object ") + _jsonFile);
    }
  }
  void gcpBuffersRegFile::close() {
    if (getUsage() == usageOut || getUsage() == usageInOut) {
      namespace gcs = google::cloud::storage;
      [](gcs::Client client, std::string bucket_name, std::string object_name,
         long desired_line_count) {
        std::string const text = "Lorem ipsum dolor sit amet";
        gcs::ObjectWriteStream stream =
            client.WriteObject(bucket_name, object_name);
        stream << jsonArgs;
        stream.Close();
      }
      //! [write object]
      (std::move(client), jsonArgs["name"], "desc");
    }

    _bufs->changeState(SEP::IO::ON_DISK);
  }
}
void gcpBuffersRegFile::createBuffers() {
  if (_bufs) return;
  if (!_hyper) error("Must set hypercube before blocking");
  if (getDataType() == SEP::DATA_UNKNOWN)
    error("Must set dataType before setting blocks");
  _bufs.reset(
      new SEP::IO::fileBuffers(getHyper(), getDataType(), _comp, _block, _mem));
  _bufs->setName(jsonArgs["name"].asString(), true);
}
