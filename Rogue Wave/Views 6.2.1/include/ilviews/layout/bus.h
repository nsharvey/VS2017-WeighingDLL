// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/bus.h
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
// Declaration of the IlvBusLayout class
// Defined in library ilvbus
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Bus_H
#define __Ilv_Layout_Bus_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvbus.lib")
#endif

#if !defined(__Ilv_Layout_Gphlayout_H)
#include <ilviews/layout/gphlayout.h>
#endif /* __Ilv_Layout_Gphlayout_H */

#if !defined(__Ilv_Graphics_Polyline_H)
#include <ilviews/graphics/polyline.h>
#endif /* __Ilv_Graphics_Polyline_H */

#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif /* __Ilv_Base_Hash_H */

#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif /* __Ilv_Base_List_H */

#if defined(ILVBUSLIB)
#define ILVBUSEXPORTED ILVBASEEXPORTED
#define ILVBUSEXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVBUSEXPORTEDVAR(type)	ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVBUSLIB */
#define ILVBUSEXPORTED ILVBASEIMPORTED
#define ILVBUSEXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVBUSEXPORTEDVAR(type)	ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVBUSLIB */

#define ILVBUSMODULEINIT(m)	IL_MODULEINIT(m, ILVBUSEXPORTED);

class IlvBusLayout;
class IlvBusLinkConnector;

enum IlvBusOrder {
    IlvBusNoOrdering = 0,
    IlvBusOrderByHeight = 1,
    IlvBusOrderByIndex = 2
};

class ILVBUSEXPORTED IlvBusLayout : public IlvGraphLayout
{
public:
    IlvBusLayout();
    ~IlvBusLayout();

    void		detach();

    virtual void	cleanObjectProperties(IlAny nodeOrLink);

private:
    void		initializeInternalVariables(const IlvRect&);

protected:
    void		layout();

public:
    IlUInt		getIndexNode() const;
    const IlArray&	getVectNodes() const;

private:
    IlList*		getNodesOnBus(IlvPolyline*) const;
public:
    void		setIndex(IlAny, IlInt);
    IlInt		getIndex(IlAny) const;

    void		createOneLevel(IlvPolyline*);

private:
    void		createBusLine(IlUInt, IlvPolyline*);

    IlAny		getNextNode(IlInt, IlUInt, IlUInt, IlBoolean);
    void		moveNodeAlone(IlAny, IlUInt);
    void		moveNode(IlAny, IlUInt, IlUInt);
    IlInt		getAvailableWidthOnLevel() const;
    IlUInt		getWidthOfNode(IlAny) const;

public:
    IlInt		getYofBusLevel(IlInt) const;

private:
    void		setYofBusLevel(IlUInt, IlInt);
    IlUInt		getMaxHeight(IlAny, IlUInt) const;

public:
    void		removeUselessPoints(IlvPolyline* bus);

private:
    void		determineNodesOnBus(IlList*, IlAny);

public:
    IlBoolean		supportsPreserveFixedNodes() const;
    IlBoolean		supportsLayoutRegion() const;

    void		setBus(IlvPolyline*);
    IlvPolyline*	getBus() const;

private:
    IlBoolean		checkBus(IlvPolyline* bus, IlBoolean illegalArgument);

    void		setLinkConnector(IlvPolyline*);
    IlvBusLinkConnector* getLinkConnector() const;

protected:
    IlvBusLinkConnector* makeLinkConnector() const;

public:
    IlvPoint*		getConnectionPoint(IlAny,
					   IlvPolyline*,
					   IlvTransformer* = 0);

public:
    void		setOrdering(IlvBusOrder value);
    IlvBusOrder		getOrdering() const;

    void		setHorizontalOffset(IlUInt value);
    IlUInt		getHorizontalOffset() const;
    void		setVerticalOffsetToLevel(IlUInt value);
    IlUInt		getVerticalOffsetToLevel() const;
    void		setVerticalOffsetToPreviousLevel(IlUInt value);
    IlUInt		getVerticalOffsetToPreviousLevel() const;

    void		setMargin(IlUInt value);
    IlUInt		getMargin() const;
    void		setMarginOnBus(IlUInt value);
    IlUInt		getMarginOnBus() const;
    void		setConnectionOnBusMargin(IlUInt value);
    IlUInt		getConnectionOnBusMargin() const;

    void		setLinkStyle(IlvLayoutLinkStyle value);
    IlvLayoutLinkStyle	getLinkStyle() const;

    static IlInt NoIndex;

    // non private because used in IlvApplyObject...
    IlvPolyline* _bus;
    IlUInt	_indexNode;
    IlInt _xMin, _xMax, _yMin, _yMax;

    // not private because used in IlvApplyObject
    IlInt	_indexNextPoint;
    IlInt	_nextLineNumber;
    // non private because used in IlvApplyObject...
    IlInt	_numberOfPoints;

    // ------------------- Accessors ----------------------------
    DeclareLayoutAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue&) const;

    static IlSymbol*	_orderingValue;
    static IlSymbol*	_horizontalOffsetValue;
    static IlSymbol*	_verticalOffsetToLevelValue;
    static IlSymbol*	_verticalOffsetToPerviousLevelValue;
    static IlSymbol*	_marginValue;
    static IlSymbol*	_marginOnBusValue;
    static IlSymbol*	_connectionOnBusMarginValue;
    static IlSymbol*	_linkStyleValue;
    IlvDeclareClassInfo();

private:
    IlvBusOrder		_ordering;
    IlUInt		_horizSpace;
    // the space between a node and the bus level to which it is connected
    IlUInt		_vertSpaceNodeToLevel;
    // the space between a node and the bus level below it
    IlUInt		_vertSpaceNodeToPreviousLevel;
    IlUInt		_margin;
    IlUInt		_marginOnBus;
    IlUInt		_connectionOnBusMargin;

    IlvLayoutLinkStyle	_linkStyle;

    IlHashTable*	_neighbors;

    IlvPoint		_fromPoint;
    IlvPoint		_toPoint;

    // to be initialized each time the layout is performed
    IlArray		_vectYofLevel;
    IlArray		_vectNodes;
    IlHashTable*	_nodesPosition;
    IlvBusLinkConnector* _linkConnector;

    IlAny		_nodeFromPreviousLevel;

    char*		_indexPropertyLabel;

    static const IlvBusOrder		DefaultOrdering;
    static const IlUInt			DefaultHorizSpace;
    static const IlUInt			DefaultVertSpaceNodeToLevel;
    static const IlUInt			DefaultVertSpaceNodeToPreviousLevel;
    static const IlUInt			DefaultMargin;
    static const IlUInt			DefaultMarginOnBus;
    static const IlUInt			DefaultConnectionOnBusMargin;
    static const IlvLayoutLinkStyle	DefaultLinkStyle;
};

ILVBUSMODULEINIT(lb_bus)
#endif /* !__Ilv_Layout_Bus_H */
