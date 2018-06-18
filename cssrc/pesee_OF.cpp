// -------------------------------------------------------------- -*- C++ -*-
// File: C:\MyDevelopment\Centrale V6\cssrc\pesee_OF.cpp
// IlogViews 5 generated source file
// File generated Tue Mar 20 19:17:39 2012
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#include "pesee_OF.h"

#if defined(ILVNOSTATICDATA)
#define FILENAME "pesee_OF.ilv"
#else  /* !ILVNOSTATICDATA */
#define FILENAME NULL
static const char _data[] = 
"// Ilv Version: 5.3\n// File generated: Tue Mar 20 19:17:39 2012\n// Creator class: IlvGadgetManagerOutput\nFileName \"pesee_OF\"\nPathName \"C:\\\\MyDevelopment\\\\Centrale V6\\\\IlogFile\\\\pesee_OF.ilv\"\nPalettes 8\n5 F \"gray\" \"black\" \"%Tahoma-40-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n\"default\" 1 F \"gray\" \"black\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n4 F \"lightblue\" \"yellow\" \"default\" \"StockedDefaultGui\" 0 solid solid 0 0 0 65535 0\n3 F \"gray\" \"black\" \"%MS Sans Serif-20-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n2 F \"darkslateblue\" 65025 65025 65025 \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n0 F \"gray\" \"black\" \"%MS Sans Serif-24-[Charset:0]\" 0 solid solid 0 0 0 65535 1\n6 F \"gray\" \"black\" \"%Arial-14-B[Charset:0]\" 0 solid solid 0 0 0 65535 0\n7 F \"gray\" \"black\" \"%MS Sans Serif-32-[Charset:0]\" 0 solid solid 0 0 0 65535 1\nIlvObjects 70\n0 { 0 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 272 168 30 F6 2 1 -1 0 \"\" } 544 \"SaisieBalance\"\n3\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieBalanceCB\"\n1 \"__ilvFocusOut\" \"FocusOutBalanceCB\"\n16384\n0 { 1 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.284318121886253 0 0 6.313068121612073 688 215.8579545468092 } 544 \"validerPlus\"\n1\n1 \"__ilvCallback\" \"validerPlusCB\"\n4096 \"quitter\"\n0 { 2 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189333628463745 0 0 6.314573803415894 688 327.886363637447 } 544 \"tarer\"\n1\n1 \"__ilvCallback\" \"tarerCB\"\n6144 \"peser\" \"mettreAZero\"\n0 { 3 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.265113576614857 0 0 6.275511303788424 688 104.1278409078717 } 544 \"valider\"\n1\n1"
" \"__ilvCallback\" \"validerCB\"\n0\n0 { 4 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.27897721284628 0 0 6.184972517144679 688 440.0555555582038 } 544 \"quitter\"\n1\n1 \"__ilvCallback\" \"quitterCB\"\n16384\n0 { 5 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.311647667080164 0 0 6.306960167124868 688 271.886363637447 } 544 \"mettreAZero\"\n1\n1 \"__ilvCallback\" \"mettreAZeroCB\"\n6144 \"tarer\" \"SaisieBalance\"\n0 { 6 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.265113576614857 0 0 6.26846584931016 688 160.1221590897442 } 544 \"tactile\"\n1\n1 \"__ilvCallback\" \"tactileCB\"\n20480 \"resultatPesee\"\n0 { 7 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.266704485690594 0 0 6.189338183646255 120 8 } 544 \"secu3\"\n1\n1 \"__ilvCallback\" \"secu3CB\"\n2\n0 { 8 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.192401909110886 0 0 6.192401909110886 688 384 } 544 \"peser\"\n1\n1 \"__ilvCallback\" \"peserCB\"\n20480 \"tarer\"\n1 { 9 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n2 IlvMessageLabel 6 499 734 41 F12 0 { IlvMessageItem 262168 4 16 4  }   } 32 \"message\"\n0\n1 { 10 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.22200029668808 0 0 6.266704485690594 8 8 } 544 \"secu1\"\n1\n1 \"__ilvCallback\" \"secu1CB\"\n16384\n1 { 11 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.189338183646255 344 8 } 544 \"secu7\"\n1\n1 \"__ilvCallback\" \"secu7CB\"\n2\n1 { 12 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0"
" \"default\" F6.266704485690594 0 0 6.189338183646255 64 8 } 544 \"secu2\"\n1\n1 \"__ilvCallback\" \"secu2CB\"\n2\n1 { 13 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.222028074467183 0 0 6.189338183646255 176 8 } 544 \"secu4\"\n1\n1 \"__ilvCallback\" \"secu4CB\"\n2\n1 { 14 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.189310331596576 400 8 } 544 \"secu8\"\n1\n1 \"__ilvCallback\" \"secu8CB\"\n2\n1 { 15 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.189338183646255 456 8 } 544 \"secu9\"\n1\n1 \"__ilvCallback\" \"secu9CB\"\n2\n1 { 16 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 272 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Balance\"  }   } 0\n0\n1 { 17 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 432 452 64 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsPese\"  }   } 0\n0\n1 { 18 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 72 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NOF\"  }   } 0\n0\n1 { 19 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 72 168 30 F6 2 1 -1 0 \"\" } 416 \"AffNOF\"\n0\n1 { 20 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 152 336 112 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&RestantAPeser\"  }   } 0\n0\n1 { 21 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 440 336 31 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"UniteTotalAPeser\"\n0\n1 { 22 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 440 304 31 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"UniteTare\"\n0\n1"
" { 23 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 240 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Recipient\"  }   } 0\n0\n1 { 24 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 304 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsTare\"  }   } 0\n0\n1 { 25 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 104 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Composant\"  }   } 0\n0\n1 { 26 4 IlvRectangularGauge 81 71 34 416 0 3000 2000 8 1 } 32 \"JaugePesee\"\n16384\n1 { 27 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 136 456 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsAPeser\"  }   } 0\n0\n1 { 28 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 656 452 31 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"UnitePoidsPese\"\n0\n1 { 29 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 400 452 31 30 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"UnitePoidsAPeser\"\n0\n1 { 30 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 240 168 30 F6 2 1 -1 0 \"\" } 544 \"SaisieRecipient\"\n3\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieRecipientCB\"\n1 \"__ilvFocusOut\" \"FocusOutRecipientCB\"\n6144 \"SaisieBalance\" \"SaisieEmplacement\"\n1 { 31 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 104 168 30 F6 2 1 -1 0 \"\" } 416 \"AffComposant\"\n0\n1 { 32 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 208 144 56 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Lot\"  }   } 32 \"EtiquetteLot\"\n0\n1 { 33 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 144 168 30 F6 2 1 -1 0 \"\" } 544 \"SaisieLot\"\n3\n1"
" \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieLotCB\"\n1 \"__ilvFocusOut\" \"FocusOutLotCB\"\n10240 \"SaisieSousLot\"\n1 { 34 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.747786134907294 0 0 3.747786134907294 648 272 } 544 \"BoutonListeBalance\"\n1\n1 \"__ilvCallback\" \"ListeBalanceCB\"\n16384\n1 { 35 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 208 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Emp\"  }   } 32 \"EtiquetteEmplacement\"\n0\n1 { 36 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 208 168 30 F6 2 1 -1 0 \"\" } 544 \"SaisieEmplacement\"\n3\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieEmplacementCB\"\n1 \"__ilvFocusOut\" \"FocusOutEmplacementCB\"\n6144 \"SaisieRecipient\" \"SaisieSousLot\"\n1 { 37 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.266704485690594 288 8 } 544 \"secu6\"\n1\n1 \"__ilvCallback\" \"secu6CB\"\n2\n1 { 38 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 552 72 96 30 F6 2 2 -1 0 \"0\" . , 0 16 -3e+038 3e+038 } 416 \"AffNPhase\"\n0\n1 { 39 1 IlvZoomableTransparentIcon 0 0 \"default\" F3.742798983556097 0 0 3.72340234140666 121 399 } 32 \"AffConnection\"\n0\n1 { 40 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n5 IlvNumberField 504 439 150 56 F6 2 2 -1 1 \"1000.000\" . , 6 16 -3.40282e+038 3.40282e+038 } 544 \"SaisiePoidsPese\"\n2\n1 \"__ilvFocusIn\" \"EntreeNumberFieldCB\"\n1 \"__ilvCallback\" \"SaisiePoidsPeseCB\"\n20480 \"SaisieBalance\"\n1 { 41 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 272 336 168 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffTotalAPeser\"\n0\n1 { 42 P 1\n[ IlvInteractorProperty"
" __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 272 304 168 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffTare\"\n0\n1 { 43 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n5 IlvNumberField 248 439 150 56 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffPoidsAPeser\"\n0\n1 { 44 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.747786134907294 0 0 3.747786134907294 648 208 } 544 \"BoutonListeEmplacement\"\n1\n1 \"__ilvCallback\" \"ListeEmplacementCB\"\n16384\n1 { 45 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.747786134907294 0 0 3.747786134907294 648 240 } 544 \"BoutonListeRecipient\"\n1\n1 \"__ilvCallback\" \"ListeRecipientCB\"\n16384\n1 { 46 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.785642364071256 0 0 3.785642364071256 648 144 } 544 \"BoutonListeLot\"\n1\n1 \"__ilvCallback\" \"ListeLotCB\"\n16384\n1 { 47 6 IlvRectangularScale 68 72 10 412 5 2 10 5 M 0 100 \"%4.f\"\n\"   0.0000\" \"  25.0000\" \"  50.0000\" \"  75.0000\" \" 100.0000\"  78 484 412 8 1  } 32 \"JaugeScale\"\n0\n1 { 48 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.189338183646255 232 8 } 544 \"secu5\"\n1\n1 \"__ilvCallback\" \"secu5CB\"\n16384\n1 { 49 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F6.189338183646255 0 0 6.189338183646255 512 8 } 544 \"secu10\"\n1\n1 \"__ilvCallback\" \"secu10CB\"\n16384\n1 { 50 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 144 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Cuve\"  }   } 32 \"EtiquetteCuve\"\n0\n1 { 51 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 "
"IlvTextField 272 144 168 30 F6 2 1 -1 0 \"\" } 544 \"SaisieCuve\"\n3\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieCuveCB\"\n1 \"__ilvFocusOut\" \"FocusOutLotCB\"\n0\n1 { 52 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 160 176 104 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&Vanne\"  }   } 32 \"EtiquetteVanne\"\n0\n1 { 53 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 272 176 168 30 F6 2 1 -1 0 \"\" } 544 \"SaisieVanne\"\n3\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvCallback\" \"SaisieVanneCB\"\n1 \"__ilvFocusOut\" \"FocusOutEmplacementCB\"\n0\n1 { 54 P 1\n[ IlvInteractorProperty __ilvInteractor \"Button\" ]\n1 IlvZoomableTransparentIcon 0 0 \"default\" F3.747786134907294 0 0 3.747786134907294 648 144 } 544 \"BoutonListeCuve\"\n1\n1 \"__ilvCallback\" \"ListeLotCB\"\n0\n1 { 55 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 552 144 96 30 F6 2 1 -1 0 \"\" } 544 \"SaisieSousLot\"\n3\n1 \"__ilvCallback\" \"SaisieSousLotCB\"\n1 \"__ilvFocusIn\" \"EntreeTextFieldCB\"\n1 \"__ilvFocusOut\" \"FocusOutSousLotCB\"\n6144 \"SaisieEmplacement\" \"SaisieLot\"\n1 { 56 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 456 144 88 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&SousLot\"  }   } 32 \"EtiquetteSousLot\"\n0\n1 { 57 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 440 144 208 30 F536870919 2 1 -1 0 \"\" } 416 \"LibSaisieCuve\"\n0\n1 { 58 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 440 208 208 30 F536870919 2 1 -1 0 \"\" } 416 \"LibSaisieEmplacement\"\n0\n1 { 59 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField 440 240 208 30 F536870919 2 1 -1 0 \"\" } 416 \"LibSaisieRecipient\"\n0\n1 { 60 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvTextField"
" 440 272 208 30 F536870919 2 1 -1 0 \"\" } 416 \"LibSaisieBalance\"\n0\n1 { 61 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvTextField 440 104 240 30 F536870919 2 1 -1 0 \"\" } 416 \"LibAffComposant\"\n0\n1 { 62 1 IlvZoomableTransparentIcon 0 0 \"default\" F6.249999761581421 0 0 6.249999761581421 688 216 } 544 \"Aide\"\n1\n1 \"__ilvCallback\" \"AideCB\"\n0\n1 { 63 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 440 368 31 32 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"UnitePoidsCumuleCible\"\n0\n1 { 64 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n0 IlvNumberField 272 368 168 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffPoidsCumuleCible\"\n0\n1 { 65 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 152 360 112 48 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsCumuleCible\"  }   } 32 \"EtiquettePoidsCumuleCible\"\n0\n1 { 66 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n7 IlvNumberField 272 400 168 30 F6 2 2 -1 0 \"0\" . , 6 16 -3.40282e+038 3.40282e+038 } 416 \"AffPoidsCumule\"\n0\n1 { 67 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 152 392 112 48 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&PoidsCumule\"  }   } 32 \"EtiquettePoidsCumule\"\n0\n1 { 68 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 440 400 31 32 F268435468 0 { IlvMessageItem 262145 4 16 4 \"Kg\"  }   } 32 \"UnitePoidsCumule\"\n0\n1 { 69 P 1\n[ IlvInteractorProperty __ilvInteractor \"Gadget\" ]\n3 IlvMessageLabel 448 72 96 30 F268435468 0 { IlvMessageItem 262153 4 16 4 \"&NPoste\"  }   } 0\n0\nSize 743 545\nBackground \"gray\"\nGeometryHandlers\n4 100 0 5 0 5 0\n 0 0 63 5 63 5\n 0 0 498 68 498 68\n 0 0 177 566 177 566\n70 3 8 0 8  50 0 50 10  685 0 685 3\n 3 344 0 344  50 0 50 11  349 0 349 3\n 3 64 0 64  50 0 50"
" 12  629 0 629 3\n 3 120 0 120  50 0 50 7  573 0 573 3\n 3 176 0 176  50 0 50 13  517 0 517 3\n 3 400 0 400  50 0 50 14  293 0 293 3\n 3 456 0 456  50 0 50 15  237 0 237 3\n 3 6 0 6  734 0 734 9  3 0 3 3\n 3 688 0 688  50 0 50 5  5 3 5 3\n 3 688 0 688  50 0 50 2  5 3 5 3\n 3 688 0 688  50 0 50 4  5 0 5 3\n 3 688 0 688  50 0 50 1  5 0 5 3\n 3 688 0 688  50 0 50 6  5 5 5 3\n 3 688 0 688  50 0 50 3  5 5 5 3\n 3 81 0 81  34 0 34 26  628 0 628 3\n 3 160 0 160  104 0 104 18  479 0 479 3\n 3 160 0 160  104 0 104 25  479 0 479 3\n 3 160 0 160  104 0 104 16  479 0 479 3\n 3 160 0 160  104 0 104 23  479 0 479 3\n 3 160 0 160  104 0 104 24  479 0 479 3\n 3 152 0 152  112 0 112 20  479 0 479 3\n 3 272 0 272  168 0 168 19  303 0 303 3\n 3 272 0 272  168 0 168 31  303 0 303 3\n 3 272 0 272  168 0 168 0  303 0 303 3\n 3 272 0 272  168 0 168 30  303 0 303 3\n 3 440 0 440  31 0 31 22  272 0 272 3\n 3 440 0 440  31 0 31 21  272 0 272 3\n 3 432 0 432  64 0 64 17  247 0 247 3\n 3 136 0 136  104 0 104 27  503 0 503 3\n 3 656 0 656  31 0 31 28  56 0 56 3\n 3 400 0 400  31 0 31 29  312 0 312 3\n 3 272 0 272  168 0 168 33  303 0 303 3\n 3 208 0 208  56 0 56 32  479 0 479 3\n 3 648 0 648  30 0 30 34  65 0 65 3\n 3 272 0 272  168 0 168 36  303 0 303 3\n 3 160 0 160  104 0 104 35  479 0 479 3\n 3 288 0 288  50 0 50 37  405 0 405 3\n 3 504 0 504  150 0 150 40  89 0 89 3\n 3 248 0 248  150 0 150 43  345 0 345 3\n 3 272 0 272  168 0 168 42  303 0 303 3\n 3 272 0 272  168 0 168 41  303 0 303 3\n 3 552 0 552  96 0 96 38  95 0 95 3\n 3 121 0 121  30 0 30 39  592 0 592 3\n 3 648 0 648  30 0 30 46  65 0 65 3\n 3 648 0 648  30 0 30 44  65 0 65 3\n 3 648 0 648  30 0 30 45  65 0 65 3\n 3 232 0 232  50 0 50 48  461 0 461 3\n 3 512 0 512  50 0 50 49  181 0 181 3\n 3 688 0 688  50 0 50 8  5 0 5 3\n 3 272 0 272  168 0 168 51  303 0 303 3\n 3 160 0 160  104 0 104 50  479 0 479 3\n 3 648 0 648  30 0 30 54  65 0 65 3\n 3 272 0"
" 272  168 0 168 53  303 0 303 3\n 3 160 0 160  104 0 104 52  479 0 479 3\n 3 552 0 552  96 0 96 55  95 0 95 3\n 3 456 0 456  88 0 88 56  199 0 199 3\n 3 440 0 440  208 0 208 57  95 0 95 3\n 3 440 0 440  208 0 208 58  95 0 95 3\n 3 440 0 440  208 0 208 59  95 0 95 3\n 3 440 0 440  208 0 208 60  95 0 95 3\n 3 0 0 0  79 0 79 47  664 0 664 3\n 3 440 0 440  240 0 240 61  63 0 63 3\n 3 688 0 688  50 0 50 62  5 0 5 3\n 3 152 0 152  112 0 112 67  479 0 479 3\n 3 272 0 272  168 0 168 66  303 0 303 3\n 3 152 0 152  112 0 112 65  479 0 479 3\n 3 272 0 272  168 0 168 64  303 1 303 3\n 3 440 0 440  31 0 31 68  272 0 272 3\n 3 440 0 440  31 0 31 63  272 0 272 3\n 3 448 0 448  96 0 96 69  199 0 199 3\n0\n0\n0\n2 100 0 117 0 117 0\n 0 0 428 117 428 117\n70 3 8 0 8  50 0 50 10  487 0 487 1\n 3 8 0 8  50 0 50 11  487 0 487 1\n 3 8 0 8  50 0 50 12  487 0 487 1\n 3 8 0 8  50 0 50 7  487 0 487 1\n 3 8 0 8  50 0 50 13  487 0 487 1\n 3 8 0 8  50 0 50 14  487 0 487 1\n 3 8 0 8  50 0 50 15  487 0 487 1\n 3 499 0 499  41 0 41 9  5 0 5 1\n 3 272 0 272  50 0 50 5  223 0 223 1\n 3 328 0 328  50 0 50 2  167 0 167 1\n 3 440 0 440  50 0 50 4  55 0 55 1\n 3 216 0 216  50 0 50 1  279 0 279 1\n 3 160 0 160  50 0 50 6  335 0 335 1\n 3 104 0 104  50 0 50 3  391 0 391 1\n 3 71 0 71  416 0 416 26  58 0 58 1\n 3 72 0 72  30 0 30 18  443 0 443 1\n 3 104 0 104  30 0 30 25  411 0 411 1\n 3 272 0 272  30 0 30 16  243 0 243 1\n 3 240 0 240  30 0 30 23  275 0 275 1\n 3 304 0 304  30 0 30 24  211 0 211 1\n 3 336 0 336  30 0 30 20  179 0 179 1\n 3 72 0 72  30 0 30 19  443 0 443 1\n 3 104 0 104  30 0 30 31  411 0 411 1\n 3 272 0 272  30 0 30 0  243 0 243 1\n 3 240 0 240  30 0 30 30  275 0 275 1\n 3 304 0 304  30 0 30 22  211 0 211 1\n 3 336 0 336  30 0 30 21  179 0 179 1\n 3 452 0 452  30 0 30 17  63 0 63 1\n 3 456 0 456  30 0 30 27  59 0 59 1\n 3 452 0 452  30 0 30 28  63 0 63 1\n 3 452 0 452  30 0 30 29  63 0 63 1\n 3 144 0 144 "
" 30 0 30 33  371 0 371 1\n 3 144 0 144  30 0 30 32  371 0 371 1\n 3 272 0 272  30 0 30 34  243 0 243 1\n 3 208 0 208  30 0 30 36  307 0 307 1\n 3 208 0 208  30 0 30 35  307 0 307 1\n 3 8 0 8  50 0 50 37  487 0 487 1\n 3 439 0 439  56 0 56 40  50 0 50 1\n 3 439 0 439  56 0 56 43  50 0 50 1\n 3 304 0 304  30 0 30 42  211 0 211 1\n 3 336 0 336  30 0 30 41  179 0 179 1\n 3 72 0 72  30 0 30 38  443 0 443 1\n 3 399 0 399  30 0 30 39  116 0 116 1\n 3 144 0 144  30 0 30 46  371 0 371 1\n 3 208 0 208  30 0 30 44  307 0 307 1\n 3 240 0 240  30 0 30 45  275 0 275 1\n 3 8 0 8  50 0 50 48  487 0 487 1\n 3 8 0 8  50 0 50 49  487 0 487 1\n 3 384 0 384  50 0 50 8  111 0 111 1\n 3 144 0 144  30 0 30 51  371 0 371 1\n 3 144 0 144  30 0 30 50  371 0 371 1\n 3 144 0 144  30 0 30 54  371 0 371 1\n 3 176 0 176  30 0 30 53  339 0 339 1\n 3 176 0 176  30 0 30 52  339 0 339 1\n 3 144 0 144  30 0 30 55  371 0 371 1\n 3 144 0 144  30 0 30 56  371 0 371 1\n 3 144 0 144  30 0 30 57  371 0 371 1\n 3 208 0 208  30 0 30 58  307 0 307 1\n 3 240 0 240  30 0 30 59  275 0 275 1\n 3 272 0 272  30 0 30 60  243 0 243 1\n 3 64 0 64  429 0 429 47  52 0 52 1\n 3 104 0 104  30 0 30 61  411 0 411 1\n 3 216 0 216  50 0 50 62  279 0 279 1\n 3 392 0 392  48 0 48 67  105 0 105 1\n 3 400 0 400  30 0 30 66  115 0 115 1\n 3 360 0 360  48 0 48 65  137 0 137 1\n 3 368 0 368  30 0 30 64  147 0 147 1\n 3 400 0 400  32 0 32 68  113 0 113 1\n 3 368 0 368  32 0 32 63  145 0 145 1\n 3 72 0 72  30 0 30 69  443 0 443 1\n0\nLayers 2\n\"\"  116 30 65535 65535 0\n\"\"  116 30 65535 65535 0\nEOF\n";
#endif /* !ILVNOSTATICDATA */

