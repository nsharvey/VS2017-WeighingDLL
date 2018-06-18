// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/cliplab.cpp
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
// Definition of the IlvClippedLabel class
// --------------------------------------------------------------------------

#include <ilviews/cliplab.h>

#if defined(ILVSTD)
#include <iostream>
#include <cstring>
#else  /* !ILVSTD */
#include <iostream.h>
#include <string.h>
#endif /* ILVSTD */

ILVSTDUSE

// --------------------------------------------------------------------------
IlvClippedLabel::IlvClippedLabel(IlvDisplay*    display,
				 const IlvRect& clip,
				 const char*    label,
				 IlvBoolean     fillLabel,
				 IlvPalette*    palette)
: IlvFilledRectangle(display,clip,palette),_fillLabel(fillLabel)
{
    _label = new char[1+strlen(label)];
    strcpy(_label,label);
}

// --------------------------------------------------------------------------
IlvClippedLabel::IlvClippedLabel(IlvDisplay*     display,
				 const IlvPoint& p,
				 const char*     label,
				 IlvBoolean      fillLabel,
				 IlvPalette*     palette)
: IlvFilledRectangle(display, palette), _fillLabel(fillLabel)
{
    int l = (int)strlen(label);
    _label = strcpy(new char[l + 1], label);
    IlvDim w=getPalette()->getFont()->stringWidth(_label, l);
    IlvDim h=getPalette()->getFont()->height();
    _drawrect.moveResize(p.x(), p.y(), w+2, h+2);
}

// --------------------------------------------------------------------------
void
IlvClippedLabel::draw(IlvPort* dst, const IlvTransformer* t,
		      const IlvRegion* clip) const
{
    IlvRect rect=_drawrect;
    if(t) t->apply(rect);
    if(clip) getPalette()->setClip(clip);
    getDisplay()->drawRectangle(dst,getPalette(),rect);
    if(clip) getPalette()->setClip();
    if(t) {
	IlvTransfoParam t11,t12,t21,t22;
	t->getValues(t11, t12, t21, t22);
    	if ((t11 < 0.98) || (t22 < 0.98))
	    return;
    }
    if (_fillLabel)
	getDisplay()->drawILabel(dst,getPalette(), _label, -1, rect, clip);
    else
	getDisplay()->drawLabel(dst,getPalette(), _label, -1,rect, clip);
}

// --------------------------------------------------------------------------
void
IlvClippedLabel::setLabel(const char* label)
{
    delete _label;
    _label = new char[1+strlen(label)];
    strcpy(_label,label);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvClippedLabel::copy() const
{
    return new IlvClippedLabel(_palette->getDisplay(), _drawrect,
			      _label, _fillLabel, _palette);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvClippedLabel::read(IlvInputFile& i, IlvPalette* pal)
{
    IlvRect clip;
    int fill;
    i.getStream() >> clip >> fill;
    char* buffer = IlvReadString(i.getStream());
    return new IlvClippedLabel(pal->getDisplay(), clip,
			      buffer, fill? IlTrue : IlFalse, pal);
}

// --------------------------------------------------------------------------
void
IlvClippedLabel::write(IlvOutputFile& o) const
{
    o.getStream() << _drawrect << " " << (int)_fillLabel << " ";
    IlvWriteString(o.getStream(), _label);
    o.getStream() <<  " " ;
}

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvPreRegisterClass(IlvClippedLabel);
ILVDEFINEINITCLASS(cliplab, IlvPostRegisterClass(IlvClippedLabel, IlvFilledRectangle);)
#else  /* !IlvDECLAREINITCLASS */
IlvRegisterClass(IlvClippedLabel, IlvFilledRectangle);
#endif /* !IlvDECLAREINITCLASS */
