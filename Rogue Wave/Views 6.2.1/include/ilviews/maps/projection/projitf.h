// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/projection/projitf.h
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
// Rogue Wave Views - Maps add-on.
// The Projection Interface
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_ProjectionInterface_H
#define __Ilv_Maps_ProjectionInterface_H

#include <ilviews/maps/macros.h>
#include <ilviews/intrface/value.h>

class ILVMAPSEXPORTED IlvProjection;

class ILVMAPSEXPORTED IlvProjectionInterface :
public IlvValueInterface
{
protected:
    IlvProjectionInterface(IlvProjection* p);
    virtual ~IlvProjectionInterface();
    friend ILVMAPSEXPORTED class IlvProjection;
public:
    virtual IlvValue&  queryValue(IlvValue& value) const;
    virtual IlBoolean applyValue(const IlvValue& value);

    virtual void getAccessors(const IlvSymbol* const** accessors,
			      const IlvValueTypeClass* const** types,
			      IlUInt& count) const;
    void getClassAccessors(const IlvSymbol* const**,
			   const IlvValueTypeClass* const**,
			   IlUInt&,
			   IlBoolean expandBaseClasses = IlTrue) const;
    virtual const IlvValueTypeClass* getValueType(const IlvSymbol* valueName)
	const;

    IlBoolean isValueReadOnly(const IlvSymbol* valueName) const;

private:
    IlvProjection* _projection;
};
#endif
