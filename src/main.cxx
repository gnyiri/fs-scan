/*
 * main.cxx
 *
 *  Created on: 2011.11.06.
 *      Author: gergely.nyiri@gmail.com
 */

#include "MainApp.h"

//------------------------------------------------------------------------
int main(int argc, char** argv)
{
  if(argc < 2)
  {
    fsscan::log("Not enough parameter! Exit");
    return -1;
  }

  fsscan::MainApp l_app(argv[1]);

  l_app.Update();
  l_app.Dump();

  return 0;
}


