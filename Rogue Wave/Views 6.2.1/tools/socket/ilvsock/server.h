// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/ilvsock/server.h
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
#ifndef __IlvSOCKETSERVER_H
#define __IlvSOCKETSERVER_H

#include <ilvsock/socket.h>
#include <ilviews/ilv.h>

class IlvAcceptSocket;
class IlvServerSocket;

// --------------------------------------------------------------------------
class IlvServerSocket : public IlvSocket
{
public:
    // INET
    IlvServerSocket(IlvDisplay*, IlUShort, IlvSocketReader = 0, IlAny = 0);
#if !defined(WINDOWS)
    // UNIX
    IlvServerSocket(IlvDisplay*, const char*, IlvSocketReader = 0,IlAny = 0);
#endif /* !WINDOWS */
    virtual ~IlvServerSocket();
    // ____________________________________________________________
    IlvDisplay*              getDisplay() { return _display; }
    void                     remove(IlvAcceptSocket* socket);
    virtual IlvAcceptSocket* make(SOCKET fd);
    virtual void             read (IlvAcceptSocket*);
    virtual void             manageInput();
#if defined(WINDOWS)
    virtual void	     registerSocket();
    virtual void	     unRegisterSocket();
#endif /* WINDOWS */
protected:
    IlvDisplay* _display;
    char*       _name;
    IlList     _connections;
};

// --------------------------------------------------------------------------
class IlvAcceptSocket : public IlvSocket
{
public:
    IlvAcceptSocket(IlvDisplay*, IlvServerSocket*, SOCKET);
    ~IlvAcceptSocket();
    // ____________________________________________________________
    IlvDisplay*	     getDisplay()	{ return _display; }
    IlvServerSocket* getServerSocket()	{ return _server;  }
    virtual void     error(int = 0);
    virtual void     manageInput();
#if defined(WINDOWS)
    virtual void     registerSocket();
    virtual void     unRegisterSocket();
#endif /* WINDOWS */
protected:
    IlvServerSocket* _server;
    IlvDisplay* _display;
};

void IlvRegisterSocket(IlvSocket*,   IlvDisplay*);
void IlvUnRegisterSocket(IlvSocket*, IlvDisplay*);

#endif /* __IlvSOCKETSERVER_H */
