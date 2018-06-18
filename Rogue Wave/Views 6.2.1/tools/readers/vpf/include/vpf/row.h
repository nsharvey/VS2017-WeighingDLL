// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/row.h
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Declaration of the VpfRow class
// --------------------------------------------------------------------------
#ifndef VPF_ROW_H
#define VPF_ROW_H

#include <vpf/basictypes.h>

class VpfCursor;
class VpfHeader;
class VpfFile;
class VpfDate;
class VpfCoordinate;
class VpfTripletID;

// --------------------------------------------------------------------------
class VpfRow
{
public:
    VpfRow(VpfCursor*);
    virtual ~VpfRow();
    // ____________________________________________________________
    int isBad() const { return (_cursor == 0); }
    void setBad() { _cursor = 0; }

    VpfUInt getNFields() const; 

    int getTextField(VpfUInt, char*&) const;
    int getIntField(VpfUInt, VpfInt&, VpfUInt = 0) const;
    int getFloatField(VpfUInt, double&, VpfUInt = 0) const;
    int getDateField(VpfUInt, VpfDate*&, VpfUInt = 0) const;
    int getCoordinateField(VpfUInt, VpfCoordinate*&, VpfUInt = 0) const;
    int getCoordinateArray(VpfUInt, VpfCoordinate*&) const;
    int getTripletID(VpfUInt field, VpfTripletID*& value, VpfUInt = 0) const;
    int getTripletID(VpfUInt field, VpfUInt subfield,
		     VpfInt& value, VpfUInt = 0) const;

    char* getText(VpfUInt field) const
	{
	    char* ptr = 0;
	    getTextField(field, ptr);
	    return ptr;
	}
    VpfDate* getDate(VpfUInt field) const
	{
	    VpfDate* ptr = 0;
	    getDateField(field, ptr);
	    return ptr;
	}
    VpfCoordinate* getCoordinate(VpfUInt field) const
	{
	    VpfCoordinate* ptr = 0;
	    getCoordinateField(field, ptr);
	    return ptr;
	}
    VpfCoordinate* getCoordinateArray(VpfUInt field) const
	{
	    VpfCoordinate* ptr = 0;
	    getCoordinateArray(field, ptr);
	    return ptr;
	}
    VpfInt getInt(VpfUInt field) const
	{
	    VpfInt i = 0;
	    getIntField(field, i);
	    return i;
	}
    double getFloat(VpfUInt field) const
	{
	    double i = 0.0;
	    getFloatField(field, i);
	    return i;
	}
    VpfInt getTripletIDPart(VpfUInt field, VpfUInt subfield) const
	{
	    VpfInt i = 0;
	    getTripletID(field, subfield, i);
	    return i;
	}
    VpfTripletID* getTripletID(VpfUInt field) const
	{
	    VpfTripletID* id = 0;
	    getTripletID(field, id);
	    return id;
	}
    int read(VpfUInt, VpfFile*);

    VpfUInt getRowNumber() const { return _number; }
    VpfUInt getCount(VpfUInt i) const { return _counts[i]; }

    void setMapped(VpfUInt i, int m)
	{ if (i != (VpfUInt)-1) _mapped[i] = m; }
    int isMapped(VpfUInt i) const
        {
	    return(i != (VpfUInt)-1)
		?_mapped[i]
		: 1;
	}
protected:
    typedef union field {
	char*		textval;
	double*		doubleval;
	VpfInt*		intval;
	VpfDate*	dateval;
	VpfCoordinate*	coordval;
	VpfTripletID*	tripletval;
    } Field;

    void free();
    void clear();

    VpfCursor*	_cursor;
    VpfUInt	_nFields;
    Field*	_fields;
    VpfUInt*	_counts;
    int*	_mapped;
    VpfUInt	_number;
};

#define VPF_QUERY_TEXTFIELD(CLASS, NAME) \
char* get##NAME() const { return getText(((CLASS*)_cursor)->_field##NAME); }

#define VPF_QUERY_INTFIELD(CLASS, NAME) \
VpfInt get##NAME() const { return getInt(((CLASS*)_cursor)->_field##NAME); }

#define VPF_QUERY_FLOATFIELD(CLASS, NAME) \
double get##NAME() const { return getFloat(((CLASS*)_cursor)->_field##NAME); }

#define VPF_QUERY_DATEFIELD(CLASS, NAME) \
VpfDate* get##NAME() const { return getDate(((CLASS*)_cursor)->_field##NAME); }

#define VPF_QUERY_COORDFIELD(CLASS, NAME) \
VpfCoordinate* get##NAME() const \
{ return getCoordinate(((CLASS*)_cursor)->_field##NAME); }

#define VPF_QUERY_COORDARRAY(CLASS, NAME) \
VpfCoordinate* get##NAME() const \
{ return getCoordinate(((CLASS*)_cursor)->_field##NAME); }\
VpfUInt get##NAME##Count() const \
{ return getCount(((CLASS*)_cursor)->_field##NAME); }

#endif /* VPF_ROW_H */
