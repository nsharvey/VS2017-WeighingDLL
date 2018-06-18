// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/mathook.h
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
// Declaration of the IlvMatrixHook class.
// Defined in library ilvgadmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Mathook_H
#define __Ilv_Gadmgr_Mathook_H

#if !defined(__Ilv_Gadmgr_Macrosadv_H)
#include <ilviews/gadmgr/macrosadv.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Gadgets_Matrix_H)
#include <ilviews/gadgets/matrix.h>
#endif

class IlvMatrixHook;

typedef void (*IlvMatrixHookCallback)(IlvMatrixHook*, IlAny);

// --------------------------------------------------------------------------
class ILVADVGDTMGREXPORTED IlvMatrixHook : public IlvManagerViewHook
{
public:
    IlvMatrixHook(IlvManager*   mgr,
		  IlvView*      view,
		  IlvContainer* cont,
		  IlvMatrix*    matrix);

    void		initialise(IlvManager*   mgr,
				   IlvView*      view,
				   IlvContainer* cont,
				   IlvMatrix*    matrix);
    virtual void	interactorChanged(IlvManagerViewInteractor* current,
					  IlvManagerViewInteractor* previous);
    void		add(IlUShort posx,
			    IlUShort posy,
			    IlvAbstractMatrixItem* item,
			    IlvManagerViewInteractor* interactor);
    void		set(IlUShort posx,
			    IlUShort posy,
			    IlvManagerViewInteractor* interactor);
    inline IlvMatrix*	getMatrix() const { return _matrix; }
    inline IlvContainer*	getContainer() const { return _container; }
    inline void		setCallback(IlvMatrixHookCallback callback,
				    IlAny arg = 0)
    {
	_callback = callback;
	_clientData = arg;
    }

protected:
    IlvContainer*		_container;
    IlvMatrix*			_matrix;
    IlvMatrixHookCallback	_callback;
    IlAny			_clientData;
};

#endif /* !__Ilv_Gadmgr_Mathook_H */
