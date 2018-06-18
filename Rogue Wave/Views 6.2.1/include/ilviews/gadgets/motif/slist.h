// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/slist.h
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
// Declaration of the IlvStringListHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Slist_H
#define __Ilv_Gadgets_Motif_Slist_H

#ifndef __Ilv_Gadgets_Slist_H
# include <ilviews/gadgets/slist.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvStringListMLFHandler
    : public IlvDefaultStringListLFHandler
{
public:
    IlvStringListMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawGadgetItem(const IlvStringList*,
				       const IlvGadgetItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawFullSelection(const IlvStringList*,
					  IlvPort*,
					  const IlvTransformer*,
					  const IlvRect&,
					  const IlvRegion*) const;
    virtual void	computeFocusItemRect(IlvRect& focusRect,
					     const IlvStringList* slist,
					     IlUShort pos,
					     const IlvTransformer* t) const;
    virtual void	drawFocusItem(const IlvStringList* slist,
				      IlvPort* dst,
				      const IlvTransformer*,
				      const IlvRect&,
				      const IlvRegion* clip,
				      IlBoolean selected) const;
    virtual IlvDim	getItemMargin(const IlvStringList*) const;
    virtual IlBoolean	itemBBox(const IlvStringList*,
				 IlUShort pos,
				 IlvRect& rect,
				 const IlvTransformer* t) const;
    virtual IlBoolean	focusFollowSelection() const;
    virtual IlvDim	getItemHeight(const IlvStringList*,
				      IlUShort pos) const;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfslist);

#endif /* !__Ilv_Gadgets_Motif_Slist_H */
