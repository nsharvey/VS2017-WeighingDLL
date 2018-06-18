// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/windows/menu.h
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
// Declaration of the IlvPopupMenuWLFHandler class
// Defined in library ilvwlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Windows_Menu_H
#define __Ilv_Gadgets_Windows_Menu_H

#if !defined(__Ilv_Gadgets_Menu_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/menu.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/menu.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Windows_H)
#  include <ilviews/looks/windows.h>
#endif
#if !defined(__Ilv_Gadgets_Windows_Macros_H)
#  include <ilviews/gadgets/windows/macros.h>
#endif

// --------------------------------------------------------------------------
class ILVWLOOKEXPORTED IlvPopupMenuWLFHandler
    : public IlvDefaultPopupMenuLFHandler
{
public:
    IlvPopupMenuWLFHandler(IlvLookFeelHandler* lfh);
    ~IlvPopupMenuWLFHandler();

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
    virtual IlvColor*	getBackground(const IlvPopupMenu*)   const;
    virtual void	setMode(IlvPopupMenu*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvPopupMenu*, IlBoolean) const;
    virtual IlvDim	getDefaultLabelOffset(const IlvPopupMenu*) const;
    inline IlvBitmap*	getCheckBitmap() const
			{
			    IL_CONSTCAST(IlvPopupMenuWLFHandler*, this)
				->initBitmaps();
			    return _checkBitmap;
			}
    inline IlvBitmap*	getRadioBitmap() const
			{
			    IL_CONSTCAST(IlvPopupMenuWLFHandler*, this)
				->initBitmaps();
			    return _radioBitmap;
			}
protected:

    IlvBitmap*		_checkBitmap;
    IlvBitmap*		_radioBitmap;

    void		initBitmaps();
};

// --------------------------------------------------------------------------
ILVWLOOKMODULEINIT(wlfmenu);

#endif /* !__Ilv_Gadgets_Windows_Menu_H */
