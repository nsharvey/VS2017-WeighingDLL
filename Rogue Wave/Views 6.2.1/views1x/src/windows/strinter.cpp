// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/windows/strinter.cpp
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
//
// --------------------------------------------------------------------------
#include <windows.h>

#include <ilviews/strinter.h>
#include <ilviews/graphics/label.h>
#include <ilviews/manager/manager.h>
#include <ilviews/graphics/lablist.h>
#include <ilviews/graphics/relflab.h>
#include <ilviews/graphics/shadlab.h>

#if defined(ILVSTD)
#include <cstring>
#include <cctype>
#else  /* !ILVSTD */
#include <string.h>
#include <ctype.h>
#endif /* ILVSTD */

ILVSTDUSE

static
#if defined(STRICT)
WNDPROC
#else  // !STRICT
FARPROC
#endif // !STRICT
__IlvTextEditproc;
static int     __IlvTextEditWndExtra = -1;
static char* IlvEDITClassName = "IlvEDIT";

// --------------------------------------------------------------------------
LRESULT
#if defined(WIN32)
CALLBACK
#else  /* !WIN32 */
FAR PASCAL
#if defined(__TCPLUSPLUS__)
_export
#endif /* __TCPLUSPLUS__ */
#if defined(__MSC__)
__export
#endif /* __MSC__ */
#endif /* !WIN32 */
IlvTextEditProc(HWND w, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CHAR:
	if (wParam == VK_RETURN) {
	    WPARAM length = (WPARAM)SendMessage(w, WM_GETTEXTLENGTH, 0, 0);
	    char* buffer = new char[length+1];
	    SendMessage(w, WM_GETTEXT, length+1, (LPARAM)buffer);
	    IlvTextFieldInteractor* t = (IlvTextFieldInteractor*)
		IlCastIlUIntToIlAny(GetWindowLong(w, __IlvTextEditWndExtra));
	    t->doIt(buffer);
	    delete buffer;
	    t->abort();
	    return 0;
	}
    }
    return CallWindowProc(__IlvTextEditproc, w, message, wParam, lParam );
}

// --------------------------------------------------------------------------
void
IlvTextFieldInteractor::setLabel(const char* s)
{
    if (_window)
	SendMessage((HWND)_window,
		    WM_SETTEXT,
		    0,
		    IlCastIlAnyToIlUInt((IlAny)s));
}

// --------------------------------------------------------------------------
void
IlvTextFieldInteractor::makeWindow(IlvPos x, IlvPos y)
{
    if (__IlvTextEditWndExtra == -1) {
	WNDCLASS wndclass;
	GetClassInfo(NULL, "EDIT", &wndclass);
	__IlvTextEditWndExtra   = wndclass.cbWndExtra;
	wndclass.cbWndExtra   += 4;
	__IlvTextEditproc       =
#if !defined(STRICT)
	    (FARPROC)
#endif // !STRICT
	    wndclass.lpfnWndProc;
#if defined(__DLL__)
	extern HINSTANCE IlvGetLibInstance();
	wndclass.hInstance = IlvGetLibInstance();
#else  /* !__DLL__ */
	wndclass.hInstance = (HINSTANCE)view()->getDisplay()->getInstance();
#endif /* !__DLL__ */
	wndclass.lpszClassName = IlvEDITClassName;
	wndclass.lpfnWndProc   = IlvTextEditProc;
	wndclass.style        |= CS_GLOBALCLASS;
	if (!RegisterClass(&wndclass)) {
	    IlvFatalError("Couldn't register '%s' window class",
			  IlvEDITClassName);
	    __IlvTextEditWndExtra = -1;
	}
    }
    _window = (IlvSystemView)CreateWindow(IlvEDITClassName, NULL,
    					  WS_CHILD|WS_BORDER|
					  WS_VISIBLE|ES_LEFT|
					  ES_AUTOHSCROLL|ES_NOHIDESEL,
					  (int)x, (int)y,
					  120, 40,
					  (HWND)view()->getSystemView(), 0,
					  (HINSTANCE)view()->getDisplay()
					                   ->getInstance(),
					  0);
    ShowWindow((HWND)_window, SW_SHOWNORMAL);
    UpdateWindow((HWND)_window);
    SetFocus((HWND)_window);
    SetWindowLong((HWND)_window,
		  __IlvTextEditWndExtra,
		  IlCastIlAnyToIlUInt(this));
}

