// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/txtinter.h
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
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Txtinter_H
#define __Ilv_Gadmgr_Txtinter_H

#if !defined(__Ilv_Gadmgr_Macrosadv_H)
#include <ilviews/gadmgr/macrosadv.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Lablist_H)
#include <ilviews/graphics/lablist.h>
#endif
#if !defined(__Ilv_Gadgets_Text_H)
#include <ilviews/gadgets/text.h>
#endif
#if !defined(__Ilv_Base_Command_H)
#include <ilviews/base/command.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTMGREXPORTED IlvManagerMakeTextInteractor
    : public IlvManagerViewInteractor
{
public:
    IlvManagerMakeTextInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view)
    {
	_text = 0;
    }
    IlvManagerMakeTextInteractor() : IlvManagerViewInteractor()
    {
	_text = 0;
    }
    ~IlvManagerMakeTextInteractor() ;

    void		setLines(const char* const* lines,
				 IlUShort           count,
				 IlBoolean          redraw = IlTrue);
    const char* const* getLines(IlUShort& count) const;
    void		reDraw();
    void		handleExpose(IlvRegion* clip);
    IlBoolean	handleEvent(IlvEvent& event);
    virtual void	doIt(const char* const* lines, IlUShort count) = 0;
    virtual void	abort();
    virtual IlBoolean	accept(IlvPoint& p);

protected:
    IlvPoint		_position;
    IlvText*		_text;
};

// --------------------------------------------------------------------------
class ILVADVGDTMGREXPORTED IlvManagerMakeListLabelInteractor
    : public IlvManagerMakeTextInteractor
{
public:
    IlvManagerMakeListLabelInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerMakeTextInteractor(manager, view),
	  _label(0)
    {}
    IlvManagerMakeListLabelInteractor()
	: IlvManagerMakeTextInteractor(),
	  _label(0)
    {}

    virtual IlBoolean	accept(IlvPoint& p);
    virtual void	doIt(const char* const* lines, IlUShort count);

protected:
    IlvListLabel*	_label;
};

#endif /* !__Ilv_Gadmgr_Txtinter_H */
