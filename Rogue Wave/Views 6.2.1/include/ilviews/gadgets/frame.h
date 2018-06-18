// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/frame.h
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
// Declaration of the IlvFrame class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Frame_H
#define __Ilv_Gadgets_Frame_H

#if !defined(__Ilv_Gadgets_Msglabel_H)
#  include <ilviews/gadgets/msglabel.h>
#endif

#define ILVFRAME_FIXED_SPACING 10
class IlvFrame;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvFrameLFHandler
: public IlvObjectLFHandler
{
public:
    IlvFrameLFHandler(IlvLookFeelHandler* lfh);
    // ____________________________________________________________
    virtual void	drawBackground(const IlvFrame* frame,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvFrame* frame,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvFrame* frame,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawGadgetItem(const IlvFrame*,
				       const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer*,
				       const IlvRegion*) const = 0;

    virtual void	setMode(IlvFrame*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvFrame*, IlBoolean) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultFrameLFHandler
: public IlvFrameLFHandler
{
public:
    IlvDefaultFrameLFHandler(IlvLookFeelHandler* lf)
    : IlvFrameLFHandler(lf)
    {}

    virtual void	drawBackground(const IlvFrame*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawGadgetItem(const IlvFrame*,
				       const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer*,
				       const IlvRegion*) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvFrame
: public IlvMessageLabel
{
public:
    IlvFrame(IlvDisplay*	display,
	     const char*	message,
	     const IlvRect&	size,
	     IlUShort		thickness   = 0,
	     IlvPalette*	palette     = 0,
	     IlBoolean		copy        = IlTrue)
    : IlvMessageLabel(display,
		      message,
		      size,
		      IlvLeft,
		      thickness,
		      palette,
		      copy)
    {}

    IlvFrame(IlvDisplay*	display,
	     const IlvPoint&	point,
	     const char*	message,
	     IlUShort		thickness   = 0,
	     IlvPalette*	palette     = 0,
	     IlBoolean		copy        = IlTrue)
    : IlvMessageLabel(display,
		      point,
		      message,
		      IlvLeft,
		      thickness,
		      palette,
		      copy)
    {}

    // ____________________________________________________________
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);

    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort*,
				       const IlvRect&,
				       const IlvTransformer* = 0,
				       const IlvRegion* = 0) const;
    IlBoolean		contains(const IlvPoint&,
				 const IlvPoint&,
				 const IlvTransformer*) const;

    DeclareLazyTypeInfo();

    IlvFrame(const IlvFrame&);
    IlvFrame(IlvInputFile&, IlvPalette*);
};

ILVGDTMODULEINIT(frame);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVMOTIFLOOK)
#    include <ilviews/gadgets/motif/frame.h>
#  endif
#  if defined(ILVWINDOWSLOOK)
#    include <ilviews/gadgets/windows/frame.h>
#  endif
#  if defined(ILVWINDOWS95LOOK)
#    include <ilviews/gadgets/win95/frame.h>
#  endif
#  if defined(ILVWINDOWSXPLOOK)
#    include <ilviews/gadgets/winxp/frame.h>
#  endif
#  if defined(ILVVXLOOK)
#    include <ilviews/gadgets/vx/frame.h>
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Frame_H */
