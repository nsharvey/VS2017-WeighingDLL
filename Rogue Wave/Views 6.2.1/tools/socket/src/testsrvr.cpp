// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/src/testsrvr.cpp
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
// Testing the IlvServerSocket class
// To be used in conjunction with testclient
// --------------------------------------------------------------------------

#include <ilvsock/server.h>
#include <ilviews/contain/contain.h>
#include <ilviews/graphics/inter.h>

#define USE_AF_INET
#define PORT 5101
#define TMPFILE "/tmp/ilv.sock"
#include <ilviews/graphics/label.h>

static void ReadRequest(IlvSocket*, IlAny);

IlvContainer* container;
IlvLabel*     aLabel;

// --------------------------------------------------------------------------
static void
Quit(IlvView* top,
     IlAny server)
{
    delete (IlvServerSocket*)server;
    IlvDisplay* display = top->getDisplay();
    delete top;
    delete display;
    IlvExit(0);
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Demo", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Can't open Display");
	return 1;
    }
    IlvRect size(0, 0, 200, 200);
    IlvView* topview = new IlvView(display,
				   "ilvtest",
				   "ilvtest",
				   size,
				   IlFalse);
    //Creating container View
    container = new IlvContainer(topview, size);
    //Creating objects
    aLabel = new IlvLabel(display, IlvPoint(100, 100), "A Label");
    aLabel->setInteractor(new IlvMoveInteractor);
    container->addObject(aLabel);
    IlvServerSocket* server = new IlvServerSocket(display,
#if defined(WINDOWS) || defined(USE_AF_INET)
						  PORT,
#else  /* !WINDOWS && !USE_AF_INET */
						  TMPFILE,
#endif /* !WINDOWS && !USE_AF_INET */
						  ReadRequest,
						  container);
    if (server->isBad())
	IlvFatalError("Bad Server...");
    topview->setDestroyCallback(Quit, server);
    topview->show();
    IlvMainLoop();
    return 0;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ReadRequest(IlvSocket* sock,
	    IlAny)
{
    IlUInt count = 0;
    char* recv = sock->readMessage(count);
    if (recv) {
	IlvPrint("Receiving %s\n", recv);
	if (!sock->writeMessage("OK"))
	    IlvPrint("error responding to client...\n");
    }
}
