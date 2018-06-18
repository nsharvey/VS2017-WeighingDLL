// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/gadbuf.h
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
// Declaration of Gadget Buffer classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Gadbuf_H
#define __IlvSt_Gadbuf_H

#ifndef __IlvSt_Stbuffer_H
#include <ivstudio/stbuffer.h>
#endif
#ifndef __IlvSt_Bufview_H
#include <ivstudio/bufview.h>
#endif
#ifndef __IlvSt_Message_H
#include <ivstudio/message.h>
#endif

class IlvStGadgetHandleMgr;
// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStGadgetBuffer : public IlvStBuffer
{
public:
    IlvStGadgetBuffer(IlvStudio* editor,
		      const char* name,
		      IlvManager* mgr = 0);
    ~IlvStGadgetBuffer();
    // ____________________________________________________________
    IlvGadgetManager*	getGadgetManager() const
			{
			    return (IlvGadgetManager*)getManager();
			}
    virtual void 	setView(IlvView*);
    virtual void 	insert(const char* filename);
    virtual void 	setSize(IlvDim w,
				IlvDim h, 
    				IlBoolean updateViewOptsPnl = IlTrue);
    virtual IlvDim 	getWidth() const;
    virtual IlvDim 	getHeight() const;
    virtual IlBoolean	isAGadgetBuffer() const;
    virtual IlBoolean   isA2DBuffer() const;
    virtual const char* getType () const;
    virtual void 	select();
    virtual void 	unSelect();
    virtual const char* getTypeLabel() const;
    virtual IlBoolean	getIgnoringSize() const;
    virtual void	setIgnoringSize(IlBoolean);
    virtual IlBoolean	getIgnoringBackground() const;
    virtual void	setIgnoringBackground(IlBoolean);
    virtual IlvBitmap*	getBackgroundBitmap() const;
    virtual void	setUpPanelClass(IlvStPanelClass*) const;
    virtual const char* const* getToolBarCommands(IlUShort& count) const;
    inline IlvStGadgetHandleMgr* getHandleMgr() const { return _handleMgr; }
    virtual char*	save(IlBoolean restoreModified = IlFalse);

    static void		RegisterType(IlvStudio*);

protected:
    IlvDim 		_bufferWidth;
    IlvDim 		_bufferHeight;
    IlvStGadgetHandleMgr* _handleMgr;
}; // class IlvStGadgetBuffer

class ILVSTGADGETCLASS IlvStGadgetHandleMgr
{
public:
    IlvStGadgetHandleMgr(IlvDisplay* display, IlvStGadgetBuffer* buffer);
    ~IlvStGadgetHandleMgr();

    IlvPosition		getDraggedHandle() const;
    void		setDraggedHandle(IlvPosition p);
    IlvDim		getHandleSize() const;
    IlvPosition		pointToHandle(IlvPoint& point);
    void		getHandleRect(IlvPosition pos, IlvRect& rect) const;
    inline IlvPalette*	getPalette() const { return _palette; };

protected: 
    IlvStGadgetBuffer*	_buffer;
    IlvPalette*		_palette;
    IlvPosition		_draggedHandle;
};

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStModeChangedSubscription : public IlvStSubscription
{
public:
    IlvStModeChangedSubscription(IlvStudio* editor);
    void		doIt(IlvStudio* editor, const IlvStMessage*, IlAny);
    void		modeChanged(IlvStGadgetBuffer& buffer,
				    const IlvStMode& mode);
    static void		ResetTransformer(IlvStGadgetBuffer& buffer);
    static void		UnSetToolTipHandler(IlvStGadgetBuffer& buffer);
    static void		UpdateToolTipHandler(IlvStGadgetBuffer& buffer);
    static IlvGraphicHolderToolTipHandler&	GetToolTipHandler();
};

