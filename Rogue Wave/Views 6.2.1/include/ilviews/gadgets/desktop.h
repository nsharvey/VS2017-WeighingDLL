// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/desktop.h
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
// Declaration of IlvDesktopManager class
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Desktop_H
#define __Ilv_Gadgets_Desktop_H

#ifndef __Ilv_Ilv_H
#include <ilviews/ilv.h>
#endif
#ifndef __Ilv_Base_Array_H
#include <ilviews/base/array.h>
#endif
#ifndef __Ilv_Gadgets_Vframe_H
#include <ilviews/gadgets/vframe.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

class ILVADVGDTEXPORTED IlvMaximizedStateHandler;

#define IlvDesktopManagerCascadeFreeSpace (IlvDim)150

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDesktopManager
{
    friend class IlvViewFrame;
public:

    IlvDesktopManager(IlvView* view);

    virtual ~IlvDesktopManager();

    inline IlvView*	getView() const { return _view; }

    static
    IlvDesktopManager*	Get(IlvView* view);

    void		tileFrames(IlvDirection direction);

    void		cascadeFrames(IlvDim =
				      IlvDesktopManagerCascadeFreeSpace,
				      IlvDim =
				      IlvDesktopManagerCascadeFreeSpace);

    virtual void	getMinimizedBBox(IlvViewFrame*, IlvRect&) const;
    virtual IlvDim	getMinimizedWidth() const;
    virtual void	updateMinimizedFrames();
    void                resetMinimizedFramePositions();
    virtual void	getMaximizedBBox(IlvRect&) const;
    virtual void        handleDesktopInput(IlvEvent&);

    virtual void	addFrame(IlvViewFrame* frame);

    virtual void	removeFrame(IlvViewFrame* frame);

    IlvViewFrame* const* getFrames(IlUInt& count) const;

    inline IlUInt	getCardinal() const { return _frames.getLength(); }

    inline
    IlvViewFrame*	getFrame(IlUInt index) const
			{
			    return (IlvViewFrame*)_frames[index];
			}

    inline
    IlvViewFrame*	getCurrentFrame() const { return _currentFrame; }

    virtual void	setCurrentFrame(IlvViewFrame* frame,
					IlBoolean raise = IlTrue);

    virtual void	frameSelectionChanged(IlvViewFrame* newFrame,
					      IlvViewFrame* oldFrame);

    IlvViewFrame*	getNextFrame() const;

    IlvViewFrame*	getPreviousFrame() const;

    inline IlvPosition	getMinimizedPlacement() const
			{
			    return _minimizedPlacement;
			}
    inline void		setMinimizedPlacement(IlvPosition pos)
			{
			    _minimizedPlacement = pos;
			}
    inline IlBoolean	isMaximizing() const { return _maximizing; }

    IlBoolean		isManaging(const IlvViewFrame* frame) const;
    virtual void	updateCurrentFrameBBox();

    virtual void	makeMaximizedStateButtons(IlvGraphicHolder* holder,
						  IlvPos vOffset = -1,
						  IlvPos hOffset = -1);
    virtual void	makeMaximizedStateButtons(IlvToolBar* toolbar);

    IlBoolean		hasMaximizedStateButtons() const;
    void		restoreFrames();
    void		maximizeFrames();
    void		updateDefaultMaximizedStateButtonsHolder();

    virtual void	frameMinimized(IlvViewFrame* frame,
				       int previousState);

    virtual void	frameMaximized(IlvViewFrame* frame,
				       int previousState);

    virtual void	frameRestored(IlvViewFrame* frame, int previousState);

    IlvViewFrame* const* getMinimizedFrames(IlUInt& count) const;

    virtual IlvPalette*	getActiveTitleBarPalette() const;

    virtual IlvPalette*	getInactiveTitleBarPalette() const;

    virtual void	viewDeleted();
    virtual void	restore(IlvViewFrame*);
    virtual void	minimize(IlvViewFrame*);
    virtual void	maximize(IlvViewFrame*);
    virtual void	maximizedStateHandlerDeleted();
    inline IlvMaximizedStateHandler*	getMaximizedStateHandler() const
					{
					    return _maxStateHandler;
					}
    void		updateMaximizedStateHandler();
    void		iRestoreFrames();

    static int		GlobalInit();

    static IlSymbol*	_Ilv_DesktopManager;
    static IlvDim	_MinimizedWidth;

protected:
    IlvView*		_view;
    IlvViewFrame*	_currentFrame;
    IlArray		_frames;
    IlArray		_minimizedFrames;
    IlvPosition		_minimizedPlacement;
    IlBoolean		_maximizing;
    IlBoolean		_showingMaxButtons;
    IlvMaximizedStateHandler*
			_maxStateHandler;
    IlBoolean		_defaultMaximizedStateButtonHolder;

    void		setMaxButtonsVisibility(IlBoolean);
    void		createDefaultMaximizedStateButtonsHolder();
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMaximizedStateHandler
{
public:
    IlvMaximizedStateHandler(IlvDesktopManager* desktop)
	: _desktop(desktop), _buttons(0)
    {}
    virtual ~IlvMaximizedStateHandler();

    inline IlvButton*	getMinimizeButton() const
			{
			    return _buttons->getMinimizeButton();
			}
    inline IlvButton*	getRestoreButton() const
			{
			    return _buttons->getRestoreButton();
			}
    inline IlvButton*	getCloseButton() const
			{
			    return _buttons->getCloseButton();
			}
    virtual void	setVisibility(IlBoolean show);

protected:
    IlvDesktopManager*		_desktop;
    IlvViewFrameButtons*	_buttons;
};

// --------------------------------------------------------------------------
ILVADVGDTMODULEINIT(desktop);

#endif /* !__Ilv_Gadgets_Desktop_H */

