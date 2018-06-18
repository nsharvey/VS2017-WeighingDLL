// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/css/stylesheet.h
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
// Declaration of the IlvCssStyleSheet class
// --------------------------------------------------------------------------
#ifndef __Ilv_Css_Stylesheet_H
#define __Ilv_Css_Stylesheet_H

#if !defined(__Ilv_Css_Macros_H)
#  include <ilviews/css/macros.h>
#endif
#if !defined(__Ilv_Base_Stylesheet_H)
#  include <ilviews/base/stylesheet.h>
#endif

// --------------------------------------------------------------------------
class ILVCSSEXPORTED IlvCssStyleSheet
: public IlvStyleSheet
{
public:
    IlvCssStyleSheet(const char* name = 0);
    virtual ~IlvCssStyleSheet();

    virtual IlBoolean	read(ILVSTDPREF istream& stream);
    virtual IlBoolean	setContent(const char* content);

    virtual const char*	getName() const;
    virtual const char*	getStylingTechnology() const;
    virtual
    IlvStyleQuery*	createStyleQuery(const IlvStylable*) const;
    virtual void	destroyStyleQuery(IlvStyleQuery*) const;

    /* TODO: Useless for distrib */
    size_t		getSize() const;

//private:
    struct		P;
    struct P*		_p;
};

#endif /* !__Ilv_Css_Stylesheet_H */
