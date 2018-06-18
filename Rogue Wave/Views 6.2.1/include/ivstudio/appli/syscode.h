// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/syscode.h
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
//  Declaration of the IlvStCodeSysInfo class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Syscode_H
#define __IlvSt_Syscode_H

#ifndef __Ilv_Base_Iostream_H
#include <ilviews/base/iostream.h>
#endif

#if !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStCodeSysInfo
: public IlvStPropertySet {
public:
    IlvStCodeSysInfo(const char* name = NULL,
		     const char* compiler = NULL,
		     IlBoolean motif = IlFalse);
    IlvStCodeSysInfo(ILVSTDPREF istream&);
    virtual ~IlvStCodeSysInfo();

    virtual void addedToSet(IlvStPropertySet*);

    // ____________________________________________________________
    // Accessors
    const char* getSystemName() const;
    void	setSystemName(const char* name)
	{ setPropertyString(_S_sysName, name); }

    const char* getLibDir() const;
    void	setLibDir(const char* str)
	{ setPropertyString(_S_libDir, str); }

    const char* getCompiler() const
	{ return getPropertyString(_S_compiler); }
    void	setCompiler(const char* str)
	{ setPropertyString(_S_compiler, str); }

    const char* getCompilerOptions() const;
    void	setCompilerOptions(const char* str)
	{ setPropertyString(_S_compilerOptions, str); }

    const char* getLinker() const;
    void 	setLinker(const char* str)
	{ setPropertyString(_S_linker, str); }

    const char*	getLinkerOptions() const;
    void 	setLinkerOptions(const char* str)
    	{ setPropertyString(_S_linkerOptions, str); }

    const char* getLibraries() const
	{ return getPropertyString(_S_libraries); }
    void	setLibraries(const char* str)
    	{ setPropertyString(_S_libraries, str); }

    const char* getJvScriptLibraries() const
	{ return getPropertyString(_S_JvScriptLibraries); }
    void	setJvScriptLibraries(const char* libs)
	{ setPropertyString(_S_JvScriptLibraries, libs); }

    const char* getMotifLibraries() const;

    const char*	getSysLibs() const;
    void	setSysLibs(const char* str)
    	{ setPropertyString(_S_syslibs, str); }


    const char* getSourceFileExtension() const
	{ return getPropertyString(_S_srcFileExtension); }
    void setSourceFileExtension(const char* str)
    	{ if (*str == '.') str++; setPropertyString(_S_srcFileExtension, str); }

    // ____________________________________________________________
    // Reading / writing
    virtual IlBoolean read(ILVSTDPREF istream&);
    virtual void writeValue(ILVSTDPREF ostream& ostm) const;

    // ____________________________________________________________
    // Static symbol accessors
    static const IlSymbol* SystemInfoSymbol() { return _S_systemInfo; }
    static const IlSymbol* SysNameSymbol() { return _S_sysName; }
    static const IlSymbol* LibDirSymbol() { return _S_libDir; }
    static const IlSymbol* CompilerSymbol() { return _S_compiler; }
    static const IlSymbol* CompilerOptionsSymbol() { return _S_compilerOptions; }
    static const IlSymbol* LinkerSymbol() { return _S_linker; }
    static const IlSymbol* LinkerOptionsSymbol() { return _S_linkerOptions; }
    static const IlSymbol* LibrariesSymbol() { return _S_libraries; }
    static const IlSymbol* MotifLibrariesSymbol() { return _S_motifLibraries; }
    static const IlSymbol* SysLibSymbol() { return _S_syslibs; }
    static const IlSymbol* SrcFileExtensionSymbol() { return _S_srcFileExtension; }
    static const IlSymbol* JvScriptLibrariesSymbol() { return _S_JvScriptLibraries; }
    static int GlobalInit();
    void	initialize();

protected:
    // static symbol
    static IlSymbol*	_S_systemInfo;
    static IlSymbol*	_S_sysName;
    static IlSymbol*	_S_libDir;
    static IlSymbol*	_S_compiler;
    static IlSymbol*	_S_compilerOptions;
    static IlSymbol*	_S_linker;
    static IlSymbol*	_S_linkerOptions;
    static IlSymbol*	_S_libraries;
    static IlSymbol*	_S_motifLibraries;
    static IlSymbol*	_S_syslibs;
    static IlSymbol* 	_S_srcFileExtension;
    static IlSymbol* 	_S_JvScriptLibraries;

protected:

    static IlBoolean _Initialized;
}; // class IlvStCodeSysInfo

// --------------------------------------------------------------------------
// IlvStCodeSysInfo inlines

inline const char*
IlvStCodeSysInfo::getSystemName() const
{
    return (getPropertyString(_S_sysName)) ?
		getPropertyString(_S_sysName) : getName();
}
// --------------------------------------------------------------------------
inline const char*
IlvStCodeSysInfo::getLibDir() const
{
    return (getPropertyString(_S_libDir)) ?
		getPropertyString(_S_libDir) : getName();
}
// --------------------------------------------------------------------------
inline const char*
IlvStCodeSysInfo::getCompilerOptions() const
{
    return getPropertyString(_S_compilerOptions) ?
		getPropertyString(_S_compilerOptions) : "";
}
// --------------------------------------------------------------------------
inline const char*
IlvStCodeSysInfo::getLinker() const
{
    return getPropertyString(_S_linker) ?
		getPropertyString(_S_linker) : getCompiler();
}
// --------------------------------------------------------------------------
inline const char*
IlvStCodeSysInfo::getLinkerOptions() const
{
    return getPropertyString(_S_linkerOptions) ?
		getPropertyString(_S_linkerOptions) : "";
}
// --------------------------------------------------------------------------
inline const char*
IlvStCodeSysInfo::getSysLibs() const
{
    return getPropertyString(_S_syslibs) ?
		getPropertyString(_S_syslibs) : "";
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTAPPLICLASS(st_syscode)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Syscode_H */




