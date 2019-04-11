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
#include "gcpBuffersRegFile.h"
#include "ZfpCompress.h"
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
//  long long n = 40;
  long long n = 100;
  long long n123 = 1;
  int ndim = 4;
  std::vector<int> ns(ndim, n), fs(ndim, 0), js(ndim, 1);
  for (int i = 0; i < ndim; i++) {
    n123 = n123 * n;
    axes.push_back(SEP::axis(n));
  }


  std::shared_ptr<SEP::hypercube> hyper(new SEP::hypercube(axes));
  std::shared_ptr<float4DReg> ar = array(hyper);

  std::string bucket = std::string("testbucket994");
  std::string bucket1 = bucket + std::string("/dataset1");
  std::string bucket2 = bucket + std::string("/dataset2");

  std::vector<int> big(4, 40), bs(4, 2);
  big[0] = 100;

  std::shared_ptr<SEP::IO::blocking> block(new SEP::IO::blocking(bs, big));

  std::vector<std::string> args;
  std::shared_ptr<ioModes> io(new ioModes(args));

  std::shared_ptr<genericIO> gcp = io->getIO("GCPBUFFERS");
  {
  std::shared_ptr<genericRegFile> fle0,fle1;
    


  ASSERT_NO_THROW(fle0 = gcp->getRegFile(bucket1, SEP::usageOut));
  std::dynamic_pointer_cast<gcpBuffersRegFile>(fle0)->setBlocking(block);

  ASSERT_NO_THROW(fle0->setHyper(hyper));

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

   std::cerr<<"Before write float stream "<<std::endl;
  fle0->writeFloatStream(ar);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto d1 = duration_cast<microseconds>(t2 - t1).count();

  double s1 = (double)n123 * 4 / d1;
  std::cerr << "To cloud " << s1 << " MB/s " << std::endl;


  ASSERT_NO_THROW(fle0->writeDescription());
  ASSERT_NO_THROW(fle0->close());
  std::cerr<<"leaving block"<<std::endl;
}

  {
	  std::cerr<<"entering 2"<<std::endl;

  std::shared_ptr<genericRegFile> fle0,fle1;
  ASSERT_NO_THROW(fle1 = gcp->getRegFile(bucket2, SEP::usageOut));
  std::dynamic_pointer_cast<gcpBuffersRegFile>(fle1)->setBlocking(block);

  ASSERT_NO_THROW(fle1->setHyper(hyper));

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

   std::cerr<<"Before write float stream "<<std::endl;
  fle1->writeFloatStream(ar);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto d1 = duration_cast<microseconds>(t2 - t1).count();

  double s1 = (double)n123 * 4 / d1;
  std::cerr << "To buffer " << s1 << " MB/s " << std::endl;


  ASSERT_NO_THROW(fle1->writeDescription());

  ASSERT_NO_THROW(fle1->close());
  }
{ 

  std::shared_ptr<genericRegFile> fle0,fle1;
      fle1 = gcp->getRegFile(bucket1, SEP::usageIn);
  ASSERT_NO_THROW(fle1->readDescription(4));

   std::cerr<<"Before read float stream "<<std::endl;
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  fle1->readFloatStream(ar);
  high_resolution_clock::time_point t3 = high_resolution_clock::now();

  ASSERT_NO_THROW(fle1->close());

  ;

  auto d2 = duration_cast<microseconds>(t3 - t2).count();
  double s2 = (double)n123 * 4 / d2;
  std::cerr << "From cloud " << (double)n123 * 4 / d2 << " MB/s " << std::endl;
  ;
}

  namespace gcs = google::cloud::storage;
  google::cloud::v0::StatusOr<gcs::Client> client =
      gcs::Client::CreateDefaultClient();
  client.value().DeleteBucket(bucket);
}
