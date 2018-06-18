// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/menu.h
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
// Declaration of the IlvPopupMenuHandler classes
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Menu_H
#define __Ilv_Gadgets_Motif_Menu_H

#ifndef __Ilv_Gadgets_Menu_H
# include <ilviews/gadgets/menu.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macros_H
# include <ilviews/gadgets/motif/macros.h>
#endif


// --------------------------------------------------------------------------
class ILVMLOOKEXPORTED IlvPopupMenuMLFHandler
    : public IlvDefaultPopupMenuLFHandler
{
public:
    IlvPopupMenuMLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawContents(const IlvPopupMenu*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*, 
				     IlBoolean drawRelief = IlTrue) const;
    virtual void	drawSelection(const IlvPopupMenu*,
				      IlvPort* port,
				      const IlvRect& rect,
				      const IlvMenuItem* item,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const;
    virtual void	itemBBox(const IlvPopupMenu*,
				 IlUShort,
				 IlvRect&,
				 const IlvTransformer*) const;
    virtual void	getInternalBBox(const IlvPopupMenu*, IlvRect&) const;
    virtual void	sizes(const IlvPopupMenu*, IlvDim&, IlvDim&) const;
    virtual void	getPreferredSize(const IlvPopupMenu*,
					 IlvDim&,
					 IlvDim&) const;
    virtual void	setSelectionCursor(const IlvPopupMenu*, IlvContainer*);
    virtual
    IlvDirection	subMenuShowPoint(IlvPopupMenu*,
					 IlShort ,
					 IlvPoint&) const;
    virtual int		getMapDelay() const;
    virtual int		getUnMapDelay() const;
    virtual IlvDim	getDefaultLabelOffset(const IlvPopupMenu*) const;
};

// --------------------------------------------------------------------------
ILVMLOOKMODULEINIT(mlfmenu);

#endif /* !__Ilv_Gadgets_Motif_Menu_H */