static void ILVCALLBACK
_SaisieRecipientCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieRecipientCB(g);
}


static void ILVCALLBACK
_secu7CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu7CB(g);
}


static void ILVCALLBACK
_tactileCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->tactileCB(g);
}


static void ILVCALLBACK
_quitterCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->quitterCB(g);
}


static void ILVCALLBACK
_AideCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->AideCB(g);
}


static void ILVCALLBACK
_SaisieSousLotCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieSousLotCB(g);
}


static void ILVCALLBACK
_FocusOutLotCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->FocusOutLotCB(g);
}


static void ILVCALLBACK
_secu8CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu8CB(g);
}


static void ILVCALLBACK
_validerCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerCB(g);
}


static void ILVCALLBACK
_tarerCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->tarerCB(g);
}


static void ILVCALLBACK
_FocusOutBalanceCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->FocusOutBalanceCB(g);
}


static void ILVCALLBACK
_ListeLotCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->ListeLotCB(g);
}


static void ILVCALLBACK
_SaisieEmplacementCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieEmplacementCB(g);
}


static void ILVCALLBACK
_SaisieBalanceCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieBalanceCB(g);
}


static void ILVCALLBACK
_secu10CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu10CB(g);
}


static void ILVCALLBACK
_secu3CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu3CB(g);
}


