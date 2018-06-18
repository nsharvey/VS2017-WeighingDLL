// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/table.cpp
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
// Definition of the VpfTable class
// --------------------------------------------------------------------------

#include <vpf/table.h>
#include <vpf/file.h>
#include <vpf/string.h>
#include <vpf/index.h>
#include <vpf/row.h>
#include <vpf/header.h>
#include <vpf/error.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

const char VpfTable::ComponentSeparator = ';';
const char VpfTable::LineContinue = '\\';
const char VpfTable::Comment = '#';
const char VpfTable::EndOfField = ':';
const char VpfTable::FieldCount = '=';
const char VpfTable::FieldSeparator = ',';
const char VpfTable::VariableCount = '*';

// --------------------------------------------------------------------------
VpfTable::VpfTable(const char* path)
: _path(0),
  _name(0),
  _description(0),
  _narrativeTableName(0),
  _isBad(0),
  _index(0),
  _nFields(0),
  _headers(0),
  _nRows(0),
  _recordLength(-1),
  _dataDefinitionLength(0),
  _byteOrder(Vpf::LSB)
{
    static const char* Class = "VpfTable::VpfTable";
    VpfError* error = 0;

    _path = VpfStrDup(path);

    char* name = strrchr(_path, '/');
    _name = VpfStrDup(name
		      ? (name + 1)
		      : _path);

    VpfErrorReporter::Push();
    VpfFile* tableFile = new VpfFile(_path, "rb");
    VpfErrorReporter::Pop();

    if (!tableFile || tableFile->isBad()) {
	delete tableFile;
	error = new VpfError(Class);
	error->getStream() << "Table file " << _path
			   << " could not be opened.";
	VpfErrorReporter::Add(error);
	setBad();
	return;
    }

    VpfUInt tableSize = (VpfUInt)tableFile->length();

    if (parseDataDefinition(tableFile)) {
	error = new VpfError(Class);
	error->getStream() << "Error while parsing the header of table "
			   << _path << ".";
	VpfErrorReporter::Add(error);
	setBad();
	return;
    }

    if (_recordLength > 0) {
	_nRows = (tableSize - _dataDefinitionLength) / _recordLength;
	_index = 0;
    } else {
	char* indexFileName = VpfStrDup(_path);
	size_t indexFNLength = strlen(indexFileName);

	if (indexFileName[indexFNLength - 1] == '.') {
	    if (!VpfStrICmp(_name, "FCS")) // Index for FCS is FCZ
		indexFileName[indexFNLength - 2] = 'z';
	    else
		indexFileName[indexFNLength - 2] = 'x';
	} else {
	    if (!VpfStrICmp(_name, "FCS")) // Index for FCS is FCZ
		indexFileName[indexFNLength - 1] = 'z';
	    else
		indexFileName[indexFNLength - 1] = 'x';
	}

	VpfFile* indexFile = new VpfFile(indexFileName, "rb");
	delete [] indexFileName;

	if (!indexFile || indexFile->isBad()) {
	    error = new VpfError(Class);
	    error->getStream() << "Table " << _path
			       << " has no index.";
	    VpfErrorReporter::Add(error);
	    setBad();
	} else {
	    VpfInt dummy = -1;
	    // We need to propagate the swap attribute
	    indexFile->setSwap(tableFile->isSwapping());
	    int result = indexFile->readInteger(&dummy);
	    if (result) {
		error = new VpfError(Class);
		error->getStream() << "The index for table " << _path
				   << " is damaged: read error.";
		VpfErrorReporter::Add(error);
		setBad();
	    } else
	    if (dummy < 0) {
		error = new VpfError(Class);
		error->getStream() << "The index for table " << _path
				   << " is damaged: negative number of rows.";
		VpfErrorReporter::Add(error);
		setBad();
		return;
	    }

	    if (!result && (dummy >= 0)) {
		_nRows = (VpfUInt)dummy;

		if (indexFile->readInteger(&dummy)) {
		    error = new VpfError(Class);
		    error->getStream() << "The index for table " << _path
				       << " is damaged: read error";
		    VpfErrorReporter::Add(error);
		    setBad();
		} else {
		    _index = new VpfIndex[_nRows + 1];

		    for (VpfUInt i = 0; i < _nRows; i++) {
			VpfInt position = -1;
			VpfInt length = -1;

			indexFile->readInteger(&position);
			indexFile->readInteger(&length);

			if ((position < 0) || (length < 0)) {
			    error = new VpfError(Class);
			    error->getStream() << "The index for table "
					       << _path
					       << " is damaged: bad entry";
			    VpfErrorReporter::Add(error);
			    setBad();
			    break;
			}
			_index[i].setPosition(position);
			_index[i].setLength(length);
		    }
		}
	    }
	}
	delete indexFile;
    }
    delete tableFile;
}

// --------------------------------------------------------------------------
VpfTable::~VpfTable()
{
    if (_name)
	delete [] _name;
    if (_path)
	delete [] _path;
    if (_description)
	delete [] _description;
    if (_narrativeTableName)
	delete [] _narrativeTableName;

    if (_index)
	delete [] _index;

    if (_headers) {
	for (VpfUInt i = 0; i < _nFields; i++)
	    if (_headers[i])
		delete _headers[i];
	delete [] _headers;
    }
}

