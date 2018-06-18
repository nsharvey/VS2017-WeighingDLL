// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/grapher/graphdoc.h
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
// Declaration of the IlvDvGrapherDocument class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Grapher_Graphdoc_H)
#define __Ilv_Appframe_Grapher_Graphdoc_H

#if !defined(__Ilv_Appframe_Manager_Managdoc_H)
#include <ilviews/appframe/manager/managdoc.h>
#endif

#if !defined(__Ilv_Appframe_Grapher_Macros_H)
#include <ilviews/appframe/grapher/macros.h>
#endif

#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif

// --------------------------------------------------------------------------
// IlvDvGrapherDocument class
// --------------------------------------------------------------------------
class ILVDVGRAPHEREXPORTED IlvDvGrapherDocument : public IlvDvManagerDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvGrapherDocument();
    virtual ~IlvDvGrapherDocument();

    // ----------------------------------------------------------------------
    virtual IlBoolean	initializeDocument(IlAny = 0);

    virtual void	clean();
    // ----------------------------------------------------------------------
    // Basic properties
    IlvGrapher*		getGrapher() const;

    // ----------------------------------------------------------------------
    // IO
    virtual void	serialize(IlvDvStream& stream);

    IlvDvDeclareInterface();

protected:
    virtual IlvManager*	createManager(IlvDisplay*);
};

// --------------------------------------------------------------------------
ILVDVGRAPHERMODULEINIT(graphdoc);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Grapher_Graphdoc_H */
