// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/filesel.h
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
// Declaration of the IlvFileSelectorFieldHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Filesel_H
#define __Ilv_Gadgets_Motif_Filesel_H

#ifndef __Ilv_Gadgets_Fbrowser_H
# include <ilviews/gadgets/fbrowser.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvFileSelectorFieldMLFHandler
: public IlvFileSelectorFieldLFHandler
{
public:
    IlvFileSelectorFieldMLFHandler(IlvLookFeelHandler*);
    // ____________________________________________________________
    virtual void drawSeparation(const IlvFileSelectorField*,
				IlvPort*,
				const IlvRegion*,
				const IlvRect&,
				IlvPalette*) const;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlffsel);

#endif /* !__Ilv_Gadgets_Motif_Filesel_H */
