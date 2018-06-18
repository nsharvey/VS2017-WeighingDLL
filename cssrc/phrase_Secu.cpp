// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\phrase_Secu.cpp
// IlogViews 5 generated source file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "phrase_Secu.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "phrase_Secu.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue May 11 17:33:38 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"phrase_Secu\"\nPathName \"C:\\\\e\\\\MyDevelopment\\\\centrale sarto modif\\\\IlogFile\\\\phrase_Secu.ilv\"\nPalettes 3\n1 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 0\n2 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 0 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 6\n1 { 0 0 IlvZoomableTransparentIcon 0 0 \"default\" F9.368497267142852 0 0 9.32937961027622 8 16 } 32 \"secu\"\n2\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.239918359243871 424 360 } 544 \"Descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.239918359243871 480 360 } 544 \"Monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.239918359243871 536 360 } 544 \"Aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.239891185331345 592 360 } 544 \"Quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n0\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvText 88 16 556 313 F129 2 N N 3 3 2 2 0 2\n\"Text\"\n\"multi lines\"\n0 0 0 0 } 32 \"PhraseSecu\"\n0\nSize 655 424\nBackground \"gray\"\nGeometryHandlers\n1 100 0 655 0 655 0\n6 3 8 0 8  75 0 75 0  572 0 572 0\n 3 88 0 88  556 0 556 5  11 0 11 0\n 3 424 0 424  50 0 50 1  181 0 181 0\n 3 480 0 480  50 0 50 2  125 0 125 0\n 3 536 0 536  50 0 50 3  69 0 69 0\n 3 592 0 592  50 0 50 4  13 0 13 0\n1 100 0 424 0 424"
" 0\n6 3 16 0 16  75 0 75 0  333 0 333 0\n 3 16 0 16  313 0 313 5  95 0 95 0\n 3 360 0 360  50 0 50 1  14 0 14 0\n 3 360 0 360  50 0 50 2  14 0 14 0\n 3 360 0 360  50 0 50 3  14 0 14 0\n 3 360 0 360  50 0 50 4  14 0 14 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_descendreCB(IlvGraphic* g, IlAny) {
    Phrase_Secu* o = (Phrase_Secu*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Phrase_Secu* o = (Phrase_Secu*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Phrase_Secu* o = (Phrase_Secu*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_monterCB(IlvGraphic* g, IlAny) {
    Phrase_Secu* o = (Phrase_Secu*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Phrase_Secu::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("descendreCB", _descendreCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("monterCB", _monterCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Phrase_Secu::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

void
Phrase_Secu::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Phrase_Secu::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Phrase_Secu::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

