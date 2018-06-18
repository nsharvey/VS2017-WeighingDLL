// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/attrcont.h
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
// Declaration of the IlvAttributeContainer class
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Attrcont_H
#define __Ilv31_Attrcont_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv31_Itf_Attrcont_H)
#include <ilviews/intrface/attrcont.h>
#endif
#if !defined(__Ilv31_Attribut_H)
#include <ilviews/attribut.h>
#endif

// --------------------------------------------------------------------------
class ILV31VAREXPORTED IlvAttributeContainer
: public IlvContainer, public IlvACItf {
public:
    IlvAttributeContainer(IlvAbstractView* parent,
			  const IlvRect&   size,
			  IlBoolean        useacc  = IlTrue,
			  IlBoolean        visible = IlTrue)
    : IlvContainer(parent, size, useacc, visible),
      _attributes() {}
    IlvAttributeContainer(IlvDisplay*    display,
			  IlvSystemView  parent,
			  const IlvRect& size,
			  IlBoolean      useacc  = IlTrue,
			  IlBoolean      visible = IlTrue)
    : IlvContainer(display, parent, size, useacc, visible),
      _attributes() {}
    IlvAttributeContainer(IlvDisplay*	display,
			  IlvSystemView window,
			  IlBoolean	useacc = IlTrue)
    : IlvContainer(display, window, useacc),
      _attributes() {}
    IlvAttributeContainer(IlvDisplay*	 display,
			  const char*	 name,
			  const char*	 title,
			  const IlvRect& dims,
			  IlBoolean	 useacc = IlTrue,
			  IlBoolean	 visible = IlTrue)
    : IlvContainer(display, name, title, dims, useacc, visible),
      _attributes() {}
    IlvAttributeContainer(IlvDisplay*	 display,
			  const char*	 name,
			  const char*	 title,
			  const IlvRect& dims,
			  IlUInt	 properties,
			  IlBoolean	 useacc       = IlTrue,
			  IlBoolean	 visible      = IlTrue,
			  IlvSystemView	 transientFor = 0)
    : IlvContainer(display, name, title, dims, properties, useacc,
		   visible, transientFor),
      _attributes() {}
    // ____________________________________________________________
    virtual IlvViewInputFile* createInputFile(IL_STDPREF istream&);
protected:
    virtual void cleanObj(IlvGraphic* object);
    virtual IlList* getAttributeList() const;
    IlList _attributes;
};

#endif /* !__Ilv31_Attrcont_H */
