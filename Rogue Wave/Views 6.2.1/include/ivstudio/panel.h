// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/panel.h
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
// Declaration of editor's panel classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Panel_H
#define __IlvSt_Panel_H

#if !defined(__IlvSt_Pnlutil_H)
#  include <ivstudio/pnlutil.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#  include <ilviews/gadgets/stdialog.h>
#endif
#if !defined(__Ilv_Gadgets_Iprompt_H)
#  include <ilviews/gadgets/iprompt.h>
#endif
#if !defined(__IlvSt_Stprop_H)
#  include <ivstudio/stprop.h>
#endif
#if !defined(__IlvSt_Object_H)
#  include <ivstudio/object.h>
#endif
#if !defined(__IlvSt_Command_H)
#  include <ivstudio/command.h>
#endif
#if !defined(__IlvSt_Message_H)
#  include <ivstudio/message.h>
#endif
#if !defined(__IlvSt_Pandesc_H)
#  include <ivstudio/pandesc.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__IlvSt_Util_H)
#  include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#  include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Combo_H)
#  include <ilviews/gadgets/combo.h>
#endif
#if !defined(__Ilv_Gadgets_Panecont_H)
#  include <ilviews/gadgets/panecont.h>
#endif

class IlvStudio;
class IlvStPanelHandler;
class IlvStToolBar;

class IlvMenuBar;
class IlvAbstractMenu;
class IlvTextField;
class IlvComboBox;
class IlvPopupMenu;
class IlvMenuItem;
class IlvNotebook;
class IlvStringList;
class IlvPane;

IlvStPanelHandler* IlvStMakeEmptyPanel(IlvStudio*, const char* name);
typedef void (*IlvStPanelCallbackType)(IlvStPanelHandler*, IlAny arg);

class ILVSTUDIOCLASS IlvStPanelHandler
  : public IlvStPropertySet, public IlvStPanelUtil {
public:
  IlvStPanelHandler(IlvStudio*,
		    const char* name,
		    const char* fileordata,
		    const IlvRect& rect,
		    IlUInt properties = 0,
		    IlvStPanelHandler* tfor = 0);

  IlvStPanelHandler(IlvStudio*		editor,
		    const char*		name, 
		    IlvGadgetContainer*	cont = 0);
  virtual ~IlvStPanelHandler();

  IlvStudio* getEditor() const;

  static IlvStPanelHandler* Get(IlvContainer*);

public:
  // ____________________________________________________________
  IlvStudio& editor() const { return *_editor; }
  IlvStPanelDescriptor* getDescriptor() const { return _descriptor; }
  const char* getName() const { return IlvStPropertySet::getName(); }
  const char* getHelpFile() const;
  void setHelpFile(const char* fname);
  const char* getCommandName() const;
  void setCommandName(const char* coname)
    { _descriptor->setCommandName(coname); }
  // --- Container ---
  virtual IlBoolean		isPanable() const;
  virtual IlvGadgetContainer* createContainer(const IlvRect&);
  virtual IlvGadgetContainer* createContainer(IlvAbstractView* parent,
					      const IlvRect&);
  virtual void		setUpContainer(IlvGadgetContainer*);
  IlvPane*		getPane() const { return _pane; }
  void		setPane(IlvPane* pane);

  IlvGadgetContainer* getContainer() const { return _container; }

  IlvGadgetContainer& container() const;

  void 		setContainer(IlvGadgetContainer*);
  IlvGraphic* 	getObject(const char* name) const
    { return _container->getObject(name); }
  IlvTextField*	getTextField(const char* name) const
    { return (IlvTextField*)_container->getObject(name);}
  IlvToggle*		getToggle(const char* name) const
    { return (IlvToggle*)_container->getObject(name); }
  IlvStringList*	getStringList(const char* name) const
    { return (IlvStringList*)_container->getObject(name); }
  IlvComboBox*	getComboBox(const char* name) const
    { return (IlvComboBox*)_container->getObject(name); }
  virtual void 	setTitle(const char* title);
  void		setDocumentTitle(const char* docname,IlBoolean modified);
  IlvDisplay* 	getDisplay() { return _container->getDisplay(); }
  // --- Virtual ---

  virtual void connect();

  virtual void disconnect();

  virtual void hide();

  virtual void show();

  virtual void apply();

  virtual void doApply();

  virtual void cancel();

  virtual void reset();

  virtual void doReset();
  virtual void help();

  virtual IlBoolean resetBeforeShowing() const;
  // --- Callbcks ---
  void addApplyCallback(IlvStCallback* cback,IlUInt ndx = (IlUInt)-1)
    {_applyCallbacks.insert(ndx, cback); }
  void addResetCallback(IlvStCallback* cback,IlUInt ndx = (IlUInt)-1)
    {_resetCallbacks.insert(ndx, cback); }
  void removeApplyCallback(IlvStCallback* cback)
    { _applyCallbacks.remove(cback); }
  void removeResetCallback(IlvStCallback* cback)
    { _resetCallbacks.remove(cback); }
  IlvStError* callApplyCallbacks(IlvValue* arg = 0)
    { return callCallbacks(_applyCallbacks, arg); }
  IlvStError* callResetCallbacks(IlvValue* arg = 0)
    { return callCallbacks(_resetCallbacks, arg); }
  // ---
  IlBoolean isVisible() const { return _visible; }
  // Description
  virtual IlBoolean	applyMenuDescription(IlvStPropertySet*);
  virtual IlBoolean	applyMenuItemDescription(IlvStPropertySet*);
  virtual IlBoolean	applyToolBarDescription(IlvStPropertySet*);
  virtual IlBoolean	applyCommandDescription(IlvStPropertySet*);
  virtual IlBoolean	applyProperties(IlvStPanelDescriptor*);
  // --- menu ---
  virtual IlvAbstractMenu* getMenuBar() const;
  void subscribe(const char* msgName,IlvStPanelCallbackType cback);
  void setMenu(IlUShort pathCount,const char* const* path,IlvPopupMenu*);
  // --- ToolBars ---
  virtual void 	addToolBar(IlvGraphic*, IlvPosition, const char* = 0);
  void 		removeToolBar(IlvGraphic*);
  virtual void 	updateToolBars();
  virtual void	commandStateChanged(IlvStCommandDescriptor*);
  void		updateToolBars(IlvStCommandDescriptor*);
  IlvArray&		getTopToolBars()  { return _topToolBars;  }
  IlvArray&		getLeftToolBars() { return _leftToolBars; }
  // --- CommandGraphic ---
  IlBoolean  hasCommand() const { return _hasCommand; }
  // --- Utilities ---
  IlBoolean		isLocked() const { return _locked; }
  void		lock(IlBoolean val) { _locked = val; }
  void		resetOnMessage(const char* msgName);
  void		resetOnSelection();

  static IlvStPanelHandler* Get(const IlvGraphic*);

protected:
  void		doCommandStateChanged(IlvStCommandDescriptor*,
				      const IlvArray&);
  IlvStError*		callCallbacks(const IlvArray& cbacks, IlvValue*);
  IlvStPanelDescriptor* _descriptor;
  IlvArray 		_topToolBars;
  IlvArray		_leftToolBars;
  IlvArray		_applyCallbacks;
  IlvArray		_resetCallbacks;
  IlvStudio* 		_editor;
  IlvGadgetContainer* _container;
  IlvPane*		_pane;
  IlBoolean          _visible	ILVSTBF;
  IlBoolean		_hasCommand	ILVSTBF;
  IlBoolean		_locked		ILVSTBF;

private:
  void init();

  friend class IlvStudio;
}; // class IlvStPanelHandler

