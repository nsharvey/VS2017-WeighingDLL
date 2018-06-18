// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/command.h
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
// Declaration of the command classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Command_H)
#define __Ilv_Appframe_Command_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class ILVDSPEXPORTED IlvBitmap;
typedef void (*IlvDvCommandCallback)(IlAny, IlAny);
class ILVDVCLASS IlvDvCommand;
class ILVDVCLASS IlvDvRegistryKey;
class ILVDVCLASS IlvDvApplication;
class ILVGDTEXPORTED IlvGadgetItem;
class ILVVWSEXPORTED IlvGraphic;
class ILVDVCLASS IlvDvNodeValue;

// --------------------------------------------------------------------------
// IlvDvAction class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvAction
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvAction(IlvDvApplication* app,
		const IlSymbol*   name,
		const char*       menuLabel = 0,
		const char*       bitmapPath = 0);
    IlvDvAction(IlvDvNodeValue*);
    virtual ~IlvDvAction();

    // ----------------------------------------------------------------------
    // Accessors
    const IlSymbol*	getName() const;
    void		setApplication(IlvDvApplication* app);

    virtual const char*	getMenuLabel() const;
    virtual void	setMenuLabel(const char* label);

    virtual const char*	getBitmapPath(const IlSymbol* state = 0,
				      IlBoolean bigIcons = IlFalse) const;
    virtual void	setBitmapPath(const char* bitmapPath,
				      IlBoolean bigIcons = IlFalse,
				      const IlSymbol* state = 0);

    virtual const char*	getTooltip() const;
    virtual void	setTooltip(const char* tooltip);

    virtual const char*	getDescription() const;
    virtual void	setDescription(const char* desc);

    virtual void	getAccelerators(IlvArray&) const;
    virtual void	addAccelerator(const char*);
    virtual IlBoolean	removeAccelerator(const char*);

    virtual void	getCategories(IlvArray&) const;
    virtual void	addCategory(const char*);
    virtual IlBoolean	removeCategory(const char*);

protected:
    IlvDvNodeValue*	_node;
    IlvDvApplication*	_app;

    static const IlSymbol*
	    ConvertGadgetItemStateToFieldName(const IlSymbol* state,
					      IlBoolean bigIcons = IlFalse);

    friend class IlvDvApplication;
};

// --------------------------------------------------------------------------
// IlvDvActionDescriptor class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvActionDescriptor : public IlvDvSerializable
{
    IlvDvDeclareClassInfo();

public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    virtual ~IlvDvActionDescriptor() {}

    // ----------------------------------------------------------------------
    // Basic properties

    virtual const char*	getLabel() const = 0;

    virtual void        setLabel(const char* label) = 0;

    virtual IlvBitmap*	getBitmap(const IlSymbol* state = 0) const = 0;

    virtual void	setBitmap(IlvBitmap*      bitmap,
				  const IlSymbol* state = 0) = 0;

    enum State {
	Active,
	Unactive,
	Unsensitive,
	None
    };

    virtual State	getState() const = 0;

    virtual void	setState(State state) = 0;

    inline void		setValid(IlBoolean valid)
			{
			    setState(valid? Active : Unsensitive);
			}

    virtual IlBoolean	isChecked() const = 0;

    virtual void	setChecked(IlBoolean check = IlTrue) = 0;

    virtual
    IlvDvActionDescriptor* find(IlvGadgetItem*) = 0;
};

// --------------------------------------------------------------------------
// IlvDvActionGadgetItem class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvActionGadgetItem : public IlvDvActionDescriptor
{
    IlvDvDeclareDynCreate();

public:
    IlvDvActionGadgetItem(IlvGadgetItem* = 0);
    ~IlvDvActionGadgetItem();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual const char*	getLabel() const;
    virtual void	setLabel(const char*);
    virtual IlvBitmap*	getBitmap(const IlSymbol*) const;
    virtual void	setBitmap(IlvBitmap*, const IlSymbol* = 0);
    virtual State	getState() const;
    virtual void	setState(State state);
    virtual IlBoolean	isChecked() const;
    virtual void	setChecked(IlBoolean = IlTrue);

    virtual
    IlvDvActionDescriptor* find(IlvGadgetItem* gadgetItem);
    // Get the gadget item that is used
    inline
    IlvGadgetItem*	getGadgetItem() const
			{
			    return _gadgetItem;
			}
    inline void		setGadgetItem(IlvGadgetItem* item)
			{
			    _gadgetItem = item;
			}

    static IlBoolean	_UseOldMenuCheck;
    static const char*	_CheckedBitmapPath;
    static const char*	_CheckedSelectedBitmapPath;
    static const char*	_UnCheckedBitmapPath;
    static const char*	_UnCheckedSelectedBitmapPath;

protected:
    IlvGadgetItem*	_gadgetItem;
};