static void ILVCALLBACK
_validerPlusCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->validerPlusCB(g);
}


static void ILVCALLBACK
_EntreeTextFieldCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->EntreeTextFieldCB(g);
}


static void ILVCALLBACK
_SaisiePoidsPeseCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisiePoidsPeseCB(g);
}


static void ILVCALLBACK
_FocusOutRecipientCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->FocusOutRecipientCB(g);
}


static void ILVCALLBACK
_secu2CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu2CB(g);
}


static void ILVCALLBACK
_secu1CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu1CB(g);
}


static void ILVCALLBACK
_ListeRecipientCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->ListeRecipientCB(g);
}


static void ILVCALLBACK
_secu6CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu6CB(g);
}


static void ILVCALLBACK
_SaisieLotCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieLotCB(g);
}


static void ILVCALLBACK
_secu9CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu9CB(g);
}


static void ILVCALLBACK
_mettreAZeroCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->mettreAZeroCB(g);
}


static void ILVCALLBACK
_FocusOutEmplacementCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->FocusOutEmplacementCB(g);
}


static void ILVCALLBACK
_peserCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->peserCB(g);
}


static void ILVCALLBACK
_SaisieVanneCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieVanneCB(g);
}


static void ILVCALLBACK
_FocusOutSousLotCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->FocusOutSousLotCB(g);
}


