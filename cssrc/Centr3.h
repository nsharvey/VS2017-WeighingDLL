// -------------------------------------------------------------- -*- C++ -*-
// File: C:\GitHub\VS2017-WeighingDLL\cssrc\Centr3.h
//                                                    application header file
// File generated Mon Jun 18 12:06:26 2018
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------

#ifndef __Centr3__header__
#define __Centr3__header__

#include <ilviews/gadgets/appli.h>

#include <clavier_tactile.h>
#include <accueil.h>
#include <selection_phase.h>
#include <selection_OF.h>
#include <pesee_OF.h>
#include <Pesee_Etalon.h>
#include <selection_Balance.h>
#include <selection_EtalonLigne.h>
#include <selection_LOT.h>
#include <selection_MWF.h>
#include <selection_Recipient.h>
#include <Choix_Balance.h>
#include <choix_OF.h>
#include <message.h>
#include <phrase_Secu.h>
#include <recontrole_OF.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Testapp: public IlvApplication {
public:
    Testapp(
        const char* appName,
        const char* displayName = 0,
        int argc = 0,
        char** argv = 0
    );
    Testapp(
        IlvDisplay* display,
        const char* appName
    );
    ~Testapp();
    virtual void makePanels();
    virtual void beforeRunning();
};

#endif /* !__Centr3__header__*/
