#include <float3DReg.h>
#include <gtest/gtest.h>  // googletest header file
#include <ioModes.h>
using namespace SEP;
TEST(TESTGCP, basic) {
  std::vector<std::string> args;
  args.push_back("args");
  ioModes modes(args);
  std::shared_ptr<genericIO> io = modes.getIO("GCPBUFFERS");

  std::shared_ptr<genericRegFile> file =
      io->getRegFile("unitTestB/testFile", usageOut);

  std::shared_ptr<hypercube> hyper(new hypercube(1000, 1000, 1000));
  std::shared_ptr<float3DReg> buf(new float3DReg(hyper));
  for (int i = 0; i < 1000 * 1000 * 1000; i++) {
    _hyper->getVals()[i] = i;
  }
  std::vector<int> nw(3, 1000), fw(3, 0), jw(3, 1);
  file->writeFloatWindow(nw, fw, jw, buf);
  file->close();
}
