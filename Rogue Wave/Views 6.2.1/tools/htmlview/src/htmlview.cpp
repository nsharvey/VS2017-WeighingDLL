// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/htmlview/src/htmlview.cpp
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
// --------------------------------------------------------------------------
// Demonstrating the IlvAnnoText object reading HTML files
// --------------------------------------------------------------------------

#include <sys/types.h>

#if defined(_MSC_VER)
#  include <windows.h>
#  include <errno.h>
#endif
#if defined(__TCPLUSPLUS__)
#  include <windows.h>
#endif

#include <ilviews/gadgets/gadcont.h>
#include <ilviews/contain/inter.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/base/memory.h>

#if defined(WINDOWS)
#  include <ilviews/windows/dump.h>
#else
#  include <ilviews/util/ps.h>
#if defined (OS2)
#  define TMPFILENAME "c:/tmp/annodump.ps"
#else
#  define TMPFILENAME "/tmp/annodump.ps"
#endif /* !OS2 */
#endif /* !WINDOWS */

#if defined(IL_STD)
#  include <cstring>
#  include <iostream>
#  include <cstdio>
#  include <cstdlib>
#  include <fstream>
#else  /* !IL_STD */
#  include <string.h>
#  include <iostream.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <fstream.h>
#endif /* IL_STD */

IL_STDUSE 

#include <ilviews/annotext/annotext.h>
#include <ilviews/annotext/cursor.h>
#include <ilviews/annotext/zone.h>
#include <ilviews/annotext/html.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/annotext/htmlload.h>
#include "../src/wheelint.h"

extern "C" IlBoolean IlvSetLanguage();

// Allows the apparition of the tRef textfield, for debugging purposes
static IlBoolean refVisible = IlTrue;

// Number of opened panels
static IlUInt nPanels = 0;

// Symbol for history management
static IlSymbol* HtmlHistory = IlGetSymbol("HtmlHistory");

// --------------------------------------------------------------------------
IlBoolean
ViewerHtmlReader::parseTag(IlvATHtmlText* text,
			   char*          sourceTag,
			   IlvATCursor*   insert,
			   istream&       stream)
{
  // Keep track of tag type
  IlBoolean close = IlFalse; // </tag> case
  IlBoolean empty = IlFalse; // <tag/> case
  char* tagCopy = 0;
  char* tag = sourceTag;
  // Skip closing escape char ('/')
  if (tag[0] == '/') {
    close = IlTrue;
    tag++;
  }
  else if (tag[strlen(tag)-1] == '/') {
    empty = IlTrue;
    tagCopy = IlCopyString(tag);
    tagCopy[strlen(tag)-1] = 0;
    tag = tagCopy;
  }
  // Tags that are recognized, but badly translated
  if ( // Tables:
      !strcmp(tag, "table") ||
      !strcmp(tag, "tr")    ||
      !strcmp(tag, "th")    ||
      !strcmp(tag, "td")    ||
      !strcmp(tag, "dd")    ||
      !strcmp(tag, "dl")    ||
      !strcmp(tag, "dt")) {
    if (!close)
      text->insertParagraph(insert);
    return IlTrue;
  }
  // Read but not translated:
  if (!strcmp(tag, "head")       ||
      !strcmp(tag, "html")       ||
      !strcmp(tag, "blockquote") ||
      !strcmp(tag, "body")       ||
      !strcmp(tag, "address")    ||
      !strncmp(tag, "!--", 3)    ||
      !strcmp(tag, "center")     ||
      !strcmp(tag, "code")       ||
      !strcmp(tag, "kbd")        ||
      !strcmp(tag, "samp")       ||
      !strcmp(tag, "form")       ||
      !strcmp(tag, "textarea")   ||
      !strcmp(tag, "select")     ||
      !strcmp(tag, "option")     ||
      !strcmp(tag, "div")        ||
      !strcmp(tag, "font")       ||
      !strcmp(tag, "tt"))
    return IlTrue;
  if (empty) {
    // Pretend we have seen <tag></tag>
    IlBoolean res = IlvATHtmlReader::parseTag(text, tag, insert, stream);
    // Build </tag>
    for (int loop = strlen(tag); loop > 0; loop--) {
      tagCopy[loop] = tag[loop-1];
    }
    tagCopy[0] = '/';
    res &= IlvATHtmlReader::parseTag(text, tagCopy, insert, stream);
    delete [] tagCopy;
    return res;
  }
  else {
    return IlvATHtmlReader::parseTag(text, sourceTag, insert, stream);
  }
}

