/*
 * BaseClass.h
 *
 *  Created on: 2011.11.12.
 *      Author: gergely.nyiri@gmail.com
 */

#ifndef BASECLASS_H_
#define BASECLASS_H_

#include <string>
#include "Logger.h"

namespace fsscan
{

  class BaseClass
  {
    enum ErrorType
    {
      ERROR_OK = 0,
      ERROR_BAD_INPUT,
      ERROR_BAD_ALLOC,
      ERROR_IO,
      ERROR_GENERAL
    };
  public:
    BaseClass();
    virtual ~BaseClass();

    static std::string GetErrorString(ErrorType p_Error);

    void Log(const std::string p_Msg) const;

  private:
    ErrorType m_Error;
    Logger* m_Logger;

  };

} /* namespace dirscan */
#endif /* BASECLASS_H_ */
