// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/i18n/src/changelang.cpp
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Sample to show how to use localized message database files and change the
// display language of the UI.
// --------------------------------------------------------------------------

#include <ilviews/ilv.h>
#include <ilviews/base/message.h>
#include <ilviews/base/graphic.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilog/pathname.h>

#if defined(IL_STD)
#include <fstream>
#include <cstdio>
IL_STDUSE
#else
#include <fstream.h>
#include <stdio.h>
#endif

// --------------------------------------------------------------------------
// This subclass of IlvContainer is the main panel of the application.
// It contains some labels, and buttons.
// --------------------------------------------------------------------------
class ChangeLangMainWindow
: public IlvGadgetContainer
{
public:
    ChangeLangMainWindow(IlvDisplay*    display,
			 const char*    name,
			 const char*    title,
			 const IlvRect& dims,
			 IlBoolean     visible = IlTrue)
    : IlvGadgetContainer(display, name, title, dims, IlFalse, visible)
    {
	// Read the message database file
	display->getDatabase()->read("changelang.dbm", display);
	// Read the description file
	readFile("changelang.ilv");
	// Read the graphic file 
	getFlag()->setBitmap(display->readBitmap("flag.png"));

	// Register the callbacks
	registerCallback("ChangeLangCB", ChangeLangCB);
	registerCallback("QuitCB", QuitCB);
    }

    ~ChangeLangMainWindow()
    {
    }
    // ______________________________________________________________________
    static void ChangeLangCB(IlvGraphic*  g,
			     IlAny /* arg */)
    {
	ChangeLangMainWindow* holder = (ChangeLangMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	const IlvValue* value = IlvGraphic::GetCurrentCallbackValue();
	if (value && value->getType() != IlvValueNoType) {
	    const char* lang = (const char*)(*value);
	    if (holder)
		holder->changelang(lang);
	}
    }
    void changelang(const char* lang)
    {
	// This call will read again the message database files in their new
	// localized paths.
	getDisplay()->setCurrentLanguage(IlvGetSymbol(lang));
	// Read again the graphic file, so that the right flag is displayed.
	getFlag()->setBitmap(getDisplay()->readBitmap("flag.png"));
	getFlag()->reDraw();
    }
    // ______________________________________________________________________
    static void QuitCB(IlvGraphic* /* g */,
		       IlvAny /* arg */)
    {
	ChangeLangMainWindow* holder = (ChangeLangMainWindow*)
	    IlvGraphic::GetCurrentCallbackHolder()->getContainer();
	if (holder)
	    holder->quit();
    }
    void quit()
    {
	delete getDisplay();
	IlvExit(0);
    }
    // ______________________________________________________________________
    IlvMessageLabel* getFlag() const
	{ return (IlvMessageLabel*)getObject("Flag"); }
};

// ------------------------------------------------------
// Entry point
// ------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    if (!IlvSetLocale())
	printf("Falling back to the C locale\n");
    IlvDisplay* display = new IlvDisplay("Change UI Language Sample", "", 
					 argc, argv);
    if (display->isBad()) {
        delete display;
        IlvFatalError("Couldn't create display");
        return -1;
    }
    IlPathName localPath(display->getHomePath());
    localPath.addDirectory("samples/foundation/i18n/data");
    display->prependToPath(localPath);
    
    ChangeLangMainWindow* container =
	new ChangeLangMainWindow(display, "Change UI Language Sample", 
				 "Change UI Language Sample", 
				 IlvRect(50, 50, 420, 220), IlFalse);

    container->show();
    IlvMainLoop();
    return 0;
}
