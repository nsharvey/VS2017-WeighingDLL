// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/file.cpp
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
// Definition of the VpfFile class
// --------------------------------------------------------------------------

#include <vpf/file.h>
#include <vpf/vpf.h>
#include <vpf/coordinate.h>
#include <vpf/date.h>
#include <vpf/tripletid.h>
#include <vpf/error.h>

#if defined(ILVSTD)
# include <cstring>
#else
# include <string.h>
#endif

// --------------------------------------------------------------------------
extern char* DowncaseString(char*);

FILE*
VpfFile::OpenFile(const char* name, const char* mode)
{
    FILE* file = fopen(name, mode);
    if (!file) {
	size_t l = strlen(name);
	char* chcase = strcpy(new char[l+2], name);
	int hasDot = 0;
	char* p;
	for (p = chcase; *p; p++)
	    if ((*p >= 'a') && (*p <= 'z'))
		*p -= 'a'-'A';
	    else
	    if (*p == '.')
		hasDot = 1;
	file = fopen(chcase, mode);
	if (file) {
	    delete [] chcase;
	    return file;
	}
	if (!hasDot) {
	    chcase[l]   = '.';
	    chcase[l+1] = 0;
	    file = fopen(chcase, mode);
	    if (file) {
		delete [] chcase;
		return file;
	    }
	}
	chcase[l]   = 0;
	for (p = chcase; *p; p++)
	    if ((*p >= 'A') && (*p <= 'Z'))
		*p += 'a'-'A';
	file = fopen(chcase, mode);
	if (file) {
	    delete [] chcase;
	    return file;
	}
	if (!hasDot) {
	    chcase[l]   = '.';
	    chcase[l+1] = 0;
	    file = fopen(chcase, mode);
	    delete [] chcase;
	    return file;
	}
	delete [] chcase;
    }
    return file;
}

// --------------------------------------------------------------------------
VpfFile::VpfFile(const char* name, const char* mode)
: _swap(0)
{
    _file = OpenFile(name, mode);

    if (!_file) {
	VpfError* error = new VpfError("VpfFile::VpfFile");
	error->getStream() << "The file " << name << " could not be opened.";
	VpfErrorReporter::Add(error);
	setBad();
    }
}

// --------------------------------------------------------------------------
VpfFile::~VpfFile()
{
    if (_file)
	fclose(_file);
}

// --------------------------------------------------------------------------
int
VpfFile::readText(char* textValue, char,
		  VpfUInt count, int trailingNull)
{
    int returnCode = 0;
    VpfError* error = 0;

    if (::fread(textValue, sizeof(char), count, _file) == count) {
	if (trailingNull)
	    textValue[count] = '\0';
    } else {
	error = new VpfError("VpfFile::readText");
	error->getStream() << "A file error occured.";
	VpfErrorReporter::Add(error);
	returnCode = 1;
    }
    return returnCode;
}

