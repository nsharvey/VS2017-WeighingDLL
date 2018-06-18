// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57divrecord.h
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
// --------------------------------------------------------------------------
#ifndef __Ilv_S57Divrecord_H
#define __Ilv_S57Divrecord_H

#include <ilviews/maps/attrprop.h>
#include <ilviews/maps/attribute/stringattr.h>

#include <ilviews/maps/format/s57/s57record.h>
#include <ilviews/maps/format/s57/s57hash.h>
#include <ilviews/maps/format/s57/i8211record.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#define ILVS57_AGENCY_ATTR   "Agency"
#define ILVS57_ID_ATTR       "Id"
#define ILVS57_CODE_ATTR     "Code"
#define ILVS57_GROUP_ATTR    "Group"
#define ILVS57_TYPE_ATTR     "PrimType"
#define ILVS57_CODENAME_ATTR "CodeName"
#define ILVS57_ATTR_COUNT    6

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvDSIDRecord : public IlvS57Record
{
public:
    IlvDSIDRecord(const IlvI8211Record& record);

    IlInt		getNocn();

    IlInt		getNocr();

    IlInt		getNoed();

    IlInt		getNofa();

    IlInt		getNogr();

    IlInt		getNoin();

    IlInt		getNolr();

    IlInt		getNomr();

    IlString&		getEdtn();

    IlString&		getDsnm();

    IlvS57Enumeration*	getIntu();

protected:
    virtual ~IlvDSIDRecord();

    IlInt		_nocn;
    IlInt		_nocr;
    IlInt		_noed;
    IlInt		_nofa;
    IlInt		_nogr;
    IlInt		_noin;
    IlInt		_nolr;
    IlInt		_nomr;
    IlString		_edtn;
    IlString		_dsnm;
    IlvS57Enumeration*	_intu;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvDSPMRecord  : public IlvS57Record
{
public:
    IlvDSPMRecord(const IlvI8211Record& record);

    IlInt		getComf();

    IlvS57Enumeration*	getCoun();

    IlInt		getCscl();

    IlInt		getDuni();

    IlInt		getHdat();

    IlInt		getHuni();

    IlInt		getPuni();

    IlInt		getSdat();

    IlInt		getSomf();

    IlInt		getVdat();

    IlvDoublePoint	makeCoordinate(IlInt x, IlInt y);
    IlDouble		makeDepth(IlInt z);

protected:
    virtual		~IlvDSPMRecord();

    IlInt		_comf;
    IlvS57Enumeration*	_coun;
    IlInt		_cscl;
    IlInt		_duni;
    IlInt		_hdat;
    IlInt		_huni;
    IlInt		_puni;
    IlInt		_sdat;
    IlInt		_somf;
    IlInt		_vdat;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvVRIDRecord : public IlvS57Record
{
public:
    IlvVRIDRecord(const IlvI8211Record& record);

    IlInt			getId();

    IlInt			getRcid();

    IlInt			getRcnm();

    IlvS57Enumeration*		getRuinType();

    IlInt			getRver();

    IlInt*			getVe3d();

    IlvS57EnumerationArray&	getVridMasks();

    IlvS57EnumerationArray&	getVridOrnts();

    IlvVRIDRecord**		getVridRecords();

    IlInt			getVridCount() const;

    IlvS57EnumerationArray&	getVridTopis();

    IlvS57EnumerationArray&	getVridUsags();

    IlvS57Enumeration*		getVrType();

    IlInt*			getXcoo();

    IlInt*			getYcoo();

    IlInt			getXcooCount() const;

    void			setup(IlvS57AssocTable& fileGeometries);

    void			addBounds(IlvI8211Rectangle& geomBounds,
					  IlvDSPMRecord* dspmRecord);

protected:
    virtual			~IlvVRIDRecord();

    IlInt			_id;
    IlvS57EnumerationArray	_masks;

    IlInt*			_names;
    IlInt			_nameCount;

    IlvS57EnumerationArray	_ornts;
    IlInt			_rcid;
    IlInt			_rcnm;
    IlvS57Enumeration*		_ruinType;
    IlInt			_rver;
    IlvS57EnumerationArray	_topis;
    IlvS57EnumerationArray	_usags;
    IlInt			_usagsCount;
    IlInt*			_ve3d;
    IlInt			_ve3dCount;
    IlvS57Enumeration*		_vrType;
    IlInt*			_xcoo;
    IlInt*			_ycoo;
    IlInt			_cooCount;
    IlvVRIDRecord**		_vridRecords;
    IlInt			_vridCount;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvFRIDRecord : public IlvS57Record
{
public:
    IlvFRIDRecord(const IlvI8211Record& record);

    IlvS57AssocId&		getId();

    IlvS57AssocId&		getLongId();

    IlvS57Enumeration*		getCode();

    IlvDSPMRecord*		getDspmRecord();

    IlvFRIDRecord**		getFridRecords();

    IlvS57EnumerationArray&	getFridRinds();

    IlInt			getGrup();

    IlvS57Enumeration*		getPrimType();

    IlInt			getPrimTypeAsBinary();

    IlInt			getRcid();

    IlInt			getRcnm();

    IlvS57Enumeration*		getRuinType();

    IlInt			getRver();

    IlvS57EnumerationArray&	getVridMasks();

    IlvS57EnumerationArray&	getVridOrnts();

    IlvVRIDRecord**		getVridRecords();

    IlvVRIDRecord*		getVridRecord(IlInt index);

    IlInt			getVridRecordCount();

    IlvS57EnumerationArray&	getVridUsags();

    static void		Init();
    void		setup(IlvS57AssocTable& fileGeometries,
			      IlvDSPMRecord*    dspmRecord);
    void		setupLongNames(IlvS57AssocTable& featuresPerName);

    void		getBounds(IlvI8211Rectangle& geomBounds);

    void		addAttributeName(const char*);
    void		resetAttributeName();

    IlvFeatureAttributeProperty* getFeatureProperties(IlvMapsError& status);

    IlvFeatureAttributeInfo*	getAttributeInfo();

    IlvStringAttribute*		createAttribute(IlInt);
    IlvStringAttribute*		createAttribute(const char*);
    IlvStringAttribute*		createAttribute(IlvValue&);

protected:
    virtual ~IlvFRIDRecord();

    IlInt			_agen;
    IlvS57Enumeration*		_code;// A valid object label/code
    IlInt			_fidn;
    IlInt			_fids;
    IlvFRIDRecord**		_fridRecords;
    IlInt			_fridRecCount;
    IlInt			_grup;	// Group Range: 1 to 254,
					// 255 - No group (binary)
    IlInt*			_lnames;// Long Names
    IlInt			_lnameCount;
    IlvS57EnumerationArray	_masks;// Masking indicators
    IlInt*			_names;// Foreign pointers
    IlInt			_nameCount;
    IlvS57EnumerationArray	_ornts;// Orientations
    IlvS57Enumeration*		_primType;// Object geometric primitive
    IlInt			_rcid;// Record identification number
    IlInt			_rcnm;// Record name
    IlvS57EnumerationArray	_rinds;// Relationship indicators
    IlvS57Enumeration*		_ruinType;//  Record update instruction
    IlInt			_rver;// serial number of the record edition
    IlvS57EnumerationArray	_usags;// Usage indicators
    IlvVRIDRecord**		_vridRecords;
    IlInt			_vridCount;
    IlvDSPMRecord*		_dspmRecord;
    IlvS57AssocId		_id;
    IlvS57AssocId		_lid;

    static IlString*		_STBaseAttrNames;
    char**			_attrNames;
    IlInt			_attrNameCount;
    IlInt			_attrNameSize;

    IlvFeatureAttributeInfo*	_attInfo;
};

#endif /* !__Ilv_S57Divrecord_H */


