// -------------------------------------------------------------- -*- C++ -*-
// File: D:\MyDevelopment\centraleX3\cssrc\selection_OF.cpp
// IlogViews 5 generated source file
// File generated Thu Jun 03 11:20:56 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "selection_OF.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "selection_OF.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Thu Jun 03 11:20:56 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"selection_OF\"\nPathName \"D:\\\\MyDevelopment\\\\centraleX3\\\\IlogFile\\\\selection_OF.ilv\"\nPalettes 3\n\"default\" 2 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 14\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 0 736 376 F43352 2 N N 0 0 0 0 1 1 104 37 1 0 0 1 1 1 7 10 V0 2 37 \n73 \n109 \n145 \n182 \n223 \n267 \n301 \n340 \n371 14 0 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&NOF\"  }  \n0 1 129 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 4 41 101 33 F268435468 0 { IlvMessageItem 262169 4 16 4 \"a\"  }   1  1 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Date\"  }   1 1 0 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 108 41 101 33 F268435468 0 { IlvMessageItem 262169 4 16 4 \"a\"  }   1  2 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Article\"  }  \n2 1 0 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 212 41 101 33 F268435468 0 { IlvMessageItem 262169 4 16 4 \"a\"  }   1  3 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Designation\"  }   3 1 0 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 316 41 101 33 F268435468 0 { IlvMessageItem 262169 4 16 4 \"a\"  }   1  4 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&TotPesee\"  }  \n4 1 0 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 420 41 101 33 F268435468 0 "
"{ IlvMessageItem 262169 4 16 4 \"a\"  }   1  5 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Unite\"  }   5 1 0 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 524 41 101 33 F268435468 0 { IlvMessageItem 262169 4 16 4 \"a\"  }   1  6 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Prio\"  }  \n6 1 0 IlvGadgetMatrixItem P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 628 41 101 33 F268435468 0 { IlvMessageItem 262169 4 16 4 \"a\"  }   1  0 N 0 0 0 1 0  } 32 \"listeSelectionOF\"\n6144 \"valider\" \"quitter\"\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.250000208616257 0 0 6.24999988079071 520 440 } 544 \"descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999955296516 0 0 6.24999988079071 576 440 } 544 \"monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999955296516 0 0 6.24999988079071 464 440 } 544 \"valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n4096 \"listeSelectionOF\"\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999761581421 0 0 6.249999895691873 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n2048 \"listeSelectionOF\"\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.250000186264515 0 0 6.249999940395354 632 440 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\n1 { 7 P 1\n[ "
"IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 1 381 1 2 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&NOF\"  }   } 0\n0\n1 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 16 378 1 1 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&Statut\"  }   } 0\n0\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 2 379 2 1 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&Article\"  }   } 0\n0\n1 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 2 376 2 1 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&Quantite\"  }   } 0\n0\n1 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 1 373 2 1 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&Unite\"  }   } 0\n0\n1 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 2 373 2 4 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&Date\"  }   } 0\n0\n1 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel -8 376 13 1 F268435468 0 { IlvMessageItem 262169 4 16 4 \"&Prio\"  }   } 0\n0\nSize 742 547\nBackground \"gray\"\nGeometryHandlers\n1 100 0 742 0 742 0\n7 3 520 0 520  50 0 50 2  172 0 172 0\n 3 576 0 576  50 0 50 3  116 0 116 0\n 3 464 0 464  50 0 50 4  228 0 228 0\n 3 688 0 688  50 0 50 5  4 0 4 0\n 3 632 0 632  50 0 50 6  60 0 60 0\n 3 0 0 6  734 0 734 1  0 0 2 0\n 3 0 0 0  736 0 736 0  0 6 6 0\n1 100 0 547 0 547 0\n7 3 440 0 440  50 0 50 2  57 0 57 0\n 3 440 0 440  50 0 50 3  57 0 57 0\n 3 440 0 440  50 0 50 4  57 0 57 0\n 3 440 0 440  50 0 50 5  57 0 57 0\n 3 440 0 440  50 0 50 6  57 0 57 0\n 3 499 0 499  41 0 41 1  0 0 7 0\n 3 0 0 0  376 0 376 0  171 3 171 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Selection_OF* o = (Selection_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Selection_OF* o = (Selection_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_descendreCB(IlvGraphic* g, IlAny) {
    Selection_OF* o = (Selection_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


static void ILVCALLBACK
_monterCB(IlvGraphic* g, IlAny) {
    Selection_OF* o = (Selection_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Selection_OF* o = (Selection_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Selection_OF::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("quitterCB", _quitterCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("descendreCB", _descendreCB);
    registerCallback("monterCB", _monterCB);
    registerCallback("validerCB", _validerCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Selection_OF::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Selection_OF::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Selection_OF::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

void
Selection_OF::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

void
Selection_OF::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

