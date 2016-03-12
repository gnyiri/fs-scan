/*
 * MainApp.cxx
 *
 *  Created on: 2011.11.06.
 *      Author: gnyiri
 */

#include <fts.h>
#include <sys/stat.h>
#include <algorithm>
#include <fstream>
#include "MainApp.h"

namespace fsscan
{
//------------------------------------------------------------------------
MainApp::MainApp(std::string p_Root) :
        m_Root(p_Root)
{
  Log("MainApp CTOR");

  Init(); 
}
//------------------------------------------------------------------------
MainApp::~MainApp()
{
  Log("MainApp DTOR");
}
//------------------------------------------------------------------------
void MainApp::Init()
{
  Log("MainApp Init");

  m_Counters["File"] = 0;
  m_Counters["Dir"]  = 0;
  m_Counters["Size"] = 0;

  m_Extensions.clear();
  m_Files.clear();
}
//------------------------------------------------------------------------
int MainApp::Update()
{
  Log("MainApp Update");

  Init();

  char *paths[] = { const_cast<char*>(m_Root.c_str()), 0 };

  FTS *t_FileTree = fts_open(paths, FTS_NOCHDIR, 0);

  if(!t_FileTree)
  {
    return 0;
  }

  FTSENT *t_Node;

  while((t_Node = fts_read(t_FileTree)))
  {
    if(t_Node->fts_level > 0 && t_Node->fts_name[0] == '.')
    {
      fts_set(t_FileTree, t_Node, FTS_SKIP);
    }
    else if(t_Node->fts_info & FTS_F)
    {
      std::string t_Ext = getFileExtension(t_Node->fts_name);

      m_Counters["Size"] += t_Node->fts_statp->st_size;
      m_Counters["File"]++;

      if(t_Ext.size() <= 4)
      {
        File t_File;

        t_File.SetLevel(t_Node->fts_level);
        t_File.SetPath(t_Node->fts_accpath);
        t_File.SetSize(t_Node->fts_statp->st_size);
        t_File.SetExtension(t_Ext);

        m_Files.push_back(t_File);

        if(m_Extensions.find(t_Ext) == m_Extensions.end())
        {
          Log("New extension found: " + t_Ext);
          m_Extensions[t_Ext].m_Count = 1;
          m_Extensions[t_Ext].m_Size  = t_Node->fts_statp->st_size;
        }
        else
        {
          m_Extensions[t_Ext].m_Count++;
          m_Extensions[t_Ext].m_Size += t_Node->fts_statp->st_size;
        }
      }
    }
    else
    {
      Log("Scanning " + std::string(t_Node->fts_name));
    }
  }

  if(fts_close(t_FileTree))
  {
    return 0;
  }

  return 1;
}
//------------------------------------------------------------------------
void MainApp::Dump()
{
  std::ofstream t_F;
  t_F.open("ext_stat.csv");

  if(false == t_F.is_open())
  {
    Log("Could not open ext_stat.csv");
    return;
  }

  std::sort(m_Files.begin(),m_Files.end(),fileCompare);

  std::cout << "*********************************************************************" << std::endl;
  std::cout << "Scanned directory:       " << m_Root << std::endl;
  std::cout << "Number of directories:   " << m_Counters["Dir"] << std::endl;
  std::cout << "Number of files:         " << m_Counters["File"] << std::endl;
  std::cout << "Overall size in mbytes : " << m_Counters["Size"] / (1024.0 * 1024.0) << " (" << m_Counters["Size"] << " bytes)" << std::endl;

  for(ExtensionMap::iterator t_It = m_Extensions.begin(); t_It != m_Extensions.end(); t_It++)
  {
    t_F << t_It->first << "," << t_It->second.m_Count << "," << t_It->second.m_Size << std::endl;
  }

  std::cout << "Largest 10 files:        " << std::endl;

  for(unsigned int t_I = 0; t_I < 10 && t_I < m_Files.size(); t_I++)
  {
    m_Files[t_I].PrintSelf();
  }

  std::cout << "*********************************************************************" << std::endl;

  t_F.close();
  
  t_F.open("hash_codes.csv");
  
  for(unsigned int t_I = 0; t_I < m_Files.size(); t_I++)
  {
    std::ifstream t_MovieFile;
    t_MovieFile.open(m_Files[t_I].GetPath().c_str(),std::ios::in | std::ios::binary | std::ios::ate);
    
    t_F << m_Files[t_I].GetPath() << "," << compute_hash(t_MovieFile) << std::endl;
    
    t_MovieFile.close();
  }
  
  t_F.close();
}

}
