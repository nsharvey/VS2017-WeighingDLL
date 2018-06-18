// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/query.cpp
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
// Definition of the query classes
// --------------------------------------------------------------------------

#include <vpf/query.h>
#include <vpf/thematicindex.h>
#include <vpf/table.h>
#include <vpf/header.h>
#include <vpf/row.h>
#include <vpf/string.h>
#include <string.h>

// --------------------------------------------------------------------------
VpfAllExpression::VpfAllExpression(VpfTable* t)
: VpfExpression(0),
  _set(0)
{
    if (t) {
	_set = new VpfSet(t->getNRows());
	_set->setAll();
    }
}


#define OCE_CREATE(TYPE) \
VpfComparisonExpression* \
VpfComparisonExpression::Create(VpfUInt field, \
				Operator op, TYPE value) \
{ \
    if (op == EQ) { \
	const VpfThematicIndex* index = \
			VpfQuery::Table()->getThematicIndex(field); \
	if (index) \
	    return new VpfIndexExpression(index, value); \
	} \
    return new VpfMatchExpression(VpfQuery::Table(), field, op, value); \
}
OCE_CREATE(const char*);
OCE_CREATE(VpfInt);
OCE_CREATE(double);

// --------------------------------------------------------------------------
VpfIndexExpression::VpfIndexExpression(const VpfThematicIndex* index,
				       const char* value)
: _index(index),
  _type('T')
{
    _value.textval = VpfStrDup(value);
}

// --------------------------------------------------------------------------
VpfIndexExpression::VpfIndexExpression(const VpfThematicIndex* index,
				       VpfInt value)
: _index(index),
  _type('I')
{
    _value.intval = value;
}

// --------------------------------------------------------------------------
VpfIndexExpression::VpfIndexExpression(const VpfThematicIndex* index,
				       double value)
: _index(index),
  _type('R')
{
    _value.floatval = value;
}

// --------------------------------------------------------------------------
VpfSet*
VpfIndexExpression::evaluate(int& destroy)
{
    VpfSet* result = 0;
    destroy = 0;

    switch(_type) {
    case 'T':
	result = _index->getAssociated(_value.textval);
	break;
    case 'R':
	result = _index->getAssociated(_value.floatval);
	break;
    case 'I':
	result = _index->getAssociated(_value.intval);
	break;
    default:
	return 0;
    }

    // The value is not present in the index
    // this means no row matches the expression.
    if (result == 0) {
	destroy = 1;
	result = new VpfSet(0);
    }

    return result;
}

// --------------------------------------------------------------------------
VpfMatchExpression::VpfMatchExpression(VpfTable* table,
                                       VpfUInt field,
                                       Operator op,
                                       const char* textval)
: VpfComparisonExpression(1),
  _table(table),
  _field(field),
  _fieldType('\0'),
  _set(0),
  _op(op)
{
    _value.textval = VpfStrDup(textval);
    assertCompatibleTypes('T');
    initSet();
}

// --------------------------------------------------------------------------
VpfMatchExpression::VpfMatchExpression(VpfTable* table,
                                       VpfUInt field,
                                       Operator op,
                                       VpfInt intval)
: VpfComparisonExpression(1),
  _table(table),
  _field(field),
  _fieldType('\0'),
  _set(0),
  _op(op)
{
    _value.intval = intval;
    assertCompatibleTypes('I');
    initSet();
}

// --------------------------------------------------------------------------
VpfMatchExpression::VpfMatchExpression(VpfTable* table,
                                       VpfUInt field,
                                       Operator op,
                                       double floatval)
: VpfComparisonExpression(1),
  _table(table),
  _field(field),
  _fieldType('\0'),
  _set(0),
  _op(op)
{
    _value.floatval = floatval;
    assertCompatibleTypes('R');
    initSet();
}

// --------------------------------------------------------------------------
VpfMatchExpression::VpfMatchExpression(VpfTable* table,
                                       VpfUInt field,
                                       Operator op,
                                       VpfUInt fieldval)
: VpfComparisonExpression(1),
  _table(table),
  _field(field),
  _fieldType('\0'),
  _set(0),
  _op(op)
{
    _value.fieldval = fieldval;
    assertCompatibleTypes('A');
    initSet();
}

// --------------------------------------------------------------------------
VpfMatchExpression::VpfMatchExpression(VpfTable* table,
                                       VpfUInt field,
                                       Operator op,
                                       const VpfDate* dateval)
: VpfComparisonExpression(1),
  _table(table),
  _field(field),
  _fieldType('\0'),
  _set(0),
  _op(op)
{
    _value.dateval = 0; //dateval ? new VpfDate(*dateval) : 0;
    assertCompatibleTypes('D');
    initSet();
}

