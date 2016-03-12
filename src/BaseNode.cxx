/*
 * BaseFile.cxx
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#include "BaseNode.h"

namespace fsscan
{

BaseNode::BaseNode() :
    m_Path("."),
    m_Level(0)
{

}

void BaseNode::SetPath(const std::string p_Path)
{
  m_Path = p_Path;
}

std::string BaseNode::GetPath() const
{
  return m_Path;
}

void BaseNode::SetLevel(const unsigned int p_Level)
{
  m_Level = p_Level;
}

int BaseNode::GetLevel() const
{
  return m_Level;
}

}
