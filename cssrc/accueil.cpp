// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\accueil.cpp
// IlogViews 5 generated source file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "accueil.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "accueil.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue May 11 17:33:38 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"accueil\"\nPathName \"C:\\\\e\\\\MyDevelopment\\\\centrale sarto modif\\\\IlogFile\\\\accueil.ilv\"\nPalettes 3\n2 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n1 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 0 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 23\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.19775452619344 0 0 6.257379628667235 632 328 } 544 \"peserOF\"\n1\n1 \"__ilvCallback\" \"peserOFCB\"\n6144 \"peserArticle\" \"quitter\"\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.285070649823546 0 0 6.235576744675637 632 440 } 544 \"peserFabrication\"\n1\n1 \"__ilvCallback\" \"peserFabricationCB\"\n6144 \"testerBalance\" \"peserArticle\"\n0 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.289315932771563 0 0 6.232211360156536 688 328 } 544 \"reconcilier\"\n1\n1 \"__ilvCallback\" \"reconcilierCB\"\n6144 \"aide\" \"testerBalance\"\n0 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.245683858028055 0 0 6.311004909484089 688 384 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n6144 \"quitter\" \"reconcilier\"\n0 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.246367820280791 0 0 6.216057514464855 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n6144 \"peserOF\" \"aide\"\n0 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.295966876056791 0 0 6.238797898429632 632 384 } 544 \"peseeArticle\"\n1\n1"
" \"__ilvCallback\" \"peserArticleCB\"\n0\n0 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.289292347866297 0 0 6.232187321695686 688 272 } 544 \"testerBalance\"\n1\n1 \"__ilvCallback\" \"testerBalanceCB\"\n0\n0 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n0 IlvZoomableTransparentIcon 0 0 \"default\" F6.232187024521837 0 0 6.21418411566349 632 272 } 544 \"refresh\"\n1\n1 \"__ilvCallback\" \"refreshCB\"\n0\n1 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n1 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 32 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Utilisateur\"  }   } 32 \"LibUtilisateur\"\n0\n1 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 248 32 170 40 F536870918 2 1 -1 0 \"\" } 32 \"ChampUtilisateur\"\n6144 \"saisieBadge\" \"quitter\"\n1 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 248 80 296 40 F536870918 2 1 -1 0 \"\" } 416 \"ChampApplication\"\n0\n1 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 128 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Date\"  }   } 32 \"LibDate\"\n0\n1 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 232 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Lieu\"  }   } 32 \"LibLieu\"\n0\n1 { 14 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 248 232 170 40 F536870918 2 1 -1 0 \"\" } 416 \"ChampLieu\"\n0\n1 { 15 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 280 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Box\"  }   } 32 \"LibBox\"\n0\n1 { 16 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 248 280 170 40 F536870918 2 1 -1 0 \"\" } 416 \"ChampBox"
"\"\n0\n1 { 17 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 328 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Balancesconnectees\"  }   } 32 \"LibConnection\"\n0\n1 { 18 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 248 328 170 40 F536870918 2 1 -1 0 \"\" } 416 \"ChampConnection\"\n0\n1 { 19 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 376 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&BalancesAEtalonner\"  }   } 32 \"LibEtalonnage\"\n0\n1 { 20 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvTextField 248 376 170 40 F536870918 2 1 -1 0 \"\" } 416 \"ChampEtalonnage\"\n0\n1 { 21 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvDateField 248 128 170 40 F15 2 1 0 0 \"31/12/2000\" / 1 3 7 } 416 \"ChampDate\"\n0\n1 { 22 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 80 230 40 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Application\"  }   } 32 \"LibApplication\"\n0\nSize 741 543\nBackground \"gray\"\nGeometryHandlers\n1 100 0 741 0 741 0\n23 3 688 0 688  50 0 50 3  3 0 3 0\n 3 0 0 6  734 0 734 8  0 0 1 0\n 3 632 0 632  50 0 50 0  59 0 59 0\n 3 688 0 688  50 0 50 4  0 0 3 0\n 3 632 0 632  50 0 50 1  59 0 59 0\n 3 6 0 6  230 0 230 9  505 0 505 0\n 3 6 0 6  230 0 230 12  505 0 505 0\n 3 248 0 248  170 0 170 10  323 0 323 0\n 3 248 0 248  296 0 296 11  197 0 197 0\n 3 6 0 6  230 0 230 13  505 0 505 0\n 3 6 0 6  230 0 230 15  505 0 505 0\n 3 6 0 6  230 0 230 17  505 0 505 0\n 3 248 0 248  170 0 170 14  323 0 323 0\n 3 248 0 248  170 0 170 16  323 0 323 0\n 3 248 0 248  170 0 170 18  323 0 323 0\n 3 6 0 6  230 0 230 19  505 0 505 0\n 3 248 0 248  170 0 170 20  323 0 323 0\n 3 248 0 248  170 0 170 21  323 0 323 0\n 3 688 0 688  50 0 50 2  3 0 3 0\n 3 6 0 6  230 0 230 22  505 0 505 0\n 3 632 0 632  50 0 50 5  59 0 59 0\n 3 688 0 688  50 0 50 6  3 0 3 0\n 3 632 0 632  50 0 50 7  59 0 59"
" 0\n1 100 0 543 0 543 0\n23 3 384 0 384  50 0 50 3  109 0 109 0\n 3 440 0 440  50 0 50 4  53 0 53 0\n 3 499 0 499  41 0 41 8  0 0 3 0\n 3 328 0 328  50 0 50 0  165 0 165 0\n 3 440 0 440  50 0 50 1  53 0 53 0\n 3 32 0 32  40 0 40 9  471 0 471 0\n 3 128 0 128  40 0 40 12  375 0 375 0\n 3 32 0 32  40 0 40 10  471 0 471 0\n 3 80 0 80  40 0 40 11  423 0 423 0\n 3 232 0 232  40 0 40 13  271 0 271 0\n 3 280 0 280  40 0 40 15  223 0 223 0\n 3 328 0 328  40 0 40 17  175 0 175 0\n 3 232 0 232  40 0 40 14  271 0 271 0\n 3 280 0 280  40 0 40 16  223 0 223 0\n 3 328 0 328  40 0 40 18  175 0 175 0\n 3 376 0 376  40 0 40 19  127 0 127 0\n 3 376 0 376  40 0 40 20  127 0 127 0\n 3 128 0 128  40 0 40 21  375 0 375 0\n 3 328 0 328  50 0 50 2  165 0 165 0\n 3 80 0 80  40 0 40 22  423 0 423 0\n 3 384 0 384  50 0 50 5  109 0 109 0\n 3 272 0 272  50 0 50 6  221 0 221 0\n 3 272 0 272  50 0 50 7  221 0 221 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_reconcilierCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->reconcilierCB(g);
}


