// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/vframe.h
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
// Declaration of the IlvViewFrameMLFHandler classes
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Vframe_H
#define __Ilv_Gadgets_Motif_Vframe_H

#ifndef __Ilv_Gadgets_Vframe_H
# include <ilviews/gadgets/vframe.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvViewFrameMLFHandler
    : public IlvDefaultViewFrameLFHandler
{
public:
    IlvViewFrameMLFHandler(IlvLookFeelHandler*);
    ~IlvViewFrameMLFHandler();

    virtual void	drawCaption(const IlvViewFrame* vframe,
				    const IlvMessageLabel* gadget,
				    IlvPort* dst,
				    const IlvTransformer* t,
				    const IlvRegion* clip) const;
    virtual void	drawFrame(const IlvViewFrame* vframe,
				  const IlvGadget* gadget,
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
    virtual void	drawReliefRectangle(IlvPort* dst,
					    const IlvRect& rect,
					    IlBoolean active,
					    IlBoolean inverted,
					    IlUShort thickness,
					    const IlvRegion* clip) const;
protected:
    IlvPalette*		_activeBs;
    IlvPalette*		_activeTs;
    IlvPalette*		_activeBg;
    IlvPalette*		_inactiveBs;
    IlvPalette*		_inactiveTs;
    IlvPalette*		_inactiveBg;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfvfram);

#endif /* !__Ilv_Gadgets_Motif_Vframe_H */
