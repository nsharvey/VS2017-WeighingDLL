// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/foliotbl.h
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
// How to create a custom IliTable object
// --------------------------------------------------------------------------
#ifndef __Sample_Foliotbl__H__
#define __Sample_Foliotbl__H__

#ifndef __Ili_Table_H
#  include <ilviews/dataccess/table.h>
#endif

enum InstrumentColumn {
  NameColumn = 0,
  BuyColumn,
  QuantityColumn,
  PriceColumn,
  ProfitsColumn,
  ColumnsCount
};

// --------------------------------------------------------------------------
// Instrument
// --------------------------------------------------------------------------
class Instrument
{
public:
  Instrument();
  Instrument(const Instrument &);
  Instrument(const char*, IlvDouble,IlvInt, IlvDouble);
  void operator=(const Instrument &);
  IlvInt operator!=(const Instrument &); 
  IlvInt operator==(const Instrument &); 
  const char* getName();
  IlvDouble   getBuy();
  IlvDouble   getPrice();
  IlvDouble   getProfits();
  IlvInt      getQuantity();
  void setName(const char*);
  void setBuy(IlvDouble);
  void setPrice(IlvDouble);
  void setQuantity(IlvInt);
  void computeProfits();
private:
  IliString _name;
  IlvDouble   _buy;
  IlvInt      _quantity;
  IlvDouble   _price;
  IlvDouble   _profits;
};

// --------------------------------------------------------------------------
// FolioTable
// --------------------------------------------------------------------------
class FolioTable
  : public IliTable 
{
public:
  FolioTable (IlvDisplay* dpy);
  FolioTable (IlvDisplay*, const Instrument* const* emps, 
	      IlvInt count, IlvBoolean copy = IlvTrue);
  FolioTable (const FolioTable&);
  FolioTable (IlvDisplay*,IL_STDPREF istream&);
  virtual ~FolioTable ();
  
  IliDeclareDTypeInfo(FolioTable);
  virtual void write (IL_STDPREF ostream&) const;
  int operator == (const FolioTable&) const;

  // -- IliTable interface
  
  virtual IlvInt getRowsCount () const { return _instrumentsCount; }  
  virtual IlvBoolean getValue (IlvInt rowno, 
			       IlvInt colno, 
			       IliValue& val) const;
  virtual void clearRows ();
  virtual IlvBoolean updateRow (IlvInt, IliTableBuffer*);
  virtual IlvBoolean insertRow (IlvInt, IliTableBuffer*);
  virtual IlvBoolean deleteRow (IlvInt);
  virtual IlvBoolean moveRow (IlvInt, IlvInt);
  virtual IlvBoolean allowRowMove () const { return IlvTrue; }

  // -- Custom interface
    
  const Instrument* const* getInstruments (IlvInt& count);
  void setInstruments (const Instrument* const *emps, 
		       IlvInt count, 
		       IlvBoolean copy = IlvTrue);

  const Instrument* getInstrument(IlvInt rowno);
  IlvBoolean setInstrument(IlvInt rowno, const Instrument* emp);
  IlvBoolean insertInstrument(IlvInt rowno,
			      const Instrument* emp,
			      IlvBoolean copy = IlvTrue);
  IlvBoolean deleteInstrument(IlvInt rowno);
  IlvBoolean appendInstrument(const Instrument* emp,
			      IlvBoolean copy = IlvTrue);

  IlvInt getInstrumentIndex (const Instrument*, IlvInt from = 0);
    
protected:
  Instrument** _instruments;
  IlvInt _instrumentsCount;

  void   defineSchema();
};

// --

IliDeclareTypeInit(FolioTable);

#endif
