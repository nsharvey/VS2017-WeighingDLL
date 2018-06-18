// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/button.h
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
// Declaration of the IlvButtonHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Button_H
#define __Ilv_Gadgets_Motif_Button_H

#ifndef __Ilv_Gadgets_Button_H
# include <ilviews/gadgets/button.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvButtonMLFHandler : public IlvDefaultButtonLFHandler
{
public:
    IlvButtonMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawContents(const IlvButton*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawBackground(const IlvButton*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvButton*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawFocus(const IlvButton*,
				  IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	computeFocusRegion(const IlvButton*,
					   IlvRegion&,
					   const IlvTransformer*) const;
    virtual void	invert(const IlvButton*, IlBoolean) const;
    void		drawButtonAsDefault(const IlvButton* button,
					    IlvPort* dst,
					    const IlvTransformer* t,
					    const IlvRegion* clip) const;
    void		computeDefaultButtonRegion(const IlvButton* button,
						   IlvRegion& region,
						   const IlvTransformer*)const;
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfbut);

#endif /* !__Ilv_Gadgets_Motif_Button_H */
