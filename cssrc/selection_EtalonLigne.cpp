// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\selection_EtalonLigne.cpp
// IlogViews 5 generated source file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "selection_EtalonLigne.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "selection_EtalonLigne.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue May 11 17:33:38 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"selection_EtalonLigne\"\nPathName \"C:\\\\e\\\\MyDevelopment\\\\centrale sarto modif\\\\IlogFile\\\\selection_EtalonLigne.ilv\"\nPalettes 3\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 2 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 7\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 0 736 376 F43352 2 N N 0 0 0 0 1 1 182 37 1 0 0 1 1 1 4 10 V0 2 39 \n76 \n114 \n152 \n186 \n220 \n257 \n295 \n332 \n371 4 0 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 6 6 175 32 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&Etalon\"  }   1 \n1 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 188 6 175 32 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&TypePesee\"  }   1  2 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 370 6 175 32 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&Effectuee\"  }   1 \n3 0 480 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 552 6 175 32 F268435468 0 { IlvMessageItem 262145 4 16 4 \"&Validee\"  }   1  0 N 0 0 0 1 0  } 32 \"ListeSelectionLigne\"\n0\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262169 4 16 4 \"&SelectionnerLigneEtalonnage\"  }   } 32 \"Message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.249999940395355 520 440 } 544 \"descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty "
"__ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999940395355 0 0 6.25 576 440 } 544 \"monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.24999988079071 0 0 6.249999761581421 464 440 } 544 \"valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n0\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.24999988079071 0 0 6.249999761581421 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n0\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999940395355 0 0 6.25 632 440 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\nSize 742 545\nBackground \"gray\"\nGeometryHandlers\n1 100 0 742 0 742 0\n7 3 520 0 520  50 0 50 2  172 0 172 0\n 3 576 0 576  50 0 50 3  116 0 116 0\n 3 464 0 464  50 0 50 4  228 0 228 0\n 3 688 0 688  50 0 50 5  4 0 4 0\n 3 632 0 632  50 0 50 6  60 0 60 0\n 3 6 0 6  734 0 734 1  2 1 2 0\n 3 0 0 0  736 0 736 0  6 6 6 0\n1 100 0 545 0 545 0\n7 3 440 0 440  50 0 50 2  55 0 55 0\n 3 440 0 440  50 0 50 3  55 0 55 0\n 3 440 0 440  50 0 50 4  55 0 55 0\n 3 440 0 440  50 0 50 5  55 0 55 0\n 3 440 0 440  50 0 50 6  55 0 55 0\n 3 499 0 499  41 0 41 1  5 5 5 0\n 3 0 0 0  376 0 376 0  169 0 169 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_descendreCB(IlvGraphic* g, IlAny) {
    Selection_EtalonLigne* o = (Selection_EtalonLigne*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Selection_EtalonLigne* o = (Selection_EtalonLigne*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Selection_EtalonLigne* o = (Selection_EtalonLigne*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Selection_EtalonLigne* o = (Selection_EtalonLigne*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_monterCB(IlvGraphic* g, IlAny) {
    Selection_EtalonLigne* o = (Selection_EtalonLigne*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Selection_EtalonLigne::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("descendreCB", _descendreCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("validerCB", _validerCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("monterCB", _monterCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Selection_EtalonLigne::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

void
Selection_EtalonLigne::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Selection_EtalonLigne::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Selection_EtalonLigne::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Selection_EtalonLigne::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

