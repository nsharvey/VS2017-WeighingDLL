// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/foundation/windows/src/ilvwin.cpp
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
// Testing the integration of RogueWaveViews into a Workshop-generated interface
// --------------------------------------------------------------------------

#include <ilviews/contain/contain.h>
#include <ilviews/graphics/all.h>

IL_STDUSE

#include <windows.h>
#include <shellapi.h>   // For Drag & Drop

#define VIEW_ID			1000
#define QUIT_OPTION_ID		1001
#define CHANGE_BACKGROUND_ID	1002
#define ZOOM_SCROLLER_ID	1003

#define TIGER_IMAGE_OPTION	1010
#define ELEFANTE_IMAGE_OPTION	1011

static void InitRogueWaveViews(IlvDisplay*, IlvSystemView);
static void ReleaseRogueWaveViews();
static void ChangeBackground();
static void LoadImage(char*);
static void ZoomView(IlvFloat);

// --------------------------------------------------------------------------
int PASCAL ILVCALLBACK
DialogProc(HWND dlg,
	   UINT msg,
	   WPARAM wParam,
	   LPARAM lParam)
{
    switch (msg) {
    case WM_INITDIALOG: {
    	DragAcceptFiles(GetDlgItem(dlg, VIEW_ID), TRUE);
	InitRogueWaveViews((IlvDisplay*)lParam,
		      (IlvSystemView)GetDlgItem(dlg, VIEW_ID));
	SetScrollRange(GetDlgItem(dlg, ZOOM_SCROLLER_ID),
		       SB_CTL,
		       1,
		       1000,
		       FALSE);
	SetScrollPos(GetDlgItem(dlg, ZOOM_SCROLLER_ID), SB_CTL, 100, TRUE);
    	(void)SetFocus(GetDlgItem(dlg, VIEW_ID));
	return 1;
    }
    case WM_VSCROLL: {
    	(void)SetFocus(GetDlgItem(dlg, VIEW_ID));
    	if ((HWND)lParam == GetDlgItem(dlg, ZOOM_SCROLLER_ID)) {
	    int oldzoom = GetScrollPos((HWND)lParam, SB_CTL);
	    int zoom    = oldzoom;
	    switch (LOWORD(wParam)) {
	    case SB_BOTTOM: {
		zoom  = 1000;
		break;
	    }
	    case SB_TOP: {
		zoom  = 1;
		break;
	    }
	    case SB_LINEDOWN: {
		zoom += 10;
		break;
	    }
	    case SB_PAGEDOWN: {
		zoom += 50;
		break;
	    }
	    case SB_LINEUP: {
		zoom -= 10;
		break;
	    }
	    case SB_PAGEUP: {
		zoom -= 50;
		break;
	    }
	    case SB_THUMBTRACK:
	    case SB_THUMBPOSITION: {
	    	zoom = HIWORD(wParam);
		break;
	    }
	    default: {
		return 0;
	    }
	    }
	    if (zoom < 1)
		zoom = 1;
	    if (zoom > 1000)
		zoom = 1000;
	    if (zoom != oldzoom) {
	    	SetScrollPos((HWND)lParam, SB_CTL, zoom, TRUE);
	        ZoomView(zoom / (IlvFloat)oldzoom);
	    }
	}
    	return 0;
    }
    case WM_COMMAND: {
    	(void)SetFocus(GetDlgItem(dlg, VIEW_ID));
    	switch (wParam) {
	case QUIT_OPTION_ID: {
	    EndDialog(dlg, 1);
	    ReleaseRogueWaveViews();
	    PostQuitMessage(0);
	    return 1;
	}
	case CHANGE_BACKGROUND_ID: {
	    ChangeBackground();
	    return 1;
	}
	case TIGER_IMAGE_OPTION: {
	    LoadImage("tiger2.Ilv");
	    return 1;
	}
	case ELEFANTE_IMAGE_OPTION: {
	    LoadImage("elefante.Ilv");
	    return 1;
	}
	}
	break;
    }
    case WM_CLOSE: {
	EndDialog(dlg, 1);
	ReleaseRogueWaveViews();
	PostQuitMessage(0);
	return 1;
    }
    }
    return 0;
}

// --------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("Rogue Wave Views", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't create display");
	if (display)
	    delete display;
	return 1;
    }
    if (DialogBoxParam((HINSTANCE)display->getInstance(),
		       "TOPVIEW",
		       0,
		       (DLGPROC)DialogProc,
		       IL_REINTERPRETCAST(LPARAM, display)) == -1)
	IlvFatalError("Couldn't create dialog\n");
    delete display;
    return 0;
}

// --------------------------------------------------------------------------
// RogueWaveViews specific functions:
// --------------------------------------------------------------------------
static IlvContainer* container;

// --------------------------------------------------------------------------
IlBoolean ILVCALLBACK
WindowProc(IlvAbstractView*,
	   IlvSystemView,
	   IlvMsgParam		msg,
	   IlvWParam		wParam,
	   IlvLParam		/* lParam */,
	   IlAny&		result,
	   IlAny)
{
    if (msg == WM_DROPFILES) {
    	char filename[256];
	DragQueryFile(IL_CAST(HDROP, IlvCastIlvWParamToIlAny(wParam)),
		      0,
		      filename,
		      256);
	LoadImage(filename);
	result = 0;
	return IlTrue;
    }
    return IlFalse;
}

// --------------------------------------------------------------------------
static void
InitRogueWaveViews(IlvDisplay* display,
	      IlvSystemView window)
{
    container = new IlvContainer(display, window);
    container->setWindowProc(WindowProc);
}

// --------------------------------------------------------------------------
static void
ReleaseRogueWaveViews()
{
    delete container;
}

// --------------------------------------------------------------------------
static void
ChangeBackground()
{
    IlvColor* color =
	container->getDisplay()->getColor((IlvIntensity)(rand() % 65535),
					  (IlvIntensity)(rand() % 65535),
					  (IlvIntensity)(rand() % 65535));
    if (color) {
        container->setBackground(color);
	container->reDraw();
    } else
	IlvFatalError("Couldn't allocate color!\n");
}

// --------------------------------------------------------------------------
static void
LoadImage(char* filename)
{
    container->removeObjects(IlTrue, IlFalse);
    container->readFile(filename);
    container->reDraw();
}

// --------------------------------------------------------------------------
static void
ZoomView(IlFloat zoom)
{
    IlvRect size;
    container->sizeVisible(size);
    container->zoomView(IlvPoint(size.centerx(), size.centery()), zoom);
}
