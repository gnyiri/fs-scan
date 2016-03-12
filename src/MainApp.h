/*
 * DirScanApp.h
 *
 *  Created on: 2011.11.06.
 *      Author: gnyiri
 */

#ifndef DIRSCANAPP_H_
#define DIRSCANAPP_H_

#include <map>
#include <vector>
#include "BaseClass.h"
#include "Helper.h"
#include "File.h"

namespace fsscan
{

class MainApp : public BaseClass
{
public:

  struct Extension
  {
    unsigned int m_Count;
    unsigned long m_Size;
  };

  typedef std::map<std::string,Extension> ExtensionMap;
  typedef std::map<std::string,unsigned long> CounterMap;
  typedef std::vector<File> FileVector;

  explicit MainApp(std::string p_Root);
  virtual ~MainApp();

  int Update();

  void Dump();

protected:

  MainApp();
  void Init();

private:

  std::string m_Root;

  CounterMap m_Counters;
  ExtensionMap m_Extensions;
  FileVector m_Files;
};

}
#endif /* DIRSCANAPP_H_ */
