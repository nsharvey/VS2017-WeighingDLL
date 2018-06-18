// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/varcell.h
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
// Declaration of the IlvVariableCellManager class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Varcell_H
#define __Ilv31_Varcell_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif

#if !defined(__Ilv31_Celledt_H)
#include <ilviews/celledt.h>
#endif
#if !defined(__Ilv31_Cellio_H)
#include <ilviews/cellio.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif
#if !defined(__Ilv31_Variable_H)
#include <ilviews/variable.h>
#endif

class IlvCellAttribute;

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableCellManager
: public IlvCellManager
{
public:
    IlvVariableCellManager(IlvDisplay* display,
			   IlUShort    nbcol,
			   IlUShort    nbrow,
			   IlUShort    xgrid = 0,
			   IlUShort    ygrid = 0,
			   IlBoolean   useAccelerators = IlTrue);
    ~IlvVariableCellManager();
    // ____________________________________________________________
    IlvParser* getParser() const      { return _parser;   }
    void setParser(IlvParser* parser) { _parser = parser; }

    IlvVariable* connect(IlvCell*, const char* name);
    IlvVariable* connect(IlvCell*, IlvVariable*);
    IlvVariable* getVariable(IlvCell*);
    IlvVariable* getVariable(const char*, IlBoolean createIt = IlTrue);
    IlBoolean   removeVariable(IlvVariable*);

    void disconnect(IlvCell* cell);
    IlvCellAttribute* getAttribute(IlvCell*) const;

    // Save Cells and Variables
    void write(IL_STDPREF ostream& stream) const;
    void read(IL_STDPREF istream& stream);
    void read(const char* filename);

    virtual void remove(IlvCell*,
			IlBoolean destroyIt = IlTrue,
			IlBoolean draw = IlTrue);
    virtual void reevaluate();
protected:
    IlvParser* _parser;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvCellAttribute
: public IlvAttribute {
public:
    IlvCellAttribute(IlvVariableCellManager*, IlvCell* cell);
    ~IlvCellAttribute();
    //---------------------------------------------------------------
    IlvDisplay*     getDisplay() const { return _manager->getDisplay();}
    IlvCellManager* getCellManager() const { return _manager; }
    IlvCell*        getCell() const        { return _cell; }
    void            setCell(IlvCell* cell) { _cell = cell; }
    void            attach(IlvCell* cell)  { _cell = cell; }

    // set and get value
    // Inherited from IlvAttribute
    virtual void notifySet(const IlvvFundamental &value);
    virtual IlFloat getValue();
    const char* getStringValue();
    virtual IlBoolean isaGraphicAttribute();
    virtual const char* className() const;
protected:
    IlvVariableCellManager* _manager;
    IlvCell*                _cell;
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableCellManagerInteractorEdit
: public IlvCellManagerInteractorEdit {
public:
    IlvVariableCellManagerInteractorEdit(IlvCellManager* cm,
					 IlvView*        view,
					 IlvDirection option = IlvBadPosition)
	: IlvCellManagerInteractorEdit(cm, view, option) {}
    // ____________________________________________________________
    virtual void doIt(const char* buffer = 0); // Also sets the variable
    virtual void setCell(IlvCell*); // Also sets the variable
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableCellOutputFile
: public IlvCellOutputFile {
public:
    IlvVariableCellOutputFile(IL_STDPREF ostream& s)
	: IlvCellOutputFile(s) {}
    // ____________________________________________________________
    virtual void save(IlvCellManager* cellmgr,
		      IlUShort fromCol, IlUShort toCol,
		      IlUShort fromRow, IlUShort toRow );
};

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvVariableCellInputFile
: public IlvCellInputFile {
public:
    IlvVariableCellInputFile(ILVSTDPREF istream& s)
	: IlvCellInputFile(s) {}
    // ____________________________________________________________
    virtual void read(IlvCellManager*,
		      IlUShort colOrig = 0,
		      IlUShort rowOrig = 0);
    void readVariable(IlvVariableCellManager* varmgr,IlvDim col,IlvDim row);
};

#endif /* __Ilv31_Varcell_H */
