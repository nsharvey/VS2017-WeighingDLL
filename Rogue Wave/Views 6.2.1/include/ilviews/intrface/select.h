// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/intrface/select.h
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
// Declaration of the IlvSelectionInterface class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Itf_Select_H
#define __Ilv_Itf_Select_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

class ILVVWSEXPORTED IlvGraphic;
class ILVVWSEXPORTED IlvDrawSelection;

class ILVVWSEXPORTED IlvSelectionInterface 
{
public:
    IlvSelectionInterface() {} ;
    virtual ~IlvSelectionInterface(); 
    virtual 
    IlvDrawSelection*	makeSelection(IlvDisplay* display,
				      IlvGraphic* obj) const = 0;

    virtual IlUInt	getMaxSelectionLevel() const;
    static
    IlvDrawSelection*	MakeSelection(IlvDisplay* dpy, IlvGraphic* obj);
    static
    IlvSelectionInterface* GetInterface(const IlvGraphic* obj);
    static IlSymbol*	GetSymbol();
    static IlSymbol*	GetSelectionLevelSymbol();
    static IlUInt	GetSelectionLevel(const IlvGraphic* obj);
    static IlUInt	IncrementSelectionLevel(IlvGraphic* obj);
    static void		ResetSelectionLevel(IlvGraphic* obj);
};

#endif
