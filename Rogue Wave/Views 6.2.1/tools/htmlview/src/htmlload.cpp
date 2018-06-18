// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/htmlview/src/htmlload.cpp
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
// Demonstrating the IlvAnnoText object reading HTML files
// -----------------------------------------------------------------------------

#include <sys/types.h>
#include <ilviews/macros.h>

#if defined(WINDOWS)
#  include <windows.h>
#  if defined(_MSC_VER)
#    include <direct.h>
#  endif /* _MSC_VER */
#  if defined(__TCPLUSPLUS__)
#    include <dir.h>
#  endif
#endif /* WINDOWS */

#if !defined(WINDOWS) && !defined(PM)
#  include <unistd.h>
#endif

#if defined(IL_STD)
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#else  /* !IL_STD */
#include <string.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream.h>
#endif /* IL_STD */

IL_STDUSE 

#include <ilviews/contain/inter.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/label.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/graphics/attach.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/base/memory.h>

#ifndef __Ilv_Annotext_Annotext_H
# include <ilviews/annotext/annotext.h>
#endif
#ifndef __Ilv_Annotext_Cursor_H
# include <ilviews/annotext/cursor.h>
#endif
#ifndef __Ilv_Annotext_Zone_H
# include <ilviews/annotext/zone.h>
#endif
#ifndef _Ilv_Annotext_Html_H
# include <ilviews/annotext/html.h>
#endif
#ifndef _Ilv_Annotext_Htmlload_H
# include <ilviews/annotext/htmlload.h>
#endif

// --------------------------------------------------------------------------
void
ViewerLinkInteractor::followLink(IlvATHtmlText* text,
				 const char* linkPathName)
{
  IlvContainer* container = IlvContainer::getContainer(text);
  IlvTextField* tfile = (IlvTextField*)container->getObject("Reference");
  if (tfile) {
    tfile->setLabel(linkPathName);
    container->reDrawObj(tfile);
    (tfile->getCallback())(tfile, container);
  }
}

// --------------------------------------------------------------------------
IlBoolean
ViewerHtmlReader::linkLoad(IlvATHtmlText* text,
			   char* refString,
			   IlBoolean history)
{
  IlvContainer* cont = IlvContainer::getContainer(text);
  IlvDisplay*   display = cont->getDisplay();
  cont->setCursor(display->getCursor("wait"));

  IlvATCursor start(text);
  IlBoolean newfile = IlFalse;
  IlBoolean wronganchor = IlFalse;
  IlBoolean delayedBitmaps = IlFalse;

  char htmlFile   [ILVATREFSIZE];
  char workString [ILVATREFSIZE];
  IlPathName  workPath;
  IlPathName  htmlPath;
  IlBoolean isAnchor;
  IlUShort anchor = 0;

  strcpy(htmlFile, refString);
  isAnchor = parsePath(htmlFile, anchor);
  if (anchor != 1) {
    if (!history) {
      getPathNameFromAddress(text, htmlFile, htmlPath);
      if (htmlPath.isSystemDirectory())
	if (!htmlPath.isDirectory()) {
	  strcpy(workString, htmlPath.getBaseName());
	  htmlPath.addDirectory(workString);
	  htmlPath.setBaseName("");
	}
      if (htmlPath.isDirectory())
	htmlPath.setBaseName(getDefaultFileName());
    } else {
      htmlPath.setValue(htmlFile);
      if (htmlPath.isDirectory())
	htmlPath.setBaseName(getDefaultFileName());
    }
    if (htmlPath != (text->getCurrentPath())) {
      if (htmlPath.doesExist()) {
	strcpy(workString, htmlPath.getString().getValue());
	workPath = htmlPath;
      } else {
	workPath.setValue(htmlPath.get83DosValue());
	if (workPath.doesExist())
	  strcpy(workString, htmlPath.get83DosValue());
	else {
	  const char* val = htmlPath.getString().getValue();
	  IlvFatalError("Cannot open %s", val);
	  cont->setCursor(display->defaultCursor());
	  return IlFalse;
	}
      }
      ifstream htmlStream(workString);
      newfile = IlTrue;
      text->setCurrentPath(htmlPath);
      IlBoolean isHtml = IlFalse;
      if (!htmlPath.getExtension().caseCompare(IlString("html")) ||
	  !htmlPath.getExtension().caseCompare(IlString("htm")))
	isHtml = IlTrue;
      strcpy(refString, htmlPath.getString().getValue());
      if (isAnchor) {
	strcat(refString, "#");
	strcat(refString, htmlFile + anchor);
      }
      text->emptyText();
      text->computeLines();
      text->reDraw();
      if (!htmlPath.getExtension().caseCompare(IlString("png")) ||
	  !htmlPath.getExtension().caseCompare(IlString("bmp")) ||
	  !htmlPath.getExtension().caseCompare(IlString("xpm")))
	readBitmapFile(text, workPath);
      else {
	read(text, htmlStream, isHtml);
	if (text->getDelayedBitmaps())
	  delayedBitmaps = IlTrue;
      }
    }
  } else {
    // the reference is only an anchor -> we complete using current dir
    strcpy(refString, text->getCurrentPath().getString().getValue());
    strcat(refString, "#");
    strcat(refString, htmlFile + anchor);
  }
  IlBoolean beginText = IlTrue;
  IlvATCursor* curs = 0;
  if (isAnchor) {
    curs = getAnchorCursor(htmlFile + anchor);
    if (!curs) {
      IlvFatalError("Cannot find anchor %s", htmlFile + anchor);
      if (newfile)
	start.moveStartText();
      // cutout the wrong anchor
      parsePath(refString, anchor);
      wronganchor = IlTrue;
    } else {
      start.moveTo(curs);
      beginText = IlFalse;
    }
  } else
    start.moveStartText();
  if (delayedBitmaps && !(text->getNumberOfProxies()))
    delayedBitmaps = IlFalse;
  if (newfile || !wronganchor) {
    // COSTLY AND UGLY WORK AROUND (doesn't matter for reasonably short files)
    // Should be corrected properly
    text->computeLines();
    if (newfile && delayedBitmaps) {
      text->computeLines();
      if (beginText)
	start.moveStartText();
      else
	start.moveTo(curs);
      text->scrollTo(&start);
      if (start.endsLine() && !start.startsLine())
	text->scrollDownLines(1);
      text->reDraw();
      getRealImages(text);
    }
    text->computeLines();
    if (beginText)
      start.moveStartText();
    else
      start.moveTo(curs);
    text->scrollTo(&start);
    if (start.endsLine() && !start.startsLine())
      text->scrollDownLines(1);
    text->reDraw();
    cont->setCursor(display->defaultCursor());
    return IlTrue;
  }
  cont->setCursor(display->defaultCursor());
  return IlFalse;
}

