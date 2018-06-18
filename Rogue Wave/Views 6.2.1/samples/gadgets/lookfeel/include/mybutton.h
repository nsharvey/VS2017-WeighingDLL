// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/lookfeel/include/mybutton.h
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

#ifndef MyButton_H
#define MyButton_H

#if !defined(__Ilv_Gadgets_Win95_Button_H)
#include <ilviews/gadgets/win95/button.h>
#endif

// --------------------------------------------------------------------------
class MyButtonLFHandler
    : public IlvButtonW95LFHandler
{
public:
    MyButtonLFHandler(IlvLookFeelHandler*);
    ~MyButtonLFHandler();
    // ____________________________________________________________
    virtual void drawBackground(const IlvButton*,
				IlvPort*,
				const IlvTransformer*,
				const IlvRegion*) const;
    virtual void drawFrame(const IlvButton*,
			   IlvPort*,
			   const IlvTransformer*,
			   const IlvRegion*) const;
    virtual void drawFocus(const IlvButton*      obj,
			   IlvPort*              dst,
			   const IlvPalette*,
			   const IlvTransformer* t,
			   const IlvRegion*      clip) const;
    virtual void drawButtonAsDefault(const IlvButton*	button,
				     IlvPort*		dst,
				     const IlvTransformer*	t,
				     const IlvRegion*	clip) const;
protected:
    IlvBitmap* _button;
    IlvBitmap* _selbutton;
    IlvBitmap* _highbutton;
};

#endif
