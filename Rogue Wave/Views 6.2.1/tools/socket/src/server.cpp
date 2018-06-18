// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/src/server.cpp
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
// Definition of the IlvServerSocket class
// --------------------------------------------------------------------------
#include <ilviews/base/view.h>
#include <ilvsock/server.h>
#if !defined(WINDOWS)
#  include <unistd.h>
#endif /* !WINDOWS */

#if defined(sgi)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <osfcn.h>
#endif /* sgi */

#include <sys/types.h>
#include <sys/stat.h>

#if defined(__xlC__)
#  include <sys/select.h>
#endif /* __xlC__ */

#if defined(__alpha) || defined(ultrix)
extern "C" {
    int socket(int, int, int);
    unsigned short htons(unsigned short);
    int listen(int, int);
    int accept(int, struct sockaddr*, int*);
    int select(int, fd_set*, fd_set*, fd_set*, struct timeval*);
}
#endif /* __alpha || utrix */

// --------------------------------------------------------------------------
static void
ReadOnSocket(int,
	     IlAny arg)
{
    IlvSocket* socket = (IlvSocket*)arg;
    socket->manageInput();
}

#if defined(WINDOWS)
#define SOCKET_MSG (WM_USER + 1)

// --------------------------------------------------------------------------
static inline HWND
GetHWnd(IlvSystemView view)
{
    return IL_REINTERPRETCAST(HWND, view);
}

// --------------------------------------------------------------------------
static inline HWND
GetHWnd()
{
    return GetHWnd(IL_REINTERPRETCAST(IlvView*,
				      IlvSocket::GetView())->getSystemView());
}

// --------------------------------------------------------------------------
IlBoolean
SocketProc(IlvAbstractView*	/* view */,
	   IlvSystemView	hWnd,
	   unsigned int		iMessage,
	   IlvWParam		wParam,
	   IlvLParam		lParam,
	   IlAny&		returned,
	   IlAny		/* userArg */)
{
    returned = 0;
    if (iMessage != SOCKET_MSG)
    	return IlFalse;
    IlvSocket* socket = IlvSocket::GetSocket((SOCKET)wParam);
    if (!socket) {
    	IlvFatalError("SocketProc:: Socket not enregistred.");
	return IlTrue;
    }
    switch(WSAGETSELECTEVENT(lParam)) {
    case FD_ACCEPT:
    	socket->manageInput();
	if (WSAAsyncSelect((int)wParam, GetHWnd(hWnd), SOCKET_MSG, FD_ACCEPT)
	    == SOCKET_ERROR)
	    IlvFatalError(
			  "SocketProc: error %d: WSAAsyncSelect failure.",
			  WSAGetLastError());
	return IlTrue;
    case FD_READ:
    	if (WSAGETSELECTERROR(lParam))
	    IlvFatalError("Error %d in FD_READ for socket %d.",
	    		  WSAGETSELECTERROR(lParam), wParam);
	socket->setReadable(IlTrue);
	if (!socket->isInRead()) {
	    socket->setInRead(IlTrue);
	    ReadOnSocket((int)wParam, socket);
	    socket->setInRead(IlFalse);
	}
	return IlTrue;
    default:
    	IlvFatalError("SocketProc: Bad Select Event: %d.",
		      WSAGETSELECTEVENT(lParam));
    }
    return IlTrue;
}
#endif /* WINDOWS */

// --------------------------------------------------------------------------
IlvServerSocket::IlvServerSocket(IlvDisplay* display,
				 IlUShort port,
				 IlvSocketReader r,
				 IlAny a)
    : IlvSocket(r, a),
      _display(display),
      _name(0)
{
#if defined(WINDOWS)
    if (!_refCount)
    	return;
#endif /* WINDOWS */
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET) {
#if defined(WINDOWS)
	IlvFatalError(
		      "IlvServerSocket::IlvServerSocket: Can't create socket (error %d).",
		      WSAGetLastError());
#else  /* !WINDOWS */
	perror("IlvServerSocket::IlvServerSocket");
#endif /* !WINDOWS */
	return;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(_socket, IL_REINTERPRETCAST(struct sockaddr*, &server),
	     sizeof(server))) {
#if defined(WINDOWS)
	IlvFatalError(
		      "IlvServerSocket::IlvServerSocket: Can't bind socket (error %d).",
		      WSAGetLastError());
#else  /* !WINDOWS */
	perror("IlvServerSocket::IlvServerSocket");
	return;
#endif /* !WINDOWS */
    }
    listen(_socket, 5);
    IlvRegisterSocket(this, _display);
}

