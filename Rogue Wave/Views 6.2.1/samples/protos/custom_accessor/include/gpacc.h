// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/custom_accessor/include/gpacc.h
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
// Declaration of the Graphic Path accessor
// --------------------------------------------------------------------------

#ifndef __Ilv_Protos_Gpacc_H
#define __Ilv_Protos_Gpacc_H

#include <ilviews/protos/useracc.h>
#include <ilviews/base/iostream.h>

// ---------------------------------------------------------------------------
// IlvGraphicPathAccessor	Graphic Path accessor class:
//				moves a node along a graphic path.
// ---------------------------------------------------------------------------

class IlvGraphicPathAccessor
    : public IlvUserAccessor
{
public:
    IlvGraphicPathAccessor(const char* name,
			   const IlvValueTypeClass* type,
			   IlvDisplay* display,
			   const char* nodeName,
			   IlUInt polyLineCount,
			   const char** polyLineNames);
    ~IlvGraphicPathAccessor();

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvGraphicPathAccessor);
protected:
    IlvDisplay* _display;
    IlDouble _value;		// Current % of distance (= value of accessor)
    IlvSymbol* _nodeName;	// Moving node
    IlUInt _polyLineCount;	// # of polylines in graphic path
    IlvSymbol** _polyLineNames;	// names of polylines in graphic path.

    virtual IlBoolean changeValue(IlvAccessorHolder* object,
				   const IlvValue& val);
    virtual IlvValue& queryValue(const IlvAccessorHolder* object,
				 IlvValue& val) const;
};

// ---------------------------------------------------------------------------
// Static initialization of module.
// ---------------------------------------------------------------------------
IL_MODULEINIT(gpacc, IL_EMPTYMACRO);

#endif /* __Ilv_Protos_Gpacc_H */
