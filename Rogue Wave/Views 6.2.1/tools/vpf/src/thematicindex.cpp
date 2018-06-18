// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/thematicindex.cpp
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
// Definition of the VpfThematicIndex feature class
// --------------------------------------------------------------------------

#include <vpf/thematicindex.h>
#include <vpf/file.h>
#include <vpf/string.h>
#include <string.h>

// --------------------------------------------------------------------------
VpfThematicIndex*
VpfThematicIndex::Open(const char* filename)
{
    VpfFile* file = new VpfFile(filename, "rb");
    if (!file || file->isBad())
	return 0;

    VpfInt nEntries = 0;
    char indexType = '\0';
    char elementType = '\0';
    VpfInt elementCount = 0;
    char idType = '\0';
    char ordered = '\0';

    file->seek(4, SEEK_SET);
    file->readInteger(&nEntries);
    file->seek(12, SEEK_SET);
    file->readText(&indexType, 'T', 1, 0);
    file->readText(&elementType, 'T', 1, 0);
    file->readInteger(&elementCount);
    file->readText(&idType, 'T', 1, 0);
    file->seek(56, SEEK_SET);
    file->readText(&ordered, 'T', 1, 0);

    // check the data type and data width are valid
    switch(elementType) {
    case 'T':
    case 'L':
    case 'M':
    case 'N':
	if (elementCount < 1) {
	    // An empty text index is nonsense
	    delete file;
	    return 0;
	}
	break;
    case 'I':
    case 'S':
    case 'F':
    case 'R':
	if (elementCount != 1) {
	    // According to the specification, only indexes
	    // on strings allow a elementCount greater than one.
	    delete file;
	    return 0;
	}
	break;
    default:
	delete file;
	return 0;
    }
    // check the id type is valid
    switch(idType) {
    case 'I':
    case 'S':
	break;
    default:
	delete file;
	return 0;
    }

    VpfThematicIndex* ti;
    switch (indexType) {
    case 'T':
	// This is legacy and even no more in the specification.
	// We assume this is an inverted list index.
    case 'I':
	ti = new VpfThematicInvertedIndex(elementType, elementCount,
					  nEntries, idType);
	break;
    case 'G':
	// This is legacy and even no more in the specification.
	// We assume this is a bit array index.
    case 'B':
	ti = new VpfThematicBitArrayIndex(elementType, elementCount, nEntries);
	break;
    default:
	delete file;
	return 0;
    }
    if (ti->readDirectory(file) || ti->readIndexData(file)) {
	delete file;
	delete ti;
	return 0;
    }
    delete file;
    return ti;
}

// --------------------------------------------------------------------------
VpfThematicIndex::VpfThematicIndex(char elementType,
				   VpfUInt elementCount, VpfUInt nElements)
: _elementType(elementType),
  _elementCount(elementCount),
  _nElements(nElements),
  _positions(0),
  _nRecords(0),
  _elements(0),
  _sets(0)
{
    _elements = new void*[nElements];
    _positions = new VpfUInt[nElements];
    _nRecords = new VpfUInt[nElements];
    _sets = new VpfSet*[nElements];
}

// --------------------------------------------------------------------------
VpfThematicIndex::~VpfThematicIndex()
{
    if (_elements) {
	for (VpfUInt i = 0; i < _nElements; i++) {
	    switch(_elementType) {
	    case 'T':
	    case 'L':
	    case 'M':
	    case 'N':
		delete [] (char*) _elements[i];
		break;
	    case 'I':
	    case 'S':
		delete [] (VpfInt*) _elements[i];
		break;
	    case 'F':
	    case 'R':
		delete [] (double*) _elements[i];
	    default:
		;
	    }
	}
	delete [] _elements;
    }

    if (_sets)
	delete [] _sets;
    if (_positions)
	delete [] _positions;
    if (_nRecords)
	delete [] _nRecords;
}

