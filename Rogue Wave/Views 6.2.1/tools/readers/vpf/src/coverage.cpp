// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/coverage.cpp
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
// Definition of the VpfCoverage class
// --------------------------------------------------------------------------

#include <vpf/library.h>
#include <vpf/coverage.h>
#include <vpf/featureclass.h>
#include <vpf/feature.h>
#include <vpf/attribute.h>
#include <vpf/theme.h>
#include <vpf/string.h>
#include <vpf/date.h>
#include <vpf/error.h>
#include <vpf/table.h>
#include <vpf/vdt.h>
#include <vpf/file.h>

#if defined(ILVSTD)
# include <cstdio>
# include <cstring>
#else
# include <stdio.h>
# include <string.h>
#endif


#if defined(_WIN32) || defined(__TCPLUSPLUS__)
#include <io.h>
#define access _access
#else
#include <unistd.h>
#endif

// --------------------------------------------------------------------------
// FCA (Feature Class Attribute) table management
// --------------------------------------------------------------------------
class VpfFcaCursor
: public VpfCursor
{
public:
    VpfFcaCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfFcaCursor::VpfFcaCursor";
	VPF_IMPL_FIELD(Class, ID,     "ID",     1, I);
	VPF_IMPL_FIELD(Class, FClass, "FCLASS", 1, TLMN);
	VPF_IMPL_FIELD(Class, Type,   "TYPE",   1, T);
	VPF_IMPL_FIELD(Class, Descr,  "DESCR",  1, TLMN);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(FClass);
    VPF_DEF_FIELD(Type);
    VPF_DEF_FIELD(Descr);
    friend class VpfFcaRow;
};

// --------------------------------------------------------------------------
class VpfFcaRow
: public VpfRow
{
public:
    VpfFcaRow(VpfFcaCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfFcaCursor, FClass);
    VPF_QUERY_TEXTFIELD(VpfFcaCursor, Descr);
    char getType() const {
	const char* ptr =
	    getText(((VpfFcaCursor*)_cursor)->VPF_FIELDNAME(Type));
	return ptr
	    ? ptr[0]
	    : '\0';
    }
};

// --------------------------------------------------------------------------
VpfRow*
VpfFcaCursor::getNewRow()
{
    return new VpfFcaRow(this);
}

// --------------------------------------------------------------------------
// FCS (Feature Classes) table management
// --------------------------------------------------------------------------
class VpfFcsCursor
: public VpfCursor
{
public:
    VpfFcsCursor(VpfTable* table)
    : VpfCursor(table)
    {
	static const char* Class = "VpfFcsCursor::VpfFcsCursor";
	VPF_IMPL_FIELD(Class, ID,           "ID",            1, I);
	VPF_IMPL_FIELD(Class, FeatureClass, "FEATURE_CLASS", 1, TLMN);
	VPF_IMPL_FIELD(Class, Table1,       "TABLE1",        1, TLMN);
	VPF_IMPL_FIELD(Class, Table1Key,    "TABLE1_KEY",    0, TLMN);
	VPF_IMPL_FIELD(Class, ForeignKey,   "FOREIGN_KEY",   0, TLMN);
	VPF_IMPL_FIELD(Class, Table2,       "TABLE2",        1, TLMN);
	VPF_IMPL_FIELD(Class, Table2Key,    "TABLE2_KEY",    0, TLMN);
	VPF_IMPL_FIELD(Class, PrimaryKey,   "PRIMARY_KEY",   0, TLMN);
    }
    // ____________________________________________________________
    virtual VpfRow* getNewRow();
private:
    VPF_DEF_FIELD(ID);
    VPF_DEF_FIELD(FeatureClass);
    VPF_DEF_FIELD(Table1);
    VPF_DEF_FIELD(Table1Key);
    VPF_DEF_FIELD(ForeignKey);
    VPF_DEF_FIELD(Table2);
    VPF_DEF_FIELD(Table2Key);
    VPF_DEF_FIELD(PrimaryKey);
    friend class VpfFcsRow;
    friend class VpfCoverage;
};