// --------------------------------------------------------------------------
class  ILVSTGADGETCLASS IlvStSCGadgetMgrRectangle
    : public IlvSCManagerRectangle
{
public:
    IlvStSCGadgetMgrRectangle(IlvGadgetContainer*	parent,
			      const IlvRect&		rect,
			      IlvStGadgetBuffer*	buffer,
			      IlvPalette*		palette = 0);
    ~IlvStSCGadgetMgrRectangle();

    virtual void	computeContentsBBox(IlvRect& bbox) const;
    virtual void	viewDeleted();

protected:
    IlvStGadgetBuffer*	_buffer;
}; // class IlvStSCGadgetMgrRectangle

// --------------------------------------------------------------------------
class  ILVSTGADGETCLASS IlvStGadBufBackgroundViewHook
: public IlvManagerViewHook
{
public:
    IlvStGadBufBackgroundViewHook(IlvStGadgetBuffer*	buffer,
				  IlvManager*		manager, 
				  IlvView*		view);
    ~IlvStGadBufBackgroundViewHook();

    virtual void	beforeDraw(IlvPort* dst,
				   const IlvTransformer* t = 0,
				   const IlvRegion* r = 0,
				   const IlvRegion* clip = 0);
    void		drawHandle(IlvPort* dst,
				   IlvPosition pos,
				   const IlvRect& rect,
				   IlvPalette* palette,
				   const IlvRegion* clip) const;
    virtual void	transformerChanged(const IlvTransformer* current,
					   const IlvTransformer* previous);
    virtual void	contentsChanged();
    inline IlvBitmap*	getBackgroundBitmap() { return _backgroundBitmap; }
    virtual void	resetBitmaps();

protected:
    IlvStGadgetBuffer*	_buffer;
    IlvPalette*		_outPalette;
    IlvBitmap*		_backgroundBitmap;
    IlvBitmap*		_scaledBitmap;
}; // class IlvStGadBufBackgroundViewHook


// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStGadgetBufferFrame : public IlvStBufferFrame
{
public:
    IlvStGadgetBufferFrame(IlvStGadgetBuffer*	buffer,
			   IlvView*		parent,
			   const char*		title,
			   const IlvRect&	rect,
			   IlBoolean		visible = IlTrue,
			   IlBoolean		scrolling = IlFalse);
    ~IlvStGadgetBufferFrame();

    inline IlvView*	getBufferView() const { return _buffer->getView(); }
    inline 
    IlvStSCGadgetMgrRectangle* getManagerRectangle() { return _mgrRect; }
    inline 
    IlvGadgetContainer*	getGadgetContainer() { return _gadCont; }
    inline IlBoolean	isScrolling() const { return _scrolling; }
    inline
    IlvStGadgetBuffer*	getGadgetBuffer()
			{
			    return (IlvStGadgetBuffer*) _buffer;
			};
    virtual void	showScrollBars();
    virtual void	hideScrollBars();
    virtual void 	centerView();
    virtual void 	resizeToBufferSize();
    virtual void	maximizeFrame();
    virtual void	restoreFrame();
    inline IlvStGadBufBackgroundViewHook* getHook() { return _hook; };

protected:
    IlvStSCGadgetMgrRectangle*		_mgrRect;
    IlvGadgetContainer*			_gadCont;
    IlBoolean				_scrolling;
    IlvStGadBufBackgroundViewHook*	_hook;

    DeclareViewProperties();
}; // class ILVSTUDIOCLASS IlvStGadgetBufferFrame

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStGadgetBufferFrameBuilder
: public IlvStBufferFrameBuilder
{
public:
    const char*		getBufferType() const;
    IlvStBufferFrame*	buildFrame(IlvStBuffer* buffer,
				   IlvView* parent,
				   const char* title,
				   const IlvRect& bbox,
				   IlBoolean visible);
}; // class IlvStGadgetBufferFrameBuilder

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTGADGETCLASS(st_gadbuf)
#endif /* IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
#endif /* __IlvSt_Gadbuf_H */
