// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/evloop.h
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
// Event loop related declarations
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Evloop_H
#define __Ilv_Base_Evloop_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Il_List_H)
#include <ilog/list.h>
#endif
// --------------------------------------------------------------------------
// External input/output callback
#if !defined(WINDOWS) && !defined(PM)
typedef void (*IlvLoopCallback)(int, IlAny);
#endif /* ! WINDOWS && ! PM */

// --------------------------------------------------------------------------
// IdleProc
typedef IlBoolean (*IlvIdleProc) (IlAny userArg);

typedef IlAny IlvIdleProcId;

// --------------------------------------------------------------------------
// Input type
typedef enum IlvInputMask {
    IlvInputNone	= 0,
    IlvInputEvent	= (1<<0),
    IlvInputTimer	= (1<<1),
    IlvInputExternal	= (1<<2),
    IlvInputAll		= (IlvInputEvent | IlvInputTimer | IlvInputExternal)
} _IlvInputMask;

// --------------------------------------------------------------------------
// doubly linked chains

class ILVDSPEXPORTED IlvRedrawProcLink
{
    friend class IlvEventLoop;

public:
    IlvRedrawProcLink(IlvIdleProc f, IlAny arg, IlvRedrawProcLink* after)
	: _arg(arg),
	  _buffered(IlFalse),
	  _erased(IlTrue),
	  _previous(after),
	  _next(0),
	  _function(f)
    {
	if (_previous) {
	    if (_previous->_next && _previous->_next != this) {
	    	_next = _previous->_next;
	    	_next->_previous = this;
	    }
	    _previous->_next = this;
	}
    }
    ~IlvRedrawProcLink()
    {
	if (_previous) 
	    _previous->_next = _next;
	if (_next) 
	    _next->_previous = _previous;
    }

    inline void		doIt()
			{
			    if (_function && _arg)
				(void) (*_function)(_arg);
			}
    inline
    IlvRedrawProcLink*	append(IlvIdleProc f, IlAny arg)
			{
			    return _next
				? _next->append(f, arg)
				: (_next = new IlvRedrawProcLink(f,arg,this));
			}

    IlAny		_arg;
    IlBoolean		_buffered;
    IlBoolean		_erased;

protected:
    IlvRedrawProcLink*	_previous;
    IlvRedrawProcLink*	_next;
    IlvIdleProc		_function;
};

// --------------------------------------------------------------------------
// IlvEventLoop class definition
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvEventLoop
{
public:
    IlvEventLoop(IlBoolean setIt = IlTrue);
    virtual ~IlvEventLoop();

    // ----------------------------------------------------------------------
    // Global eventLoop
    inline static
    IlvEventLoop*	getEventLoop()
			{
			    return _currentEventLoop
				? _currentEventLoop
				: _defaultEventLoop;
			}
    inline static void	setEventLoop(IlvEventLoop* eventLoop)
			{
			    _currentEventLoop = eventLoop;
			}

#if !defined(WINDOWS) && !defined(PM)
    // External input/output. Only implemented on Unix platforms.
    virtual void	addInput(int			fd,
				 IlvLoopCallback	cb,
				 IlAny			arg     = 0,
				 IlvLoopCallback	errorCb = 0);
    virtual void	addOutput(int			fd,
				  IlvLoopCallback	cb,
				  IlAny			arg     = 0,
				  IlvLoopCallback	errorCb = 0);

    virtual void	removeInput(int fd);

    virtual void	removeOutput(int fd);
#endif /* ! WINDOWS && ! PM */

    // ----------------------------------------------------------------------
    // IdleProc management
    virtual
    IlvIdleProcId	addIdleProc(IlvIdleProc idleProc, IlAny userArg);
    virtual IlBoolean	removeIdleProc(IlvIdleProcId idleProcId);

    // ----------------------------------------------------------------------
    // Input source management
    virtual
    IlvInputMask	pendingInput();

    virtual
    IlvInputMask	processInput(IlvInputMask inputMask);

    // ----------------------------------------------------------------------
    // Event management
    virtual IlBoolean	dispatchEvent(IlAny systemEvent);

    virtual IlAny	nextEvent(IlAny systemEvent);

    // ----------------------------------------------------------------------
    // Lazy redraw management
    inline IlBoolean	partialLazyRedraw() const { return _lazyRedraw > 0; }
    inline IlBoolean	lazyRedraw() const { return _lazyRedraw > 1; }
    inline IlUInt	lazyRedrawLevel() const { return _lazyRedraw; }
    inline void		setLazyRedraw(IlUInt lazy) { _lazyRedraw = lazy; }

    virtual
    IlvRedrawProcLink*	addRedrawProc(IlvIdleProc redrawProc, IlAny userArg);
    virtual IlBoolean 	removeRedrawProc(IlvRedrawProcLink* procId);
    void		flushRedraw(IlUInt level = 0);
    inline IlBoolean	pendingRedraw() { return _redrawLink != 0; }

    // ----------------------------------------------------------------------
    // Not documented
    inline IlAny	getInternal() const { return _internal; }
    inline IlAny	getExt()      const { return _ext; }
    inline static
    IlvEventLoop*	getDefaultEventLoop() { return _defaultEventLoop; }

    static void		_staticInit();

protected:
    static
    IlvEventLoop* 	_defaultEventLoop;
    static
    IlvEventLoop*	_currentEventLoop;

    IlAny		_internal;
    IlAny		_ext;
    IlUInt		_lazyRedraw;
    IlvRedrawProcLink* 	_redrawLink;
    IlvRedrawProcLink* 	_lastRedraw;
};

// --------------------------------------------------------------------------
extern "C" {
ILVDSPEXPORTEDFUNCTION(void) IlvMainLoop();
ILVDSPEXPORTEDFUNCTION(void) IlvExit(int);
}

/*
 * These functions are dependant of the system.
 * To use them you must declare them in your code.

 // X or Motif version:
 extern "C" IlBoolean  IlvDispatchEvent(XEvent*);
 extern "C" IlvDisplay* IlvNextEvent(XEvent*);

 // Windows version
 extern "C" ILVDSPEXPORTEDFUNCTION(void) IlvDispatchEvent(MSG*);
 extern "C" ILVDSPEXPORTEDFUNCTION(IlBoolean) IlvNextEvent(MSG*);
 */

#if !defined(WINDOWS) && !defined(PM)

inline void IlvRegisterInput(int		fd,
			     IlvLoopCallback	cb,
			     IlAny		arg	= 0,
			     IlvLoopCallback	errorCb	= 0)
{
    IlvEventLoop::getEventLoop()->addInput(fd, cb, arg, errorCb);
}

inline void IlvRegisterOutput(int		fd,
			      IlvLoopCallback	cb,
			      IlAny		arg	= 0,
			      IlvLoopCallback	errorCb = 0)
{
    IlvEventLoop::getEventLoop()->addOutput(fd, cb, arg, errorCb);
}

inline void IlvUnRegisterInput(int fd)
{
    IlvEventLoop::getEventLoop()->removeInput(fd);
}

inline void IlvUnRegisterOutput(int fd)
{
    IlvEventLoop::getEventLoop()->removeOutput(fd);
}

#endif /* !defined(WINDOWS) && !defined(PM) */

#endif /* ! __Ilv_Base_Evloop_H */
