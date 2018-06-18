// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/ilvattr.h
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
// Declaration of the IlvAbstractAttribute class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Ilvattr_H
#define __Ilv_Base_Ilvattr_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
class IlvGraphic;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvAbstractVariable
{
public:
    virtual void	reevaluate() = 0;
protected:
    IlvAbstractVariable() {}
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvAbstractAttribute
{
public:
    virtual IlBoolean			check(const IlvGraphic*, IlAny) const;
    virtual const char*			className() const = 0;
    virtual void			setValue(IlInt   value)       = 0;
    virtual void			setValue(IlFloat value)       = 0;
    virtual void			setValue(const char* formula) = 0;
    virtual IlvAbstractVariable*	getAbstractVariable() const;

protected:
    IlvAbstractAttribute() {}
};

#endif /* __Ilv_Attrs_Base_H */
