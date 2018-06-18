// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/win95/menu.h
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
// Declaration of the IlvPopupMenuW95LFHandler class
// Defined in library ilvw95look
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Win95_Menu_H
#define __Ilv_Gadgets_Win95_Menu_H

#if !defined(__Ilv_Gadgets_Windows_Menu_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/menu.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/menu.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Win95_H)
#  include <ilviews/looks/win95.h>
#endif
#if !defined(__Ilv_Gadgets_Win95_Macros_H)
#  include <ilviews/gadgets/win95/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVW95LOOKEXPORTED IlvPopupMenuW95LFHandler
    : public IlvPopupMenuWLFHandler
{
public:
    IlvPopupMenuW95LFHandler(IlvLookFeelHandler* lfh);

     virtual void	drawBackground(const IlvPopupMenu*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*,
				       IlBoolean drawRelief = IlTrue) const;
    virtual void	drawFrame(const IlvPopupMenu*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*,
				  IlBoolean drawRelief = IlTrue) const;
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
    virtual
    IlvDirection	subMenuShowPoint(IlvPopupMenu*,
					 IlShort ,
					 IlvPoint&) const;
    virtual int		getMapDelay() const;
    virtual int		getUnMapDelay() const;
    virtual void	setMode(IlvPopupMenu*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvPopupMenu*, IlBoolean) const;
    virtual IlBoolean	allowSelectWithMove() const;
    virtual
    IlvDirection	getAcceleratorAlignment() const;
    virtual IlUShort	getHMargin() const;
};

// --------------------------------------------------------------------------
ILVW95LOOKMODULEINIT(w9fmenu);

#endif /* !__Ilv_Gadgets_Win95_Menu_H */
