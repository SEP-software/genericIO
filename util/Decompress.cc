#include "regVector.h"

#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include "ioModes.h"
using namespace SEP;
int main(int argc, char** argv) {
  ioModes modes(argc, argv);

  std::shared_ptr<genericIO> io = modes.getDefaultIO();
  std::shared_ptr<paramObj> par = io->getParamObj();

  std::string out = par->getString(std::string("out"));
  std::string inDir = par->getString(std::string("indir"));
  std::cerr << "where 1" << std::endl;
  std::shared_ptr<genericRegFile> inp =
      modes.getIO("BUFFERS")->getRegFile(inDir, usageIn);

  std::shared_ptr<genericRegFile> outp = io->getRegFile(out, usageOut);
  std::cerr << "where 2" << std::endl;

  std::shared_ptr<hypercube> hyperIn = inp->getHyper();
  std::cerr << "where 2" << std::endl;

  std::vector<int> ng = hyperIn->getNs();
  std::cerr << "where 2" << std::endl;

  outp->setHyper(hyperIn);
  std::cerr << "where1 2" << std::endl;

  outp->setDataType(inp->getDataType());
  std::cerr << "where 22" << std::endl;

  int ndim = inp->getHyper()->getNdimG1();

  std::vector<axis> axes = hyperIn->getAxes(), axesBuf = hyperIn->getAxes();

  std::vector<int> bs, nb, nw, fw, jw;
  std::cerr << "where32 " << ndim << std::endl;

  switch (ndim) {
    case 1: {
      nw.push_back(std::min(hyperIn->getN123(), (long long)250000));
      fw.push_back(0);
      jw.push_back(1);
      size_t done = 0;
      axes[0].n = nw[0];
      std::shared_ptr<hypercube> hypOut(new hypercube(axes));
      std::shared_ptr<regSpace> vec = vecFromHyper(hypOut, inp->getDataType());
      while (fw[0] < hyperIn->getN123()) {
        inp->readWindow(nw, fw, jw, vec);
        outp->writeWindow(nw, fw, jw, vec);
        fw[0] += nw[0];
        nw[0] = std::min((long long)250000, hyperIn->getN123() - fw[0]);
      }
    } break;

    case 2: {
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
          outp->writeWindow(nw, fw, jw, vec);
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
      std::cerr << "where 1 " << std::endl;
      std::vector<int> ns(7, 1), nb(3, 1);
      std::cerr << "MMM" << std::endl;

      for (int i = 0; i < axes.size(); i++) ns[i] = axes[i].n;
      for (int i = 3; i < axesBuf.size(); i++) axesBuf[i].n = 1;
      std::cerr << "MM1M" << std::endl;
      if (axes[0].n * axes[1].n * axes[2].n < (long long)250000000) {
        std::cerr << "MM2M" << std::endl;

        for (int i = 0; i < 3; i++) {
          nb[i] = axes[i].n;
        }
      } else if (axes[0].n * axes[1].n < (long long)25000000) {
        std::cerr << "MMM3" << std::endl;

        nb[0] = axes[0].n;
        nb[1] = axes[1].n;
        nb[2] = 250000000 / nb[0] / nb[1];
      } else if (axes[0].n < (long long)250000000) {
        std::cerr << "MMM4" << std::endl;

        nb[0] = axes[0].n;

        nb[1] = 250000000 / axes[0].n;
        nb[2] = 1;
      } else {
        nb[0] = 250000000;
        nb[1] = 1;
        nb[2] = 1;
      }
      std::cerr << "where 1 " << std::endl;

      for (int i = 0; i < 3; i++) {
        nw.push_back(nb[i]);
        fw.push_back(0);
        jw.push_back(1);
        std::cerr << "where 1 " << i << " " << axesBuf.size() << std::endl;

        axesBuf[i].n = nb[i];
      }
      std::cerr << "mmm" << std::endl;
      for (int i = 3; i < 7; i++) {
        nw.push_back(1);
        fw.push_back(0);
        jw.push_back(1);
      }
      std::cerr << "where 12 " << std::endl;

      std::shared_ptr<hypercube> hypOut(new hypercube(axes));
      std::cerr << "where 31 " << getTypeString(inp->getDataType())
                << std::endl;

      std::shared_ptr<regSpace> vec = vecFromHyper(hypOut, inp->getDataType());
      std::cerr << "where4 " << std::endl;

      for (int i6 = 0; i6 < ns[6]; i6++) {
        fw[6] = i6;
        for (int i5 = 0; i5 < ns[5]; i5++) {
          fw[5] = i5;
          for (int i4 = 0; i4 < ns[4]; i4++) {
            for (int i3 = 0; i3 < ns[3]; i3++) {
              while (fw[2] < axes[2].n) {
                while (fw[1] < axes[1].n) {
                  while (fw[0] < axes[0].n) {
                    std::cerr << "doing read " << fw[0] << " " << fw[1] << " "
                              << fw[2] << " n-" << nw[0] << " " << nw[1] << " "
                              << nw[2] << std::endl;
                    inp->readWindow(nw, fw, jw, vec);
                    std::cerr << "after read" << std::endl;
                    outp->writeWindow(nw, fw, jw, vec);
                    std::cerr << "after write" << std::endl;
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
