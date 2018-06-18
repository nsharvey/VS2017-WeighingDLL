// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\recontrole_OF.cpp
// RogueWaveViews 5 generated source file
// File generated Mon Dec 21 11:57:35 2015
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------
#include "recontrole_OF.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "recontrole_OF.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.6\n// File generated: Mon Dec 21 11:57:35 2015\n// Creator class: IlvGadgetManagerOutput\nFileName \"recontrole_OF\"\nPathName \"C:\\\\Développement ILOG\\\\V5.x - Révisions extraites\\\\centrale 150 sartorius + modif SMO\\\\IlogFile\\\\recontrole_OF.ilv\"\nPalettes 4\n\"default\" 3 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n1 F \"darkslateblue\" 65025 65025 65025 \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"IlvStToolBar\" 2 F \"gray\" \"black\" \"normal\" \"%Tahoma-11-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 14\n1 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 8 129 138 39 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Composant\"  }   } 32 \"LibelleComposant\"\n0\n1 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 329 749 49 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 7 200 139 39 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Lot\"  }   } 32 \"LibelleLot\"\n0\n1 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 12 59 126 39 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NOF\"  }   } 0\n0\n1 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 156 59 166 39 F6 2 1 -1 0 \"\" } 416 \"AffNOF\"\n20480 \"SaisieLot\"\n1 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvFrame 12 59 404 59 F268435468 0 { IlvMessageItem 262168 4 16 4  }   } 0\n0\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 7 259 139 39 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&SousLot\"  }   } 32 \"LibelleSousLot\"\n0\n1 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 340 59 56 39 F6 2 2 -1 0 \"0\" . , 0 16 -3e+038 3e+038 } 416 \"AffNPhase\"\n0\n1 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 156 129 236 39 F6 2 1 -1 0 \"\" } 544 \"SaisieComposant\"\n2\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieComposantCB\"\n20480 \"SaisiContenuCab\"\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 156 200 236 39 F6 2 1 -1 0 \"\" } 544 \"SaisieLot\"\n2\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieLotCB\"\n20480 \"SaisieComposant\"\n1 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n3 IlvZoomableTransparentIcon 0 0 \"default\" F7.344703500000001 0 0 7.353110999999999 679 143.1258666666667 } 544 \"Tactile\"\n1\n1 \"__ilvCallback\" \"TactileCB\"\n20480 \"codeBalance\"\n1 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n3 IlvZoomableTransparentIcon 0 0 \"default\" F7.398668833333334 0 0 7.331972531165311 679 239.1248433604335 } 544 \"Quitter\"\n1\n1 \"__ilvCallback\" \"QuitterCB\"\n20480 \"Tactile\"\n1 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 156 259 236 39 F6 2 1 -1 0 \"\" } 544 \"SaisieSousLot\"\n2\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieSousLotCB\"\n20480 \"SaisieLot\"\n1 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 12 8 404 35 F6 2 1 -1 0 \"\" } 544 \"SaisiContenuCab\"\n2\n1 \"__ilvCallback\" \"SaisiContenuCabCB\"\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n16384\nSize 773 400\nBackground \"gray\"\nGeometryHandlers\n1 100 0 773 0 773 0\n14 3 8 0 8  138 0 138 0  627 0 627 0\n 3 6 0 6  749 0 749 1  18 0 18 0\n 3 12 0 12  126 0 126 3  635 0 635 0\n 3 156 0 156  166 0 166 4  451 0 451 0\n 3 12 0 12  404 0 404 5  357 0 357 0\n 3 7 0 7  139 0 139 2  627 0 627 0\n 3 679 0 679  59 0 59 10  35 3 35 0\n 3 679 0 679  59 0 59 11  35 0 35 0\n 3 156 0 156  236 0 236 9  381 0 381 0\n 3 156 0 156  236 0 236 8  381 0 381 0\n 3 7 0 7  139 0 139 6  627 0 627 0\n 3 340 0 340  56 0 56 7  377 0 377 0\n 3 156 0 156  236 0 236 12  381 0 381 0\n 3 12 0 12  404 0 404 13  357 0 357 0\n1 100 0 400 0 400 0\n14 3 129 0 129  39 0 39 0  232 0 232 0\n 3 329 0 329  49 0 49 1  22 0 22 0\n 3 59 0 59  39 0 39 3  302 0 302 0\n 3 59 0 59  39 0 39 4  302 0 302 0\n 3 59 0 59  59 0 59 5  282 0 282 0\n 3 200 0 200  39 0 39 2  161 0 161 0\n 3 143 0 143  59 0 59 10  198 196 198 0\n 3 239 0 239  59 0 59 11  102 92 102 0\n 3 200 0 200  39 0 39 9  161 0 161 0\n 3 129 0 129  39 0 39 8  232 0 232 0\n 3 259 0 259  39 0 39 6  102 0 102 0\n 3 59 0 59  39 0 39 7  302 0 302 0\n 3 259 0 259  39 0 39 12  102 0 102 0\n 3 0 0 8  35 0 35 13  357 0 357 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void
_SaisieLotCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieLotCB(g);
}


static void
_SaisieSousLotCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieSousLotCB(g);
}


static void
_QuitterCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->QuitterCB(g);
}


static void
_SaisiContenuCabCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisiContenuCabCB(g);
}


static void
_EntreeTextFieldCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->EntreeTextFieldCB(g);
}


static void
_TactileCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->TactileCB(g);
}


static void
_SaisieComposantCB(IlvGraphic* g, IlAny) {
    Recontrole_OF* o = (Recontrole_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieComposantCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Recontrole_OF::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("SaisieLotCB", _SaisieLotCB);
    registerCallback("SaisieSousLotCB", _SaisieSousLotCB);
    registerCallback("QuitterCB", _QuitterCB);
    registerCallback("SaisiContenuCabCB", _SaisiContenuCabCB);
    registerCallback("EntreeTextFieldCB", _EntreeTextFieldCB);
    registerCallback("TactileCB", _TactileCB);
    registerCallback("SaisieComposantCB", _SaisieComposantCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Recontrole_OF::SaisieLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieLotCB method ...",className);
}

void
Recontrole_OF::SaisieSousLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieSousLotCB method ...",className);
}

void
Recontrole_OF::QuitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : QuitterCB method ...",className);
}

void
Recontrole_OF::SaisiContenuCabCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisiContenuCabCB method ...",className);
}

void
Recontrole_OF::EntreeTextFieldCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : EntreeTextFieldCB method ...",className);
}

void
Recontrole_OF::TactileCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : TactileCB method ...",className);
}

void
Recontrole_OF::SaisieComposantCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieComposantCB method ...",className);
}

