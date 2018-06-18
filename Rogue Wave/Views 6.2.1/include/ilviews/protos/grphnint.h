// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/grphnint.h
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
// Declaration of the Group interactors.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Grphnint_H
#define __Ilv_Protos_Grphnint_H

#if !defined(__Ilv_Protos_Group_H)
#include <ilviews/protos/group.h>
#endif
#if !defined(__Ilv_Protos_Grphnode_H)
#include <ilviews/protos/grphnode.h>
#endif
#if !defined(__Ilv_Protos_Grpgraph_H)
#include <ilviews/protos/grpgraph.h>
#endif
#if !defined(__Ilv_Manager_Selinter_H)
#include <ilviews/manager/selinter.h>
#endif
#if !defined(__Ilv_Grapher_Inters_H)
#include <ilviews/grapher/inters.h>
#endif
// ---------------------------------------------------------------------------
// IlvGroupSelectInteractor    Selection of a group with graphic nodes
//				in a manager.
// ---------------------------------------------------------------------------
class ILVGDPEXPORTED IlvGroupSelectInteractor : public IlvSelectInteractor
{
public:
    IlvGroupSelectInteractor(IlvManager* manager,
			     IlvView*    view,
			     IlUShort    button             = IlvLeftButton,
			     IlBoolean   showCursor         = IlFalse,
			     IlBoolean   allowNodeSelection = IlFalse)
	: IlvSelectInteractor(manager, view, button, showCursor),
	  _allowNodeSelection(allowNodeSelection)
    {}
    IlvGroupSelectInteractor(IlUShort  button             = IlvLeftButton,
			     IlBoolean showCursor         = IlFalse,
			     IlBoolean allowNodeSelection = IlFalse)
	: IlvSelectInteractor(button, showCursor),
	  _allowNodeSelection(allowNodeSelection)
    {}
    // ____________________________________________________________
    virtual void	doSelect();
    virtual void	abort();
    IlvGroup*		getSelectedGroup();
    IlvGroup**		getSelectedGroups(IlUInt& count);
    IlvGroupGraphic*	getGroupGraphic();
    IlvGroupGraphic**	getGroupGraphics(IlUInt& count);
    void		selectGroup(IlvGroup* group,
				    IlBoolean selectIt    = IlTrue,
				    IlBoolean deselectAll = IlTrue);

    inline IlBoolean	isNodeSelectionAllowed() const
			{
			    return _allowNodeSelection;
			}
    inline void		allowNodeSelection(IlBoolean allowIt)
			{
			    _allowNodeSelection = allowIt;
			}

    IlvGroup*		findSelectedGroup(IlvGroupGraphic* groupGraphic);
    IlvGroupGraphic*	findGroupGraphic(IlvGroup* group);

protected:
    IlBoolean		_allowNodeSelection;
};

// ---------------------------------------------------------------------------
// IlvGroupGraphSelectInteractor    Selection of a group with graphic nodes
//				    in a grapher.
// ---------------------------------------------------------------------------
class ILVGDPEXPORTED IlvGroupGraphSelectInteractor
    : public IlvGraphSelectInteractor
{
public:
    IlvGroupGraphSelectInteractor(IlvManager* manager,
				  IlvView*    view,
				  IlUShort                     = IlvLeftButton,
				  IlBoolean	               = IlFalse,
				  IlBoolean allowNodeSelection = IlFalse)
	: IlvGraphSelectInteractor(manager, view),
	  _allowNodeSelection(allowNodeSelection)
    {}
    IlvGroupGraphSelectInteractor(IlUShort                     = IlvLeftButton,
				  IlBoolean	               = IlFalse,
				  IlBoolean allowNodeSelection = IlFalse)
	: IlvGraphSelectInteractor(),
	  _allowNodeSelection(allowNodeSelection)
    {}

    virtual void	doSelect();
    virtual void	abort();

    IlvGroup*		getSelectedGroup();
    IlvGroup**		getSelectedGroups(IlUInt& count);
    IlvGroupGraphic*	getGroupGraphic();
    IlvGroupGraphic**	getGroupGraphics(IlUInt& count);
    void		selectGroup(IlvGroup* group,
				    IlBoolean selectIt    = IlTrue,
				    IlBoolean deselectAll = IlTrue);

    IlvGroup*		findSelectedGroup(IlvGroupGraphic* groupGraphic);
    IlvGroupGraphic*	findGroupGraphic(IlvGroup* group);

protected:
    IlBoolean		_allowNodeSelection;
};

#endif /* __Ilv_Protos_Grphnint_H */
