// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/src/socket.cpp
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
// Definition of the IlvSocket class
// --------------------------------------------------------------------------
#include <ilvsock/socket.h>
#include <ilviews/ilv.h>

#if !defined(WINDOWS)
#if !defined(USE_READ_WRITE)
#define USE_READ_WRITE 1
#endif /* USE_READ_WRITE */
#include <unistd.h>
#if defined(sgi)
#include <sys/types.h>
#include <sys/time.h>
#endif /* sgi */
#else  /* WINDOWS */
#if defined(USE_READ_WRITE)
#undef USE_READ_WRITE
#endif /* USE_READ_WRITE */
WSAData IlvSocket::_wsaData;
int	IlvSocket::_refCount = 0;
#define WS_VERSION_REQD  0x0101
#define WS_VERSION_MAJOR HIBYTE(WS_VERSION_REQD)
#define WS_VERSION_MINOR LOBYTE(WS_VERSION_REQD)
#define MIN_SOCKETS_REQD 6
extern "C" ILVDSPEXPORTEDFUNCTION(void) ILVCALLBACK IlvDispatchEvent(MSG*);
extern "C" ILVDSPEXPORTEDFUNCTION(IlBoolean) ILVCALLBACK IlvNextEvent(MSG*);
#endif /* WINDOWS */

// --------------------------------------------------------------------------
#if defined(__SVR4) || defined(sgi) || defined(ultrix) || defined(sun)
#define USE_UTSNAME
#include <sys/utsname.h>
#endif /* __SVR4 || sgi || ultrix || Sun */
#if defined(__alpha)
extern "C" int gethostname(char*, int);
#endif /* __alpha */
const char*
IlvHostName()
{
#if defined(USE_UTSNAME)
    static struct utsname uts;
    uname(&uts);
    return(uts.nodename);
#else  /* !USE_UTSNAME */
#define MAX_HOST_LEN 512
    static char host[MAX_HOST_LEN];
    gethostname(host, MAX_HOST_LEN);
    return host;
#endif /* !USE_UTSNAME */
}

#if defined(WINDOWS)
// --------------------------------------------------------------------------
IlAny IlvSocket::_view	      = 0;
IlAny IlvSocket::_allSockets = 0;

// --------------------------------------------------------------------------
IlvSocket*
IlvSocket::GetSocket(SOCKET s)
{
    IlvLink* link = (IlvLink*)_allSockets;
    while (link) {
	if (((IlvSocket*)link->getValue())->getSocket() == s)
	    return (IlvSocket*)(link->getValue());;
        link = link->getNext();
    }
    return 0;
}

// --------------------------------------------------------------------------
void
IlvSocket::registerSocket()
{
}

// --------------------------------------------------------------------------
void
IlvSocket::unRegisterSocket()
{
}
#endif /* WINDOWS */

// --------------------------------------------------------------------------
IlvSocket::IlvSocket(IlvSocketReader r,
		     IlAny a)
    : _socket(INVALID_SOCKET),
      _inputid(0),
      _reader(r),
      _arg(a)
#if defined(WINDOWS)
    , _async(IlFalse),
      _readable(IlTrue),
      _inread(IlFalse)
#endif /* WINDOWS */
{
#if defined(WINDOWS)
    if (!_refCount) {
	if (WSAStartup(WS_VERSION_REQD, &_wsaData)) {
	    IlvFatalError("winsock.dll not responding.");
	    return;
	}
	if ((LOBYTE(_wsaData.wVersion) < WS_VERSION_MAJOR) ||
	    ((LOBYTE(_wsaData.wVersion) == WS_VERSION_MAJOR) &&
	     (HIBYTE(_wsaData.wVersion) < WS_VERSION_MINOR))) {
	    IlvFatalError(
			  "Windows Sockets version (%d.%d) is previous to (%d.%d).",
			  LOBYTE(_wsaData.wVersion), HIBYTE(_wsaData.wVersion),
			  WS_VERSION_MAJOR, WS_VERSION_MINOR);
	    return;
	}
	if (_wsaData.iMaxSockets < MIN_SOCKETS_REQD) {
	    IlvFatalError(
			  "This application requires a minimum of %d supported sockets.",
			  MIN_SOCKETS_REQD);
	    return;
	}
    }
    _refCount++;
#endif /* WINDOWS */
}

