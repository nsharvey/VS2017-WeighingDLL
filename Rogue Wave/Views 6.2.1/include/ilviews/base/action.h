// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/action.h
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
// Definition of the IlvAction and IlvActionHistory classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Action_H
#define __Ilv_Base_Action_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Memory_H)
#  include <ilviews/base/memory.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_String_H)
#  include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Base_Smartptr_H)
#  include <ilviews/base/smartptr.h>
#endif
#if !defined(__Ilv_Base_Observer_H)
#  include <ilviews/base/observer.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif

// The classes \c IlvManager and \c IlvContainer
// are predeclared for convenience, but they do not need to be linked
// to use the action history.

class IlvManager;
class IlvContainer;
class IlvActionHistory;
class IlvDisplay;
class IlvValueInterface;

// ------------------------ Action flags, used in IlvAction -----------------
#define IlvBoolMinLength 2

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvActionFlags
{
public:
    IlvActionFlags(IlBoolean d, IlBoolean c, IlBoolean r, IlBoolean p)
    : isDone(d),
      isCommand(c),
      isRepeatable(r),
      isPersistent(p),
      implicitTarget(IlFalse),
      padding(0),
      error(0) {}
    IlBoolean isDone		: IlvBoolMinLength;
    IlBoolean isCommand		: IlvBoolMinLength;
    IlBoolean isRepeatable	: IlvBoolMinLength;
    IlBoolean isPersistent	: IlvBoolMinLength;

    IlBoolean implicitTarget	: IlvBoolMinLength;
    IlUChar   padding		: IlvBoolMinLength*3;
    IlUShort			error;
};

// --------------------------------------------------------------------------
// IlvAction class
// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvAction
{
public:
    IlvAction(IlvActionHistory* history = 0,
	      IlBoolean         repeatable = IlTrue,
	      IlBoolean         persistent = IlFalse)
    : _context(history),
      _flags(IlFalse, IlFalse, repeatable, persistent)
    {}
    // for repeatability
    IlvAction(const IlvAction& action)
    : _context(action._context),
	_flags(action._flags)
    {
	setDone(IlFalse);
    }
    virtual ~IlvAction();
    // ____________________________________________________________
    virtual IlvAction*	duplicate() const;
    virtual void	execute(); // Called to perform the action
    virtual void	executeIt() = 0; // what the user implements
    // properties
    virtual IlString	userName() const;
    virtual IlString	errorMessage(IlUInt& severity) const;
    inline IlBoolean	isCommand() const { return _flags.isCommand; }
    inline IlBoolean	isRepeatable() const { return _flags.isRepeatable; }
    inline IlBoolean	isPersistent() const { return _flags.isPersistent; }
    inline IlBoolean	isDone() const { return _flags.isDone; }
    inline void		setDone(IlBoolean d = IlTrue) { _flags.isDone = d; }
    inline
    IlvActionHistory*	getContext() const { return _context; }
    virtual void	setContext(IlvActionHistory* history);

    // for Serialization/macro recording
    virtual void	write(ILVSTDPREF ostream&) const;
    virtual void	load(ILVSTDPREF istream&);
    static IlvAction*	read(ILVSTDPREF istream&, IlvActionHistory* h = 0);
    // for UI customizability
    static IlvAction*	instantiate(const char* name,
				    IlvActionHistory* h = 0);
protected:
    IlvActionHistory*	_context;

public:
    // because sub sub classes may need to access the flags, we need to
    // declare the _flags field as public.
    IlvActionFlags	_flags;

    IlvDeclarePropRootClassInfo();
};

// --------------------------------------------------------------------------
inline ILVSTDPREF ostream&
operator<<(ILVSTDPREF ostream& os, const IlvAction& a)
{
    a.write(os);
    return os;
}

// ---------------- action class info is the metaclass for all actions ------
class ILVVWSEXPORTED IlvActionClassInfo
: public IlvPropClassInfo, public IlvObservable
{
public:
    ~IlvActionClassInfo();
    // ____________________________________________________________
    IlvAction* (*_creator)(IlvActionHistory*);

    static
    IlvActionClassInfo* Create(const char*,
			       IlvClassInfo**,
			       IlvAction* (*)(IlvActionHistory*) = 0);
protected:
    IlvActionClassInfo(const char* className,
		       IlvClassInfo** superClass,
		       IlvAction* (*c)(IlvActionHistory*) = 0)
    : IlvPropClassInfo(className, superClass),
      IlvObservable(),
      _creator(c)
    {}
};

// ---------------- macros to define new action classes ---------------------
#define IlvActionDeclareMembers() 			\
public: IlvDeclarePropClassInfo();			\
static IlvAction* createInstance(IlvActionHistory* = 0)

#define IlvRepeatableActionDeclareMembers(classname) 			\
public:									\
inline IlvAction* duplicate() const { return new classname(*this); }	\
   classname(const classname&)

#define IlvPersistentActionDeclareMembers()		\
public: void write(ILVSTDPREF ostream&) const;		\
	void load(ILVSTDPREF istream&)

#define IlvDefineActionClass(classname, superclass) 		\
IlvAction* classname::createInstance(IlvActionHistory* h)	\
	{ return new classname (h); }				\
IlvClassInfo* classname::getClassInfo() const { 		\
    if (!_classinfo) 						\
	_classinfo = IlvActionClassInfo::Create(#classname,	\
			superclass::ClassPtr(), 		\
			&classname::createInstance);		\
    return _classinfo; }					\
