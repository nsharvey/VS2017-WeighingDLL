// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/stddrop.h
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
// Declaration of Studio drag & drop classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Stddrop_H
#define __IlvSt_Stddrop_H

#include <ivstudio/object.h>
#include <ilviews/ilv.h>
#include <ilviews/base/graphic.h>

class IlvStDdRecipient;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDdData
: public IlvStNamedObject
{
public:
    IlvStDdData(const char* name);
    virtual ~IlvStDdData();

    virtual void begin(const IlvPoint&);
    virtual void dragged(IlvStDdRecipient*, const IlvPoint&);
    virtual void end(IlvStDdRecipient*, const IlvPoint&);
    virtual void abort();

    const char*		getSenderName() const { return _senderName; }
    void		setSenderName(const char* name)
	{ IlvStSetString(_senderName, name); }
    IlAny		getSender() const { return _sender; }
    void		setSender(IlAny sender) { _sender = sender; }
protected:
    char*	_senderName;
    IlAny	_sender;
}; // class IlvStDdData

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDdRecipient
: public IlvStNamedObject
{
public:
    IlvStDdRecipient(IlvStudio* editor, const char* name);

    virtual ~IlvStDdRecipient();
    virtual IlBoolean	    accept(IlvStDdData*, const IlvPoint&) = 0;
    virtual void	    take(IlvStDdData*, const IlvPoint&) = 0;
    virtual void	    enter(IlvStDdData*, const IlvPoint&);
    virtual void	    drag(IlvStDdData*, const IlvPoint&);
    virtual void	    leave(IlvStDdData*, const IlvPoint&);
    virtual IlvCursor*	    getCursor(IlvStDdData*, const IlvPoint&);
    static void		    GlobalToLocal(IlvView*,
					  const IlvPoint& point,
					  IlvPoint& result);
    static IlvCursor*	    GetDefaultCursor();
    static void		    SetDefaultCursor(IlvCursor*);
protected:
    IlvStudio*	_editor;
    static IlvCursor* _DefaultCursor;
}; // class ILVSTUDIOCLASS IlvStDdRecipient

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDdRecipientManager
{
public:
    IlvStDdRecipientManager();
    ~IlvStDdRecipientManager();
    void		add(IlvStDdRecipient*, IlUInt ndx = (IlUInt)-1);
    IlvStDdRecipient*	find(IlvStDdData*, const IlvPoint&);
    void		attach(IlvView*);
    void		detach(IlvView*);
    static IlvStDdRecipientManager* Get(IlvView*);
protected:
    IlvArray	    _recipients;
}; // class IlvStDdRecipientManager

// --------------------------------------------------------------------------
class IlvStudio;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDragDrop
{
public:
    IlvStDragDrop(IlvStudio* editor);
    virtual ~IlvStDragDrop();
    IlvStDdRecipient*	begin(IlvEvent&,
			      IlvStDdData*,
			      IlvCursor* = 0,
			      IlvView* srcView = 0);
    IlvStDdRecipient*	drag(IlvEvent&, IlvStDdData*);
    IlvStDdRecipient*	end(IlvEvent&, IlvStDdData*);
    void 		abort(IlvStDdData*);
    IlvStDdRecipient*	getRecipient() const { return _recipient; }
    IlvView*		getSourceView() const { return _sourceView; }
    void		setSourceView(IlvView* view) { _sourceView = view; }
    IlvCursor*		getDragCursor() const { return _dragCursor; }
    void		setDragCursor(IlvCursor* cursor)
	{ _dragCursor = cursor; }
    IlvCursor*		getDefaultDragCursor() const
	{ return _defaultDragCursor; }
    void		setDefaultDragCursor(IlvCursor* cursor)
	{ _defaultDragCursor = cursor; }
protected:
    void    changeCursor(IlvCursor* cursor);
    void    restoreCursor();

    IlvStudio*		_editor;
    IlvStDdRecipient*	_recipient;
    IlvPoint		_point;
    IlBoolean		_dragged;
    IlvView*		_sourceView;
    IlvCursor*		_lastCursor;
    IlvCursor*		_dragCursor;
    IlvCursor*		_defaultDragCursor;
}; // class IlvStDragDrop

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
#endif /* __IlvSt_Stddrop_H */
