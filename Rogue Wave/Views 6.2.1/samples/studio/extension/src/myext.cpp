// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/studio/extension/src/myext.cpp
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
// Implementation of the MyStudioExtension class
// Initialize the extension
// --------------------------------------------------------------------------

#include <ivstudio/studio.h>
#include <ivstudio/inspect.h>
#include <ivstudio/appcode.h>
#include <ivstudio/option.h>
#include <ivstudio/buffer.h>
#include <ivstudio/continfo.h>
#include <ilog/pathname.h>

#include <ivstudio/graphicx.h>
#include <ivstudio/appli/applix.h>
#include <ivstudio/appli/genext.h>
#include <ivstudio/gadgets/gadgetx.h>
#if defined(WINDOWS)
#include <ivstudio/windows/winext.h>
#endif


#include <mybuf.h>
#include <myclass.h>
#include <myclinsp.h>
#include <myext.h>
#include <myinter.h>
#include <mypan.h>
#include <mycont.h>

// --------------------------------------------------------------------------
static const char* ExtName = "MyStudioExtension";

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
    // Make all needed extensions.
    // Note: these extensions are made by the IlvStDefaultExtension
    // implemented in the studio/src/defaultx.cpp file
    IlvStGraphicExtension::Make(editor);
    IlvStGadgetExtension::Make(editor);
    IlvStGenerationExtension::Make(editor);
    IlvStApplicationExtension::Make(editor);
#ifdef WINDOWS
    IlvStWindowsExtension::Make(editor);
#endif

    // Create My Studio Extension if it is not yet created.
    MyStudioExtension* ext = Get(editor);
    if (!ext)
	ext = new MyStudioExtension(editor);
    return ext;
}

// --------------------------------------------------------------------------
MyStudioExtension::MyStudioExtension(IlvStudio* editor)
    : IlvStExtension(ExtName, editor)
{
    editor->addOptionFile("mystudio.opt");
}

// --------------------------------------------------------------------------
// A buffer constructor
static IlvStBuffer* ILVCALLBACK
MakeMyBuffer(IlvStudio*  editor,
	     const char* name,
	     const char*)
{
    return new MyGadgetBuffer(editor, name);
}

// --------------------------------------------------------------------------
class MyContainerInfo : public IlvStContainerInfo
{
public:
    MyContainerInfo() : IlvStContainerInfo("MyContainer") {}
    IlvContainer* createContainer(IlvAbstractView* parent,
				  const IlvRect&   bbox,
				  IlBoolean       useacc,
				  IlBoolean       visible)
    {
	return new MyContainer(parent, bbox, useacc, visible);
    }
    IlvContainer* createContainer(IlvDisplay*	   display,
				  const char*      name,
				  const char*      title,
				  const IlvRect&   bbox,
				  IlUInt           properties,
				  IlBoolean        useacc,
				  IlBoolean        visible,
				  IlvSystemView    transientFor) {
	return new MyContainer(display,
			       name,
			       title,
			       bbox,
			       properties,
			       useacc,
			       visible,
			       transientFor);
    }
    const char* getFileCreatorClass() const {
	return "MyGadgetManagerOutput";
    }
}; // class MyContainerInfo

// --------------------------------------------------------------------------


// --------------------------------------------------------------------------
IlBoolean
MyStudioExtension::preInitialize()
{
    IlvStudio* editor = getEditor();
    // Add the path
    IlPathName localPath(editor->getDisplay()->getHomePath());
    localPath.addDirectory("samples/studio/extension/data");
    editor->getDisplay()->prependToPath(localPath);
    // Must be done here so
    // The first default buffer will be a MyGadgetBuffer
    editor->buffers().setDefaultConstructor(MakeMyBuffer);
    // Add the container info
    editor->addContainerInfo(new MyContainerInfo());    
    return IlTrue;
}

// --------------------------------------------------------------------------
IlBoolean
MyStudioExtension::initializePanels()
{
    // Create MyPanel
    MyPanelHandler* pan = new MyPanelHandler(getEditor(), "MyPanel");
    pan->connect();
    return IlTrue;
}

// --------------------------------------------------------------------------
static IlvStCommand* ILVCALLBACK
MkMyShowGadgetPalette(IlvStudio* editor)
{
    return new IlvStShowPanel(editor->getPanel("MyGadgets"));
}

// --------------------------------------------------------------------------
static IlvStCommand* ILVCALLBACK
MkMyShowPanel(IlvStudio* editor)
{
    return new IlvStShowPanel(editor->getPanel("MyPanel"));
}

// --------------------------------------------------------------------------
#include <ivstudio/edit.h>

class MyAddClass: public IlvStClickAddObject
{
protected:
    virtual IlvStError* makeObject(IlvGraphic*& obj,
				   IlvStudio* ed,
				   IlAny)
    {
	MyClass* mc = new MyClass(ed->getDisplay(), IlvRect(0, 0, 40, 40));
	obj = mc;
	return 0;
    }
};

// --------------------------------------------------------------------------
static IlvStCommand* ILVCALLBACK
MkMyAddClass(IlvStudio*)
{
    return new MyAddClass;
}

// --------------------------------------------------------------------------
class MyNewBuffer: public IlvStCommand
{
public:
    virtual IlvStError* doIt(IlvStudio*,
			     IlAny);
};

// --------------------------------------------------------------------------
IlvStError*
MyNewBuffer::doIt(IlvStudio* editor,
		  IlAny arg)
{
    if (arg) {
        editor->buffers().setCurrent((IlvStBuffer*)arg);
        return 0;
    }
    const char* name = editor->options().getDefaultBufferName();
    IlvStBuffer* buffer = new MyGadgetBuffer(editor, name);
    if (editor->buffers().get(name))
	buffer->newName(name); // uniq name
    return editor->execute(IlvNmNewBuffer, 0, 0, buffer);
} // IlvStNewVariableBuffer::doIt

// --------------------------------------------------------------------------
static IlvStCommand* ILVCALLBACK
MkMyNewBuffer(IlvStudio*) { return new MyNewBuffer; }

// --------------------------------------------------------------------------
IlBoolean
MyStudioExtension::initializeCommandDescriptors()
{
    // register my commands
    IlvStudio* editor = getEditor();
    editor->registerCommand("MyShowPanel", MkMyShowPanel);
    editor->registerCommand("MyShowGadgetPalette", MkMyShowGadgetPalette);
    editor->registerCommand("AddMyClass", MkMyAddClass);
    editor->registerCommand("MyNewBuffer", MkMyNewBuffer);
    return IlvTrue;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
MyCallback(IlvGraphic*,
	   IlAny)
{
    IlvPrint("MyCallback is called");
}

// --------------------------------------------------------------------------
IlBoolean
MyStudioExtension::initializeBuffers()
{
    IlvStudio* editor = getEditor();
    editor->buffers().registerType("MyGadgetManagerOutput", MakeMyBuffer);
    editor->registerCallback("MyCallback", MyCallback);
    editor->registerCallback("myCallback", MyCallback);
    return IlTrue;
}

// --------------------------------------------------------------------------
IlvBoolean
MyStudioExtension::initializeInspectors()
{
    IlvStudio* editor = getEditor();
    editor->inspector().registerBuilder("MyClass", new MyClassInspectorBuilder);
    return IlvTrue;
}

// --------------------------------------------------------------------------