// --------------------------------------------------------------------------
VpfMatchExpression::~VpfMatchExpression()
{
    switch (_fieldType) {
    case 'T':
    case 'L':
    case 'M':
    case 'N':
	if (_value.textval)
	    delete [] _value.textval;
	break;
    case 'D':
	//if (_value.dateval) delete _value.dateval;
	break;
    default:;
    }
}

// --------------------------------------------------------------------------
void
VpfMatchExpression::initSet()
{
    if (_table)
	_set = new VpfSet(_table->getNRows()); 
}

// --------------------------------------------------------------------------
void
VpfMatchExpression::match(VpfRow* row)
{
    char* textval = 0;
    VpfInt intval;
    double floatval;

    int matches = 0;

    switch(_fieldType) {
    case 'T':
    case 'L':
    case 'M':
    case 'N':
	row->getTextField(_field, textval);

	switch(_op) {
	case EQ:
	    matches = !strcmp(textval, _value.textval);
	    break;
	case NE:
	    matches = strcmp(textval, _value.textval);
	    break;
	case LE:
	    matches = (strcmp(textval, _value.textval) <= 0);
	    break;
	case GE:
	    matches = (strcmp(textval, _value.textval) >= 0);
	    break;
	case LT:
	    matches = (strcmp(textval, _value.textval) < 0);
	    break;
	case GT:
	    matches = (strcmp(textval, _value.textval) > 0);
	    break;
	default:
	    matches = 0;
	}
	break;

    case 'F':
    case 'R':
	row->getFloatField(_field, floatval);
	switch(_op) {
	case EQ:
	    matches = (floatval == _value.floatval);
	    break;
	case NE:
	    matches = (floatval != _value.floatval);
	    break;
	case LE:
	    matches = (floatval <= _value.floatval);
	    break;
	case GE:
	    matches = (floatval >= _value.floatval);
	    break;
	case LT:
	    matches = (floatval < _value.floatval);
	    break;
	case GT:
	    matches = (floatval > _value.floatval);
	    break;
	default:
	    matches = 0;
	}
	break;
    case 'I':
    case 'S':
	row->getIntField(_field, intval);
	switch(_op) {
	case EQ:
	    matches = (intval == _value.intval);
	    break;
	case NE:
	    matches = (intval != _value.intval);
	    break;
	case LE:
	    matches = (intval <= _value.intval);
	    break;
	case GE:
	    matches = (intval >= _value.intval);
	    break;
	case LT:
	    matches = (intval < _value.intval);
	    break;
	case GT:
	    matches = (intval > _value.intval);
	    break;
	default:
	    matches = 0;
	}
	break;
    case 'D':
	matches = 0;
	break;
    default:
	matches = 0;
    };

    if (matches)
	_set->set(row->getRowNumber(), 1);
}

// --------------------------------------------------------------------------
int
VpfMatchExpression::assertCompatibleTypes(char valueType)
{
    VpfHeader* header = _table->getHeader(_field);
    char fieldType = _fieldType = header->getType();

    if (valueType == 'A') {
	// This is another field
	VpfHeader* fh = _table->getHeader(_value.fieldval);
	valueType = fh->getType();
    }
    switch(fieldType) {
    case 'T':
    case 'L':
    case 'M':
    case 'N':
	return ((valueType == 'T') ||
		(valueType == 'L') ||
		(valueType == 'M') ||
		(valueType == 'N'));
    case 'I':
    case 'S':
	return ((valueType == 'I') ||
		(valueType == 'S'));
    case 'F':
    case 'R':
	return ((valueType == 'F') ||
		(valueType == 'R'));
    default:
	return (fieldType == valueType);
    }
}

// --------------------------------------------------------------------------
VpfQuery::VpfQuery(VpfTable* table, const char* filter)
: _table(table),
  _nMatches(0),
  _matches(0),
  _expression(0)
{
    parse(filter);
}

// --------------------------------------------------------------------------
VpfQuery::~VpfQuery()
{
    if (_expression)
	delete _expression;
    if (_matches)
	delete [] _matches;
}

// --------------------------------------------------------------------------
void
VpfQuery::buildMatchArray(VpfUInt& i, VpfExpression* expression)
{
    if (expression->isMatch())
	_matches[i++] = (VpfMatchExpression*) expression;
    else {
	for (VpfUInt j = 0; j < expression->getNExpressions(); j++)
	    buildMatchArray(i, expression->getExpression(j));
    }
}

// --------------------------------------------------------------------------
int
VpfQuery::parse(const char* filter)
{
    _expression  = Parse(_table, filter);

    if (_expression) {
	_nMatches = _expression->getNMatches();
	_matches = new VpfMatchExpression*[_nMatches];
	VpfUInt i = 0;
	buildMatchArray(i, _expression);
    }
    return !_expression;
}
