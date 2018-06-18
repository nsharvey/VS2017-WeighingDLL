// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/vlabel.cpp
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
// Implementation of the IlvVerticalLabel class
// --------------------------------------------------------------------------

#include <ilviews/vlabel.h>

#if defined(ILVSTD)
#include <iostream>
#include <cstring>
#else  /* !ILVSTD */
#include <iostream.h>
#include <string.h>
#endif /* ILVSTD */

ILVSTDUSE

// --------------------------------------------------------------------------
IlvVerticalLabel::IlvVerticalLabel(IlvDisplay* d, const IlvPoint& p,
				   const char* s,
				   IlvPalette* pal)
: IlvLabel(d, p, s, pal)
{
    computeMaxWidth();
    _center.move(p.x()+_maxWidth/2,
		 (int)(p.y() +
		       strlen(_label)*getPalette()->getFont()->height()/2));
}

// --------------------------------------------------------------------------
void
IlvVerticalLabel::computeMaxWidth()
{
    _maxWidth=0;
    const char* s = getLabel();
    IlvFont* font=getPalette()->getFont();
    while(*s) {
	_maxWidth = IlvMax(_maxWidth,(IlvUShort)font->stringWidth(s,1));
	s++;
    }
}
// --------------------------------------------------------------------------
void
IlvVerticalLabel::setLabel(const char* label)
{
    IlvLabel::setLabel(label);
    computeMaxWidth();
}
// --------------------------------------------------------------------------
void
IlvVerticalLabel::draw(IlvPort* dst, const IlvTransformer* t,
		       const IlvRegion* rect) const
{
    IlvPoint p=_center;
    if (t) t->apply(p);
    unsigned int l = (int)strlen(_label);
    IlvPos h= getPalette()->getFont()->height();
    IlvPos d= getPalette()->getFont()->descent();
    IlvPos height=h*l;
    p.move((IlvPos)(p.x() - _maxWidth/2),
	   (IlvPos)(p.y() -  height/2)+h-d);
    if (rect) _palette->setClip(rect);
    char* s =_label;
    for (unsigned int loop=0; loop<l; loop++,s++) {
	getDisplay()->drawString(dst, _palette, p, s, 1);
	p.translate(0,(IlvDeltaPos)h);
    }
    if (rect) _palette->setClip();
}

// --------------------------------------------------------------------------
void
IlvVerticalLabel::boundingBox(IlvRect& rect, const IlvTransformer* t) const
{
    IlvPoint p = _center;
    if (t) t->apply(p);
    int l = (int)strlen(_label);
    IlvPos h= getPalette()->getFont()->height();
    //IlvPos d= getPalette()->getFont()->descent();
    IlvPos height=h*l;
    rect.move((IlvPos)(p.x() - _maxWidth/2),(IlvPos)(p.y() -  height/2));
    rect.resize(_maxWidth,(IlvDim)height);
}


// --------------------------------------------------------------------------
IlvGraphic*
IlvVerticalLabel::copy() const
{
    IlvRect bbox;
    boundingBox(bbox);
    return new IlvVerticalLabel(_palette->getDisplay(),
				bbox.orig(), _label, _palette);
}

// --------------------------------------------------------------------------
IlvGraphic*
IlvVerticalLabel::read(IlvInputFile& i, IlvPalette* pal)
{
    IlvPoint p;
    i.getStream() >> p;
    char* buffer=IlvReadString(i.getStream());
    return new IlvVerticalLabel(pal->getDisplay(), p, buffer, pal);
}

#if defined(IlvDECLAREINITCLASS)
IlvPreRegisterClass(IlvVerticalLabel);
ILVDEFINEINITCLASS(vlabel, IlvRegisterClass2(IlvVerticalLabel,IlvLabel);)
#else  /* !IlvDECLAREINITCLASS */
IlvRegisterClass(IlvVerticalLabel,IlvLabel);
#endif /* !IlvDECLAREINITCLASS */
