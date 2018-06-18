// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/gadset.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliGadgetSet class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Gadset_H
#define __Ili_Gadset_H

#if !defined(__Ilv_Base_Link_H)
#  include <ilviews/base/link.h>
#endif
#if !defined(__Ilv_Graphics_Tooltip_H)
#  include <ilviews/graphics/tooltip.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Module_H)
#  include <ilviews/dataccess/module.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliGadgetSetToolTip
: public IlvToolTip
{
public:
    IliGadgetSetToolTip();

    DeclarePropertyInfoRO();
    DeclarePropertyIOConstructors(IliGadgetSetToolTip);

    virtual void	init(const IlvView*,
			     const IlvGraphic*,
			     const IlvPoint&);
    virtual void	reInit(const IlvView*,
			       const IlvGraphic*,
			       const IlvPoint&);
    virtual void	show(IlvView*, IlvRect& rect);
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliGadgetSet
: public IlvGadget
{
public:
    IliGadgetSet(IlvDisplay* display,
		 const IlvRect& rect,
		 IlUShort thickness = IlvDefaultGadgetThickness,
		 IlvPalette* palette = 0);
    ~IliGadgetSet();

    const IlvList*	getList() const;
    IlUInt		getCardinal() const;
    IlvGadget*		getObject(IlUInt index) const;
    IlvGadget*		getObject(const char* name) const;
    IlInt		getIndex(IlvGadget* g) const;
    virtual void	addObject(IlvGadget* obj, IlBoolean visible = IlTrue);
    virtual void	removeObject(IlvGadget* obj,
				     IlBoolean deleteIt = IlTrue);

    virtual void	objectReceivedEvent(IlvGadget* obj);

    IlvGadget*		firstContains(const IlvPoint& p,
				      const IlvPoint& tp,
				      const IlvTransformer* t = 0) const;
    IlvGadget*		firstIntersects(const IlvRegion& tregion,
					const IlvTransformer* t = 0) const;
    IlBoolean		isVisible(const IlvGadget*) const;
    void		setVisible(IlvGadget* obj, IlBoolean visible);
    IlBoolean		isObjectSensitive(IlvGadget* obj) const;
    void		setObjectSensitive(IlvGadget* obj, IlBoolean active);
    IlvGadget*		getFocusObject() const;
    virtual IlBoolean	setFocusObject(IlvGadget* obj);

    IlvGadget*		closestFocusableNeighbor(IlvGadget* obj,
						 IlBoolean = IlTrue);
    void		adjustFocus();

    // -- overrides IlvGraphic
    virtual void	apply(IlvApplyObject, IlAny);
    virtual void	applyReferences(IlvApplyObject, IlAny);
    virtual IlBoolean	contains(const IlvPoint& p,
				 const IlvPoint& tp,
				 const IlvTransformer* t = 0) const;
    virtual IlBoolean	intersects(const IlvRegion& tregion,
				   const IlvTransformer* t = 0) const;
    virtual IlBoolean	inside(const IlvRegion& tregion,
			       const IlvTransformer* t = 0) const;
    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t=0,
			     const IlvRegion* clip = 0) const;
    virtual void	drawPalette(const IlvPalette*,
				    IlvPort* dst,
				    const IlvTransformer* t = 0,
				    const IlvRegion* clip = 0) const;

    virtual void	drawFocus(IlvPort*,
				  const IlvPalette* ,
				  const IlvTransformer* t = 0,
				  const IlvRegion* clip = 0) const;
    virtual void	computeFocusRegion(IlvRegion&,
					   const IlvTransformer* t = 0) const;
    virtual void	computeHighlightRegion(IlvRegion&,
					       const IlvTransformer* = 0)const;

    virtual IlBoolean	handleAccelerator(IlvEvent&) const;

    virtual void	applyTransform(const IlvTransformer* t);
    virtual void	boundingBox(IlvRect& r,
				    const IlvTransformer* t = 0) const;
    virtual IlBoolean	zoomable() const;

    virtual void	setOverwrite(IlBoolean o);
    virtual void	setMode(IlvDrawMode m);
    virtual void	invert(IlBoolean temp=IlFalse);

    virtual void	setSensitive(IlBoolean value);
    virtual void	setThickness(IlUShort);
    virtual void	setPalette(IlvPalette* pal);
    virtual void	setBackground(IlvColor* c);
    virtual void	setForeground(IlvColor* c);
    virtual void	setFont(IlvFont* f);
    virtual void	setColorPattern(IlvColorPattern* b);
    virtual void	setPattern(IlvPattern* p);
    virtual void	setArcMode(IlvArcMode m);
    virtual void	setFillRule(IlvFillRule m);
    virtual void	setFillStyle(IlvFillStyle f);
    virtual void	setLineStyle(IlvLineStyle* style);
    virtual void	setLineWidth(IlUShort width);
    virtual void	setPlaneMask(unsigned int);
    virtual void	setAlpha(IlvIntensity alpha);
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);

    virtual void	print(IL_STDPREF ostream&, int level = 0) const;

    DeclareTypeInfo();
    DeclareIOConstructors(IliGadgetSet);

    // -- override IlvGadget

    // virtual void setThickness(IlUShort);
    // virtual void useDefaultSize(IlBoolean);

    IlBoolean		classFocusable() const;
    virtual void	setHolder(IlvGadgetHolder* holder);
    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	focusIn();
    virtual void	focusOut();
    virtual void	enterGadget();

    virtual void	getToolTipText(const IlvPoint& pt, IliString& s);
    void		enableToolTip();
    void		disableToolTip();
    void		enablePaletteToolTip();

    virtual void	setVisible(IlBoolean value);

protected:
    IlBoolean		_hasFocus;
    IlBoolean		_fitsToContents;
    IlBoolean		_areObjectsPersistent;
    IlBoolean		_inHandleEvent;
    IlBoolean		_paletteToolTip;
    IlvList		_list;
    IlvHashTable	_table;
    IlvGadget*		_focusGadget;
    IliGadgetSetToolTip* _toolTipProp;

    IlvGadget*		gadgetForAccelerator(IlvEvent& event) const;
    virtual void	objectNeedsReDraw(IlvGadget*);
    virtual void	regionNeedsReDraw(const IlvRegion&);
    IlInt		getVisibleObjectsCount() const;
    void		adjustSensitivity();
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliGadgetSet);

#endif /* !__Ili_Gadset_H */