// --------------------------------------------------------------------------
class VpfFcsRow
: public VpfRow
{
public:
    VpfFcsRow(VpfFcsCursor* cursor)
    : VpfRow(cursor)
    {}
    // ____________________________________________________________
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, FeatureClass);
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, Table1);
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, Table1Key);
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, ForeignKey);
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, Table2);
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, Table2Key);
    VPF_QUERY_TEXTFIELD(VpfFcsCursor, PrimaryKey);
};

// --------------------------------------------------------------------------
VpfRow*
VpfFcsCursor::getNewRow()
{
    return new VpfFcsRow(this);
}

// --------------------------------------------------------------------------
// VpfCoverage
// --------------------------------------------------------------------------
VpfCoverage::VpfCoverage(VpfLibrary* library,
                         char* name,
                         char* description,
                         VpfInt topolevel)
: _library(library),
  _name(name),
  _path(library ? library->getPath() : 0),
  _dir(library ? library->getPath() : 0),
  _description(description),
  _topologyLevel(topolevel),
  _nFeatureClasses(0),
  _featureClasses(0),
  _nThemes(0),
  _themes(0)
{
    _path += '/';
    _path += _name;
    if (initFeatureClasses())
	setBad();
    if (initThemes())
	setBad();
}

// --------------------------------------------------------------------------
VpfCoverage::~VpfCoverage()
{
    if (_themes) {
	for (VpfUInt i = 0; i < _nThemes; ++i)
	    if (_themes[i])
		delete _themes[i];
	delete [] _themes;
    }
    if (_featureClasses) {
	for (VpfUInt i = 0; i < _nFeatureClasses; i++)
	    if (_featureClasses[i])
		delete _featureClasses[i];
	delete [] _featureClasses;
    }
}

//-----------------------------------------------------------------------------
static const char* joinTypes[] = { ".ajt", ".ljt", ".rjt", ".njt", 0};


// --------------------------------------------------------------------------
char*
IsJoin(const char* path, const char* featureClass)
{
    char* tempfilename;
    tempfilename = new char[strlen(path) + strlen(featureClass) + 6];
    if (!tempfilename)
	return 0;

    const char** ptr = &joinTypes[0];
    while (*ptr) {
	strcpy(tempfilename, path);
	strcat(tempfilename, "/");
	strcat(tempfilename, featureClass);
	strcat(tempfilename, *ptr);

	FILE* file = VpfFile::OpenFile(tempfilename,"r");
	if(file) {
	    fclose(file);
	    strcpy(tempfilename, featureClass);
	    strcat(tempfilename, *ptr);
	    return tempfilename;
	}
	
	ptr++;
    }
    delete [] tempfilename;
    return 0;
}

