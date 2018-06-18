// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/animacc.h
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
// Declaration of some IlvUserAccessor subclasses to emulate missing "native"
// accessors of the IlvGraphic class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Animacc_H
#define __Ilv_Protos_Animacc_H

#if !defined(__Ilv_Protos_Useracc_H)
#include <ilviews/protos/useracc.h>
#endif
#if !defined(__Ilv_Protos_Grphnode_H)
#include <ilviews/protos/grphnode.h>
#endif
#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
// ---------------------------------------------------------------------------
// IlvAnimationAccessor		Base user accessor class for animations.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvAnimationAccessor : public IlvUserAccessor
{
public:
    IlvAnimationAccessor(const char* name,
			 const IlvValueTypeClass* type,
			 IlvDisplay* display,
			 const char* periodVal);
    ~IlvAnimationAccessor();
    static void		UseSharedTimers(IlBoolean shared);
    static IlBoolean	UseSharedTimers();

    static void		SetTimersActive(IlBoolean running);
    static IlBoolean	GetTimersActive();

    void		initialize(const IlvAccessorHolder* object);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvAnimationAccessor);

protected:
    static IlBoolean	_TimersActive;
    IlvTimer*		_timer;
    IlvAccessorHolder*	_object;
    IlvDisplay*		_display;
    IlSymbol*		_periodVal;

    virtual IlvValue&	queryValue(const IlvAccessorHolder* object,
				   IlvValue& val) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder* object,
				    const IlvValue& val);
    virtual void	doit();
    virtual IlUInt	getSynchronizeCount();
    void		synchronize();
    inline
    IlvAccessorHolder*	getObject() { return(_object); }
    inline IlvDisplay*	getDisplay() { return(_display); }
    IlUInt		getPeriod();
    void		setTimer(IlUInt p);
    static void		TimerProc(IlvTimer* timer, IlAny arg);

private:
    IlBoolean		isShared() const;
    void		setShared(IlBoolean shared);
};

// ---------------------------------------------------------------------------
// IlvInvertAccessor	Animation accessor that makes objects invert
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvInvertAccessor : public IlvAnimationAccessor
{
public:
    IlvInvertAccessor(const char* name,
		      const IlvValueTypeClass* type,
		      IlvDisplay* display,
		      const char* periodVal,
		      const char* initialValue,
		      const char* alternateValue);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvInvertAccessor);

protected:
    IlSymbol*		_fgValue;
    IlSymbol*		_bgValue;

    virtual void	doit();
    virtual IlUInt	getSynchronizeCount();
};

// ---------------------------------------------------------------------------
// IlvBlinkAccessor	Animation accessor that makes objects blink
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvBlinkAccessor : public IlvAnimationAccessor
{
public:
    IlvBlinkAccessor(const char* name,
		     const IlvValueTypeClass* type,
		     IlvDisplay* display,
		     const char* periodVal,
		     const char* booleanValue);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvBlinkAccessor);

protected:
    virtual void	doit();
    virtual IlUInt	getSynchronizeCount();

    IlSymbol*		_visibleValue;
};

// ---------------------------------------------------------------------------
// IlvRotateAccessor	Rotate a node around its center.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvRotateAccessor : public IlvAnimationAccessor
{
public:
    IlvRotateAccessor(const char* name,
		      const IlvValueTypeClass* type,
		      IlvDisplay* display,
		      const char* periodVal,
		      const char* nodeName,
		      const char* angleValue,
		      const char* centerXValue,
		      const char* centerYValue);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvRotateAccessor);

protected:
    virtual void	doit();

    IlSymbol*		_nodeName;
    IlSymbol*		_angleValue;
    IlSymbol*		_centerXValue;
    IlSymbol*		_centerYValue;
};

IlvDECLAREINITPROCLASS(animacc)

#endif /* __Ilv_Protos_Animacc_H */
