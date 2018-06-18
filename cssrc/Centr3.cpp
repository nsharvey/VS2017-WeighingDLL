// -------------------------------------------------------------- -*- C++ -*-
// File: C:\GitHub\Weighing2017\cssrc\Centr3.cpp
//                                                    application source file
// File generated Thu Jun 14 11:11:09 2018
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------

#include <Centr3.h>
#include <ilviews/jvscript/script.h>
#include <ilviews/gadgets/scrdlg.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
Testapp::Testapp(const char* appName,
                 const char* displayName,
                 int argc,
                 char** argv)
: IlvApplication(appName, displayName, argc, argv)
{
}

// --------------------------------------------------------------------------
Testapp::Testapp(IlvDisplay* display,
                 const char* appName)
: IlvApplication(display, appName)
{
}

// --------------------------------------------------------------------------
Testapp::~Testapp()
{
}

// --------------------------------------------------------------------------
void
Testapp::beforeRunning()
{
    IlvApplication::beforeRunning();
}

// --------------------------------------------------------------------------
void
Testapp::makePanels()
{
    // --- Bind the Application to JvScript ---
    IlvJvScriptLanguage::GetGlobalContext()->
        bind(this, "Application");
    IlvJvScriptLanguage::InitAuxiliaryLib(getDisplay());
}

// --------------------------------------------------------------------------
// C++ entry point
// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    IlvSetLocale();
    Testapp* appli = new Testapp("Centr3", 0, argc, argv);
    if (!appli->getDisplay())
        return -1;
    appli->run();
    return 0;
}