static void ILVCALLBACK
_SaisieCuveCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->SaisieCuveCB(g);
}


static void ILVCALLBACK
_EntreeNumberFieldCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->EntreeNumberFieldCB(g);
}


static void ILVCALLBACK
_ListeBalanceCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->ListeBalanceCB(g);
}


static void ILVCALLBACK
_secu5CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu5CB(g);
}


static void ILVCALLBACK
_ListeEmplacementCB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->ListeEmplacementCB(g);
}


static void ILVCALLBACK
_secu4CB(IlvGraphic* g, IlAny) {
    Pesee_OF* o = (Pesee_OF*)IlvGraphic::GetCurrentCallbackHolder()->getContainer();
    if (o) o->secu4CB(g);
}


#include <ilviews/base/sstream.h>
ILVSTDUSE

// --------------------------------------------------------------------------
void
Pesee_OF::initialize() {
#if defined(ILVNOSTATICDATA)
    readFile(FILENAME);
#else  /* !ILVNOSTATICDATA */
    istrstream str((char*)_data);
    read(str);
#endif /* !ILVNOSTATICDATA */
    registerCallback("SaisieRecipientCB", _SaisieRecipientCB);
    registerCallback("secu7CB", _secu7CB);
    registerCallback("tactileCB", _tactileCB);
    registerCallback("quitterCB", _quitterCB);
    registerCallback("AideCB", _AideCB);
    registerCallback("SaisieSousLotCB", _SaisieSousLotCB);
    registerCallback("FocusOutLotCB", _FocusOutLotCB);
    registerCallback("secu8CB", _secu8CB);
    registerCallback("validerCB", _validerCB);
    registerCallback("tarerCB", _tarerCB);
    registerCallback("FocusOutBalanceCB", _FocusOutBalanceCB);
    registerCallback("ListeLotCB", _ListeLotCB);
    registerCallback("SaisieEmplacementCB", _SaisieEmplacementCB);
    registerCallback("SaisieBalanceCB", _SaisieBalanceCB);
    registerCallback("secu10CB", _secu10CB);
    registerCallback("secu3CB", _secu3CB);
    registerCallback("validerPlusCB", _validerPlusCB);
    registerCallback("EntreeTextFieldCB", _EntreeTextFieldCB);
    registerCallback("SaisiePoidsPeseCB", _SaisiePoidsPeseCB);
    registerCallback("FocusOutRecipientCB", _FocusOutRecipientCB);
    registerCallback("secu2CB", _secu2CB);
    registerCallback("secu1CB", _secu1CB);
    registerCallback("ListeRecipientCB", _ListeRecipientCB);
    registerCallback("secu6CB", _secu6CB);
    registerCallback("SaisieLotCB", _SaisieLotCB);
    registerCallback("secu9CB", _secu9CB);
    registerCallback("mettreAZeroCB", _mettreAZeroCB);
    registerCallback("FocusOutEmplacementCB", _FocusOutEmplacementCB);
    registerCallback("peserCB", _peserCB);
    registerCallback("SaisieVanneCB", _SaisieVanneCB);
    registerCallback("FocusOutSousLotCB", _FocusOutSousLotCB);
    registerCallback("SaisieCuveCB", _SaisieCuveCB);
    registerCallback("EntreeNumberFieldCB", _EntreeNumberFieldCB);
    registerCallback("ListeBalanceCB", _ListeBalanceCB);
    registerCallback("secu5CB", _secu5CB);
    registerCallback("ListeEmplacementCB", _ListeEmplacementCB);
    registerCallback("secu4CB", _secu4CB);
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
Pesee_OF::SaisieRecipientCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieRecipientCB method ...",className);
}

