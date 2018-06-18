// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/mmenu.h
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
// Declaration of the IlvMarkingMenu class
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Mmenu_H
#define __Ilv_Gadgets_Mmenu_H

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Base_Timer_H)
#include <ilviews/base/timer.h>
#endif
#if !defined(__Ilv_Graphics_Ellipse_H)
#include <ilviews/graphics/ellipse.h>
#endif
#if !defined(__Ilv_Graphics_Set_H)
#include <ilviews/graphics/set.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Gadgets_Msglabel_H)
#include <ilviews/gadgets/msglabel.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

class IlvMarkingMenuGraphic;
class IlvMarkingMenu;
class IlvPseudoTransparentView;

typedef void (*IlvMarkingMenuCallback)(IlvMarkingMenu* menu,
				       IlUShort portion,
				       IlAny arg);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMarkingMenu
{
public:
    IlvMarkingMenu(IlvDisplay* display,
		   IlUInt	    portions	= 4,
		   IlvPalette* palette		= 0,
		   IlvPalette* invertedPalette	= 0,
		   IlUInt	    space	= 5,
		   IlUInt	    cmlIn	= 50,
		   IlUInt	    cmlOut	= 110,
		   IlUInt	    cmlSegment	= 5);

    virtual ~IlvMarkingMenu();
    // ____________________________________________________________
    virtual void	setPortionCallback(IlShort i,
					   const char* label,
					   IlvMarkingMenuCallback callback,
					   IlAny arg = 0,
					   IlvBitmap* b = 0,
					   IlvPosition alignment  = IlvCenter,
					   IlBoolean opaque = IlTrue,
					   IlBoolean isCircular = IlFalse);

    virtual void	setPortionSubMenu(IlShort i,
					  const char* label,
					  IlvMarkingMenu* markingMenu,
					  IlvBitmap* b = 0,
					  IlvPosition alignment = IlvCenter,
					  IlBoolean opaque = IlTrue,
					  IlBoolean isCircular = IlFalse);

    virtual void	doIt(IlvPoint* origin = 0);

    inline IlUInt	getCardinal() const { return _portions; }

    IlvMessageLabel*	getPortion(IlUInt portion);

    virtual void	unsetPortion(IlShort i);

    void		moveSelectedItem(IlBoolean move);

    IlvMarkingMenu*	getSubMenu(IlUInt portion);

    IlAny		getCallbackArg(IlUInt portion); 

    inline void		setReplacePointer(IlBoolean replace)
			{
			    _replacePointer = replace;
			}
    inline IlBoolean	getReplacePointer() const { return _replacePointer;}

    static void		SetNeutralZoneRadius(IlUInt nzr);
    inline static
    IlUInt		GetNeutralZoneRadius() { return _neutralZoneRadius; }

    inline static void	SetDelayDrawTime(IlUInt ddt) { _delayDrawTime = ddt; }
    inline static
    IlUInt		GetDelayDrawTime() { return _delayDrawTime; }

    static void		SetTrace(IlBoolean trace){_MarkingMenuTrace = trace;}

    void		setPalette(IlvPalette* palette);
    void		setInvertedPalette(IlvPalette* invertedPalette);
    IlvPalette*		getPalette();
    IlvPalette*		getInvertedPalette();

    //  WISH ?
    /*virtual void attach(IlvContainer* container,
			IlUShort eventData,
			IlUShort modifiers         = 0,
                        IlAny    userArg           = 0,
			IlUShort modifiersToIgnore = 0);*/
    /*virtual void detach(IlvContainer* container,
			IlUShort eventData,
			IlUShort modifiers         = 0,
                        IlAny    userArg           = 0,
			IlUShort modifiersToIgnore = 0);*/

    virtual void	inactiveParent();
    virtual void	graphicActive(IlBoolean value);
    virtual IlBoolean	handleEvent(IlvEvent& event);

protected:
    virtual void	handleButtonDragged(IlvEvent& event);
    virtual void	handleButtonUp(IlvEvent& event);

    struct IlvMarkingMenuActionStruct
    {
	IlvMarkingMenuCallback _function;
	IlAny		    _arg;
	// hierarchical marking menu
	IlvMarkingMenu*	    _subMarkingMenu;
    };

    IlvDisplay*		_display;
    IlUInt		_portions;
    static IlUInt	_neutralZoneRadius;	// default 16 pixels
    static IlUInt	_delayDrawTime;		// default 300 ms
    IlvPoint		_origin;
    IlvView*		_eventView;
    IlvMarkingMenuActionStruct**	_actionList;

    // IlvMarking Menu Trace
    void		drawConnectionWithPreviousMenu(IlBoolean
						       allConnect = IlFalse);
    void		drawTrace(IlvPoint& start, IlvPoint& end);
    static IlBoolean	_LastTrace;
    static IlBoolean	_MarkingMenuTrace;
    IlvPalette*		_xorPalette;

    // selection
    virtual void	selectItem(const IlvPoint& origin,
				   const IlvPoint& destination);
    virtual void	inactive(IlBoolean seeTrace);

    // Replace pointer option
    IlBoolean		_replacePointer;
    IlvPoint		_oldPoint; // use if replacePointer
    virtual
    IlvMarkingMenu*	originMenu();

    // Graphic Part
    IlvMarkingMenuGraphic* _graphicPart;
    static IlvTimer*	_GraphicTimer; // static ?

    static void		subMenuTimerProc(IlvTimer*, IlAny userarg);

    // Hierarchical marking menu
    IlDouble		_referenceAngle;
    IlBoolean		_hasReference;
    IlvPoint		_lastPoint;
    IlvTimer*		_subMenuTimer;
    IlShort 		_currentChoice;
    IlUShort		_backCounter;
    IlBoolean 	        _returnToParent;
    IlvMarkingMenu*	_parentMarkingMenu;
    IlvEllipse*		_parentNeutralZone;

    static IlBoolean	_InactiveFlag; // Exceed

    // To manage the update.
    static IlvArray	_MarkingMenuArray;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMarkingMenuGraphic
{
public:
    IlvMarkingMenuGraphic(IlvDisplay* display,
			  IlUInt      portions,
			  IlUInt      neutralZoneRadius,
			  IlvView*    parentView,
			  IlvPalette* palette		= 0,
			  IlvPalette* invertedPalette	= 0,
			  IlUInt      cmlIn		= 50,
			  IlUInt      cmlOut		= 110,
			  IlUInt      cmlSegment	= 5,
			  IlUInt      space		= 5);
    virtual ~IlvMarkingMenuGraphic();

    virtual void	show(IlvPoint& point);
    virtual IlBoolean	isVisible();
    virtual void	hide();
    virtual void	setPortion(IlUShort   p,
				   const char* label,
				   IlvBitmap*  b,
				   IlvPosition textPosition,
				   IlBoolean  opaque     = IlTrue,
				   IlBoolean  isCircular = IlTrue);
    virtual void	unsetPortion(IlUShort p);

    virtual IlUShort	drawingRadius();
    virtual void	drawChoose(IlUShort       choose = (IlUShort)-1,
				   const IlvPoint* point  = 0);
    void		drawNeutralZone(IlvPos x, IlvPos y);
    inline void		moveSelectedItem(IlBoolean move)
			{
			    _moveSelectedItem = move;
			}
    virtual IlBoolean	handleEvent(IlvEvent& event);
    void		compute(IlUInt nZR);
    IlvMessageLabel*	getPortion(IlUInt portion);

    void		setPalette(IlvPalette* palette);
    void		setInvertedPalette(IlvPalette* invertedPalette);
    IlvPalette*		getPalette();
    IlvPalette*		getInvertedPalette();

protected:
    void		deselectItem();
    void		selectItem(IlShort choose);
    virtual void	placeLabel(IlInt choose = -1);

    void		neutralZoneCreation(IlUInt nZR);

    IlvPalette*		_palette;
    IlvPalette*		_invpalette;

    IlvDisplay*		_display;
    IlUInt		_portions;
    IlUInt		_neutralZoneRadius;
    IlUInt		_cmlIn;
    IlUInt		_cmlOut;
    IlUInt		_cmlSegment;
    IlUInt		_space;
    IlvGraphicSet*	_neutralZone;
    IlvPseudoTransparentView*  _mainView;
    IlvMessageLabel**	_portionItem;
    IlvView*		_parentView;
    IlvPoint		_origin;
    IlvMessageLabel*	_activeItem;
    IlvTimer*		_timer;
    IlUShort		_timerCounter;
//private:
    IlShort		_choose;
    IlvPoint		_point;
    IlBoolean		_visible;
    IlBoolean		_moveSelectedItem;
    // To draw the selected item
    IlvContainer*	_selectedItemView;
    IlvMessageLabel*	_selectedItemMessageLabel;
    IlvPalette*		_xorPalette;
};

#endif /* __Ilv_Gadgets_Mmenu_H */
