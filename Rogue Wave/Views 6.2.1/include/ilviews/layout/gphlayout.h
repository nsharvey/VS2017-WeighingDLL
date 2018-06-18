// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/gphlayout.h
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
// Declaration of the IlvGraphLayout class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Gphlayout_H
#define __Ilv_Layout_Gphlayout_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Il_Iostream_H)
#include <ilog/iostream.h>
#endif /* __Il_Iostream_H */

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif /* __Ilv_Ilv_H */

#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif /* __Ilv_Grapher_Grapher_H */

#if !defined(__Ilv_Layout_Gphadapt_H)
#include <ilviews/layout/gphadapt.h>
#endif /* __Ilv_Layout_Gphadapt_H */

#if !defined(__Ilv_Layout_Listener_H)
#include <ilviews/layout/listener.h>
#endif /* __Ilv_Layout_Listener_H */

#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif /* __Ilv_Itf_Value_H */

#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif /* __Ilv_Base_Value_H */

#if !defined(__Ilv_Util_Runtime_H)
#include <ilviews/util/runtime.h>
#endif /* __Ilv_Util_Runtime_H */

class IlvGraphLayoutReport;
class IlvGraphLayoutObserver;
class IlvMgrView;

#define DeclareLayoutAccessors()				\
    virtual IlvValue&  queryValue(IlvValue&) const;		\
    virtual IlBoolean applyValue(const IlvValue&);		\
    static void GetAccessors(const IlSymbol* const**,		\
			     const IlvValueTypeClass* const**,	\
			     IlUInt&)

// ----------------------------------------------------------------------
enum IlvLayoutLinkStyle {
    IlvLayoutNoReshapeLinkStyle = 0,
    IlvLayoutStraightLineLinkStyle = 1,
    IlvLayoutOrthogonalLinkStyle = 2,
    IlvLayoutDirectLinkStyle = 3,
    IlvLayoutPolylineLinkStyle = 4,
    IlvLayoutMixedLinkStyle = 5
};

// ----------------------------------------------------------------------
enum IlvLayoutConnectorStyle {
    IlvLayoutAutomaticPins = 0,
    IlvLayoutCenteredPins = 1,
    IlvLayoutClippedPins = 2,
    IlvLayoutEvenlySpacedPins = 3
};

// ----------------------------------------------------------------------
class ILVGRLEXPORTED IlvGraphLayout : public IlvGraphModelListener
{
public:
    IlvGraphLayout();
    virtual ~IlvGraphLayout();

    IlUInt		getInstanceId() const;

    virtual void	attach(IlvGrapher* grapher);
    virtual void	attach(IlvGraphModel* graphModel);
    virtual void	detach();

    virtual void	cleanObjectProperties(IlAny nodeOrLink);
    inline void		needToCleanObjectProperties(IlBoolean val)
			{
			    _needToCleanObjectProperties = val;
			}
    inline IlBoolean	isCleanObjectPropertiesNeeded() const
			{
			    return _needToCleanObjectProperties;
			}

    IlvGraphModel*	getGraphModel() const;
    void		setGrapher(IlvGrapher* grapher);
    IlvGrapher*		getGrapher() const;

    IlBoolean		isIlvGrapherAttached() const;

protected:
    virtual IlvGraphLayoutReport* createLayoutReport();

public:
    IlvGraphLayoutReport* getLayoutReport() const;

    IlvGraphLayoutReport*	performLayout();

protected:
    virtual IlBoolean	isLayoutNeeded() const;

protected:
    virtual void	layout() = 0;

public:
    IlBoolean		isLayoutRunning() const;

public:
    void	addGraphLayoutEventListener(const IlvGraphLayoutListener*);
    void	removeGraphLayoutEventListener(const IlvGraphLayoutListener*);

    virtual void	layoutStepPerformed();

    IlBoolean		isStructureUpToDate() const;

public:
    void		setStructureUpToDate(IlBoolean);

    void		setGeometryUpToDate(IlBoolean);

public:
    IlBoolean		isGeometryUpToDate() const;

  ////////////////////////////////////////////////////////////////
  //          PARAMETERS
  ////////////////////////////////////////////////////////////////

public:
    void		setParametersUpToDate(IlBoolean);
    virtual IlBoolean	isParametersUpToDate() const;

    virtual void	setUseDefaultParameters(IlBoolean arg);
    virtual IlBoolean	isUseDefaultParameters() const;
    void		setUsingViewCoordinates(IlBoolean arg);
    IlBoolean		isUsingViewCoordinates() const;

    virtual void	setLinkReplacementAllowed(IlBoolean);
    virtual IlBoolean	isLinkReplacementAllowed() const;

    void		setLinkConnectorReplacementAllowed(IlBoolean allow);

    IlBoolean		isLinkConnectorReplacementAllowed() const;

