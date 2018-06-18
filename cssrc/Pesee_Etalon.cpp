// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\Pesee_Etalon.cpp
// IlogViews 5 generated source file
// File generated Tue Sep 24 15:20:40 2013
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "Pesee_Etalon.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "Pesee_Etalon.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue Sep 24 15:20:40 2013\n// Creator class: IlvGadgetManagerOutput\nFileName \"Pesee_Etalon\"\nPathName \"C:\\\\Développement ILOG\\\\V5.x - Révisions extraites\\\\centrale 150 sartorius + modif SMO\\\\IlogFile\\\\Pesee_Etalon.ilv\"\nPalettes 6\n1 F \"darkslateblue\" 65025 65025 65025 \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n5 F \"gray\" \"black\" \"%Arial-16-B[Charset:0]\" 0 solid solid 0 0 0 65535 0\n3 F \"lightblue\" \"yellow\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n2 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"IlvStToolBar\" 4 F \"gray\" \"black\" \"normal\" \"%Tahoma-11-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 0 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 37\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 384 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n6144 \"quitter\" \"Tactile\"\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 216 } 544 \"Tactile\"\n1\n1 \"__ilvCallback\" \"tactileCB\"\n6144 \"aide\" \"Valider\"\n0 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 96 } 544 \"Valider\"\n1\n1 \"__ilvCallback\" \"validerCB\"\n6144 \"Tactile\" \"PoidsPese\"\n0 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F3.75 0 0 3.75 616 176 } 544 \"listerEtalonLignes\"\n1\n1 \"__ilvCallback\" \"listerEtalonCB\"\n6144 \"PoidsPese\" \"TypePesee\"\n0 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 272 } 544 "
"\"mettreAZero\"\n1\n1 \"__ilvCallback\" \"mettreAZeroCB\"\n0\n0 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n6144 \"PoidsEtalon\" \"aide\"\n1 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"Message\"\n0\n1 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 160 8 142 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Balance\"  }   } 32 \"LabelBalance\"\n0\n1 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 312 8 163 30 F6 2 1 -1 0 \"\" } 416 \"AffBalance\"\n16384\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 160 56 144 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&FicheEtalon\"  }   } 32 \"LabelFicheEtalon\"\n0\n1 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 144 176 160 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Poids/Type\"  }   } 32 \"LabelPoidsType\"\n0\n1 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 144 224 160 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PctTolerance\"  }   } 32 \"LabelPctTolerance\"\n0\n1 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 312 56 124 30 F6 2 1 -1 0 \"\" } 416 \"AffFicheEtalon\"\n16384\n1 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gauge\" ]\n3 IlvRectangularGauge 88 8 39 466 0 100 80 8 1 } 32 \"JaugePesee\"\n16384\n1 { 14 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 144 336 160 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsPese\"  }   } 32 \"LabelPoidsPese\"\n0\n1 { 15 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 "
"IlvMessageLabel 144 384 160 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsAPeser\"  }   } 32 \"LabelPoidsAPeser\"\n0\n1 { 16 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 144 432 160 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&EcartPoids\"  }   } 32 \"LabelEcartPoids\"\n0\n1 { 17 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 160 104 144 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Compteur\"  }   } 32 \"LabelCompteur\"\n0\n1 { 18 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 312 104 65 30 F6 2 2 -1 0 \"\" } 416 \"AffCompteur\"\n16384\n1 { 19 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n4 IlvFrame 150 0 594 152 F268435468 0 { IlvMessageItem 262168 4 16 4  }   } 0\n0\n1 { 20 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 440 56 272 30 F6 2 1 -1 0 \"\" } 416 \"AffDesFiche\"\n0\n1 { 21 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 480 336 70 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"LabelUnPesee\"\n0\n1 { 22 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 480 384 70 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"LabelUnAPeser\"\n0\n1 { 23 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 480 432 70 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"LabelUnEcart\"\n0\n1 { 24 0 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 512 0 } 32 \"Lighton\"\n0\n1 { 25 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvNumberField 312 224 170 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"PctTolerance\"\n0\n1 { 26 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvNumberField 312 384 170 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 "
"3.40282e+038 } 416 \"PoidsAPeser\"\n0\n1 { 27 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvNumberField 312 432 170 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"EcartPoids\"\n0\n1 { 28 5 IlvRectangularScale 75 9 10 462 5 2 10 5 M 0 100 \"%4.f\"\n\"   0.0000\" \"  25.0000\" \"  50.0000\" \"  75.0000\" \" 100.0000\"  85 471 462 8 1  } 32 \"JaugeScale\"\n0\n1 { 29 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n4 IlvFrame 0 0 140 488 F268435468 0 { IlvMessageItem 262168 4 16 4  }   } 0\n0\n1 { 30 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 448 176 160 30 F6 2 1 -1 0 \"\" } 416 \"LibTypPesee\"\n0\n1 { 31 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvNumberField 312 176 132 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"PoidsEtalon\"\n0\n1 { 32 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 328 } 544 \"peser\"\n1\n1 \"__ilvCallback\" \"peserCB\"\n0\n1 { 33 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 144 272 160 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NbPesees\"  }   } 32 \"LabelcompteurPesees\"\n0\n1 { 34 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 312 272 65 30 F6 2 2 -1 0 \"\" } 416 \"AffCompteurPesees\"\n16384\n1 { 35 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvNumberField 312 336 170 30 F6 2 2 -1 0 \"0\" . , 2 16 -3.4e+038 3.4e+038 } 544 \"PoidsPese\"\n2\n1 \"__ilvCallback\" \"poidsPeseCB\"\n1 \"__ilvFocusIn\" \"EntreeNumberFieldCB\"\n0\n1 { 36 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 480 8 232 30 F6 2 1 -1 0 \"\" } 416 \"AffLibBalance\"\n16384\nSize 749 545\nBackground \"gray\"\nGeometryHandlers\n1 100 0 749 0 749 0\n37 3 160 0 160  142 0 142 7  447 0 447 "
"0\n 3 160 0 160  144 0 144 9  445 0 445 0\n 3 144 0 144  160 0 160 10  445 0 445 0\n 3 144 0 144  160 0 160 11  445 0 445 0\n 3 312 0 312  163 0 163 8  274 0 274 0\n 3 312 0 312  124 0 124 12  313 0 313 0\n 3 688 0 688  50 0 50 0  11 0 11 0\n 3 688 0 688  50 0 50 5  11 0 11 0\n 3 6 0 6  734 0 734 6  9 0 9 0\n 3 88 0 88  39 0 39 13  622 0 622 0\n 3 144 0 144  160 0 160 14  445 0 445 0\n 3 144 0 144  160 0 160 15  445 0 445 0\n 3 144 0 144  160 0 160 16  445 0 445 0\n 3 440 0 440  272 0 272 20  37 0 37 0\n 3 312 0 312  65 0 65 18  372 0 372 0\n 3 160 0 160  144 0 144 17  445 0 445 0\n 3 150 0 150  594 0 594 19  5 0 5 0\n 3 616 0 616  30 0 30 3  103 0 103 0\n 3 688 0 688  50 0 50 2  11 0 11 0\n 3 688 0 688  50 0 50 1  11 0 11 0\n 3 512 0 512  1 0 1 24  236 0 236 0\n 3 688 0 688  50 0 50 4  11 0 11 0\n 3 480 0 480  70 0 70 21  199 0 199 0\n 3 480 0 480  70 0 70 22  199 0 199 0\n 3 480 0 480  70 0 70 23  199 0 199 0\n 3 312 0 312  170 0 170 25  267 0 267 0\n 3 312 0 312  170 0 170 26  267 0 267 0\n 3 312 0 312  170 0 170 27  267 0 267 0\n 3 0 0 0  86 0 86 28  663 0 663 0\n 3 0 0 0  140 0 140 29  609 0 609 0\n 3 448 0 448  160 0 160 30  141 0 141 0\n 3 312 0 312  132 0 132 31  305 0 305 0\n 3 688 0 688  50 0 50 32  11 0 11 0\n 3 312 0 312  65 0 65 34  372 0 372 0\n 3 144 0 144  160 0 160 33  445 0 445 0\n 3 312 0 312  170 0 170 35  267 0 267 0\n 3 480 0 480  232 0 232 36  37 0 37 0\n1 100 0 545 0 545 0\n37 3 0 0 8  30 0 30 7  507 0 507 0\n 3 56 0 56  30 0 30 9  459 0 459 0\n 3 176 0 176  30 0 30 10  339 0 339 0\n 3 224 0 224  30 0 30 11  291 0 291 0\n 3 0 0 8  30 0 30 8  507 0 507 0\n 3 56 0 56  30 0 30 12  459 0 459 0\n 3 384 0 384  50 0 50 0  111 0 111 0\n 3 440 0 440  50 0 50 5  55 0 55 0\n 3 499 0 499  41 0 41 6  5 0 5 0\n 3 0 0 8  466 0 466 13  71 0 71 0\n 3 336 0 336  30 0 30 14  179 0 179 0\n 3 384 0 384  30 0 30 15  131 0 131 0\n 3 432 0 432  30 0 30 16  83 0 83 0\n "
"3 56 0 56  30 0 30 20  459 0 459 0\n 3 104 0 104  30 0 30 18  411 0 411 0\n 3 104 0 104  30 0 30 17  411 0 411 0\n 3 0 0 0  152 0 152 19  393 0 393 0\n 3 176 0 176  30 0 30 3  339 0 339 0\n 3 96 0 96  50 0 50 2  399 0 399 0\n 3 216 0 216  50 0 50 1  279 0 279 0\n 3 0 0 0  1 0 1 24  544 0 544 0\n 3 272 0 272  50 0 50 4  223 0 223 0\n 3 336 0 336  30 0 30 21  179 0 179 0\n 3 384 0 384  30 0 30 22  131 0 131 0\n 3 432 0 432  30 0 30 23  83 0 83 0\n 3 224 0 224  30 0 30 25  291 0 291 0\n 3 384 0 384  30 0 30 26  131 0 131 0\n 3 432 0 432  30 0 30 27  83 0 83 0\n 3 0 0 0  482 0 482 28  63 0 63 0\n 3 0 0 0  488 0 488 29  57 0 57 0\n 3 176 0 176  30 0 30 30  339 0 339 0\n 3 176 0 176  30 0 30 31  339 0 339 0\n 3 328 0 328  50 0 50 32  167 0 167 0\n 3 272 0 272  30 0 30 34  243 0 243 0\n 3 272 0 272  30 0 30 33  243 0 243 0\n 3 336 0 336  30 0 30 35  179 0 179 0\n 3 0 0 8  30 0 30 36  507 0 507 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_mettreAZeroCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->mettreAZeroCB(g);
}


