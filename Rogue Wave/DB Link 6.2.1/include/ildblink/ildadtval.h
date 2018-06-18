// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildadtval.h
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
// Values class for ADT
// --------------------------------------------------------------------------

#ifndef __ILD_ILDADTVAL_H
#define __ILD_ILDADTVAL_H

#ifndef __Il_Ilidtime_H
#   include <ildblink/ilidtime.h>
#endif
#ifndef __ILD_ILDENT_H
#   include <ildblink/ildent.h>
#endif
#ifndef __ILD_ILDVAL_H
#   include <ildblink/ildval.h>
#endif

#ifndef __Il_Array_H
#   include <ilog/array.h>
#endif

class IldValue;
class IldADTDescriptor;

class ILD_EXPORTED IlDeclareArrayWithoutEquality(IldValue*,
						 IldValueArray);

// ==========================================================================
// ADTValue class: base class for value of ADTs: User Defined Types
// 
//   Possible entity types: 
//	- with identical elements:
//		- array : count limits the number of elements (Ora)
//		- list, multiset, set: no limit in number of elements (Inf9)
//	- with different element types:
//		- object: (Ora)
//		- named or unnamed row: (Inf9)
// ==========================================================================
class ILD_EXPORTED IldADTValue {

 protected:
    const IldADTDescriptor*	_type;
    IldValueArray		_valMgr;
    IlBitArray			_nullsMgr;

 public:
    virtual
				~IldADTValue	();

    IldADTValue	(const IldADTDescriptor* type,
		 const char* table = 0);

    // Deep copy
    IldADTValue (const IldADTValue& other);
    IlUInt			getCount	() const;

    inline void			setCount	(IlUInt count)
    {
	while (count < _valMgr.getLength()) {
	    _valMgr.remove(count) ;
	}
    }

    inline IlUInt		getSize		() const
    {
	return _valMgr.getLength();
    }

    // Getters
    inline const IldADTDescriptor*	getDescriptor	() const
    {
	return _type;
    }

    inline IldADTType		getADTType	() const
    {
	return _type->getType();
    }

    inline const char*		getTableName	() const
    {
	//  return (_tableName[0] ? _tableName : 0);
	return 0;
    }

    inline const char*		getTypeName	() const
    {
	return _type->getName();
    }

    inline IldColumnType	getType		(IlUInt index) const;

    IlBoolean			isNull		(IlUInt index) const;

    const char*			getStringValue	(IlUInt index) const;

    const char*			getPurgedStringValue(IlUInt index) const;

    const char*			getRTrimedStringValue(IlUInt index) const;

    IlInt			getIntegerValue	(IlUInt index) const;

    double			getRealValue	(IlUInt index) const;

    IlUChar			getByteValue	(IlUInt index) const;

    IlAny			getAnyValue	(IlUInt index) const;

    inline double		getMoneyValue	(IlUInt index) const
    {
	return getRealValue(index);
    }

    inline const char*		getDateValue	(IlUInt index) const
    {
	return getStringValue(index);
    }

    IlNumeric			getNumericValue	(IlUInt index) const;

    IldDateTime			getDateTimeValue(IlUInt index) const;

    IldADTValue*		getADTValue	(IlUInt index) const;

    IldBytes			getBytesValue	(IlUInt index) const;

    IldBytes			getRefValue	(IlUInt index) const;

    // Setters
    IlBoolean			setNull		(IlBoolean flag,
						 IlUInt index);

    IlBoolean			setValue	(const char* val,
						 IlUInt index);

    IlBoolean			setValue	(IlInt val,
						 IlUInt index);

    IlBoolean			setValue	(double val,
						 IlUInt index);

    IlBoolean			setValue	(IlUChar val,
						 IlUInt index);
    IlBoolean			setValue	(IlAny val,
						 IlUInt index);

    IlBoolean			setValue	(IldBytes val,
						 IlUInt index);

    IlBoolean			setValue	(const IlNumeric* val,
						 IlUInt index);

    IlBoolean			setValue	(const IldDateTime* val,
						 IlUInt index);

    IlBoolean			setValue	(IldADTValue* val,
						 IlUInt index);

};


// --------------------------------------------------------------------------
// Inlines
// --------------------------------------------------------------------------
inline IldColumnType
IldADTValue::getType (IlUInt index) const
{
    return (index < _valMgr.getLength())
	   ? _valMgr[index]->getType() : IldUnknownType;
}

#endif // __ILD_ILDADTVAL_H
