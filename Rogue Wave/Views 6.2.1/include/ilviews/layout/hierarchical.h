// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/hierarchical.h
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
// Declaration of the IlvHierarchicalLayout class
// Defined in library ilvhierarchical
// --------------------------------------------------------------------------

#ifndef __Ilv_Layout_Hierarchical_H
#define __Ilv_Layout_Hierarchical_H

#include <assert.h>

#if !defined(__Ilv_Layout_Gphlayout_H)
#  include <ilviews/layout/gphlayout.h>
#endif /* __Ilv_Layout_Gphlayout_H */

#if !defined(ILVBUILDLIBS) && defined(_MSC_VER) && !defined(ILV_DONT_USE_LIBPRAGMA)
#  pragma comment(lib, "ilvhierarchical.lib")
#endif

#if defined(ILVHIERLIB)
#define ILVHIEREXPORTED ILVBASEEXPORTED
#define ILVHIEREXPORTEDFUNCTION(type)	ILVBASEEXPORTEDFUNCTION(type)
#define ILVHIEREXPORTEDVAR(type)	ILVBASEEXPORTEDFUNCTION(type)
#else  /* !ILVHIERLIB */
#define ILVHIEREXPORTED ILVBASEIMPORTED
#define ILVHIEREXPORTEDFUNCTION(type)	ILVBASEIMPORTEDFUNCTION(type)
#define ILVHIEREXPORTEDVAR(type)	ILVBASEIMPORTEDFUNCTION(type)
#endif /* !ILVHIERLIB */

#define ILVHIERMODULEINIT(m)	IL_MODULEINIT(m, ILVHIEREXPORTED);

// Forward declaration.

class ILVHIEREXPORTED IlvHGraph;


