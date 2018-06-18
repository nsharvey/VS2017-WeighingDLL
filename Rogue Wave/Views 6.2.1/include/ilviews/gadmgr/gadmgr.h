// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadmgr/gadmgr.h
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
// Declaration of the IlvGadgetManager class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadmgr_Gadmgr_H
#define __Ilv_Gadmgr_Gadmgr_H

#if !defined(__Ilv_Gadmgr_Macros_H)
#  include <ilviews/gadmgr/macros.h>
#endif
#if !defined(__Ilv_Manager_Io_H)
#  include <ilviews/manager/io.h>
#endif
#if !defined(__Ilv_Manager_Holder_H)
#  include <ilviews/manager/holder.h>
#endif

class ILVGDTMGREXPORTED IlvGadgetManager;
typedef void (*IlvManagerSelectCallback)(IlvGadgetManager*,
					 IlvGraphic*,
					 IlBoolean);

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvGadgetManager
    : public IlvManager {
public:
    IlvGadgetManager(IlvDisplay* display,
                     int         layers    = 2,
                     IlBoolean   useacc    = IlTrue,
                     IlUShort   maxInList  = IlvMaxObjectsInList,
                     IlUShort   maxInNode  = IlvMaxObjectsInList);
    virtual ~IlvGadgetManager();
    // ____________________________________________________________
    virtual void             addObject(IlvGraphic*,
				       IlBoolean = IlTrue,
				       int       = -1);
    virtual void             addObject(const char*,
				       IlvGraphic*,
				       IlBoolean = IlTrue,
				       int       = -1);
    virtual void             handleInput(IlvEvent&,
					 IlvView*);
    IlvGraphic*              lastRecordedContains(const IlvPoint&,
						  const IlvView*,
						  IlvEvent&) const;
    void                     recordEvent(IlvGraphic*,
					 IlvEvent&,
					 IlvView*) const;
    virtual IlBoolean        cleanObj(IlvGraphic*,
				      IlBoolean = IlTrue,
				      IlBoolean = IlTrue);
    virtual IlBoolean       dispatchToObjects(IlvEvent&,
					      IlvView*);
    IlBoolean               isLoadingResources() const
	{ return _loadResources; }
    IlBoolean               loadResources(IlBoolean l)
	{ return (_loadResources = l); }
    virtual IlBoolean	     isFocusTabClient(const IlvGraphic*) const;
    virtual void             focusIn(IlvEvent&);
    virtual void             focusOut(IlvEvent&);
    virtual IlBoolean        gadgetShortCut(IlvEvent&);
    IlvGraphic*		     getAcceleratorGadget(IlvEvent&) const;
    inline IlvLookFeelHandler* getLookFeelHandler() const
	{ return getHolder()->getLookFeelHandler(); }
    inline void		     setLookFeelHandler(IlvLookFeelHandler* lfh)
	{ getHolder()->setLookFeelHandler(lfh); }
    virtual IlvGraphic*      getFocus() const;
    virtual void             setFocus(IlvGraphic* graphic = 0,
				      IlBoolean   redraw  = IlTrue);
    virtual void             moveFocusAfter(IlBoolean redraw = IlTrue);
    virtual void             moveFocusBefore(IlBoolean redraw = IlTrue);
    virtual void             moveFocusFirst();
    virtual void             moveFocusLast();
    virtual IlvGraphic*      getNextFocusGraphic(IlvGraphic* object) const;
    virtual
    IlvGraphic*		getPreviousFocusGraphic(IlvGraphic* object) const;
    virtual IlvGraphic*      getFirstFocusGraphic() const;
    virtual IlvGraphic*      getLastFocusGraphic()  const;
    virtual void             objectMouseEnter(IlvGraphic*,
					      IlvView*);
    virtual void             objectMouseLeave(IlvGraphic*,
					      IlvView*);
    IlvGraphicHolder*        getNextFocusHolder() const
	{ return getHolder() ? getHolder()->getNextFocusHolder() : 0; }
    IlvGraphicHolder*        getPreviousFocusHolder() const
	{ return getHolder() ? getHolder()->getPreviousFocusHolder() : 0; }
    virtual IlvManagerInputFile*
                             createInputFile(IL_STDPREF istream&);
    virtual IlvManagerOutputFile*
                             createOutputFile(IL_STDPREF ostream&) const;
    virtual void             viewResized(const IlvView*, IlvRect&);
    virtual void             applyResize(IlvView*   view,
					 IlFloat    sx,
					 IlFloat    sy,
					 IlBoolean redraw = IlTrue);
    inline void              applyResize(IlvView* view,
					 IlBoolean redraw = IlTrue)
	{ applyResize(view, (IlFloat)1., (IlFloat)1., redraw); }
    virtual void             applyResize(IlvView*    view,
					 IlvGraphic* g,
					 IlFloat     sx,
					 IlFloat     sy,
					 IlBoolean   redraw = IlTrue);
    inline void              applyResize(IlvView*    view,
					 IlvGraphic* g,
					 IlBoolean  redraw = IlTrue)
	{ applyResize(view, g, (IlFloat)1., (IlFloat)1., redraw); }
    virtual IlBoolean       isFocusAllowed() const;
    virtual IlBoolean       allowFocus(IlBoolean flag);
    virtual void             drawFocus(IlvPort*              dst,
				       const IlvTransformer* t = 0,
				       const IlvRegion*      clip = 0) const;
    inline IlvGraphic*       getOverriddenFocus() const
	{ return _overriddenFocus; }
    inline void              overrideFocus(IlvGraphic* obj)
	{ _overriddenFocus = obj; }
    virtual IlvGraphic*      getGrab() const;
    virtual void             setGrab(IlvGraphic* object);
    virtual void             removeGrab();
    inline IlBoolean         isAutoResizing() const
	{ return _autoResize; }
    inline IlBoolean        autoResize(IlBoolean a)
	{
	    _autoResize = a;
	    return a;
	}
    virtual void	    setBackground(IlvView* view,
					  IlvColor*  color,
					  IlvBitmap* bitmap = 0);
    inline IlBoolean        getIgnoringSize() const
	{ return _ignoringSize; }
    inline void             setIgnoringSize(IlBoolean val)
	{ _ignoringSize = val; }
    inline IlBoolean        getIgnoringBackground() const
	{ return _ignoringBackground; }
    inline void             setIgnoringBackground(IlBoolean val)
	{ _ignoringBackground = val; }
    inline IlBoolean        getIgnoringBackgroundBitmap() const
	{ return _ignoringBackgroundBitmap; }
    inline void             setIgnoringBackgroundBitmap(IlBoolean val)
	{ _ignoringBackgroundBitmap = val; }
    virtual void            setSelected(IlvGraphic*,
					IlBoolean = IlTrue,
					IlBoolean    = IlTrue);
    inline void             setSelectCallback(IlvManagerSelectCallback cb)
	{ _selectCallback = cb; }
    void                     sendFocusIn(IlvGraphic*);
    void                     sendFocusOut(IlvGraphic*);
    virtual void             addView(IlvView*);
    virtual IlBoolean        removeView(IlvView*);
    virtual void             setView(IlvView*);
    virtual IlvColor*        getViewBackground() const;
    virtual IlvBitmap*       getViewBackgroundBitmap() const;
    virtual void             setViewBackground(IlvColor*, IlvBitmap* = 0);
    virtual void             getViewSize(IlvDim&, IlvDim&) const;
    virtual void             setViewSize(IlvDim, IlvDim);
    virtual IlvDim           getViewWidth() const;
    virtual IlvDim           getViewHeight() const;
    void                     selectionRequest(const IlvGraphic*);
    void                     cleanSelection(const IlvGraphic*);
    // Look, Language and Bidi callbacks _________________________________
    virtual void	     changeLook();

    IlBoolean               isRightToLeft() const; // ILVBIDI

    IlvPos		    getAttachWidth();
    IlvPos		    getAttachHeight();
    void		    setAttachSize(IlvPos, IlvPos);
    IlBoolean		    isAttachAutoSizing();
    void		    setAttachAutoSizing(IlBoolean);

    virtual IlBoolean	    wantsNavigationHandler() const;

protected:
    IlvGraphic*              _graphicButtonDown;
    IlvGraphic*              _graphicKeyDown;
    IlvGraphic*              _lastGraphicIn;
    IlvGraphic*              _focusGraphic;
    IlvGraphic*              _lastFocusGraphic;
    IlvGraphic*              _grabGraphic;
    IlvGraphic*              _graphicSelection;
    IlvGraphic*              _overriddenFocus;
    IlBoolean                _loadResources;
    IlvManagerSelectCallback _selectCallback;
    IlvColor*                _viewBackground;
    IlvBitmap*               _viewBackgroundBitmap;
    IlvDim                   _viewWidth, _viewHeight;
    IlBoolean 		     _allowFocus;
    IlBoolean                _autoResize;
    IlBoolean	 	     _ignoringSize;
    IlBoolean		     _ignoringBackground;
    IlBoolean		     _ignoringBackgroundBitmap;
    IlvPos		     _attachWidth;
    IlvPos		     _attachHeight;
    IlBoolean		     _attachAutoSizing;

    void                     focusKeySetFocus(IlvGraphic* = 0,
					      IlBoolean   = IlTrue);

    static enum IlvFocusDetail _focusDetail;
    friend class IlvEdBuffer;
    friend class IlvEdGadgetBuffer;
};

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvGadgetManagerOutputFile
    : public IlvManagerOutputFile {
public:
    IlvGadgetManagerOutputFile(IL_STDPREF ostream& stream,
                               const IlvGadgetManager* manager = 0)
    : IlvManagerOutputFile(stream, manager)
	{}
    // ____________________________________________________________
    const IlvGadgetManager*  getGadgetManager() const
	{ return(const IlvGadgetManager*)getManager(); }
    virtual void             writeObject(const IlvGraphic*);
    virtual const char*      typeOf() const;
    virtual void             saveMoreInfo(IlUInt, IlvGraphic* const*);
};

// --------------------------------------------------------------------------
class ILVGDTMGREXPORTED IlvGadgetManagerInputFile
    : public IlvManagerInputFile {
public:
    IlvGadgetManagerInputFile(IL_STDPREF istream& stream,
			      IlvGadgetManager* manager = 0)
        : IlvManagerInputFile(stream, manager)
    {}
    // ____________________________________________________________
    inline IlvGadgetManager*        getGadgetManager() const
	{ return (IlvGadgetManager*)getManager(); }
    virtual void             readAll(IlvManager*);
    virtual IlvGraphic*      readObject();
    virtual IlBoolean        parseBlock(const char*);
    virtual const char*      typeOf() const;
};

#endif /* !__Ilv_Gadmgr_Gadmgr_H */
