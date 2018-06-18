// -------------------------------------------------------------- -*- C++ -*-
// File: D:\MyDevelopment\centraleX3\cssrc\selection_MWF.cpp
// IlogViews 5 generated source file
// File generated Thu Aug 19 16:56:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "selection_MWF.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "selection_MWF.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Thu Aug 19 16:56:38 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"selection_MWF\"\nPathName \"D:\\\\MyDevelopment\\\\centraleX3\\\\IlogFile\\\\selection_MWF.ilv\"\nPalettes 3\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 2 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 7\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 0 736 376 F43352 2 N N 0 0 0 0 1 1 104 37 1 1 0 1 1 1 7 10 V0 2 7 0 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Composant\"  }  \n1 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Designation\"  }   2 0 192 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QuantiteAPeser\"  }  \n3 0 192 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QteRest\"  }   4 0 192 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QteAllou\"  }  \n5 0 192 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QuantiteDisponible\"  }   6 0 192 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Unite\"  }  \n0 N 0 0 0 1 0  } 32 \"listeSelectionMWF\"\n0\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262169 4 16 4 \"SelectionnezComposant\"  }   } 32 \"message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999940395355 0 0 6.249999940395355 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999895691872 0 0 6.25 520 440 } 544 \"descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 "
"\"default\" F6.249999940395355 0 0 6.24999988079071 576 440 } 544 \"monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.250000007450582 0 0 6.250000149011612 464 440 } 544 \"valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n0\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999895691872 0 0 6.249999940395355 632 440 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\nSize 742 545\nBackground \"gray\"\nGeometryHandlers\n2 100 0 490 0 490 0\n 0 0 252 490 252 490\n7 3 688 0 688  50 0 50 2  4 0 4 1\n 3 6 0 6  734 0 734 1  2 0 2 1\n 3 0 0 0  736 0 736 0  6 6 6 1\n 3 632 0 632  50 0 50 6  60 0 60 1\n 3 576 0 576  50 0 50 4  116 0 116 1\n 3 520 0 520  50 0 50 3  172 0 172 1\n 3 464 0 464  50 0 50 5  228 0 228 1\n0\n2 100 0 464 0 464 0\n 0 0 81 464 81 464\n7 3 440 0 440  50 0 50 2  55 0 55 1\n 3 499 0 499  41 0 41 1  5 0 5 1\n 3 0 0 0  376 0 376 0  169 0 169 1\n 3 440 0 440  50 0 50 6  55 0 55 1\n 3 440 0 440  50 0 50 4  55 0 55 1\n 3 440 0 440  50 0 50 3  55 0 55 1\n 3 440 0 440  50 0 50 5  55 0 55 1\n0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_monterCB(IlvGraphic* g, IlAny) {
    Selection_MWF* o = (Selection_MWF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Selection_MWF* o = (Selection_MWF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_descendreCB(IlvGraphic* g, IlAny) {
    Selection_MWF* o = (Selection_MWF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Selection_MWF* o = (Selection_MWF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Selection_MWF* o = (Selection_MWF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Selection_MWF::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("monterCB", _monterCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("descendreCB", _descendreCB);
    registerCallback("validerCB", _validerCB);
    registerCallback("aideCB", _aideCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Selection_MWF::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

void
Selection_MWF::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Selection_MWF::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

void
Selection_MWF::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Selection_MWF::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

