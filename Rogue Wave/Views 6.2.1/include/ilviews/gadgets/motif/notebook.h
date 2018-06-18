// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/motif/notebook.h
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
// Declaration of the IlvNotebookHandler classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Motif_Notebook_H
#define __Ilv_Gadgets_Motif_Notebook_H

#ifndef __Ilv_Gadgets_Notebook_H
# include <ilviews/gadgets/notebook.h>
#endif
#ifndef __Ilv_Looks_Motif_H
# include <ilviews/looks/motif.h>
#endif
#ifndef __Ilv_Gadgets_Motif_Macrosadv_H
# include <ilviews/gadgets/motif/macrosadv.h>
#endif

// --------------------------------------------------------------------------
class ILVADVMLOOKEXPORTED IlvNotebookMLFHandler
    : public IlvDefaultNotebookLFHandler
{
public:
    IlvNotebookMLFHandler(IlvLookFeelHandler* lfh)
	: IlvDefaultNotebookLFHandler(lfh) {}

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
    virtual void	draw(const IlvNotebook*,
			     IlvPort*,
			     const IlvTransformer*,
			     const IlvRegion*) const;
    virtual IlvDim	getArrowSize(const IlvNotebook*) const;
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
    virtual void	getTabSize(const IlvNotebookPage*,
				   IlvDim&,
				   IlvDim&) const;
    virtual IlUShort	getLastVisibleTab(const IlvNotebook* nbg,
					  IlBoolean& arrows,
					  IlBoolean& cuttab,
					  IlBoolean& decrSensitive,
					  IlBoolean& incrSensitive) const;
    virtual IlBoolean	propagateColors() const;
    virtual IlvDim	getDeltaMargin(const IlvNotebook*) const;
};

// --------------------------------------------------------------------------
ILVADVMLOOKMODULEINIT(mlfnoteb);

#endif /* !__Ilv_Gadgets_Motif_Notebook_H */
