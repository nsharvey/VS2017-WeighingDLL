// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/propacc.h
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
// Declaration of IlvStIPropertyAccessor classes
// --------------------------------------------------------------------------
#if !defined(__IlvSt_PropAcc_H)
#define __IlvSt_PropAcc_H

// --------------------------------------------------------------------------
// Includes
#if !defined(__IlvSt_Genacces_H)
#include <ivstudio/inspectors/genacces.h>
#endif

#if !defined(__Ilv_Object_H)
#include <ivstudio/object.h>
#endif

#if !defined(__Ilv_Stprop_H)
#include <ivstudio/stprop.h>
#endif

#if !defined(__IlvSt_Listacc_H)
#include <ivstudio/inspectors/listacc.h>
#endif

class IlvStProperty;
class IlvStPropertySet;

#ifdef ILVSTDEBUG
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#endif

// --------------------------------------------------------------------------
// IlvStIStudioProperty
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStIStudioProperty :
public IlvStIProperty
{
    IlvDeclareInspClassInfo();
public:
    IlvStIStudioProperty(const IlvStIStudioProperty& prop);
    IlvStIStudioProperty(IlvStProperty* prop = 0,
		       IlBoolean bDelete = IlFalse);
    virtual ~IlvStIStudioProperty();
    virtual IlvStIProperty* copy()const;

    virtual void       clean();
    virtual void       modified();
    virtual void       set(const IlvStIProperty& src);
    virtual void       resetFrom(const IlvStIProperty& prop);

    virtual void       setValue(const IlvValue& value);
    virtual IlvValue&  getValue(IlvValue& value)const;

    virtual const char* getString()const;
    virtual void        setString(const char* str);

    virtual IlAny      getPointer()const { return (IlAny)_property; }
    virtual void        setPointer(IlAny);

    virtual void lock();
    virtual void unLock();

#ifdef ILVALLOCCHECK
    virtual void dump(ILVSTDPREF ostream&);
#endif // ILVALLOCCHECK
    // ----------------------------------------------------------------------
    // Specific accessors
    IlvStProperty* getStudioProperty()const { return _property; }
    IlvStProperty* detachStudioProperty();
    void setDeleteStProperty(IlBoolean bDelete);

    // ----------------------------------------------------------------------
    // Statics (casting functions)
    static IlvStProperty* GetStudioProperty(IlvStIProperty*);
    static const IlvStProperty* GetStudioProperty(const IlvStIProperty*);
    static IlvStPropertySet* GetStudioPropertySet(IlvStIProperty*);
    static const IlvStPropertySet* GetStudioPropertySet(const IlvStIProperty*);

protected:
    IlvStProperty* _property;
    IlBoolean     _deleteStProperty;
};

// --------------------------------------------------------------------------
// IlvStPropertyOfSetAccessor class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStPropertyOfSetAccessor
: public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStPropertyOfSetAccessor(IlvStIPropertyAccessor* propSetAcc = 0,
			       const char* name = 0,
			       IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			       IlvStIAccessor::BuildMode = IlvStIAccessor::None);
protected:
    IlvStPropertySet* getPropertySet()const;
};

// --------------------------------------------------------------------------
// IlvStPropertySetFieldAccessor
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStPropertySetFieldAccessor
: public IlvStPropertyOfSetAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStPropertySetFieldAccessor(IlvStIPropertyAccessor* setAccessor = 0,
				  const char* fieldProperty = 0,
				  IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			          IlvStIAccessor::BuildMode =
					    IlvStIAccessor::CreateAndCopy);
    ~IlvStPropertySetFieldAccessor();

protected:
    const IlSymbol* _fieldPropertySymb;

    virtual IlvStIProperty* getOriginalValue();
    virtual void	  replaceValue(IlvStIProperty*, IlvStIProperty*);
    virtual IlvStIProperty* createDefaultProperty()const;
};

// --------------------------------------------------------------------------
// IlvStPropertySetIndFieldAccessor
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStPropertySetIndFieldAccessor
: public IlvStPropertyOfSetAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStPropertySetIndFieldAccessor(IlvStIPropertyAccessor* setAccessor = 0,
				 int index = -1,
				 IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			          IlvStIAccessor::BuildMode =
					    IlvStIAccessor::None,
				 const char* name = 0);
    ~IlvStPropertySetIndFieldAccessor();

protected:
    int                         _index;

    virtual IlvStIProperty* getOriginalValue();
    virtual void	  replaceValue(IlvStIProperty*, IlvStIProperty*);
    virtual IlvStIProperty* createDefaultProperty()const;
};

// --------------------------------------------------------------------------
// IlvStPropertyNameAccessor class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStPropertyNameAccessor
: public IlvStPropertyOfSetAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStPropertyNameAccessor(IlvStIPropertyAccessor* accessor = 0,
			      IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			      IlvStIAccessor::BuildMode =
					    IlvStIAccessor::None,
			      const char* name = 0);
    ~IlvStPropertyNameAccessor();

protected:
    virtual IlvStIProperty* getOriginalValue(); // Need to override in most cases
    virtual void          applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStPropertySetAccessor class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStPropertySetAccessor
: public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStPropertySetAccessor(IlvStIPropertyAccessor* accessor = 0,
			     const char* = 0,
			     IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			     IlvStIAccessor::BuildMode =
					    IlvStIAccessor::None);
    ~IlvStPropertySetAccessor();

protected:
    virtual IlvStIProperty** getInitialProperties(IlUInt&);

    virtual void deleteProperty(IlvStIProperty* prop, IlUInt);
    virtual void addProperty(IlvStIProperty*, IlUInt);
    virtual void replaceProperty(IlvStIProperty* original,
				 IlvStIProperty* newProperty, IlUInt);

    IlvStPropertySet* getPropertySet()const;
};

// --------------------------------------------------------------------------
// IlvStRepeatablePropertyAccessor class
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStRepeatablePropertyAccessor
: public IlvStPropertySetAccessor
{
    IlvDeclareInspClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStRepeatablePropertyAccessor(
		    IlvStIPropertyAccessor* accessor = 0,
		    const char* name = 0,
		    IlvStIAccessor::UpdateMode = IlvStIAccessor::Inherited,
		    IlvStIAccessor::BuildMode = IlvStIAccessor::Copy);
    ~IlvStRepeatablePropertyAccessor();

protected:
    virtual IlvStIProperty** getInitialProperties(IlUInt&);
};

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(propacc)
#endif // IlvDECLAREINITCLASS
// --------------------------------------------------------------------------
#endif // __IlvSt_PropAcc_H
