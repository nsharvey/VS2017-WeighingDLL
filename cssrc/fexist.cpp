// fexist.cpp
// ----------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#include "stdafx.h"
#include "fexist.h"


#include <sys/stat.h>



int fexist(const char* fileName) {
  int result;   
#if !__STDC__
  /* Non-ANSI names for compatibility */
  struct stat buf;   
  result = stat( fileName, &buf );
#else
  struct _stat buf;   
  result = _stat( fileName, &buf );
#endif
  return (result == 0);
}



void fcheck(const char* fileName) {
  if (!fexist(fileName)) {
    throw AdxFileExcept(fileName);
  }
}