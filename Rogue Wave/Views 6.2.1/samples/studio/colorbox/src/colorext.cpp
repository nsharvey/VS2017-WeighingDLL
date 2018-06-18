// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/colorbox/src/colorext.cpp
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
// Definition of the MyStudioExtension class
// Initialize the extension
// --------------------------------------------------------------------------

#include <ivstudio/studio.h>
#include <ivstudio/inspect.h>
#include <ivstudio/appcode.h>
#include <ivstudio/option.h>
#include <ivstudio/buffer.h>

#include <ivstudio/graphicx.h>
#include <ivstudio/gadgets/gadgetx.h>
#include <ivstudio/appli/applix.h>
#include <ivstudio/appli/genext.h>
#ifdef WINDOWS
#include <ivstudio/windows/winext.h>
#endif

#include <colorbox.h>
#include <colorpnl.h>
#include <colorext.h>

// --------------------------------------------------------------------------
static const char* ExtName = "ColorBox";

// --------------------------------------------------------------------------
MyStudioExtension*
MyStudioExtension::Get(IlvStudio* editor)
{
    return (MyStudioExtension*)editor->getExtension(ExtName);
}

// --------------------------------------------------------------------------
MyStudioExtension*
MyStudioExtension::Make(IlvStudio* editor)
{
    // Take care of wanted extensions
    IlvStGraphicExtension::Make(editor);
    IlvStGadgetExtension::Make(editor);
    IlvStGenerationExtension::Make(editor);
    IlvStApplicationExtension::Make(editor);
#ifdef WINDOWS
    IlvStWindowsExtension::Make(editor);
#endif

    // Create my own extension
    MyStudioExtension* ext = Get(editor);
    if (!ext)
	ext = new MyStudioExtension(editor);
    return ext;
} // MyStudioExtension::Make

// --------------------------------------------------------------------------
MyStudioExtension::MyStudioExtension(IlvStudio* editor)
    : IlvStExtension(ExtName, editor)
{
    editor->addOptionFile("colorbox.opt");
}

// --------------------------------------------------------------------------
IlvBoolean
MyStudioExtension::preInitialize()
{
    // Add the path
    const char* home = _editor->getDisplay()->getEnvOrResource("ILVHOME", 0);
        if (home && *home) {
          IlString strHome = home;
          strHome+= "/";
          IlPathName dataPath = strHome;
          dataPath.addDirectory("samples/studio/colorbox/data/");
          _editor->getDisplay()->prependToPath((const char*)dataPath);
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
#include <ivstudio/edit.h>

class AddColorComboBox: public IlvStClickAddObject
{
protected:
    virtual IlvStError* makeObject(IlvGraphic*& obj,
				   IlvStudio* ed,
				   IlAny)
    {
	IlvColorComboBox* colorCB =
	    new IlvColorComboBox(ed->getDisplay(), IlvRect(0, 0, 100, 23));
	obj = colorCB;

	// Set default 16 colors
	IlUInt count = (IlUInt)colorCB->getCardinal();
	IlvColor* colors[16];
#define INTENSITY(c) \
    (IlUShort)(IlUInt)((long)0xFFFF * (long)c / (long)255)
#define RGB_COLOR(r, g, b) \
    ed->getDisplay()->getColor(INTENSITY(r), INTENSITY(g), INTENSITY(b))

	colors[0]  = RGB_COLOR(   0,   0,   0);
	colors[1]  = RGB_COLOR( 255, 255, 255);
	colors[2]  = RGB_COLOR( 192, 192, 192); // Light gray
	colors[3]  = RGB_COLOR( 255,   0,   0); // Red
	colors[4]  = RGB_COLOR( 255, 255,   0); // yellow
	colors[5]  = RGB_COLOR(   0, 255,   0); // green
	colors[6]  = RGB_COLOR(   0, 255, 255); // cyan
	colors[7]  = RGB_COLOR(   0,   0, 255); // blue
	colors[8]  = RGB_COLOR( 255,   0, 255); // magenta
	colors[9]  = RGB_COLOR( 128, 128, 128); // Dark gray
	colors[10] = RGB_COLOR( 128,   0,   0); // Dark red
	colors[11] = RGB_COLOR( 128, 128,   0); // Dark yellow
	colors[12] = RGB_COLOR(   0, 128,   0); // Dark green
	colors[13] = RGB_COLOR(   0, 128, 128); // Dark cyan
	colors[14] = RGB_COLOR(   0,   0, 128); // Dark blue
	colors[15] = RGB_COLOR( 128,   0, 128); // Dark magenta
	colorCB->setColors(colors,
			   (IlUShort)(sizeof(colors) / sizeof(colors[0])));
	count = (IlUInt)colorCB->getCardinal();
	colorCB->setSelected(0);
	return 0;
    }
};

// --------------------------------------------------------------------------
static IlvStCommand* ILVCALLBACK
MkAddColorComboBox(IlvStudio*)
{
    return new AddColorComboBox;
}

// --------------------------------------------------------------------------
IlBoolean
MyStudioExtension::initializeCommandDescriptors()
{
    // register my commands
    _editor->registerCommand("AddColorComboBox", MkAddColorComboBox);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlvBoolean
MyStudioExtension::initializeInspectors()
{
    // You might need those variables in a more complex application
    // IlvSystemView transientFor = _editor->getTransientFor();
    // IlvManager*   manager      = _editor->getManager();
    _editor->inspector().registerBuilder("IlvColorComboBox",
					 new IlvColorInspectorPanelBuilder);
    return IlTrue;
}