void
Pesee_OF::secu7CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu7CB method ...",className);
}

void
Pesee_OF::tactileCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : tactileCB method ...",className);
}

void
Pesee_OF::quitterCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : quitterCB method ...",className);
}

void
Pesee_OF::AideCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : AideCB method ...",className);
}

void
Pesee_OF::SaisieSousLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieSousLotCB method ...",className);
}

void
Pesee_OF::FocusOutLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : FocusOutLotCB method ...",className);
}

void
Pesee_OF::secu8CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu8CB method ...",className);
}

void
Pesee_OF::validerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerCB method ...",className);
}

void
Pesee_OF::tarerCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : tarerCB method ...",className);
}

void
Pesee_OF::FocusOutBalanceCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : FocusOutBalanceCB method ...",className);
}

void
Pesee_OF::ListeLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : ListeLotCB method ...",className);
}

void
Pesee_OF::SaisieEmplacementCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieEmplacementCB method ...",className);
}

void
Pesee_OF::SaisieBalanceCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieBalanceCB method ...",className);
}

void
Pesee_OF::secu10CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu10CB method ...",className);
}

void
Pesee_OF::secu3CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu3CB method ...",className);
}

void
Pesee_OF::validerPlusCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : validerPlusCB method ...",className);
}

void
Pesee_OF::EntreeTextFieldCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : EntreeTextFieldCB method ...",className);
}

