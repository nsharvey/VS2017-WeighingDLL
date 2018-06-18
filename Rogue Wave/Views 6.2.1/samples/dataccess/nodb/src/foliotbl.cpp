// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/src/foliotbl.cpp
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
#include <ilviews/dataccess/util.h>
#include <ilviews/util/util.h>
#include <foliotbl.h>

IL_STDUSE

// --------------------------------------------------------------------------
// Class Instrument
// --------------------------------------------------------------------------
 
// --------------------------------------------------------------------------
// Default constructor
// -------------------------------------------------------------------------- 
Instrument::Instrument() {
  _name     = "...";
  _buy      = 100.0;
  _quantity = 1;
  _price    = 100.0;
  _profits  = 0.0;
}

// -------------------------------------------------------------------------- 
// Copy constructor
// -------------------------------------------------------------------------- 
Instrument::Instrument(const Instrument &inst) {
  _name     = inst._name;
  _buy      = inst._buy;
  _quantity = inst._quantity;
  _price    = inst._price;
  _profits  = inst._profits;
}
  
// --------------------------------------------------------------------------
// Custom constructor
// -------------------------------------------------------------------------- 
Instrument::Instrument(const char *name, IlvDouble buy,
		       IlvInt quantity, IlvDouble price) {
  _name     = name;
  _buy      = buy;
  _quantity = quantity;
  _price    = price;
  computeProfits();
}

// -------------------------------------------------------------------------- 
// Assignment operator
// -------------------------------------------------------------------------- 
void 
Instrument::operator=(const Instrument &inst) {
  _name     = inst._name;
  _buy      = inst._buy;
  _quantity = inst._quantity;
  _price    = inst._price;
  _profits  = inst._profits;
}

// -------------------------------------------------------------------------- 
// Equality operators
// -------------------------------------------------------------------------- 
IlvInt 
Instrument::operator==(const Instrument &inst)
{
  return (_name == inst._name
	  && _buy == inst._buy
	  && _quantity == inst._quantity
	  && _price == inst._price);
}

// -------------------------------------------------------------------------- 
// Not equality operators
// -------------------------------------------------------------------------- 
IlvInt 
Instrument::operator!=(const Instrument &inst) {
  return ! operator==(inst);
}

// -------------------------------------------------------------------------- 
// Returns the name
// -------------------------------------------------------------------------- 
const char*
Instrument::getName() {
  return (const char*)_name;
}

// -------------------------------------------------------------------------- 
// Returns the quantity
// -------------------------------------------------------------------------- 
IlvInt
Instrument::getQuantity() {
  return _quantity;
}

// -------------------------------------------------------------------------- 
// Returns the buy price
// -------------------------------------------------------------------------- 
IlvDouble
Instrument::getBuy() {
  return _buy;
}
  
// -------------------------------------------------------------------------- 
// Returns the last price
// -------------------------------------------------------------------------- 
IlvDouble
Instrument::getPrice() {
  return _price;
}
  
// -------------------------------------------------------------------------- 
// Returns the profits
// -------------------------------------------------------------------------- 
IlvDouble
Instrument::getProfits() {
  return _profits;
}
  
// -------------------------------------------------------------------------- 
// Sets the name
// -------------------------------------------------------------------------- 
void 
Instrument::setName(const char *name) {
  _name = name;
}
  
// -------------------------------------------------------------------------- 
// Sets the quantity
// -------------------------------------------------------------------------- 
void 
Instrument::setQuantity(IlvInt quantity) { 
  _quantity = quantity; 
}
  
// -------------------------------------------------------------------------- 
// Sets the buy price
// -------------------------------------------------------------------------- 
void 
Instrument::setBuy(IlvDouble buy) { 
  _buy = buy; 
}

// -------------------------------------------------------------------------- 
// Sets the last price
// -------------------------------------------------------------------------- 
void 
Instrument::setPrice(IlvDouble price) { 
  _price = price; 
}

// -------------------------------------------------------------------------- 
// Computes the profits
// -------------------------------------------------------------------------- 
void 
Instrument::computeProfits() { 
  _profits = (_price - _buy) * ((IlvDouble)_quantity); 
}

// --------------------------------------------------------------------------
// Class FolioTable
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
FolioTable::FolioTable (IlvDisplay* dpy) : IliTable(dpy) {
  _instruments = 0;
  _instrumentsCount = 0;
  defineSchema();
}

// --------------------------------------------------------------------------
// Constructor 
// --------------------------------------------------------------------------
FolioTable::FolioTable (IlvDisplay* dpy, const Instrument* const* emp,
			IlvInt count, IlvBoolean copy) 
  : IliTable(dpy) {
  _instrumentsCount = 0;
  _instruments = 0;
  defineSchema();
  setInstruments(emp, count, copy);
}

