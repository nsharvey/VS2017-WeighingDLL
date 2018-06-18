// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/readers/vpf/include/vpf/error.h
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
// Declaration of the error handling related classes
// --------------------------------------------------------------------------
#ifndef VPF_ERROR_H
#define VPF_ERROR_H

#include <ilog/sstream.h>
#include <vpf/string.h>
IL_STDUSE

// --------------------------------------------------------------------------
class VpfError
{
public:
    VpfError(const char*);
    ~VpfError();
    // ____________________________________________________________
    strstream& getStream() { return _stream; }
    
    void setNext(VpfError* next) { _next = next; }
    VpfError* getNext() const { return _next; }
    
    const char* getWhere() const { return _where; }
protected:
    char*	_where;
    strstream	_stream;
    VpfError*	_next;
};

// --------------------------------------------------------------------------
class VpfErrorReporter
{
public:
    VpfErrorReporter();
    ~VpfErrorReporter();
    // ____________________________________________________________
    void add(VpfError*);
    VpfError* getFirst();
    const VpfError* getFirst() const;
    void clear();
    VpfErrorReporter* clone() const;
    void push();
    void pop();

    static void Add(VpfError* error) { _ErrorReporter.add(error); }
    static VpfError* GetFirst() { return _ErrorReporter.getFirst(); }
    static void Clear() { _ErrorReporter.clear(); }
    static void Push() { _ErrorReporter.push(); }
    static void Pop() { _ErrorReporter.pop(); }

protected:
    VpfError*		_head;
    VpfError*		_queue;
    VpfErrorReporter*	_stack;

    static VpfErrorReporter _ErrorReporter;
};
#endif /* VPF_ERROR_H */

