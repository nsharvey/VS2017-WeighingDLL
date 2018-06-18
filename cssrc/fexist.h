// fexist.h
// --------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#ifndef FEXIST_H
#define FEXIST_H


//
// Test wether a file exists or not
// 2 versions : one returns the result, the other throws an exception
//


class AdxFileExcept {
private:
  const char* _fileName;
public:
  AdxFileExcept(const char* fileName) : _fileName(fileName) {};
  const char* getFileName() const {return _fileName;}
};


//
// does the file exist or not.
// replies 1 if the file exists, 0 if not
//
int fexist(const char* fileName);

//
// throws an exception IlgFileExcept
// if the specified file does not exist
//
void fcheck(const char* fileName);


#endif
