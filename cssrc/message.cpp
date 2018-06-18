// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\message.cpp
// IlogViews 5 generated source file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "message.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "message.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue May 11 17:33:38 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"message\"\nPathName \"C:\\\\e\\\\MyDevelopment\\\\centrale sarto modif\\\\IlogFile\\\\message.ilv\"\nPalettes 2\n1 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 0 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 5\n1 { 0 0 IlvZoomableTransparentIcon 0 0 \"default\" F9.335194956390559 0 0 9.334765268906951 8 16 } 32 \"secu\"\n2\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 90 28 549 50 F268435468 0 { IlvMessageItem 262169 4 16 4 \"MessageLabel\"  }   } 32 \"Message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvButton 128 104 120 53 F13 2 { IlvMessageItem 262145 4 16 4 \"&OUI\"  }   } 544 \"BoutonOui\"\n1\n1 \"__ilvCallback\" \"BoutonCB\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvButton 400 104 120 53 F13 2 { IlvMessageItem 262145 4 16 4 \"&NON\"  }   } 544 \"BoutonNon\"\n1\n1 \"__ilvCallback\" \"BoutonCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvButton 264 104 120 53 F13 2 { IlvMessageItem 262145 4 16 4 \"&OK\"  }   } 544 \"BoutonOK\"\n1\n1 \"__ilvCallback\" \"BoutonCB\"\n0\nSize 646 190\nBackground \"gray\"\nGeometryHandlers\n1 100 0 646 0 646 0\n5 3 8 0 8  75 0 75 0  563 0 563 0\n 3 90 0 90  549 0 549 1  7 1 7 0\n 3 128 0 128  120 0 120 2  398 0 398 0\n 3 264 0 264  120 0 120 4  262 0 262 0\n 3 400 0 400  120 0 120 3  126 0 126 0\n1 100 0 190 0 190 0\n5 3 16 0 16  75 0 75 0  99 0 99 0\n 3 28 0 28  50 0 50 1  112 0 112 0\n 3 104 0 104  53 0 53 2  33 0 33 0\n 3 104 0 104  53 0 53 4  33 0 33 0\n 3 104 0 104  53 0 53 3  33 0 33 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_BoutonCB(IlvGraphic* g, IlAny) {
    Message* o = (Message*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->BoutonCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Message::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("BoutonCB", _BoutonCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Message::BoutonCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : BoutonCB method ...",className);
}

