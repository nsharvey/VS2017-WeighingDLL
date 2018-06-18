// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/ghlink.h
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
// Declaration of the IlvStGHInteractor class
// --------------------------------------------------------------------------
#ifndef __Ilv_Ghlink_H
#define __Ilv_Ghlink_H

#if      !defined(__IlvSt_Stselect_H)
#include <ivstudio/stselect.h>
#endif
#if      !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if      !defined(__Ilv_Manager_Holder_H)
#include <ilviews/manager/holder.h>
#endif

#if      !defined(__IlvSt_Ghedit_H)
#include <ivstudio/gadgets/ghedit.h>
#endif

// --------------------------------------------------------------------------
extern ILVSTGADGETEXPORTEDVAR (const char*) IlvNmAttachment;

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStGHInteractor : public IlvStSelectInteractor
{
public:
    IlvStGHInteractor(IlvStudio*, IlvManager*, IlvView*);
    IlvStGHInteractor(IlvStudio*);
    virtual ~IlvStGHInteractor();
    // ____________________________________________________________
    virtual void	attach(IlvManager* manager, IlvView* view);
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	abort();
    virtual void	init();
    virtual void	handleExpose(IlvRegion* rect = 0);
    // ____________________________________________________________
    virtual void	handleKeyDown(IlvEvent&);
    virtual void	handleButtonDown(IlvEvent&);
    virtual void	handleButtonUp(IlvEvent&);
    virtual void	handleDoubleClick(IlvEvent&);
    virtual void	handleButtonDragged(IlvEvent&);
    virtual void	dragMoveGuide(IlvEvent&);
    virtual void	dragInsertGuide(IlvEvent&);
    virtual void	dragSelection(IlvEvent&);
    // ____________________________________________________________
    inline IlBoolean	isVisible() const { return _edit->isVisible(); }
    IlBoolean		removeSelection(IlvEvent&);
    void		updateGuideInspector();
    inline IlvStGHEdit*	getGHEdit() const { return _edit; }
    IlBoolean		hasDragged() const;

protected:
    IlvStGHEdit*	_edit;
    IlvPos		_prevGuidePos;
    IlvPos		_prevObjPos;
    IlvDirection	_objDir;
    IlvPoint		_downPoint;
    IlvPoint		_prevPoint;
    IlvDirection	_hiliGuideDir;
    IlUInt		_hiliGuideNdx;
    IlUShort		_dragCount;
    IlvPosition		_attachmentPart;
    IlvGraphic*		_attachedObject;
    IlBoolean		_hasMoved	ILVSTBF;
    IlBoolean		_onGuideLine	ILVSTBF;

    IlvGuideHandler*	getGuideHandler(IlvDirection dir) const
			{
			    return getManager()->getHolder()->
				getGuideHandler(dir);
			}
    void		addGuide(const IlUInt& pos,
				 IlvDirection dir,
				 IlBoolean redraw = IlTrue);
    void		showGuideLines();
    void		hideGuideLines();
    IlvPalette*		getGuideLinePalette();
    void		guideLineBBox(IlvRect&, IlvPos, IlvDirection);
    void		invalidateGuideLineRegion(IlvDirection);
    void		initialize();
    inline IlvDirection	guideDir() const
			{
			    return _edit->getSelectionDirection();
			}
    inline IlUInt	guideNdx() const { return _edit->getSelectionIndex(); }
    void		drawLine();
    IlBoolean		updateObjectAttachment(IlvEvent&);
    IlBoolean		toggleObjectAttachment(IlvEvent&);
}; // class IlvStGHInteractor

// --------------------------------------------------------------------------

#endif /*  ! __Ilv_Ghlink_H */
