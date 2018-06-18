// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/util/modeldfs.h
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
// Declaration of the IlvGraphModelDFS class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Util_Modeldfs_H
#define __Ilv_Layout_Util_Modeldfs_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif

#if !defined(__Ilv_Layout_Graphmod_H)
#include <ilviews/layout/graphmod.h>
#endif

#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

class ILVGRLEXPORTED IlvGraphModelDFS
{
public:
    IlvGraphModelDFS();
    virtual ~IlvGraphModelDFS();

    IlAny	execute(IlvGraphModel*, IlAny, IlAny);

protected:
    virtual IlAny	dfsVisit(IlAny);
    virtual void	markNode(IlAny);
    virtual IlBoolean	isMarkedNode(IlAny);
    virtual void	markLink(IlAny);
    virtual IlBoolean	isMarkedLink(IlAny);
    virtual void	initResult();
    virtual void	startVisit(IlAny);
    virtual void	traverseDiscovery(IlAny, IlAny);
    virtual void	traverseBack(IlAny, IlAny);
    virtual IlBoolean	isDone();
    virtual void	finishVisit(IlAny);
    virtual IlAny	result();

    IlvGraphModel*	_model;
    IlAny		_visitResult;
    IlAny		_startNode;
    IlHashTable*	_markedVerts;
    IlHashTable*	_markedEdges;
private:
};

#endif /* !__Ilv_Layout_Util_Modeldfs_H */
