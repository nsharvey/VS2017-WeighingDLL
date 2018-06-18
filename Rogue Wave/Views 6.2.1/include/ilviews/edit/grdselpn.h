// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/grdselpn.h
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
// Declaration of the IlvGradientSelector class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------


#ifndef __Ilv_Edit_Grdselpn_H
#define __Ilv_Edit_Grdselpn_H

#include <ilviews/edit/macros.h>
#include <ilviews/gadgets/idialog.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/ellipse.h>
#include <ilviews/graphics/marker.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/slider.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/gadgets/colorch.h>
#include <ilviews/gadmgr/rectscmg.h>

class IlvGradientSelectorCommon;
class IlvGradientSelectorColorStops;
class IlvGradientSelectorLinear;
class IlvGradientSelectorRadial;
class IlvGradientSelectorPreview;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvGradientSelector : public IlvDialog
{
public:

    IlvGradientSelector(IlvDisplay* display,
			IlvSystemView transientFor = 0);
    virtual ~IlvGradientSelector();

    // ____________________________________________________________

    IlvGradientPattern*		getGradientPattern();

    IlvGradientPattern*		get(IlBoolean grab = IlFalse,
				    IlvCursor* cursor = 0);
    inline IlvGradientPattern*	getCurrentGradient() const 
				{
				    return _currentGradient;
				}
    inline IlvGradientPattern*	getOriginGradient() const 
				{
				    return _originGradient;
				}

    void			set(IlvGradientPattern* gradient);

    inline
    IlvGradientSelectorCommon*	getCommonAttr() { return _commonAttr; }
    inline
    IlvGradientSelectorColorStops*
				getColorsAttr() { return _colorStopsAttr; }
    inline
    IlvGradientSelectorLinear*	getLinearAttr() { return _linearAttr; }
    inline
    IlvGradientSelectorRadial*	getRadialAttr() { return _radialAttr; }
    inline
    IlvGradientSelectorPreview*	getPreviewAttr() { return _previewAttr; }

    inline IlBoolean		isUpdateEnabled() { return _updateEnabled; }
    void			enableUpdate(IlBoolean updateEnabled);

    static void			AliasCB(IlvGraphic* g, IlAny arg);
    static void			TransformModeCB(IlvGraphic* g, IlAny arg);
    static void			AspectRatioCB(IlvGraphic* g, IlAny arg);
    static void			SpreadCB(IlvGraphic* g, IlAny arg);
    static void			TypeCB(IlvGraphic* g, IlAny arg);
    static void			WidthCB(IlvGraphic* g, IlAny arg);
    static void			HeightCB(IlvGraphic* g, IlAny arg);
    static void			SlidableValueCB(IlvGraphic* g, IlAny arg);
    static void			AddColorStopCB(IlvGraphic* g, IlAny arg);
    static void			RemoveColorStopCB(IlvGraphic* g, IlAny arg);
    static void			ColorRectCB(IlvGraphic* g, IlAny arg);
    static void			ToggleGraphicCB(IlvGraphic* g, IlAny arg);
    static void			ToggleControlPointsCB(IlvGraphic* g, IlAny a);
    static void			ResetPreviewCB(IlvGraphic* g, IlAny arg);
    static void			ZoomCB(IlvGraphic* g, IlAny arg);

 protected:
    IlvGradientPattern*			_originGradient;
    IlvGradientPattern*			_currentGradient;
    IlvGradientSelectorCommon*		_commonAttr;
    IlvGradientSelectorColorStops*	_colorStopsAttr;
    IlvGradientSelectorLinear*		_linearAttr;
    IlvGradientSelectorRadial*		_radialAttr;
    IlvGradientSelectorPreview*		_previewAttr;
    IlBoolean				_updateEnabled;
};

// --------------------------------------------------------------------------
// Common Attributes and Gadgets
// --------------------------------------------------------------------------
class IlvGradientSelectorCommon
{
public:
    IlvGradientSelectorCommon(IlvGradientSelector* gradSel);
    virtual ~IlvGradientSelectorCommon();

    const char*			getAlias() const;
    void			setAlias(const char* alias);

