// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/buffers.h
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
// Declaration of IlvStBuffers
// --------------------------------------------------------------------------
#ifndef __IlvSt_Buffers_H
#define __IlvSt_Buffers_H

// --------------------------------------------------------------------------
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif
#ifndef __IlvSt_Object_H
#include <ivstudio/object.h>
#endif

#ifndef __Ilv_Gadgets_Scombo_H
#include <ilviews/gadgets/scombo.h>
#endif

#ifndef __Ilv_Manager_Hook_H
#include <ilviews/manager/hook.h>
#endif

// --------------------------------------------------------------------------
class IlvContainer;

class IlvStBuffer;
class IlvStudio;
class IlvStPanelClass;
class IlvStError;
class IlvStBufferViewHandler;
class IlvStBufferFrameBuilder;

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDVAR(const char*) IlvNmAfterClosingBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmAfterReadingData;
extern ILVSTEXPORTEDVAR(const char*) IlvNmAfterSavingData;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeClosingBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeReadingData;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeSavingData;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBufferModified;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBufferRenamed;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBufferTypeChanged;
extern ILVSTEXPORTEDVAR(const char*) IlvNmCloseAllBuffers;
extern ILVSTEXPORTEDVAR(const char*) IlvNmCloseBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmFitToContents;
extern ILVSTEXPORTEDVAR(const char*) IlvNmGenerateStringData;
extern ILVSTEXPORTEDVAR(const char*) IlvNmInsertBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmNewBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmOpenBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmRefresh;
extern ILVSTEXPORTEDVAR(const char*) IlvNmResizePanel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmRevertBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSaveBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSaveBufferAs;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectBuffer;
extern ILVSTEXPORTEDVAR(const char*) IlvNmTestPanel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmBeforeDeletingTestPanel;

typedef IlvStBuffer* (*IlvStBufferConstructor)(IlvStudio* editor,
					       const char* name,
					       const char* filename);
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStZoomLevelViewHook : public IlvManagerViewHook
{
public: 
    IlvStZoomLevelViewHook(IlvStudio* e, IlvManager* m = 0, IlvView* v = 0);

    virtual void transformerChanged(const IlvTransformer* current,
                        const IlvTransformer* previous);
private:
    IlvStudio* _editor;
};


class ILVSTUDIOCLASS IlvStBuffers
{
public:
  IlvStBuffers(IlvStudio* editor);
  ~IlvStBuffers();
  // ____________________________________________________________
  IlvStBuffer* get(const char* name) const;
  IlvStBuffer* get(const IlvStPanelClass*) const;
  IlvStBuffer* fullPathGet(const char*) const;
  IlvStBuffer* getCurrent() const;
  void         setCurrent(IlvStBuffer* buf);
  void         reconnectHooks(IlvView* v);
  void         add(IlvStBuffer* buf, IlBoolean realize = IlTrue);
  void         remove(IlvStBuffer* buf = 0, IlAny caller = 0);
  void	 close(IlvStBuffer* buf, IlAny caller = 0);
  void	 closeAll(IlAny caller = 0);
  IlvStBuffer* operator[](IlUShort ndx) const
    { return (IlvStBuffer*)_array[ndx]; }
  IlUShort    count() const { return (IlUShort)_array.getLength(); }
  IlvStBuffer* make(const char* filename, const char* name);
  IlvStBuffer* makeDefault(const char* name = 0);
  IlvStBuffer* makeNew(const char* name = 0);
  void	 	testPanel(IlvContainer*);
  IlvContainer* getTestPanel() const { return _test; }
  void	 	killTestPanel();
  IlBoolean		isTesting() const { return _test ? IlTrue : IlFalse; }

  void registerType(const char* type, IlvStBufferConstructor fct);

  IlvStBufferConstructor getDefaultConstructor() const
    { return _defaultConstructor; }
  void	setDefaultConstructor(IlvStBufferConstructor func)
    { _defaultConstructor = func; }
  IlvStBufferConstructor getNewConstructor() const
    { return _newConstructor; }
  void	setNewConstructor(IlvStBufferConstructor func)
    { _newConstructor = func; }
  IlBoolean	hasModifiedBuffers() const;
  IlBoolean	confirmDiscardModifiedBuffers(const char* msg) const;
  IlBoolean	selectBuffer(IlvStPanelClass*);
  IlvStError*	selectOrOpen(const char* fullPath, IlAny caller = 0);
  IlvStBufferViewHandler*	getViewHandler() const { return _viewHandler; }
  void			setViewHandler(IlvStBufferViewHandler*);

private:
  IlvStudio*    		_editor;
  IlvArray  			_array;
  IlvStBufferViewHandler*	_viewHandler;
  IlvContainer* 		_test;
  IlvStHash			_constructors;
  IlvStBufferConstructor 	_defaultConstructor;
  IlvStBufferConstructor	_newConstructor;

public:
  void addFrameBuilder(IlvStBufferFrameBuilder*);
  IlvStBufferFrameBuilder* getFrameBuilder(const char*) const;
  IlvStBufferFrameBuilder* getDefaultFrameBuilder() const;
  void setDefaultFrameBuilder(IlvStBufferFrameBuilder*);

  const IlvStHash& 	getGadgets() const { return _gadgets; };
  IlvGadget*		getGadget(const char* key);
  void			addGadget(const char* key, IlvGadget* gadget);
  void			removeGadgets();
  void 			updateZoomLevel();

private:
  IlvArray			_frameBuilders;
  IlvStBufferFrameBuilder*	_defaultFrameBuilder;
  IlvStZoomLevelViewHook*	_zoomHook;
  IlvStHash              	_gadgets;
}; // class IlvStBuffers

#endif /* __IlvSt_Buffers_H */
