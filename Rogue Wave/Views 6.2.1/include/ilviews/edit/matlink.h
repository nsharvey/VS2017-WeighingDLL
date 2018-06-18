// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/matlink.h
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
// Declaration of the IlvMakeMatLinkInteractor class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Matlink_H
#define __Ilv_Edit_Matlink_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class ILVGDTEXPORTED IlvMatrix;
class ILVEDTEXPORTED IlvMatrixItemPanel;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvMakeMatLinkInteractor
    : public IlvManagerViewInteractor {
public:
    IlvMakeMatLinkInteractor(IlvManager* mgr,
			     IlvView* v);
    IlvMakeMatLinkInteractor();
    ~IlvMakeMatLinkInteractor();
    // ____________________________________________________________
    virtual void attach(IlvManager* manager,
			IlvView* view);
    virtual IlBoolean handleEvent(IlvEvent& event);
    virtual void detach();
    virtual void abort();
    virtual void init();
    virtual void drawGhost();
    virtual void doIt(IlvMatrix* mb,
		      IlUShort col,
		      IlUShort,
		      IlvGraphic*);
    IlvMatrixItemPanel* getMatrixItemPanel() { return _matrixItemPanel; }
 protected:
    IlvMatrix*                    _matrix;
    IlvGraphic*                   _graphic;
    IlvPoint                      _prev;
    IlvPoint                      _first;
    IlUShort                     _col;
    IlUShort                     _row;
    IlvMatrixItemPanel*           _matrixItemPanel;
    void popMatrixItemInspector(IlvMatrix* matrix,
				IlUShort col,
				IlUShort row);
};

#endif /* !__Ilv_Edit_Matlink_H */
