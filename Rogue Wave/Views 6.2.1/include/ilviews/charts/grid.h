// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/grid.h
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
// Declaration of the classes that define grids.
// Contains:
//  - IlvAbstractGridDisplayer: the abstract class that allows you to define
//    a grid that can be added to a given scale.
//  - IlvRectangularGridDisplayer: a subclass of IlvAbstractGridDisplayer
//    which allows you to define a rectangular grid that can be used with a
//    cartesian chart.
//  - IlvCircularGridDisplayer: a subclass of IlvAbstractGridDisplayer
//    which allows you to define a circular grid that can be used with a
//    polar chart.
//  - IlvRadialGridDisplayer: a subclass of IlvAbstractGridDisplayer
//    which allows you to define a radial grid that can be used with a
//    polar chart.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Grid_H
#define __Ilv_Charts_Grid_H

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Common_H)
#include <ilviews/charts/common.h>
#endif
#if !defined(__Ilv_Charts_Scaledis_H)
#include <ilviews/charts/scaledis.h>
#endif

class IlvAbstractGridDisplayer;
class IlvRadialGridDisplayer;
class IlvCircularGridDisplayer;
// --------------------------------------------------------------------------
// IlvAbstractGridDisplayer persistence
// --------------------------------------------------------------------------
typedef IlvAbstractGridDisplayer*
    (* IlvGridDisplayerConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvGridDisplayerClassInfo : public IlvValuedClassInfo
{
public:
    inline
    IlvGridDisplayerClassInfo* getGridDisplayerSuperClass() const
		{
		    return ILVDYNAMICCAST(IlvGridDisplayerClassInfo*,
					  getSuperClass());
		}
    inline
    IlvGridDisplayerConstructor getConstructor() const { return _constructor; }
    static
    IlvGridDisplayerClassInfo* Create(const char*,
				      IlvClassInfo**,
				      IlvGridDisplayerConstructor);

protected:
    IlvGridDisplayerClassInfo(const char* className,
				      IlvClassInfo** superClass,
				      IlvGridDisplayerConstructor c)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(c)
	{}

    IlvGridDisplayerConstructor _constructor;
};
#define IlvRegisterGridDisplayerClass(classname, superclass)	\
ILVDEFINECLASSINFOMEMBERS(classname,				\
		IlvGridDisplayerClassInfo::Create(#classname,	\
		ILVSUPERCLASSINFO(superclass),		\
		(IlvGridDisplayerConstructor)classname::Read))
#define IlvPreRegisterGridDisplayerClass(classname) \
  ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterGridDisplayerClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
		IlvGridDisplayerClassInfo::Create(#classname,		\
		ILVSUPERCLASSINFO(superclass),				\
		(IlvGridDisplayerConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvAbstractGridDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvAbstractGridDisplayer : public IlvValueInterface
{
public:
    friend class IlvAxisElement;
    friend class IlvAbscissaAxisElement;

    virtual ~IlvAbstractGridDisplayer();

    // Accessors
    inline IlBoolean	isVisible() const { return _visible; }

    inline void		setVisible(IlBoolean visible) { _visible = visible; }

    inline IlvPalette*	getMajorPalette() const
			{
			    return _majorPalette
				? _majorPalette
				: getDefaultPalette();
			}

    void		setMajorPalette(IlvPalette* pal);

    inline IlvPalette*	getMinorPalette() const
			{
			    return _minorPalette
				? _minorPalette
				: getDefaultPalette();
			}

    void		setMinorPalette( IlvPalette* pal);

    inline IlvPalette*	getDefaultPalette() const
			{
			    return _tickScale
				? _tickScale->getAxisPalette()
				: 0;
			}

    inline IlBoolean	isDrawingMinorLines() const {return _drawMinorLines;}

    inline void		drawMinorLines(IlBoolean flag)
			{
			    _drawMinorLines = flag;
			}

    inline IlvDrawOrder	getDrawOrder() const { return _drawOrder; }

    inline void		setDrawOrder(IlvDrawOrder drawOrder)
			{
			    _drawOrder = drawOrder;
			}

    inline
    const IlvAbstractProjector* getProjector() const 
			{
			    return _tickScale
				? _tickScale->getProjector()
				: 0;
			}

    inline
    const IlvSingleScaleDisplayer* getTickScale() const { return _tickScale; }

    // The _dataDisplayArea and the _tickScale are set
    // by the scale displayer to which the grid is attached.

    // Obsolete
    inline void		setProjector(const IlvAbstractProjector*) {}
    inline void		setDataDisplayArea( const IlvRect& rect) 
			{
			    _dataDisplayArea = rect;
			}
    inline void		setTickScale( const IlvSingleScaleDisplayer* scale)
			{
			    _tickScale = scale;
			}

    // Drawing

    virtual void	drawTick(IlUInt tickIdx,
				 const IlvPoint& tickPoint,
				 IlDouble tickAngle,
				 IlBoolean major,
				 IlvPort* dst,
				 const IlvRegion* clip) const= 0;

    virtual void	setOverwrite(IlBoolean o);

    virtual void	setMode(IlvDrawMode mode);

    virtual
    IlvAbstractGridDisplayer* copy() const = 0;

    // Persistence

    IlvOutputFile&	save(IlvOutputFile& file) const;

    static
    IlvAbstractGridDisplayer* Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    IlvDeclarePropRootClassInfo();

protected:
    IlvRect		_dataDisplayArea;
    IlBoolean		_visible;
    IlvPalette*		_majorPalette;
    IlvPalette*		_minorPalette;
    IlvAxisElement*	_axisElement;

    // The grid will be drawn using the ticks of the scale displayer
    // _tickScale.
    const IlvSingleScaleDisplayer*	_tickScale;

    // The grid appears on minor ticks if _drawMinorLines.
    IlBoolean		_drawMinorLines;
    IlvDrawOrder	_drawOrder;

    // Constructors

    IlvAbstractGridDisplayer(IlvPalette* major= 0, IlvPalette* minor= 0);

    IlvAbstractGridDisplayer(const IlvAbstractGridDisplayer& grid);

    IlvAbstractGridDisplayer(IlvInputFile& file);

    inline void		setAxisElement(IlvAxisElement *el)
			{
			    _axisElement = el;
			}
    inline
    IlvAxisElement*	getAxisElement() { return _axisElement; }
};

// --------------------------------------------------------------------------
// Class IlvRectangularGridDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvRectangularGridDisplayer
    : public IlvAbstractGridDisplayer
{
public:

    IlvRectangularGridDisplayer(IlvPalette* major = 0,
				IlvPalette* minor = 0);

    virtual ~IlvRectangularGridDisplayer();

    virtual void	drawTick(IlUInt tickIdx,
				 const IlvPoint& tickPoint,
				 IlDouble tickAngle,
				 IlBoolean major,
				 IlvPort* dst,
				 const IlvRegion* givenClip) const;

    // Misc

    virtual
    IlvRadialGridDisplayer* createRadialGrid() const;

    virtual IlvCircularGridDisplayer*
		createCircularGrid(IlvCircularScaleDisplayer* ref) const;

    DeclareGridDisplayerTypeInfoRO(IlvRectangularGridDisplayer);

};

// --------------------------------------------------------------------------
// Class IlvCircularGridDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvCircularGridDisplayer
    : public IlvAbstractGridDisplayer
{
public:

    IlvCircularGridDisplayer(IlvCircularScaleDisplayer* ref,
			     IlvPalette* major = 0,
			     IlvPalette* minor = 0);

    virtual ~IlvCircularGridDisplayer();

    // Accessors

    inline
    const IlvCircularScaleDisplayer* getReferenceScale() const
			{
			    return _referenceScale;
			}

    inline
    void setReferenceScale(const IlvCircularScaleDisplayer* scale)
			{
			    _referenceScale= scale;
			}

    virtual void	drawTick( IlUInt tickIdx,
				  const IlvPoint& tickPoint,
				  IlDouble tickAngle,
				  IlBoolean major,
				  IlvPort* dst,
				  const IlvRegion* givenClip) const;

    // Misc

    virtual
    IlvRectangularGridDisplayer* createRectangularGrid() const;

    DeclareGridDisplayerTypeInfo(IlvCircularGridDisplayer);

protected:
    const IlvCircularScaleDisplayer* _referenceScale;

};

// --------------------------------------------------------------------------
// Class IlvRadialGridDisplayer
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvRadialGridDisplayer : public IlvAbstractGridDisplayer
{
public:

    IlvRadialGridDisplayer( IlvPalette* major= 0, IlvPalette* minor= 0);

    virtual ~IlvRadialGridDisplayer();

    virtual void	drawTick(IlUInt tickIdx,
				 const IlvPoint& tickPoint,
				 IlDouble tickAngle,
				 IlBoolean major,
				 IlvPort* dst,
				 const IlvRegion* givenClip) const;

    virtual
    IlvRectangularGridDisplayer* createRectangularGrid() const;

    DeclareGridDisplayerTypeInfoRO(IlvRadialGridDisplayer);
};

ILVCHTMODULEINIT(grid);

#endif /* !__Ilv_Charts_Grid_H */
