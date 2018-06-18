// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: inform30/include/inform/gadgets/dbstrlst.h
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
#ifndef __Ili_Compat_Dbstrlst_H
#define __Ili_Compat_Dbstrlst_H

#include <../inform30/include/inform/macros.h>
#include <ilviews/dataccess/gadgets/dbstrlst.h>

#ifndef __Ilv_Sclist_H
#  include <ilviews/sclist.h>
#endif

#ifndef __Ili_Fielditf_H
#  include <../inform30/include/inform/fielditf.h>
#endif

#ifndef __Ili_Datasrc_H
#  include <../inform30/include/inform/gadgets/datasrc.h>
#endif

// --------------------------------------------------------------------------
// IliDbOldStringList
// --------------------------------------------------------------------------
class ILV_INFORM30_EXPORTED IliDbOldStringList
  : public IlvScrolledStringList,
    public IliFieldItf 
{
public:
  IliDbOldStringList (IlvDisplay*,
		     const IlvRect&,
		     const char* const* labels = 0,
		     IlvUShort count = 0,
		     IlvUShort thickness = IlvDefaultGadgetThickness,
		     IlvPalette* palette = 0);
  ~IliDbOldStringList ();
  
  DeclareTypeInfo();
  DeclareIOConstructors(IliDbOldStringList);

  virtual void setHolder (IlvGadgetHolder*);
  virtual IlvBoolean handleEvent (IlvEvent& event);
  virtual void doIt ();

  // -- implements IliFieldItf

  virtual const IliValue& f_getValue (IlvBoolean internalP = IlvFalse) const;
  virtual IlvBoolean f_setValue (const IliValue&,
				 IlvBoolean internalP = IlvFalse);
  virtual void f_refresh ();  
  virtual IlvBoolean f_isConsistent () const;
  virtual void f_internalToExternal ();
  virtual IlvBoolean f_externalToInternal ();
  virtual IlvBoolean f_isReadOnly () const;
  virtual void f_setReadOnly (IlvBoolean);

  virtual void f_setForeignTable (IliTable*, IlvBoolean owner = IlvFalse);
  virtual void f_setForeignValueColumnName(const char*);
  virtual void f_setForeignDisplayColumnName(const char*);

  virtual void select(IlvUShort);
  virtual void unSelect(IlvUShort);
  virtual void doSelect();
      
  virtual const IlvValueTypeClass* getValueType(const IlvSymbol* name) const;
  virtual IlvBoolean getValueDescriptor(IlvValue& value) const;
  virtual IlvValue&  queryValue(IlvValue& value) const;
  virtual IlvBoolean applyValue(const IlvValue& value);
  static  void GetAccessors(const IlvSymbol* const** accessors,
			    const IlvValueTypeClass* const** types,
			    IlvUInt& count);
  virtual IlvBoolean f_supportsAccessor(IliFieldAccessorTag) const;
  static  IlvBoolean F_supportsAccessor(IliFieldAccessorTag);

protected:
  IliValue _value;
  IlvBoolean _readOnly;
  IliTableHook* _tableHook;
  IlvUInt _batchCount;
  IlvBoolean _refreshRequested;

  IlvBoolean  strListRemoveItem(IlvInt);
  IlvBoolean  strListAppendItem(const char*);
  IlvBoolean  strListInsertItem(IlvInt, const char*);
  IlvBoolean  strListSetItem(IlvInt,const char*);
  const char* strListGetLabel(IlvInt row, IlvInt col = -1);
      
  void init ();
  void startOfBatch ();
  void endOfBatch ();
  IlvInt posInTable (const IliValue&, IlvInt colno) const;
  IlvInt getValueColumn () const;
  IlvInt getDisplayColumn () const;
  void refreshValuesList ();
  friend class IliDbOldStringListHook;
};

IliModuleDECL_exp(ILV_INFORM30_EXPORTED,IliDbOldStringList);

#ifdef ILI_COMPAT_PREFIX
#define IlvSwDbStringList IliDbOldStringList
#endif

#endif
