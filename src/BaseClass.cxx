/*
 * BaseClass.cxx
 *
 *  Created on: 2011.11.12.
 *      Author: gergely.nyiri@gmail.com
 */

#include "BaseClass.h"

namespace fsscan
{

BaseClass::BaseClass() :
    m_Error(ERROR_OK)
{
  m_Logger = Logger::GetInstance();
}

BaseClass::~BaseClass()
{
  Log("BaseClass DTOR");
}

void BaseClass::Log(const std::string p_Msg) const
{
  m_Logger->Print(p_Msg);
}

std::string BaseClass::GetErrorString(ErrorType p_Error)
{
  switch(p_Error)
  {
  case ERROR_OK:
    return "No Error";
    break;
  case ERROR_BAD_INPUT:
    return "Bad Input";
    break;
  case ERROR_BAD_ALLOC:
    return "Bad Allocation";
    break;
  case ERROR_IO:
    return "I/O Error";
    break;
  default:
    return "General Error";
    break;
  }
  return "";
}

} /* namespace dirscan */
