// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/maps/mapfeature.h
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
// Definition of the IlvMapFeature class.
// Definition of the IlvMapFeatureIterator class.
// Defined in library ilvmaps
// --------------------------------------------------------------------------
#ifndef __Ilv_Maps_Mapfeature_H
#define __Ilv_Maps_Mapfeature_H

#if !defined(__Ilv_Maps_Attrprop_H)
#  include <ilviews/maps/attrprop.h>
#endif
#if !defined(__Ilv_Maps_Geometry_H)
#  include <ilviews/maps/geometry.h>
#endif
#if !defined(__Ilv_Maps_Featureid_H)
#  include <ilviews/maps/featureid.h>
#endif
#if !defined(__Ilv_Maps_Projection_Project_H)
#  include <ilviews/maps/projection/project.h>
#endif

// --------------------------------------------------------------------------
class ILVMAPSEXPORTED IlvMapFeature
{
public:
    IlvMapFeature();
    IlvMapFeature(const IlvMapFeature& source);
    virtual ~IlvMapFeature();

    IlvMapGeometry*	setGeometry(IlvMapGeometry* geometry);
    inline const IlvMapGeometry* getGeometry() const { return _geometry; }
    void		setAttributeInfo(IlvFeatureAttributeInfo* info);
    inline const IlvFeatureAttributeInfo* getAttributeInfo() const
			{
			    return _attributeInfo;
			}
    IlvFeatureAttributeProperty*
		setAttributes(IlvFeatureAttributeProperty* attributes);
    inline const IlvFeatureAttributeProperty* getAttributes() const
			{
			    return _attributes;
			}
    void		setProjection(IlvProjection* projection);
    inline const IlvProjection* getProjection() const { return _projection; }
    IlvMapFeatureId*	setId(IlvMapFeatureId* id);
    inline const IlvMapFeatureId* getId() const { return _id; }
    inline IlvMapFeature*	copy() const
	{ return new IlvMapFeature(*this); }
private:
    IlvMapFeatureId*		_id;		// owned
    IlvMapGeometry*		_geometry;	// owned
    IlvFeatureAttributeInfo*	_attributeInfo; // locked
    IlvFeatureAttributeProperty* _attributes;	// owned
    IlvProjection*		_projection;	// not owned
};

class ILVMAPSEXPORTED IlvFeatureRenderer;

// --------------------------------------------------------------------------
//		class info macros for iterators
// --------------------------------------------------------------------------
#define IlvMapFeatureIteratorDeclareClassInfo()		\
public:							\
    static IlvClassInfo* ClassInfo();			\
    static IlvClassInfo** ClassInfoRef();		\
    virtual IlvClassInfo* getClassInfo() const;		\
private:						\
    static IlvClassInfo* _classinfo			\

#define IlvMapFeatureIteratorDefineClassInfo(className,superClass) \
IlvClassInfo* className::getClassInfo() const {		\
    return ClassInfo();					\
}							\
IlvClassInfo** className::ClassInfoRef() {		\
    ClassInfo();					\
    return &_classinfo;					\
}							\
IlvClassInfo* className::_classinfo = 0;		\
IlvClassInfo* className::ClassInfo() {			\
    if (!_classinfo) {					\
	_classinfo = IlvClassInfo::Create(#className,	\
	                 superClass::ClassInfoRef());	\
	return _classinfo;				\
    }							\
    return _classinfo;					\
}

ILVMAPSMODULEINIT(IlvMapFeatureIterator);

class ILVMAPSEXPORTED IlvMapFeatureIterator
{
public:
    virtual ~IlvMapFeatureIterator();

    virtual IlBoolean	getLowerRightCorner(IlvCoordinate& result) const = 0;
    virtual IlBoolean	getUpperLeftCorner(IlvCoordinate& result) const = 0;
    virtual
    const IlvProjection* getProjection() const = 0;
    virtual void	setSourceProjection(IlvProjection* projection);
    virtual
    const IlvMapFeature* getNextFeature(IlvMapsError& status) = 0;
    virtual IlvFeatureRenderer*
		getDefaultFeatureRenderer(IlvDisplay *display) = 0;
    virtual
    IlvMapsError	getInitStatus() const = 0;
    virtual
    IlvClassInfo*	getClassInfo() const = 0;
    static IlvClassInfo*	ClassInfo();

    static IlvClassInfo**	ClassInfoRef();
private:
    static
    IlvClassInfo*	_classinfo;
};

#endif /* !__Ilv_Maps_Mapfeature_H */
