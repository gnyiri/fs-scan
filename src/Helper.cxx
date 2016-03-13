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
  //------------------------------------------------------------------------
  void log(std::string p_Log)
  {
    time_t t_raw_time;
    time(&t_raw_time);

    std::cout << t_raw_time << " - " << p_Log << std::endl;
    std::cout.flush();
  }
  //------------------------------------------------------------------------
  std::string getFileExtension(std::string p_FileName)
  {
    return p_FileName.substr(p_FileName.find_last_of(".") + 1);
  }
  //------------------------------------------------------------------------
  bool fileCompare(File& p_a, File& p_b)
  {
    return p_a.GetSize() > p_b.GetSize();
  }
  //------------------------------------------------------------------------
  unsigned long compute_hash(std::ifstream &f)
  {
    unsigned long hash, fsize;

    f.seekg(0, std::ios::end);
    fsize = f.tellg();
    f.seekg(0, std::ios::beg);

    hash = fsize;
    for(unsigned long tmp = 0, i = 0; i < 65536 / sizeof(tmp) && f.read((char*) &tmp, sizeof(tmp)); i++, hash += tmp);

    f.seekg(std::max(0ul, (unsigned long) fsize - 65536), std::ios::beg);

    for(unsigned long tmp = 0, i = 0; i < 65536 / sizeof(tmp) && f.read((char*) &tmp, sizeof(tmp)); i++, hash += tmp);

    return hash;
  }
}
