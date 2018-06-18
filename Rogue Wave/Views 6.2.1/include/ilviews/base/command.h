// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/command.h
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
// Definition of the IlvCommand and IlvCommandHistory classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Command_H
#define __Ilv_Base_Command_H

#if !defined(__Ilv_Base_Action_H)
#include <ilviews/base/action.h>
#endif

// --------------------------------------------------------------------------
// IlvCommand class
// --------------------------------------------------------------------------
enum IlvUndoabilityReason {
    undoable, // everything is ok
    unApplicable, // undo() in this context doesn't mean anything
    committing, // the command has had to commit the changes made and 
     		// therefore can't revert
    outOfMemory, // or other errors that prevent reverting to the
		 // previous state.
    notImplemented // should not happen, but sometimes needed
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvCommandFlags
{
public:
    IlvCommandFlags(IlvUndoabilityReason r, IlBoolean p)
    : undoability(r),
      isPseudoCommand(p),
      padding(0) {}
    IlvUndoabilityReason undoability:     3;
    IlBoolean		 isPseudoCommand: IlvBoolMinLength;
    IlUChar		 padding:	  3;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvCommand : public IlvAction
{
    IlvActionDeclareMembers();
public:
    IlvCommand (IlvActionHistory*    h  = 0,
		IlvUndoabilityReason u  = notImplemented,
		IlBoolean            ps = IlFalse,
		IlBoolean            r  = IlTrue,
		IlBoolean            p  = IlFalse)
    : IlvAction(h, r, p),
      _cflags(u, ps)
    {
	_flags.isCommand = IlTrue;
    }
    IlvCommand(const IlvCommand& c)
    : IlvAction(c),
      _cflags(c._cflags) {}
    ~IlvCommand();
    // ----------------------------------------------------------------------
    // Main operations
    virtual void	undo();		// external interface
    virtual void	undoIt();	// what the user implements, together
					// with executeIt()
    virtual void	redo();		// calls execute() by default.
    // ----------------------------------------------------------------------
    // Basic properties
    inline IlvUndoabilityReason	isUndoable() const
				{
				    return (IlvUndoabilityReason)
					_cflags.undoability;
				}
    inline IlBoolean	isPseudoCommand() const
			{
			    return _cflags.isPseudoCommand;
			}

public:
    // should be protected, yet subsubclasses may need to access them
    IlvCommandFlags	_cflags;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED
IlDeclareAndImplementArrayOfPointerTo(IlvCommand, IlvCommandArray);

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvMacroCommand : public IlvCommand
{
    IlvActionDeclareMembers();
    IlvRepeatableActionDeclareMembers(IlvMacroCommand);
    IlvPersistentActionDeclareMembers();
public:
    IlvMacroCommand(IlvActionHistory* h = 0, const IlString& name = "&macro");
    ~IlvMacroCommand();
    // ____________________________________________________________
    void		add(IlvCommand* c);
    // internal undo
    void		undoInner();
    void		redoInner();
    IlBoolean		canUndo() const;
    IlBoolean		canRedo() const;
    inline IlUInt	getLength() const { return _commands.getLength(); }
    inline IlvCommand*	operator[](IlUInt i) const { return _commands[i]; }
    void		remove(IlUInt i);
    void		close();
    // main functions
    void		executeIt();
    void		undoIt();
    IlString		userName() const;
    inline void		setName(const IlString& n) { _name=n; }

protected:
    virtual void	updateFlags(IlvCommand*);
    virtual void	resetFlags();
    IlvCommandArray	_commands;
    IlvCommandArray	_undone;
    IlString		_name;
};

// --------------------------------------------------------------------------
#define IlvDefaultMaxCommand 64
class ILVVWSEXPORTED IlvCommandHistory : public IlvActionHistory
{
public:
    IlvCommandHistory(IlUInt n = IlvDefaultMaxCommand);
    ~IlvCommandHistory();
    // ____________________________________________________________
    // Main operations
    void		add(IlvAction* c);
    virtual void	undo(IlUInt n = 1);
    virtual IlBoolean	canUndo(IlUInt n = 1) const;
    virtual void	redo(IlUInt n = 1);
    virtual IlBoolean	canRedo(IlUInt n = 1) const;
    // Basic properties
    inline IlvCommand*	lastUndoneCommand()
			{
			    return (_unDoneCommands.getLength() > 0)
				?_unDoneCommands[_unDoneCommands.getLength()-1]
				: 0;
			}
    // Macro-related functions
    void		openMacro(const IlString& name);
    inline void		setMacroName(const IlString& name)
			{
			    if (_currentChunk)
				_currentChunk->setName(name);
			    IlvActionMessage m (othermsg, 0);
			    notify(&m);
			}
    inline IlBoolean	isMacroRecording() const
			{
			    return (_currentChunk != 0);
			}
    void		closeMacro();

protected:
    IlvCommandArray	_unDoneCommands;
    IlvMacroCommand*	_currentChunk;
    IlInt		_chunkLevel;
};

IlvDerivedPointerClass(IlvpCommandHistory,
		       IlvpActionHistory,
		       IlvCommandHistory,
		       ILVVWSEXPORTED);

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvChangeValueCommand : public IlvCommand
{
    IlvActionDeclareMembers();
    IlvRepeatableActionDeclareMembers(IlvChangeValueCommand);
    IlvPersistentActionDeclareMembers();
public:
    IlvChangeValueCommand(IlvActionHistory*  h  = 0,
			  IlUInt             n  = 0,
			  const IlvValue*    af = 0,
			  IlvValueInterface* o  = 0,
			  const IlvValue*    bf = 0);
    ~IlvChangeValueCommand();
    // ____________________________________________________________
    virtual void		snapshot(IlvValueInterface* o,
					 const IlSymbol*    s,
					 IlBoolean          before = IlTrue);
    virtual void		executeIt();
    virtual void		undoIt();
    IlString			userName() const;
    inline IlvValueInterface*	getObject() const { return _object; }
    inline const IlvValue&	getValue(IlBoolean b, IlUInt i) const
				{
				    return b ? _before[i] : _after[i];
				}

protected:
    IlvValueInterface*		_object;
    IlUInt			_count;
    IlvValue*			_before;
    IlvValue*			_after;
};

// --------------------------------------------------------------------------
// observer to handle the modified flag of commands.
class ILVVWSEXPORTED IlvModifiedFlagObserver : public IlvObserver
{
public:
    IlvModifiedFlagObserver(IlvCommandHistory* h)
    : IlvObserver(),
      _changed(IlFalse),
      _cantReset(IlFalse),
      _initialCmd(0),
      _history(h)
	{
	    if (h) {
		attach(h);
		_initialCmd=h->getLast();
	    }
	}
    ~IlvModifiedFlagObserver();
    // ____________________________________________________________
    void		update(IlvObservable*, IlAny);
    virtual void	setModified(IlBoolean);
    inline IlBoolean	getModifiedFlag() const { return _changed; }
    // this last method should be implemented in derived classes to
    // notify whatever piece of the UI needs to reflect the
    // state of the document attached to the command history.
    virtual void	flagChanged(IlBoolean b);

protected:
    IlBoolean		_changed;
    IlBoolean		_cantReset;
    IlvAction*		_initialCmd;
    IlvCommandHistory*	_history;
};

#endif /* !__Ilv_Base_Command_H */