// --------------------------------------------------------------------------
int
VpfFile::readInteger(VpfInt* intValue, char type, VpfUInt count)
{
    VpfUInt i = 0;
    VpfError* error = 0;
    int returnCode = 0;

    switch(type) {
    case 'I':
	if (::fread((char*)intValue, sizeof(VpfInt), count, _file) != count) {
	    error = new VpfError("VpfFile::readInteger");
	    error->getStream() << "A file error occured.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	} else
	if (_swap)
	    for (i = 0; i < count; i++)
		Vpf::SwapFour(&intValue[i]);
	break;
    case 'S':
	for (i = 0; i < count; i++) {
	    short int value;
	    if (::fread((char*)&value, sizeof(short int), 1, _file) != 1) {
		error = new VpfError("VpfFile::readText");
		error->getStream() << "A file error occured.";
		VpfErrorReporter::Add(error);
		returnCode = 1;
		break;
	    }
	    if (_swap)
		Vpf::SwapTwo(&value);
	    intValue[i] = value;
	}
	break;

    default:
	error = new VpfError("VpfCursor::readInteger");
	error->getStream() << "Method invoked with invalid type argument: "
			   << type << ".";
	VpfErrorReporter::Add(error);
	returnCode = 1;
    }

    return returnCode;
}

// --------------------------------------------------------------------------
int
VpfFile::readFloat(double* doubleValue, char type, VpfUInt count)
{
    VpfUInt i = 0;
    VpfError* error = 0;
    int returnCode = 0;
    float value = 0.0;

    switch(type) {
    case 'L':
	if (::fread((char*)doubleValue, sizeof(double), count, _file) != count) {
	    error = new VpfError("VpfFile::readFloat");
	    error->getStream() << "A file error occured.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	} else
	if (_swap)
	    for (i = 0; i < count; i++)
		Vpf::SwapEight(&doubleValue[i]);
	break;

    case 'F':
	for (i = 0; i < count; i++) {
	    if (::fread((char*)&value, sizeof(float), 1, _file) != 1) {
		error = new VpfError("VpfFile::readFloat");
		error->getStream() << "A file error occured.";
		VpfErrorReporter::Add(error);
		returnCode = 1;
		break;
	    }
	    if (_swap)
		Vpf::SwapFour(&value);
	    doubleValue[i] = value;
	}
	break;

    default:
	error = new VpfError("VpfFile::readFloat");
	error->getStream() << "Method invokation with invalid type argument: "
			   << type << ".";
	VpfErrorReporter::Add(error);
	returnCode = 1;
    }
    return returnCode;
}

// --------------------------------------------------------------------------
int
VpfFile::readDate(VpfDate* date, VpfUInt count)
{
    char tmp[20];
    VpfError* error = 0;
    int returnCode = 0;

    for (VpfUInt i = 0; i < count; i++) {
	if (::fread(tmp, 20, 1, _file) != 1) {
	    error = new VpfError("VpfFile::readFloat");
	    error->getStream() << "A file error occured.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	    break;
	}
	date[i].set(tmp);
    }
    return returnCode;
}

// --------------------------------------------------------------------------
int
VpfFile::readTripletPart(int size, VpfInt& value)
{
    value = 0;
    char tmp[4];
    VpfError* error = 0;
    int returnCode = 0;

    switch(size) {
    case 0:
	break;
    case 1:
	if (::fread(tmp, 1, 1, _file) != 1) {
	    error = new VpfError("VpfFile::readTripletPart");
	    error->getStream() << "A file error occured.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	} else
	    value = ((unsigned char*) tmp)[0];
	break;
    case 2:
	if (::fread(tmp, 2, 1, _file) != 1) {
	    error = new VpfError("VpfFile::readTripletPart");
	    error->getStream() << "A file error occured.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	} else {
	    if (_swap)
		Vpf::SwapTwo(tmp);
	    value = ((unsigned short*)tmp)[0];
	}
	break;
    case 4:
	if (::fread(tmp, 4, 1, _file) != 1) {
	    error = new VpfError("VpfFile::readTripletPart");
	    error->getStream() << "A file error occured.";
	    VpfErrorReporter::Add(error);
	    returnCode = 1;
	} else {
	    if (_swap)
		Vpf::SwapFour(tmp);
	    value = ((unsigned int*)tmp)[0];
	}
	break;
    default:
	error = new VpfError("VpfFile::readTripletPart");
	error->getStream() << "Method invokation with invalid argument size: ";
	error->getStream() << size << ".";
	VpfErrorReporter::Add(error);
	returnCode = 1;
    }

    return returnCode;
}

// --------------------------------------------------------------------------
int
VpfFile::readTripletID(VpfTripletID* triplet, VpfUInt count)
{
    unsigned char size;
    VpfError* error = 0;
    int returnCode = 0;

    if (::fread((char*)&size, 1, 1, _file) != 1) {
	error = new VpfError("VpfFile::readTripletID");
	error->getStream() << "A file error occured.";
	VpfErrorReporter::Add(error);
	returnCode = 1;
    } else {
	VpfInt ID;
	VpfInt tileID;
	VpfInt extID;
	VpfInt dummy;

	for (VpfUInt i = 0; i < count; i++) {
	    if (readTripletPart((size & 0xC0) >> 6, ID) ||
		readTripletPart((size & 0x30) >> 4, tileID) ||
		readTripletPart((size & 0x0C) >> 2, extID) ||
		readTripletPart((size & 0x03), dummy))
		returnCode = 1;
	    else
		triplet[i].set(ID, tileID, extID);
	}
    }
    return returnCode;
}

// --------------------------------------------------------------------------
int
VpfFile::readCoordinate(VpfCoordinate* coordinates, char type, VpfUInt count)
{
    float f[3];
    double d[3];
    VpfUInt i = 0;
    VpfError* error = 0;
    int returnCode = 0;
    VpfUInt icount = 0;

    switch(type) {
    case 'C':
    case 'Z':
	for (i = 0; i < count; i++) {
	    icount = (type == 'C') ? 2 : 3;
	    if (::fread((char*)f, sizeof(float), icount, _file) == icount) {
		if (_swap) {
		    Vpf::SwapFour(&f[0]);
		    Vpf::SwapFour(&f[1]);
		}
		coordinates[i].set(f[0], f[1]);
	    } else {
		error = new VpfError("VpfFile::readCoordinate");
		error->getStream() << "A file error occured.";
		VpfErrorReporter::Add(error);
		returnCode = 1;
	    }
	}
	break;
    case 'B':
    case 'Y':
	for (i = 0; i < count; i++) {
	    icount = (type == 'B') ? 2 : 3;
	    if (::fread((char*)d, 8, icount, _file) == icount) {
		if (_swap) {
		    Vpf::SwapEight(&d[0]);
		    Vpf::SwapEight(&d[1]);
		}
		coordinates[i].set(d[0], d[1]);
	    } else {
		error = new VpfError("VpfFile::readCoordinate");
		error->getStream() << "A file error occured.";
		VpfErrorReporter::Add(error);
		returnCode = 1;
	    }
	}
	break;
    default:
	error = new VpfError("VpfFile::readCoordinate");
	error->getStream() << "Method invoked with invalid argument type: "
			   << type << ".";
	VpfErrorReporter::Add(error);
	returnCode = 1;
    }

    return returnCode;
}