// --------------------------------------------------------------------------
int
VpfThematicIndex::readDirectory(VpfFile* file)
{
    VpfInt position = 0;
    VpfInt nRecords = 0;

    file->seek(60, SEEK_SET);

    for (VpfUInt i = 0; i < _nElements; i++) {
	switch(_elementType) {
	case 'T':
	case 'L':
	case 'M':
	case 'N':
	    _elements[i] = new char[_elementCount];
	    file->readText((char*) _elements[i], _elementType,
			   _elementCount, 0);
	    VpfStrTrim((char*) _elements[i]);
	    break;
	case 'I':
	case 'S':
	    _elements[i] = new VpfInt;
	    file->readInteger((VpfInt*) _elements[i], _elementType);
	    break;
	case 'F':
	case 'R':
	    _elements[i] = new double;
	    file->readFloat((double*) _elements[i], _elementType);
	    break;
	default:
	    // should never happen anyway
	    _elements[i] = 0;
	} // switch
	file->readInteger(&position);
	file->readInteger(&nRecords);
	if ((position < 0) || (nRecords < 0))
	    // Negative position or number of records is
	    // pure nonsense
	    return 1;

	_positions[i] = (VpfUInt) position;
	_nRecords[i] = (VpfUInt) nRecords;
    } // for

    return 0;
} // thematicIndex::readDirectory

// --------------------------------------------------------------------------
VpfSet*
VpfThematicIndex::getAssociated(const char* value) const
{
    if ((_elementType != 'T') &&
	(_elementType != 'L') &&
	(_elementType != 'M') &&
	(_elementType != 'N'))
	return 0;
    for (VpfUInt i = 0; i < _nElements; i++)
	if (!strncmp(value, (char*) _elements[i], _elementCount))
	    return getAssociatedFromIndex(i);
    return 0;
}

// --------------------------------------------------------------------------
VpfSet*
VpfThematicIndex::getAssociated(VpfInt value) const
{
    if ((_elementType != 'S') &&
	(_elementType != 'I'))
	return 0;
    for (VpfUInt i = 0; i < _nElements; i++)
	if (value == *((VpfInt*) _elements[i]))
	    return getAssociatedFromIndex(i);
    return 0;
}

// --------------------------------------------------------------------------
VpfSet*
VpfThematicIndex::getAssociated(double value) const
{
    if ((_elementType != 'F') &&
	(_elementType != 'R'))
	return 0;
    for (VpfUInt i = 0; i < _nElements; i++)
	if (value == *((double*) _elements[i]))
	    return getAssociatedFromIndex(i);
    return 0;
}


// --------------------------------------------------------------------------
VpfThematicInvertedIndex::VpfThematicInvertedIndex(char elementType,
                                                   VpfUInt elementCount,
                                                   VpfUInt nElements,
                                                   char IDType)
: VpfThematicIndex(elementType, elementCount, nElements),
  _IDType(IDType)
{
}

// --------------------------------------------------------------------------
VpfThematicInvertedIndex::~VpfThematicInvertedIndex()
{
}

// --------------------------------------------------------------------------
int
VpfThematicInvertedIndex::readIndexData(VpfFile* file)
{
    for (VpfUInt i = 0; i < _nElements; i++) {
	if (_nRecords[i] == 0) {
	    _sets[i] = new VpfSet(_positions[i] + 1);
	    _sets[i]->set(_positions[i], 1);
	} else {
	    VpfInt* tmp = new VpfInt[_nRecords[i]];
	    file->seek(_positions[i], SEEK_SET);
	    file->readInteger(tmp, _IDType, _nRecords[i]);

	    VpfInt max = tmp[0];
	    VpfUInt j;
	    for (j = 1; j < _nRecords[i]; j++)
		if (tmp[j] > max)
		    max = tmp[j];

	    _sets[i] = new VpfSet(max);
	    for (j = 0; j < _nRecords[i]; j++)
		// We substract one to the ID since IDs are in the
		// [1..n] range and sets are in the [0..n-1].
		_sets[i]->set(tmp[j] - 1, 1);

	    delete [] tmp;
	}
    }

    delete [] _positions; _positions = 0;
    delete [] _nRecords; _nRecords = 0;
    return 0;
}

// --------------------------------------------------------------------------
VpfThematicBitArrayIndex::VpfThematicBitArrayIndex(char elementType,
                                                   VpfUInt elementCount,
                                                   VpfUInt nElements)
: VpfThematicIndex(elementType, elementCount, nElements)
{
}

// --------------------------------------------------------------------------
VpfThematicBitArrayIndex::~VpfThematicBitArrayIndex()
{
}

// --------------------------------------------------------------------------
int
VpfThematicBitArrayIndex::readIndexData(VpfFile* file)
{
    for (VpfUInt i = 0; i < _nElements; i++) {
	char* ptr = new char[_nRecords[i]];
	_sets[i] = new VpfSet(_nRecords[i] * 8, ptr, 1);
	file->seek(_positions[i], SEEK_SET);
	file->readText(ptr, 'T', _nRecords[i], 0);
    }

    delete [] _positions; _positions = 0;
    delete [] _nRecords; _nRecords = 0;
    return 0;
}
