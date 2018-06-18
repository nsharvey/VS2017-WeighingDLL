// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/src/error.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
// Definition of the error handlng routines
// --------------------------------------------------------------------------

#include <vpf/error.h>

// --------------------------------------------------------------------------
VpfError::VpfError(const char* where)
: _where(VpfStrDup(where)),
  _stream(),
  _next(0)
{
}

// --------------------------------------------------------------------------
VpfError::~VpfError()
{
    if (_where)
	delete [] _where;
    if (_next)
	delete _next;
}

VpfErrorReporter VpfErrorReporter::_ErrorReporter;

// --------------------------------------------------------------------------
VpfErrorReporter::VpfErrorReporter()
: _head(0), 
  _queue(0),
  _stack(0)
{
}

// --------------------------------------------------------------------------
VpfErrorReporter::~VpfErrorReporter()
{
    // Principle: let the last reporter in the
    // stack delete the head error
    // (and thus all the following ones)
    if (_stack)
	delete _stack;
    else
    if (_head)
	delete _head;
}

// --------------------------------------------------------------------------
void
VpfErrorReporter::add(VpfError* error)
{
    if (_head) {
	_queue->setNext(error);
	_queue = error;
    } else {
	_head = error;
	_queue = error;
    }
}

// --------------------------------------------------------------------------
VpfError*
VpfErrorReporter::getFirst()
{
    return _head;
}

// --------------------------------------------------------------------------
const VpfError*
VpfErrorReporter::getFirst() const
{
    return _head;
}

// --------------------------------------------------------------------------
void
VpfErrorReporter::clear()
{
    if (_head)
	delete _head;
    _head = 0;
    _queue = 0;

    while (_stack) {
	VpfErrorReporter* ptr = _stack;
	_stack = ptr->_stack;
	ptr->_stack = 0;
	ptr->_head = 0;
	delete ptr;
    }
}

// --------------------------------------------------------------------------
VpfErrorReporter*
VpfErrorReporter::clone() const
{
    VpfErrorReporter* ptr = new VpfErrorReporter();
    if (ptr) {
	ptr->_head = _head;
	ptr->_queue = _queue;
	ptr->_stack = _stack;
    }
    return ptr;
}

// --------------------------------------------------------------------------
void
VpfErrorReporter::push()
{
    VpfErrorReporter* ptr = clone();
    if (ptr)
	_stack = ptr;
}

// --------------------------------------------------------------------------
void
VpfErrorReporter::pop()
{
    VpfErrorReporter* ptr = _stack;
    if (!ptr)
	return;

    _head = ptr->_head;
    _queue = ptr->_queue;
    _stack = ptr->_stack;

    if (_queue) {
	if (_queue->getNext()) {
	    delete _queue->getNext();
	    _queue->setNext(0);
	}
    }

    ptr->_head = 0;
    ptr->_queue = 0;
    ptr->_stack = 0;
    delete ptr;
}
