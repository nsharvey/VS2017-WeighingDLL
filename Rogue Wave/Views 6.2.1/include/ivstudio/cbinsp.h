// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/cbinsp.h
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
// Declaration of IlvStCallbackInspector
// --------------------------------------------------------------------------
#ifndef __IlvSt_Cbinsp_H
#define __IlvSt_Cbinsp_H

#ifndef __IlvSt_Panel_H
#include <ivstudio/panel.h>
#endif

// --------------------------------------------------------------------------
class IlvStSheet;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCallbackInspector
: public IlvStPanelHandler {
public:
    IlvStCallbackInspector(IlvStudio*);
    virtual void	connect();
    virtual IlBoolean  resetBeforeShowing() const;
    virtual void	doApply();
    virtual void	doReset();
    void		cleanUp();

    IlvStSheet*		getSheet() const { return _sheet; }
protected:
    void		setUpSheet();

    IlvStSheet*		_sheet;
}; // class IlvStCallbackInspector

// --------------------------------------------------------------------------
#endif /* __IlvSt_Cbinsp_H */
