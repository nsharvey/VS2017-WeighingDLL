// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\selection_Balance.cpp
// RogueWaveViews 5 generated source file
// File generated Thu Sep 03 16:57:04 2015
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------
#include "selection_Balance.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "selection_Balance.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.6\n// File generated: Thu Sep 03 16:57:04 2015\n// Creator class: IlvGadgetManagerOutput\nFileName \"selection_Balance\"\nPathName \"C:\\\\Développement ILOG\\\\V5.x - Révisions extraites\\\\centrale 150 sartorius + modif SMO\\\\IlogFile\\\\selection_Balance.ilv\"\nPalettes 3\n\"default\" 2 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 7\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 0 736 376 F43352 2 N N 0 0 0 0 1 1 121 41 1 1 0 1 1 1 6 9 V0 2 6 0 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 6 6 114 34 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&NoBalance\"  }   1 \n1 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 127 6 114 34 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&DesBalance\"  }   1  2 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 248 6 114 34 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&PorteeMini\"  }   1  3 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 369 6 114 34 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&PorteeMaxi\"  }   1  4 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 490 6 114 34 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&TareMaxi\"  }   1 \n5 0 224 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 611 6 114 34 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&UnitePoids\"  }   1  0 N 0 0 0 1 0  } 32 \"listeSelectionBalance\"\n0\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor "
"\"Gadget\" ]\n1 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 520 440 } 544 \"Descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 576 440 } 544 \"Monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 464 440 } 544 \"valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n0\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 440 } 544 \"Quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n0\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 632 440 } 544 \"Aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\nSize 1048 859\nBackground \"gray\"\nGeometryHandlers\n1 100 0 742 0 742 0\n7 3 520 0 520  50 0 50 2  172 0 172 0\n 3 576 0 576  50 0 50 3  116 0 116 0\n 3 464 0 464  50 0 50 4  228 0 228 0\n 3 688 0 688  50 0 50 5  4 0 4 0\n 3 632 0 632  50 0 50 6  60 0 60 0\n 3 6 0 6  734 0 734 1  2 0 2 0\n 3 0 0 0  736 0 736 0  6 6 6 0\n1 100 0 545 0 545 0\n7 3 440 0 440  50 0 50 2  55 0 55 0\n 3 440 0 440  50 0 50 3  55 0 55 0\n 3 440 0 440  50 0 50 4  55 0 55 0\n 3 440 0 440  50 0 50 5  55 0 55 0\n 3 440 0 440  50 0 50 6  55 0 55 0\n 3 499 0 499  41 0 41 1  5 0 5 0\n 3 0 0 0  376 0 376 0  169 1 169 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void
_monterCB(IlvGraphic* g, IlAny) {
    Selection_Balance* o = (Selection_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


static void
_validerCB(IlvGraphic* g, IlAny) {
    Selection_Balance* o = (Selection_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void
_aideCB(IlvGraphic* g, IlAny) {
    Selection_Balance* o = (Selection_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void
_quitterCB(IlvGraphic* g, IlAny) {
    Selection_Balance* o = (Selection_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void
_descendreCB(IlvGraphic* g, IlAny) {
    Selection_Balance* o = (Selection_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Selection_Balance::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("monterCB", _monterCB);
    registerCallback("validerCB", _validerCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("descendreCB", _descendreCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Selection_Balance::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

void
Selection_Balance::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Selection_Balance::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Selection_Balance::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Selection_Balance::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

