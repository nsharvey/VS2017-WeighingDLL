// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/pinedit.h
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
// Declaration of the pin editor related classes
// Defined in library ilvgrapher
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Pinedit_H
#define __Ilv_Grapher_Pinedit_H

#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif
#if !defined(__Ilv_Grapher_Nodesel_H)
#include <ilviews/grapher/nodesel.h>
#endif

class ILVVWSEXPORTED IlvGraphic;
class ILVGRAPHEXPORTED IlvGrapherPin;
class ILVGRAPHEXPORTED IlvGenericPin;
class ILVGRAPHEXPORTED IlvLinkImage;

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvPinEditorInteractor
    : public IlvManagerViewInteractor
{
    friend class IlvMovePinInteractor;

public:
    IlvPinEditorInteractor(IlvManager* mgr, IlvView* view);
    IlvPinEditorInteractor();

    virtual void	abort();
    virtual void	init();

    //== Event handling ========
    virtual IlBoolean	handleEvent(IlvEvent &event);

    virtual IlBoolean	handleButtonDown(IlvEvent& event);
    virtual IlBoolean	handleButtonUp(IlvEvent& event);
    virtual IlBoolean	handleKeyUp(IlvEvent& event);

    virtual void	validate(IlvPoint& p);

    //== Action methods ========
    virtual void	doConnectPin(IlvGraphic* link, IlUInt pinIndex);
    virtual void	doRemovePin(IlUInt pinIndex);
    virtual IlUInt	doAddPin(const IlvPoint& p);
    virtual void	doMovePin(IlUInt pinIndex, const IlvPoint& p);

    IlvGraphNodeSelection* getNodeSelection() const;


    IlvMakeSelection	setMakeNodeSelection(IlvMakeSelection mksel) 
			{
			    IlvMakeSelection old = _makeNodeSelection;
			    _makeNodeSelection = mksel;
			    return old;
			}

    IlvPinEditorInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    IlvGraphNodeSelection* addNodeSelection(IlvGraphic*, IlBoolean reDraw);
    void		removeNodeSelection(IlvGraphic*, IlBoolean reDraw);
    void		drawGhost();
    void		movePin(const IlvPoint& p);

    IlvGraphic*		_node;
    IlBoolean		_wasSelected;
    IlvLinkImage*	_link;
    IlvMakeSelection	_makeNodeSelection;
};

ILVGRAPHMODULEINIT(gpinedit);
#endif

