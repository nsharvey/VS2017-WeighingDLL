// -------------------------------------------------------------- -*- C++ -*-
// File: C:\MyDevelopment\Centrale V6\cssrc\choix_OF.cpp
// IlogViews 5 generated source file
// File generated Tue Mar 20 19:40:07 2012
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "choix_OF.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "choix_OF.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue Mar 20 19:40:07 2012\n// Creator class: IlvGadgetManagerOutput\nFileName \"choix_OF\"\nPathName \"C:\\\\MyDevelopment\\\\Centrale V6\\\\IlogFile\\\\choix_OF.ilv\"\nPalettes 4\n\"default\" 1 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n2 F \"darkslateblue\" \"white\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n3 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 4 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 38\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 16 248 30 F6 2 1 -1 0 \"\" } 544 \"SaisieNOF\"\n2\n1 \"__ilvFocusOut\" \"SaisieNOFCB\"\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n2048 \"SaisiePhase\"\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.750000067055227 0 0 3.750000178813933 400 16 } 544 \"BoutonListeOF\"\n1\n1 \"__ilvCallback\" \"listeOFCB\"\n4096 \"SaisieNOF\"\n0 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.750000134110448 0 0 3.750000134110451 656 16 } 544 \"BoutonListePhase\"\n1\n1 \"__ilvCallback\" \"listePhaseCB\"\n20480 \"SaisiePhase\"\n0 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999940395355 0 0 6.249999940395355 688 440 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n0\n0 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999940395355 0 0 6.249999821186066 688 384 } 544 \"aide\"\n1\n1 \"__ilvCallback\" \"aideCB\"\n4096 \"Allouer\"\n0 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.24999988079071"
" 0 0 6.25 688 160 } 544 \"Valider\"\n1\n1 \"__ilvCallback\" \"ValidationCB\"\n4096 \"BoutonListePhase_Art\"\n0 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.25 0 0 6.25 688 216 } 544 \"Tactile\"\n1\n1 \"__ilvCallback\" \"TactileCB\"\n4096 \"Valider\"\n0 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999940395355 0 0 6.25 688 272 } 544 \"VideBox\"\n1\n1 \"__ilvCallback\" \"VideBoxCB\"\n4096 \"Tactile\"\n0 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 96 248 30 F6 2 1 -1 0 \"\" } 544 \"SaisieComposant\"\n2\n1 \"__ilvFocusOut\" \"SaisieComposantCB\"\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n6144 \"SaisieNOF_Art\" \"SaisieComposant_Art\"\n0 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.750000029802322 0 0 3.750000067055225 400 96 } 544 \"BoutonListeComposant\"\n1\n1 \"__ilvCallback\" \"listeComposantCB\"\n4096 \"BoutonListePhase_Art\"\n0 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.24999988079071 0 0 6.25 688 328 } 544 \"Allouer\"\n1\n1 \"__ilvCallback\" \"AllouerCB\"\n4096 \"VideBox\"\n0 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.75 0 0 3.750000134110451 400 16 } 544 \"BoutonListeComposant_Art\"\n1\n1 \"__ilvCallback\" \"listeComposantCB\"\n6144 \"SaisieNOF_Art\" \"SaisieComposant_Art\"\n0 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.749999888241291 0 0 3.749999888241291 656 96 } 544 \"BoutonListePhase_Art\"\n1\n1 \"__ilvCallback\" \"listePhaseCB\"\n4096 \"SaisieComposant\"\n0 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 "
"IlvTextField 152 96 248 30 F6 2 1 -1 0 \"\" } 544 \"SaisieNOF_Art\"\n2\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvFocusOut\" \"SaisieNOFCB\"\n6144 \"SaisiePhase_Art\" \"BoutonListeComposant_Art\"\n0 { 14 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.750000067055227 0 0 3.750000178813933 400 96 } 544 \"BoutonListeOF_Art\"\n1\n1 \"__ilvCallback\" \"listeOFCB\"\n6144 \"SaisiePhase_Art\" \"SaisieNOF\"\n1 { 15 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 499 734 41 F536870924 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 16 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 16 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NOF\"  }   } 32 \"EtiquetteNoOF\"\n0\n1 { 17 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 432 16 144 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NPoste\"  }   } 32 \"EtiquettePhase\"\n0\n1 { 18 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 176 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&ArticleLance\"  }   } 32 \"EtiquetteArtLance\"\n0\n1 { 19 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 256 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&LotLance\"  }   } 32 \"EtiquetteLotLance\"\n0\n1 { 20 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 256 248 30 F6 2 1 -1 0 \"\" } 416 \"AffLot\"\n0\n1 { 21 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 176 248 30 F6 2 1 -1 0 \"\" } 416 \"AffArticle\"\n0\n1 { 22 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 0 336 144 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&QuantiteAllouee\"  }   } 32 \"EtiquetteQteAllouee\"\n0\n1 { 23 P 1\n[ IlvInteractorProperty"
" __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 336 336 51 30 F268435468 0 { IlvMessageItem 262169 4 16 4 \"UN\"  }   } 32 \"AffUniteComp\"\n0\n1 { 24 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 208 504 30 F6 2 1 -1 0 \"\" } 416 \"AffLibArticle\"\n0\n1 { 25 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 96 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Composant\"  }   } 32 \"EtiquetteComposant\"\n0\n1 { 26 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 128 504 30 F6 2 1 -1 0 \"\" } 416 \"AffLibComposant\"\n0\n1 { 27 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 400 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&QuantiteAPeser\"  }   } 32 \"LibQuantiteAPeser\"\n0\n1 { 28 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 336 400 51 30 F268435468 0 { IlvMessageItem 262169 4 16 4 \"UN\"  }   } 32 \"AffUniteComposant\"\n0\n1 { 29 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 152 336 176 30 F14 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffQuantite\"\n0\n1 { 30 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 152 400 176 30 F14 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffQuantiteAPeser\"\n0\n1 { 31 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 576 16 80 30 F6 2 2 -1 0 \"0\" . , 0 0 -2147483648 2147483647 } 544 \"SaisiePhase\"\n2\n1 \"__ilvFocusIn\" \"EntreeNumberFieldCB\"\n1 \"__ilvFocusOut\" \"SaisiePhaseCB\"\n6144 \"SaisieComposant_Art\" \"SaisieNOF\"\n1 { 32 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 16 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Composant\"  }   } 32 \"EtiquetteComposant_Art\"\n0\n1 { 33 P 1\n[ IlvInteractorProperty "
"__ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 48 504 30 F6 2 1 -1 0 \"\" } 416 \"AffLibComposant_Art\"\n0\n1 { 34 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvMessageLabel 432 96 144 32 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NPoste\"  }   } 32 \"EtiquettePhase_Art\"\n0\n1 { 35 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 576 96 80 30 F6 2 2 -1 0 \"0\" . , 0 0 -2147483648 2147483647 } 544 \"SaisiePhase_Art\"\n2\n1 \"__ilvFocusIn\" \"EntreeNumberFieldCB\"\n1 \"__ilvFocusOut\" \"SaisiePhaseCB\"\n6144 \"Valider\" \"BoutonListeOF_Art\"\n1 { 36 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 8 96 136 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NOF\"  }   } 32 \"EtiquetteNoOF_Art\"\n0\n1 { 37 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 152 16 248 30 F6 2 1 -1 0 \"\" } 544 \"SaisieComposant_Art\"\n2\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvFocusOut\" \"SaisieComposantCB\"\n6144 \"SaisieComposant\" \"SaisiePhase\"\nSize 742 545\nBackground \"gray\"\nGeometryHandlers\n1 100 0 742 0 742 0\n38 3 688 0 688  50 0 50 3  4 0 4 0\n 3 688 0 688  50 0 50 4  4 0 4 0\n 3 6 0 6  734 0 734 15  2 0 2 0\n 3 688 0 688  50 0 50 5  4 0 4 0\n 3 688 0 688  50 0 50 6  4 4 4 0\n 3 432 0 432  144 0 144 17  166 0 166 0\n 3 0 0 0  144 0 144 22  598 0 598 0\n 3 152 0 152  248 0 248 20  342 0 342 0\n 3 152 0 152  248 0 248 21  342 0 342 0\n 3 152 0 152  248 0 248 0  342 0 342 0\n 3 400 0 400  30 0 30 1  312 0 312 0\n 3 656 0 656  30 0 30 2  56 0 56 0\n 3 8 0 8  136 0 136 16  598 0 598 0\n 3 0 0 8  136 0 136 18  598 0 598 0\n 3 0 0 8  136 0 136 19  598 0 598 0\n 3 152 0 152  504 0 504 24  86 0 86 0\n 3 336 0 336  51 0 51 23  355 0 355 0\n 3 688 0 688  50 0 50 7  4 4 4 0\n 3 152 0 152  504 0 504 26  86 0 86 0\n 3 400 0 400  30 0 30 9  312 0 312 0\n 3 152 0 152  248 0 "
"248 8  342 0 342 0\n 3 8 0 8  136 0 136 25  598 0 598 0\n 3 0 0 8  136 0 136 27  598 0 598 0\n 3 336 0 336  51 0 51 28  355 0 355 0\n 3 688 0 688  50 0 50 10  4 4 4 0\n 3 152 0 152  176 0 176 29  414 0 414 0\n 3 152 0 152  176 0 176 30  414 0 414 0\n 3 576 0 576  80 0 80 31  86 0 86 0\n 3 0 0 8  136 0 136 32  598 0 598 0\n 3 152 0 152  504 0 504 33  86 0 86 0\n 3 400 0 400  30 0 30 11  312 0 312 0\n 3 576 0 576  80 0 80 35  86 0 86 0\n 3 432 0 432  144 0 144 34  166 0 166 0\n 3 656 0 656  30 0 30 12  56 0 56 0\n 3 152 0 152  248 0 248 37  342 0 342 0\n 3 152 0 152  248 0 248 13  342 0 342 0\n 3 8 0 8  136 0 136 36  598 0 598 0\n 3 400 0 400  30 0 30 14  312 0 312 0\n1 100 0 545 0 545 0\n38 3 440 0 440  50 0 50 3  55 0 55 0\n 3 384 0 384  50 0 50 4  111 0 111 0\n 3 499 0 499  41 0 41 15  5 0 5 0\n 3 160 0 160  50 0 50 5  335 0 335 0\n 3 216 0 216  50 0 50 6  279 0 279 0\n 3 16 0 16  30 0 30 17  499 0 499 0\n 3 336 0 336  30 0 30 22  179 0 179 0\n 3 256 0 256  30 0 30 20  259 0 259 0\n 3 176 0 176  30 0 30 21  339 0 339 0\n 3 16 0 16  30 0 30 0  499 0 499 0\n 3 16 0 16  30 0 30 1  499 0 499 0\n 3 16 0 16  30 0 30 2  499 0 499 0\n 3 16 0 16  30 0 30 16  499 0 499 0\n 3 176 0 176  30 0 30 18  339 0 339 0\n 3 256 0 256  30 0 30 19  259 0 259 0\n 3 208 0 208  30 0 30 24  307 0 307 0\n 3 336 0 336  30 0 30 23  179 0 179 0\n 3 272 0 272  50 0 50 7  223 5 223 0\n 3 128 0 128  30 0 30 26  387 0 387 0\n 3 96 0 96  30 0 30 9  419 0 419 0\n 3 96 0 96  30 0 30 8  419 0 419 0\n 3 96 0 96  30 0 30 25  419 0 419 0\n 3 400 0 400  30 0 30 27  115 0 115 0\n 3 400 0 400  30 0 30 28  115 0 115 0\n 3 328 0 328  50 0 50 10  167 0 167 0\n 3 336 0 336  30 0 30 29  179 0 179 0\n 3 400 0 400  30 0 30 30  115 0 115 0\n 3 16 0 16  30 0 30 31  499 0 499 0\n 3 16 0 16  30 0 30 32  499 0 499 0\n 3 48 0 48  30 0 30 33  467 0 467 0\n 3 16 0 16  30 0 30 11  499 0 499 0\n 3 96 0 96  30 0 30 35  419 0"
" 419 0\n 3 96 0 96  32 0 32 34  417 0 417 0\n 3 96 0 96  30 0 30 12  419 0 419 0\n 3 16 0 16  30 0 30 37  499 0 499 0\n 3 96 0 96  30 0 30 13  419 0 419 0\n 3 96 0 96  30 0 30 36  419 0 419 0\n 3 96 0 96  30 0 30 14  419 0 419 0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nScript \"JvScript\" Inline \"\"\n\r\nstatic function ValidationCB(obj)\r\n{ \r\n  var panel = Application.pesee_OF;\r\n  if (panel.visible == true)\r\n   {panel.visible == false;\r\n   }\r\n  else\r\n   {panel.visible == true;\r\n   }\r\n \r\n}\r\n\r\nScriptEnd\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_ValidationCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->ValidationCB(g);
}


