// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/mapbuilder/include/prjselector.h
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
// Declaration of the ProjectionSelector class
// -------------------------------------------------------------------------
#ifndef _ProjectionSelector_h_
#define _ProjectionSelector_h_

#include <ilviews/gadgets/rectgadc.h>

#include <ilviews/maps/projection/project.h>
#include <ilviews/maps/projection/projdict.h>

class IlvMatrix;
class IlvGadgetContainerRectangle;
class IlvScrolledComboBox;
class IlvViewRectangle;
class IlvMapAdapter;

// -------------------------------------------------------------------------
class ProjectionSelector
    : public IlvGadgetContainerRectangle
{
public:
    ProjectionSelector(IlvDisplay* display,
		       const IlvRect& rect,
		       IlvProjection* defaultProjection=0);
    virtual ~ProjectionSelector();

    virtual IlvView* createView(IlvAbstractView*, const IlvRect&);

    IlvProjection* getProjection() const
	{ return _projection; }
    void setProjection(IlvProjection* projection);
    void setEllipsoid(const IlvEllipsoid* e);
    void setEllipsoid(IlUInt i);

    // for internal use
    IlvScrolledComboBox* _getProjectionCombo() const
	{ return _projectionCombo; }
    const IlvProjectionDictionary& _getDictionary() const
	{ return _projdict; }
    IlvScrolledComboBox* _getEllipsoidCombo() const
	{ return _ellipsoidCombo; }
    void updatePreview();
    void projectObject(IlvGraphic* g);

private:
    IlvScrolledComboBox*    _projectionCombo;
    IlvProjectionDictionary _projdict;
    IlvProjection*          _projection;

    IlvMatrix*              _matrix;

    const char**            _ellipsoidNames;
    IlUInt                  _ellipsoidCount;
    IlvScrolledComboBox*    _ellipsoidCombo;
    IlvMatrix*              _eMatrix;
    IlvEllipsoid*           _currentEllipsoid;

    IlvViewRectangle*       _preview;
    IlvManager*             _previewManager;
    IlvManager*             _sourceManager;
    IlvMapAdapter*          _previewAdapter;
};
#endif
