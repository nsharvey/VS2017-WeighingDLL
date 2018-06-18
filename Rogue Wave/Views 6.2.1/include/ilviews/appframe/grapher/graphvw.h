// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/grapher/graphvw.h
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
// Declaration of the IlvDvGrapherView class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Grapher_Graphvw_H)
#define __Ilv_Appframe_Grapher_Graphvw_H

#if !defined(__Ilv_Appframe_Manager_Managvw_H)
#  include <ilviews/appframe/manager/managvw.h>
#endif
#if !defined(__Ilv_Appframe_Grapher_Macros_H)
#  include <ilviews/appframe/grapher/macros.h>
#endif

class IlvGrapher;
class IlvDvGrapherDocument;
// --------------------------------------------------------------------------
// IlvDvGrapherView class
// --------------------------------------------------------------------------
class ILVDVGRAPHEREXPORTED IlvDvGrapherView
: public IlvDvManagerView {
    IlvDvDeclareViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvGrapherView(IlvGadgetContainer* parent);
    virtual ~IlvDvGrapherView();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual void		initializeView();

    // ----------------------------------------------------------------------
    // Basic properties
    IlvDvGrapherDocument*	getGrapherDocument() const;
    IlvGrapher*			getGrapher() const;

    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();
};

ILVDVGRAPHERMODULEINIT(graphvw);
#endif /* !__Ilv_Appframe_Grapher_Graphvw_H */
