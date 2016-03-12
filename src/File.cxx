/*
 * File.cxx
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#include "File.h"
#include <iostream>

namespace fsscan
{

File::File()
{

}

File::~File()
{

}

void File::SetSize(unsigned long p_Size)
{
  m_Size = p_Size;
}

unsigned long File::GetSize() const
{
  return m_Size;
}

void File::SetExtension(std::string p_Extension)
{
  m_Extension = p_Extension;
}
std::string File::GetExtension() const
{
  return m_Extension;
}

void File::PrintSelf()
{
  std::cout << "Path = " << m_Path << ", level = " << m_Level << ", size = " << m_Size << std::endl;
}

}