// --------------------------------------------------------------------------
// IlvDvActionDescriptorArray class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvActionDescriptorArray : public IlvDvActionDescriptor
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvActionDescriptorArray();
    ~IlvDvActionDescriptorArray();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual const char*	getLabel() const;
    virtual void	setLabel(const char*);
    virtual IlvBitmap*	getBitmap(const IlSymbol*) const;
    virtual void	setBitmap(IlvBitmap*, const IlSymbol* = 0);
    virtual State	getState() const;
    virtual void	setState(State state);
    virtual IlBoolean	isChecked() const;
    virtual void	setChecked(IlBoolean = IlTrue);

    virtual
    IlvDvActionDescriptor*	find(IlvGadgetItem* gadgetItem);
    IlvDvActionDescriptor*	getActionDescriptor(IlUInt) const;
    void		insertActionDescriptor(IlvDvActionDescriptor* desc,
					       IlUInt index = (IlUInt)-1);
    IlBoolean		deleteActionDescriptor(IlvGadgetItem*);
    inline IlUInt	getCardinal() const { return _cmdUIs.getLength(); }

protected:
    IlvArray		_cmdUIs;
};

// --------------------------------------------------------------------------
// IlvDvActionManager class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif

class ILVDVCLASS IlvDvActionManager
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvActionManager();
    virtual ~IlvDvActionManager();

    // ----------------------------------------------------------------------
    // Basic properties
    virtual IlvDvActionDescriptor* getActionDescriptor(const IlSymbol*) const;
    virtual IlvDvActionDescriptor* getActionDescriptor(const char*) const;
    virtual void	addActionDescriptor(const IlSymbol* actionName,
					    IlvDvActionDescriptor* desc);
    virtual void	removeActionDescriptor(const IlSymbol* actionName);
    virtual void	removeActionDescriptors();
    virtual void	refreshActions(IlvDvApplication* app);
    virtual IlBoolean	refreshAction(const IlSymbol*, IlvDvApplication* app);
    virtual void	refreshActionsByCategory(const IlSymbol*,
						 IlvDvApplication* app);
    IlBoolean		detachFromActionDescriptor(IlvGadgetItem* gadgetItem,
						   IlBoolean sub = IlTrue);
    void		initializeActionDescriptor(IlvGadgetItem* gadgetItem,
						   const IlvDvApplication* app,
						   IlBoolean sub = IlTrue);
    virtual IlBoolean	isActionChecked(const char* actionName) const;
    virtual IlBoolean	isActionChecked(const IlSymbol* actionName) const;
    virtual void	setActionChecked(const char* actionName,
					 IlBoolean checked = IlTrue);
    virtual void	setActionChecked(const IlSymbol* actionName,
					 IlBoolean checked = IlTrue);
    virtual IlBoolean	isActionValid(const char*) const;
    virtual IlBoolean	isActionValid(const IlSymbol*) const;
    virtual void	setActionValid(const char* actionName,
				       IlBoolean valid = IlTrue);
    virtual void	setActionValid(const IlSymbol* actionName,
				       IlBoolean valid = IlTrue);

    void		addGraphicGadgetItem(IlvGadgetItem*,
					     const IlvDvApplication*);

    // ----------------------------------------------------------------------
    // Adding / removing actions
    void		addAction(IlvDvAction*);
    IlBoolean		removeAction(IlvDvAction*,
				     IlBoolean deleteIt = IlTrue);

    static
    const IlSymbol*	GetActionName(const IlvGadgetItem*);
    static void		SetActionName(IlvGadgetItem*, const IlSymbol*);
    static IlSymbol*	_ActionNameSymbol;
    static IlSymbol*	_ActionDescriptorProperty;

protected:
    IlvArray		_actions;
    IlvHashTable	_cmdUIs;
    IlvDvActionDescriptorArray*
		getActionDescriptorArray(const IlSymbol* actionName,
					 const IlvHashTable* hash = 0) const;
    IlvDvActionDescriptorArray*
		ensureActionDescriptorArray(const IlSymbol* actionName,
					    IlvHashTable* hash);

    IlvHashTable	_graphicGadgetItems;
};

