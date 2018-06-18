// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/document.h
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
// Declaration of the IlvStDocument class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Document_H
#define __IlvSt_Document_H

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

class IlvStBuffer;
class IlvStError;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDocument
: public IlvStNamedObject {
public:
    IlvStDocument(IlvStudio* editor, const char* name);
    virtual ~IlvStDocument();
    virtual const char*	getDataFileExtension() const = 0;
    // ____________________________________________________________
    IlvStudio* getEditor() 	const { return _editor; }
    // --- IO ---
    void 		setFileName(const char* name);
    const char* 	makeFilePath(const char* dir, const char* ext) const;
    virtual const char* getDataFile() const;
    static char* 	makeName(const char* path);
    // --- Code properties ---
    const char* 	getFileBaseName() const
        { return (_filename) ? _filename : getName(); }
    void 		setFileBaseName(const char* name)
    	{ IlvStSetString(_filename, name); }
    const char* 	getDataDir() const { return _dataDir; }
    void 		setDataDir(const char* dir)
    	{ IlvStSetString(_dataDir, dir); setModified(IlTrue); }
    // --- Modified flag ---
    virtual IlBoolean  isModified() const;
    virtual void 	setModified(IlBoolean);
protected:
    IlvStudio*		_editor;
    char*               _filename;
    char*		_dataDir;
    IlBoolean		_modified	ILVSTBF;
};

#endif /* __IlvSt_Document_H */