    virtual IlBoolean	supportsPreserveFixedNodes() const;
    virtual void	setPreserveFixedNodes(IlBoolean arg);
    virtual IlBoolean	isPreserveFixedNodes() const;
    virtual void	setFixed(IlAny nodeOrLink, IlBoolean val);
    IlBoolean		isFixed(IlAny nodeOrLink) const;
    void		unfixAllNodes();

    virtual IlBoolean	supportsPreserveFixedLinks() const;
    virtual void	setPreserveFixedLinks(IlBoolean arg);
    virtual IlBoolean	isPreserveFixedLinks() const;
    void		unfixAllLinks();

    virtual IlBoolean	supportsAnimation() const;
    void		setAnimate(IlBoolean arg);
    IlBoolean		isAnimate() const;

private:
    IlvLayoutGraphicFilter*	createGraphicFilterIfNeeded();

public:
    virtual IlBoolean	supportsMemorySavings() const;
    virtual IlBoolean	isMemorySavings() const;
    virtual void	setMemorySavings(IlBoolean arg);

    virtual IlBoolean	supportsLayoutRegion() const;
    void		setLayoutRegion(IlvMgrView* view);
    void		setLayoutRegion(IlvMgrView* view,
					const IlvRect& rect);
    void		setLayoutRegion(const IlvRect& rect);
    void		getLayoutRegion(IlvRect& rect) const;

    IlBoolean		isFitToView() const;

    IlvMgrView*		getFirstManagerView() const;

    virtual IlBoolean	supportsRandomGenerator() const;

    virtual void	setSeedValueForRandomGenerator(IlUShort seedValue);
    virtual IlUShort	getSeedValueForRandomGenerator();
    virtual void	setUseSeedValueForRandomGenerator(IlBoolean);
    virtual IlBoolean	isUseSeedValueForRandomGenerator();

    virtual IlBoolean	supportsAllowedTime() const;
    virtual
    IlvRunTimeType	getAllowedTime() const;
    void		setAllowedTime(IlvRunTimeType time);
    virtual IlBoolean	isLayoutTimeElapsed() const;

    void		layoutRunning(IlBoolean);

    void		contentsChanged(const IlvGraphModelEvent& event);

    DeclareLayoutAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_useDefaultValuesValue;
    static IlSymbol*	_preserveFixedNodesOptionValue;
    static IlSymbol*	_animateValue;
    static IlSymbol*	_layoutMethod;
    static IlSymbol*	_useViewCoordinatesValue;

    IlvDeclareLazyClassInfo();

protected:

private:
    void		initPropertiesNames();

    IlvGrapherAdapter*		_adapter;
    IlvGraphModel*		_graphModel;
    IlBoolean			_isIlvGrapherAttached;
    IlvGraphLayoutReport*	_layoutReport;
    IlvMgrView*	  		_viewToFit;
    IlvRect			_rectangleToFit;
    IlBoolean			_fitToView;
    IlBoolean			_parametersUpToDate;
    IlBoolean			_defaultUseDefaultValues;
    IlUShort			_defaultSeedValue;
    IlBoolean			_defaultUserDefinedSeedOption;
    IlBoolean			_defaultPreserveFixedNodesOption;
    IlBoolean			_defaultPreserveFixedLinksOption;
    IlBoolean			_defaultAnimate;
    IlBoolean			_defaultLinkReplacementAllowed;
    IlBoolean			_defaultLinkConnectorReplacementAllowed;
    IlBoolean			_useDefaultValues;
    IlvRunTimeType		_defaultAllowedTime;
    IlBoolean			_defaultIsMemorySavings;
    IlUShort			_seedValue;
    IlBoolean			_linkReplacementAllowed;
    IlBoolean			_linkConnectorReplacementAllowed;
    IlBoolean			_userDefinedSeedOption;
    IlBoolean			_preserveFixedNodesOption;
    IlBoolean			_preserveFixedLinksOption;
    IlBoolean			_animate;
    IlvRunTimeType		_allowedTime;
    IlBoolean			_isMemorySavings;
    IlString			_fixedPropertyLabel;
    static IlUInt		_uniqueIdCounter;
    IlUInt			_uniqueId;
    IlBoolean			_structureUpToDate;

    IlBoolean			_geometryUpToDate;
    IlvTransformer*		_identityTransformer;
    IlBoolean			_isLayoutRunning;
    IlvLayoutGraphicFilter*	_graphicFilter;
    IlvLayoutGraphicFilter*	_userGraphicFilter;
    IlvRect			_oldLayoutRegion;
    IlBoolean			_isUsingViewCoordinates;
    IlvGraphLayoutEvent*	_layoutEvent;
    IlList			_listenerList;
    IlvGraphLayoutObserver*	_observer;
    IlBoolean			_needToCleanObjectProperties;
    IlBoolean			_ownsGraphModel;
};

ILVGRLMODULEINIT(l_gphlayout)
#endif /* !__Ilv_Layout_Gphlayout_H */
