// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\Choix_Balance.cpp
// IlogViews 5 generated source file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "Choix_Balance.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "Choix_Balance.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue May 11 17:33:38 2010\n// Creator class: IlvGadgetManagerOutput\nFileName \"Choix_Balance\"\nPathName \"C:\\\\e\\\\MyDevelopment\\\\centrale sarto modif\\\\IlogFile\\\\Choix_Balance.ilv\"\nPalettes 4\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 1 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n2 F \"darkslateblue\" 65025 65025 65025 \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n3 F \"gray\" 32640 0 32640 \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\nIlvObjects 50\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 49 70 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 1\"  }   } 544 \"Balance1\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance2\" \"quitter\"\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 49 190 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 2\"  }   } 544 \"Balance2\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance3\" \"Balance1\"\n0 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 49 310 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 3\"  }   } 544 \"Balance3\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance4\" \"Balance2\"\n0 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 49 430 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 4\"  }   } 544 \"Balance4\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance5\" \"Balance3\"\n0 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 279 70 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 5\"  }   } 544 \"Balance5\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance6\" \"Balance4\"\n0 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 279 310 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 7\"  }   } 544 \"Balance7\"\n1\n1"
" \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance8\" \"Balance6\"\n0 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 279 430 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 8\"  }   } 544 \"Balance8\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"quitter\" \"Balance7\"\n0 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.190079940966797 0 0 6.205041444757085 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n6144 \"Balance1\" \"Balance8\"\n0 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvButton 279 190 129 40 F13 2 { IlvMessageItem 262145 4 16 4 \"Balance 6\"  }   } 544 \"Balance6\"\n1\n1 \"__ilvCallback\" \"BalanceCB\"\n6144 \"Balance7\" \"Balance5\"\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262169 4 16 4 \"&SelectionnerBalance\"  }   } 32 \"Message\"\n0\n1 { 10 3 IlvReliefDiamond 109 10 9 45 2 } 32 \"Diamond1\"\n0\n1 { 11 1 IlvReliefRectangle 49 50 59 10 2 } 32 \"Diamond1G\"\n0\n1 { 12 1 IlvReliefRectangle 119 50 59 10 2 } 32 \"Diamond1D\"\n0\n1 { 13 3 IlvReliefDiamond 109 130 9 45 2 } 32 \"Diamond2\"\n0\n1 { 14 1 IlvReliefRectangle 49 170 59 10 2 } 32 \"Diamond2G\"\n0\n1 { 15 1 IlvReliefRectangle 119 170 59 10 2 } 32 \"Diamond2D\"\n0\n1 { 16 3 IlvReliefDiamond 109 250 9 45 2 } 32 \"Diamond3\"\n0\n1 { 17 1 IlvReliefRectangle 49 290 59 10 2 } 32 \"Diamond3G\"\n0\n1 { 18 1 IlvReliefRectangle 119 290 59 10 2 } 32 \"Diamond3D\"\n0\n1 { 19 3 IlvReliefDiamond 109 370 9 45 2 } 32 \"Diamond4\"\n0\n1 { 20 1 IlvReliefRectangle 49 410 59 10 2 } 32 \"Diamond4G\"\n0\n1 { 21 1 IlvReliefRectangle 119 410 59 10 2 } 32 \"Diamond4D\"\n0\n1 { 22 3 IlvReliefDiamond 339 10 9 45 2 } 32 \"Diamond5\"\n0\n1 { 23 1 IlvReliefRectangle 279 50 59 10 2 } 32 \"Diamond5G\"\n0\n1 { 24 1 IlvReliefRectangle 349 50 59 10 2 } 32 \"Diamond5D\"\n0\n1 { 25 3 IlvReliefDiamond 339 250 9 45 2 } "
"32 \"Diamond7\"\n0\n1 { 26 1 IlvReliefRectangle 279 290 59 10 2 } 32 \"Diamond7G\"\n0\n1 { 27 1 IlvReliefRectangle 349 290 59 10 2 } 32 \"Diamond7D\"\n0\n1 { 28 3 IlvReliefDiamond 339 370 9 45 2 } 32 \"Diamond8\"\n0\n1 { 29 1 IlvReliefRectangle 279 410 59 10 2 } 32 \"Diamond8G\"\n0\n1 { 30 1 IlvReliefRectangle 349 410 59 10 2 } 32 \"Diamond8D\"\n0\n1 { 31 3 IlvReliefDiamond 339 130 9 45 2 } 32 \"Diamond6\"\n0\n1 { 32 1 IlvReliefRectangle 279 170 59 10 2 } 32 \"Diamond6G\"\n0\n1 { 33 1 IlvReliefRectangle 349 170 59 10 2 } 32 \"Diamond6D\"\n0\n1 { 34 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 149 20 } 32 \"Lighton1\"\n0\n1 { 35 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 139 140 } 32 \"Lighton2\"\n0\n1 { 36 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 149 260 } 32 \"Lighton3\"\n0\n1 { 37 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 149 380 } 32 \"Lighton4\"\n0\n1 { 38 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 369 20 } 32 \"Lighton5\"\n0\n1 { 39 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 369 138 } 32 \"Lighton6\"\n0\n1 { 40 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 369 260 } 32 \"Lighton7\"\n0\n1 { 41 1 IlvZoomableTransparentIcon 0 0 \"default\" F0.125 0 0 0.125 369 380 } 32 \"Lighton8\"\n0\n1 { 42 1 IlvRectangle 39 250 149 110 } 32 \"Etalon3\"\n0\n1 { 43 1 IlvRectangle 39 10 149 110 } 32 \"Etalon1\"\n0\n1 { 44 1 IlvRectangle 39 130 149 110 } 32 \"Etalon2\"\n0\n1 { 45 1 IlvRectangle 39 370 149 110 } 32 \"Etalon4\"\n0\n1 { 46 1 IlvRectangle 269 10 149 110 } 32 \"Etalon5\"\n0\n1 { 47 1 IlvRectangle 269 130 149 110 } 32 \"Etalon6\"\n0\n1 { 48 1 IlvRectangle 269 250 149 110 } 32 \"Etalon7\"\n0\n1 { 49 1 IlvRectangle 269 370 149 110 } 32 \"Etalon8\"\n0\nSize 742 545\nBackground \"gray\"\nGeometryHandlers\n1 100 0 742 0 742 0\n50 3 688 0 688  50 0 50 7  4 2 4 0\n 3 0 0 6  734 0 734 9  0 0 2 0\n 3 109 0 109  9 0 9 10  624 0 624 0\n 3 49 0 "
"49  59 0 59 11  634 0 634 0\n 3 119 0 119  59 0 59 12  564 0 564 0\n 3 49 0 49  129 0 129 0  564 0 564 0\n 3 109 0 109  9 0 9 13  624 0 624 0\n 3 49 0 49  59 0 59 14  634 0 634 0\n 3 119 0 119  59 0 59 15  564 0 564 0\n 3 49 0 49  129 0 129 1  564 0 564 0\n 3 49 0 49  59 0 59 17  634 0 634 0\n 3 119 0 119  59 0 59 18  564 0 564 0\n 3 49 0 49  129 0 129 2  564 0 564 0\n 3 109 0 109  9 0 9 19  624 0 624 0\n 3 49 0 49  59 0 59 20  634 0 634 0\n 3 49 0 49  129 0 129 3  564 0 564 0\n 3 119 0 119  59 0 59 21  564 0 564 0\n 3 279 0 279  129 0 129 6  334 0 334 0\n 3 279 0 279  59 0 59 29  404 0 404 0\n 3 349 0 349  59 0 59 30  334 0 334 0\n 3 339 0 339  9 0 9 28  394 0 394 0\n 3 279 0 279  129 0 129 5  334 0 334 0\n 3 349 0 349  59 0 59 27  334 0 334 0\n 3 279 0 279  59 0 59 26  404 0 404 0\n 3 339 0 339  9 0 9 25  394 0 394 0\n 3 279 0 279  129 0 129 4  334 0 334 0\n 3 279 0 279  59 0 59 23  404 0 404 0\n 3 349 0 349  59 0 59 24  334 0 334 0\n 3 339 0 339  9 0 9 22  394 0 394 0\n 3 339 0 339  9 0 9 31  394 0 394 0\n 3 279 0 279  59 0 59 32  404 0 404 0\n 3 349 0 349  59 0 59 33  334 0 334 0\n 3 279 0 279  129 0 129 8  334 0 334 0\n 3 109 0 109  9 0 9 16  624 0 624 0\n 3 149 0 149  1 0 1 34  592 0 592 0\n 3 139 0 139  1 0 1 35  602 0 602 0\n 3 149 0 149  1 0 1 36  592 0 592 0\n 3 149 0 149  1 0 1 37  592 0 592 0\n 3 369 0 369  1 0 1 38  372 0 372 0\n 3 369 0 369  1 0 1 39  372 0 372 0\n 3 369 0 369  1 0 1 40  372 0 372 0\n 3 369 0 369  1 0 1 41  372 0 372 0\n 3 39 0 39  149 0 149 42  554 0 554 0\n 3 39 0 39  149 0 149 43  554 0 554 0\n 3 39 0 39  149 0 149 44  554 0 554 0\n 3 39 0 39  149 0 149 45  554 0 554 0\n 3 269 0 269  149 0 149 46  324 0 324 0\n 3 269 0 269  149 0 149 47  324 0 324 0\n 3 269 0 269  149 0 149 48  324 0 324 0\n 3 269 0 269  149 0 149 49  324 0 324 0\n1 100 0 545 0 545 0\n50 3 440 0 440  50 0 50 7  55 0 55 0\n 3 499 0 499  41 0 41 9  0 5 5 0\n 3 10 0 10  45 0 45 10  490 0 490 0\n 3 50 0 50  10 0 10 11  485 0 485 0\n 3 50 0 50  10 0 10 12  485 "
"0 485 0\n 3 70 0 70  40 0 40 0  435 0 435 0\n 3 130 0 130  45 0 45 13  370 0 370 0\n 3 170 0 170  10 0 10 14  365 0 365 0\n 3 170 0 170  10 0 10 15  365 0 365 0\n 3 190 0 190  40 0 40 1  315 0 315 0\n 3 290 0 290  10 0 10 17  245 0 245 0\n 3 290 0 290  10 0 10 18  245 0 245 0\n 3 310 0 310  40 0 40 2  195 0 195 0\n 3 370 0 370  45 0 45 19  130 0 130 0\n 3 410 0 410  10 0 10 20  125 0 125 0\n 3 430 0 430  40 0 40 3  75 0 75 0\n 3 410 0 410  10 0 10 21  125 0 125 0\n 3 430 0 430  40 0 40 6  75 0 75 0\n 3 410 0 410  10 0 10 29  125 0 125 0\n 3 410 0 410  10 0 10 30  125 0 125 0\n 3 370 0 370  45 0 45 28  130 0 130 0\n 3 310 0 310  40 0 40 5  195 0 195 0\n 3 290 0 290  10 0 10 27  245 0 245 0\n 3 290 0 290  10 0 10 26  245 0 245 0\n 3 250 0 250  45 0 45 25  250 0 250 0\n 3 70 0 70  40 0 40 4  435 0 435 0\n 3 50 0 50  10 0 10 23  485 0 485 0\n 3 50 0 50  10 0 10 24  485 0 485 0\n 3 10 0 10  45 0 45 22  490 0 490 0\n 3 130 0 130  45 0 45 31  370 0 370 0\n 3 170 0 170  10 0 10 32  365 0 365 0\n 3 170 0 170  10 0 10 33  365 0 365 0\n 3 190 0 190  40 0 40 8  315 0 315 0\n 3 250 0 250  45 0 45 16  250 0 250 0\n 3 20 0 20  1 0 1 34  524 0 524 0\n 3 140 0 140  1 0 1 35  404 0 404 0\n 3 260 0 260  1 0 1 36  284 0 284 0\n 3 380 0 380  1 0 1 37  164 0 164 0\n 3 20 0 20  1 0 1 38  524 0 524 0\n 3 138 0 138  1 0 1 39  406 0 406 0\n 3 260 0 260  1 0 1 40  284 0 284 0\n 3 380 0 380  1 0 1 41  164 0 164 0\n 3 250 0 250  110 0 110 42  185 0 185 0\n 3 10 0 10  110 0 110 43  425 0 425 0\n 3 130 0 130  110 0 110 44  305 0 305 0\n 3 370 0 370  110 0 110 45  65 0 65 0\n 3 10 0 10  110 0 110 46  425 0 425 0\n 3 130 0 130  110 0 110 47  305 0 305 0\n 3 250 0 250  110 0 110 48  185 0 185 0\n 3 370 0 370  110 0 110 49  65 0 65 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Choix_Balance* o = (Choix_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_BalanceCB(IlvGraphic* g, IlAny) {
    Choix_Balance* o = (Choix_Balance*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->BalanceCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Choix_Balance::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("quitterCB", _quitterCB);
    registerCallback("BalanceCB", _BalanceCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Choix_Balance::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Choix_Balance::BalanceCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : BalanceCB method ...",className);
}