// --------------------------------------------------------------------------
int
VpfTable::IsNull(const char* text)
{
    return (!strcmp(text, "-") ||
	    !strcmp(text, "--") ||
	    !strncmp(text, "N/A", 3))
	? 1
	: 0;
}

// --------------------------------------------------------------------------
long
VpfTable::getRowPosition(VpfUInt i) const
{
    return _index
	? _index[i].getPosition()
	: _dataDefinitionLength + _recordLength * i;
}

// --------------------------------------------------------------------------
unsigned int
VpfTable::getRowLength(VpfUInt i) const
{
    return _index
	? _index[i].getLength()
	: _recordLength;
}

// --------------------------------------------------------------------------
int
VpfTable::parseDataDefinition(VpfFile* tableFile)
{
    static const char* Class = "VpfTable::parseDataDefinition";
    VpfError* error = 0;
    VpfUInt n, i;
    VpfUInt p;
    char *buf, byte; /*temporary storage */

    int status = 0;
    VpfInt dataDefinitionLength = 0;
    
    // Skip the first long integer and read byte order
    tableFile->seek(4, SEEK_SET);
    tableFile->readText(&byte);

    _byteOrder = Vpf::LSB; // Default byte order
    if ((byte == 'M') || (byte == 'm'))
	_byteOrder = Vpf::MSB;
    tableFile->setSwap(_byteOrder != Vpf::MachineByteOrder);
    tableFile->rewind();

    // Read data definition length and skip byteorder
    // and semicolon separator
    tableFile->readInteger(&dataDefinitionLength);

    if (dataDefinitionLength < 0) {
	// ??
    }

    /* header with first 4 bytes */
    _dataDefinitionLength = dataDefinitionLength + 4;

    buf = new char[dataDefinitionLength + 1];
    tableFile->readText(buf, 'T', dataDefinitionLength);

    const char* stringGot = 0;
 
    p = 2;
    stringGot = GetString(p, buf, ComponentSeparator);
    _description = VpfStrDup(stringGot);
    VpfStrTrim(_description);

    stringGot = GetString(p, buf, ComponentSeparator);
    _narrativeTableName = VpfStrDup(stringGot);
    VpfStrTrim(_narrativeTableName);
    // Find out how many fields there are
    n = 0;
    for (i = p; i < (VpfUInt) dataDefinitionLength; i++)
	if (buf[i] == LineContinue)
	    i++;	// skip past line continue, and next character
	else
	if (buf[i] == EndOfField) // Found end of field
	    n++; // Increment nfields
	else
	if (buf[i] == Comment) // Skip past comments
	    while ((buf[i] != LineContinue) &&
		   (buf[i] != EndOfField) &&
		   (buf[i] != '\0'))
		i++;

    _nFields = n;
    _headers = new VpfHeader*[n+1];

    for (i = 0; i < n; i++)
	_headers[i] = 0;

    _recordLength = 0;

    VpfInt count = 0;
    for (i = 0; i < n; i++) {
	_headers[i] = new VpfHeader(this);

	_headers[i]->setName(GetString(p, buf, FieldCount));
	_headers[i]->setType(toupper(GetChar(p, buf)));
	_headers[i]->setCount(GetNumber(p, buf, FieldSeparator));

	if ((i == 0) && VpfStrICmp(_headers[0]->getName(), "ID")) {
	    error = new VpfError(Class);
	    error->getStream() << "Table " << _path
			       << " is corrupted (first field is not ID).";
	    VpfErrorReporter::Add(error);
	    return 1;
	}
	
	if ((count = _headers[i]->getCount()) == -1)
	    _recordLength = -1;
	
  	status = 0;
  	switch (_headers[i]->getType()) {
	case 'I':
	    if (_recordLength >= 0)
		_recordLength += 4 * count;
	    break;
	case 'S':
	    if (_recordLength >= 0)
		_recordLength += 2 * count;
	    break;
  	case 'F':
	    if (_recordLength >= 0)
		_recordLength += 4 * count;
	    break;
	case 'R':
	    if (_recordLength >= 0)
		_recordLength += 8 * count;
	    break;
	case 'T':
	    if (_recordLength >= 0)
		_recordLength += count;
	    break;
	case 'C':
	    if (_recordLength >= 0)
		_recordLength += 8 * count;
	    break;
	case 'B':
	    if (_recordLength >= 0)
		_recordLength += 16 * count;
	    break;
	case 'Z':
	    if (_recordLength >= 0)
		_recordLength += 12 * count;
	    break;
	case 'Y':
	    if (_recordLength >= 0)
		_recordLength += 24 * count;
	    break;
	case 'D':
	    if (_recordLength >= 0)
		_recordLength += 20 * count;
	    break;
	case 'K':
	    _recordLength = -1;
	    break;
	case 'X':
	    break;

	default:
	    //VpfError("VpfTable::parseDataDef: no such type < %c >", _header[i].getType());
	    status = 1;
	    break;
	} /* switch */
	
	if (status)
	    return 0;
	
	_headers[i]->setKeyType(GetChar(p, buf));
	_headers[i]->setDescription(GetString(p, buf, FieldSeparator));
	_headers[i]->setValueDescriptionTableName(GetString(p, buf,
							    FieldSeparator));
	if (p >= (VpfUInt) dataDefinitionLength || buf[p] == EndOfField) {
	    _headers[i]->setThematicIndexTableName("-");
	}
	else
	    _headers[i]->setThematicIndexTableName(GetString(p, buf,
							 FieldSeparator));
	if (p >= (VpfUInt) dataDefinitionLength || buf[p] == EndOfField) {
	    _headers[i]->setNarrativeTableName("-");
	}
	else
	    _headers[i]->setNarrativeTableName(GetString(p, buf,
						     FieldSeparator));

	if(p >= (VpfUInt) dataDefinitionLength)
	    break;
	
	p += 1; /* eat semicolon */
    }

    delete [] buf;

    return 0;
}

