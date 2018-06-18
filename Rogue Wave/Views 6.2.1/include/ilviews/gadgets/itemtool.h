// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/itemtool.h
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
// Declaration of the IlvEditItemView class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Itemtool_H
#define __Ilv_Gadgets_Itemtool_H

#if !defined(__Ilv_Graphics_Tooltip_H)
#include <ilviews/graphics/tooltip.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Gadgets_Eltextfd_H)
#include <ilviews/gadgets/eltextfd.h>
#endif

class IlvEditItemView;
class IlvGadgetItem;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvEditionTextField : public IlvElasticTextField
{
    friend class IlvEditItemView;
public:
    IlvEditionTextField(IlvEditItemView* editView,
			const char*	label,
			IlvDim		minimumSize,
			IlvDim		maximumSize,
			IlUShort	thick = IlvDefaultGadgetThickness,
			IlvPalette*	pal = 0);

    virtual void	drawFrame(IlvPort*		dst,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	clip = 0) const;
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	focusOut();
    virtual void	cancel();
    virtual void	validate();
    void		adjustView();

protected:
    virtual void	init();
    virtual IlvDim	computeSize() const;
    virtual void	afterResize();

    IlvEditItemView*	_editView;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvEditItemView : public IlvGadgetContainer
{
public:
    IlvEditItemView(IlvView*,
		    IlvGadgetItem*,
		    const IlvRect&,
		    const IlvRect&,
		    IlvPalette* palette,
		    const char* label = 0);
    virtual ~IlvEditItemView();

    IlvEditionTextField*	getTextField() const;
    IlvEditionTextField*	createTextField(IlvDim,
						IlvDim,
						const char*,
						IlvPalette*) const;
    inline
    IlvGadgetItem*	getGadgetItem() const { return _item; }
    inline
    const char*		getOldLabel() const { return _oldLabel; }
    IlBoolean		isElastic() const;
    void		setElastic(IlBoolean);
    virtual void	validate(const char*);
    virtual void	focusOut(IlvEvent& event);
    virtual void	cancel();
    virtual void	show();
    virtual void	hide();

protected:
    IlvEditionTextField* _textfield;
    IlvGadgetItem*	_item;
    IlvDim		_maxSize;
    char*		_oldLabel;
    IlvPalette*		_palette;
    IlBoolean		_allowFocus;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvItemToolTipView : public IlvToolTipView
{
public:
    IlvItemToolTipView(IlvGadgetItem*	item,
		       const IlvRect&	bbox,
		       IlvView*		transient,
		       IlvPalette*	palette = 0);
    virtual ~IlvItemToolTipView();

    IlvGadgetItem*	getGadgetItem() const { return _item; }
    virtual void	drawContents(IlvPort*		dst,
				     const IlvRect&	rect,
				     const IlvRegion*	clip);
    virtual void	hide();
    virtual void	show();

protected:
    IlvGadgetItem*	_item;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvItemTruncatedToolTipView : public IlvItemToolTipView
{
public:
    IlvItemTruncatedToolTipView(IlvGadgetItem*	item,
				const IlvRect&	bbox,
				IlvView*	transient,
				IlvPalette*	palette = 0);
    virtual ~IlvItemTruncatedToolTipView();

    virtual void	callInput(IlvEvent& event);
    virtual void	show();
    virtual void	hide();
protected:
    IlvRect		_rect;
    IlvRect		_clip;
    IlBoolean		_stillVisible;
    IlBoolean		_oldFocus;
};

#endif /* !__Ilv_Gadgets_Itemtool_H */