static void ILVCALLBACK
_poidsPeseCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->poidsPeseCB(g);
}


static void ILVCALLBACK
_listerEtalonCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->listerEtalonCB(g);
}


static void ILVCALLBACK
_EntreeNumberFieldCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->EntreeNumberFieldCB(g);
}


static void ILVCALLBACK
_peserCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->peserCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_tactileCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->tactileCB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Pesee_Etalon* o = (Pesee_Etalon*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Pesee_Etalon::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("mettreAZeroCB", _mettreAZeroCB);
    registerCallback("poidsPeseCB", _poidsPeseCB);
    registerCallback("listerEtalonCB", _listerEtalonCB);
    registerCallback("EntreeNumberFieldCB", _EntreeNumberFieldCB);
    registerCallback("peserCB", _peserCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("tactileCB", _tactileCB);
    registerCallback("validerCB", _validerCB);
    registerCallback("aideCB", _aideCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Pesee_Etalon::mettreAZeroCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : mettreAZeroCB method ...",className);
}

void
Pesee_Etalon::poidsPeseCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : poidsPeseCB method ...",className);
}

void
Pesee_Etalon::listerEtalonCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : listerEtalonCB method ...",className);
}

void
Pesee_Etalon::EntreeNumberFieldCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : EntreeNumberFieldCB method ...",className);
}

void
Pesee_Etalon::peserCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : peserCB method ...",className);
}

void
Pesee_Etalon::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Pesee_Etalon::tactileCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : tactileCB method ...",className);
}

void
Pesee_Etalon::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Pesee_Etalon::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

