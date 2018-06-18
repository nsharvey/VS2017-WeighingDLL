// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/layout.h
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
// Declaration of the classes that allow to compute the chart layout.
// That means: the positioning of the drawing area, the graph area and the
// data display area.
// Contains:
//  - IlvChartLayout: this class allows you to have a fixed margin around the
//    drawing area where nothing will be displayed. By default, it
//    automatically computes the drawing area (where the drawing is
//    performed), the graph area (including all the curves and scales), and
//    the data display area (containing only the data).
//    The drawing area is computed from the chart bounding box by removing
//    a margin on the left, right, top and bottom.
//    The graph area and the data display area are then computed from the
//    drawing area.
//    However the graph area or the data display area can be set by hand.
//
// --------------------------------------------------------------------------
#ifndef __Ilv_Charts_Layout_H
#define __Ilv_Charts_Layout_H

#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif
#if !defined(__Ilv_Charts_Macros_H)
#include <ilviews/charts/macros.h>
#endif
#if !defined(__Ilv_Charts_Chart_H)
#include <ilviews/charts/chart.h>
#endif

class IlvChartGraphic;

// --------------------------------------------------------------------------
// IlvChartLayout persistence
// --------------------------------------------------------------------------
class IlvChartLayout;
typedef IlvChartLayout*
(* IlvChartLayoutConstructor)(IlvInputFile&);

class ILVCHTEXPORTED IlvChartLayoutClassInfo : public IlvValuedClassInfo
{
public:
    inline
    IlvChartLayoutClassInfo* getChartLayoutSuperClass() const
			{ return ILVDYNAMICCAST(IlvChartLayoutClassInfo*,
						getSuperClass());
			}
    inline
    IlvChartLayoutConstructor getConstructor() const { return _constructor; }
    static IlvChartLayoutClassInfo* Create(const char*,
					   IlvClassInfo**,
					   IlvChartLayoutConstructor);

protected:
    IlvChartLayoutClassInfo(const char*		    className,
			    IlvClassInfo**	    superClass,
			    IlvChartLayoutConstructor constructor)
	: IlvValuedClassInfo(className, superClass),
	  _constructor(constructor)
    {}
    IlvChartLayoutConstructor _constructor;
};
#define IlvRegisterChartLayoutClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
			IlvChartLayoutClassInfo::Create(#classname,	\
			    ILVSUPERCLASSINFO(superclass),		\
			    (IlvChartLayoutConstructor)classname::Read))
#define IlvPreRegisterChartLayoutClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)
#define IlvPostRegisterChartLayoutClass(classname, superclass)	\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,			\
		IlvChartLayoutClassInfo::Create(#classname,	\
			   ILVSUPERCLASSINFO(superclass),	\
			   (IlvChartLayoutConstructor)classname::Read))

// --------------------------------------------------------------------------
// Class IlvChartLayout
// --------------------------------------------------------------------------
class ILVCHTEXPORTED IlvChartLayout : public IlvValueInterface
{
public:

    IlvChartLayout(IlvDim leftMargin = 0,
		   IlvDim rightMargin = 0,
		   IlvDim topMargin = 0,
		   IlvDim bottomMargin = 0);

    IlvChartLayout(const IlvChartLayout& layout);

    IlvChartLayout(IlvInputFile& file);

    virtual ~IlvChartLayout();

    // Accessors

    void		setLeftMargin(IlvDim m,
				      IlBoolean updateLayout = IlFalse);

    inline IlvDim	getLeftMargin() const { return _leftMargin; }

    void		setRightMargin(IlvDim m,
				       IlBoolean updateLayout = IlFalse);

    inline IlvDim	getRightMargin() const { return _rightMargin; }

    void		setTopMargin(IlvDim m,
				     IlBoolean updateLayout = IlFalse);

    inline IlvDim	getTopMargin() const { return _topMargin; }

    void		setBottomMargin(IlvDim m,
					IlBoolean updateLayout = IlFalse);

    inline IlvDim	getBottomMargin() const { return _bottomMargin; }

    void		getGraphArea(IlvRect& graphArea,
				     const IlvTransformer* t = 0) const;

    void		setGraphArea(const IlvRect& graphArea,
				     IlBoolean updateLayout = IlFalse);

    void		setGraphAreaRelatively(IlvPos leftMargin,
					       IlvPos rightMargin,
					       IlvPos topMargin,
					       IlvPos bottomMargin,
					       IlBoolean updateLayout =
					       IlFalse);

