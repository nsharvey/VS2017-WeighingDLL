// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/stylesheet.h
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
// Declaration of the IlvStyleSheet class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Stylesheet_H
#define __Ilv_Base_Stylesheet_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Il_Iostream_H)
#  include <ilog/iostream.h>
#endif
#include <list>

class IlvStylable;
class IlvStylist;
class IlvStyleQuery;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvStyleSheet
{
public:
    typedef std::list<IlvStyleSheet*> List;

    IlvStyleSheet(const char* name)
    : _counter(0)
    {}
    virtual ~IlvStyleSheet();

    virtual IlBoolean	read(ILVSTDPREF istream& stream) = 0;
    virtual IlBoolean	setContent(const char* content) = 0;

    virtual const char*	getName() const;

    virtual const char*	getStylingTechnology() const = 0;
    virtual
    IlvStyleQuery*	createStyleQuery(const IlvStylable*) const = 0;
    virtual void	destroyStyleQuery(IlvStyleQuery*) const = 0;

    void		attach(IlvStylist*);
    void		detach(IlvStylist*);

    std::list<IlvStylist*>* getStylists() const;

    void		lock();
    void		unLock();
private:
    IlUInt		_counter;
};

#endif /* !__Ilv_Base_Stylesheet_H */
