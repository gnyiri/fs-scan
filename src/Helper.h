/*
 * Helper.h
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <iostream>
#include <string>

#include "File.h"

namespace fsscan
{

  void log(std::string p_Log);
  std::string getFileExtension(std::string p_FileName);
  bool fileCompare(File t_A,File t_B);
  unsigned long compute_hash(std::ifstream &f);
}

#endif /* HELPER_H_ */
