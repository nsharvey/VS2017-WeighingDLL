// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/rlfggpnl.h
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
// Declaration of the IlvReliefGaugePanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Rlfggpnl_H
#define __Ilv_Edit_Rlfggpnl_H

#if !defined(__Ilv_Edit_Rctggpnl_H)
#include <ilviews/edit/rctggpnl.h>
#endif

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvReliefGaugePanel
: public IlvRectangularGaugePanel
{
public:
    IlvReliefGaugePanel(IlvManager*, IlvSystemView transientFor = 0);
    // ____________________________________________________________
    virtual void applyChange(IlvGraphic*);
    void initFrom(IlvGraphic*);
protected:
    IlvReliefGaugePanel(IlvManager*,
			const char*   className,
			const char*   title,
			const char*   icon,
			const char*   data,
			const char*   filename = 0, // if present, overloads data
			IlvSystemView transientFor = 0);
};

#endif /* !__Ilv_Edit_Rlfggpnl_H */
