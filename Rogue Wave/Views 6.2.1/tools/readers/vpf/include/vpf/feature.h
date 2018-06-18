// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/feature.h
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
// Declaration of the different feature classes
// --------------------------------------------------------------------------
#ifndef VPF_FEATURE_H
#define VPF_FEATURE_H

#include <vpf/basictypes.h>
#include <vpf/extent.h>

class VpfTable;
class VpfCursor;
class VpfEdgCursor;
class VpfRngCursor;
class VpfFacCursor;
class VpfCndCursor;
class VpfTxtCursor;
class VpfRow;
class VpfEdgRow;
class VpfRngRow;
class VpfFacRow;
class VpfCndRow;
class VpfTxtRow;
class VpfRing;
class VpfCoverage;
class VpfFeatureClass;
class VpfFeatureItem;

// --------------------------------------------------------------------------
class VpfFeature
{
public:
    typedef enum {
	Contained,
	Intersects,
	Reshape
    } ExtentMatchMode;

    VpfFeature(VpfFeatureClass*, const VpfExtent&,
	       ExtentMatchMode = Contained);
    virtual ~VpfFeature();
    // ____________________________________________________________
    int isBad() const { return (_class == 0); }
    void setBad() { _class = 0; }

    int select(const char* expression);
    virtual VpfUInt getNSelected() const;

    virtual VpfFeatureItem* getNextObject();
protected:
    int getTileAndPrimId(VpfInt, VpfInt&, VpfInt&);
    virtual int selectTile(VpfInt) = 0;
    virtual int getFeatureMBR(VpfInt, VpfExtent&);
    virtual VpfFeatureItem* getFeature(VpfInt) = 0;

    VpfCoverage*	_coverage;
    VpfFeatureClass*	_class;
    ExtentMatchMode	_matchMode;
    int			_currentTileID;
    struct VRFIndex {
	VpfInt	tileID;
	VpfInt	primitiveID;
    } *			_index;
    int			_nbFeatures;
    int			_layerIndex;

    VpfTable*		_fbrTable;
    VpfCursor*		_fbrCursor;
    VpfRow*		_fbrRow;

    VpfTable*		_featureTable;
    VpfCursor*		_featureCursor;
    VpfRow*		_featureRow;

    VpfTable*		_joinTable;
    VpfCursor*		_joinCursor;
    VpfRow*		_joinRow;

    VpfExtent		_extent;
};

// --------------------------------------------------------------------------
class VpfAreaFeature
: public VpfFeature
{
public:
    VpfAreaFeature(VpfFeatureClass*, const VpfExtent&,
		   ExtentMatchMode = Contained);
    virtual ~VpfAreaFeature();
protected:
    virtual int selectTile(VpfInt);
    virtual VpfFeatureItem* getFeature(VpfInt);
    virtual VpfInt nextFaceEdge(VpfInt&, VpfInt);
    virtual VpfRing* getRingCoords(VpfInt, VpfInt, VpfInt);
    VpfTable*		_faceTable;
    VpfFacCursor*	_faceCursor;
    VpfFacRow*		_faceRow;

    VpfTable*		_ringTable;
    VpfRngCursor*	_ringCursor;
    VpfRngRow*		_ringRow;

    VpfTable*		_edgeTable;
    VpfEdgCursor*	_edgeCursor;
    VpfEdgRow*		_edgeRow;
};

// --------------------------------------------------------------------------
class VpfLineFeature
: public VpfFeature
{
public:
    VpfLineFeature(VpfFeatureClass*, const VpfExtent&,
		   ExtentMatchMode = Contained);
    virtual ~VpfLineFeature();
protected:
    virtual int selectTile(VpfInt);
    virtual VpfFeatureItem* getFeature(VpfInt);
    
    VpfTable*		_edgeTable;
    VpfEdgCursor*	_edgeCursor;
    VpfEdgRow*		_edgeRow;
};

// --------------------------------------------------------------------------
class VpfPointFeature
: public VpfFeature
{
public:
    VpfPointFeature(VpfFeatureClass*, const VpfExtent&);
    virtual ~VpfPointFeature();
    // ____________________________________________________________
    virtual VpfFeatureItem* getNextObject();
protected:
    virtual int selectTile(VpfInt);
    virtual VpfFeatureItem* getFeature(VpfInt);

    VpfTable*		_pointTable;
    VpfCndCursor*	_pointCursor;
    VpfCndRow*		_pointRow;
};

// ____________________________________________________________
class VpfTextFeature
: public VpfFeature
{
public:
    VpfTextFeature(VpfFeatureClass*, const VpfExtent&);
    virtual ~VpfTextFeature();
    // ____________________________________________________________
    virtual VpfFeatureItem* getNextObject();
protected:
    virtual int selectTile(VpfInt);
    virtual VpfFeatureItem* getFeature(VpfInt);

    VpfTable*		_textTable;
    VpfTxtCursor*	_textCursor;
    VpfTxtRow*		_textRow;
};

#endif /* VPF_FEATURE_H */
