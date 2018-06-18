// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/cadrg/cadrgtoc.h
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
// Definition of the IlvCADRGTocReader class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Cadrg_Cadrgtoc_H
#define __Ilv_Maps_Format_Cadrg_Cadrgtoc_H

#if !defined(__Ilv_Maps_Format_Mapinput_H)
#  include <ilviews/maps/format/mapinput.h>
#endif
#if !defined(__Ilv_Maps_Format_Cadrg_Cadrgutil_H)
#  include <ilviews/maps/format/cadrg/cadrgutil.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#  include <ilviews/base/link.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvCADRGTocReader
{
public:
    IlvCADRGTocReader(const char* fileName);
    virtual ~IlvCADRGTocReader();

    IlvMapsError getInitStatus() const
	{ return _status; }
    const IlvCADRGCoverage* const* getCoverages(IlUShort& count) const;
    const IlvCADRGFrame* const* getLegendFrames(IlUShort& count) const;
    const IlvCADRGFrame* const* getOverviewFrames(IlUShort& count) const;
    static IlvMapsError FormatError();

private:
    IlvMapsError read();
    IlvMapsError readHeaderSection();
    IlvMapsError findGoverningStandardNumber();
    IlvMapsError readLocationSection();
    IlvMapsError readBoundaryRectangleRecords();
    IlvMapsError readBoundaryRectangleSubHeader();
    void cleanCoverages();
    IlvMapsError readFileIndexSection();
    IlvMapsError readFileIndexSectionSubHeader();
    IlvMapsError readFrameFileIndexSubsection();
    IlvMapsError readFrameFileIndexTable();
    IlvMapsError readPathNameTable();
    void initFrameDirectories();

    IlvMapInput _input;
    char* _fileName;
    IlvMapsError _status;
    IlvCADRGCoverage** _coverages;
    IlShort _coverageCount;
    IlInt _numberOfFrameFileIndexRecords;
    IlShort _numberOfPathNameRecords;
    IlShort _frameFileIndexRecordLength;
    IlvHashTable _pathTable;
    IlvList _legends;
    IlvList _overviews;
    IlvCADRGFrame** _legendFrames;
    IlvCADRGFrame** _overviewFrames;
};

#endif /* !__Ilv_Maps_Format_Cadrg_Cadrgtoc_H */
