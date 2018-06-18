// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/propedt.h
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
// Declaration of generic editor classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_PropEdt_H
#define __IlvSt_PropEdt_H

// --------------------------------------------------------------------------
// Includes

#if !defined(__IlvSt_Edtlist_H)
#include <ivstudio/inspectors/edtlist.h>
#endif

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

class IlvStPropertySet;
// --------------------------------------------------------------------------
// IlvStPropertySetEditor class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStPropertySetEditor : public IlvIPropertyListEditor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStPropertySetEditor(IlvIPropertyAccessor* accessor = 0,
			   const char* = 0,
			   NotificationMode = IlvIAbstractEditor::AsOwner);
    ~IlvStPropertySetEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();

protected:
    IlvIPropertyAccessor* _accessor;
    virtual void updateProperties();

    virtual IlUInt getIndex(const IlvIProperty* property)const;
    virtual void deleteProperty(IlvIProperty* prop);
    virtual void addProperty(IlvIProperty* prop, IlUInt index);

    IlvStPropertySet* getPropertySet()const;
};

// --------------------------------------------------------------------------
// IlvStRepeatablePropertyEditor class
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStRepeatablePropertyEditor
: public IlvStPropertySetEditor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStRepeatablePropertyEditor(IlvIPropertyAccessor* accessor = 0,
				  const char* name = 0,
				  IlvIAbstractEditor::NotificationMode mode =
					    IlvIAbstractEditor::AsOwner);
    ~IlvStRepeatablePropertyEditor();

protected:
    virtual void updateProperties();
};

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(propedt)
#endif // IlvDECLAREINITCLASS
// --------------------------------------------------------------------------
#endif // __IlvSt_PropEdt_H
