// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tblprop.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliTablePropertyManager class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblprop_H
#define __Ili_Tblprop_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ili_Tblptr_H)
#  include <ilviews/dataccess/tblptr.h>
#endif

class IliTable;
class IliTableProperty;
class IliTablePropertyManager;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliPropertyList
{
public:
    IliPropertyList();
    ~IliPropertyList();

    void tidy();
    void read(IL_STDPREF istream&);
    void write(IL_STDPREF ostream&);

    // -- Manipulation

    void setProperty(const IlvSymbol*, const IliValue&);
    void removeProperty(const IlvSymbol*);
    IlBoolean getProperty(const IlvSymbol*, IliValue&) const;

    // -- Introspection

    IlInt getPropertyCount() const;
    const IlvSymbol* getPropertyNameAt(IlInt) const;

private:
    IlvStringHashTable* _hash;

    void setProperty(IliTableProperty*);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliPropertyListVector
{
public:
    IliPropertyListVector();
    ~IliPropertyListVector();

    void tidy();
    void read(IL_STDPREF istream&);
    void write(IL_STDPREF ostream&);

    // Manipulation
    void setProperty(IlInt, const IlvSymbol*, const IliValue&);
    void removeProperty(IlInt, const IlvSymbol*);
    IlBoolean getProperty(IlInt, const IlvSymbol*, IliValue&) const;

    void removeKey(IlInt);

    // Introspection
    IlInt getKeyCount() const;
    IlInt getKeyAt(IlInt) const;

    IlInt getPropertyCount(IlInt) const;
    const IlvSymbol* getPropertyNameAt(IlInt, IlInt) const;

    typedef void (* IteratorFn) (const IliPropertyListVector*, IlInt, IlAny);
    IL_DEFINEFPTRTOANYCAST(IteratorFn);

    void forEachKey(IteratorFn, IlAny) const;

private:
    IlvHashTable* _hash;

    IliPropertyList* getPropertyList(IlInt, IlBoolean = IlFalse) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliPropertyListMatrix
{
public:
    IliPropertyListMatrix();
    virtual ~IliPropertyListMatrix();

    void tidy();
    void read(IL_STDPREF istream&);
    void write(IL_STDPREF ostream&);

    // Manipulation
    void setProperty(IlInt, IlInt, const IlvSymbol*, const IliValue&);
    void removeProperty(IlInt, IlInt, const IlvSymbol*);
    IlBoolean getProperty(IlInt, IlInt, const IlvSymbol*, IliValue&) const;

    IlBoolean getScopedProperty(IlInt, IlInt,
				const IlvSymbol*, IliValue&) const;

    void removeKey(IlInt);
    void removeKey(IlInt, IlInt);
    void removeKey2(IlInt);

    // Introspection
    IlInt getKeyCount() const;
    IlInt getKeyAt(IlInt) const;

    IlInt getKeyCount(IlInt) const;
    IlInt getKeyAt(IlInt, IlInt) const;

    IlInt getPropertyCount(IlInt, IlInt) const;
    const IlvSymbol* getPropertyNameAt(IlInt, IlInt, IlInt) const;

    typedef void (* IteratorFn) (const IliPropertyListMatrix*, IlInt, IlAny);
    IL_DEFINEFPTRTOANYCAST(IteratorFn);

    typedef void (* Iterator2Fn) (const IliPropertyListMatrix*,
				  IlInt, IlInt, IlAny);
    IL_DEFINEFPTRTOANYCAST(Iterator2Fn);

    void forEachKey(IteratorFn, IlAny) const;
    void forEachKey(IlInt, Iterator2Fn, IlAny) const;

protected:
    virtual void keyGot(IlInt) const;
    virtual void keyLost(IlInt) const;

private:
    IlvHashTable* _hash;

    IliPropertyListVector*
    getPropertyListVector(IlInt, IlBoolean = IlFalse) const;
};

// --------------------------------------------------------------------------
// IliTablePropertyObserver
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTablePropertyObserver
{
public:
    IliTablePropertyObserver() {}
    virtual ~IliTablePropertyObserver();

    virtual void propertySet(IliTablePropertyManager* propMgr,
			     IlInt rowno, IlInt colno,
			     const IlvSymbol* propName);
    virtual void propertyRemoved(IliTablePropertyManager* propMgr,
				 IlInt rowno, IlInt colno,
				 const IlvSymbol* propName);
};

// ----------------------------------------------------------------------
class ILV_INF_EXPORTED IliTablePropertyManager
: public IliRefCounted
{
public:
    IliTablePropertyManager(IliTable* table);
    IliTable* getTable() const;
    inline const char* getName() const
	{ return _name; }

    virtual void tidy() = 0;

    // Introspection

    virtual IlInt getPropertyCount(IlInt rowno, IlInt colno) const = 0;
    virtual const IlvSymbol* getPropertyNameAt(IlInt rowno, IlInt colno,
					       IlInt propIndex) const = 0;
    virtual IlBoolean hasProperty(IlInt rowno, IlInt colno,
				  const IlvSymbol* propName) const;
    virtual IlBoolean hasScopedProperty(IlInt rowno, IlInt colno,
					const IlvSymbol* propName) const;

    // Access
    virtual IlBoolean getProperty(IlInt rowno, IlInt colno,
				  const IlvSymbol* propName,
				  IliValue& propVal) const = 0;
    virtual void setProperty(IlInt rowno, IlInt colno, const IlvSymbol* propName,
			     const IliValue& propVal) = 0;
    virtual void removeProperty(IlInt rowno, IlInt colno,
				const IlvSymbol* propName) = 0;
    virtual IlBoolean getScopedProperty(IlInt rowno, IlInt colno,
					const IlvSymbol* propName,
					IliValue& propVal) const = 0;

    // Persistance
    virtual IlBoolean isPersistent() const = 0;
    virtual void read(IL_STDPREF istream&) = 0;
    virtual void write(IL_STDPREF ostream&) = 0;

    // Observers
    void addObserver(IliTablePropertyObserver* observer);

    void removeObserver(IliTablePropertyObserver* observer);

private:
    IliTablePtr _tablePtr;
    IlvList _observers;

    friend class IliTable;
protected:
    virtual ~IliTablePropertyManager();

    IliString _name;

    virtual void propertySet(IlInt, IlInt, const IlvSymbol*);
    virtual void propertyRemoved(IlInt, IlInt, const IlvSymbol*);
    inline void setName(const char* name)
	{ _name = name; }



    virtual void columnToBeDeleted(IlInt);
    virtual void rowToBeDeleted(IlInt);
};

#endif /* !__Ili_Tblprop_H */