// --------------------------------------------------------------------------
// Copy constructor
// --------------------------------------------------------------------------
FolioTable::FolioTable (const FolioTable& o) : IliTable(o) {
  _instrumentsCount = 0;
  _instruments = 0;
  setInstruments((const Instrument* const*)o._instruments,
		 o._instrumentsCount, IlvTrue);
}

// --------------------------------------------------------------------------
// Stream based constructor
// --------------------------------------------------------------------------
FolioTable::FolioTable (IlvDisplay* dpy, istream& is):IliTable(dpy, is) {
  const char *name;
  IlvInt     quantity;
  IlvDouble  buy;
  IlvDouble  price;
      
  is >> _instrumentsCount;
  if (_instrumentsCount > 0) {
    _instruments = new Instrument*[_instrumentsCount];
    for (IlvInt i = 0; i < _instrumentsCount; ++i) {
      name = IlvReadString(is);
      is >> buy;
      is >> quantity;
      is >> price;
      _instruments[i] = new Instrument(name, buy, quantity, price);
    }
  }
  else
    _instruments = 0;
}

// --------------------------------------------------------------------------
// Defines the schema of the table
// --------------------------------------------------------------------------
void   
FolioTable::defineSchema() {
  //---- use functions from IliSchema ----

  //---- define columns ----
  insertColumn(NameColumn,     "NAME",     IliStringType);
  insertColumn(BuyColumn,      "BUY",      IliDoubleType);
  insertColumn(QuantityColumn, "QUANTITY", IliIntegerType);
  insertColumn(PriceColumn,    "PRICE",    IliDoubleType);
  insertColumn(ProfitsColumn,  "PROFITS",  IliDoubleType);
  
  //---- format columns ----
  setColumnTitle(NameColumn,     "Name");
  setColumnTitle(BuyColumn,      "Buy");
  setColumnTitle(QuantityColumn, "Quantity");
  setColumnTitle(PriceColumn,    "Last Price");
  setColumnTitle(ProfitsColumn,  "Profits");
    
  setColumnAlignment(NameColumn,     IlvLeft);
  setColumnAlignment(BuyColumn,      IlvRight);
  setColumnAlignment(QuantityColumn, IlvRight);
  setColumnAlignment(PriceColumn,    IlvRight);
  setColumnAlignment(ProfitsColumn,  IlvRight);

  // see the Getting Started Manual, Appendix B

  setColumnFormat(NameColumn,    ">@<"); 
  setColumnFormat(BuyColumn,     "###,##0.00");
  setColumnFormat(PriceColumn,   "###,##0.00");
  setColumnFormat(ProfitsColumn, "###,##0.00");
  
  setColumnNullable(NameColumn, IlvFalse);
  setColumnNullable(BuyColumn, IlvFalse);
  setColumnNullable(PriceColumn, IlvFalse);
  setColumnNullable(QuantityColumn, IlvFalse);
  setColumnNullable(ProfitsColumn, IlvTrue);
  setColumnDefault(ProfitsColumn, "0.00");
  setColumnReadOnly(ProfitsColumn,IlvTrue);
}

// --------------------------------------------------------------------------
// Destructor 
// --------------------------------------------------------------------------
FolioTable::~FolioTable () {
  clearRows();
}
  
// --------------------------------------------------------------------------
// Write method
// --------------------------------------------------------------------------
void
FolioTable::write (ostream& os) const {
  IliTable::write(os);
  os << _instrumentsCount << ' ';
  for (IlvInt i = 0; i < _instrumentsCount; ++i) {
    IlvWriteString(os, _instruments[i]->getName());
    os << ' ';
    os << _instruments[i]->getBuy();
    os << ' ';
    os << _instruments[i]->getQuantity();
    os << ' ';
    os << _instruments[i]->getPrice();
    os << ' ';
  }
}

// --------------------------------------------------------------------------
// Equality
// --------------------------------------------------------------------------
int
FolioTable::operator == (const FolioTable& o) const {
  if (!IliTable::operator == (o))
    return 0;
  if (_instrumentsCount != o._instrumentsCount)
    return 0;
  for (IlvInt i = 0; i < _instrumentsCount; ++i) {
    if (*(_instruments[i]) != *(o._instruments[i]))
      return 0;
  }
  return 1;
}

