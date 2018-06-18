// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/toolbar.h
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
// Declaration of the IlvToolBar class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Toolbar_H
#define __Ilv_Gadgets_Toolbar_H

#if !defined(__Ilv_Gadgets_Absbar_H)
#include <ilviews/gadgets/absbar.h>
#endif

class IlvToolBar;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvToolBarLFHandler : public IlvObjectLFHandler
{
public:
    IlvToolBarLFHandler(IlvLookFeelHandler* lfh);

    virtual void	setMode(IlvToolBar*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvToolBar*, IlBoolean) const = 0;
    virtual IlUShort	getHMargin(const IlvToolBar*) const = 0;
    virtual IlUShort	getVMargin(const IlvToolBar*) const = 0;
    virtual void	drawGadgetItem(const IlvToolBar* toolbar,
				       const IlvMenuItem* item,
				       IlvPort* dst,
				       const IlvRect& bbox,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvToolBar*	toolbar,
				  IlvPort*		dst,
				  const IlvTransformer*	t,
				  const IlvRegion*	clip) const = 0;
    virtual void	drawBackground(const IlvToolBar* toolbar,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvToolBar* toolbar,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawHighlight(const IlvToolBar* toolbar,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvMenuItem* item,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const = 0;
    virtual void	drawSelection(const IlvToolBar* toolbar,
				      IlvPort* dst,
				      const IlvRect& rect,
				      const IlvMenuItem* item,
				      const IlvTransformer* t,
				      const IlvRegion* clip) const = 0;
    virtual IlBoolean	handleEvent(IlvToolBar* toolbar,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultToolBarLFHandler : public IlvToolBarLFHandler
{
public:
    IlvDefaultToolBarLFHandler(IlvLookFeelHandler* lf)
	: IlvToolBarLFHandler(lf)
    {}

    virtual void	setMode(IlvToolBar*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvToolBar*, IlBoolean) const;
    virtual IlUShort	getHMargin(const IlvToolBar*) const;
    virtual IlUShort	getVMargin(const IlvToolBar*) const;
    virtual void	drawGadgetItem(const IlvToolBar*,
				       const IlvMenuItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawFrame(const IlvToolBar*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(const IlvToolBar*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawContents(const IlvToolBar*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual IlBoolean	handleEvent(IlvToolBar* bar, IlvEvent& event) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvToolBar : public IlvAbstractBar
{
    friend class IlvDefaultToolBarLFHandler;
public:

    IlvToolBar(IlvDisplay*        display,
	       const IlvPoint&    point,
	       const char* const* labels    = 0,
	       IlUShort           count     = 0,
	       IlUShort           thickness = IlvDefaultGadgetThickness,
	       IlvPalette*        palette   = 0);

    IlvToolBar(IlvDisplay*        display,
	       const IlvRect&     rect,
	       const char* const* labels    = 0,
	       IlUShort           count     = 0,
	       IlUShort           thickness = IlvDefaultGadgetThickness,
	       IlvPalette*        palette   = 0);

    IlvToolBar(IlvDisplay*        display,
	       const IlvPoint&    point,
	       IlvMenuItem*	  items,
	       IlUShort           count,
	       IlUShort           thickness = IlvDefaultGadgetThickness,
	       IlvPalette*        palette   = 0);

    IlvToolBar(IlvDisplay*        display,
	       const IlvRect&     rect,
	       IlvMenuItem*	  items,
	       IlUShort           count,
	       IlUShort           thickness = IlvDefaultGadgetThickness,
	       IlvPalette*        palette   = 0);

    // ____________________________________________________________

    IlvMenuItem*	getFocusItem() const { return _focusItem; }

    void		setFocusItem(IlvMenuItem* item);

    void		setItemSelected(IlUShort index,
					IlBoolean value = IlTrue);

    IlBoolean		hasToolTips() const;

    void		useToolTips(IlBoolean value);

    inline static void	EnableToolTips(IlBoolean value = IlTrue)
			{
			    _EnableToolTips = value;
			}

    inline static
    IlBoolean		AreToolTipsEnabled() { return _EnableToolTips; }

    DeclareGraphicAccessors();
    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvToolBar);

protected:
    IlvMenuItem*	_lastHighlighted;
    IlvMenuItem*	_gadgetButtonDown;
    IlvMenuItem*	_focusItem;
    IlBoolean		_wasSelected;
    static IlBoolean	_EnableToolTips;

    virtual void	remove(IlUShort pos, IlBoolean destroy = IlTrue);
    virtual void	highlightItem(IlShort pos);
    virtual IlBoolean	iHandleEvent(IlvEvent& event);

public:
    virtual void	empty();
    virtual IlvPalette*	getSelectionTextPalette() const;
    virtual void	internalBBox(IlvRect&,
				     const IlvTransformer* t = 0) const;
    virtual void	setMode(IlvDrawMode m);
    virtual void	setOverwrite(IlBoolean value);
    virtual void	drawHighlight(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem*, 
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawSelection(IlvPort* dst,
				      const IlvRect& rect,
				      const IlvGadgetItem*, 
				      const IlvTransformer* t = 0,
				      const IlvRegion* clip = 0) const;
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual IlvDim	getMarginSelection() const;
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual IlBoolean	isSelectable(const IlvMenuItem*) const;
    virtual IlBoolean	buttonDown(IlShort);
    virtual IlBoolean	buttonUp();
    virtual IlUShort	getHMargin() const;
    virtual IlUShort	getVMargin() const;

    virtual
    const IlvStylable*	getItemHolderStylable() const;
};

// --------------------------------------------------------------------------
inline IlBoolean
IsAnIlvToolBar(const IlvGraphic* object)
{
    return object->isSubtypeOf(IlvToolBar::ClassInfo());
}

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(toolbar);
#if defined(ILVMOTIFLOOK)
#include <ilviews/gadgets/motif/toolbar.h>
#endif
#if defined(ILVWINDOWSLOOK)
#include <ilviews/gadgets/windows/toolbar.h>
#endif
#if defined(ILVWINDOWS95LOOK)
#include <ilviews/gadgets/win95/toolbar.h>
#endif
#if defined(ILVWINDOWSXPLOOK)
#include <ilviews/gadgets/winxp/toolbar.h>
#endif
#if defined(ILVVXLOOK)
#include <ilviews/gadgets/vx/toolbar.h>
#endif
#endif /* !__Ilv_Gadgets_Toolbar_H */