// --------------------------------------------------------------------------
IlvTextFieldInteractor::~IlvTextFieldInteractor()
{
    if (_window)
	DestroyWindow((HWND)_window);
}

// --------------------------------------------------------------------------
void
IlvTextFieldInteractor::drawGhost()
{
}

// --------------------------------------------------------------------------
IlvBoolean
IlvMakeLabelInteractor::accept(IlvPoint& p)
{
    IlvTextFieldInteractor::accept(p);
    IlvGraphic* object = manager()->lastContains(p,_mgrview);
    if (object && object->isSubtypeOf("IlvLabel")) {
	if (object->isSubtypeOf("IlvLabel")) {
	    _label = (IlvLabel *)object;
	    setLabel(_label->getLabel());
	} else
	    if (object->isSubtypeOf("IlvReliefLabel")) {
		_label = (IlvLabel*)object;
		setLabel(((IlvReliefLabel*)object)->getLabel());
	    } else
		if (object->isSubtypeOf("IlvShadowLabel")) {
		    _label = (IlvLabel*)object;
		    setLabel(((IlvShadowLabel*)object)->getLabel());
		} else
		    _label=0;
    } else _label=0;
    return IlvTrue;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ChangeLabel(IlvGraphic* obj,IlvAny arg)
{
    if (obj->isSubtypeOf("IlvLabel"))
	((IlvLabel*)obj)->setLabel((char*)arg);
    else if (obj->isSubtypeOf("IlvReliefLabel"))
	((IlvReliefLabel*)obj)->setLabel((char*)arg);
    else if (obj->isSubtypeOf("IlvShadowLabel"))
	((IlvShadowLabel*)obj)->setLabel((char*)arg);
}

// --------------------------------------------------------------------------
void
IlvMakeLabelInteractor::doIt(char* buffer)
{
    if (_label) {
	manager()->applyToObject(_label, ChangeLabel, buffer);
	_label=0;
    } else {
	IlvPoint p(_x, _y);
	if (transformer())
	    transformer()->inverse(p);
	IlvGraphic* obj = new IlvLabel(manager()->getDisplay(), p, buffer);
	manager()->deSelect();
	manager()->addObject(obj);
	manager()->makeSelected(obj);
    }
    callPrevious();
}

// --------------------------------------------------------------------------
IlvBoolean
IlvMakeFilledLabelInteractor::accept(IlvPoint& p)
{
    IlvTextFieldInteractor::accept(p);
    IlvGraphic* object = manager()->lastContains(p, _mgrview);
    if (object && object->isSubtypeOf("IlvFilledLabel")) {
	_label=(IlvFilledLabel *)object;
	setLabel(_label->getLabel());
    } else _label = 0;
    return IlvTrue;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ChangeFilledLabel(IlvGraphic* obj,IlvAny arg)
{
    ((IlvFilledLabel*)obj)->setLabel((char *)arg);
}

// --------------------------------------------------------------------------
void
IlvMakeFilledLabelInteractor::doIt(char* buffer)
{
    if (_label) {
	manager()->applyToObject(_label,ChangeFilledLabel, buffer);
	_label=0;
    } else {
	IlvPoint p(_x, _y);
	if (transformer()) transformer()->inverse(p);
	IlvGraphic* obj =
	    new IlvFilledLabel(manager()->getDisplay(), p, buffer);
	manager()->deSelect();
	manager()->addObject(obj);
	manager()->makeSelected(obj);
    }
    callPrevious();
}

// --------------------------------------------------------------------------
void
IlvTextFieldInteractor::abort()
{
    if (_window)
	DestroyWindow((HWND)_window);
    _window = 0;
}

// --------------------------------------------------------------------------
IlvBoolean
IlvTextFieldInteractor::accept(IlvPoint& p)
{
    _x = p.x();
    _y = p.y();
    makeWindow(_x, _y);
    return IlvTrue;
}

// --------------------------------------------------------------------------
IlBoolean
IlvTextFieldInteractor::handleEvent(IlvEvent& event)
{
    IlBoolean consumed = IlFalse;
    switch (event.type()) {
    case IlvKeyDown:
    case IlvKeyUp:
    case IlvButtonUp:
    case IlvButtonDragged: {
	consumed = manager()->shortCut(event, _mgrview);
	break;
    }
    case IlvButtonDown: {
	if (event.button() == IlvRightButton) {
	    if (_window)
		abort();
	    consumed = manager()->shortCut(event, _mgrview);
	}
	if (event.button() == IlvMiddleButton) {
	    if (_window)
		abort();
	}
	if (!_window && (event.button() == IlvLeftButton)) {
	    IlvPoint p(event.x(), event.y());
	    accept(p);
	    IlvDeltaPoint dp(10, 10);
	    manager()->getDisplay()->movePointer(dp);
	    consumed = IlTrue;
	}
	break;
    }
    default: {
	consumed = getManager()->shortCut(event, _mgrview);
	break;
    }
    }
    return consumed;
}


// --------------------------------------------------------------------------
// Multi Text Decoder
// --------------------------------------------------------------------------
void
IlvTextInteractor::makeWindow(IlvPos x, IlvPos y)
{
    RECT bbox;
    GetWindowRect((HWND)view()->getSystemView(), &bbox);
    _window = (IlvSystemView)CreateWindow("EDIT", NULL,
					  WS_POPUP|WS_VISIBLE|ES_LEFT|
					  WS_DLGFRAME|ES_AUTOHSCROLL|
					  ES_AUTOVSCROLL|ES_NOHIDESEL|
					  ES_MULTILINE,
					  IlvMax((int)(x+bbox.left-100),0),
					  IlvMax((int)(y+bbox.top-100),0),
					  200, 200,
					  (HWND)view()->getSystemView(), 0,
					  (HINSTANCE)view()->getDisplay()
					                   ->getInstance(),
					  0);
    SetFocus((HWND)_window);
//    SetWindowLong((HWND)_window, GWL_WNDPROC, (LONG)__IlvTextEditproc);
}

// --------------------------------------------------------------------------
IlBoolean
IlvTextInteractor::handleEvent(IlvEvent& event)
{
    IlBoolean consumed = IlFalse;
    switch (event.type()) {
    case IlvButtonUp:
    case IlvButtonDragged: {
	consumed = manager()->shortCut(event, _mgrview);
	break;
    }
    case IlvDoubleClick: {
	if (_window) {
	    getText();
	    consumed = IlTrue;
	}
	break;
    }
    case IlvButtonDown: {
	if (event.button() == IlvRightButton) {
	    if (_window)
		abort();
	    consumed = manager()->shortCut(event, _mgrview);
	}
	if (event.button() == IlvMiddleButton) {
	    if (_window) {
		getText();
		consumed = IlTrue;
	    }
	    return consumed;
	}
	if (!_window && (event.button() == IlvLeftButton)) {
	    _p.move(event.x(), event.y());
	    makeWindow(event.x(), event.y());
	    accept(_p);
	    IlvDeltaPoint dp(10, 10);
	    manager()->getDisplay()->movePointer(dp);
	    consumed = IlTrue;
	}
	break;
    }
    default: {
	consumed = getManager()->shortCut(event, _mgrview);
	break;
    }
    }
    return consumed;
}

// --------------------------------------------------------------------------
IlvTextInteractor::~IlvTextInteractor()
{
    if (_window)
	DestroyWindow((HWND)_window);
}

// --------------------------------------------------------------------------
IlvBoolean
IlvTextInteractor::accept(IlvPoint&)
{
    return IlvTrue;
}

// --------------------------------------------------------------------------
IlvBoolean
IlvMakeListLabelInteractor::accept(IlvPoint& p)
{
    IlvTextInteractor::accept(p);
    IlvGraphic* object=getManager()->lastContains(p,_mgrview);
    if (object && object->isSubtypeOf("IlvListLabel"))
       _listlabel=(IlvListLabel*)object;
    else _listlabel = 0;
    if (_listlabel) {
	static char buffer[512];
	int l = 0;
	int sl;
	for (IlvUInt i = 0; i < _listlabel->count(); i++) {
	    sl = (int)strlen(_listlabel->getLabel(i));
	    if (l+sl >= 512)
		break;
	    strcpy(buffer+l, _listlabel->getLabel(i));
	    l += sl;
	    buffer[l++] = '\r';
	    buffer[l++] = '\n';
	}
	buffer[l] = 0;
	setText(buffer);
    }
    return IlvTrue;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
ChangeLabels(IlvGraphic* obj,IlvAny arg)
{
    IlvAny* args   = (IlvAny*)arg;
    int*   count  = (int*)args[0];
    const char** labels = (const char**)args[1];
    ((IlvListLabel*)obj)->setLabels(labels, *count);
}

// --------------------------------------------------------------------------
void
IlvMakeListLabelInteractor::doIt(char* buffer)
{
    if (!buffer)
	return;
    if (_mgrview->transformer())
	_mgrview->transformer()->inverse(_p);
    // Count lines
    IlvUInt count = 0;
    char* c;
    for (c = buffer; *c; c++)
	if (*c == '\n')
	    count++;
    if (*(c-1) != '\n')
	count++;
    char** labels = new char* [count];
    char*  pc     = buffer;
    IlvUInt i = 0;
    for (c = buffer; *c; c++) {
	if (*c == '\n') {
	    *c = 0;
	    if (*(c-1) == '\r') *(c-1) = 0;
	    labels[i] = new char [strlen(pc)+1];
	    strcpy(labels[i], pc);
	    i++;
	    pc = c+1;
	}
    }
    if (c != pc) {
	if ((*(c-1) == '\r') && (c != pc+1)) {
	    *(c-1) = 0;
	    labels[i] = new char [strlen(pc)+1];
	    strcpy(labels[i], pc);
	    i++;
	}
    }
    if (_listlabel){
	IlvAny args[2];
	args[0]=&i;
	args[1]=labels;
	manager()->applyToObject(_listlabel,ChangeLabels,args);
	_listlabel=0;
    } else {
	IlvGraphic* obj = new IlvListLabel(manager()->getDisplay(),
					   _p,
					   i,
					   (const char**)labels);
	for (IlvUInt j = 0; j < i; j++)
	    delete labels[j];
	delete [] labels;
	manager()->deSelect();
	manager()->addObject(obj);
	manager()->makeSelected(obj);
    }
    callPrevious();
}

// --------------------------------------------------------------------------
void
IlvTextInteractor::abort()
{
    if (_window)
	DestroyWindow((HWND)_window);
    _window = 0;
}

// --------------------------------------------------------------------------
void
IlvTextInteractor::getText()
{
    if (_window) {
	WPARAM length =
	    (WPARAM)SendMessage((HWND)_window, WM_GETTEXTLENGTH, 0, 0);
	char* buffer = new char[length+1];
	SendMessage((HWND)_window, WM_GETTEXT, length+1, (LPARAM)buffer);
	abort();
	doIt(buffer);
	delete buffer;
    }
}

// --------------------------------------------------------------------------
void
IlvTextInteractor::setText(const char* text)
{
    if (_window)
	SendMessage((HWND)_window,
		    WM_SETTEXT,
		    0,
		    IlCastIlAnyToIlUInt((IlAny)text));
}