// --------------------------------------------------------------------------
// Returns a value from a cell of the table
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::getValue (IlvInt rowno, IlvInt colno, 
		     IliValue& val) const {
  if ((rowno >= 0) && (rowno < getRowsCount())
      && (colno >= 0) && (colno < 5))  {
    switch(colno) {
    case NameColumn:
      val.setNull(IliStringType);
      return val.importString(_instruments[rowno]->getName());
    case BuyColumn:
      val.setNull(IliDoubleType);
      return val.importDouble(_instruments[rowno]->getBuy());
    case QuantityColumn:
      val.setNull(IliIntegerType);
      return val.importInteger(_instruments[rowno]->getQuantity());
    case PriceColumn:
      val.setNull(IliDoubleType);
      return val.importDouble(_instruments[rowno]->getPrice());
    case ProfitsColumn:
      val.setNull(IliDoubleType);
      return val.importDouble(_instruments[rowno]->getProfits());
    }
  }
  return IlvFalse;
}

// --------------------------------------------------------------------------
// Deletes all rows from the table
// --------------------------------------------------------------------------
void
FolioTable::clearRows () {
  startOfBatch();
  for (IlvInt i = 0; i < _instrumentsCount; ++i)
    delete _instruments[i];
  if (_instruments)
    delete [] _instruments;
  _instrumentsCount = 0;
  _instruments = 0;
  tableChanged();
  endOfBatch();
}

// --------------------------------------------------------------------------
// Modifies a row
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::updateRow (IlvInt rowno, IliTableBuffer* tblBuf) {
  if (tblBuf->getTable() == this && !isReadOnly() &&
      (rowno >= 0) && (rowno < getRowsCount())) {
    IlvBoolean modified = IlvFalse;
    IlvBoolean computes = IlvFalse;

    rowToBeChanged(rowno);
    
    if (tblBuf->at(NameColumn).isModified()) { 
      _instruments[rowno]->setName(tblBuf->at(NameColumn).asString(0)); 
      modified = IlvTrue;
    }
    if (tblBuf->at(BuyColumn).isModified()){ 
      _instruments[rowno]->setBuy(tblBuf->at(BuyColumn).asDouble());
      computes = IlvTrue;
      modified = IlvTrue;
    }
    if (tblBuf->at(QuantityColumn).isModified()) { 
      _instruments[rowno]->setQuantity(tblBuf->at(QuantityColumn).asInteger()); 
      computes = IlvTrue;
      modified = IlvTrue;
    }
    if (tblBuf->at(PriceColumn).isModified()){ 
      _instruments[rowno]->setPrice(tblBuf->at(PriceColumn).asDouble()); 
      computes = IlvTrue;
      modified = IlvTrue;
    }
    if (computes)
      _instruments[rowno]->computeProfits();
    if (modified)
      rowChanged(rowno);
    return IlvTrue;
  }
  else
    return IlvFalse;
}

// --------------------------------------------------------------------------
// Inserts a row
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::insertRow (IlvInt rowno, IliTableBuffer* tblBuf) {
  if (tblBuf->getTable() == this) {
    Instrument inst(tblBuf->at(NameColumn),
		    tblBuf->at(BuyColumn),
		    tblBuf->at(QuantityColumn),
		    tblBuf->at(PriceColumn));
    return insertInstrument(rowno, &inst, IlvTrue);
  }
  return IlvFalse;
}

// --------------------------------------------------------------------------
// Deletes a row
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::deleteRow (IlvInt rowno) {
  return deleteInstrument(rowno);
}

// --------------------------------------------------------------------------
// Moves a row
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::moveRow (IlvInt from, IlvInt to) {
  if (!isReadOnly() &&
      (from >= 0) && (from < getRowsCount()) &&
      (to >= 0) && (to < getRowsCount())) {
    Instrument* fromEmp = _instruments[from];
    IlvInt i;
    if (from < to)
      for (i = from; i < to; ++i) 
	_instruments[i] = _instruments[i + 1];
    else
      for (i = from; i > to; --i) 
	_instruments[i] = _instruments[i - 1];
    _instruments[to] = fromEmp;
    rowMoved(from, to);
    return IlvTrue;
  }
  return IlvFalse;
}

// --------------------------------------------------------------------------
// Returns all instruments
// --------------------------------------------------------------------------
const Instrument* const*
FolioTable::getInstruments (IlvInt& count) {
  count = _instrumentsCount;
  return (const Instrument* const*)_instruments;
}