// --------------------------------------------------------------------------
static void
Quit(IlvView* view,
     IlAny)
{
  IlvDisplay* display = view->getDisplay();
  delete view;
  if (--nPanels == 0) {
    delete display;
    IlvExit(0);
  }
}

// --------------------------------------------------------------------------
static void
Quit(IlvGraphic* g,
     IlAny)
{
  Quit(IlvContainer::getContainer(g), 0);
}

// --------------------------------------------------------------------------
static void
ToggleEdit(IlvGraphic* g,
	   IlAny)
{
  IlvContainer*  cont = IlvContainer::getContainer(g);
  IlvToggle*     tog  = (IlvToggle*)g;
  IlvATHtmlText* text = (IlvATHtmlText*)cont->getObject("Text");
  text->setEditable(tog->getState());
}

// --------------------------------------------------------------------------
#if 0
static void
EmptyText(IlvGraphic* g,
	  IlAny)
{
  IlvContainer*  cont = IlvContainer::getContainer(g);
  IlvATHtmlText* text = (IlvATHtmlText*) cont->getObject("Text");
  text->emptyText();
  text->computeLines();
  cont->reDrawObj(text);
}
#endif

// --------------------------------------------------------------------------
#if 0
static void
PrintContents(IlvGraphic* g,
	      IlAny)
{
  IlvContainer* cont = IlvContainer::getContainer(g);
  IlvATHtmlText* text = (IlvATHtmlText*) cont->getObject("Text");
  IlFloat xmargin = (IlFloat)18.0;
  IlFloat ymargin = (IlFloat)30.0;
  IlvTransformer t((IlFloat)1, (IlFloat)0,
		   (IlFloat)0, (IlFloat)1, xmargin, ymargin);
  IlvRect initbbox(0, 0, 0, 0);
#if !defined(WINDOWS)
  IlvPSDevice psdevice(cont->getDisplay());
  initbbox.w(psdevice.getPaperWidth () - 2 * ((IlvDim)xmargin));
  initbbox.h(psdevice.getPaperHeight () - 2 * ((IlvDim)ymargin));
  if (psdevice.init(TMPFILENAME, &initbbox)) {
    text->printContents(&psdevice, t, initbbox);
    psdevice.end();
  }
#else  /* WINDOWS */
  IlvWindowsDevice windevice(cont->getDisplay());
  const char* printer = IlvGetWindowsPrinter(IlTrue);
  if (printer) {
    windevice.init(printer);
    initbbox.w(windevice.getPaperWidth () - 2 * ((IlvDim)xmargin));
    initbbox.h(windevice.getPaperHeight () - 2 * ((IlvDim)ymargin));
    windevice.clip(&initbbox);
    text->printContents(&windevice, t, initbbox);
    windevice.end();
  }
#endif /* WINDOWS */
}
#endif

// --------------------------------------------------------------------------
static IlBoolean
LinkLoad(IlvGraphic* g,
	 IlBoolean history)
{
  IlvContainer* container = IlvContainer::getContainer(g);
  IlvTextField* tRef   = (IlvTextField*)container->getObject("Reference");
  char refString[ILVATREFSIZE];
  IlvATHtmlText* text    = (IlvATHtmlText*)container->getObject("Text");
  IlBoolean result = IlFalse;
  if (tRef->getLabel()) {
    strcpy(refString, tRef->getLabel());
    ViewerHtmlReader* reader = (ViewerHtmlReader*)text->getReader();
    if (reader->linkLoad(text, refString, history)) {
      tRef->setLabel(refString);
      container->reDrawObj(tRef);
      container->setTitle(text->getReader()->getTitle());
      result = IlTrue;
    }
  }
  return result;
}

// --------------------------------------------------------------------------
static void
Reload(IlvGraphic* g,
       IlAny)
{
  IlvContainer* container = IlvContainer::getContainer(g);
  IlvTextField* tRef = (IlvTextField*)container->getObject("Reference");
  IlvATHtmlHistory* hist =
    (IlvATHtmlHistory*)tRef->getProperty(HtmlHistory);
  tRef->setLabel(hist->getRef().getString().getValue());
  IlvATHtmlText* text    = (IlvATHtmlText*)container->getObject("Text");
  text->setCurrentPath("");
  container->reDrawObj(tRef);
  LinkLoad(g, IlTrue);
}

