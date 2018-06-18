// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/observer.h
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
#ifndef __Ilv_Grapher_Observer_H
#define __Ilv_Grapher_Observer_H

#if !defined(__Ilv_Manager_Observer_H)
#include <ilviews/manager/observer.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif
#if !defined(__Ilv_Grapher_Links_H)
#include <ilviews/grapher/links.h>
#endif

#define IlvGrapherMsgContentsMask		0x00000100

#define IlvGrapherMsgTopologyMask		0x00000200

#define IlvGrapherMsgLinkConnection		2048

class ILVGRAPHEXPORTED IlvLinkConnectionMessage
: public IlvManagerObjectMessage
{
public:
    IlvLinkConnectionMessage(IlvLinkImage* link,
			     IlvLinkType type,
			     IlvGraphic* oldNode)
    : IlvManagerObjectMessage(IlvGrapherMsgLinkConnection, link, 
			      IlvGrapherMsgTopologyMask),
      _type(type),
      _oldNode(oldNode){}

    inline IlvLinkImage* getLink() const 
    { return IL_CAST(IlvLinkImage*, getObject());} 

    inline IlvGraphic* getOldNode() const { return _oldNode; }

    inline IlvLinkType getType() const {return _type;}

protected:
    IlvLinkType _type;
    IlvGraphic* _oldNode;
};

#endif /* __Ilv_Grapher_Observer_H */
