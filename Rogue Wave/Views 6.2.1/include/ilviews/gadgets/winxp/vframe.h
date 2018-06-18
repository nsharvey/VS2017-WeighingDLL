// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/winxp/vframe.h
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
// Declaration of the IlvViewFrameWXPLFHandler class
// Defined in library ilvawxplook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Winxp_Vframe_H
#define __Ilv_Gadgets_Winxp_Vframe_H

#if defined(_WIN32)

#if !defined(__Ilv_Gadgets_Vframe_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/vframe.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/vframe.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Winxp_H)
#  include <ilviews/looks/winxp.h>
#endif
#if !defined(__Ilv_Gadgets_Winxp_Macrosadv_H)
#  include <ilviews/gadgets/winxp/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVWXPLOOKEXPORTED IlvViewFrameWXPLFHandler
    : public IlvDefaultViewFrameLFHandler
{
public:
    IlvViewFrameWXPLFHandler(IlvLookFeelHandler*);
    ~IlvViewFrameWXPLFHandler();

    virtual void	drawFrame(const IlvViewFrame* vframe,
				  const IlvGadget* gadget,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const;
    virtual void	drawCaption(const IlvViewFrame* vframe,
				    const IlvMessageLabel* gadget,
				    IlvPort* dst,
				    const IlvTransformer* t,
				    const IlvRegion* clip) const;
    virtual void	drawMinimizeButton(const IlvViewFrame* vframe,
					   const IlvButton* button,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const;
    virtual void	drawMaximizeButton(const IlvViewFrame* vframe,
					   const IlvButton* button,
					   IlvPort* dst,
					   const IlvTransformer* t,
					   const IlvRegion* clip) const;
    virtual void	drawRestoreButton(const IlvViewFrame* vframe,
					  const IlvButton* button,
					  IlvPort* dst,
					  const IlvTransformer* t,
					  const IlvRegion* clip) const;
    virtual void	drawCloseButton(const IlvViewFrame* vframe,
					const IlvButton* button,
					IlvPort* dst,
					const IlvTransformer* t,
					const IlvRegion* clip) const;
    virtual IlvDim	getTitleBarHeight(IlBoolean minimized) const;
    virtual IlvDim	getBorderSize(IlBoolean minimized) const;
    virtual void	updateLook(const IlvViewFrameButtons* buttons) const;
    HTHEME		getTheme() const { return _theme; }

protected:
    HTHEME		_theme;
};

// --------------------------------------------------------------------------
ILVADVWXPLOOKMODULEINIT(wxpvfram);

#endif /* _WIN32 */

#endif /* !__Ilv_Gadgets_Winxp_Vframe_H */
