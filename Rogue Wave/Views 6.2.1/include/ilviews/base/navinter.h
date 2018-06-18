// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/navinter.h
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
// Declaration of the IlvNavigationInteractor class
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Navinter_H
#define __Ilv_Base_Navinter_H

#if !defined(__Ilv_Base_Timer_H)
#  include <ilviews/base/timer.h>
#endif
#if !defined(__Il_Date_H)
#  include <ilog/date.h>
#endif

// --------------------------------------------------------------------------
// IlvNavigationInteractor
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvNavigationInteractor
{
public:
    IlvNavigationInteractor(IlvDisplay* display);
    virtual ~IlvNavigationInteractor();

    IlBoolean		handleEvent(IlvEvent& event);

    IlBoolean		isTranslationAllowed() const;
    void		allowTranslation(IlBoolean allow);
    IlvTransfoParam	getTranslationThreshold() const;
    void		setTranslationThreshold(IlvTransfoParam threshold);
    void		setInertiaRatio(IlFloat ratio);

    IlBoolean		isZoomAllowed() const;
    void		allowZoom(IlBoolean allow);
    IlvTransfoParam	getZoomThreshold() const;
    void		setZoomThreshold(IlvTransfoParam threshold);

    IlBoolean		isRotationAllowed() const;
    void		allowRotation(IlBoolean allow);
    IlvTransfoParam	getRotationThreshold() const;
    void		setRotationThreshold(IlvTransfoParam threshold);

    IlBoolean		isResetOnDoubleTapAllowed() const;
    void		allowResetOnDoubleTap(IlBoolean allow);
    IlvTransfoParam	getDoubleTapDistance() const;
    void		setDoubleTapDistance(IlvTransfoParam dist);
    IlDate		getDoubleTapDelay() const;
    void		setDoubleTapDelay(IlDate delay);

    void		allowEverything(IlBoolean allow);

    static IlBoolean	getStatus(const char*, IlBoolean);

protected:
    virtual void	changeTransformer(IlvTransformer& t) = 0;

    virtual
    IlvTransformer*	getTransformer() const = 0;

    struct P;
    friend struct P;
    struct P*		_p;
};

#endif /* !__Ilv_Base_Navinter_H */