class ILVSTUDIOCLASS IlvStDialog : public IlvStPanelHandler 
{
public:
  IlvStDialog(IlvStudio* editor,
	      const char* name,
	      IlvDialog* dialog = 0);

  IlvStDialog(IlvStudio*,
	      const char* name,
	      const char* fileordata,
	      const IlvRect& rect,
	      IlUInt properties = 0,
	      IlvStPanelHandler* = 0);
  // ____________________________________________________________
  IlvDialog* getDialog() const { return (IlvDialog*)_container; }

  IlvDialog& dialog() const;
  virtual void apply();
  virtual void cancel();
}; // class IlvStDialog

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStToolTipHandler {
public:
    IlvStToolTipHandler(IlvStudio* editor);
    ~IlvStToolTipHandler();
    void	attach(IlvContainer*);
    void	showToolTip();
    void	hideToolTip();
    void	handlePointerMoved(IlvContainer*, IlvEvent&);
    void	tipDeleted() { _tipView = 0; }
protected:
    IlvStudio*		    _editor;
    IlvStCommandDescriptor* _lastCoDesc;
    IlvGraphic*		    _lastObj;
    IlvView*		    _tipView;
    IlvTimer*		    _timer;
}; // class ILVSTUDIOCLASS IlvStToolTipHandler

class ILVSTUDIOCLASS IlvStShowPanel : public IlvStCommand
{
public:
  IlvStShowPanel(IlvStPanelHandler* panel);

  // ____________________________________________________________
  virtual IlvStError* doIt(IlvStudio*, IlAny);
  virtual IlvStError* unDo(IlvStudio*);
  IlvStPanelHandler& panel() const { return *_panel; }
private:
  IlvStPanelHandler* _panel;
}; // IlvStShowPanel

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStHidePanel: public IlvStCommand
{
public:
    IlvStHidePanel(IlvStPanelHandler* panel)
    : _panel(panel) {}
    // ____________________________________________________________
    virtual IlvStError* doIt(IlvStudio*, IlAny);
    virtual IlvStError* unDo(IlvStudio*);
    IlvStPanelHandler& panel() const { return *_panel; }
private:
    IlvStPanelHandler* _panel;
}; // IlvStHidePanel

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDFUNC(void)
IlvStNoInputContext(IlvContainer*, const char* = 0);
#endif /* ! __IlvSt_Panel_H */
