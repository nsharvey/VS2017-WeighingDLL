// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\selection_LOT.cpp
// IlogViews 5 generated source file
// File generated Wed Feb 02 09:04:46 2011
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "selection_LOT.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "selection_LOT.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Wed Feb 02 09:04:46 2011\n// Creator class: IlvGadgetManagerOutput\nFileName \"selection_LOT\"\nPathName \"C:\\\\Développement ILOG\\\\V5.x - Révisions extraites\\\\centrale 150 sartorius + modif SMO\\\\IlogFile\\\\selection_LOT.ilv\"\nPalettes 3\n\"default\" 2 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 17\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 -8 736 376 F43352 2 N N 0 0 0 0 1 1 91 46 1 1 0 1 1 1 8 8 V0 2 8 0 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Lot\"  }  \n1 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&SousLot\"  }  \n2 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Emp\"  }  \n3 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QuantiteDisponible\"  }  \n4 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Alloue\"  }  \n5 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Peremp\"  }  \n6 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Titre\"  }  \n7 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Statut\"  }  \n0 N 0 0 0 1 0  } 32 \"listeSelectionLot\"\n0\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMatrix 0 0 736 374 F43352 2 N N 0 0 0 0 1 1 81 46 1 1 0 0 1 1 9 8 V0 2 9 0 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Cuve\"  }  \n1 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Vanne\"  }  \n2 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Lot\"  }  \n3 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&SousLot\"  }  \n4 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&QuantiteDisponible\"  }  \n5 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Alloue\"  }  \n6 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 "
"\"&Peremp\"  }  \n7 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Titre\"  }  \n8 0 448 IlvGadgetItemMatrixItem { IlvGadgetItem 1 2 4 \"&Statut\"  }  \n0 N 0 0 0 0 0  } 32 \"listeSelectionCuve\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 734 39 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.289333153394062 0 0 6.289299610133654 520 440 } 544 \"descendre\"\n1\n1 \"__ilvCallback\" \"descendreCB\"\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.289333153394062 0 0 6.289299610133654 576 440 } 544 \"monter\"\n1\n1 \"__ilvCallback\" \"monterCB\"\n0\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.24664982128191 0 0 6.289299610133654 464 440 } 544 \"valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n0\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.289333445795377 0 0 6.289274610135204 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n0\n1 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.289333153394062 0 0 6.289299610133654 632 440 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n0\n1 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.220024822043658 0 0 6.289299610133654 296 440 } 544 \"imprimer\"\n1\n1 \"__ilvCallback\" \"imprimerCB\"\n0\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.287799820104599 0 0 6.288057943543957 352 440 } 544 \"allouer\"\n1\n1 \"__ilvCallback\" \"allouerCB\"\n0\n1 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 168 384 172 30 "
"F14 2 1 -1 0 \"\" } 416 \"AffComposant\"\n0\n1 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 8 384 152 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Composant\"  }   } 0\n0\n1 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 352 384 152 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&ResteAPeser\"  }   } 0\n0\n1 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 688 384 48 30 F268435468 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"AffUS\"\n0\n1 { 14 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 512 384 172 30 F14 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffQuantite\"\n0\n1 { 15 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.287799819070716 0 0 6.288057943543957 408 440 } 544 \"desallouer\"\n1\n1 \"__ilvCallback\" \"desallouerCB\"\n0\n1 { 16 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n2 IlvZoomableTransparentIcon 0 0 \"default\" F6.287799819070716 0 0 6.288057943543957 240 440 } 544 \"consultationStockDetaille\"\n1\n1 \"__ilvCallback\" \"consultationStockDetailleCB\"\n0\nSize 742 545\nBackground \"gray\"\nGeometryHandlers\n2 100 0 55 0 55 0\n 0 0 687 55 687 55\n17 3 520 0 520  50 0 50 3  172 0 172 1\n 3 576 0 576  50 0 50 4  116 0 116 1\n 3 464 0 464  50 0 50 5  228 0 228 1\n 3 688 0 688  50 0 50 6  4 4 4 1\n 3 632 0 632  50 0 50 7  60 0 60 1\n 3 6 0 6  734 0 734 2  2 0 2 1\n 3 0 0 0  736 0 736 0  6 6 6 1\n 3 168 0 168  172 0 172 10  402 0 402 1\n 3 8 0 8  152 0 152 11  582 0 582 1\n 3 352 0 352  152 0 152 12  238 0 238 1\n 3 688 0 688  48 0 48 13  6 0 6 1\n 3 352 0 352  50 0 50 9  340 0 340 1\n 3 296 0 296  50 0 50 8  396 0 396 1\n 3 512 0 512  172 0 172 14  58 0 58 1\n 3 0 0 0  736 0 736 1  6 6 6 1\n 3 408 0 408  50 0 50 15  284 0 284 1\n 3 240 0 240  50 0 50 16  452 0 452 1\n0\n2 100 0 442 0 442 0\n 0 0 103 442 103 442\n17 3 440 0 "
"440  50 0 50 3  55 0 55 1\n 3 440 0 440  50 0 50 4  55 0 55 1\n 3 440 0 440  50 0 50 5  55 0 55 1\n 3 440 0 440  50 0 50 6  55 0 55 1\n 3 440 0 440  50 0 50 7  55 0 55 1\n 3 499 0 499  39 0 39 2  7 0 7 1\n 3 0 -8 -8  376 0 376 0  177 61 177 1\n 3 384 0 384  30 0 30 10  131 0 131 1\n 3 384 0 384  30 0 30 11  131 0 131 1\n 3 384 0 384  30 0 30 12  131 0 131 1\n 3 384 0 384  30 0 30 13  131 0 131 1\n 3 440 0 440  50 0 50 9  55 0 55 1\n 3 440 0 440  50 0 50 8  55 0 55 1\n 3 384 0 384  30 0 30 14  131 0 131 1\n 3 0 0 0  374 0 374 1  171 3 171 1\n 3 440 0 440  50 0 50 15  55 0 55 1\n 3 440 0 440  50 0 50 16  55 0 55 1\n0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_descendreCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->descendreCB(g);
}


static void ILVCALLBACK
_monterCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->monterCB(g);
}


static void ILVCALLBACK
_consultationStockDetailleCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->consultationStockDetailleCB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void ILVCALLBACK
_desallouerCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->desallouerCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_imprimerCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->imprimerCB(g);
}


static void ILVCALLBACK
_allouerCB(IlvGraphic* g, IlAny) {
    Selection_LOT* o = (Selection_LOT*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->allouerCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Selection_LOT::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("aideCB", _aideCB);
    registerCallback("descendreCB", _descendreCB);
    registerCallback("monterCB", _monterCB);
    registerCallback("consultationStockDetailleCB", _consultationStockDetailleCB);
    registerCallback("validerCB", _validerCB);
    registerCallback("desallouerCB", _desallouerCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("imprimerCB", _imprimerCB);
    registerCallback("allouerCB", _allouerCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Selection_LOT::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Selection_LOT::descendreCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : descendreCB method ...",className);
}

void
Selection_LOT::monterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : monterCB method ...",className);
}

void
Selection_LOT::consultationStockDetailleCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : consultationStockDetailleCB method ...",className);
}

void
Selection_LOT::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Selection_LOT::desallouerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : desallouerCB method ...",className);
}

void
Selection_LOT::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Selection_LOT::imprimerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : imprimerCB method ...",className);
}

void
Selection_LOT::allouerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : allouerCB method ...",className);
}

