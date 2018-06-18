// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/eventacc.h
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
// Declaration of the "interactor" accessor classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Eventacc_H
#define __Ilv_Protos_Eventacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// ---------------------------------------------------------------------------
// IlvAbstractEventAccessor
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvAbstractEventAccessor : public IlvUserAccessor
{
public:
     IlvAbstractEventAccessor(const char*		name,
			      const IlvValueTypeClass*	type,
			      const char*		nodeName);
    ~IlvAbstractEventAccessor();

    virtual void	initialize(const IlvAccessorHolder* object);
    virtual IlBoolean	handleEvent(IlvAccessorHolder*	object,
				    IlvGraphic*		g,
				    IlvEvent&		event,
				    IlvView*		view,
				    IlvTransformer*	t);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvAbstractEventAccessor);

    inline
    const IlSymbol*	nodeName() const { return _nodeName; }

protected:
    IlSymbol*			_nodeName;
    const IlvAccessorHolder*	_object;
};

// ---------------------------------------------------------------------------
// IlvEventAccessor
// ---------------------------------------------------------------------------
enum IlvEventAccessorData {
    IlvEventAccessorType,
    IlvEventAccessorDetail,
    IlvEventAccessorModifiers,
    IlvEventAccessorX,
    IlvEventAccessorY,
    IlvEventAccessorGlobalX,
    IlvEventAccessorGlobalY
};

class ILVPROEXPORTED IlvEventAccessor : public IlvAbstractEventAccessor
{
public:
    IlvEventAccessor(const char*		name,
		     const IlvValueTypeClass*	type,
		     const char*		nodeName,
		     IlvEventType		eventType,
		     IlUShort			detail,
		     IlUShort			modifiers,
		     IlvEventAccessorData	whichData);
    virtual IlBoolean	handleEvent(IlvAccessorHolder*	object,
				    IlvGraphic*		g,
				    IlvEvent&,
				    IlvView*,
				    IlvTransformer*	t);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvEventAccessor);

protected:
    IlvEventType		_eventType;
    IlUShort			_detail;
    IlUShort			_modifiers;
    IlvEventAccessorData	_whichData;
};

IlvDECLAREINITPROCLASS(eventacc)

#endif /* __Ilv_Protos_Eventacc_H */
