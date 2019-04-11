#include <gtest/gtest.h>  // googletest header file
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "float4DReg.h"
#include "google/cloud/status_or.h"
#include "google/cloud/storage/client.h"
#include "google/cloud/storage/oauth2/google_credentials.h"
#include "ioModes.h"
#include "ioTypes.h"
#include "blocking.h"
using namespace std::chrono;

using std::string;
using namespace SEP;

std::shared_ptr<float4DReg> array(std::shared_ptr<SEP::hypercube> hyper) {
  std::shared_ptr<float4DReg> buf(new float4DReg(hyper));
  float *v = buf->getVals();
  for (auto ii = 0; ii < buf->getHyper()->getN123(); ii++)
    v[ii] = (float)rand() / ((float)RAND_MAX) + ii * .04 + 5.;
return buf;
}

TEST(TESTBucketCreation, gcpBuffers) {
  std::vector<SEP::axis> axes;
  long long n = 40;
  //long long n = 200;
  long long n123 = 1;
  int ndim = 4;
  std::vector<int> ns(ndim, n), fs(ndim, 0), js(ndim, 1);
  for (int i = 0; i < ndim; i++) {
    n123 = n123 * n;
    axes.push_back(SEP::axis(n));
  }


  std::cerr<<"where do i die 1 "<<std::endl;
  std::shared_ptr<SEP::hypercube> hyper(new SEP::hypercube(axes));
  std::shared_ptr<float4DReg> ar = array(hyper);

  std::cerr<<"where1do i die 1 "<<std::endl;
  std::string bucket = std::string("testbucket994");
  std::string bucket1 = bucket + std::string("/dataset1");
  std::string bucket2 = bucket + std::string("/dataset2");

  std::vector<int> big(4, 40), bs(4, 2);
  big[0] = 100;

  std::cerr<<"where2do i die 1 "<<std::endl;
  std::shared_ptr<SEP::IO::blocking> block(new SEP::IO::blocking(bs, big));

  std::vector<std::string> args;
  std::shared_ptr<ioModes> io(new ioModes(args));

  std::cerr<<"where3do i die 1 "<<std::endl;
  std::shared_ptr<genericIO> gcp = io->getIO("GCPBUFFERS");
  std::shared_ptr<genericRegFile> fle0;


  std::cerr<<"where4do i die 1 "<<std::endl;
  ASSERT_NO_THROW(fle0 = gcp->getRegFile(bucket1, SEP::usageOut));

  ASSERT_NO_THROW(fle0->setHyper(hyper));

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  std::cerr<<"where6do i die 1 "<<std::endl;

  ASSERT_NO_THROW(fle0->writeFloatStream(ar));
  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  std::cerr<<"where5do i die 1 "<<std::endl;
  ASSERT_NO_THROW(fle0->writeDescription());

  ASSERT_NO_THROW(fle0->close());

  std::shared_ptr<genericRegFile> fle1;

  ASSERT_NO_THROW(
      fle1 = gcp->getRegFile("testbucket1993/testIt", SEP::usageIn));
  ASSERT_NO_THROW(fle1->readDescription(4));

  ASSERT_NO_THROW(fle1->readFloatStream(ar));
  high_resolution_clock::time_point t3 = high_resolution_clock::now();

  ASSERT_NO_THROW(fle1->close());

  auto d1 = duration_cast<microseconds>(t2 - t1).count();

  double s1 = (double)n123 * 4 / d1;
  std::cerr << "To buffer " << s1 << " MB/s " << std::endl;
  ;

  auto d2 = duration_cast<microseconds>(t3 - t2).count();
  double s2 = (double)n123 * 4 / d2;
  std::cerr << "From cloud " << (double)n123 * 4 / d2 << " MB/s " << std::endl;
  ;

  namespace gcs = google::cloud::storage;
  google::cloud::v0::StatusOr<gcs::Client> client =
      gcs::Client::CreateDefaultClient();
  client.value().DeleteBucket(bucket);
}