    const char*			getPreviousAlias() const;
    void			setPreviousAlias(const char* alias);

    IlvGradientTransformMode	getTransformMode() const;
    void			setTransformMode(IlvGradientTransformMode t);

    IlvGradientAspectRatio	getAspectRatio() const;
    void			setAspectRatio(IlvGradientAspectRatio a);

    IlvGradientSpread		getSpread() const;
    void			setSpread(IlvGradientSpread spread);

    IlvPtrnType			getType() const;
    void			setType(IlvPtrnType type);

    IlvDim			getWidth() const;
    void			setWidth(IlvDim width);

    IlvDim			getHeight() const;
    void			setHeight(IlvDim height);

    inline IlvTextField*	getAliasField() const 
				{
				    return _aliasTextField;
				}

    inline IlvComboBox*		getAspectRatioCombo() const 
				{
				    return _aspectRatioCombo;
				}

protected:
    IlvGradientSelector*	_gradSel;
    const char*			_previousAlias;
    const char*			_alias;
    IlvTextField*		_aliasTextField;
    IlvComboBox*		_transformModeCombo;
    IlvComboBox*		_aspectRatioCombo;
    IlvComboBox*		_spreadCombo;
    IlvComboBox*		_typeCombo;
    IlvNumberField*		_widthField;
    IlvNumberField*		_heightField;
};

// --------------------------------------------------------------------------
// ColorStops Attributes and Gadgets
// --------------------------------------------------------------------------
class IlvGradientSelectorColorStops
{
public:
    IlvGradientSelectorColorStops(IlvGradientSelector* gradSel);
    virtual ~IlvGradientSelectorColorStops();

    IlUInt 		getColorsCount() const;
    IlvColorStop**	getColorStops(IlUInt &count,
    				      IlBoolean duplicates = IlFalse) const;
    IlvColorStop*	getColorStop(IlUInt index) const;
    void		addColorStop(IlvColorStop* colStop, IlBoolean movable);
    void 		removeColorStop(IlvColorStop* colStop);
    void 		emptyColorStops();

    IlvGraphic*		getGraphic(IlvColorStop* colStop) const;
    IlvColorStop* 	whichSelected() const;
    void		select(IlvColorStop* colStop);

    IlvColor*		getColor() const;
    void		setColor(IlvColor* color);
    IlFloat		getOffset() const;
    void		setOffset(IlFloat offset);
    IlvIntensity	getAlpha() const;
    void		setAlpha(IlvIntensity alpha);

    inline
    IlvNumberField*	getAlphaField() const { return _alphaField; }
    inline
    IlvNumberField*	getOffsetField() const { return _offsetField; }
    inline
    IlvColorSelector*	getColorSelector() const { return _colorSel; }
    inline
    IlvFilledRectangle*	getPreviewRectangle() const
			{
			    return _previewRectangle;
			}
    inline
    IlvGradientPattern* getPreviewGradient() const { return _previewGradient; }

protected:
    IlvGradientSelector*	_gradSel;
    IlvFilledRectangle*		_previewRectangle;
    IlvGradientPattern*		_previewGradient;
    IlvColorSelector*		_colorSel;
    IlvFilledRectangle*		_colorRectangle;
    IlvSlider*			_alphaSlider;
    IlvNumberField*		_alphaField;
    IlvNumberField*		_offsetField;
    IlvButton*			_addColorStopButton;
    IlvButton*			_removeColorStopButton;
    IlvColorStop*		_selected;
    IlList			_previewSliders;
};

// --------------------------------------------------------------------------
// Linear Gradient Attributes and Gadgets
// --------------------------------------------------------------------------
class IlvGradientSelectorLinear
{
public:
    IlvGradientSelectorLinear(IlvGradientSelector* gradSel);
    virtual ~IlvGradientSelectorLinear();

    IlvPoint		getStartPoint() const;
    void		setStartPoint(IlvPoint);
    IlvPoint		getEndPoint() const;
    void		setEndPoint(IlvPoint);

    void		setMaxXPos(IlvDim pos);
    void		setMaxYPos(IlvDim pos);

