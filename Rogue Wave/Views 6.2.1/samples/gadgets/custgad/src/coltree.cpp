// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/custgad/src/coltree.cpp
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
// Declaration of the ColoredTreeGadget class
// --------------------------------------------------------------------------

#include <coltree.h>

#if defined(IL_STD)
#include <iostream>
#else  /* !IL_STD */
#include <iostream.h>
#endif /* IL_STD */

ILVSTDUSE

// --------------------------------------------------------------------------
ColoredTreeGadget::ColoredTreeGadget(IlvDisplay*        display,
				     const IlvRect&     rect,
				     IlUShort          thickness,
				     IlvPalette*        palette)
    : IlvTreeGadget(display, rect, thickness, palette),
      _drawChildrenBg(IlTrue)
{
}

// --------------------------------------------------------------------------
ColoredTreeGadget::ColoredTreeGadget(const ColoredTreeGadget& source)
    : IlvTreeGadget(source),
      _drawChildrenBg(source._drawChildrenBg)
{
    // Nothing to do here
}

// --------------------------------------------------------------------------
ColoredTreeGadget::ColoredTreeGadget(IlvInputFile& is,
				     IlvPalette* palette)
    : IlvTreeGadget(is, palette),
      _drawChildrenBg(IlTrue)
{
    // Read the _drawChildrenBg flag
    int drawChildrenBg;
    is.getStream() >> drawChildrenBg;
    _drawChildrenBg = drawChildrenBg ? IlTrue : IlFalse;
}

// --------------------------------------------------------------------------
void
ColoredTreeGadget::write(IlvOutputFile& os) const
{
    IlvTreeGadget::write(os);
    // Write the _drawChildrenBg flag
    os.getStream() << IlvSpc() << (int)_drawChildrenBg << IlvSpc();
}

// --------------------------------------------------------------------------
static IlBoolean
UnlockPalette(IlvGadgetItem* item,
	      IlAny arg)
{
    ColoredTreeGadget* tree = (ColoredTreeGadget*)arg;
    tree->setChildrenBackground((IlvTreeGadgetItem*)item, 0, IlFalse);
    return IlTrue;
}

// --------------------------------------------------------------------------
ColoredTreeGadget::~ColoredTreeGadget()
{
    // Unlock all the palettes before destroying the items
    applyToItems(UnlockPalette, (IlAny)this);
}

// --------------------------------------------------------------------------
void
ColoredTreeGadget::drawChildrenBackground(IlBoolean value,
					  IlBoolean redraw)
{
    _drawChildrenBg = value;
    if (redraw)
	reDraw();
}

// --------------------------------------------------------------------------
static IlvSymbol*
GetChildrenBackgroundSymbol()
{
    // This symbol is used to connect a tree gadget item to the color of its
    // children
    static IlSymbol* symbol = IlGetSymbol("ChildrenBackground");
    return symbol;
}

// --------------------------------------------------------------------------
IlvPalette*
ColoredTreeGadget::getBackgroundPalette(const IlvTreeGadgetItem* item) const
{
    // Returns the palette that will be used to draw the background of 'item'
    // This information is stored in its parent
    if (item->getParent()) {
	IlvPalette* palette = (IlvPalette*)
	    item->getParent()->getProperty(GetChildrenBackgroundSymbol());
	if (!palette)
	    palette = getBackgroundPalette(item->getParent());
	return palette;
    } else
	return 0;
}

// --------------------------------------------------------------------------
void
ColoredTreeGadget::setChildrenBackground(IlvTreeGadgetItem* item,
					 IlvColor* color,
					 IlBoolean redraw)
{
    // Retrieve the oldColor
    IlvPalette* oldPalette =
	(IlvPalette*)item->getProperty(GetChildrenBackgroundSymbol());
    // Compute the new one
    IlvPalette* palette = color
	? getDisplay()->getPalette(0, color)
	: 0;
    // Lock it
    if (palette)
	palette->lock();
    // Unlock the old one
    if (oldPalette)
	oldPalette->unLock();
    // Set the property to the item
    item->setProperty(GetChildrenBackgroundSymbol(), (IlAny)palette);
    // Redraw if asked
    if (redraw)
	reDraw();
}

// --------------------------------------------------------------------------
IlvColor*
ColoredTreeGadget::getChildrenBackground(const IlvTreeGadgetItem* item) const
{
    // Returns the color stored in the property list of the specified item
    IlvPalette* palette =
	(IlvPalette*)item->getProperty(GetChildrenBackgroundSymbol());
    return palette
	? palette->getForeground()
	: 0;
}

// --------------------------------------------------------------------------
void
ColoredTreeGadget::drawGadgetItem(const IlvGadgetItem* item,
				  IlvPort* port,
				  const IlvRect& rect,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const
{
    if (isDrawingChildrenBackground()) {
	// Check if the item being drawn has a special palette
	IlvPalette* palette = getBackgroundPalette((IlvTreeGadgetItem*)item);
	if (palette) {
	    // Compute the visible bounding box
	    IlvRect bbox;
	    visibleBBox(bbox, t);
	    // Move and resize it to match the item bounding box
	    bbox.y(rect.y());
	    bbox.h(rect.h());
	    IlvPushClip pushClip(*palette, clip);
	    port->fillRectangle(palette, bbox);
	}
    }
    // Draw the item
    IlvTreeGadget::drawGadgetItem(item, port, rect, t, clip);
}

// --------------------------------------------------------------------------
static IlSymbol*
GetDrawChildrenBackgroundSymbol()
{
    // This symbol is used to access to drawChildrenBackground accessor of
    // the colored tree gadget
    static IlSymbol* symbol = IlGetSymbol("drawChildrenBackground");
    return symbol;
}

// --------------------------------------------------------------------------
IlvValue&
ColoredTreeGadget::queryValue(IlvValue& value) const
{
    if (value.getName() == GetDrawChildrenBackgroundSymbol())
	return value = isDrawingChildrenBackground();
    else
	return IlvTreeGadget::queryValue(value);
}

// --------------------------------------------------------------------------
IlBoolean
ColoredTreeGadget::applyValue(const IlvValue& value)
{
    if (value.getName() == GetDrawChildrenBackgroundSymbol()) {
	drawChildrenBackground((IlBoolean)value, IlFalse);
	return IlTrue;
    } else
	return IlvTreeGadget::applyValue(value);
}

// --------------------------------------------------------------------------
void
ColoredTreeGadget::GetAccessors(const IlSymbol* const** a,
				const IlvValueTypeClass* const** t,
				IlUInt& c)
{
    DeclareAccessor(GetDrawChildrenBackgroundSymbol(),
		    IlvValueBooleanType,
		    a,
		    t,
		    c);

}

IlvPredefinedIOMembers(ColoredTreeGadget)
    
// --------------------------------------------------------------------------
IlvRegisterClass(ColoredTreeGadget, IlvTreeGadget);