// --------------------------------------------------------------------------
static void
LoadNew(IlvGraphic* g,
	IlAny)
{
  IlvContainer* container = IlvContainer::getContainer(g);
  if (LinkLoad(g, IlFalse)) {
    IlvTextField* tRef = (IlvTextField*)container->getObject("Reference");
    IlvATHtmlHistory* hist =
      (IlvATHtmlHistory*)tRef->getProperty(HtmlHistory);
    hist->addPage(tRef->getLabel());
  }
}

// --------------------------------------------------------------------------
static void
Home(IlvGraphic* g,
     IlAny)
{
  IlvContainer* container = IlvContainer::getContainer(g);
  IlvTextField* tRef = (IlvTextField*)container->getObject("Reference");
  IlvATHtmlText* text    = (IlvATHtmlText*)container->getObject("Text");
  tRef->setLabel(text->getReader()->getHome().getString().getValue());
  if (refVisible)
    container->reDrawObj(tRef);
  char refString  [ILVATREFSIZE];
  strcpy(refString, tRef->getLabel());
  text->setCurrentPath("");
  ViewerHtmlReader* reader = (ViewerHtmlReader*) text->getReader();
  reader->linkLoad(text, refString, IlFalse);
  tRef->setLabel(refString);
  if (refVisible)
    container->reDrawObj(tRef);
  container->setTitle(text->getReader()->getTitle());
  IlvATHtmlHistory* hist =
    (IlvATHtmlHistory*)tRef->getProperty(HtmlHistory);
  hist->addPage(tRef->getLabel());
}

// --------------------------------------------------------------------------
static void
LinkBack(IlvGraphic* g,
	 IlAny)
{
  IlvContainer* container = IlvContainer::getContainer(g);
  IlvTextField* tRef = (IlvTextField*)container->getObject("Reference");
  IlvATHtmlHistory* hist =
    (IlvATHtmlHistory*)tRef->getProperty(HtmlHistory);
  if (hist->back()) {
    tRef->setLabel(hist->getRef().getString().getValue());
    container->reDrawObj(tRef);
    LinkLoad(g, IlTrue);
  }
  else
    container->getDisplay()->bell();
}

// --------------------------------------------------------------------------
static void
LinkForward(IlvGraphic* g,
	    IlAny)
{
  IlvContainer* container = IlvContainer::getContainer(g);
  IlvTextField* tRef = (IlvTextField*)container->getObject("Reference");
  IlvATHtmlHistory* hist =
    (IlvATHtmlHistory*)tRef->getProperty(HtmlHistory);
  if (hist->forward()) {
    tRef->setLabel(hist->getRef().getString().getValue());
    container->reDrawObj(tRef);
    LinkLoad(g, IlTrue);
  }
  else
    container->getDisplay()->bell();
}

// --------------------------------------------------------------------------
// Add buttons
// --------------------------------------------------------------------------
IlvButton*
AddButton(IlvGadgetContainer* cont,
	  const char*         label,
	  IlvRect&            rect,
	  IlvDim              margin)
{
  IlvDisplay* display = cont->getDisplay();
  IlvButton* button = new IlvButton(display, label, rect);
  cont->addObject(button);
  IlvSetAttachment(button, IlvTop, IlvFixedAttach, margin);
  rect.translate(rect.w(), 0);
  return button;
}

// --------------------------------------------------------------------------
static void
AddTextPanel(IlvDisplay*,
	     ViewerHTMLReader*);

static void
AddPanel(IlvGraphic* g,
	 IlAny)
{
  IlvContainer* cont = IlvContainer::getContainer(g);
  IlvATHtmlText* text = (IlvATHtmlText*)cont->getObject("Text");
  AddTextPanel(cont->getDisplay(), (ViewerHtmlReader*)(text->getReader()));
}

// --------------------------------------------------------------------------
// Defining accelerator functions for line scrolling
// --------------------------------------------------------------------------
static void
AccScrollUp(IlvAnnoText* atext,
	    IlvEvent&,
	    IlAny)
{
  IlvContainer* cont = IlvContainer::getContainer(atext);
  if (atext->scrollUpLines(1))
    cont->reDrawObj(atext);
}

// --------------------------------------------------------------------------
static void
AccScrollDown(IlvAnnoText* atext,
	      IlvEvent&,
	      IlAny)
{
  IlvContainer* cont = IlvContainer::getContainer(atext);
  if (atext->scrollDownLines(1))
    cont->reDrawObj(atext);
}