#if !defined(WINDOWS)
// --------------------------------------------------------------------------
IlvServerSocket::IlvServerSocket(IlvDisplay* display,
				 const char* name,
				 IlvSocketReader r,
				 IlAny a)
    : IlvSocket(r, a),
      _display(display),
      _name(0)
{
    _name = new char[strlen(name)+1];
    strcpy(_name, name);
    unlink(_name);
    struct sockaddr_un serverun;
    _socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (_socket < 0) {
	perror("IlvServerSocket::IlvServerSocket");
	return;
    }
    serverun.sun_family = AF_UNIX;
    strcpy(serverun.sun_path, name);
    if (bind(_socket, IL_REINTERPRETCAST(struct sockaddr*, &serverun),
	     sizeof(serverun)))
	perror("IlvServerSocket::IlvServerSocket");
    else {
	listen(_socket, 5);
	IlvRegisterSocket(this, _display);
    }
}
#endif /* !WINDOWS */

// --------------------------------------------------------------------------
IlvServerSocket::~IlvServerSocket()
{
    IlvAcceptSocket* socket;
    IlvMapList(&_connections, IlvAcceptSocket*, socket,
	       delete socket;
	       );
    IlvUnRegisterSocket(this,_display);
    if (_name) {
#if defined(WINDOWS) && defined(_MSC_VER) && (_MSC_VER >= 1400) /* x86_.net2005_8.0 or higher */
	_chmod(_name, 0x700);
	_unlink(_name);
#else /* x86_.net2003_7.1 or lower for windows, or any Unix/Linux ports */
	chmod(_name, 0x700);
	unlink(_name);
#endif
	delete _name;
    }
}

// --------------------------------------------------------------------------
void
IlvServerSocket::read(IlvAcceptSocket* socket)
{
    if (_reader)
	_reader(socket,_arg);
}

// --------------------------------------------------------------------------
IlvAcceptSocket::IlvAcceptSocket(IlvDisplay*		d,
				 IlvServerSocket*	srv,
				 SOCKET			fd)
    : _server(srv),
      _display(d)
{
    _socket = fd;
}

// --------------------------------------------------------------------------
IlvAcceptSocket::~IlvAcceptSocket()
{
    IlvUnRegisterSocket(this, _display);
}

// --------------------------------------------------------------------------
void
IlvAcceptSocket::manageInput()
{
    _server->read(this);
}

// --------------------------------------------------------------------------
void
IlvServerSocket::manageInput()
{
    SOCKET msgsock;
    msgsock = accept(getSocket(),
		     (struct sockaddr*)0,
#if !defined(_AIX) && !defined(sinix) && !defined(linux)
		     (int*)
#endif
		     0);
    if (msgsock == INVALID_SOCKET) {
#if defined(WINDOWS)
	IlvFatalError(
		      "IlvServerSocket::IlvServerSocket: Can't accept socket (error %d).",
		      WSAGetLastError());
#else  /* !WINDOWS */
	perror("accept");
#endif /* !WINDOWS */
	return;
    }
    IlvAcceptSocket* socket = make(msgsock);
    _connections.insert(socket);
}

// --------------------------------------------------------------------------
IlvAcceptSocket*
IlvServerSocket::make(SOCKET fd)
{
    IlvAcceptSocket* socket = new IlvAcceptSocket(_display, this, fd);
    IlvRegisterSocket(socket, _display);
    return socket;
}

// --------------------------------------------------------------------------
void
IlvServerSocket::remove(IlvAcceptSocket* socket)
{
    _connections.remove(socket);
    delete socket;
}

// --------------------------------------------------------------------------
void
IlvAcceptSocket::error(int)
{
    _server->remove(this);
}

#if !defined(WINDOWS)
// --------------------------------------------------------------------------
static void
ErrorOnSocket(int,
	      IlAny arg)
{
    IlvSocket* socket = (IlvSocket*)arg;
    socket->setInputId(0);
}

