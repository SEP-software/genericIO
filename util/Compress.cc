//#include <boost/filesystem.hpp>
#include "regVector.h"

#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include "ZfpCompress.h"
#include "buffersRegFile.h"
#include "ioModes.h"
using namespace SEP;
int main(int argc, char** argv) {
  ioModes modes(argc, argv);

  std::shared_ptr<genericIO> io = modes.getDefaultIO();
  std::shared_ptr<paramObj> par = io->getParamObj();

  std::string in = par->getString(std::string("in"));

  std::string outDir = par->getString(std::string("outdir"));

  std::shared_ptr<genericRegFile> inp = io->getRegFile(in, usageIn);

  std::shared_ptr<genericRegFile> outp =
      modes.getIO("BUFFERS")->getRegFile(outDir, usageOut);

  std::shared_ptr<hypercube> hyperIn = inp->getHyper();
  std::vector<int> ng = hyperIn->getNs();
  outp->setHyper(hyperIn);
  outp->setDataType(inp->getDataType());

  SEP::IO::ZfpParams zpars;

  std::string mode =
      par->getString(std::string("mode"), std::string("tolerance"));
  float rate, tolerance;
  int precision;

  if (mode == std::string("tolerance")) {
    zpars._meth = SEP::IO::ZFP_TOLERANCE;
    zpars._tolerance = par->getFloat(std::string("tolerance"), 3e-1);

  } else if (mode == std::string("accuracy")) {
    zpars._meth = SEP::IO::ZFP_ACCURACY;
    zpars._precision = par->getInt(std::string("precision"), 15);
  } else if (mode == std::string("precision")) {
    zpars._meth = SEP::IO::ZFP_PRECISION;
    zpars._rate = par->getInt(std::string("rate"), 7.);

  } else
    par->error("Only support rate, accuracy, or precission modes for now");

  std::cerr << inp->getDataTypeString() << "=datatype" << std::endl;
  std::shared_ptr<SEP::IO::ZfpCompression> comp(
      new SEP::IO::ZfpCompression(outp->getDataType(), zpars));
  std::cerr << "where1 do i2 die " << std::endl;

  std::shared_ptr<SEP::buffersRegFile> bufFile =
      std::dynamic_pointer_cast<SEP::buffersRegFile>(outp);
  std::cerr << "before SET COMPRE 2do i2 die " << std::endl;
  assert(bufFile);
  std::cerr << "After assert " << std::endl;
  bufFile->setCompression(comp);
  std::cerr << "w1here do i2 die " << std::endl;

  bufFile->setDataType(inp->getDataType());
  std::cerr << "w2here do i2 die " << std::endl;

  int ndim = inp->getHyper()->getNdimG1();
  std::cerr << "w3here do i2 die " << std::endl;

  std::vector<axis> axes = hyperIn->getAxes(), axesBuf = hyperIn->getAxes();
  std::cerr << "w4here do i2 die " << std::endl;

  std::vector<int> bs, nb, nw, fw, jw;
  std::cerr << "NDIM= " << ndim << std::endl;

  switch (ndim) {
    case 1: {
      bs.push_back(1);
      nb.push_back(std::min((long long)250000, hyperIn->getN123()));
      std::shared_ptr<SEP::IO::blocking> block(new SEP::IO::blocking(bs, nb));
      bufFile->setBlocking(block);
      nw.push_back(std::min(hyperIn->getN123(), (long long)250000));
      fw.push_back(0);
      jw.push_back(1);
      size_t done = 0;
      axes[0].n = nw[0];
      std::shared_ptr<hypercube> hypOut(new hypercube(axes));
      std::shared_ptr<regSpace> vec = vecFromHyper(hypOut, inp->getDataType());
      while (fw[0] < hyperIn->getN123()) {
        inp->readWindow(nw, fw, jw, vec);
        bufFile->writeWindow(nw, fw, jw, vec);
        fw[0] += nw[0];
        nw[0] = std::min((long long)250000, hyperIn->getN123() - fw[0]);
      }
    } break;

    case 2: {
      bs.push_back(16);
      bs.push_back(4);
      nb.push_back(1024);
      nb.push_back(256);
      std::shared_ptr<SEP::IO::blocking> block(new SEP::IO::blocking(bs, nb));
      bufFile->setBlocking(block);
      if (axes[0].n < 250000000) {
        std::vector<int> nb(2, 1);
        nw.push_back(axes[0].n);
        nb[0] = axes[0].n;
        nb[1] =
            std::min((long long)axes[1].n, (long long)250000000 / axes[0].n);
      } else {
        nb[0] = 250000000;
        nb[1] = 1;
      }

      nw.push_back(nb[0]);
      nw.push_back(nb[1]);
      fw.push_back(0);
      jw.push_back(1);
      fw.push_back(0);
      jw.push_back(1);
      axesBuf[0].n = nw[0];
      axesBuf[1].n = nw[1];
      std::shared_ptr<hypercube> hypOut(new hypercube(axes));

      std::shared_ptr<regSpace> vec = vecFromHyper(hypOut, inp->getDataType());

      while (fw[1] < axes[1].n) {
        while (fw[0] < axes[0].n) {
          inp->readWindow(nw, fw, jw, vec);
          bufFile->writeWindow(nw, fw, jw, vec);
          fw[0] += nw[0];
          nw[0] = std::min(axes[0].n - fw[0], nb[0]);
        }
        fw[0] = 0;
        nw[0] = nb[0];
        fw[1] += nb[1];
        nw[1] = std::min(axes[1].n - fw[1], nb[1]);
      }
    } break;

    default: {
      std::vector<int> ns(7, 1), nb(3, 1);
      for (int i = 0; i < axes.size(); i++) ns[i] = axes[i].n;
      for (int i = 3; i < axesBuf.size(); i++) axesBuf[i].n = 1;
      bs.push_back(16);
      bs.push_back(4);
      bs.push_back(4);
      nb.push_back(256);
      nb.push_back(32);
      nb.push_back(32);
      std::shared_ptr<SEP::IO::blocking> block(new SEP::IO::blocking(bs, nb));
      bufFile->setBlocking(block);
      if (axes[0].n * axes[1].n * axes[2].n < (long long)250000000) {
        for (int i = 0; i < 3; i++) {
          nb[i] = axes[i].n;
        }
      } else if (axes[0].n * axes[1].n < (long long)25000000) {
        nb[0] = axes[0].n;
        nb[1] = axes[1].n;
        nb[2] = 250000000 / nb[0] / nb[1];
      } else if (axes[0].n < (long long)250000000) {
        nb[0] = axes[0].n;

        nb[1] = 250000000 / axes[0].n;
        nb[2] = 1;
      } else {
        nb[0] = 250000000;
        nb[1] = 1;
        nb[2] = 1;
      }
      for (int i = 0; i < 3; i++) {
        nw.push_back(nb[i]);
        fw.push_back(0);
        jw.push_back(1);
        axesBuf[i].n = nb[i];
      }
      for (int i = 3; i < 7; i++) {
        nw.push_back(1);
        fw.push_back(0);
        jw.push_back(1);
      }

      std::shared_ptr<hypercube> hypOut(new hypercube(axes));

      std::shared_ptr<regSpace> vec = vecFromHyper(hypOut, inp->getDataType());

      for (int i6 = 0; i6 < ns[6]; i6++) {
        fw[6] = i6;
        for (int i5 = 0; i5 < ns[5]; i5++) {
          fw[5] = i5;
          for (int i4 = 0; i4 < ns[4]; i4++) {
            for (int i3 = 0; i3 < ns[3]; i3++) {
              while (fw[2] < axes[2].n) {
                while (fw[1] < axes[1].n) {
                  while (fw[0] < axes[0].n) {
                    inp->readWindow(nw, fw, jw, vec);
                    bufFile->writeWindow(nw, fw, jw, vec);
                    fw[0] += nw[0];
                    nw[0] = std::min(axes[0].n - fw[0], nb[0]);
                  }
                  fw[0] = 0;
                  nw[0] = nb[0];
                  fw[1] += nb[1];
                  nw[1] = std::min(axes[1].n - fw[1], nb[1]);
                }
                fw[1] = 0;
                nw[1] = nb[1];
                fw[2] += nb[2];
                nw[2] = std::min(axes[2].n - fw[2], nb[2]);
              }
            }
          }
        }
      }
    } break;
  }
  outp->writeDescription();
  outp->close();
  return EXIT_SUCCESS;
}
