// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/genprop.h
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
// Declaration of property classes
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Genprop_H)
#define __IlvSt_Inspectors_Genprop_H

#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIProperty
    : public IlvStObject
{
    IlvDeclareInspClassInfo();
public:
    virtual ~IlvStIProperty() {}

    // ----------------------------------------------------------------------
    virtual IlvStIProperty*	copy() const = 0;
    virtual void	clean();

    virtual void	modified();

    virtual void	set(const IlvStIProperty& prop) = 0;
    virtual void	resetFrom(const IlvStIProperty& prop) { set(prop); }

    virtual IlvValue&  getValue(IlvValue& val) const = 0;
    virtual void	setValue(const IlvValue& val) = 0;

    virtual const char*	getString() const = 0;
    virtual void	setString(const char* str) = 0;

    virtual IlAny	getPointer() const { return 0; }
    virtual void	setPointer(IlAny) {}

    // ----------------------------------------------------------------------
    // Lock / unlock mechanism
    virtual void	lock() { ++_nLocks; }
    virtual void	unLock();

protected:
    IlvStIProperty() : _nLocks(0) {}

    IlUInt		_nLocks;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIValueProperty : public IlvStIProperty
{
    IlvDeclareInspClassInfo();
public:
    IlvStIValueProperty(const IlvStValue& value,
			const char* name = IlString::EmptyCString);
    IlvStIValueProperty(const IlvStIValueProperty& src);
    virtual ~IlvStIValueProperty() {}

    // ----------------------------------------------------------------------
    virtual IlvStIProperty*	copy() const
	{ return ILVI_NEW IlvStIValueProperty(*this); }
    virtual void	clean() { _value = (IlInt)0; }
    virtual void	set(const IlvStIProperty&);

    virtual IlvValue&	getValue(IlvValue&) const;
    virtual void	setValue(const IlvValue&);

    virtual const char*	getString() const { return (const char*)_value; }
    virtual void	setString(const char* str) { _value = str; }

    virtual IlAny	getPointer() const { return (IlAny)_value; }
    virtual void	setPointer(IlAny p) { _value = p; }

#ifdef ILVALLOCCHECK
    virtual void	dump(ILVSTDPREF ostream&);
#endif

protected:
    IlvValue		_value;
};

// --------------------------------------------------------------------------
// IlvStIAgregateProperty class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIAgregateProperty
    : public IlvStIProperty
{
    IlvDeclareInspClassInfo();
public:
    IlvStIAgregateProperty();
    IlvStIAgregateProperty(const IlvStIAgregateProperty&);
    virtual ~IlvStIAgregateProperty();

    // ----------------------------------------------------------------------
    virtual IlvStIProperty*	copy() const
	{ return ILVI_NEW IlvStIAgregateProperty(*this); }
    virtual void	clean();
    virtual void	set(const IlvStIProperty&);

    virtual IlvValue&	getValue(IlvValue&) const;
    virtual void	setValue(const IlvValue&);

    virtual const char*	getString() const;
    virtual void	setString(const char*);

    virtual IlAny	getPointer() const;
    virtual void	setPointer(IlAny);

    // ----------------------------------------------------------------------
    // Specific accessors
    IlvStIProperty*	getField(const IlSymbol*);
    void		setField(const IlSymbol*, IlvStIProperty*);

protected:
    IlHashTable		_fields;
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_genprop)
#endif /* !__IlvSt_Inspectors_Genprop_H */
