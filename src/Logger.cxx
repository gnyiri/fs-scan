/*
 * Logger.cxx
 *
 *  Created on: 2011.11.12.
 *      Author: gnyiri
 */

#include "Logger.h"

namespace fsscan
{

  Logger* Logger::m_Instance = 0;
//------------------------------------------------------------------------
  Logger::Logger()
  {
    m_Instance = 0;

    OpenFile("fs-scan.log");
  }
//------------------------------------------------------------------------
  Logger* Logger::GetInstance()
  {
    if(!m_Instance)
    {
      m_Instance = new Logger;
    }

    return m_Instance;
  }
//------------------------------------------------------------------------
  int Logger::OpenFile(std::string p_FileName)
  {
    m_LogFile.open(p_FileName.c_str());

    if(!m_LogFile.is_open())
    {
      return 0;
    }

    return 1;
  }
//------------------------------------------------------------------------
  void Logger::Print(std::string p_Msg)
  {
    time_t t_RawTime;
    time(&t_RawTime);

    m_LogFile << t_RawTime << " - " << p_Msg << std::endl;
    std::cout << t_RawTime << " - " << p_Msg << std::endl;
  }

} /* namespace dirscan */
