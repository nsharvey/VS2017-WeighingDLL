// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/sclist.h
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
// Declaration of the IlvScrolledStringList class
// Defined in library ilv31gadgt
// --------------------------------------------------------------------------
#ifndef __Ilv31_Sclist_H
#define __Ilv31_Sclist_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif

// --------------------------------------------------------------------------
class ILV31GDTEXPORTED IlvScrolledStringList
: public IlvStringList {
    friend class IlvScrolledComboBox;
public:
    IlvScrolledStringList(IlvDisplay*     display,
			  const IlvPoint& point,
			  const char* const* labels = 0,
			  IlUShort     count       = 0,
			  IlUShort     thickness= IlvDefaultGadgetThickness,
			  IlvPalette*   palette     = 0);
    IlvScrolledStringList(IlvDisplay*   display,
			  const IlvRect& rect,
			  const char* const* labels = 0,
			  IlUShort    count        = 0,
			  IlUShort    thickness = IlvDefaultGadgetThickness,
			  IlvPalette*  palette      = 0);
    ~IlvScrolledStringList();
    // ____________________________________________________________
    void adjustScrollbar() { adjustScrollBars(); } // 2.1 compat.
    virtual const char* getDefaultInteractor() const;

    // event handling methods
    virtual IlBoolean handleEvent(IlvEvent& event);
    static IlvScrolledStringList* CurrentStringList() { return _cStringList; }
    static void CurrentStringList(IlvScrolledStringList* cStringList)
	{ _cStringList = cStringList; }
    void setInList(IlBoolean f);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvScrolledStringList);
protected:
    // Interactor state
    IlUShort     _state;
    // event handling methods
    void iCallScrollBarChanged(IlvScrollBar* sbar, IlvDirection which);
    static IlvScrolledStringList* _cStringList;
};

ILV31GDTMODULEINIT(sclist);
#endif /* !__Ilv31_Sclist_H */
