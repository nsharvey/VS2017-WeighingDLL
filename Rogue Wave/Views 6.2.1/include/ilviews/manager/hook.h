// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/hook.h
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
// Declaration of the IlvManagerViewHook class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Hook_H
#define __Ilv_Manager_Hook_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif

class IlvManager;
class IlvManagerViewInteractor;

// --------------------------------------------------------------------------
// Manager View Hook
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerViewHook
{
    friend class IlvMgrView;
public:
    IlvManagerViewHook(IlvManager* manager = 0, IlvView* view = 0)
    : _manager(manager),
      _view(view),
      _toupdate() {}
    virtual ~IlvManagerViewHook();
    // ____________________________________________________________
    inline IlvManager*	getManager()              const { return _manager;    }
    inline void		setManager(IlvManager* manager) { _manager = manager; }
    inline IlvView*	getView()                 const { return _view;       }
    inline void		setView(IlvView* view)		  { _view = view;     }
    inline void		addUpdateRegion(const IlvRect& r) { _toupdate.add(r); }
    void		addUpdateRegion(const IlvRegion&);
    virtual void	beforeDraw(IlvPort*              dst,
				   const IlvTransformer* t      = 0,
				   const IlvRegion*      region = 0,
				   const IlvRegion*      clip   = 0);
    virtual void	afterDraw(IlvPort*              dst,
				  const IlvTransformer* t      = 0,
				  const IlvRegion*      region = 0,
				  const IlvRegion*      clip   = 0);
    virtual void	afterExpose(const IlvRect& rect);
    virtual void	interactorChanged(IlvManagerViewInteractor* current,
					  IlvManagerViewInteractor* previous);
    virtual void	transformerChanged(const IlvTransformer* current,
					   const IlvTransformer* previous);
    virtual void	viewResized();
    virtual void	viewRemoved();
    virtual void	contentsChanged();

protected:
    inline void		resetUpdateRegion() { _toupdate.empty(); }
    void		addUpdateRegion(IlvRegion* region) const;

    IlvManager*		_manager;
    IlvView*		_view;
    IlvRegion		_toupdate;
};

#endif /* !__Ilv_Manager_Hook_H */
