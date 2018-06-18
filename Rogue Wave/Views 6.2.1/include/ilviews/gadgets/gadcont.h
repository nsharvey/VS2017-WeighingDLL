// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/gadcont.h
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
// Declaration of the IlvGadgetContainer class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Gadcont_H
#define __Ilv_Gadgets_Gadcont_H

#if !defined(ILVNODEFAULTLOOK)
#  include <ilviews/looks/default.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Base_Look_H)
#  include <ilviews/base/look.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#  include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Contain_Holder_H)
#  include <ilviews/contain/holder.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#  include <ilviews/graphics/attach.h>
#endif

class IlvButton;

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetContainer
    : public IlvContainer,
      public IlvStylist
{
public:
    IlvGadgetContainer(IlvDisplay*	display,
		       const char*	name,
		       const char*	title,
                       const IlvRect&	rect,
                       IlBoolean	useacc = IlFalse,
                       IlBoolean	visible = IlTrue);

    IlvGadgetContainer(IlvDisplay*	display,
		       const char*	name,
		       const char*	title,
                       const IlvRect&	rect,
		       IlUInt		properties,
                       IlBoolean	useacc		= IlFalse,
                       IlBoolean	visible		= IlTrue,
		       IlvSystemView	transientFor	= 0);

    IlvGadgetContainer(IlvAbstractView*	parent,
                       const IlvRect&	rect,
                       IlBoolean	useacc	= IlFalse,
                       IlBoolean	visible = IlTrue);

    IlvGadgetContainer(IlvDisplay*	display,
                       IlvSystemView	parent,
                       const IlvRect&	rect,
                       IlBoolean	useacc	= IlFalse,
                       IlBoolean	visible = IlTrue);

    IlvGadgetContainer(IlvDisplay*	display,
		       IlvSystemView	window,
                       IlBoolean	useacc = IlFalse);
    virtual ~IlvGadgetContainer();

    virtual void	setBackground(IlvColor* c);
    virtual void	setBackgroundBitmap(IlvBitmap* b);
    virtual void	setBackgroundPainter(IlvBackgroundPainter painter,
					     IlAny = 0);
    // Managing objects
    virtual void	addObject(IlvGraphic*	obj,
				  IlBoolean	redraw = IlFalse);
    virtual void	addObject(const char*	objectName,
				  IlvGraphic*	obj,
				  IlBoolean	redraw = IlFalse);
    virtual IlBoolean	removeObject(IlvGraphic* obj,
				     IlBoolean	redraw = IlFalse);
    virtual IlvGraphic*	replace(IlvGraphic*	oldObject,
				IlvGraphic*	newObject,
				IlBoolean	redraw = IlFalse);
    void		removeObjects(IlBoolean deleteIt = IlTrue,
				      IlBoolean redraw   = IlTrue);

    // Default Button
    void		setDefaultButton(IlvButton*	button,
					 IlBoolean	redraw = IlTrue);
    void		changeDefaultButton(IlvButton*,
					    IlBoolean	redraw = IlTrue);
    inline IlvButton*	getDefaultButton() const { return _defaultButton; }

    // Focus management
    virtual IlBoolean	isFocusTabClient(const IlvGraphic*) const;
    virtual void	focusIn(IlvEvent& event);
    virtual void	focusOut(IlvEvent& event);

    virtual IlvGraphic*	getFocus() const;

    virtual void	setFocus(IlvGraphic*	graphic	= 0,
				 IlBoolean	redraw	= IlTrue);

    virtual void	moveFocusAfter(IlBoolean redraw = IlTrue);

    virtual void	moveFocusBefore(IlBoolean redraw = IlTrue);

    virtual void	moveFocusFirst();
    virtual void	moveFocusLast();
    inline IlvGraphicHolder*	getNextFocusHolder() const
	{
	    return getHolder()
		   ? getHolder()->getNextFocusHolder()
		   : 0;
	}
    inline IlvGraphicHolder*	getPreviousFocusHolder() const
	{
	    return getHolder()
		   ? getHolder()->getPreviousFocusHolder()
		   : 0;
	}
    virtual IlvGraphic*	getNextFocusGraphic(IlvGraphic* object) const;

    virtual IlvGraphic*	getPreviousFocusGraphic(IlvGraphic* object) const;

    virtual IlvGraphic*	getFirstFocusGraphic() const;

    virtual IlvGraphic*	getLastFocusGraphic() const;

    virtual IlBoolean	isFocusAllowed() const;

    virtual IlBoolean	allowFocus(IlBoolean value);

    virtual void	drawFocus(IlvPort*,
				  const IlvTransformer*	t    = 0,
				  const IlvRegion*	clip = 0);

    // I/O
    virtual
    IlvViewInputFile*	createInputFile(IL_STDPREF istream&);
    virtual IlBoolean	read(IL_STDPREF istream& );

    inline IlBoolean	isAutoResizing() const { return _autoResize; }

    inline IlBoolean	autoResize(IlBoolean a) { return (_autoResize = a); }

    inline IlBoolean	isLoadingResources() const { return _loadResources; }
    inline IlBoolean	loadResources(IlBoolean l)
	{ return (_loadResources = l); }

    virtual void	handleExpose(IlvEvent&);
    // Geometry management
    virtual void	handleResize(IlvRect& rect);

    virtual IlBoolean	dispatchToObjects(IlvEvent& event);

    virtual IlvGraphic*	getGrab() const;

    virtual void	setGrab(IlvGraphic* object);

    virtual void	removeGrab();

    inline IlvLookFeelHandler*	getLookFeelHandler() const
	{ return getHolder()->getLookFeelHandler(); }

    inline void		setLookFeelHandler(IlvLookFeelHandler* lfh)
	{ getHolder()->setLookFeelHandler(lfh); }

    // Styling
    virtual IlvStylist*			getParentStylist() const;
    virtual std::list<IlvStyleSheet*>*	getStyleSheetList(IlBoolean) const;
    virtual IlvStylist* getStylist() const;

    inline IlvGraphic*	getOverriddenFocus() const
	{ return _overriddenFocus; }

    inline void		overrideFocus(IlvGraphic* obj)
	{ _overriddenFocus = obj; }

    virtual void	applyResize(IlFloat	sx,
				    IlFloat	sy,
				    IlBoolean	redraw = IlTrue);
    void		applyResize(IlvGraphic*,
				    IlFloat	sx,
				    IlFloat	sy,
				    IlBoolean	redraw = IlTrue);
    inline void		applyResize(IlBoolean	redraw = IlTrue)
	{ applyResize((IlFloat)1., (IlFloat)1., redraw); }
    inline void		applyResize(IlvGraphic* g, IlBoolean redraw = IlTrue)
	{ applyResize(g, (IlFloat)1., (IlFloat)1., redraw); }

    // Misc
    inline IlAny	getClientData() const     { return _clientData; }
    inline void		setClientData(IlAny dta)  { _clientData = dta;  }

    // Bidi interface
    virtual
    IlvBidiContext*	getBidiContext(IlBoolean fallback = IlTrue) const;
    virtual
    IlvBidiContext*	getDefaultBidiContext() const;
    virtual IlBoolean	setBidiContext(IlvBidiContext*);
    virtual IlBoolean	changeOrientation();
    IlBoolean		isRightToLeft() const;

    DeclareViewAccessors();

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static  IlSymbol*	_setFocusMethod;
    static  IlSymbol*	_getFocusMethod;
    static  IlSymbol*	_allowFocusValue;
    static  IlSymbol*	_getGrabMethod;
    static  IlSymbol*	_setGrabMethod;
    static  IlSymbol*	_removeGrabMethod;
    static  IlSymbol*	_autoResizeValue;

protected:
    void		init();
    virtual void	beforeDraw(IlvPort*		dst,
				   const IlvTransformer* t	= 0,
				   const IlvRegion*	clip	= 0);
    virtual void	afterDraw(IlvPort*,
				  const IlvTransformer*	t = 0,
				  const IlvRegion*	r = 0);
    virtual void	cleanObj(IlvGraphic* object);
    virtual void	drawDefaultButton(IlvPort*,
					  const IlvTransformer*,
					  const IlvRegion*);
    void	computeDefaultButtonRegion(IlvRegion& region,
					   const IlvTransformer*) const;

    IlvGraphic*		_lastGraphicIn;
    IlvGraphic*		_focusGraphic;
    IlvGraphic*		_lastFocusGraphic;
    IlvGraphic*		_overriddenFocus;
    IlBoolean		_allowFocus;
    IlvGraphic*		_grabGraphic;
    IlvGraphic*		_graphicButtonDown;
    IlvGraphic*		_graphicKeyDown;
    IlvGraphic*		_graphicSelection;
    IlBoolean		_autoResize;
    IlBoolean		_loadResources;
    IlAny		_clientData;
    IlvButton*		_defaultButton;
    IlvButton*		_veryDefaultButton;
    IlBoolean		_hasDefaultBg;
    IlBoolean		_hasDefaultBgBitmap;
    IlBoolean		_hasDefaultBgPainter;
    IlvBackgroundPainter _backgroundPainter;
    IlAny		_backgroundPainterArg;
    IL_MUTABLE std::list<IlvStyleSheet*>* _styleSheets;

    static enum IlvFocusDetail _focusDetail;

    DeclareLazyViewProperties();

public:
    // Not documented
    inline IlBoolean	hasDefaultBackground() const
	{ return _hasDefaultBg; }
    inline IlBoolean	hasDefaultBackgroundBitmap() const
	{ return _hasDefaultBgBitmap; }
    inline IlBoolean	hasDefaultBackgroundPainter() const
	{ return _hasDefaultBgPainter; }
    inline IlvBackgroundPainter getBackgroundPainter() const
	{ return _backgroundPainter; }
    inline IlvButton*	getVeryDefaultButton() const
	{ return _veryDefaultButton; }
    virtual void	sendFocusIn(IlvGraphic*);
    virtual void	sendFocusOut(IlvGraphic*);
    IlvGraphic*		lastRecordedContains(const IlvPoint& p,
					     IlvEvent&) const;
    void		recordEvent(IlvGraphic*, IlvEvent& event) const;
    virtual void	invalidateObject(const IlvGraphic*);
    virtual IlAny	internalHandleMnemonic(char) const;
    virtual IlvGraphic*	handleMnemonic(char) const;
    virtual void	objectMouseEnter(IlvGraphic*);
    virtual void	objectMouseLeave(IlvGraphic*);
    void		selectionRequest(const IlvGraphic*);
    void		cleanSelection(const IlvGraphic*);
    virtual void	changeLook();
    virtual void	changeLayoutAttributes(IlAny ,IlAny);
};

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvGadgetViewInputFile
    : public IlvViewInputFile
{
public:
    IlvGadgetViewInputFile(IL_STDPREF istream& stream,
			   IlvGadgetContainer* cont = 0)
	: IlvViewInputFile(stream, cont)
    {}

    virtual IlvGraphic*	readObject();
    virtual IlBoolean	parseBlock(const char*);
};

// --------------------------------------------------------------------------
ILVGDTMODULEINIT(gadcont);

#endif /* !__Ilv_Gadgets_Gadcont_H */
