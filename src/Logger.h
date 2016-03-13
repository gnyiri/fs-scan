/*
 * Logger.h
 *
 *  Created on: 2011.11.12.
 *      Author: gnyiri
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <iostream>
#include <fstream>

namespace fsscan
{

  class Logger
  {
  public:
    static Logger* GetInstance();

    void Print(std::string p_Msg);

  private:

    Logger();
    ~Logger();

    int OpenFile(std::string p_FileName);
    static Logger* m_Instance;

    std::ofstream m_LogFile;
  };

} /* namespace dirscan */
#endif /* LOGGER_H_ */
