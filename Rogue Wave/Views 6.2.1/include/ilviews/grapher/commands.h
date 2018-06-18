// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/commands.h
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
// Declaration of predefined grapher commands
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Commands_H
#define __Ilv_Grapher_Commands_H

#if !defined(__Ilv_Manager_Commands_H)
#include <ilviews/manager/commands.h>
#endif
#if !defined(__Ilv_Grapher_Grapher_H)
#include <ilviews/grapher/grapher.h>
#endif

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvAddNodeCommand
: public IlvManagerCommand {
    IlvActionDeclareMembers();
public:
    IlvAddNodeCommand(IlvManager* grapher, IlvGraphic* obj, int layer = 0);
    ~IlvAddNodeCommand();
    // ____________________________________________________________
    virtual void doIt();
    virtual void  unDo();
    IlvManagerCommand* copy() const;
protected:
    int _layer;
    IlvGraphic* _object;  // Object to add
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvRemoveNodeCommand
: public IlvManagerCommand {
    IlvActionDeclareMembers();
public:
    IlvRemoveNodeCommand(IlvManager* grapher, IlvGraphic* obj, int layer = 0);
    ~IlvRemoveNodeCommand();
    // ____________________________________________________________
    virtual void doIt();
    virtual void  unDo();
    IlvManagerCommand* copy() const;
protected:
    int _layer;
    IlvGraphic *_object;  // Object removed
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvAddLinkCommand
: public IlvManagerCommand {
    IlvActionDeclareMembers();
public:
    IlvAddLinkCommand(IlvManager* grapher, IlvLinkImage* obj, int layer = 0);
    ~IlvAddLinkCommand();
    // ____________________________________________________________
    virtual void doIt();
    virtual void  unDo();
    IlvManagerCommand* copy() const;
protected:
    int _layer;
    IlvLinkImage* _object; // Object to add
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvRemoveLinkCommand
: public IlvManagerCommand {
    IlvActionDeclareMembers();
public:
    IlvRemoveLinkCommand(IlvManager* grapher, IlvLinkImage* obj, int layer = 0);
    ~IlvRemoveLinkCommand();
    // ____________________________________________________________
    virtual void doIt();
    virtual void  unDo();
    IlvManagerCommand* copy() const;
protected:
    int _layer;
    IlvLinkImage* _object; // Object removed
    IlUInt	  _fPinIdx;
    IlUInt	  _tPinIdx;

    void initPinIdx(IlvLinkImage* link);

};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvReconnectLinkCommand
: public IlvManagerCommand {
    IlvActionDeclareMembers();
public:
    IlvReconnectLinkCommand(IlvGrapher*,
			    IlvLinkImage*, 
			    IlvLinkType, 
			    IlvGraphic*,
			    IlvGraphic*);
    ~IlvReconnectLinkCommand();

    virtual void doIt();
    virtual void  unDo();
    IlvManagerCommand* copy() const;
protected:
    IlvLinkImage*   _link;	// Considered link
    IlvLinkType	    _type;	// Cnxn type
    IlvGraphic*	    _prevNode;	// Previous node 
    IlvGraphic*	    _newNode;	// New node 
};

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvConnectPinCommand
: public IlvManagerCommand {
    IlvActionDeclareMembers();
public:
    IlvConnectPinCommand(IlvGrapher*, 
			 IlvLinkImage*,
			 IlvLinkType  type,
			 IlvGraphic*,
			 IlUInt,
			 IlUInt);
    ~IlvConnectPinCommand();
    // ____________________________________________________________
    virtual void doIt();
    virtual void  unDo();
    IlvManagerCommand* copy() const;
protected:
    IlvLinkImage*   _link; 
    IlvLinkType	    _type;
    IlvGraphic*	    _node;
    IlUInt	    _prevIdx;
    IlUInt	    _newIdx;
};

#endif /* !__Ilv_Grapher_Commands_H */
