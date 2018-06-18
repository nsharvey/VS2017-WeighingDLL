// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/ilvsock/socket.h
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
#ifndef __IlvSOCKET_H
#define __IlvSOCKET_H

#include <ilviews/macros.h>

#if defined(WINDOWS)
#include <winsock.h>
#include <io.h>
#else  /* !WINDOWS */
#define SOCKET int
#define INVALID_SOCKET -1
#if !defined(closesocket)
#define closesocket close
#endif /* !closesocket */
#if defined(__alpha)
extern "C" {
#endif /* __alpha */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#if defined(__alpha)
}
#endif /* __alpha */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#endif /* !WINDOWS */

class IlvSocket;
typedef void (*IlvSocketReader)(IlvSocket* socket, IlAny arg);

// --------------------------------------------------------------------------
class IlvSocket
{
public:
    virtual ~IlvSocket();
    // ____________________________________________________________
    IlAny	 getInputId()		{ return _inputid; }
    void	 setInputId(IlAny id)	{ _inputid = id;   }
    void	 setCallback(IlvSocketReader reader, IlAny arg = 0)
    {
	_reader = reader;
	_arg = arg;
    }
    IlInt	 readBytes(char*, IlUInt maxToRead);
    IlBoolean	 readNBytes(char*, IlUInt maxToRead);
    IlInt	 writeBytes(const char*, IlInt max = -1);
    SOCKET	 getSocket() {return _socket;}
    IlBoolean	 isBad() const;
    IlBoolean	 writeMessage(const char*, int = 0);
    char*	 readMessage(IlUInt&);
    virtual void error(int = 0);
    virtual void manageInput();
#if defined(WINDOWS)
    virtual void      registerSocket();
    virtual void      unRegisterSocket();
    IlBoolean	      isReadable() const	 { return !_async||_readable; }
    void	      setReadable(IlBoolean f)	 { _readable = f; }
    void	      setASync(IlBoolean f)	 { _async = f; }
    IlBoolean	      isInRead() const		 { return _inread; }
    void	      setInRead(IlBoolean f)	 { _inread = f; }
    static IlAny      GetView()			 { return _view; }
    static IlvSocket* GetSocket(SOCKET);
    static void	      SetView(IlAny v)		 { _view = v; }
    static IlAny      GetAllSockets()		 { return _allSockets; }
    static void	      SetAllSockets(IlAny a)	 { _allSockets = a; }
#endif /* WINDOWS */
protected:
    SOCKET	    _socket;
    IlAny	    _inputid;
    IlvSocketReader _reader;
    IlAny	    _arg;
#if defined(WINDOWS)
    IlBoolean	    _async;
    IlBoolean	    _readable;
    IlBoolean	    _inread;
    static WSAData  _wsaData;
    static int	    _refCount;
    static IlAny    _view;
    static IlAny    _allSockets;
#endif /* WINDOWS */
    IlvSocket(IlvSocketReader = 0, IlAny = 0);
};

extern const char* IlvHostName();
#endif /* __IlvSOCKET_H */