// --------------------------------------------------------------------------
// Sets all instruments
// --------------------------------------------------------------------------
void
FolioTable::setInstruments(const Instrument* const* emps,
			   IlvInt count, IlvBoolean copy) {
  if (!isReadOnly()) {
    startOfBatch();
    if (_instrumentsCount > 0)
      clearRows();
    if (count < 0) {
      count = 0;
      emps = 0;
      IlvWarning("FolioTable::setInstruments: negative count");
    }
    if (copy) {
      _instrumentsCount = count;
      _instruments = (_instrumentsCount > 0
		    ? new Instrument* [_instrumentsCount]
		    : 0);
      for (IlvInt i = 0; i < _instrumentsCount; ++i) {
	_instruments[i] = new Instrument(*(emps[i]));
      }      
    }
    else {
      _instruments = (Instrument**)emps; 
      _instrumentsCount = count;
    }
    if (_instrumentsCount == 0)
      _instruments = 0;
    tableChanged();
    endOfBatch();
  }
}

// --------------------------------------------------------------------------
// Returns an instrument
// --------------------------------------------------------------------------
const Instrument*
FolioTable::getInstrument(IlvInt rowno) {
  return ((rowno >= 0) && (rowno < getRowsCount()))? _instruments[rowno] : 0;
}

// --------------------------------------------------------------------------
// Modifies an instrument
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::setInstrument(IlvInt rowno, const Instrument* inst)
{
  if (!isReadOnly() && (rowno >= 0) && (rowno < getRowsCount()) && inst) {
    *_instruments[rowno] = *inst;
    rowChanged(rowno);
    return IlvTrue;
  }
  return IlvFalse;
}

// --------------------------------------------------------------------------
// Inserts an instrument
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::insertInstrument(IlvInt rowno, const Instrument* emp,
			     IlvBoolean copy) {
  if (!isReadOnly() && (rowno >= 0) && (rowno <= _instrumentsCount) && emp) {
    IlvInt i;
    Instrument** newInstruments = new Instrument* [_instrumentsCount + 1];
    for (i = 0; i < rowno; ++i) 
      newInstruments[i] = _instruments[i];
    newInstruments[rowno] = 0;
    for (i = rowno; i < _instrumentsCount; ++i)
      newInstruments[i + 1] = _instruments[i];
    _instrumentsCount++;
    if (_instruments)
      delete [] _instruments;
    _instruments = newInstruments;

    if (copy)
      _instruments[rowno] = new Instrument(*emp);
    else
      _instruments[rowno] = (Instrument*)emp;
    rowInserted(rowno);
    return IlvTrue;
  }
  else {
    return IlvFalse;
  }
}

// --------------------------------------------------------------------------
// Appends an instrument
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::appendInstrument(const Instrument* emp, IlvBoolean copy) {
  return insertInstrument(_instrumentsCount, emp, copy);
}

// --------------------------------------------------------------------------
// Deletes an instrument
// --------------------------------------------------------------------------
IlvBoolean
FolioTable::deleteInstrument (IlvInt rowno) {
  if (!isReadOnly() && (rowno >= 0) && (rowno < getRowsCount())) {
    IlvInt i;
    rowToBeDeleted(rowno);
    Instrument** newInstruments = (_instrumentsCount > 1
			       ? new Instrument* [_instrumentsCount - 1]
			       : 0);
    for (i = 0; i < rowno; ++i) 
      newInstruments[i] = _instruments[i];
    for (i = rowno + 1; i < _instrumentsCount; ++i)
      newInstruments[i - 1] = _instruments[i];
    _instrumentsCount--;
    delete _instruments[rowno];
    delete [] _instruments;
    _instruments = newInstruments;
    rowDeleted(rowno);
    return IlvTrue;  
  }
  return IlvFalse;
}

// --------------------------------------------------------------------------
// Returns the index of an instrument
// --------------------------------------------------------------------------
IlvInt
FolioTable::getInstrumentIndex (const Instrument* inst, IlvInt from) {
  if (inst) {
    from = (from < 0)? 0 : from;
    for (IlvInt rowno = from; rowno < _instrumentsCount; ++rowno) {
      if (*_instruments[rowno] == *inst)
	return rowno;
    }
  }
  return -1;
}

// --------------------------------------------------------------------------
// Class Info
// --------------------------------------------------------------------------
IliClassInfoCodeDisplay(FolioTable);

// --------------------------------------------------------------------------
// Module
// --------------------------------------------------------------------------
#define ILI_FOLIO_EXPORTEDFN(type) type

// --------------------------------------------------------------------------
// AtInit
// --------------------------------------------------------------------------
void IliAtInitModuleFoliotbl() {
IliClassInfoCommonInitialize(FolioTable,IliTable);
}

// --------------------------------------------------------------------------
// AtExit
// --------------------------------------------------------------------------
void IliAtExitModuleFoliotbl() {
}

// --------------------------------------------------------------------------
// Module definition
// --------------------------------------------------------------------------
IliModuleDefinition(FolioTable,Foliotbl)



