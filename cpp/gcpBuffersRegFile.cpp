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
                                     const std::string &progName,
                                     const int ndimMax) {
  setUsage(usage);
  setupGCP(arg, tag);
  if (!_newFile) {
    readDescription(ndimMax);

    if (jsonArgs["bufferInfo"].isNull())
      error(std::string("bufferInfo not provided in JSON file"));
    _bufs.reset(
        new SEP::IO::gcpBuffers(getHyper(), tag, jsonArgs["bufferInfo"]));
  }

  jsonArgs["progName"] = progName;
  jsonArgs["name"] = tag;
}

void gcpBuffersRegFile::setupGCP(const Json::Value &arg,
                                 const std::string &tag) {
  _tag = tag;
  std::string bucket, baseName;

  int pos;
  if ((pos = dir.find("/")) == std::string::npos) {  // No subdirectory
    bucket = tage;
    baseName = ;
  } else {
    _baseName = dir;
    bucket = baseName.substr(0, baseName.find("/"));
    baseName.erase(0, baseName.find("/") + 1);
  }
  _bucket = bucket;
  _dir = basename;
  _projectID = getEnvVar("projectID", "NONE");
  _region = getEnvVar("region", "us-west1");
  if (_projectID == std::string("NONE")) {
    std::cerr << "Must set environmental variable " << _projectID << std::endl;
    exit(1);
  }
  namespace gcs = google::cloud::storage;
  google::cloud::v0::StatusOr<gcs::Client> client =
      gcs::Client::CreateDefaultClient();
  if (!client)
    throw(SEPException(std::string("Trouble creating default client")));
  _client = client;
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
      [](gcs::Client client, std::string bucket_name, std::string object_name,
         std::shared_ptr<storeByte> buf) {
        gcs::ObjectReadStream stream =
            client.ReadObject(bucket_name, object_name);
        jsonArgs << stream;
        stream.Close();
      }(std::move(_client.value()), bucketName, basename + std::string("/dir"),
        val);
    } catch (std::exception const &ex) {
      std::cerr << "Trouble reading from bucket " << _name << std::endl;
      exit(1);
    }
  }
  if (_usage == usageIn || !_newFile) {
    try {
      [](gcs::Client client, std::string bucket_name, std::string object_name,
         std::shared_ptr<storeByte> buf) {
        gcs::ObjectReadStream stream =
            client.ReadObject(bucket_name, object_name);
        jsonArgs << stream;
        stream.Close();
      }(std::move(_client.value()), bucketName, basename + std::string("/dir"),
        val);
    } catch (std::exception const &ex) {
      std::cerr << "Trouble reading from bucket " << _name << std::endl;
      exit(1);
    }
  }
}
void gcpBuffersRegFile::close() {
  if (getUsage() == usageOut) ||getUsage() == usageInOut) {
      gcs::ObjectWriteStream stream =
          _client.value().WriteObject(_bucketName, _dir + std::string("/dir"));
      stream << jsonArgs;
      stream.Close();
      google::cloud::v0::StatusOr<gcs::ObjectMetadata> metadata =
          std::move(stream).metadata();
      if (!metadata) {
        std::cerr << "FAILURE " << _name << std::endl;
        std::cerr << metadata.status().message() << std::endl;
        throw SEPException(std::string("Trouble writing object"));
      }
    }
  _bufs->changeState(SEP::IO::ON_DISK);
}
void gcpBuffersRegFile::createBuffers() {
  if (_bufs) return;
  if (!_hyper) error("Must set hypercube before blocking");
  if (getDataType() == SEP::DATA_UNKNOWN)
    error("Must set dataType before setting blocks");
  _bufs.reset(
      new SEP::IO::gcpBuffers(getHyper(), getDataType(), _comp, _block, _mem));
  _bufs->setName(jsonArgs["name"].asString(), true);
}
