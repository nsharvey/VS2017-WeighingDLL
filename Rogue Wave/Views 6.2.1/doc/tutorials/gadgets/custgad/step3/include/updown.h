// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/gadgets/custgad/step3/include/updown.h
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

#ifndef __UpDownField
#define __UpDownField

#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/textfd.h>

// --------------------------------------------------------------------------
class UpDownField
: public IlvGadget
{
public:
    UpDownField(IlvDisplay*    display,
                const IlvRect& rect,
                const char*    label,
                IlvUShort      thickness = IlvDefaultGadgetThickness,
                IlvPalette*    palette   = 0);
    ~UpDownField();
    // ____________________________________________________________
    const char* getLabel() const { return _textField->getLabel(); }
    void setLabel(const char* label, IlvBoolean redraw = IlvFalse)
    	{ _textField->setLabel(label, redraw); }
    void  setUpCallback(IlvGraphicCallback callback)
    	{ setCallback(upCallbackType(), callback); }
    void  setDownCallback(IlvGraphicCallback callback)
    	{ setCallback(downCallbackType(), callback); }
    virtual void draw(IlvPort* dst,
		      const IlvTransformer* t = 0,
		      const IlvRegion* clip = 0) const;
    virtual void setHolder(IlvGraphicHolder*);
    virtual void applyTransform(const IlvTransformer* t);
    virtual void setBackground(IlvColor*);
    virtual void setForeground(IlvColor*);
    virtual void setFont(IlvFont*);
    virtual void setMode(IlvDrawMode);
    virtual void setPalette(IlvPalette*);
    virtual void setThickness(IlvUShort);

    void computeRects(IlvRect& r1,
		      IlvRect& r2,
		      IlvRect& r3,
                      const IlvTransformer* t = 0) const;

    virtual IlvBoolean handleEvent(IlvEvent& event);
    virtual void decrement();
    virtual void increment();
    virtual IlvUInt getCallbackTypes(const char* const**,
                                     const IlvSymbol* const**) const;

    static IlvSymbol* upCallbackType()
      { return IlvGetSymbol("UpCallback", IlvTrue); }
    static IlvSymbol* downCallbackType()
      { return IlvGetSymbol("DownCallback", IlvTrue); }

    void setFocus(IlvGadget*);
    virtual void drawFocus(IlvPort* dst,
                           const IlvPalette* palette,
                           const IlvTransformer* t = 0,
                           const IlvRegion* clip = 0) const;
    virtual void computeFocusRegion(IlvRegion&,
                                    const IlvTransformer* t = 0) const;
    virtual IlvBoolean classFocusable() const;

    DeclareTypeInfo();
    DeclareIOConstructors(UpDownField);

protected:
    IlvTextField* _textField;
    IlvButton*    _rightButton;
    IlvButton*    _leftButton;
    IlvGadget*    _focusGadget;

    void init(const char* label = 0);
};

#endif
