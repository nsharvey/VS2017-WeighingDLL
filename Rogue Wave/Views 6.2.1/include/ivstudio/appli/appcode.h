// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/appcode.h
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
//  Declaration of the IlvStAppCode class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Appcode_H
#define __IlvSt_Appcode_H

#if	 !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif
#if defined(ILVSTD)
#include <iostream>
#else /* !ILVSTD */
#include <iostream.h>
#endif

// --------------------------------------------------------------------------
class IlvStudio;
class IlvStPanelCode;
class IlvStPanelClass;
class IlvStCodeSysInfo;

// --------------------------------------------------------------------------
typedef enum IlvStCodeContext {
    IlvStAppCodeTopLevel,
    IlvStAppCodeBeforeRunning,
    IlvStAppCodeConstructor1,
    IlvStAppCodeConstructor2,
    IlvStAppCodeDestructor,
    IlvStAppCodeMain,
    IlvStAppCodeGenerateMakefile,
    IlvStAppCodeAugmentMakefile
} _IlvStCodeContext;

typedef IlBoolean (* IlvStCodeWriter)(ILVSTDPREF ostream&, IlvStudio*, IlvStCodeContext);

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStAppCode
{
public:
    IlvStAppCode(IlvStudio*);
    virtual ~IlvStAppCode();
    // ---  ---
  ////void 		registerClass(const char* name, const char* hfile);
    void 		registerInteractor(const char*, const char*);
    // ---  ---
    IlBoolean 		generate(IlBoolean incr);
    IlBoolean		generateApplication();
    virtual void 	generateMakeFile(ILVSTDPREF ostream&);
    IlBoolean 		generateMakeFile();
    virtual void 	generateHeaderFile(ILVSTDPREF ostream&);
    virtual void	generateMsvc32MakeFile(ILVSTDPREF ostream&);
    virtual void	generateBc32MakeFile(ILVSTDPREF ostream&);
    virtual void	generateVisualAge3MakeFile(ILVSTDPREF ostream&);
    virtual void	generateOs2bc20MakeFile(ILVSTDPREF ostream&);
    virtual void	generateOs2csetMakeFile(ILVSTDPREF ostream&);
    virtual void	generateOs2vage3MakeFile(ILVSTDPREF ostream&);
    virtual void	generateWinvage3MakeFile(ILVSTDPREF ostream&);
    virtual void	generateUnixMakeFile(ILVSTDPREF ostream&);
    IlBoolean 		generateHeaderFile();
    virtual void 	generateDataFile(ILVSTDPREF ostream&);
    IlBoolean 		generateDataFile();
    IlBoolean 		generateSourceFile();
    virtual void 	generateSourceFile(ILVSTDPREF ostream&);
    IlBoolean		generatePanelClass();
    void		includePanelClassHeaders(ILVSTDPREF ostream& ostm);
    void		definePanelAccessors(ILVSTDPREF ostream& ostm);
    // -- data accessors ---
    IlBoolean 		useMotif() const   { return _useMotif; }
    void 		useMotif(IlBoolean val) { _useMotif = val;  }
    const IlvStStringArray& getUserObjectFiles() const
    	{ return _userObjectFiles; }
    const char* const* 	getUserObjectFiles(IlUShort& count) const {
	count = (IlUShort)_userObjectFiles.getLength();
	return (const char* const*)_userObjectFiles.getArray();
    }
    void 		setUserObjectFiles(const IlvStStringArray& ofiles)
    	{ _userObjectFiles.setStrings(ofiles); }
    const char* 	getDefaultSystemName() const;
    const char* 	getSystemName() const;
    void 		setSystemName(const char* name)
    	{ IlvStSetString(_systemName, name); }
    IlvStCodeSysInfo*	getSysInfo() const;
    void		setSysInfo(IlvStCodeSysInfo* sysinfo);
    IlvStCodeSysInfo*	getSysInfo(const char* name) const;
    void		addSysInfo(IlvStCodeSysInfo* info)
    	{ _sysInfoTable.add(info); }
    void	      	insertInfo(IlvStCodeSysInfo* info)
    	{ _sysInfoTable.insert(0, info); }
    const IlvArray&	getSystemInfoTable() const { return _sysInfoTable; }
    const char*		getLibraries(const IlvStCodeSysInfo*);
    virtual const char* getCommentLine() const;
    IlvStudio*		getEditor() const { return _editor; }
    IlvStPanelCode* 	getPanelCode() const { return _pancode; }
    // --- Utilities ---
    IlBoolean		isValidOutFile(const char* fname) const;
    virtual IlBoolean 	checkBeforeGenerating() const;
    virtual IlBoolean	checkOutFiles() const;
    virtual IlBoolean	checkClassNames() const;
    IlvStCodeWriter	getCodeWriter() const { return _codeWriter; }
    void		setCodeWriter(IlvStCodeWriter coder)
    	{ _codeWriter = coder; }
    IlvStCallbackChecker getCallbackChecker() const;
    void		setCallbackChecker(IlvStCallbackChecker func);

protected:
    virtual void	writeHeaderFileHeader(ILVSTDPREF ostream&);
    virtual void	writeSourceFileHeader(ILVSTDPREF ostream&);
    virtual void	writeMakePanels(ILVSTDPREF ostream&);
    virtual void	generateStateReading(ILVSTDPREF ostream&);
    virtual void 	writeMainFunction(ILVSTDPREF ostream&);
    virtual void	writeUserHeaderFileCode(ILVSTDPREF ostream&);
    virtual void	writeUserSourceFileCode(ILVSTDPREF ostream&);
    virtual void	writeConstructors(ILVSTDPREF ostream&);
    virtual void	writeDestructor(ILVSTDPREF ostream&);
    virtual void	writeBeforeRunning(ILVSTDPREF ostream&);
    void		registerBitmapReaders(ILVSTDPREF ostream&);
    void		includeBitmapReaders(ILVSTDPREF ostream&);

    virtual IlBoolean	generatePanels(IlBoolean incr = IlFalse);
    IlBoolean		makeBuffers();
    void		clearInternalBuffers();
    IlvStBuffer*	getBuffer(const char* name) const;
    void		initSysInfoTable();
    // --- fields ---
    IlvStudio*		_editor;
    IlvArray		_buffers;
    IlvStPanelCode*	_pancode;
    ILVSTDPREF ostream* _ostream;
    IlvStStringArray	_userObjectFiles;
    char* 		_systemName;
    IlvArray		_sysInfoTable;
    IlvStCodeSysInfo*	_sysInfo;
    IlvStCodeWriter	_codeWriter;
    IlBoolean	        _useMotif ILVSTBF;
private:
    void		registerCommands();
    IlvStString		_libraries;
}; // class IlvStAppCode

// --------------------------------------------------------------------------
#endif /* __IlvSt_Appcode_H */
