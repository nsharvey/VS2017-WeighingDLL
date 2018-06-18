// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/custgad/include/coltree.h
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
// Declaration of the ColotedTreeGadget class
// --------------------------------------------------------------------------

#ifndef __ColoredTreeGadget
#define __ColoredTreeGadget

#include <ilviews/gadgets/tree.h>

// --------------------------------------------------------------------------
class ColoredTreeGadget
    : public IlvTreeGadget {
public:
    ColoredTreeGadget(IlvDisplay*        display,
		      const IlvRect&     rect,
		      IlUShort           thickness = IlvDefaultGadgetThickness,
		      IlvPalette*        palette   = 0);
    ~ColoredTreeGadget();
    // ____________________________________________________________
    IlBoolean isDrawingChildrenBackground() const { return _drawChildrenBg; }
    void drawChildrenBackground(IlBoolean value,
				IlBoolean redraw = IlTrue);
    void setChildrenBackground(IlvTreeGadgetItem* item,
			       IlvColor* color,
			       IlBoolean redraw = IlTrue);
    IlvColor* getChildrenBackground(const IlvTreeGadgetItem* item) const;
    virtual IlvPalette* getBackgroundPalette(const IlvTreeGadgetItem*) const;
    
    virtual void drawGadgetItem(const IlvGadgetItem* item,
				IlvPort* port,
				const IlvRect& rect,
				const IlvTransformer* t = 0,
				const IlvRegion* clip = 0) const;
    
    DeclareTypeInfo();
    DeclareIOConstructors(ColoredTreeGadget);
    DeclareGraphicAccessors();

protected:
    IlBoolean _drawChildrenBg;
};

#endif
