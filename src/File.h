/*
 * File.h
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#ifndef FILE_H_
#define FILE_H_

#include "BaseNode.h"

namespace fsscan
{

class File: public BaseNode
{
public:
  File();
  virtual ~File();

  void SetSize(unsigned long p_Size);
  unsigned long GetSize() const;
  
  void SetExtension(std::string p_Extension);
  std::string GetExtension() const;

  void PrintSelf();

protected:
  std::string m_BaseName;
  std::string m_Extension;
  unsigned long m_Size;
};

}
#endif /* FILE_H_ */
