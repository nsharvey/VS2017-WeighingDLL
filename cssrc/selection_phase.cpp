// -------------------------------------------------------------- -*- C++ -*-
// File: D:\MyDevelopment\centraleX3\cssrc\selection_phase.cpp
// IlogViews 5 generated source file
// File generated Fri Jun 04 13:03:47 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "selection_phase.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "selection_phase.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Fri Jun 04 13:03:47 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"selection_phase\"\nPathName \"D:\\\\MyDevelopment\\\\centraleX3\\\\IlogFile\\\\selection_phase.ilv\"\nPalettes 3\n\"default\" 2 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 7\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 0 736 376 F43352 2 N N 0 0 0 0 1 1 104 37 1 1 0 1 1 1 7 10 V0 2 7 0 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&NOF\"  }  \n1 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Phase\"  }   2 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Statut\"  }  \n3 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Date\"  }   4 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QteRest\"  }  \n5 0 192 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QteAllou\"  }   6 0 193 IlvGadgetItemMatrixItem { IlvGadgetItem 97 2 4 \"&Unite\"  }  \n0 N 0 0 0 1 0  } 32 \"listeSelectionPhase\"\n20480 \"quitter\"\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 733 41 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.12500014603138 0 0 6.25 519 440 } 544 \"descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n4096 \"valider\"\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.12500014603138 0 0 6.25 575 440 } 544 \"monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor"
" \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.12500014603138 0 0 6.25 463 440 } 544 \"valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n6144 \"descendre\" \"quitter\"\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.12500014603138 0 0 6.25 687 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n2048 \"valider\"\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.12500014603138 0 0 6.25 631 440 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\nSize 742 545\nBackground \"gray\"\nGeometryHandlers\n1 100 0 742 0 742 0\n7 3 519 0 519  49 0 49 2  174 0 174 0\n 3 575 0 575  49 0 49 3  118 0 118 0\n 3 463 0 463  49 0 49 4  230 0 230 0\n 3 687 0 687  49 0 49 5  6 0 6 0\n 3 631 0 631  49 0 49 6  62 0 62 0\n 3 6 0 6  733 0 733 1  3 0 3 0\n 3 0 0 0  736 0 736 0  6 6 6 0\n1 100 0 545 0 545 0\n7 3 440 0 440  50 0 50 2  55 0 55 0\n 3 440 0 440  50 0 50 3  55 0 55 0\n 3 440 0 440  50 0 50 4  55 0 55 0\n 3 440 0 440  50 0 50 5  55 0 55 0\n 3 440 0 440  50 0 50 6  55 0 55 0\n 3 499 0 499  41 0 41 1  5 0 5 0\n 3 0 0 0  376 0 376 0  169 0 169 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_descendreCB(IlvGraphic* g, IlAny) {
    Selection_phase* o = (Selection_phase*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Selection_phase* o = (Selection_phase*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Selection_phase* o = (Selection_phase*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Selection_phase* o = (Selection_phase*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_monterCB(IlvGraphic* g, IlAny) {
    Selection_phase* o = (Selection_phase*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Selection_phase::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("descendreCB", _descendreCB);
    registerCallback("validerCB", _validerCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("monterCB", _monterCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Selection_phase::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

void
Selection_phase::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Selection_phase::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Selection_phase::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Selection_phase::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

