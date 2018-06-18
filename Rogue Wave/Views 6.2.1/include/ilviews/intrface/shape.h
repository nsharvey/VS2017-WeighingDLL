// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/intrface/shape.h
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
// Declaration of the IlvShapeInterface class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Itf_Shape_H
#define __Ilv_Itf_Shape_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif

#if !defined(__Ilv_Util_Util_H)
#include <ilviews/util/util.h>
#endif

#define IlvRegisterShapeInterface(Cl,Itf) IlvRegisterInterface(Shape,Cl,Itf)

class ILVVWSEXPORTED IlvGraphic;

class ILVVWSEXPORTED IlvShapePosition
{
public:
    struct BarycentricCoordinate
    {
	IlUInt vtx;
	IlDouble weight;
    };

    IlvShapePosition() : _coordinates(0), _count(0) {}
    IlvShapePosition(IlUShort count ...);
    IlvShapePosition(const IlvShapePosition& src);
    ~IlvShapePosition();

    void		setCoordinates(IlUShort count ...);

    inline IlUShort	getCardinal() const { return _count; }
    BarycentricCoordinate& operator[](int idx) { return _coordinates[idx]; }
    const BarycentricCoordinate& operator[](int idx) const
			{
			    return _coordinates[idx];
			}
    IlvShapePosition& operator=(const IlvShapePosition& src);

    IlBoolean		getPosition(IlUInt count,
				    const IlvPoint* pts,
				    IlvPoint& point) const;

private:
    BarycentricCoordinate* _coordinates;
    IlUShort		_count;    

    void		setCoordinates(const IlvShapePosition& src);
};

extern ILVVWSEXPORTEDFUNCTION(IL_STDPREF ostream&)
    operator<<(IL_STDPREF ostream& o, const IlvShapePosition&);
extern ILVVWSEXPORTEDFUNCTION(IL_STDPREF istream&)
    operator>>(IL_STDPREF istream& i, IlvShapePosition&);


class ILVVWSEXPORTED IlvShapeInterface 
{
public:
    IlvShapeInterface() {} ;
    virtual ~IlvShapeInterface(); 

    virtual IlUInt	getShapeCount(const IlvGraphic* obj,
				      const IlvTransformer* t = 0) const = 0;


    virtual
    const IlvPoint*	getShape(IlUInt& count,
				 const IlvGraphic* obj,
				 const IlvTransformer* t = 0,
				 IlvPoint* buffer = 0) const = 0;

    IlBoolean		getShapePosition(const IlvGraphic* obj,
					 const IlvPoint& p,
					 IlvShapePosition& shapePos,
					 const IlvTransformer* t = 0) const;

    IlBoolean		getPosition(const IlvGraphic* obj,
				    const IlvShapePosition& shapePos,
				    IlvPoint& p,
				    const IlvTransformer* t = 0,
				    IlvPoint* buffer = 0) const;


    static
    IlvShapeInterface*	GetInterface(const IlvGraphic* obj);

    static IlSymbol*	GetSymbol();

    static IlBoolean	GetShapePosition(const IlvGraphic* obj,
					 const IlvPoint& p,
					 IlvShapePosition& shapePos,
					 const IlvTransformer* t = 0)
			{
			    IlvShapeInterface* si = GetInterface(obj);
			    return si
				? si->getShapePosition(obj, p, shapePos, t)
				: IlFalse;
			}

    static IlBoolean	GetPosition(const IlvGraphic* obj,
				    const IlvShapePosition& shapePos,
				    IlvPoint& p,
				    const IlvTransformer* t = 0,
				    IlvPoint* buffer = 0)
			{
			    IlvShapeInterface* si = GetInterface(obj);
			    return  si
				? si->getPosition(obj, shapePos, p, t, buffer)
				: IlFalse;
			}

    static IlUInt	GetShapeCount(const IlvGraphic* obj,
				      const IlvTransformer* t = 0)
			{
			    IlvShapeInterface* si = GetInterface(obj);
			    return  si ? si->getShapeCount(obj, t) : 0;
			}

    static
    const IlvPoint*	GetShape(IlUInt& count,
				 const IlvGraphic* obj,
				 const IlvTransformer* t = 0,
				 IlvPoint* buffer = 0)
			{
			    IlvShapeInterface* si = GetInterface(obj);    
			    return  si
				? si->getShape(count, obj, t, buffer)
				: 0;
			}

    static IlDouble	GetDelta() { return _delta; }
    static void		SetDelta(IlDouble delta) { _delta = delta; }

protected:
    static IlDouble _delta;
};

#endif
