// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/menubar.h
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
// Declaration of the IlvMenuBar class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Menubar_H
#define __Ilv_Gadgets_Menubar_H

#if !defined(__Ilv_Gadgets_Absbar_H)
#include <ilviews/gadgets/absbar.h>
#endif

class IlvMenuBar;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMenuBarLFHandler : public IlvObjectLFHandler
{
public:
    IlvMenuBarLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawGadgetItem(const IlvMenuBar* menu,
				       const IlvMenuItem* item,
				       IlvPort* dst,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvMenuBar* menu,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	drawBackground(const IlvMenuBar* menu,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvMenuBar* menu,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	getInternalBBox(const IlvMenuBar*,IlvRect&) const = 0;
    virtual IlBoolean	handleEscape(IlvMenuBar*, IlShort) const = 0;
    virtual void	setMode(IlvMenuBar*, IlvDrawMode) const = 0;
    virtual void	setOverwrite(IlvMenuBar*, IlBoolean) const = 0;
    virtual IlBoolean	handleEvent(IlvMenuBar* menu,
				    IlvEvent& event) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultMenuBarLFHandler : public IlvMenuBarLFHandler
{
public:
    IlvDefaultMenuBarLFHandler(IlvLookFeelHandler* lf)
	: IlvMenuBarLFHandler(lf)
    {}

    virtual void	drawGadgetItem(const IlvMenuBar*,
				       const IlvMenuItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const;
    virtual void	drawContents(const IlvMenuBar*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawBackground(const IlvMenuBar*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvMenuBar*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual IlBoolean	handleEvent(IlvMenuBar* bar, IlvEvent& event) const;
    virtual void	setMode(IlvMenuBar*, IlvDrawMode) const;
    virtual void	setOverwrite(IlvMenuBar*, IlBoolean) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMenuBar : public IlvAbstractBar
{
    friend class IlvDefaultMenuBarLFHandler;
public:

    IlvMenuBar(IlvDisplay*		display,
	       const IlvPoint&		point,
	       const char* const*	labels    = 0,
	       IlUShort			count     = 0,
	       IlUShort			thickness = IlvDefaultGadgetThickness,
	       IlvPalette*		palette   = 0);

    IlvMenuBar(IlvDisplay*		display,
	       const IlvRect&		rect,
	       const char* const*	labels    = 0,
	       IlUShort			count     = 0,
	       IlUShort			thickness = IlvDefaultGadgetThickness,
	       IlvPalette*		palette   = 0);

    IlvMenuBar(IlvDisplay*	display,
	       const IlvPoint&	point,
	       IlvMenuItem*	items,
	       IlUShort		count,
	       IlUShort		thickness = IlvDefaultGadgetThickness,
	       IlvPalette*	palette   = 0);

    IlvMenuBar(IlvDisplay*	display,
	       const IlvRect&	rect,
	       IlvMenuItem*	items,
	       IlUShort		count,
	       IlUShort		thickness = IlvDefaultGadgetThickness,
	       IlvPalette*	palette   = 0);

    void		setMode(IlvDrawMode m);
    void		setOverwrite(IlBoolean value);
    void		internalBBox(IlvRect&,
				     const IlvTransformer* t = 0) const;
    virtual const char*	getDefaultInteractor() const;
    virtual void	drawGadgetItem(const IlvGadgetItem*,
				       IlvPort* port,
				       const IlvRect& rect,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawContents(IlvPort* dst,
				     const IlvTransformer* t = 0,
				     const IlvRegion* clip = 0) const;
    virtual void	drawBackground(IlvPort* dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion* clip = 0) const;
    virtual void	drawFrame(IlvPort* dst,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;

    virtual IlBoolean	handleEvent(IlvEvent& event);
    DeclareGraphicAccessors();

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvMenuBar);

    void		iCallUnSelect(IlUShort pos);

    virtual
    const IlvStylable*	getItemHolderStylable() const;

protected:
    void		iCallSelect(IlUShort pos);
    virtual IlBoolean	iHandleEvent(IlvEvent& event);
};

// --------------------------------------------------------------------------
inline IlBoolean
IsAnIlvMenuBar(const IlvGraphic* object)
{
    return object->isSubtypeOf(IlvMenuBar::ClassInfo());
}

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvHMenuBarInteractor : public IlvHGadgetInteractor
{
public:
    virtual void	select(IlvMenuBar*, IlUShort) = 0;
    virtual void	unSelect(IlvMenuBar*, IlUShort) = 0;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(menubar);
#if defined(ILVMOTIFLOOK)
#include <ilviews/gadgets/motif/menubar.h>
#endif
#if defined(ILVWINDOWSLOOK)
#include <ilviews/gadgets/windows/menubar.h>
#endif
#endif /* !__Ilv_Gadgets_Menubar_H */