// --------------------------------------------------------------------------
VpfHeader*
VpfTable::getHeader(VpfUInt i) const
{
    return _headers[i];
}

// --------------------------------------------------------------------------
const VpfThematicIndex* 
VpfTable::getThematicIndex(VpfUInt i) const
{
    return _headers[i]->getThematicIndex();
}

// --------------------------------------------------------------------------
VpfInt
VpfTable::getFieldPosition(const char* name) const
{
    for (VpfUInt i = 0; i < _nFields; i++)
	if (!VpfStrICmp(name, _headers[i]->getName()))
	    return i;
    return -1;
}

// --------------------------------------------------------------------------
const char*
VpfTable::CopyToDelimiter(VpfUInt& ind, char* src, char delimiter)
{
#if 1
    static char		staticbuf[1024];
#else
    static VpfString staticbuf(128);
#endif

    VpfUInt i, skipchar;
    char* temp;

#if 1
    staticbuf[0] = 0;
#else
    staticbuf = "";
#endif

    // remove all blanks ahead of good data
    skipchar = 0 ;
    while (src[skipchar]
	   && ((src[skipchar] == ' ') || (src[skipchar] == '\t')))
	skipchar++ ;

    temp = &src[skipchar];
  
    // If the first character is a COMMENT, goto LINE_CONTINUE
    if (*temp == Comment) {
	while ((*temp != LineContinue) && (*temp != EndOfField) && *temp) {
	    temp++ ;
	    skipchar++ ;
	}
	skipchar++ ;
	temp++ ;		// skip past LC, EOF, or NULL
    }

    if (*temp == '\"') { // If field is quoted, do no error checks
	temp++ ; 	  // skip past quote character
	skipchar++ ;  // update the position pointer

	for (i=0 ; *temp; temp++, i++) {
	    if ((*temp == LineContinue) || (*temp == '\t')) {
		temp++ ;
		skipchar++ ;
	    } else
	    if (*temp == '\"' )
		break;

	    // Now copy the char into the output string
#if 1
	    {
		size_t index = strlen(staticbuf);
		staticbuf[index++] = *temp;
		staticbuf[index++] = 0;
	    }
#else
	    staticbuf += *temp ;
#endif
	}

	ind += (i + skipchar + 2);	// Increment position locate past
	return staticbuf; 	        // quote and semicolon
    }

    // search for delimiter to end, or end of string
    i=0;	// initialize
    if (*temp != EndOfField) {	// backward compatability check
	for (i = 0; *temp; temp++, i++) { // Stop on NULL
	    if (((*temp == LineContinue) && (*(temp+1) == '\n')) ||
		(*temp == '\t')) {
		temp++;
		skipchar++;
	    } else
	    if (*temp == delimiter)
		break ;    // break for delimiter 
	    
	    // Now copy the char into the output string
#if 1
	    { size_t index = strlen(staticbuf);
	    staticbuf[index++] = *temp;
	    staticbuf[index++] = 0;
	    }
#else
	    staticbuf += *temp;
#endif
	}

	// Eat the delimiter from ind also
	ind += (i + skipchar + 1);	// Increment position locate
    }

    return staticbuf;
}

// --------------------------------------------------------------------------
const char*
VpfTable::GetString(VpfUInt& ind, char* src, char delimit)
{
    const char* temp = CopyToDelimiter(ind, &src[ind], delimit);
    if (IsNull(temp))
	return 0;
    return temp;
}

// --------------------------------------------------------------------------
char
VpfTable::GetChar(VpfUInt& ind, char* src)
{
    char temp;
    while ((src[ind] == ' ') || (src[ind] == '\t'))
	ind++;
    temp  = src[ind];
    ind += 2;
    return temp;
}

// --------------------------------------------------------------------------
VpfInt
VpfTable::GetNumber(VpfUInt& ind, char* src, char delemit)
{
    const char* temp  = CopyToDelimiter(ind, &src[ind], delemit);
    return !strchr(temp, VariableCount)
	? atoi(temp)
	: -1;
}
