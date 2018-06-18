// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/msglabel.h
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
// Declaration of the IlvMessageLabel class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Msglabel_H
#define __Ilv_Gadgets_Msglabel_H

#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Gadgets_Itemgdt_H)
#  include <ilviews/gadgets/itemgdt.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif

class IlvMessageLabel;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMessageLabelLFHandler : public IlvObjectLFHandler
{
public:
    IlvMessageLabelLFHandler(IlvLookFeelHandler* lfh);

    virtual void	drawBackground(const IlvMessageLabel* msg,
				       IlvPort* dst,
				       const IlvTransformer* t,
				       const IlvRegion* clip) const = 0;
    virtual void	drawFrame(const IlvMessageLabel* msg,
				  IlvPort* dst,
				  const IlvTransformer* t,
				  const IlvRegion* clip) const = 0;
    virtual void	drawContents(const IlvMessageLabel* msg,
				     IlvPort* dst,
				     const IlvTransformer* t,
				     const IlvRegion* clip) const = 0;
    virtual void	getPreferredSize(const IlvMessageLabel* obj,
					 IlvDim& w,
					 IlvDim& h) const = 0;
    virtual IlBoolean	handleEvent(IlvMessageLabel* sc,
				    IlvEvent& e) const = 0;
    virtual IlBoolean	handleAccelerator(const IlvMessageLabel*,
					  IlvEvent& event) const = 0;
    virtual IlUShort	getHorizontalMargin(const IlvMessageLabel*) const = 0;
    virtual IlUShort	getVerticalMargin(const IlvMessageLabel*) const = 0;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDefaultMessageLabelLFHandler
    : public IlvMessageLabelLFHandler
{
public:
    IlvDefaultMessageLabelLFHandler(IlvLookFeelHandler* lf)
	: IlvMessageLabelLFHandler(lf)
    {}

    virtual void	drawBackground(const IlvMessageLabel*,
				       IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(const IlvMessageLabel*,
				  IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(const IlvMessageLabel*,
				     IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	getPreferredSize(const IlvMessageLabel* obj,
					 IlvDim& w,
					 IlvDim& h) const;
    virtual IlBoolean	handleEvent(IlvMessageLabel* sc, IlvEvent& e) const;
    virtual IlBoolean	handleAccelerator(const IlvMessageLabel* obj,
					  IlvEvent& event) const;
    virtual IlUShort	getHorizontalMargin(const IlvMessageLabel*) const;
    virtual IlUShort	getVerticalMargin(const IlvMessageLabel*) const;
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvMessageLabel
    : public IlvGadget,
      public IlvGadgetItemHolder
{
    friend class IlvDefaultMessageLabelLFHandler;
public:

    IlvMessageLabel(IlvDisplay*      display,
		    const char*      message,
		    const IlvRect&   rect,
		    IlvAlignment     alignment   = IlvLeft,
		    IlUShort         thickness   = 0,
		    IlvPalette*      palette     = 0,
		    IlBoolean        copy        = IlTrue);

    IlvMessageLabel(IlvDisplay*      display,
		    const IlvPoint&  at,
		    const char*      message,
		    IlvAlignment     alignment   = IlvLeft,
		    IlUShort         thickness   = 0,
		    IlvPalette*      palette     = 0,
		    IlBoolean        copy        = IlTrue);

    ~IlvMessageLabel();

    // Label management
    inline const char*	getLabel() const { return _item->getLabel(); }

    inline void		setLabel(const char* label, IlBoolean copy = IlTrue)
			{
			    _item->setLabel(label, copy);
			}

    inline const char*	getMessage() const { return _item->getMessage(); }

    inline char		getMnemonic() const { return _item->getMnemonic(); }

    inline IlvAlignment	getAlignment() const
			{
			    return _item->getLabelAlignment();
			}

    inline void		setAlignment(IlvAlignment alignment)
			{
			    _item->setLabelAlignment(alignment);
			}

    inline IlvBitmap*	getBitmap() const { return _item->getBitmap(); }

    inline void		setBitmap(IlvBitmap* bitmap)
			{
			    _item->setBitmap(bitmap);
			}

    inline IlvBitmap*	getInsensitiveBitmap() const
			{
			    return _item->getBitmap(IlvGadgetItem::InsensitiveBitmapSymbol());
			}

    inline void		setInsensitiveBitmap(IlvBitmap* bitmap)
			{
			    _item->setBitmap(IlvGadgetItem::InsensitiveBitmapSymbol(), bitmap);
			}

    virtual IlvPosition	getLabelPosition() const;

    void		setLabelPosition(IlvPosition pos,
					 IlBoolean redraw = IlTrue);

    virtual void	getLabelOrientation(IlvOrientation& orientation,
					    IlBoolean& flip) const;

    void		setLabelOrientation(IlvOrientation orientation,
					    IlBoolean flip   = IlFalse,
					    IlBoolean redraw = IlTrue);

    inline IlUShort	getSpacing() const { return _item->getSpacing(); }

    void		setSpacing(IlUShort spacing,
				   IlBoolean redraw = IlTrue);

protected:
    virtual void	invalidateItem(IlvGadgetItem*,
				       const IlvGadgetItemGeometry&,
				       const IlvGadgetItemGeometry&);

    IlvPosition		_labelPosition;
    IlvPosition		_labelOrientation;
    IlBoolean		_flipLabel;
    IlvGadgetItem*	_item;

public:
    virtual IlUShort	getHorizontalMargin() const;
    virtual IlUShort	getVerticalMargin() const;
    virtual
    IlvGadgetItem*	applyToItems(IlvApplyGadgetItem f, IlAny arg);
    virtual
    const IlvGadget*	getGadget() const;
    virtual
    const IlvStylable*	getItemHolderStylable() const;
    virtual IlvPalette* getOpaquePalette() const;
    virtual IlvPalette* getSelectionPalette() const;
    virtual IlvPalette* getSelectionTextPalette() const;
    virtual IlvPalette* getInsensitivePalette() const;
    virtual IlvPalette* getNormalTextPalette() const;
    virtual void	getPreferredSize(IlvDim& w, IlvDim& h) const;
    virtual IlUInt	getBitmapMask() const;
    virtual void	drawBackground(IlvPort*,
				       const IlvTransformer*,
				       const IlvRegion*) const;
    virtual void	drawFrame(IlvPort*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    virtual void	drawContents(IlvPort*,
				     const IlvTransformer*,
				     const IlvRegion*) const;
    virtual void	drawMessageString(IlvPort*,
					  const IlvRect&,
					  const IlvTransformer* = 0,
					  const IlvRegion* = 0) const;
    IlBoolean		classFocusable() const;
    virtual void	drawFocus(IlvPort*,
				  const IlvPalette*,
				  const IlvTransformer*,
				  const IlvRegion*) const;
    inline
    IlvGadgetItem*	getItem() const { return _item; }
    virtual IlBoolean	handleEvent(IlvEvent&);
    IlBoolean		handleAccelerator(IlvEvent&) const;
    virtual void	apply(IlvApplyObject f, IlAny arg);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setFont(IlvFont* fnt);
    virtual void	setMode(IlvDrawMode);
    virtual void	setOverwrite(IlBoolean);
    virtual void	setSensitive(IlBoolean);
    virtual void	changeLanguage(const IlSymbol*);
    virtual void	updateLook();
    virtual void	changeLayoutAttributes(IlAny, IlAny);

    DeclareLazyTypeInfo();

    IlvMessageLabel(const IlvMessageLabel&);
    IlvMessageLabel(IlvInputFile&, IlvPalette*, IlBoolean = IlFalse);

    DeclareGraphicAccessors();
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(msglabel);
#if !defined(ILVSKIPLOOKS)
#  if defined(ILVWINDOWSLOOK)
// No specific L&F
#  endif
#  if defined(ILVWINDOWS95LOOK)
// No specific L&F
#  endif
#  if defined(ILVVXLOOK)
// No specific L&F
#  endif
#endif /* !ILVSKIPLOOKS */

#endif /* !__Ilv_Gadgets_Msglabel_H */
