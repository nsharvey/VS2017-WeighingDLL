// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/vx/notebook.h
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
// Declaration of the IlvNotebookVXLFHandler class
// Defined in library ilvavxlook
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Vx_Notebook_H
#define __Ilv_Gadgets_Vx_Notebook_H

#if !defined(__Ilv_Gadgets_Windows_Notebook_H)
#  if defined(ILVSKIPLOOKS)
#    include <ilviews/gadgets/windows/notebook.h>
#  else
#    define ILVSKIPLOOKS
#    include <ilviews/gadgets/windows/notebook.h>
#    undef ILVSKIPLOOKS
#  endif
#endif
#if !defined(__Ilv_Looks_Vx)
#  include <ilviews/looks/vx.h>
#endif
#if !defined(__Ilv_Gadgets_Vx_Macrosadv_H)
#  include <ilviews/gadgets/vx/macrosadv.h>
#endif

// --------------------------------------------------------------------------

class ILVADVVXLOOKEXPORTED IlvNotebookVXLFHandler 
    : public IlvNotebookWLFHandler
{
public:
    IlvNotebookVXLFHandler(IlvLookFeelHandler* lfh)
	: IlvNotebookWLFHandler(lfh) {}

    virtual void	drawBody(const IlvNotebook* notebook,
				 IlvPort* dst,
				 const IlvRect& rect,
				 const IlvRegion* clip) const;
    virtual void	computeAreas(const IlvNotebook*,
				     const IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     IlvRect&,
				     IlvRect&) const;
    virtual void	setMode(const IlvNotebook*, IlvDrawMode) const;
    virtual void	setOverwrite(const IlvNotebook*, IlBoolean) const;
    virtual IlvDim	getArrowSize(const IlvNotebook*) const;
    virtual void	draw(const IlvNotebook*,
			     IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const;
    void		drawTab(const IlvNotebook*,
				IlUShort,
				const IlvRect&,
				IlvPort*,
				const IlvRegion*) const;
    void		drawTabContents(const IlvNotebook*,
					const IlvNotebookPage*,
					const IlvRect& ,
					IlvPort*,
					const IlvRegion*) const;
    virtual void	setViewBackground(const IlvNotebookPage* nbg,
					  IlvView* view,
					  IlvColor* color) const;
    virtual void	computeShadowColors(const IlvNotebookPage* nbg,
					    IlvColor*& ts,
					    IlvColor*& bs) const;
    virtual void	computeFocusRegion(const IlvNotebook*,
					   IlvRegion&,
					   const IlvTransformer*) const;
    virtual void	getTabRect(const IlvNotebook*,
				   IlUShort,
				   const IlvRect&,
				   IlvRect&) const;
    IlUShort		getLastVisibleTab(const IlvNotebook* nbg,
					  IlBoolean& arrows,
					  IlBoolean& cuttab,
					  IlBoolean& decrSensitive,
					  IlBoolean& incrSensitive) const;
    virtual IlBoolean	propagateColors() const;
    virtual IlvDim	getDeltaMargin(const IlvNotebook*) const;
};

// --------------------------------------------------------------------------
ILVADVVXLOOKMODULEINIT(vxfnoteb);

#endif /* !__Ilv_Gadgets_Vx_Notebook_H */
