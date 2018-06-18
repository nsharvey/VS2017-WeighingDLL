// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/s57/s57reader.h
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
#ifndef __Ilv_S57reader_H
#define __Ilv_S57reader_H

#include <ilviews/maps/format/s57/s57divrecord.h>
#include <ilviews/maps/format/s57/s57hash.h>

#if defined(IL_STD)
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvS57Reader
{
public:
    IlvS57Reader(IlvDisplay* display);
    virtual ~IlvS57Reader();

    IlvDSIDRecord*	readFile(IL_STDPREF ifstream* stream);

    void		readCatalog(IL_STDPREF ifstream* stream,
				    const IlString&      dir,
				    IlBoolean            skipNon000Files);

    void		addFileFeatures(IlvFRIDRecord*);

    void		reset();

    void		addAll(IlvFRIDRecord** items,IlInt count);

    void		resetFeatures();

    
    IlvFRIDRecord**	getFeatures();

    IlvFRIDRecord*	getFeature(IlInt index);

    IlInt		getFeatureCount();

    void			resetFiles();
    void			addFile(IlString*);
    IL_STDPREF ifstream*	getUrl(IlInt ndx);

protected:
    IlvFRIDRecord**	_fileFeatures;
    IlInt		_featureCount;
    IlInt		_featureSize;

    IlvS57AssocTable	_fileGeometries;
    IlvS57AssocTable	_localTable;

    IlvFRIDRecord**	_allFeatures;
    IlInt		_allCount;
    IlInt		_allSize;

    IlString**		_files;
    IlInt		_fileCount;
    IlInt		_fileSize;
};

#endif /* !__Ilv_S57reader_H */