// --------------------------------------------------------------------------
int 
VpfCoverage::initFeatureClasses()
{
    static const char* Class = "VpfCoverage::initFeatureClasses()";

    // A coverage contains a FCS (Feature Class Schema Table) and can
    // optionnaly contain a FCA (Feature Class Attribute Table).

    const char* featureClass;
    const char* featureTableName;
    const char* primitiveTableName;
    const char* featureTablePrimIdName;

    const char* joinTableName;
    const char* joinTableForeignKeyName;

    const char* description;

    char* buf2;
    char* buf3;

    char code;

    char* tempfilename = 0;

    VpfUInt nFcsRows = 0;

    VpfTable* fcaTable = 0;
    VpfFcaCursor* fcaCursor = 0;
    VpfFcaRow* fcaRow = 0;
    VpfUInt nFcaRows = 0;
    
    VpfUInt i = 0;
    VpfUInt j = 0;

    VpfString fcsPath(_path);
    fcsPath += "/fcs";
    VpfString fcaPath(_path);
    fcaPath += "/fca";

    char** fcNames = 0;
    VpfUInt* fcIndex = 0;
  
    VpfTable* fcsTable = new VpfTable(fcsPath);
    VpfFcsCursor* fcsCursor = 0;
    VpfFcsRow* fcsRow = 0;
    VpfFcsRow* fcsRow2 = 0;
    if (!fcsTable || fcsTable->isBad())
	goto error;
    if (!(fcsCursor = new VpfFcsCursor(fcsTable)) || fcsCursor->isBad())
	goto error;
    if (!(fcsRow = (VpfFcsRow*)fcsCursor->getNewRow()) || fcsRow->isBad())
	goto error;
    if (!(fcsRow2 = (VpfFcsRow*)fcsCursor->getNewRow()) || fcsRow2->isBad())
	goto error;

    nFcsRows = fcsCursor->getNRows();
    fcsCursor->setTrim(1);

    VpfErrorReporter::Push();
    fcaTable = new VpfTable(fcaPath);
    VpfErrorReporter::Pop();

    if (fcaTable && !fcaTable->isBad()) {
	fcaCursor = new VpfFcaCursor(fcaTable);
	if (!fcaCursor || fcaCursor->isBad())
	    goto error;
	fcaRow = (VpfFcaRow*) fcaCursor->getNewRow();
	if (!fcaRow || fcaRow->isBad())
	    goto error;
	nFcaRows = fcaCursor->getNRows();
	fcaCursor->setTrim(1);
    } else
	nFcaRows = 0;

    _nFeatureClasses = 0;

    if (nFcsRows) {
	// nFcsRow is the highest possible number of feature classes;
	// Of course, there are usually less since there are many joints.
	fcNames = new char*[nFcsRows];
	fcIndex = new VpfUInt[nFcsRows];
	if (!fcNames || !fcIndex)
	    goto error;

	for (i = 0; i < nFcsRows; i++) {
	    fcNames[i] = 0;
	    fcIndex[i] = 0;
	}
	fcsRow->setMapped(fcsCursor->VPF_FIELDNAME(FeatureClass), 1);
	for (i = 0; i < nFcsRows; i++) {
	    fcsCursor->getNextRow(fcsRow);
	    fcNames[i] = fcsRow->getFeatureClass();
	}
	// Remove duplicate entries of the FCS table
	for (i = 0; i < nFcsRows; i++) {
	    if (fcNames[i]) {
		for (j = i + 1; j < nFcsRows; j++) {
		    if (!VpfStrICmp(fcNames[i], fcNames[j])) {
			// Found same feature class
			delete [] fcNames[j];
			fcNames[j] = 0;
		    }
		}
		if (_nFeatureClasses != i) {
		    fcNames[_nFeatureClasses] = fcNames[i];
		    fcIndex[_nFeatureClasses] = i;
		    fcNames[i] = 0;
		}
		_nFeatureClasses++;
	    }
	}
    }
    
    if (_nFeatureClasses) {
	_featureClasses = new VpfFeatureClass*[_nFeatureClasses];

	for (i = 0; i < _nFeatureClasses; i++)
	    _featureClasses[i] = 0;

	fcsCursor->setCurrentRow(0);

	for (i = 0; i < _nFeatureClasses; i++) {
	    featureClass = fcNames[i];
	    description = 0;
	    featureTableName = 0;
	    featureTablePrimIdName = 0;
	    primitiveTableName = 0;
	    tempfilename = 0;
	    joinTableName = 0;
	    joinTableForeignKeyName = 0;
	    if (featureClass == 0) {
		VpfError* error = new VpfError(Class);
		error->getStream() << "Library " << getPath() << "; "
				   << "Internal error, feature class " << i
				   << "'s name is null and should not be.";
		VpfErrorReporter::Add(error);
		goto error;
	    }

	    tempfilename = IsJoin(_path, featureClass);

	    fcsCursor->setCurrentRow(fcIndex[i]);
	    if (fcsCursor->getNextRow(fcsRow))
		goto error;

	    featureTableName = fcsRow->getTable1();
	    primitiveTableName = fcsRow->getTable2();
	    code = primitiveTableName[strlen(primitiveTableName) - 2];
            
	    if (tempfilename) {
		// Feature class has a join table
		if ((code == 'j') || (code == 'J')) {
		    // Primitive table is a join table

		    joinTableName = primitiveTableName;
		    primitiveTableName = 0;
		    joinTableForeignKeyName = fcsRow->getTable1Key();
		    if (! joinTableForeignKeyName)
			joinTableForeignKeyName = fcsRow->getForeignKey();

		    for (; j < nFcsRows; j++) {
			fcsCursor->getNextRow(fcsRow2);

			buf2 = fcsRow2->getTable1();
			buf3 = fcsRow2->getTable2();

			if (!VpfStrICmp(buf2, joinTableName) &&
			    VpfStrICmp(buf3, featureTableName)) {
			    featureTablePrimIdName = buf3;
			    primitiveTableName = fcsRow2->getTable1Key();
			    if (! primitiveTableName)
				primitiveTableName = fcsRow2->getForeignKey();
			    break;
			}
		    } // for j
		} else {
		    // Primitive table is not a join table
		    joinTableName = tempfilename;
		    joinTableForeignKeyName = 0;
		    featureTablePrimIdName = fcsRow->getTable1Key();
		    if (! featureTablePrimIdName)
			featureTablePrimIdName = fcsRow->getForeignKey();
		}
	    } else {
		// Feature class has no join table
		joinTableName = 0;
		joinTableForeignKeyName = 0;
		featureTablePrimIdName = fcsRow->getTable1Key();
		if (! featureTablePrimIdName)
		    featureTablePrimIdName = fcsRow->getForeignKey();
	    }

	    if (fcaCursor) {
		fcaCursor->setCurrentRow(0);
		for (j = 0; j < nFcaRows; j++) {
		    if (fcaCursor->getNextRow(fcaRow))
			break;
		    if (!VpfStrICmp(featureClass, fcaRow->getFClass())) {
			description = fcaRow->getDescr();
			break;
		    }
		}
	    }
	    _featureClasses[i] = new VpfFeatureClass(this,
						     featureClass,
						     description,
						     featureTableName,
						     featureTablePrimIdName,
						     primitiveTableName,
						     joinTableName,
						     joinTableForeignKeyName);

	    if (tempfilename)
		delete [] tempfilename;
	    tempfilename = 0;
	} // for i
    } // if _nFeatureClasses

    if (fcNames) {
	for (i = 0; i < nFcsRows; i++)
	    if (fcNames[i]) delete [] fcNames[i];
	delete [] fcNames;
    }

    if (fcIndex)
	delete [] fcIndex;

    delete fcaRow;
    delete fcaCursor;
    delete fcaTable;

    delete fcsRow2;
    delete fcsRow;
    delete fcsCursor;
    delete fcsTable;

    return 0;

error:
    if (fcNames) {
	for (i = 0; i < nFcsRows; i++)
	    if (fcNames[i])
		delete [] fcNames[i];
	delete [] fcNames;
    }

    if (fcIndex)
	delete [] fcIndex;

    if (fcaRow)
	delete fcaRow;
    if (fcaCursor)
	delete fcaCursor;
    if (fcaTable)
	delete fcaTable;

    if (fcsRow2)
	delete fcsRow2;
    if (fcsRow)
	delete fcsRow;
    if (fcsCursor)
	delete fcsCursor;
    if (fcsTable)
	delete fcsTable;

    if (tempfilename)
	delete [] tempfilename;

    return 1;
}

