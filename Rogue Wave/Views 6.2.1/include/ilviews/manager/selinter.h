// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/selinter.h
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
// Definition of the default 'select' interactor class: IlvSelectInteractor
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Selinter_H
#define __Ilv_Manager_Selinter_H

#if !defined(__Ilv_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Base_Timer_H)
#include <ilviews/base/timer.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvSelectInteractor
: public IlvManagerViewInteractor
{
public:
    IlvSelectInteractor(IlvManager* manager,
			IlvView*    view,
			IlUShort    button     = IlvLeftButton,
			IlBoolean   showCursor = IlFalse)
    : IlvManagerViewInteractor(manager, view),
      _state(InitState),
      _deltax(0),
      _deltay(0),
      _firstx(0),
      _firsty(0),
      _oppositex(0),
      _oppositey(0),
      _bbox(),
      _was_selected(IlFalse),
      _direction(IlvBadPosition),
      _move(0),
      _reshape(0),
      _xor_rectangle(),
      _lastpoint(),
      _cursorShown(IlFalse),
      _showCursor(showCursor),
      _cursorPosition(),
      _button(button),
      _extendSelectionModifier(IlvShiftModifier),
      _deSelectOnReselect(IlFalse),
      _opaqueMove(IlFalse),
      _opaqueReshape(IlFalse),
      _useGhostRectangle(IlFalse),
      _smartSel(IlTrue),
      _initBbox(),
      _initBboxSymbol(0),
      _oldCursor(0),
      _noMove(IlFalse),
      _moveTimer(0),
      _interactiveSelection(0), 
      _keepAspectRatio(IlFalse) 
      {}
    IlvSelectInteractor(IlUShort  button     = IlvLeftButton,
			IlBoolean showCursor = IlFalse)
    : IlvManagerViewInteractor(),
      _state(InitState),
      _deltax(0),
      _deltay(0),
      _firstx(0),
      _firsty(0),
      _oppositex(0),
      _oppositey(0),
      _bbox(),
      _was_selected(IlFalse),
      _direction(IlvBadPosition),
      _move(0),
      _reshape(0),
      _xor_rectangle(),
      _lastpoint(),
      _cursorShown(IlFalse),
      _showCursor(showCursor),
      _cursorPosition(),
      _button(button),
      _extendSelectionModifier(IlvShiftModifier),
      _deSelectOnReselect(IlFalse),
      _opaqueMove(IlFalse),
      _opaqueReshape(IlFalse),
      _useGhostRectangle(IlFalse),
      _smartSel(IlTrue),
      _initBbox(),
      _initBboxSymbol(0),
      _oldCursor(0),
      _noMove(IlFalse),
      _moveTimer(0),
      _interactiveSelection(0),
      _keepAspectRatio(IlFalse)
      {}

    ~IlvSelectInteractor()
	{
	    if (_moveTimer)
		delete _moveTimer;
	    _moveTimer = 0;
	}
    // ____________________________________________________________
    inline IlUShort	getButton() const { return _button; }
    inline void		setButton(IlUShort b) { _button = b;    }
    inline IlUShort	getExtendedSelectionModifier() const
			{
			    return _extendSelectionModifier;
			}
    inline void		setExtendedSelectionModifier(IlUShort m)
			{
			    _extendSelectionModifier = m;
			}
    inline IlBoolean	doesDeselectOnReselect() const
			{
			    return _deSelectOnReselect;
			}
    inline void		deSelectOnReselect(IlBoolean f)
			{
			    _deSelectOnReselect = f;
			}
    virtual void	handleExpose(IlvRegion* rect = 0);
    void		drawGhost();
    void		init();
    inline void		showCursor(IlBoolean useIt) { _showCursor = useIt; }
    void		abort() ;
    IlBoolean		handleEvent(IlvEvent& event);
    virtual void	addedToSelection(IlvGraphic*);
    virtual void	removedFromSelection(IlvGraphic*);
    virtual void	drawGhostMove(IlvGraphic* object, IlvRegion* clip = 0);
    virtual void	drawGhost(IlvRect& rect, IlvRegion* clip = 0);
    virtual void	drawGhostReshape(IlvGraphic* object,
					 IlvRegion*  clip = 0);
    virtual void	doTranslate(const IlvPoint& p);
    virtual void	doReshape(IlvGraphic* object, const IlvRect& rect);
    virtual void	objectReshaped(IlvGraphic*);
    virtual void	objectReSelected(IlvGraphic*);
    inline const IlvRect&	getRectangle() const { return _xor_rectangle; }
    inline IlBoolean	opaqueMove(IlBoolean useIt)
			{
			    return _opaqueMove = useIt;
			}
    inline IlBoolean	opaqueReshape(IlBoolean useIt)
			{
			    return _opaqueReshape = useIt;
			}
    inline IlBoolean	opaqueMove() const { return _opaqueMove; }
    inline IlBoolean	opaqueReshape() const { return _opaqueReshape; }
    inline IlBoolean	useGhostRectangle() const
			{
			    return _useGhostRectangle;
			}
    inline IlBoolean	useGhostRectangle(IlBoolean useIt)
			{
			    return _useGhostRectangle = useIt;
			}
    virtual void	doSelect();

    // These variables enable the lock mechanism that prevents accidental
    // moves to happen when selecting an object.
    static IlUShort	MoveThreshold; // defaults to 8 pixels
    static IlUInt	MoveTimeOut; // defaults to 800ms if 0 (no threshold)

    IlvSelectInteractor(IlvInputFile&);
    DeclareLazyManagerViewInteractorInfoRO();

protected:
    static void		MoveTimerCallback(IlvTimer*, IlAny);

    void		startMoveTimer();
    IlBoolean		readyToMove(const IlvPoint&);

    void		storeOpposite(IlvGraphic*);
    void		handleButtonDown(IlvEvent&);
    void		handleButtonDragged(IlvPoint& p);
    void		handleButtonUp(IlvEvent& event);
    void		drawCursor(IlvRegion* clip = 0);
    void		endOperation();

    typedef enum {
	InitState,
	Rectangle,
	Reshaping,
	Moving
    } IlvSelInterState;

    IlvSelInterState	_state;
    IlvPos		_deltax;
    IlvPos		_deltay;
    IlvPos		_firstx;
    IlvPos		_firsty;
    IlvPos		_oppositex;
    IlvPos		_oppositey;
    IlvRect		_bbox;
    IlBoolean		_was_selected;
    IlvDirection	_direction;
    IlvGraphic*		_move;
    IlvDrawSelection*	_reshape;
    IlvRect		_xor_rectangle;
    IlvPoint		_lastpoint;
    IlBoolean		_cursorShown;
    IlBoolean		_showCursor;
    IlvPoint		_cursorPosition;
    IlUShort		_button;
    IlUShort		_extendSelectionModifier;
    IlBoolean		_deSelectOnReselect;
    IlBoolean		_opaqueMove;
    IlBoolean		_opaqueReshape;
    IlBoolean		_useGhostRectangle;
    IlBoolean		_smartSel;
    IlvRect		_initBbox;
    IlSymbol*		_initBboxSymbol;
    IlvCursor*		_oldCursor;
    // to handle temporary lock of selection when moving.
    IlBoolean		_noMove;
    IlvTimer*		_moveTimer;
    IlvDrawSelection*	_interactiveSelection;
    IlBoolean		_keepAspectRatio;
};

ILVMGRMODULEINIT(m0_selinter);

#endif /* !__Ilv_Manager_Selinter_H */
