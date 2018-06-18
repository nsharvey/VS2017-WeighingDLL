// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/cluster.h
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
// Definition of the classes IlvvNamedCell
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Cluster_H
#define __Ilv31_Variable_Cluster_H

#if !defined(__Ilv31_Variable_Hash_H)
#include <ilviews/variable/hash.h>
#endif
#if !defined(__Ilv31_Variable_List_H)
#include <ilviews/variable/list.h>
#endif
#if !defined(__Ilv31_Variable_Sheet_H)
#include <ilviews/variable/sheet.h>
#endif
#if !defined(__Ilv31_Variable_Ccell_H)
#include <ilviews/variable/ccell.h>
#endif
#if !defined(__Ilv31_Variable_Cell_H)
#include <ilviews/variable/cell.h>
#endif

#if defined(ILVSTD)
#include <cstring>
#include <fstream>
#include <cassert>
#else  /* !ILVSTD */
#include <string.h>
#include <fstream.h>
#include <assert.h>
#endif /* !ILVSTD */

class IlvVariable;

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvNamedCell
: public IlvvCell
{
public:
    IlvvNamedCell(const char*, IlvvExpr* = 0, IlvVariable* = 0);
    ~IlvvNamedCell();
    // ____________________________________________________________
    IlvVariable* getVariable() const { return _variable; }
    const char* getName() const { return _name; }
    void remove() { IlvvCell::remove(); }
    virtual void notifyUpdated();
    virtual void notifyInCycle();
    virtual void notifyUndefined();
private:
    IlvVariable* _variable;
    char*        _name;
#if defined(__GNUC__)
    IlvvNamedCell(const IlvvNamedCell&);
#endif /* __GNUC__ */
};


// --------------------------------------------------------------------------
class IlvvReconnectableCellRef;
ILVV_LIST_DEF3(IlvvReconnectableCellRefList, IlvvReconnectableCellRef*, IlvvReconnectableCellRef*)
class ILV31VAREXPORTED IlvvCellRefConnection
{
public:
    IlvvCellRefConnection(const char* cellname, IlvvReconnectableCellRef* cr);
    ~IlvvCellRefConnection();
    // ____________________________________________________________
    void add(IlvvReconnectableCellRef* cr){_cell_ref_list.cons(cr);}
    void remove(IlvvReconnectableCellRef* cr){_cell_ref_list.remove(cr);}
    const char* cellName() const { return _cellname; }
    IlvvBoolean empty() const {return _cell_ref_list.link()?IlvvFalse:IlvvTrue;}
    IlvvReconnectableCellRefList &cellRefList(){return _cell_ref_list;}
private:
   // forbidden
   IlvvCellRefConnection(const IlvvCellRefConnection &);
   char* _cellname;
   IlvvReconnectableCellRefList _cell_ref_list;
};

// --------------------------------------------------------------------------
ILVV_HASH_DEF(IlvvCellRefConnectionHashTable, IlvvCellRefConnection*, const char*)
class ILV31VAREXPORTED IlvvReconnectableCellRefHashTable
{
public:
   IlvvReconnectableCellRefHashTable()
    : _hashTable() {}
    // ____________________________________________________________
    void operator<<(IlvvReconnectableCellRef*);
    void remove(IlvvReconnectableCellRef*);
    void suppress(const char*);
    IlvvCellRefConnection* get(const char*);
private:
    IlvvCellRefConnectionHashTable _hashTable;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvReconnectableCellRef
: public IlvvCellRef
{
public:
    IlvvReconnectableCellRef(IlvvPath*, IlvvCell*);
    ~IlvvReconnectableCellRef();
    // ____________________________________________________________
    IlvvPath* path() const {return _path;}
    char* charPath() const {return _charpath;}
    static IlvvReconnectableCellRefHashTable* getTablePointer()
    { return _hash_table; }
    static void resolveCell(IlvvCell &);
private:
    // to forbid it
    IlvvReconnectableCellRef(const IlvvReconnectableCellRef &);
    void removeCell(IlvvCell*);
    IlvvPath* _path;
    // cached path so that hashing is efficient
    char* _charpath;
    static IlvvReconnectableCellRefHashTable& getTable();
    static IlvvReconnectableCellRefHashTable* _hash_table;
};

// --------------------------------------------------------------------------
ILVV_HASH_DEF(IlvvBaseCluster, IlvvNamedCell*, const char*)
typedef ILVV_HASH_DESC(IlvvBaseCluster) IlvvClusterDescriptor;
class IlvvCluster;
ILVV_LIST_DEF3(IlvvClusterList, IlvvCluster*, const char*)
typedef ILVV_LIST_LINK(IlvvClusterList) IlvvClusterLink;

class ILV31VAREXPORTED IlvvClusterContext
{
 public:
   virtual IlvvPath* computePath(IlvvPath*)=0;
   virtual void rmCluster(IlvvCluster*)=0;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvvReconnectableSheet:
public IlvvSheet,
public
#if !defined(IL_SUNCC2_1)
virtual
#endif
IlvvCellContext
{
public:
    IlvvReconnectableSheet(const char* name);
    virtual ~IlvvReconnectableSheet();
    // ____________________________________________________________
    const char* getName() const { return _name; }
protected:
    IlvvCellRef* buildCellRef(IlvvPath*);
    void extraInsert(IlvvNamedCell*);
    void extraRemove(IlvvNamedCell*);
    virtual void alreadyAdded(const char*);
private:
    // forbidden
    IlvvReconnectableSheet(const IlvvReconnectableSheet &);
    char* _name;
};

class ILV31VAREXPORTED IlvvCluster
: public IlvvReconnectableSheet,
  public IlvvBaseCluster,
  public
#if !defined(IL_SUNCC2_1)
  virtual
#endif
          IlvvClusterContext
{
public:
    IlvvCluster(const char* name);
    virtual ~IlvvCluster();
    // ____________________________________________________________
    const IlvvClusterList& sub() const { return _sub; }
    virtual IlvvCluster* buildCluster(const char* name);
    void addCluster(const char* name);
    void removeCluster(const char* name);
    IlvvBoolean inserted() const { return _context ? IlvvTrue : IlvvFalse; }
    void setContext(IlvvClusterContext* c) { _context = c; }
    IlvvClusterContext* getContext() const { return _context; }
    virtual void unknownCluster(const char*);
    void rm() { if (_context) _context->rmCluster(this); }
protected:
    void addCluster(IlvvCluster &);
private:
    void extraInsert(IlvvNamedCell*);
    void extraRemove(IlvvNamedCell*);
    // forbidden
    IlvvCluster(const IlvvCluster &);
    IlvvPath* computePath(IlvvPath*);
    void removeCell(IlvvCell* c)
	{ remove((IlvvNamedCell*)c); }
    void rmCluster(IlvvCluster* o) { _sub.remove(o); }
    IlvvCell* findCell(const IlvvPath*);
    IlvvCluster* getParent() const { return _parent; }
    void	 setParent(IlvvCluster* parent) { _parent = parent; }
    IlvvCluster*	_parent;
    IlvvClusterList	_sub;
    IlvvClusterContext*	_context;
};

#endif
