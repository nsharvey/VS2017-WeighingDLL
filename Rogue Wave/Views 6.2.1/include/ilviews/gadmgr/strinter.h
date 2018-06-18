// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/strinter.h
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
// Declaration of predefined text-related interactors classes
// Defined in library ilvgadmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Strinter_H
#define __Ilv_Gadmgr_Strinter_H

#if !defined(__Ilv_Gadmgr_Macros_H)
#include <ilviews/gadmgr/macros.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Gadgets_Eltextfd_H)
#include <ilviews/gadgets/eltextfd.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvManagerMakeStringInteractor
    : public IlvManagerViewInteractor
{
public:
    IlvManagerMakeStringInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view)
    {
	_text = 0;
    }
    IlvManagerMakeStringInteractor()
	: IlvManagerViewInteractor()
    {
	_text = 0;
    }
    ~IlvManagerMakeStringInteractor();

    void               setLabel(const char* label, IlBoolean redraw = IlTrue);
    const char*        getLabel();
    void               reDraw();
    void               handleExpose(IlvRegion* clip);
    IlBoolean          handleEvent(IlvEvent& event);
    virtual void       doIt(const char* label) = 0;
    virtual void       abort();
    virtual IlBoolean  accept(IlvPoint& p);

protected:
    IlvPoint             _position;
    IlvElasticTextField* _text;
};

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvManagerMakeLabelInteractor
    : public IlvManagerMakeStringInteractor
{
public:
    IlvManagerMakeLabelInteractor(IlvManager* manager, IlvView* eview)
	: IlvManagerMakeStringInteractor(manager, eview),
	  _label(0)
    {}
    IlvManagerMakeLabelInteractor()
	: IlvManagerMakeStringInteractor(),
	  _label(0)
    {}

    virtual IlBoolean    accept(IlvPoint& p);
    virtual void doIt(const char* label);

protected:
    IlvLabel* _label;
};

#endif /* !__Ilv_Gadmgr_Strinter_H */
