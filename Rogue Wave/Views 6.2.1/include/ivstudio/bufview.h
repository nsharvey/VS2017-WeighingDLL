// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/bufview.h
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
// Declaration of buffer view classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Bufview_H
#define __IlvSt_Bufview_H

#if !defined(__Ilv_Vframe_H)
#include <ilviews/gadgets/vframe.h>
#endif

#if !defined(__Ilv_Desktop_H)
#include <ilviews/gadgets/desktop.h>
#endif

#if !defined(__IlvSt_Stbuffer_H)
#include <ivstudio/stbuffer.h>
#endif

#if !defined(__Ilv_Gadmgr_Rectscmg_H)
#include <ilviews/gadmgr/rectscmg.h>
#endif

class IlvStBufferViewHook;
class IlvScrolledView;

extern ILVSTEXPORTEDVAR(const char*) IlvNmMakeBufferFrame;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBufferViewChanged;
// --------------------------------------------------------------------------
class  ILVSTUDIOCLASS IlvStSCManagerRectangle
: public IlvSCManagerRectangle {
public:
    IlvStSCManagerRectangle(IlvGadgetContainer* parent,
			    const IlvRect& rect,
			    IlvPalette* palette = 0);
    ~IlvStSCManagerRectangle();
    void	setManagerField(IlvManager* mgr) { _manager = mgr; }
    void	callRemoveHook() { removeHook(); }
    void	callInitHook()   { initHook();   }
    void	viewDeleted()    { _view = 0;    }
protected:
    IlvManager*	    _defaultManager;
}; // class IlvStSCManagerRectangle


// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStBufferFrame
: public IlvViewFrame {
public:
    ~IlvStBufferFrame();
    IlvStBuffer*	getBuffer() const { return _buffer; }
    virtual IlvView*	getBufferView() const = 0;
    virtual void	adjustBoundingBox();
    virtual void	installView(IlvView*);
    virtual void	uninstallView(IlvView*);

protected:
    IlvStBufferFrame(IlvStBuffer* buffer,
		     IlvView* parent,
		     const char* title,
		     const IlvRect& size,
		     IlBoolean visible = IlTrue);
protected:
    IlvStBuffer*	    _buffer;
    IlvStBufferViewHook*    _hook;
    DeclareViewProperties();

public:

    virtual void	restoreFrame();
    virtual void	minimizeFrame();
    virtual void	maximizeFrame();
    virtual void	handleInput(IlvEvent&);

    virtual void	showScrollBars();
    virtual void	hideScrollBars();
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvSt2DBufferFrame
: public IlvStBufferFrame {
public:
    IlvSt2DBufferFrame(IlvStBuffer* buffer,
		       IlvView*	parent,
		       const char* title,
		       const IlvRect& rect,
		       IlBoolean visible = IlTrue);
    ~IlvSt2DBufferFrame();
    IlvView* getBufferView() const;
protected:
    IlvStSCManagerRectangle* _scMgrRect;

    DeclareViewProperties();
}; // class ILVSTUDIOCLASS IlvSt2DBufferFrame

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStBufferFrameBuilder
{
public:
    virtual ~IlvStBufferFrameBuilder() {}
    virtual const char* getBufferType() const = 0;
    virtual IlvStBufferFrame* buildFrame(IlvStBuffer* buffer,
					 IlvView* parent,
					 const char* title,
					 const IlvRect& bbox,
					 IlBoolean visible) = 0;
}; // class IlvStBufferFrameBuilder

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStWorkDesktop
: public IlvDesktopManager {
public:
    IlvStWorkDesktop(IlvStudio* editor, IlvView* view);
    virtual void frameSelectionChanged(IlvViewFrame*, IlvViewFrame*);
    virtual void frameMinimized(IlvViewFrame*, int);
    virtual void frameMaximized(IlvViewFrame*, int);
    virtual void frameRestored(IlvViewFrame*, int);

    IlvStBuffer*	getBuffer(IlvViewFrame* frame) const;
    IlvStBufferFrame*	getBufferFrame(IlvStBuffer*) const;
    IlvStBufferFrame*	addBuffer(IlvStBuffer*);
    void		realizeBuffer(IlvStBuffer*);
    void		removeBuffer(IlvStBuffer*);
    void		getDocumentWindowSize(IlvDim& w, IlvDim& h) const;

    // Frame builders
    void addFrameBuilder(IlvStBufferFrameBuilder*);
    IlvStBufferFrameBuilder* getFrameBuilder(const char*) const;
    IlvStBufferFrame* buildFrame(IlvStBuffer*,
				 IlvView* parent,
				 const char* title,
				 const IlvRect&,
				 IlBoolean visible);
protected:
    IlvStudio*	_editor;
}; // class IlvStMainPanelDesktop

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_bufview)
#endif /* IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
#endif /* __IlvSt_Bufview_H */