#else  /* WINDOWS */
// --------------------------------------------------------------------------
static void
InsertInList(IlvSocket* socket,
	     IlvDisplay* display)
{
    if (!IlvSocket::GetAllSockets()) {
	IlvSocket::SetAllSockets(new IlvLink(socket));
	if (!IlvSocket::GetView())
	    IlvSocket::SetView(new IlvView(display,
					   "hidden_view", "Hidden view",
					   IlvRect(0, 0, 10, 10), IlFalse));
	((IlvView*)IlvSocket::GetView())->setWindowProc(SocketProc);
    } else
	if (!IlvSocket::GetSocket(socket->getSocket()))
	    IlvSocket::SetAllSockets(
				     new IlvLink(socket, (IlvLink*)IlvSocket::GetAllSockets()));
}

// --------------------------------------------------------------------------
static void
RemoveFromInList(IlvSocket* socket)
{
    IlvLink* link = (IlvLink*)IlvSocket::GetAllSockets();
    IlvLink* prev = 0;
    while (link) {
	if (link->getValue() == socket) {
	    if (prev)
		prev->setNext(link->getNext());
	    else
	    	IlvSocket::SetAllSockets(link->getNext());
	    link->setNext(0);
	    delete link;
	    break;
	}
    	prev = link;
        link = link->getNext();
    }
    if (!IlvSocket::GetAllSockets()) {
    	delete (IlvView*)IlvSocket::GetView();
	IlvSocket::SetView(0);
    }
}

// --------------------------------------------------------------------------
void
IlvServerSocket::registerSocket()
{
    InsertInList(this, getDisplay());
    if (WSAAsyncSelect(getSocket(),
		       GetHWnd(),
		       SOCKET_MSG,
		       FD_ACCEPT) == SOCKET_ERROR)
	IlvFatalError(
		      "IlvServerSocket::registerSocket: error %d: WSAAsyncSelect failure.",
		      WSAGetLastError());
    setASync(IlTrue);
    setReadable(IlFalse);
}

// --------------------------------------------------------------------------
void
IlvServerSocket::unRegisterSocket()
{
    if (WSAAsyncSelect(_socket, GetHWnd(), 0, 0) == SOCKET_ERROR) {
	IlvFatalError(
		      "IlvServerSocket::unRegisterSocket: error %d: WSAAsyncSelect failure.",
		      WSAGetLastError());
    }
    RemoveFromInList(this);
    setASync(IlFalse);
}

// --------------------------------------------------------------------------
void
IlvAcceptSocket::registerSocket()
{
    InsertInList(this, getDisplay());
    if (WSAAsyncSelect(_socket, GetHWnd(), SOCKET_MSG, FD_READ) == SOCKET_ERROR) {
	IlvFatalError(
		      "IlvAcceptSocket::registerSocket: error %d: WSAAsyncSelect failure.",
		      WSAGetLastError());
    }
    setASync(IlTrue);
    setReadable(IlFalse);
}

// --------------------------------------------------------------------------
void
IlvAcceptSocket::unRegisterSocket()
{
    if (WSAAsyncSelect(_socket, GetHWnd(), 0, 0) == SOCKET_ERROR) {
	IlvFatalError(
		      "IlvAcceptSocket::unRegisterSocket: error %d: WSAAsyncSelect failure.",
		      WSAGetLastError());
    }
    RemoveFromInList(this);
    setASync(IlFalse);
}
#endif /* WINDOWS */

// --------------------------------------------------------------------------
void
IlvRegisterSocket(IlvSocket* socket,
		  IlvDisplay*)
{
#if defined(WINDOWS)
    socket->registerSocket();
#else  /* !WINDOWS */
    IlvRegisterInput(socket->getSocket(),
		     ReadOnSocket,
		     socket,
		     ErrorOnSocket);
#endif /* !WINDOWS */
}

// --------------------------------------------------------------------------
void
IlvUnRegisterSocket(IlvSocket* socket,
		    IlvDisplay*)
{
#if defined(WINDOWS)
    socket->unRegisterSocket();
#else  /* !WINDOWS */
    IlvUnRegisterInput(socket->getSocket());
#endif /* !WINDOWS */
}
