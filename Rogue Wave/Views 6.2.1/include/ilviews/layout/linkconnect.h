// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/layout/linkconnect.h
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
// Declaration of the IlvLinkConnector class
// Defined in library ilvlayout
// --------------------------------------------------------------------------
#ifndef __Ilv_Layout_Linkconnect_H
#define __Ilv_Layout_Linkconnect_H

#if !defined(__Ilv_Layout_Macros_H)
#include <ilviews/layout/macros.h>
#endif /* __Ilv_Layout_Macros_H */

#if !defined(__Ilv_Grapher_Pin_H)
#include <ilviews/grapher/pin.h>
#endif /* __Ilv_Grapher_Pin_H */

#if !defined(__Ilv_Grapher_Links_H)
#include <ilviews/grapher/links.h>
#endif /* __Ilv_Grapher_Links_H */

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvLinkConnector
: public IlvGrapherPin
{
public:
    IlvLinkConnector(IlvGraphic*);
    ~IlvLinkConnector();

    IlBoolean	isPersistent() const;
    IlvGraphic*	getNode() const;

    virtual void	detach();
    virtual void	attach(IlvGraphic*);

    virtual void connectLink(IlvLinkImage*,  const IlvPoint&,
			     IlBoolean, IlvTransformer*) = 0;

    IlvDeclareLazyClassInfo();
protected:
private:
    IlvGraphic*	_obj;
};

// --------------------------------------------------------------------------
class ILVGRLEXPORTED IlvRelativeLinkConnector
: public IlvLinkConnector
{
public:
    IlvRelativeLinkConnector(IlvGraphic*);
    ~IlvRelativeLinkConnector();

    void	detach();

    IlBoolean	getConnectionPoint(IlvPoint& point,
				   const IlvLinkImage* link, 
				   IlBoolean origin,
				   const IlvTransformer* transformer) const;
    void	connectLink(IlvLinkImage*,
			    const IlvPoint&,
			    IlBoolean,
			    IlvTransformer*);

protected:
    IlBoolean zoomable() const;

public:

protected:
    void	linkRemoved(IlvLinkImage* link);
    void	allLinksRemoved();

public:
    IlBoolean	getLinkLocation(const IlvGraphic* node,
				const IlvGraphic* link,
				const IlvTransformer* t,
				IlvPoint& p) const;

    IlvDeclareLazyClassInfo();
private:
    IlvRect		_nodeRect;
    IlHashTable*	_connectionPoints;
    IlHashTable*	_selfLoopToConnectionPoints;

    void		cleanInternal();
    IlHashTable*	getConnectionTable(const IlvLinkImage*,
					   IlBoolean) const;
    void		store(const IlvLinkImage* link,
			      const IlvFloatPoint& point,
			      IlBoolean origin);
};

ILVGRLMODULEINIT(l_linkconnect);

#endif /* !__Ilv_Layout_Linkconnect_H */