// -------------------------------------------------------------------------
// ViewerCommandInteractor
// -------------------------------------------------------------------------
// a ported (undocumented ...) sleep function
extern ILVDSPEXPORTEDFUNCTION(void) IlvUSleep(IlUInt microseconds);

void
ViewerCommandInteractor::executeCommand(IlvATHtmlText* text,
					const char* commandName)
{
  IlvContainer*  cont = IlvContainer::getContainer(text);
  IlvDisplay*    display = cont->getDisplay();
  char	   commandString[ILVATREFSIZE];
  IlPathName	   currentPath;
  IlPathName	   commandPath;
  IlvATHtmlText* htmlText = (IlvATHtmlText*)text;
  htmlText->getReader()->getPathNameFromAddress(text,
						commandName, commandPath);
  currentPath.queryCurrentDirectory();

  if (!commandPath.changeCurrentDirectory()) {
    IlvFatalError("Path not found %s", commandPath.getDirName().getValue());
    return;
  }

  cont->setCursor(display->getCursor("wait"));
#if defined(WINDOWS)
  strcpy(commandString, commandPath.getBaseName());
  int status = WinExec(commandString, SW_SHOWNORMAL);
  if (status <= 31) {
    // > 31 ok; else 0 no more resources; ERROR_FILE_NOT_FOUND;
    //      ERROR_PATH_NOT_FOUND; ERROR_BAD_FORMAT;
    switch (status) {
    case 0 :
      IlvFatalError("No more resources");
      break;
    case 2 : // ERROR_FILE_NOT_FOUND :
    case 3 : // ERROR_PATH_NOT_FOUND :
      IlvFatalError("Command not found: %s", commandString);
      break;
    case 11 : // ERROR_BAD_FORMAT :
      IlvFatalError("Bad format: %s", commandString);
      break;
    default :
      IlvFatalError("Error %i launching: %s", status, commandString);
      break;
    }
  }
#else  /* !WINDOWS */
  strcpy(commandString,"./");
  strcat(commandString,commandPath.getBaseName());
  strcat(commandString,"&");
  int commandStatus = system(commandString);
  if (commandStatus)
    IlvFatalError("Error %d launching: %s", commandStatus, commandString);
#endif /* !WINDOWS */

  if (!currentPath.changeCurrentDirectory()) {
    IlvFatalError("Couldn't restore original path %s",
		  currentPath.getDirName().getValue());
  }

  display->flush();
  IlvUSleep(3000000);
  cont->setCursor(display->defaultCursor());
}