void
Pesee_OF::SaisiePoidsPeseCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisiePoidsPeseCB method ...",className);
}

void
Pesee_OF::FocusOutRecipientCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : FocusOutRecipientCB method ...",className);
}

void
Pesee_OF::secu2CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu2CB method ...",className);
}

void
Pesee_OF::secu1CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu1CB method ...",className);
}

void
Pesee_OF::ListeRecipientCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : ListeRecipientCB method ...",className);
}

void
Pesee_OF::secu6CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu6CB method ...",className);
}

void
Pesee_OF::SaisieLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieLotCB method ...",className);
}

void
Pesee_OF::secu9CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu9CB method ...",className);
}

void
Pesee_OF::mettreAZeroCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : mettreAZeroCB method ...",className);
}

void
Pesee_OF::FocusOutEmplacementCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : FocusOutEmplacementCB method ...",className);
}

void
Pesee_OF::peserCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : peserCB method ...",className);
}

void
Pesee_OF::SaisieVanneCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieVanneCB method ...",className);
}

void
Pesee_OF::FocusOutSousLotCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : FocusOutSousLotCB method ...",className);
}

void
Pesee_OF::SaisieCuveCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : SaisieCuveCB method ...",className);
}

void
Pesee_OF::EntreeNumberFieldCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : EntreeNumberFieldCB method ...",className);
}

void
Pesee_OF::ListeBalanceCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : ListeBalanceCB method ...",className);
}

void
Pesee_OF::secu5CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu5CB method ...",className);
}

void
Pesee_OF::ListeEmplacementCB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : ListeEmplacementCB method ...",className);
}

void
Pesee_OF::secu4CB(IlvGraphic* g) {
    const char* className = g->className();
    IlvPrint(" %s : secu4CB method ...",className);
}