    void		getGraphAreaRelatively(IlvPos& leftMargin,
					       IlvPos& rightMargin,
					       IlvPos& topMargin,
					       IlvPos& bottomMargin) const;

    void		getDataDisplayArea(IlvRect& dataDisplayArea,
					   const IlvTransformer* t = 0) const;

    void		setDataDisplayArea(const IlvRect& dataDisplayArea,
					   IlBoolean updateLayout = IlFalse);

    void	setDataDisplayAreaRelatively(IlvPos leftMargin,
					     IlvPos rightMargin,
					     IlvPos topMargin,
					     IlvPos bottomMargin,
					     IlBoolean updateLayout = IlFalse);

    void	getDataDisplayAreaRelatively(IlvPos& leftMargin,
					     IlvPos& rightMargin,
					     IlvPos& topMargin,
					     IlvPos& bottomMargin) const;

    inline IlBoolean	isAutoDataDisplayArea() const
			{
			    return _autoDataDisplayArea;
			}

    inline void		setAutoDataDisplayArea(IlBoolean flag)
			{
			    _autoDataDisplayArea = flag;
			}

    inline IlBoolean	isAutoGraphArea() const { return _autoGraphArea; }

    inline void		setAutoGraphArea(IlBoolean flag)
			{
			    _autoGraphArea = flag;
			}

    inline IlBoolean	isAutoLayout() const
			{
			    return _autoDataDisplayArea && _autoGraphArea;
			}

    inline void		setAutoLayout()
			{
			    _autoDataDisplayArea = IlTrue;
			    _autoGraphArea = IlTrue;
			}

    virtual IlBoolean	getDrawingArea(IlvRect& drawingArea,
				       const IlvTransformer* t = 0) const;

    // Accessors for updating
    inline IlBoolean	isLayoutValid() const { return _layoutValid; }

    inline void		invalidate() { _layoutValid = IlFalse; }

    inline
    const IlvChartGraphic* getChartGraphic() const { return _chart; }

    inline void		setChartGraphic(IlvChartGraphic* chart) 
			{
			    _chart = chart;
			}

    virtual void	update();

    virtual void	applyTransform(const IlvTransformer *t);

    virtual
    IlvChartLayout*	copy() const;

    // Persistence
    IlvOutputFile&	save(IlvOutputFile& file) const;

    static IlvChartLayout* Load(IlvInputFile& file);

    virtual void	write(IlvOutputFile& file) const;

    static
    IlvChartLayout*	Read(IlvInputFile& file);

    IlvDeclarePropRootClassInfo();

protected:
    IlvDim		_leftMargin;
    IlvDim		_rightMargin;
    IlvDim		_topMargin;
    IlvDim		_bottomMargin;
    IlBoolean		_autoDataDisplayArea;
    IlBoolean		_autoGraphArea;
    IlvRect		_graphArea;
    IlvPos		_graphAreaLeftMargin;
    IlvPos		_graphAreaRightMargin;
    IlvPos		_graphAreaTopMargin;
    IlvPos		_graphAreaBottomMargin;
    IlBoolean		_relativeGraphArea;
    IlvRect		_dataDisplayArea;
    IlvPos		_dataDisplayAreaLeftMargin;
    IlvPos		_dataDisplayAreaRightMargin;
    IlvPos		_dataDisplayAreaTopMargin;
    IlvPos		_dataDisplayAreaBottomMargin;
    IlBoolean		_relativeDataDisplayArea;
    IlBoolean		_layoutValid;
    IlvChartGraphic*	_chart;

    // Internal accessors
    inline void		setLayoutValid(IlBoolean flag) { _layoutValid = flag; }

    IlBoolean		relativeGraphArea() const
			{
			    return _relativeGraphArea;
			}
    inline void		setRelativeGraphArea(IlBoolean flag)
			{
			    _relativeGraphArea = flag;
			}

    inline IlBoolean	relativeDataDisplayArea() const
			{
			    return _relativeDataDisplayArea;
			}
    inline void		setRelativeDataDisplayArea(IlBoolean flag)
			{
			    _relativeDataDisplayArea = flag;
			}

    // Internal methods
    void		updateGraphAreaFromMargins();
    void		updateDataDisplayAreaFromMargins();
    IlBoolean		updateGraphAreaRelativeMargins();
    IlBoolean		updateDataDisplayAreaRelativeMargins();

    virtual void	computeGraphAndDataAreas();

    virtual void	computeGraphFromDataArea();

    virtual void	computeDataFromGraphArea();

};

ILVCHTMODULEINIT(layout);

#endif /* !__Ilv_Charts_Layout_H */