IlvClassInfo* classname::_classinfo

#define IlvDefineAbstractActionClass(classname, superclass) 	\
IlvAction* classname::createInstance(IlvActionHistory*) {	\
    return 0;							\
}								\
IlvClassInfo* classname::getClassInfo() const { 		\
    if (!_classinfo) 						\
	_classinfo=IlvActionClassInfo::Create(#classname,	\
			superclass::ClassPtr(), 		\
			&classname::createInstance);		\
	return _classinfo; }					\
IlvClassInfo* classname::_classinfo

// ------------ Ancilliary classes of the Action History --------------------
class ILVVWSEXPORTED
IlDeclareAndImplementArrayOfPointerTo(IlvAction, IlvActionArray);

// for notification, we use our own message structure
enum IlvActionMessageType {
    addmsg,
    destroymsg,
    purgemsg,
    repeatmsg,
    undomsg,
    redomsg,
    othermsg
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvActionMessage
{
public:
    IlvActionMessage(IlvActionMessageType m, IlvAction* a)
    : _message(m),
      _action(a) {}
    IlvActionMessageType	_message;
    IlvAction*			_action;
};

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvActionSelectionHandler
{
public:
    IlvActionSelectionHandler()
    : _result() {}
    virtual ~IlvActionSelectionHandler();
    // ____________________________________________________________

    // used by commands without arguments to get the current selection
    virtual IlvValueInterface* const*	getSelection(IlUInt& count,
						     IlvActionHistory* h);

    // used by commands to gather their result
    inline void		setResult(IlUInt n, const IlvValueInterface** result)
			{
			    _result.erase();
			    _result.append((IlAny*)result, n);
			}

    inline void		removeFromResult(const IlvValueInterface* result)
			{
			    _result.remove((IlAny)result);
			}
    inline void		addToResult(IlUInt c, const IlvValueInterface** r)
			{
			    _result.append((IlAny*)r, c);
			}

    // to set the command result once a chunk of actions has been executed
    virtual void	reset();
    virtual void	commit();
    IlArray		_result;

    // to handle errors
    virtual void	handleError(IlvAction* action);
    virtual IlvDisplay* getDisplay();
};

// --------------- IlvActionHistory -----------------------------------------
class ILVVWSEXPORTED IlvActionHistory
: public IlvObservable {
public:
    IlvActionHistory(IlUInt max = 8);
    virtual ~IlvActionHistory();
    // ____________________________________________________________
    // main functions
    virtual void	add(IlvAction* action);
    inline IlUInt	getLength() const { return _actions.getLength(); }

    inline IlvAction*	getAction (IlUInt i) const
			{
			    return ((i < getLength()) && (getLength() > 0))
				? _actions[getLength()-i-1]
				: 0;
			}
    inline IlvAction*	getLast() const { return getAction(0); }
    // to handle repeat
    virtual void	repeatLast();
    // Unsafe, use only if you're sure all your actions have been
    // implemented in a way that allows arbitrary repetition of sequences.
    virtual void	repeatSequence(IlUInt from, IlUInt to);
    virtual IlvAction*	canRepeat();
    // for smart repeat handling
    void		addProperty(const IlSymbol* key, IlAny value);
    IlBoolean		removeProperty(const IlSymbol* key);
    IlBoolean		replaceProperty(const IlSymbol* key, IlAny value);
    IlAny		getProperty(const IlSymbol* key) const;
    IlBoolean		hasProperty(const IlSymbol* key) const;
    // to set limits to the history...   
    virtual void	setMaxLength(IlUInt maxLength);
    inline IlUInt	getMaxLength() const { return _maxLength; }
    // For internal use. Use purge for external use.
    virtual void	remove(IlvAction*);
    virtual void	purge(IlUInt n = (IlUInt)-1);
    // input/output for macro recording/playing
    virtual void	write(ILVSTDPREF ostream&) const;
    virtual IlUInt	read(ILVSTDPREF istream&, IlUInt = (IlUInt)-1);
    // Handle generic commands
    IlvValueInterface* const*	getCurrentSelection(IlUInt& c)
	{
	    if (_selectionHandler) {
		return _selectionHandler->getSelection(c, this);
	    } else {
		c = 0;
		return 0;
	    }
	}
    inline void	      setSelectionHandler(IlvActionSelectionHandler* handler)
	{
	    _selectionHandler = handler;
	}
    inline IlvActionSelectionHandler*	getSelectionHandler() const
	{
	    return _selectionHandler;
	}
    inline IlBoolean	recordValueChanges() const
	{
	    return _recordValueChanges;
	}
    inline void		setRecordValueChanges(IlBoolean b)
	{
	    _recordValueChanges = b;
	}

    // convenience functions for Views
    virtual IlvManager*	getManager();
    virtual void	setManager(IlvManager*);
    virtual
    IlvContainer*	getContainer();
    virtual void	setContainer(IlvContainer*);

protected:
    IlvActionArray	_actions;
    IlAList		_properties;
    IlUInt		_maxLength;
    IlBoolean		_recordValueChanges;
    IlvActionSelectionHandler* _selectionHandler;
};

IlvPointerClass(IlvpActionHistory, IlvActionHistory, ILVVWSEXPORTED)

// --------------------------------------------------------------------------
inline ILVSTDPREF ostream&
operator<<(ILVSTDPREF ostream& os, const IlvActionHistory& h)
{
    h.write(os);
    return os;
}

ILVVWSMODULEINIT(action);
#endif /* !__Ilv_Base_Action_H */