// --------------------------------------------------------------------------
// Adding a Text Panel
// --------------------------------------------------------------------------
static void
AddTextPanel(IlvDisplay* display,
	     ViewerHTMLReader* htmlReader)
{
  nPanels++;
  // Dimension parameters
  IlvDim refHeight    = 20;
  IlvDim refLeft      = 100;
  IlvDim buttonHeight = 20;
  IlvDim buttonWidth  = 60;
  IlvDim totalWidth   = 640;
  IlvDim totalHeight  = 480;
  IlvDim panelOffset  = 70;
  IlvDim margin       = 5;
  IlvDim refSpace     = refVisible ? (refHeight + margin) : 0;
  IlvRect size(panelOffset * nPanels, panelOffset * nPanels,
	       totalWidth, totalHeight);
  IlvGadgetContainer* cont =
    new IlvGadgetContainer(display,
			   "HTML Viewer",
			   "HTML Viewer",
			   size,
			   IlFalse);
  IlvRect bbox(margin,
	       2 * margin + buttonHeight + refSpace,
	       totalWidth - 2 * margin,
	       totalHeight - 3 * margin - refSpace - buttonHeight);
  // Getting environment resources
  // Text manipulation
  IlvATHtmlText* text =
    new IlvATHtmlText(display, bbox, htmlReader->getDefaultStyle());
  text->setReader(htmlReader);
  cont->addObject(text);
  cont->setObjectName(text, "Text");

  // Interactor
  text->setInteractor(new IlvScrolledGadgetPanInteractor(text));

  // Accelerators
  text->addAccelerator(AccScrollUp, IlvKeyDown, IlvCtrlChar('u'), 0, 0);
  text->addAccelerator(AccScrollDown, IlvKeyDown, IlvCtrlChar('d'), 0, 0);

  // Attachments on the text
  IlvSetAttachment(text, IlvLeft,   IlvFixedAttach, margin);
  IlvSetAttachment(text, IlvTop, IlvFixedAttach,
		   2 * margin + buttonHeight + refSpace);
  IlvSetAttachment(text, IlvRight,  IlvFixedAttach, margin);
  IlvSetAttachment(text, IlvBottom, IlvFixedAttach, margin);
  IlvSetAttachment(text, IlvVertical,   IlvElasticAttach);
  IlvSetAttachment(text, IlvHorizontal, IlvElasticAttach);

  // Textfield
  bbox.moveResize(refLeft, 2 * margin + buttonHeight,
		  totalWidth - (refLeft + margin), refHeight);
  IlvTextField* tRef =
    new IlvTextField(display, htmlReader->getHome().getString().getValue(),
		     bbox);
  cont->addObject(tRef);
  cont->setObjectName(tRef, "Reference");
  if (!refVisible)
    cont->setVisible(tRef, IlFalse);
  else {
    IlvSetAttachment(tRef, IlvLeft,  IlvFixedAttach, refLeft);
    IlvSetAttachment(tRef, IlvRight, IlvFixedAttach, margin);
    IlvSetAttachment(tRef, IlvTop, IlvFixedAttach, 2 * margin + buttonHeight);
    IlvSetAttachment(tRef, IlvHorizontal, IlvElasticAttach);
  }
  tRef->setCallback(LoadNew);
  
  // Label
  if (refVisible) {
    IlvLabel* lRef =
      new IlvLabel(display, margin,
		   2 * margin + buttonHeight + refHeight - 4,
		   "Reference");
    cont->addObject(lRef);
  }

  // button row
  bbox.moveResize(margin, margin, buttonWidth, buttonHeight);
  // The another    button
  IlvButton* banoth  = AddButton(cont, "Another", bbox, margin);
  banoth->setCallback(AddPanel);
  // The home    button
  IlvButton* bhome  = AddButton(cont, "Home", bbox, margin);
  bhome->setCallback(Home);
  // The back   button
  IlvButton* bback  = AddButton(cont, "Back", bbox, margin);
  bback->setCallback(LinkBack);
  // The Forward   button
  IlvButton* bforw  = AddButton(cont, "Forward", bbox, margin);
  bforw->setCallback(LinkForward);
  // The Forward   button
  IlvButton* brelo  = AddButton(cont, "Reload", bbox, margin);
  brelo->setCallback(Reload);
#if 0
  // Print
  IlvButton* bprint  = AddButton(cont, "Print", bbox, margin);
  bprint->setCallback(PrintContents);
#endif
  // The quit button
  IlvButton* bquit = AddButton(cont, "Quit", bbox, margin);
  bquit->setCallback(Quit);

  // The edit toggle
  IlvDim toggleLeft   = 100;
  bbox.resize(toggleLeft, margin);
  IlvToggle* tedit = new IlvToggle(display, "Editable", bbox);
  cont->addObject(tedit);
  IlvSetAttachment(tedit, IlvTop, IlvFixedAttach, ((IlvDim)bbox.y()));
  tedit->setCallback(ToggleEdit);

  // HTML Page Load
  cont->setDestroyCallback(Quit);
  cont->show();
  LinkLoad(tRef, IlFalse);
  tRef->addProperty(HtmlHistory, new IlvATHtmlHistory(tRef->getLabel()));

}

