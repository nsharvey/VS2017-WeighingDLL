// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/zone.h
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
// Declaration of the IlvATZone class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Zone_H
#define __Ilv_Annotext_Zone_H

#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif

class ILVATEXPORTED IlvAnnoText;
class ILVATEXPORTED IlvATCursor;
class ILVATEXPORTED IlvATInteractor;
class ILVATEXPORTED IlvATPalette;

// --------------------------------------------------------------------------
class ILVATEXPORTED  IlvATZone
{
public:
    IlvATZone(IlvATCursor* start, IlvATCursor* end);
    ~IlvATZone();

    inline IlAny	getUserData() const { return _userData;}
    inline void		setUserData(IlAny userData) { _userData = userData; }
    IlvAnnoText*	getAnnoText() const;
    inline
    IlvATPalette*	getTextPalette() const { return _tpalette;}
    inline IlvATZone*	getParent() const { return _parent; }
    inline void		setInteractor(IlvATInteractor* inter)
	{ _inter=inter; }
    IlvATInteractor*	getInteractor(IlBoolean recursive = IlFalse) const;

    ////////////////////////////////////
    // Not documented
    ////////////////////////////////////
    inline IlvATCursor*	getStart() const		{ return _start;   }
    inline void		setStart(IlvATCursor* start)	{ _start = start;  }
    inline IlvATCursor*	getEnd() const			{ return _end;     }
    inline void		setEnd(IlvATCursor* end)	{ _end = end;      }
    void		extract();
    inline void		setParent(IlvATZone* parent)	{ _parent = parent;}
    inline void		setTextPalette(IlvATPalette* tpal)
	{ _tpalette = tpal;}
    int			private1();

    // Returns the object on which to apply interactor
    IlvGraphic*		getGraphic() const;
protected:
    IlvATCursor*	_start;
    IlvATCursor*	_end;
    IlvATPalette*	_tpalette;
    IlvATZone*		_parent;
    IlAny		_userData;
    IlvATInteractor*	_inter;
    IlAny		_ext1;
};

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATInteractor
{
public:
    IlvATInteractor();
    // ____________________________________________________________
    virtual IlBoolean	handleEvent(IlvATZone* zone, IlvEvent& event) = 0;
    inline IlBoolean	areGadgetsActive() const { return _activeGadgets; }
    inline void		setGadgetsActive(IlBoolean active)
			{
			    _activeGadgets = active;
			}
protected:
    IlBoolean		_activeGadgets;
};

#endif /* !__Ilv_Annotext_Zone_H */
