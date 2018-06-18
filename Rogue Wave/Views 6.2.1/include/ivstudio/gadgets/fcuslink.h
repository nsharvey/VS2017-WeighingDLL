// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/fcuslink.h
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
// Declaration of the IlvStFocusLink class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Fcuslink_H
#define __IlvSt_Fcuslink_H

#if      !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
class IlvStudio;

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStFocusLink : public IlvManagerViewInteractor
{
public:
    IlvStFocusLink(IlvStudio* ed) :
	_editor(ed),
	_from(0),
	_to(0),
	_down(),
	_where(),
	_pathVisible(IlTrue) {}

    // ____________________________________________________________
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	handleExpose(IlvRegion* = 0);
    virtual void	drawGhost();
    virtual void	abort();
    virtual void	init();
    virtual void	doIt();
    virtual void	handleButtonDown(IlvEvent&);
    virtual void	handleButtonUp(IlvEvent&);
    virtual void	handleButtonDragged(IlvEvent&);
    inline IlBoolean	isPathVisible() const { return _pathVisible; }
    inline void		setPathVisible(IlBoolean val) { _pathVisible = val; }
    void		drawPath(IlvRegion*);
    void		drawPath(const IlvGraphic*,
				 const IlvGraphic*,
				 const IlvPalette*);
protected:
    IlvStudio*		_editor;
    IlvGraphic*		_from;
    IlvGraphic*		_to;
    IlvPoint		_down;
    IlvPoint		_where;
    IlBoolean		_pathVisible	ILVSTBF;
};

#endif /* __IlvSt_Fcuslink_H */