static void ILVCALLBACK
_peserOFCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->peserOFCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_refreshCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->refreshCB(g);
}


static void ILVCALLBACK
_testerBalanceCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->testerBalanceCB(g);
}


static void ILVCALLBACK
_peserFabricationCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->peserFabricationCB(g);
}


static void ILVCALLBACK
_peserArticleCB(IlvGraphic* g, IlAny) {
    Accueil* o = (Accueil*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->peserArticleCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Accueil::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("quitterCB", _quitterCB);
    registerCallback("reconcilierCB", _reconcilierCB);
    registerCallback("peserOFCB", _peserOFCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("refreshCB", _refreshCB);
    registerCallback("testerBalanceCB", _testerBalanceCB);
    registerCallback("peserFabricationCB", _peserFabricationCB);
    registerCallback("peserArticleCB", _peserArticleCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Accueil::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Accueil::reconcilierCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : reconcilierCB method ...",className);
}

void
Accueil::peserOFCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : peserOFCB method ...",className);
}

void
Accueil::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Accueil::refreshCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : refreshCB method ...",className);
}

void
Accueil::testerBalanceCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : testerBalanceCB method ...",className);
}

void
Accueil::peserFabricationCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : peserFabricationCB method ...",className);
}

void
Accueil::peserArticleCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : peserArticleCB method ...",className);
}

