/*
 * BaseNode.h
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#ifndef BASEFILE_H_
#define BASEFILE_H_

#include <string>

namespace fsscan
{

class BaseNode
{
public:
  BaseNode();
  virtual ~BaseNode() {};
  virtual void PrintSelf() = 0;

  void SetLevel(const unsigned int p_Level);
  int GetLevel() const;

  void SetPath(const std::string p_Path);
  std::string GetPath() const;

protected:
  std::string m_Path;
  unsigned int m_Level;
};

}
#endif /* BASEFILE_H_ */
