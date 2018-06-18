// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/src/client.cpp
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
// Implementation of the IlvClientSocket class
// --------------------------------------------------------------------------

#include <ilvsock/client.h>
#if defined(WINDOWS)
#include <ilviews/ilv.h>
#else  /* !WINDOWS */
#include <unistd.h>
#endif /* !WINDOWS */

#if defined(__alpha) || defined(__DECCXX)
extern "C" int socket(int, int, int);
extern "C" unsigned short htons(unsigned short);
extern "C" int listen(int, int);
extern "C" int accept(int, struct sockaddr*, int*);
extern "C" int select(int, fd_set*, fd_set*, fd_set*, struct timeval*);
extern "C" int gethostname(char*, int);
#endif /* __alpha || __DECCXX */

// --------------------------------------------------------------------------
IlvClientSocket::IlvClientSocket(IlUShort port,
				 const char* host,
				 IlvSocketReader r,
				 IlAny a)
    : IlvSocket(r, a)
{
    struct sockaddr_in server;
    struct hostent* hp;
    int code;
#if defined(WINDOWS)
    if (!_refCount)
    	return;
#endif /* WINDOWS */
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET) {
#if defined(WINDOWS)
	IlvFatalError(
		      "IlvClientSocket::IlvClientSocket: Can't create socket (error %d).",
		      WSAGetLastError());
#else  /* !WINDOWS */
	perror("IlvClientSocket::IlvClientSocket socket");
#endif /* !WINDOWS */
	return;
    }
    server.sin_family = AF_INET;
    if (!host || !strlen(host))
	host = IlvHostName();
    hp = gethostbyname((char*)host);
    if (!hp) {
#if defined(WINDOWS)
	IlvFatalError(
		      "IlvClientSocket::IlvClientSocket: Can't create socket (error %d).",
		      WSAGetLastError());
#else  /* !WINDOWS */
	perror("IlvClientSocket::IlvClientSocket gethostbyname");
#endif /* !WINDOWS */
	return;
    }
    memcpy((char*)&server.sin_addr, (char*)hp->h_addr, hp->h_length);
    server.sin_port = htons(port);
    code = connect(_socket, IL_REINTERPRETCAST(struct sockaddr*, &server),
		   sizeof(server));
    if (code) {
#if defined(WINDOWS)
	IlvFatalError(
		      "IlvClientSocket::IlvClientSocket: Can't connect to socket (error %d).",
		      WSAGetLastError());
#else  /* !WINDOWS */
	perror("IlvClientSocket::IlvClientSocket connect");
#endif /* !WINDOWS */
	return;
    }
}

#if !defined(WINDOWS)
// --------------------------------------------------------------------------
IlvClientSocket::IlvClientSocket(const char* path,
				 IlvSocketReader r,
				 IlAny a)
    : IlvSocket(r, a)
{
    struct sockaddr_un serverun;
    int code;
    _socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (_socket < 0) {
	perror("IlvClientSocket::IlvClientSocket connect");
	return;
    }
    serverun.sun_family = AF_UNIX;
    strcpy(serverun.sun_path,path);
    code = connect(_socket, IL_REINTERPRETCAST(struct sockaddr*, &serverun),
		   sizeof(serverun));
    if (code) {
	perror("IlvClientSocket::IlvClientSocket connect");
	return;
    }
}
#endif /* !WINDOWS */
