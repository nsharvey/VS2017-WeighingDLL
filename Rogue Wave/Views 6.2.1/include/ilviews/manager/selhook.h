// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/selhook.h
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
// Declaration of the IlvManagerSelectionHook class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Selhook_H
#define __Ilv_Manager_Selhook_H

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerSelectionHook
{
public:
    IlvManagerSelectionHook()
    : _manager(0),
      _next(0)
    {}
    virtual ~IlvManagerSelectionHook();
    // ____________________________________________________________
    inline IlvManager*	getManager() const { return _manager;    }
    void		setManager(IlvManager* manager);
    virtual void	selectionChangedStart();
    virtual void	selectionChangedEnd();
    virtual void	selectionChanged(IlvGraphic* object,
					 IlBoolean   selected);

private:
    IlvManager*			_manager;
    IlvManagerSelectionHook*	_next;
    friend class IlvManager;
};

#endif /* !__Ilv_Manager_Selhook_H */
