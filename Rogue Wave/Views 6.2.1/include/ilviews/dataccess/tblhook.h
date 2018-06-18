// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/tblhook.h
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
// Declaration of the IliTableHook class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Tblhook_H
#define __Ili_Tblhook_H

#ifndef __Ilv_H
#  include <ilviews/ilv.h>
#endif

#ifndef __Ili_Error_H
#  include <ilviews/dataccess/error.h>
#endif

// --------------------------------------------------------------------------
// IliTableHook
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableHook {
public:
  inline IliTableHook ();
  virtual ~IliTableHook ();

  inline IlBoolean isEnabled () const;
  inline void enable ();
  inline void disable ();

   virtual void startOfBatch ();

   virtual void endOfBatch ();


   virtual void tableDeleted ();
   virtual void tableChanged ();

   virtual void columnInserted (IlInt colno);
   virtual void columnChanged (IlInt colno);
   virtual void columnToBeDeleted (IlInt colno);
   virtual void columnDeleted (IlInt colno);
   virtual void columnMoved (IlInt src, IlInt dest);

   virtual void allRowsDeleted();
   virtual void rowsInserted(IlInt fromRow, IlInt toRow);
   virtual void rowInserted (IlInt rowno);
   virtual void rowToBeChanged (IlInt rowno);
   virtual void rowChanged (IlInt rowno);
   virtual void rowToBeDeleted (IlInt rowno);
   virtual void rowDeleted (IlInt rowno);
   virtual void rowMoved (IlInt src, IlInt dest);
   virtual void rowsExchanged (IlInt rowno1, IlInt rowno2);
   virtual void rowsFetched(IlInt fromRow, IlInt toRow);
   virtual void rowFetched (IlInt rowno);

   virtual void columnCellsChanged (IlInt colno);
   virtual void cellChanged (IlInt rowno, IlInt colno);

   virtual void namedPropertyManagerAdded (const char* name);
   virtual void namedPropertyManagerRemoved (const char* name);

   virtual void raiseError (const IliErrorMessage& msg);

   virtual void tableInserted (IlInt tblno);
   virtual void tableToBeDeleted (IlInt tblno);

   virtual void joinInserted (IlInt);
   virtual void joinToBeDeleted (IlInt);

   virtual void conjunctInserted (IlInt, IlBoolean);
   virtual void conjunctToBeDeleted (IlInt, IlBoolean);
   virtual void conjunctDeleted (IlInt, IlBoolean);

   virtual void aliasesChanged ();
   virtual void sqlTextChanged (IlInt colno);
   virtual void columnNameChanged (IlInt colno);
   virtual void columnDisplayWidthChanged (IlInt colno);

   virtual void parametersChanged ();

   virtual void schemaNameChanged();
   virtual void elementTypeNameChanged();

   virtual void tableParentPathChanged(IlInt tblno);

  inline IlBoolean wantsRowEvents() const;
  inline void setWantsRowEvents(IlBoolean);

protected:
  IlBoolean _enabled;
  IlBoolean _wantsRowEvents;
};

// --

inline
IliTableHook::IliTableHook () {
  _enabled = IlTrue;
  _wantsRowEvents = IlTrue;
}

inline IlBoolean
IliTableHook::isEnabled () const {
  return _enabled;
}

inline void
IliTableHook::enable () {
  _enabled = IlTrue;
}

inline void
IliTableHook::disable () {
  _enabled = IlFalse;
}

inline IlBoolean
IliTableHook::wantsRowEvents() const {
  return _wantsRowEvents;
}

inline void
IliTableHook::setWantsRowEvents(IlBoolean f) {
  _wantsRowEvents = f;
}

#endif
