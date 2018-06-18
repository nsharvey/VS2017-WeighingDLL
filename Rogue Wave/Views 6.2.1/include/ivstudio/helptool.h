// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/helptool.h
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
// Declaration of IlvStHelpTool and related classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Helptool_H
#define __IlvSt_Helptool_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

#ifndef __IlvSt_Object_H
#include <ivstudio/object.h>
#endif

class IlvStudio;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStHelpItem
{
public:
    virtual ~IlvStHelpItem();
    virtual IlSymbol* getType() const = 0;
}; // class IlvStHelpItem


// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStHtmlHelpItem
: public IlvStHelpItem {
public:
    IlvStHtmlHelpItem(const char* htmlFile);
    ~IlvStHtmlHelpItem();
    virtual IlSymbol* getType() const;

    const char* getHtmlFile() const;
    void	setHtmlFile(const char*);
    const char*	getCompiledFile() const;
    void	setCompiledFile(const char*);
    const char* getDirectory() const;
    void	setDirectory(const char*);

    static IlSymbol* GetType();

protected:
    char* _htmlFile;
    char* _compiledFile;
    char* _directory;
}; // class IlvStHtmlHelpItem

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStHelpTool
{
public:
    IlvStHelpTool(IlvStudio*);
    virtual ~IlvStHelpTool();
    virtual IlBoolean showHelp(IlvStHelpItem*) = 0;

    IlvStudio* getEditor() const { return _editor; }
protected:
    IlvStudio* _editor;
};

// --------------------------------------------------------------------------
#endif /* __IlvSt_Helptool_H */