class ILVHIEREXPORTED IlvHierarchicalLayout
: public IlvGraphLayout {
public:

    IlvHierarchicalLayout();
    virtual ~IlvHierarchicalLayout();

    // This is Views specific
    IlvDeclareClassInfo();
protected:
    virtual void layout();
private:
    // ----------------------------------------------------------------------
    // Properties

    char* _linkPriorityProperty;
    char* _linkStyleProperty;
    char* _specLevelIndexProperty;
    char* _calcLevelIndexProperty;
    char* _specPositionIndexProperty;
    char* _calcPositionIndexProperty;
private:
    // ----------------------------------------------------------------------
    // Storage for the layout options

    static const IlvLayoutLinkStyle _defaultGlobalLinkStyle;
    IlvLayoutLinkStyle _globalLinkStyle;
    static const IlvLayoutConnectorStyle _defaultConnectorStyle;
    IlvLayoutConnectorStyle _connectorStyle;
    static const IlvDirection _defaultFlowDirection;
    IlvDirection _flowDirection;
    static const IlvDirection _defaultLevelJustification;
    IlvDirection _levelJustification;
    static const IlvPos _defaultNodeOffsetX;
    IlvPos _nodeOffsetX;
    static const IlvPos _defaultNodeOffsetY;
    IlvPos _nodeOffsetY;
    static const IlvPos _defaultLinkOffsetX;
    IlvPos _linkOffsetX;
    static const IlvPos _defaultLinkOffsetY;
    IlvPos _linkOffsetY;
    static const IlvPos _defaultNodeLinkOffsetX;
    IlvPos _nodeLinkOffsetX;
    static const IlvPos _defaultNodeLinkOffsetY;
    IlvPos _nodeLinkOffsetY;

    // timer to avoid that layoutStepPerformed is called too often.
    IlvRunTimeType _lastLayoutStepPerformedTime;

    // flag to indicate that we run out of time
    IlBoolean _preliminaryStopped;
public:
    // ----------------------------------------------------------------------
    // The supports-features
    virtual IlBoolean supportsPreserveFixedNodes() const;
    virtual IlBoolean supportsPreserveFixedLinks() const;
    virtual IlBoolean supportsAllowedTime() const;

    // ----------------------------------------------------------------------
    // The layout parameters
    void setGlobalLinkStyle(IlvLayoutLinkStyle style);
    IlvLayoutLinkStyle getGlobalLinkStyle() const;

    void setConnectorStyle(IlvLayoutConnectorStyle style);
    IlvLayoutConnectorStyle getConnectorStyle() const;

    void setFlowDirection(IlvDirection flowDirection);
    IlvDirection getFlowDirection() const;

    void setLevelJustification(IlvDirection justification);
    IlvDirection getLevelJustification() const;

    void setHorizontalNodeOffset(IlvPos offset);
    IlvPos getHorizontalNodeOffset() const;

    void setVerticalNodeOffset(IlvPos offset);
    IlvPos getVerticalNodeOffset() const;

    void setHorizontalLinkOffset(IlvPos offset);
    IlvPos getHorizontalLinkOffset() const;

    void setVerticalLinkOffset(IlvPos offset);
    IlvPos getVerticalLinkOffset() const;

    void setHorizontalNodeLinkOffset(IlvPos offset);
    IlvPos getHorizontalNodeLinkOffset() const;

    void setVerticalNodeLinkOffset(IlvPos offset);
    IlvPos getVerticalNodeLinkOffset() const;

    void setLinkStyle(IlAny link, IlvLayoutLinkStyle style);
     IlvLayoutLinkStyle getLinkStyle(IlAny link) const;

    void setLinkPriority(IlAny link, IlDouble priority);
    IlDouble getLinkPriority(IlAny link) const;

    void setSpecNodeLevelIndex(IlAny node, IlInt index);
    IlInt getSpecNodeLevelIndex(IlAny node) const;

    IlInt getCalcNodeLevelIndex(IlAny node) const;
    // Sets the calculated level index of a node during layout.
    // This is not documented since it does not make sense to be called from
    // outside layout.
    void setCalcNodeLevelIndex(IlAny node, IlInt index);

    void setSpecNodePositionIndex(IlAny node, IlInt index);

    IlInt getSpecNodePositionIndex(IlAny node) const;

    IlInt getCalcNodePositionIndex(IlAny node) const;
    // Sets the calculated index of the node position within a level during
    // layout. This is not documented since it does not make sense to be
    // called from outside layout.
    void setCalcNodePositionIndex(IlAny node, IlInt index);

    // ----------------------------------------------------------------------
    // Remaining methods
    virtual void detach();

    virtual void cleanObjectProperties(IlAny nodeOrLink);
private:
    void transferLayoutOptions(IlvHGraph* graph);
public:
    // Informs the layout instance that a step of the layout algorithm has
    // been performed. The method notified the listeners of the layout
    // events.
    // In order to automatically avoid that notification is done too often,
    // it notifies only if there was a delay of at least 50 ms since the
    // last notification.
    void callLayoutStepPerformed();

    // Returns IlTrue if the layout can continue.
    IlBoolean mayContinue() const;
public:
    DeclareLayoutAccessors();
    virtual IlBoolean getValueDescriptor(IlvValue&) const;
    static IlSymbol* _globalLinkStyleValue;
    static IlSymbol* _connectorStyleValue;
    static IlSymbol* _flowDirectionValue;
    static IlSymbol* _levelJustificationValue;
    static IlSymbol* _horizontalNodeOffsetValue;
    static IlSymbol* _verticalNodeOffsetValue;
    static IlSymbol* _horizontalLinkOffsetValue;
    static IlSymbol* _verticalLinkOffsetValue;
    static IlSymbol* _horizontalNodeLinkOffsetValue;
    static IlSymbol* _verticalNodeLinkOffsetValue;
};

ILVHIERMODULEINIT(lh_hierarchical)

// --------------------------------------------------------------------------
#endif /* !__Ilv_Layout_Hierarchical_H */
