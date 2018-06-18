// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/appli/appbuf.h
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
// Declaration of application buffer classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Appbuf_H
#define __IlvSt_Appbuf_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif
#ifndef __IlvSt_Gadbuf_H
#include <ivstudio/gadgets/gadbuf.h>
#endif
#ifndef __Ilv_Desktop_H
#include <ilviews/gadgets/desktop.h>
#endif
#ifndef __IlvSt_Stddrop_H
#include <ivstudio/stddrop.h>
#endif

class IlvManager;
class IlvTransparentIcon;
class IlvPopupMenu;

class IlvStPanelInstance;
class IlvStPanelInstanceFrame;
class IlvStudio;
class IlvStDdRecipientManager;
class IlvStApplicationBufferDesktop;

extern ILVSTAPPLIEXPORTEDVAR(const char*) IlvNmPanelInstanceContainerCreated;

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStApplicationBuffer
: public IlvStGadgetBuffer
{
public:
    IlvStApplicationBuffer(IlvStudio*);
    ~IlvStApplicationBuffer();

    virtual const char* getDataFile() const;
    void    		addPanelInstance(IlvStPanelInstance*);
    void		removePanelInstance(IlvStPanelInstance*);
    void		addSubPanelInstance(IlvStPanelInstance*);
    void		removeSubPanelInstance(IlvStPanelInstance*);
    virtual IlBoolean 	isModified() const;
    virtual void 	setModified(IlBoolean);

    static IlvStApplicationBuffer* Get(IlvStudio*);

public:

    virtual const char*	getType() const;
    virtual const char* getTypeLabel() const;
    virtual IlBoolean	isAnApplicationBuffer() const;
    virtual IlBoolean	canBePanelClass() const;
    virtual IlvStError* close(IlAny caller = 0, IlAny arg = 0);
    virtual IlBoolean	accept(IlvGraphic*);
    virtual IlvDim 	getWidth() const;
    virtual IlvDim 	getHeight() const;
    virtual void 	setView(IlvView*);
    virtual IlvStError*	deleteSelections();
    virtual char* 	save(IlBoolean restoreModified);

    IlvStApplicationBufferDesktop* getDesktopManager() const
	{ return _desktop; }

protected:
    IlvStDdRecipientManager* _ddRecMgr;
    IlvDim _width;
    IlvDim _height;
    IlvStApplicationBufferDesktop* _desktop;

public:
    virtual IlvStError* doSaveCommand(IlAny arg);
    virtual IlvStError* doSaveAsCommand(IlAny arg);
    virtual IlvStError* doRevertCommand(IlAny arg);
    virtual IlvStError* doCloseCommand(IlAny arg);
    virtual IlvStError* doTestCommand(IlAny arg);
    virtual IlvStError* doInspectCommand(IlAny arg);
    virtual IlvStError* doGenerateCommand(IlAny arg);

    IlvStPanelInstanceFrame* getPanelInstanceFrame(const char*) const;
    IlvStDdRecipientManager* getDdRecipientManager() const
	{ return _ddRecMgr; }
    IlvContainer* createPanelInstanceContainer(IlvAbstractView* parent,
					       IlvStPanelInstance*);

    friend class IlvStApplicationBufferDesktop;
}; // class ILVSTUDIOCLASS IlvStApplicationBuffer

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStApplicationBufferDesktop
: public IlvDesktopManager {
public:
    IlvStApplicationBufferDesktop(IlvStApplicationBuffer* appbuf);
    ~IlvStApplicationBufferDesktop();
    IlvStApplicationBuffer* getApplicationBuffer() const
	{ return _appbuf; }
    IlvStPanelInstanceFrame* getPanelInstanceFrame(IlvStPanelInstance*) const;

    void setActiveTitleBarPalette(IlvPalette* palette);
    void setInactiveTitleBarPalette(IlvPalette* palette);
protected:
    IlvStApplicationBuffer* _appbuf;
    IlvPalette*		    _activePalette;
    IlvPalette*		    _inactivePalette;
    IlvPopupMenu*	    _menu;

public:
    virtual IlvPalette* getActiveTitleBarPalette() const;
    virtual IlvPalette* getInactiveTitleBarPalette() const;
    virtual void	getMinimizedBBox(IlvViewFrame*, IlvRect&) const;
    virtual void	updateMinimizedFrames();
    IlvPopupMenu*   getMenu() const { return _menu; }
    void	    makeMenu(IlvPopupMenu* menu, IlShort pos);
}; // class IlvStApplicationBufferDesktop

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStApplicationBufferFrame
: public IlvStBufferFrame {
public:
    IlvStApplicationBufferFrame(IlvStApplicationBuffer* buffer,
			   IlvView* parent,
			   const char* title,
			   const IlvRect& rect,
			   IlBoolean visible = IlTrue,
			   IlBoolean scrolling = IlTrue);
    ~IlvStApplicationBufferFrame();
    IlvStApplicationBuffer* getBuffer() const
	{ return (IlvStApplicationBuffer*) _buffer; }
    IlvView*		getBufferView() const { return _bufferView; }
    //virtual void	adjustBoundingBox();
    IlBoolean		isScrolling() const { return _scrolling; }
    virtual void	showScrollBars();
    virtual void	hideScrollBars();
    virtual void	adjustClientSize();
    virtual void	maximizeFrame();
protected:
    IlvScrolledView*	_scView;
    IlvView*		_bufferView;
    IlBoolean		_scrolling;

    DeclareViewProperties();
}; // class IlvStApplicationBufferFrame

// --------------------------------------------------------------------------
class ILVSTAPPLICLASS IlvStApplicationBufferFrameBuilder
: public IlvStBufferFrameBuilder {
public:
    const char* getBufferType() const;
    IlvStBufferFrame* buildFrame(IlvStBuffer* buffer,
				 IlvView* parent,
				 const char* title,
				 const IlvRect& bbox,
				 IlBoolean visible);
}; // class IlvStApplicationBufferFrameBuilder

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTAPPLICLASS(st_appbuf)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Appbuf_H */
