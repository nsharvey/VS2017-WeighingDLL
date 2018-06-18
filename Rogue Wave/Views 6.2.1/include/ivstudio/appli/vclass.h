// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/vclass.h
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
// Declaration of IlvStViewsClass
// --------------------------------------------------------------------------
#ifndef __IlvSt_Vclass_H
#define __IlvSt_Vclass_H

#if !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif

class ILVSTAPPLICLASS IlvStStringItem
{
public:
  IlvStStringItem(const char* str,IlvStStringItem* next);

  IlvStStringItem* getNext() const;
  const IlString& getValue() const;

protected:
  IlvStStringItem* _next;
  IlString _value;
};

class ILVSTAPPLICLASS IlvStStringList 
{
public:
  IlvStStringList();
  ~IlvStStringList();

  IlBoolean insert(const char* str);
  IlBoolean has(const char* str) const;
  void removeAll();

  IlUInt getCount() const;
  const char* get(IlUInt) const;

protected:
  IlvStStringItem* _items;
  IlUInt _count;
};

class IlvStLibraryInfo;

class ILVSTAPPLICLASS IlvStGenerationInfo
{
public:
  ~IlvStGenerationInfo();

  static IlvStGenerationInfo& GetInstance();
  // --- Register ---
  static void RegisterLibraryInfo(const char* lib,
				  const char* dep,const char* path);
  static void RegisterLibraryIncludePath(const char* lib,const char* path);
  static void RegisterLibraryCCFlags(const char* lib,const char* flag);
  static void RegisterLibraryPcLdFlags(const char* lib,const char* flag);
  static void RegisterLibraryIncludeDataFile(const char* lib,const char* txt);

  // --- Returns information ---
  static const char* GetLibraryDependencies(const char* lib);
  static const char* GetLibraryPath(const char* lib);
  static const char* GetLibraryIncludePath(const char* lib);
  static const char* GetLibraryCCFlags(const char* lib);
  static const char* GetLibraryPcLdFlags(const char* lib);
  static const char* GetLibraryIncludeDataFile(const char* lib);
protected:
  IlvStGenerationInfo();

  IlvStLibraryInfo* getLibraryInfo(const char* lib) const;

  IlvStLibraryInfo* _libsInfo;
};

#define IlvStRegisterLibraryInfo(lib,dep,path) \
  IlvStGenerationInfo::RegisterLibraryInfo(lib,dep,path)

#define IlvStRegisterLibraryIncludePath(lib,path) \
  IlvStGenerationInfo::RegisterLibraryIncludePath(lib,path)

#define IlvStRegisterLibraryCCFlags(lib,flags) \
  IlvStGenerationInfo::RegisterLibraryCCFlags(lib,flags)

#define IlvStRegisterLibraryPcLdFlags(lib,flags) \
  IlvStGenerationInfo::RegisterLibraryPcLdFlags(lib,flags)

#define IlvStRegisterLibraryIncludeDataFile(lib,txt) \
  IlvStGenerationInfo::RegisterLibraryIncludeDataFile(lib,txt)

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStViewsInteractor
: public IlvStPropertySet {
public:
    IlvStViewsInteractor(const char* name = 0);
    ~IlvStViewsInteractor();

    void setHeaderFile(const char* file) 
	{ setPropertyString(_S_headerFile, file); }
    const char* getHeaderFile() const
	{ return getPropertyString(_S_headerFile); }

    virtual void addedToSet(IlvStPropertySet*);
    static int GlobalInit();

    static IlSymbol* _S_ViewsInteractor;
    static IlSymbol* _S_headerFile;
    static IlBoolean _Initialized;
};

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTAPPLICLASS(st_vclass)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt__H */
