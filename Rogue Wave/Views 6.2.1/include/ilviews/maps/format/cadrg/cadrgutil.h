// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/format/cadrg/cadrgutil.h
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
// Definition of the IlvCADRGFrame and IlvCADRGCoverage classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Format_Cadrg_Cadrgutil_H
#define __Ilv_Maps_Format_Cadrg_Cadrgutil_H

#if !defined(__Ilv_Maps_Coord_H)
#  include <ilviews/maps/coord.h>
#endif

class IlvCADRGCoverage;
class IlvCADRGFrameReader;
class IlvProjection;

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvCADRGFrame
{
public:
    IlvCADRGFrame(const char*,
		  IlInt,
		  IlShort,
		  IlShort);
    IlvCADRGFrame(const IlvCADRGFrame&, IlvCADRGCoverage*);
    ~IlvCADRGFrame();

    void setCoverage(IlvCADRGCoverage* coverage)
	{_coverage = coverage;}
    const char* getFileName() const
	{ return _fileName; }
    const char* getPathName() const
	{ return _pathName; }
    const IlvCADRGCoverage* getCoverage() const
	{ return _coverage; }
    IlBoolean getUpperLeftCorner(IlvCoordinate& ul) const;
    IlBoolean getLowerRightCorner(IlvCoordinate& lr) const;
    IlShort getRow() const
	{ return _row; }
    IlShort getColumn() const
	{ return _column; }
    IlvCADRGFrameReader* makeReader() const;

    IlInt getPathLocation() const
	{ return _pathIndex; }
    void setPathName(const char*);
private:
    char*		_fileName;
    IlInt		_pathIndex;
    IlShort		_row;
    IlShort		_column;
    IlvCADRGCoverage*	_coverage;
    char*		_pathName;
};

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvCADRGCoverage
{
public:
    IlvCADRGCoverage(IlInt,
		     const IlvCoordinate&,
		     const IlvCoordinate&,
		     const IlvCoordinate&,
		     const IlvCoordinate&,
		     IlDouble,
		     IlDouble,
		     IlDouble,
		     IlDouble,
		     IlInt,
		     IlInt,
		     const char*);
    IlvCADRGCoverage(IlInt,
		     IlInt,
		     IlInt,
		     const char*);
    IlvCADRGCoverage(const IlvCADRGCoverage&);
    virtual ~IlvCADRGCoverage();

     const IlvCADRGFrame* getFrame(IlShort row, IlShort column) const
	{ return _frames ? _frames[row][column] : 0; }
    IlInt getRows() const
	{ return _rows; }
    IlInt getColumns() const
	{ return _columns; }
    IlBoolean getUpperLeftCorner(IlvCoordinate& ul) const
	{ ul = _upperLeftCorner; return _georeferenced; }
    IlBoolean getLowerRightCorner(IlvCoordinate& lr) const
	{ lr = _lowerRightCorner; return _georeferenced; }
    IlDouble getFrameWidth() const
	{
	    return (_lowerRightCorner.x() - _upperLeftCorner.x())
		   / (IlDouble) _columns;
	}
    IlDouble   getFrameHeight() const
	{
	    return (_upperLeftCorner.y() - _lowerRightCorner.y())
		   / (IlDouble) _rows;
	}
    IlDouble getVerticalInterval() const
	{ return _verticalInterval; }
    IlDouble getHorizontalInterval() const
	{ return _horizontalInterval; }
    IlInt getIndex() const
	{ return _index; }
    IlvProjection* getProjection() const;

    void setFrame(IlShort, IlShort, IlvCADRGFrame*);
    IlBoolean isGeoreferenced() const
	{ return _georeferenced; }
    const char* getTocPathName() const
	{ return _tocPathName; }
private:
    IlBoolean _georeferenced;
    IlInt _index;
    IlvCoordinate _upperLeftCorner;
    IlvCoordinate _lowerLeftCorner;
    IlvCoordinate _upperRightCorner;
    IlvCoordinate _lowerRightCorner;
    IlDouble _verticalResolution;
    IlDouble _horizontalResolution;
    IlDouble _verticalInterval;
    IlDouble _horizontalInterval;
    IlInt _rows;
    IlInt _columns;
    // do not use the coverage if the toc is deleted
    char* _tocPathName;
    IlvCADRGFrame*** _frames;
    IlvProjection* _projection;
};

#endif /* !__Ilv_Maps_Format_Cadrg_Cadrgutil_H */
