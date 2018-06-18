// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/socket/src/testclnt.cpp
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
// Testing the IlvClientSocket class
// To be used in conjunction with testserver
// --------------------------------------------------------------------------

#include <ilvsock/client.h>
#include <ilviews/ilv.h>
#if defined(IL_STD)
#include <cstdlib>
#include <cstdio>
IL_STDUSE
#else  /* !IL_STD */
#include <stdlib.h>
#include <stdio.h>
#endif /* !IL_STD */
#if defined(WINDOWS)
#if defined(_MSC_VER)
#define sleep _sleep
#endif /* _MSC_VER */
#if defined(__BORLANDC__)
#include <dos.h>
#endif /* __BORLANDC__ */
#else  /* !WINDOWS */
#include <unistd.h>
#endif /* !WINDOWS */

#define USE_AF_INET
#define PORT 5101
#define TMPFILE "/tmp/ilv.sock"
// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
#if defined(WINDOWS) || defined(USE_AF_INET)
    IlvClientSocket client(PORT, (argc > 1) ? argv[1] : 0);
#else  /* !WINDOWS && !USE_AF_INET */
    IlvClientSocket client(TMPFILE);
#endif /* !WINDOWS && !USE_AF_INET */
    if (client.isBad()) {
	IlvFatalError("Invalid client...\n");
	return 1;
    }
    char    buffer[80];
    int     i = 0;
    char*   message;
    IlUInt count = 0;
    while(1) {
#if defined(WINDOWS) && defined(_MSC_VER) && (_MSC_VER >= 1400) /* x86_.net2005_8.0 or higher */
	Sleep(1);
#else /* x86_.net2003_7.1 or lower for windows, or any Unix/Linux ports */
	sleep(1);
#endif
	sprintf(buffer, "Client Request %d.\n", i++);
	if (!client.writeMessage(buffer) ||
	    ((message = client.readMessage(count)) == 0))
	    break;
	IlvPrint("Receiving %s.", message);
    }
    IlvPrint("Exiting...");
    return 0;
}
