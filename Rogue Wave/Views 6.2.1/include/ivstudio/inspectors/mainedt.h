// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/mainedt.h
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
// Declaration of IlvStIMainEditor and its internal classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Mainedt_H
#define __IlvSt_Inspectors_Mainedt_H

#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif

class IlvStIAccessor;
// --------------------------------------------------------------------------
// IlvStIApplyButtonEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIApplyButtonEditor
    : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIApplyButtonEditor(const char* = 0, IlvStIPropertyAccessor* = 0);

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean initialize() { return IlTrue; }
    virtual IlBoolean apply() { return IlTrue; }
    virtual void       setModified(IlBoolean);

protected:
    virtual const char*	getGraphicClassName() const;
    virtual IlSymbol*	getCallbackType() const;
    virtual IlvGraphic* createGraphic(IlvDisplay*, const char*);
    virtual void onGraphicNotification();
};

// --------------------------------------------------------------------------
// IlvStIResetButtonEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIResetButtonEditor
    : public IlvStIApplyButtonEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIResetButtonEditor(const char* = 0,
			    IlvStIPropertyAccessor* = 0);

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void setModified(IlBoolean);

protected:
    virtual void onGraphicNotification();
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIMainEditor
    : public IlvStIEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIMainEditor(const char* applyGadgetName = 0,
		     const char* resetGadgetName = 0,
		     const char* name = 0,
		     NotificationMode mode = Default);
    virtual ~IlvStIMainEditor();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean initialize();
    virtual IlBoolean apply();
    virtual IlBoolean connectHolder(IlvGraphicHolder*);

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void createEditorObjects(IlvDisplay*, IlArray&, IlArray&);
    // ----------------------------------------------------------------------
    // Mode managment
    virtual IlBoolean isModified() const;
    virtual void       setModified(IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Accessors managment
    virtual void            setAccessor(IlvStIPropertyAccessor*);
    virtual IlvStIAccessor* findAccessor(const char*) const;

    static IlSymbol* _AccessorsEditorName;

    // ----------------------------------------------------------------------
    // Editor managment
    virtual void addEditor(IlvStIEditor*);

protected:
    IlArray _applyEditors;
    IlArray _resetEditors;
    IlvStIApplyButtonEditor* getApplyEditor(IlUInt) const;
    IlvStIResetButtonEditor* getResetEditor(IlUInt) const;
    IlvStIPropertyEditorSet* _accessorsEditor;
};

// --------------------------------------------------------------------------
class IlvButton;

ILVINSPEXPORTEDFUNC(void)
IlvStISetDefaultButton(IlvGraphicHolder*, IlvButton*);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_mainedt)
#endif /* !__IlvSt_Inspectors_Mainedt_H */
