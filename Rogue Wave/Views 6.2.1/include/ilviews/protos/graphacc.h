// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/graphacc.h
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
// Declaration of some IlvUserAccessor subclasses that operate on graphics.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Graphacc_H
#define __Ilv_Protos_Graphacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif
#if !defined(__Ilv_Protos_Eventacc_H)
#include <ilviews/protos/eventacc.h>
#endif
#include <stdarg.h>

// ---------------------------------------------------------------------------
// IlvRotationAccessor	Control the angle of a graphic node.
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvRotationAccessor : public IlvAbstractEventAccessor
{
public:
    IlvRotationAccessor(const char* name,
			const char* nodename,
			const char* angleMin,
			const char* angleRange,
			const char* valueMin,
			const char* valueRange,
			const char* centerX,
			const char* centerY,
			IlBoolean allowInteraction = IlFalse);

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    virtual void	initialize(const IlvAccessorHolder* object);
    virtual IlBoolean	handleEvent(IlvAccessorHolder* object,
				    IlvGraphic* g,
				    IlvEvent&,
				    IlvView*,
				    IlvTransformer* t);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvRotationAccessor);

protected:
    IlBoolean		getParameters(const IlvAccessorHolder* object,
				      IlFloat& angleMin,
				      IlFloat& angleRange,
				      IlFloat& valueMin,
				      IlFloat& valueRange,
				      IlvPoint* center) const;

    IlSymbol*		_angleMin;
    IlSymbol*		_angleRange;
    IlSymbol*		_valueMin;
    IlSymbol*		_valueRange;
    IlSymbol*		_centerX;
    IlSymbol*		_centerY;
    IlBoolean		_allowInteraction;
    IlFloat		_rotation;
};

// ---------------------------------------------------------------------------
// IlvZoomXAccessor	Control the horizontal zoom of a node
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvZoomXAccessor : public IlvUserAccessor
{
public:
    IlvZoomXAccessor(const char* name,
		     const char* nodename,
		     const char* centerX);

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvZoomXAccessor);

protected:
    IlSymbol*		_nodename;
    IlSymbol*		_centerX;
    IlFloat		_zoomX;
};

// ---------------------------------------------------------------------------
// IlvZoomYAccessor	Control the vertical zoom of a node
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvZoomYAccessor : public IlvUserAccessor
{
public:
    IlvZoomYAccessor(const char* name,
		     const char* nodename,
		     const char* centerY);

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvZoomYAccessor);

protected:
    IlSymbol*		_nodename;
    IlSymbol*		_centerY;
    IlFloat		_zoomY;
};

// ---------------------------------------------------------------------------
// IlvSlideXAccessor	Control the horizontal position of a node
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvSlideXAccessor : public IlvAbstractEventAccessor
{
public:
    IlvSlideXAccessor(const char* name,
		      const char* nodename,
		      const char* minX,
		      const char* deltaX,
		      const char* minVal,
		      const char* deltaVal,
		      IlBoolean allowInteraction = IlFalse);

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    virtual void	initialize(const IlvAccessorHolder* object);
    virtual IlBoolean	handleEvent(IlvAccessorHolder* object,
				    IlvGraphic* g,
				    IlvEvent&,
				    IlvView*,
				    IlvTransformer* t);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvSlideXAccessor);

protected:
    IlBoolean		getParameters(const IlvAccessorHolder* object,
				      IlInt& minX,
				      IlInt& deltaX,
				      IlFloat& minVal,
				      IlFloat& deltaVal) const;

    IlSymbol*		_minX;
    IlSymbol*		_deltaX;
    IlSymbol*		_minVal;
    IlSymbol*		_deltaVal;
    IlBoolean		_allowInteraction;
    IlFloat		_curVal;
};

// ---------------------------------------------------------------------------
// IlvSlideYAccessor	Control the vertical position of a node
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvSlideYAccessor : public IlvAbstractEventAccessor
{
public:
    IlvSlideYAccessor(const char* name,
		      const char* nodename,
		      const char* minY,
		      const char* deltaY,
		      const char* minVal,
		      const char* deltaVal,
		      IlBoolean allowInteraction = IlFalse);

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);

    virtual void	initialize(const IlvAccessorHolder* object);
    virtual IlBoolean	handleEvent(IlvAccessorHolder* object,
				    IlvGraphic* g,
				    IlvEvent&,
				    IlvView*,
				    IlvTransformer* t);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvSlideYAccessor);

protected:
    IlSymbol*		_minY;
    IlSymbol*		_deltaY;
    IlSymbol*		_minVal;
    IlSymbol*		_deltaVal;
    IlBoolean		_allowInteraction;
    IlFloat		_curVal;

    IlBoolean		getParameters(const IlvAccessorHolder* object,
				      IlInt& minY,
				      IlInt& deltaY,
				      IlFloat& minVal,
				      IlFloat& deltaVal) const;
};

IlvDECLAREINITPROCLASS(graphacc)

#endif /* __Ilv_Protos_Graphacc_H */
