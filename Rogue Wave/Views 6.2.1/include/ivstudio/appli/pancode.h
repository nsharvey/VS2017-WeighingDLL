// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/pancode.h
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Declaration of IlvStPanelCode class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Pancode_H
#define __IlvSt_Pancode_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

#include <ivstudio/appli/vclass.h>

// --------------------------------------------------------------------------
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmBeforeGeneratingPanelClass;
extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmAfterGeneratingPanelClass;

// --------------------------------------------------------------------------
class IlvStudio;
class IlvStPanelClass;
class IlvManager;
class IlvGraphic;
class IlvStPanelCode;

typedef void (* IlvStConstructorsWriter)(IlvStPanelCode*, IlAny);

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStPanelCode
{
public:
  IlvStPanelCode(IlvStudio*);
  virtual ~IlvStPanelCode();
  // ____________________________________________________________
  IlvStudio* 		getEditor() const { return _editor; }
  IlvStPanelClass*	getPanelClass() const { return _pclass; }
  IlvStBuffer*	getBuffer()     const { return _buffer; }
  IlvStStringList& getUsedHeaderFiles()  { return _usedHeaderFiles; }
  IlvHashTable& 	getUsedCallbacks()    { return _usedCallbacks; }
  ILVSTDPREF ostream&		getOStream()	      { return *_ostream; }
  const char*		getBaseClass() const;
  void 		registerInteractor(const char*, const char*);
  virtual void 	explore(IlvGraphic*);
  virtual void 	writeIncludeFile(const char* hfile) const;
  virtual void 	writeCallbackBody(IlSymbol* callback);
  virtual void 	writeCallbackMethod(IlSymbol* callback);
  virtual void 	writeData();
  virtual void 	writeNameAccessor(IlvGraphic*);
  virtual void 	generateHeaderFile(ILVSTDPREF ostream&);
  IlBoolean 		generateHeaderFile();
  virtual void 	generateDataFile(ILVSTDPREF ostream&);
  IlBoolean 		generateDataFile();
  virtual void 	generateSourceFile(ILVSTDPREF ostream&);
  IlBoolean 		generateSourceFile();
  IlBoolean 		generate(IlvStPanelClass*,
				 IlvStBuffer*,
				 IlBoolean saveData = IlFalse);
  virtual void	writeConstructors();
  virtual void	writeDefaultConstructors();
  void		writeGadgetContainerConstructors();
  void		writeDialogConstructors();
  void		registerConstructorsWriter(const char* baseClass,
					   IlvStConstructorsWriter);
  IlvStConstructorsWriter getConstructorsWriter(const char* bseCls) const;
  void 		useClass(const char*);
  void 		useInteractor(const char*);
  void 		useCallback(IlSymbol*);
  virtual IlvStError*	generateSubClass(IlvStPanelClass*);

  void          clearUsedLibraries(const char* def = 0);
  const IlvStStringList& getUsedLibraries() const;
  const IlvStStringList& getUsedLibrariesPath() const;
  const IlvStStringList& getUsedIncludePath() const;
  const IlvStStringList& getUsedCCFlags() const;
  const IlvStStringList& getUsedPcLdFlags() const;
  const IlvStStringList& getUsedIncludeDataFiles() const;
  void          computeLibraryInfo();
protected:
  IlBoolean 		checkOutFile(const char* fname) const;
  void insertLibraryFile(const char* file);
  const char* 	findClassHeaderFile(const char* className) const;
  const char* 	findClassLibraryFiles(const char* className) const;
  const char* 	findInteractorHeaderFile(const char* name) const;
  void 		initClasses();
  void 		setUp(IlvStPanelClass*, IlvStBuffer*);
  IlBoolean 	doGenerate(IlBoolean saveData = IlFalse);
  IlvStError*	doGenerateSubClass(const IlvStPanelClass* baseClass);
  IlvStError*	doGenerateSubClassHeader(const IlvStPanelClass*);
  IlvStError*	doGenerateSubClassSource();
  void 		clear();
  ILVSTDPREF ostream& ostrm() const { return *_ostream; }

  IlvStudio* 	        _editor;
  IlvStPanelClass*    _pclass;
  IlvStBuffer*	_buffer;
  IlvManager*		_manager;
  IlvStStringList	_usedHeaderFiles;
  IlvStStringList	_usedLibraryFiles;
  IlvStStringList	_usedLibraryPath;
  IlvStStringList	_usedIncludePath;
  IlvStStringList	_usedCCFlags;
  IlvStStringList       _usedPcLdFlags;
  IlvStStringList       _usedIncludeDataFiles;
  IlvHashTable        _usedCallbacks;
  IlAList		_constructorsWriters;
  ILVSTDPREF ostream* _ostream;
}; // IlvStPanelCode

// --------------------------------------------------------------------------
#endif /* __Ilv_Pancode_H */


