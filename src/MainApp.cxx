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

    char* paths[] = { const_cast<char*>(m_Root.c_str()), 0 };

    FTS* l_file_tree = fts_open(paths, FTS_NOCHDIR, 0);

    if(!l_file_tree)
    {
      return 0;
    }

    FTSENT* l_node = 0;

    while((l_node = fts_read(l_file_tree)))
    {
      if(l_node->fts_level > 0 && l_node->fts_name[0] == '.')
      {
        fts_set(l_file_tree, l_node, FTS_SKIP);
      }
      else if(l_node->fts_info & FTS_F)
      {
        std::string l_extension = getFileExtension(l_node->fts_name);

        m_Counters["Size"] += l_node->fts_statp->st_size;
        m_Counters["File"]++;

        if(l_extension.size() <= 4)
        {
          File l_file;

          l_file.SetLevel(l_node->fts_level);
          l_file.SetPath(l_node->fts_accpath);
          l_file.SetSize(l_node->fts_statp->st_size);
          l_file.SetExtension(l_extension);

          m_Files.push_back(l_file);

          if(m_Extensions.find(l_extension) == m_Extensions.end())
          {
            Log("New extension found: " + l_extension);
            m_Extensions[l_extension].m_Count = 1;
            m_Extensions[l_extension].m_Size  = l_node->fts_statp->st_size;
          }
          else
          {
            m_Extensions[l_extension].m_Count++;
            m_Extensions[l_extension].m_Size += l_node->fts_statp->st_size;
          }
        }
      }
      else
      {
        Log("Scanning " + std::string(l_node->fts_name));
      }
    }

    if(fts_close(l_file_tree))
    {
      return 0;
    }

    return 1;
  }
//------------------------------------------------------------------------
  void MainApp::Dump()
  {
    std::ofstream l_file;
    l_file.open("ext_stat.csv");

    if(false == l_file.is_open())
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

    for(ExtensionMap::iterator l_it = m_Extensions.begin(); l_it != m_Extensions.end(); l_it++)
    {
      l_file << l_it->first << "," << l_it->second.m_Count << "," << l_it->second.m_Size << std::endl;
    }

    std::cout << "Largest 10 files:        " << std::endl;

    for(unsigned int l_i = 0; l_i < 10 && l_i < m_Files.size(); l_i++)
    {
      m_Files[l_i].PrintSelf();
    }

    std::cout << "*********************************************************************" << std::endl;

    l_file.close();

    l_file.open("hash_codes.csv");

    for(unsigned int l_i = 0; l_i < m_Files.size(); l_i++)
    {
      std::ifstream l_movie_file;
      l_movie_file.open(m_Files[l_i].GetPath().c_str(),std::ios::in | std::ios::binary | std::ios::ate);

      l_file << m_Files[l_i].GetPath() << "," << compute_hash(l_movie_file) << std::endl;

      l_movie_file.close();
    }

    l_file.close();
  }

}