// --------------------------------------------------------------------------
int 
VpfCoverage::initThemes()
{
    VpfTable* cvdtTable = 0;
    VpfString cvdt(_path);
    cvdt += "/char.vdt";
    VpfCharVdtCursor* cvdtCursor = 0;
    VpfCharVdtRow* cvdtRow = 0;
    VpfErrorReporter::Push();
    cvdtTable = new VpfTable(cvdt);
    VpfErrorReporter::Pop();
    if (!cvdtTable || cvdtTable->isBad()) {
	delete cvdtTable;
	cvdtTable = 0;
    }
    if (cvdtTable) {
	cvdtCursor = new VpfCharVdtCursor(cvdtTable);
	if (!cvdtCursor || cvdtCursor->isBad()) {
	    delete cvdtCursor;
	    cvdtCursor = 0;
	    delete cvdtTable;
	    cvdtTable = 0;
	}
	if (cvdtCursor) {
	    cvdtCursor->setTrim(1);
	    cvdtRow = (VpfCharVdtRow*)cvdtCursor->getNewRow();
	    if (!cvdtRow || cvdtRow->isBad()) {
		delete cvdtRow;
		cvdtRow = 0;
		delete cvdtCursor;
		cvdtCursor = 0;
		delete cvdtTable;
		cvdtTable = 0;
	    }
	}
    }
    VpfTable* ivdtTable = 0;
    VpfString ivdt(_path);
    ivdt += "/int.vdt";
    VpfIntVdtCursor* ivdtCursor = 0;
    VpfIntVdtRow* ivdtRow = 0;
    VpfErrorReporter::Push();
    ivdtTable = new VpfTable(ivdt);
    VpfErrorReporter::Pop();
    if (!ivdtTable || ivdtTable->isBad()) {
	delete ivdtTable;
	ivdtTable = 0;
    }
    if (ivdtTable) {
	ivdtCursor = new VpfIntVdtCursor(ivdtTable);
	if (!ivdtCursor || ivdtCursor->isBad()) {
	    delete ivdtCursor;
	    ivdtCursor = 0;
	    delete ivdtTable;
	    ivdtTable = 0;
	}
	if (ivdtCursor) {
	    ivdtCursor->setTrim(1);
	    ivdtRow = (VpfIntVdtRow*)ivdtCursor->getNewRow();
	    if (!ivdtRow || ivdtRow->isBad()) {
		delete ivdtRow;
		ivdtRow = 0;
		delete ivdtCursor;
		ivdtCursor = 0;
		delete ivdtTable;
		ivdtTable = 0;
	    }
	}
    }
    VpfUInt cnRows = cvdtTable
	? cvdtTable->getNRows()
	: 0;
    VpfUInt inRows = ivdtTable
	? ivdtTable->getNRows()
	: 0;
    VpfUInt currentTheme = 0;
    if (cnRows || inRows) {
	_themes = new VpfTheme* [cnRows+inRows];
	VpfUInt loop;
	for (loop = 0; loop < cnRows; loop++) {
	    cvdtCursor->getNextRow(cvdtRow);
	    for (VpfUInt fIdx = 0; fIdx < _nFeatureClasses; fIdx++) {
		if (!strcmp(cvdtRow->getTable(),
			    _featureClasses[fIdx]->getTable())) {
		    _themes[currentTheme++] =
			new VpfTheme(_featureClasses[fIdx],
				     cvdtRow->getAttribute(),
				     new VpfValue(cvdtRow->getDescription(),
						  cvdtRow->getValue()));
		    break;
		}
	    }
	}
	for (loop = 0; loop < inRows; loop++) {
	    ivdtCursor->getNextRow(ivdtRow);
	    for (VpfUInt fIdx = 0; fIdx < _nFeatureClasses; fIdx++) {
		if (!strcmp(ivdtRow->getTable(),
			    _featureClasses[fIdx]->getTable())) {
		    _themes[currentTheme++] =
			new VpfTheme(_featureClasses[fIdx],
				     ivdtRow->getAttribute(),
				     new VpfValue(ivdtRow->getDescription(),
						  ivdtRow->getValue()));
		    break;
		}
	    }
	}
    }
    _nThemes = currentTheme;
    delete ivdtRow;
    delete ivdtCursor;
    delete ivdtTable;
    delete cvdtRow;
    delete cvdtCursor;
    delete cvdtTable;
    return 0;
}

// --------------------------------------------------------------------------
int
VpfCoverage::isTiled() const
{
    return (!VpfStrICmp(_name, "libref") ||
	    !VpfStrICmp(_name, "tileref"))
	? 0
	: _library->isTiled();
}

// --------------------------------------------------------------------------
VpfFeatureClass*
VpfCoverage::getFeatureClass(const char* name) const
{
    for (VpfUInt i = 0; i < _nFeatureClasses; i++)
	if (!strcmp(_featureClasses[i]->getName(), name))
	    return _featureClasses[i];
    return 0;
}
