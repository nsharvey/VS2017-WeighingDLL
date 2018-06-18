// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/celledt.h
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
// Definition of the IlvCellManagerInteractor class and some predefined
// subtypes
// Defined in library ilvgadgt31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Celledt_H
#define __Ilv31_Celledt_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Cellint_H)
#include <ilviews/cellint.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif

class IlvContainer;
// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvCellManagerInteractorEdit
: public IlvCellManagerInteractor {
public:
    IlvCellManagerInteractorEdit(IlvCellManager* cm,
				 IlvView*        view,
				 IlvDirection    option = IlvBadPosition);
    ~IlvCellManagerInteractorEdit();
    // ____________________________________________________________
    virtual void setCell(IlvCell*);
    IlvCell* getCell() const  { return _cell; }
    void setLabel(const char* label);
    void handleEvent(IlvEvent& event);
    virtual void drawGhost();
    virtual void doIt(const char* buffer = 0);
    virtual void abort();
    virtual void changeCellValue(IlvCell*, const char* buffer);
    const char* getLabel() const;
    IlvContainer* getContainer() const { return _window;}
    virtual IlvTextField* createTextField(IlvDisplay*, const IlvPoint&, const char*);
protected:
    IlvDirection  _option;
    IlvCell*      _cell;
    IlvContainer* _window;
    char          _buffer[256];
    void makeWindow(IlvPos,IlvPos,IlvDim,IlvDim);
};

#endif /* !__Ilv31_Celledt_H */
