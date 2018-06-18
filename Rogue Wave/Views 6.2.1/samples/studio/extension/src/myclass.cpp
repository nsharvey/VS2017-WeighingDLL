// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/myclass.cpp
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
// Definition of the MyClass class.
// --------------------------------------------------------------------------

#include <myclass.h>

#if defined(IL_STD)
#include <fstream>
IL_STDUSE
#else  /* !IL_STD */
#include <fstream.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
void
MyClass::draw(IlvPort* dst,
	      const IlvTransformer* t,
	      const IlvRegion* clip) const
{
    // Some useful local variables
    IlvPalette* palette = getPalette();
    // first draw and fill  the rectangle
    IlvRect rect=_drawrect;
    if (t)
	t->apply(rect);
    dst->drawRectangle(palette, rect);
    dst->drawLabel(palette, "MyClass", -1, rect, clip);
}

// --------------------------------------------------------------------------
IlvGraphic*
MyClass::copy() const
{
    return new MyClass(_palette->getDisplay(), _drawrect, _palette);
}

// --------------------------------------------------------------------------
IlvGraphic*
MyClass::read(IlvInputFile& i,
	      IlvPalette* pal)
{
    IlvRect drawrect;
    i.getStream() >> drawrect;
    return new MyClass(pal->getDisplay(), drawrect, pal);
}

// --------------------------------------------------------------------------
void
MyClass::write(IlvOutputFile& o) const
{
    o.getStream() << _drawrect ;
}

// --------------------------------------------------------------------------
IlvPreRegisterClass(MyClass);

#if defined(linux) || defined(__TCPLUSPLUS__)
// Gnu 2.7.2 has a bug on Linux...
static int initMyClass()
{
    IlvPostRegisterClass(MyClass, IlvFilledRectangle);
    IlvRegisterClassCodeInformation(MyClass,"myclass.h","");
    return 0;
}
#endif /* !linux && !defined(__TCPLUSPLUS__) */

IL_BEGINMODULEINITDEF(myclass)
#if defined(linux) || defined(__TCPLUSPLUS__)
// Gnu 2.7.2 has a bug on Linux...
static int _initMyClass = initMyClass();
#else  /* !linux && !defined(__TCPLUSPLUS__) */
IlvPostRegisterClass(MyClass, IlvFilledRectangle);
IlvRegisterClassCodeInformation(MyClass,"myclass.h","");
#endif /* !linux && !defined(__TCPLUSPLUS__) */
IL_ENDMODULEINITDEF(myclass)