static void ILVCALLBACK
_listeComposantCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->listeComposantCB(g);
}


static void ILVCALLBACK
_EntreeTextFieldCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->EntreeTextFieldCB(g);
}


static void ILVCALLBACK
_AllouerCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->AllouerCB(g);
}


static void ILVCALLBACK
_listePhaseCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->listePhaseCB(g);
}


static void ILVCALLBACK
_VideBoxCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->VideBoxCB(g);
}


static void ILVCALLBACK
_SaisieComposantCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieComposantCB(g);
}


static void ILVCALLBACK
_TactileCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->TactileCB(g);
}


static void ILVCALLBACK
_listeOFCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->listeOFCB(g);
}


static void ILVCALLBACK
_SaisiePhaseCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisiePhaseCB(g);
}


static void ILVCALLBACK
_EntreeNumberFieldCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->EntreeNumberFieldCB(g);
}


static void ILVCALLBACK
_aideCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->aideCB(g);
}


static void ILVCALLBACK
_SaisieNOFCB(IlvGraphic* g, IlAny) {
    Choix_OF* o = (Choix_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieNOFCB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Choix_OF::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("quitterCB", _quitterCB);
    registerCallback("ValidationCB", _ValidationCB);
    registerCallback("listeComposantCB", _listeComposantCB);
    registerCallback("EntreeTextFieldCB", _EntreeTextFieldCB);
    registerCallback("AllouerCB", _AllouerCB);
    registerCallback("listePhaseCB", _listePhaseCB);
    registerCallback("VideBoxCB", _VideBoxCB);
    registerCallback("SaisieComposantCB", _SaisieComposantCB);
    registerCallback("TactileCB", _TactileCB);
    registerCallback("listeOFCB", _listeOFCB);
    registerCallback("SaisiePhaseCB", _SaisiePhaseCB);
    registerCallback("EntreeNumberFieldCB", _EntreeNumberFieldCB);
    registerCallback("aideCB", _aideCB);
    registerCallback("SaisieNOFCB", _SaisieNOFCB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Choix_OF::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Choix_OF::ValidationCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : ValidationCB method ...",className);
}

void
Choix_OF::listeComposantCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : listeComposantCB method ...",className);
}

void
Choix_OF::EntreeTextFieldCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : EntreeTextFieldCB method ...",className);
}

void
Choix_OF::AllouerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : AllouerCB method ...",className);
}

void
Choix_OF::listePhaseCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : listePhaseCB method ...",className);
}

void
Choix_OF::VideBoxCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : VideBoxCB method ...",className);
}

void
Choix_OF::SaisieComposantCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieComposantCB method ...",className);
}

void
Choix_OF::TactileCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : TactileCB method ...",className);
}

void
Choix_OF::listeOFCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : listeOFCB method ...",className);
}

void
Choix_OF::SaisiePhaseCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisiePhaseCB method ...",className);
}

void
Choix_OF::EntreeNumberFieldCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : EntreeNumberFieldCB method ...",className);
}

void
Choix_OF::aideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : aideCB method ...",className);
}

void
Choix_OF::SaisieNOFCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieNOFCB method ...",className);
}

