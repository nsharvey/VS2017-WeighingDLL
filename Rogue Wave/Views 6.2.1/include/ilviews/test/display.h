// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/test/display.h
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
// Declaration of the IlvDisplayTestApi base class
// Defined in library display
// --------------------------------------------------------------------------
#ifndef __Ilv_Test_Display_H
#define __Ilv_Test_Display_H

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Event_H)
#include <ilviews/base/event.h>
#endif

class IlvDisplayTestApi;

typedef IlvDisplayTestApi* (*IlvDisplayTestApiFactory) ();

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvDisplayTestApi
{
public:
    virtual ~IlvDisplayTestApi();
    // ____________________________________________________________
    // after receiving event notification, before calling callbacks
    virtual void	inputNotify(IlvView* view, IlvEvent& event);
    virtual void	destroyNotify(IlvView* view);
    virtual void	resizeNotify(IlvView* view, IlvRect& rect);

    // explicit geometry change by program requests
    virtual void	moveResizeNotify(IlvAbstractView* view,
					 IlvPos           newX,
					 IlvPos           newY,
					 IlvDim           newW,
					 IlvDim           newH);
    virtual void	moveNotify(IlvAbstractView* view,
				   IlvPos           newX,
				   IlvPos           newY);
    virtual void	resizeCallNotify(IlvAbstractView* view,
					 IlvDim           newW,
					 IlvDim           newH);

    static IlBoolean	SetFactory(IlvDisplayTestApiFactory factory);
    static IlvDisplayTestApiFactory	GetFactory();

protected:
    IlvDisplayTestApi() {}

    static IlvDisplayTestApiFactory	_factory;
};

#endif /* !__Ilv_Test_Display_H */