// --------------------------------------------------------------------------
IlvSocket::~IlvSocket()
{
    if (_socket > 0)
	closesocket(_socket);
#if defined(WINDOWS)
    if (!--_refCount)
	WSACleanup();
#endif /* WINDOWS */
}

// --------------------------------------------------------------------------
IlBoolean
IlvSocket::isBad() const
{
    if (_socket <= 0)
	return IlTrue;
    else
	return IlFalse;
}

// --------------------------------------------------------------------------
IlInt
IlvSocket::readBytes(char* buffer,
		     IlUInt lg)
{
    int code;
#if defined(WINDOWS)
    MSG msg;
    while (!isReadable() && IlvNextEvent(&msg))
    	IlvDispatchEvent(&msg);
    setReadable(IlFalse);
#endif /* WINDOWS */
#if defined(USE_READ_WRITE)
    code = read(_socket, buffer, (int)lg);
#else  /* !USE_READ_WRITE */
    code = recv(_socket, buffer, (int)lg, 0);
#endif /* !USE_READ_WRITE */
    if (code <= 0) {
	//perror("IlvSocket::readBytes");
	error(code);
	return -1;
    }
    return code;
}

// --------------------------------------------------------------------------
IlInt
IlvSocket::writeBytes(const char* buffer,
		      IlInt lg)
{
    int code;
#if defined(USE_READ_WRITE)
    code = write(_socket, (char*)buffer, (int)lg);
#else  /* !USE_READ_WRITE */
    code = send(_socket, (char*)buffer, (int)lg, 0);
#endif /* !USE_READ_WRITE */
    if (code <=  0) {
	//perror("IlvSocket::writeBytes");
	error(code);
	return -1;
    }
    return code;
}

// --------------------------------------------------------------------------
IlBoolean
IlvSocket::readNBytes(char* buffer,
		      IlUInt lg)
{
    int done = 0;
    int code;
    while (done < (int)lg) {
#if defined(WINDOWS)
	MSG msg;
	while (!isReadable() && IlvNextEvent(&msg))
	    IlvDispatchEvent(&msg);
	setReadable(IlFalse);
#endif /* WINDOWS */
#if defined(USE_READ_WRITE)
	code = read(_socket, buffer + done, (int)(lg - done));
#else  /* !USE_READ_WRITE */
	code = recv(_socket, buffer + done, (int)(lg - done), 0);
#endif /* !USE_READ_WRITE */
	if (code <=  0) {
	    //perror("IlvSocket::readNBytes");
	    error(code);
	    return IlFalse;
	}
	done += code;
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
IlvSocket::writeMessage(const char* message,
			int length)
{
    IlInt l = (IlInt)(length ? length : strlen(message));
    if (!l)
	return IlTrue;
    IlInt nl = (IlInt)ntohl(l);
    if ((writeBytes((char*)&nl, sizeof(IlInt)) > 0) &&
        (writeBytes(message, l) > 0))
	return IlTrue;
    return IlFalse;
}

// --------------------------------------------------------------------------
char*
IlvSocket::readMessage(IlUInt& count)
{
    static char*  buffer = 0;
    static IlInt length = 0;
    IlInt l;
    count = 0;
    if (readNBytes((char*)&l, sizeof(IlInt))) {
    	l = (IlInt)ntohl(l);
	if (length <= l) {
	    delete buffer;
	    buffer = new char[l + 1];
	    length = l + 1;
	}
	if (readNBytes(buffer, l)) {
	    buffer[l] = 0;
	    count = l;
	    return buffer;
	}
    }
    return 0;
}

// --------------------------------------------------------------------------
void
IlvSocket::error(int)
{}

// --------------------------------------------------------------------------
void
IlvSocket::manageInput()
{}
