// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/butpanel.h
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
// Declaration of the IlvButtonPanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Butpanel_H
#define __Ilv_Edit_Butpanel_H

#if !defined(__Ilv_Edit_Inspanel_H)
#include <ilviews/edit/inspanel.h>
#endif

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvButtonPanel
: public IlvInspectorPanel
{
public:
    IlvButtonPanel(IlvManager*, IlvSystemView transientFor = 0);
    // ____________________________________________________________
    virtual void applyChange(IlvGraphic*);
    virtual void initFrom(IlvGraphic*);
protected:
    IlvButtonPanel(IlvManager*,
		   const char*   className,
		   const char*   title,
		   const char*   icon,
		   const char*   data,
		   const char*   filename = 0, // if present, overloads data
		   IlvSystemView transientFor = 0);
};

#endif /*  ! __Ilv_Edit_Butpanel_H */