    void		enable(IlBoolean);

protected:
    IlvGradientSelector*	_gradSel;
    IlvSlider*			_startXSlider;
    IlvNumberField*		_startXField;
    IlvSlider*			_startYSlider;
    IlvNumberField*		_startYField;
    IlvSlider*			_endXSlider;
    IlvNumberField*		_endXField;
    IlvSlider*			_endYSlider;
    IlvNumberField*		_endYField;
};

// --------------------------------------------------------------------------
// Radial Gradient Attributes and Gadgets
// --------------------------------------------------------------------------
class IlvGradientSelectorRadial
{
public:
    IlvGradientSelectorRadial(IlvGradientSelector* gradSel);
    virtual ~IlvGradientSelectorRadial();

    IlvPoint		getStartCenter() const;
    void		setStartCenter(IlvPoint);
    IlvDim		getStartRadius() const;
    void		setStartRadius(IlvDim);
    IlvPoint		getEndCenter() const;
    void		setEndCenter(IlvPoint);
    IlvDim		getEndRadius() const;
    void		setEndRadius(IlvDim);

    void		setMaxXPos(IlvDim pos);
    void		setMaxYPos(IlvDim pos);

    void		enable(IlBoolean);

protected:
    IlvGradientSelector*	_gradSel;
    IlvSlider*			_startXSlider;
    IlvNumberField*		_startXField;
    IlvSlider*			_startYSlider;
    IlvNumberField*		_startYField;
    IlvSlider*			_startRadiusSlider;
    IlvNumberField*		_startRadiusField;
    IlvSlider*			_endXSlider;
    IlvNumberField*		_endXField;
    IlvSlider*			_endYSlider;
    IlvNumberField*		_endYField;
    IlvSlider*			_endRadiusSlider;
    IlvNumberField*		_endRadiusField;
};

// --------------------------------------------------------------------------
// Preview
// --------------------------------------------------------------------------
class IlvGradientSelectorPreview
{
public:
    IlvGradientSelectorPreview(IlvGradientSelector* gradSel);
    virtual ~IlvGradientSelectorPreview();

    virtual void	update();

    inline
    IlvFilledRectangle*	getRectangle()		{ return _rectangle;}
    inline
    IlvFilledEllipse*	getEllipse()		{ return _ellipse;}

    inline IlvMenuItem* getEllipseItem() 	{ return _ellipseItem; }
    inline IlvMenuItem* getRectangleItem() 	{ return _rectangleItem; }
    inline IlvMenuItem* getCtrlPointsItem() 	{ return _ctrlPointsItem; }
    inline IlvMenuItem* getResetItem() 		{ return _resetItem; }
    inline IlvMenuItem* getZoomOutItem() 	{ return _zoomOutItem; }
    inline IlvMenuItem* getZoomInItem() 	{ return _zoomInItem; }
    inline IlvManager*	getManager()
			{
			    return _managerRectangle->getManager();
			}
    inline
    IlvManagerRectangle* getManagerRectangle() { return _managerRectangle; }

protected:
    void		computeAspectRatioBBox(IlvRect& rect);

    IlvGradientSelector*	_gradSel;
    IlvManagerRectangle*	_managerRectangle;
    IlvManagerViewHook*		_hook;
    IlvMenuItem*		_rectangleItem;
    IlvMenuItem*		_ellipseItem;
    IlvMenuItem*		_ctrlPointsItem;
    IlvMenuItem*		_resetItem;
    IlvMenuItem*		_zoomOutItem;
    IlvMenuItem*		_zoomInItem;
    IlvFilledRectangle*		_rectangle;
    IlvFilledEllipse*		_ellipse;
    IlvRectangle*		_gradientOutlineRectangle;
    IlvMarker*			_startPointMarker;
    IlvMarker*			_endPointMarker;
    IlvMarker*			_startCenterMarker;
    IlvMarker*			_endCenterMarker;
    IlvEllipse*			_startEllipse;
    IlvEllipse*			_endEllipse;
    IlvBitmap*			_backBitmap;
};

#endif /* !__Ilv_Edit_Grdselpn_H */