// --------------------------------------------------------------------------
// IlvDvCommand class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvCommand : public IlvDvSerializable
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    IlvDvCommand(const char* name = 0);

    IlvDvCommand(const IlvDvCommand& source);

    virtual ~IlvDvCommand();

    // ----------------------------------------------------------------------
    virtual
    IlvDvCommand*	copy() const = 0;

    virtual void	doIt() = 0;

    virtual void	undo() = 0;

    virtual
    IlBoolean		canUndo() const;

    virtual
    IlBoolean		bringChanges() const;
    // ----------------------------------------------------------------------
    // Basic properties
    inline
    const char*		getName() const { return (_name ? _name->name() : 0); }
    inline
    const IlSymbol*	getNameSymbol() const { return _name; }
    virtual
    const char*		getToolTip() const;

protected:
    const IlSymbol*	_name;
};

// --------------------------------------------------------------------------
// IlvDvCommandArray class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvCommandArray : public IlvArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvCommandArray(IlUInt initialLength = 8) : IlvArray(initialLength) {}
    ~IlvDvCommandArray() { emptyCommands(); }

    // ----------------------------------------------------------------------
    // Main operations
    void		emptyCommands();
    IlvDvCommand*	getCommand(IlUInt) const;
    void		addCommand(IlvDvCommand* cmd);
    IlvDvCommand*	popCommand();
    IlvDvCommand**	getCommands(IlUInt&) const;
};

// --------------------------------------------------------------------------
// IlvDvMacroCommand class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvMacroCommand : public IlvDvCommand
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvMacroCommand(const char* name = 0);
    virtual ~IlvDvMacroCommand();

    // ----------------------------------------------------------------------
    // Main operations
    virtual void	doIt();
    virtual void	undo();
    virtual IlBoolean	canUndo() const;
    virtual IlBoolean	bringChanges() const;

    // ----------------------------------------------------------------------
    // Basic properties
    inline void		addCommand(IlvDvCommand* cmd)
			{
			    _commands.addCommand(cmd);
			}

protected:
    IlvDvCommandArray	_commands;
};

// --------------------------------------------------------------------------
// IlvDvCommandHistory class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvCommandHistory : public IlvDvSerializable
{
    IlvDvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvCommandHistory();
    ~IlvDvCommandHistory();

    // ----------------------------------------------------------------------
    // Main operations
    virtual void	doCmd(IlvDvCommand*);
    void		addCmd(IlvDvCommand*, IlBoolean isDone = IlTrue);
    virtual IlBoolean	undoCmd();
    virtual IlBoolean	canUndo() const;
    virtual IlBoolean	redo();
    virtual IlBoolean	canRedo() const;
    virtual IlBoolean	repeat();
    virtual IlBoolean	canRepeat() const;

    // ----------------------------------------------------------------------
    // Basic properties
    IlvDvCommand**	getDoneCommands(IlUInt&) const;
    IlvDvCommand**	getUndoneCommands(IlUInt&) const;
    IlvDvCommand*	findCommand(const IlSymbol*, IlBoolean& isDone) const;
    IlBoolean		isLastDone(const IlvDvCommand*) const;
    IlBoolean		isLastUndone(const IlvDvCommand*) const;
    IlvDvCommand*	getLastDoneCommand() const;
    IlvDvCommand*	getLastUndoneCommand() const;
    void		removeCommand(IlvDvCommand*,
				      IlBoolean isDone,
				      IlBoolean bDelete = IlTrue);
    IlBoolean		isModified() const;
    void		resetModified();

protected:
    IlvDvCommandArray	_doneCmds;
    IlvDvCommandArray	_undoneCmds;
    IlUInt		_unmodifiedLevel;

    IlvDvCommand*	getCommand(IlUInt iCmd, const IlvArray& cmds) const;
};

// --------------------------------------------------------------------------
// IlvDvActionProcessor class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvActionProcessor : public IlvDvInterface
{
public:
    // ----------------------------------------------------------------------
    IlvDvActionProcessor(const IlSymbol* name = 0);

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	execute() = 0;
    virtual IlBoolean	setActionDescriptor(IlvDvActionDescriptor*) const;
    virtual IlBoolean	refreshAction(const IlSymbol* actionName,
				      IlvDvActionDescriptor*) const;

    IlvDvDeclareInterface();
    // ----------------------------------------------------------------------
    // Basic properties
    inline
    const IlSymbol*	getCommandName() const { return _cmdName; }
    inline void		setCommandName(const IlSymbol* name)
			{
			    _cmdName = name;
			}

protected:
    const IlSymbol*	_cmdName;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(command);
// --------------------------------------------------------------------------

#endif /* !__Ilv_Appframe_Command_H */
