/*
 * Helper.cxx
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#include "Helper.h"
#include <time.h>
#include <iostream>
#include <fstream> 

namespace fsscan
{

  void log(std::string p_Log)
  {
    time_t t_RawTime;
    time(&t_RawTime);

    std::cout << t_RawTime << " - " << p_Log << std::endl;
    std::cout.flush();
  }

  std::string getFileExtension(std::string p_FileName)
  {
    return p_FileName.substr(p_FileName.find_last_of(".") + 1);
  }

  bool fileCompare(File t_A, File t_B)
  {
    return t_A.GetSize() > t_B.GetSize();
  }

  int MAX(int x, int y)
  {
    if ((x) > (y))
      return x;
    else
      return y;
  }

  unsigned long compute_hash(std::ifstream& f)
  {
    unsigned long hash, fsize;

    f.seekg(0, std::ios::end);
    fsize = f.tellg();
    f.seekg(0, std::ios::beg);

    hash = fsize;
    for (unsigned long tmp = 0, i = 0; i < 65536 / sizeof (tmp) && f.read((char*) &tmp, sizeof (tmp)); i++, hash += tmp);

    f.seekg(MAX(0, (unsigned long) fsize - 65536), std::ios::beg);

    for (unsigned long tmp = 0, i = 0; i < 65536 / sizeof (tmp) && f.read((char*) &tmp, sizeof (tmp)); i++, hash += tmp);

    return hash;
  }

}
