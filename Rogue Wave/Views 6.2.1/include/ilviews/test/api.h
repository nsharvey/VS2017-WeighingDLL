// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/test/api.h
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
// Declaration of the IlvTestApi  base class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Test_Api_H
#define __Ilv_Test_Api_H

#if !defined(__Ilv_Test_Display_H)
#include <ilviews/test/display.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvTestApi : public IlvDisplayTestApi
{
public:
    IlvTestApi();
    virtual ~IlvTestApi();
    // ____________________________________________________________
    // Static functions for Test Api requests
    static
    IlvView* const*	TopLevelWinNumber(IlUInt& nb_win,
					  IlvDisplay* display = 0);
    static IlBoolean	IsObjectVisible(const IlvGraphic* object,
					const IlvView*	view,
					IlvRect& visibleRegion);

    static
    const char* const*	GetObjectCallbackTypesList(const IlvGraphic* obj,
						   IlUInt& count);

    static
    IlvGraphic* const*	GetObjects(const IlvView* ownerView, IlUInt& count);
    static
    IlvGraphic* const*	GetObjects(const IlvGraphic* complexGraphic,
				   IlUInt& count);

    static const IlvDisplay* const* GetAllDisplays(IlUInt& count);

    static void		ObjCoordinatesInTopWindow(const IlvGraphic* object,
						  const IlvView*    ownerView,
						  IlvRect&          rect);

    static void		HighLight(IlvView*	view,
				  IlvPos	x,
				  IlvPos	y,
				  IlvDim	width,
				  IlvDim	height,
				  IlvDisplay*	display = 0);

    static
    const IlvView*	UnderPointer(IlvGraphic*&	object,
				     IlvDisplay*	display = 0);

    // Called before actual callbacks are called
    virtual void	callbackNotifyStart(IlvGraphic*	obj,
					    const IlSymbol* callBacktype);
    // One call for each callback of the object
    virtual void	callbackNotify(IlvGraphic*     obj,
				       const IlSymbol* callBacktype,
				       IlAny           clientData,
				       const IlSymbol* callbackName = 0);
    // Called after actual callbacks are called
    virtual void	callbackNotifyEnd(IlvGraphic* obj,
					  const IlSymbol* callBacktype);

    // Returns current callback type
    inline
    const IlSymbol*	getCurrentCallbackType() const
			{
			    return _callbackType;
			}

    // Undocumented members
    void		setCurrentCallbackType(const IlSymbol*);

protected:
    static void		AddInTopList(IlvDisplay* display,
				     IlList*& toplist,
				     IlInt& topNb);
    static void		PtCoordinatesInTopWin(const IlvPoint& trueOrig,
					      IlvPoint&	inTop,
					      const IlvView* ownerView);
private:
    const IlSymbol*	_callbackType;
};

#endif /* !__Ilv_Test_Api_H */
