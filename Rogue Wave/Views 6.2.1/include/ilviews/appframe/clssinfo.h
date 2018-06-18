// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/clssinfo.h
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
// Declaration of the IlvDvDynClassInfo class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Clssinfo_H)
#define __Ilv_Appframe_Clssinfo_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif

class IlvDvSerializable;
typedef IlvDvSerializable* (*IlvDvObjectBuilder)();

// --------------------------------------------------------------------------
// IlvDvDynClassInfo class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDynClassInfo : public IlvPropClassInfo
{
public:
    inline
    IlvDvObjectBuilder	getBuilder() const { return _builder; }
    inline void		setBuilder(IlvDvObjectBuilder builder)
			{
			    _builder = builder;
			}
    inline
    IlvDvSerializable*	createObject() const
			{
			    return _builder ? _builder() : 0;
			}
    static
    IlvDvDynClassInfo*	Create(const char*, IlvClassInfo**,
			       IlvDvObjectBuilder = 0);

protected:
    IlvDvDynClassInfo(const char*	 className,
		      IlvClassInfo**     superClass,
		      IlvDvObjectBuilder builder = 0)
	: IlvPropClassInfo(className, superClass),
	  _builder(builder) {}

    IlvDvObjectBuilder	_builder;
};


// --------------------------------------------------------------------------
#endif /* ! __Ilv_Appframe_Clssinfo_H */