// --------------------------------------------------------------------------
// Entry point
// --------------------------------------------------------------------------
int main(int argc,
	 char* argv[])
{
  IlvSetLanguage();
  IlvDisplay* display = new IlvDisplay("HtmlView", 0, argc, argv);
  if (!display || display->isBad()) {
    IlvFatalError("Cannot initialize display");
    return 1;
  }
  
  char styleFile[ILVATREFSIZE];
  styleFile[0] = 0;
  IlPathName workPath;
  const char* workdir;
  IlShort lastchar;
  // creating the default directory name
  workdir = display->getEnvOrResource("StyleFile");
  if (workdir)
    workPath.setValue(workdir);
  else {
    workPath.setValue(display->getHome());
    workPath.addDirectory("tools/htmlview/data/");
    workPath.setBaseName("html.stl");
  }
  strcpy(styleFile, workPath.getString().getValue());
  
  // Create an HTML reader
  ViewerHTMLReader* htmlReader = new ViewerHTMLReader(display);
  htmlReader->getHome().setValue("");
  if (argc) {
    int i = 1;
    IlBoolean correctArgs = IlTrue;
    while ((i < argc) && correctArgs) {
      if (!strcmp("-server", argv[i])) {
	i++;
	if (i == argc)
	  correctArgs = IlFalse;
	else
	  htmlReader->setServerAddress(argv[i]);
	i++;
      }
      else
	if (!strcmp("-path", argv[i])) {
	  i++;
	  if (i == argc)
	    correctArgs = IlFalse;
	  else {
	    htmlReader->setRootDir(argv[i]);
	  }
	  i++;
	}
	else
	  if (!strcmp("-v", argv[i])) {
	    i++;
	    htmlReader->setVerbose(IlTrue);
	  }
	  else
	    if (i == (argc - 1)) {
	      htmlReader->getHome().setValue(argv[i]);
	      i++;
	    }
	    else
	      correctArgs = IlFalse;
    }
    if (!correctArgs) {
      IlvFatalError("Usage: htmlview [-server <http-address>] [-path <pathname>] html-filename");
      return 1;
    }
  }
  if (!htmlReader->getRootDir().isEmpty()) {
    if (!htmlReader->getRootDir().isSystemDirectory()) {
      const char* val = htmlReader->getRootDir().getString().getValue();
      IlvFatalError("%s pathname is not a valid directory", val);
    }
  }
  if (htmlReader->getRootDir().isEmpty()) {
    if (!htmlReader->getHome().isAbsolute()) {
      workPath.setValue(display->getHome());
      workPath.addDirectory("tools/htmlview/data/");
      htmlReader->getHome().prepend(workPath);
    }
  }
  else
    if (htmlReader->getHome().isEmpty())
      htmlReader->getHome().setValue("/");
  // serverAddress is stored without the final "/"
  char*    dirstring;
  if (htmlReader->getServerAddress()) {
    lastchar = IlShort(strlen(htmlReader->getServerAddress()) - 1);
    dirstring = htmlReader->getServerAddress();
    if ((dirstring[lastchar] == '/') ||
	(dirstring[lastchar] == '\\'))
      dirstring[lastchar] = 0;
  }
  if (!htmlReader->readStyles(styleFile))
    return 1;
  htmlReader->setDefaultFileName(IL_CONSTCAST(char*, "index.html"));
  
  // Create an initial panel
  AddTextPanel(display, htmlReader);
  IlvMainLoop();
  return 0;
}
