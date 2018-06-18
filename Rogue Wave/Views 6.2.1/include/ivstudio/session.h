// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/session.h
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
// Declaration of IlvStSession
// --------------------------------------------------------------------------
#ifndef __IlvSt_Session_H
#define __IlvSt_Session_H

#ifndef __IlvSt_Stprop_H
#include <ivstudio/stprop.h>
#endif

#ifndef __Ilv_Base_Pathname_H
#include <ilviews/base/pathname.h>
#endif
#ifndef __Ilv_Base_Array_H
#include <ilviews/base/array.h>
#endif

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDVAR(const char*) IlvNmRecentFileListChanged;

// --------------------------------------------------------------------------
class IlvStRecentFileList;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSession
: public IlvStPropertySet
{
public:
    IlvStSession(IlvStudio* editor);
    ~IlvStSession();

    IlvStError*		readSession(const char* = 0);
    void		updateProperties();
    IlvStError*		saveSession(const char* = 0);

public:
    const IlPathName&	    getFilePath() const { return _filePath; }
    void		    setFilePath(const IlPathName&);
    IlvStRecentFileList&    recentFileList();
    void		    insertRecentFile(const char* fpath);
    void		    removeRecentFile(const char* fpath);
    virtual IlvStProperty*  readProperty(IL_STDPREF istream&,const IlSymbol*);
    IlUInt		    getNumberOfPlugIns() const;
    const char*		    getPlugIn(IlUInt ndx) const;
    IlBoolean		    addPlugIn(const char*);
    IlBoolean		    removePlugIn(const char*);

protected:
    IlvStudio*		    _editor;
    IlPathName		    _filePath;
    IlvStRecentFileList*    _rflist;
}; // class IlvStSession

// --------------------------------------------------------------------------
class IlvStRecentFileList
    : public IlvStPropertySet {
public:
    IlvStRecentFileList();
    ~IlvStRecentFileList();

    IlBoolean	    insertFile(const char* fpath);
    IlBoolean	    removeFile(const char* fpath);
    IlUShort	    getMaxLength() const { return _maxLength; }
    IlUShort	    setMaxLength(IlUShort mxl);
protected:
    IlUShort	    _maxLength;

}; // class IlvStRecentFileList

// --------------------------------------------------------------------------
#endif /* __IlvSt_Session_H */
