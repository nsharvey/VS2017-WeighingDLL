// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/stbuffer.h
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
// Declaration of Studio Buffer base classe
// --------------------------------------------------------------------------
#ifndef __IlvSt_Stbuffer_H
#define __IlvSt_Stbuffer_H

#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__IlvSt_Document_H)
#include <ivstudio/document.h>
#endif
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#ifndef __Ilv_Gadmgr_Gadmgr_H
#include <ilviews/gadmgr/gadmgr.h>
#endif
#ifndef __IlvSt_Buffers_H
#include <ivstudio/buffers.h>
#endif

extern ILVSTEXPORTEDFUNC(char*)
IlvStSave(IlvManager* manager, IlBoolean restoreModified = IlFalse);

// --------------------------------------------------------------------------
class IlvStudio;
class IlvStCommand;
class IlvStPanelClass;
class IlvParser;
class IlvStMode;
class IlvStBufferFrameBuilder;
class IlvMarkingMenu;

class ILVSTUDIOCLASS IlvStBuffer : public IlvStDocument 
{
public:
  IlvStBuffer(IlvStudio* editor, const char* name, IlvManager* mgr = 0);

  virtual ~IlvStBuffer();
  // ____________________________________________________________
  virtual const char*	getDataFileExtension() const;

  IlvManager* 	getManager() const;

  IlvView* 		getView() const { return _view; }

  void newName(const char* name);

  IlvStError* 	save(const char* filename);
  virtual char*	save(IlBoolean restoreModified = IlFalse);
  void 		setDoubleBuffering(IlBoolean value);
  IlvGraphic* 	getInspectedObject() const   { return _inspected; }
  void 		inspect(IlvGraphic* obj);
  virtual IlBoolean 	isModified() const;
  virtual void 	setModified(IlBoolean);
  // ---
  virtual void 	setView(IlvView*);
  virtual void 	insert(const char* filename);
  virtual void 	select();
  virtual void 	unSelect();
  virtual void	enableEvents(IlBoolean = IlTrue);
  virtual IlvDim 	getWidth() const;
  virtual IlvDim 	getHeight() const;
  virtual IlBoolean	getIgnoringSize() const;
  virtual void	setIgnoringSize(IlBoolean);
  virtual IlBoolean	getIgnoringBackground() const;
  virtual void	setIgnoringBackground(IlBoolean);
  virtual IlvBitmap*	getBackgroundBitmap() const;
  virtual IlvStError*	deleteSelections();
  // --- commands
  virtual IlvStError* doSaveCommand(IlAny arg);
  virtual IlvStError* doSaveAsCommand(IlAny arg);
  virtual IlvStError* doRevertCommand(IlAny arg);
  virtual IlvStError* doCloseCommand(IlAny arg);
  virtual IlvStError* doTestCommand(IlAny arg);
  virtual IlvStError* doInspectCommand(IlAny arg);
  virtual IlvStError* doGenerateCommand(IlAny arg);
  // -- Code generation
  virtual IlvContainer* makeTestPanel();

  virtual void	setUpPanelClass(IlvStPanelClass* pl) const;
  virtual IlBoolean	isAnApplicationBuffer() const;
  virtual IlBoolean  isA2DBuffer() const;
  virtual IlBoolean	isAGadgetBuffer() const;
  virtual IlBoolean	isAGrapherBuffer() const;
  virtual IlBoolean	canBePanelClass() const;
  virtual void	codeHeaderFile(ILVSTDPREF ostream&,
			       IlvStPanelClass*) const;
  virtual void	codeDeclarePublic(ILVSTDPREF ostream&,
				  IlvStPanelClass*) const;
  virtual void	codeDeclareProtected(ILVSTDPREF ostream&,
				     IlvStPanelClass*) const;
  virtual void	codeInitializeFunction(ILVSTDPREF ostream&,
				       IlvStPanelClass*) const;
  virtual void	codeWriteFunctions(ILVSTDPREF ostream&,
				   IlvStPanelClass*) const;
  virtual const char* getType () const;
  virtual const char* getTypeLabel() const;
  virtual IlvParser*	getParser() const;
  //
  virtual IlvStError* close(IlAny caller = 0, IlAny arg = 0);
  virtual IlBoolean	accept(IlvGraphic*);
  virtual const char* const* getToolBarCommands(IlUShort& count) const;
  virtual const char*	    getMenuTitle() const;
  virtual const IlvArray& getMenuCommands();
  IlvStMode*	getLastMode() const { return _lastMode; }
  void	setLastMode(IlvStMode* mode) { _lastMode = mode; }
  IlvGraphic*		getObjectAtGlobalLocation(const IlvPoint& point);

protected:
  IlvManager*         _manager;
  IlvView*            _view;
  IlvGraphic*         _inspected;
  IlvArray		_menuCmds;
  IlvStMode*		_lastMode;
  IlvMarkingMenu*	_contextualMenu;
  IlvManagerViewInteractor* _nullInter;

public:
  static void			SetInspectFunction(IlvStCommandFunction);
  static IlvStCommandFunction GetInspectFunction();
  static void			SetGenerateFunction(IlvStCommandFunction);
  static IlvStCommandFunction GetGenerateFunction();

protected:
  static IlvStCommandFunction _InspectFunction;
  static IlvStCommandFunction _GenerateFunction;

}; // class IlvStBuffer

// --------------------------------------------------------------------------
typedef void (*IlvStWaitCallback)(IlvStudio*, IlvEvent& event, IlAny arg);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStBufferViewHandler {
public:
    IlvStBufferViewHandler(IlvStudio* editor);
    virtual ~IlvStBufferViewHandler();
    virtual void	addBuffer(IlvStBuffer*)	   = 0;
    virtual void	realizeBuffer(IlvStBuffer*)= 0;
    virtual void	removeBuffer(IlvStBuffer*) = 0;
    virtual void	setBuffer(IlvStBuffer*)    = 0;
    virtual void	unSetBuffer(IlvStBuffer*)  = 0;
    virtual IlvView*	getView() const = 0;
    virtual void	grabEvent(IlvEventType etype,
				  IlvStWaitCallback cback,
				  IlAny arg,
				  IlvGraphic* ghost,
				  IlvCursor* cursor);
    virtual void	handleGrabbedEvent(IlvEvent&);
    virtual void	stopGrabbingEvent(IlvEvent&);
    virtual void	doGrabbedEventAction(IlvEvent& event);
    virtual void	drawGhost(const IlvPoint& pos, IlvGraphic* ghost);
    IlvStudio*		getEditor() const { return _editor; }
protected:
    IlvStudio*		_editor;
    IlvEventType	_waitEventType;
    IlvStWaitCallback	_waitCallback;
    IlAny		_waitArg;
    IlvGraphic*		_waitGhost;
    IlvCursor*		_waitCursor;
    IlvPoint		_waitPosition;
}; // class IlvStBufferViewHandler

// --------------------------------------------------------------------------
#endif /* __IlvSt_Stbuffer_H */
