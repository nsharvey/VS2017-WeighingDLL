// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/alignpnl.h
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
// Declaration of the IlvAlignPanel class
// Defined in library ilvedit.
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Alignpnl_H
#define __Ilv_Edit_Alignpnl_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif

class ILVVWSEXPORTED IlvManager;
class ILVGDTEXPORTED IlvMatrix;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvAlignPanel
    : public IlvDialog
{
public:
    IlvAlignPanel(IlvManager*,
		  IlvSystemView transientFor = 0);
    // ____________________________________________________________
    IlvManager* getManager() const { return _manager; }
    void        setManager(IlvManager* mgr) { _manager = mgr; }
protected:
    IlvManager* _manager;
private:
    void makeItem(IlvMatrix* matrix,
		  IlUShort posx,
		  IlUShort posy,
		  unsigned char ILVHUGE* bits);
    void initAlignPanel();
};

#endif /*  ! __Ilv_Edit_Alignpnl_H */
