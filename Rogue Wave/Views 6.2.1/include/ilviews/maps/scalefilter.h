// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/scalefilter.h
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
// Definition of the IlvScaleVisibilityFilter class
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Scalefilter_H
#define __Ilv_Maps_Scalefilter_H

#if !defined(__Ilv_Manager_Layer_H)
#  include <ilviews/manager/layer.h>
#endif
#if !defined(__Ilv_Maps_Unitconv_H)
#  include <ilviews/maps/unitconv.h>
#endif

class ILVMAPSEXPORTED IlvScaleVisibilityFilter
: public IlvLayerVisibilityFilter
{
public:
    IlvScaleVisibilityFilter(IlDouble minScale,
			     IlDouble maxScale);
    virtual ~IlvScaleVisibilityFilter();

    inline IlDouble getMinScale() const { return _minScale; }
    void setMinScale(IlDouble minScale);
    inline IlDouble getMaxScale() const { return _maxScale; }
    void setMaxScale(IlDouble maxScale);

    // Documented in superclass
    virtual IlBoolean isVisible(const IlvManagerLayer*,
				const IlvMgrView*) const;
    static IlDouble NoLimit();
public:
    // For IO
    static IlvLayerVisibilityFilter* read(IlvInputFile&);
    virtual void write(IlvOutputFile&) const;
    static IlvClassInfo* ClassInfo();
    virtual IlvClassInfo* getClassInfo() const;
    inline const char* className() const
	{ return getClassInfo()->getClassName(); }
    inline IlBoolean isSubtypeOf(const char* t) const
	{ return getClassInfo()->isSubtypeOf(t); }
    inline IlBoolean isSubtypeOf(const IlvClassInfo* c) const
	{ return getClassInfo()->isSubtypeOf(c); }
    static IlvClassInfo* _classinfo;

    DeclareLayerVisibilityFilterIOConstructors(IlvScaleVisibilityFilter);
protected:
    IlDouble _minScale;
    IlDouble _maxScale;
};

ILVMAPSMODULEINIT(IlvScaleVisibilityFilter);
#endif /* !__Ilv_Maps_Scalefilter_H */
