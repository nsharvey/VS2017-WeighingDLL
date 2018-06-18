// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views1x/src/gview.cpp
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
// Definition of the IlvGridView class
// --------------------------------------------------------------------------
#include <ilviews/gview.h>
#include <ilviews/graphics/io.h>
#include <ilviews/graphics/handle.h>
#include <ilviews/graphics/set.h>
#include <ilviews/base/sstream.h>

ILVSTDUSE
#if defined(WINDOWS)
#include <windows.h>
#endif /* WINDOWS */

#if defined(IlvDECLAREINITCLASS)
IlvViewGridInteractor*  IlvGridView::_gridInteractor = 0;
ILVDEFINEINITCLASS(gview, IlvGridView::_gridInteractor = new IlvViewGridInteractor();)
#else  /* !IlvDECLAREINITCLASS */
IlvViewGridInteractor*
IlvGridView::_gridInteractor = new IlvViewGridInteractor();
#endif /* !IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
void
IlvGridView::handleInput(IlvEvent& event)
{
    if(!_gridInteractor->handleEvent(_grid,event,this,_transformer))
	IlvContainer::handleInput(event);
}

// --------------------------------------------------------------------------
void
IlvGridView::handleResize(IlvRect& rect)
{
    IlvRect bbox;
    _grid->boundingBox(bbox,_transformer);
    IlvFloat sx=(IlvFloat)rect.w()/(IlvFloat)bbox.w();
    IlvFloat sy=(IlvFloat)rect.h()/(IlvFloat)bbox.h();
    IlvTransformer t(sx, (IlvFloat)0, (IlvFloat)0, sy,
		     (IlvFloat)0, (IlvFloat)0);
    addTransformer(t);
#if defined(WINDOWS)
    RECT r;
    r.left   = (int)bbox.x();
    r.top    = (int)bbox.y();
    r.right  = (int)(bbox.x() + bbox.w());
    r.bottom = (int)(bbox.y() + bbox.h());
    InvalidateRect((HWND)IlCastIlAnyToIlUInt(getSystemView()), &r, TRUE);
#else /* WINDOWS */
    IlvRegion region(bbox);
    reDraw(&region);
#endif /* WINDOWS */
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
GCopyToClipboard(IlvContainer* container, IlvEvent& event, IlvAny)
{
    IlvPoint p(event.x(),event.y());
    IlvGraphic* graphic=container->contains(p);
    if(!graphic || !graphic->isSubtypeOf("IlvGridObj")) return;
    IlvGridObj* grid=(IlvGridObj*)graphic;
    if(container->getTransformer()) container->getTransformer()->inverse(p);
    IlvUShort irow, icol;
    if (grid->pointToPosition(p, icol, irow)) {
	IlvGraphic* old = grid->getObject(icol, irow);
	if (old) {
	    IlvUInt n;
	    ostrstream stream;
	    IlvOutputFile output(stream);
	    output.saveObjects(1,&old,n);
#if defined(IL_USING_STRINGSTREAM)    
	    int count = stream.str().size();
	    char* s = const_cast<char*>(stream.str().data());
#else  /* !IL_USING_STRINGSTREAM */
	    int count=stream.pcount();
	    char* s = stream.str();
#endif /* !IL_USING_STRINGSTREAM */
	    container->getDisplay()->putClipboard(s,count);
#if defined(_MSC_VER)
	    stream.rdbuf()->freeze(0);
#else  /* !_MSC_VER */
#  if !defined(IL_USING_STRINGSTREAM)    
	    delete [] s;
#  endif /* !IL_USING_STRINGSTREAM */
#endif /* !_MSC_VER */
	}
    }
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
GCopyFromClipboard(IlvContainer* container, IlvEvent& event, IlvAny)
{
    IlvPoint p(event.x(),event.y());
    IlvGraphic* graphic=container->contains(p);
    if(!graphic || !graphic->isSubtypeOf("IlvGridObj")) return;
    IlvGridObj* grid=(IlvGridObj*)graphic;
    if(container->getTransformer()) container->getTransformer()->inverse(p);
    IlvUShort irow, icol;
    if (grid->pointToPosition(p, icol, irow)) {
	IlvGraphic* old = grid->getObject(icol, irow);
	int l=0;
	char* s=(char*)container->getDisplay()->getClipboard(l);
	if (!l) return;
       	istrstream stream(s);
	IlvInputFile input(stream);
	IlvUInt count=0;
	IlvGraphic* ILVHUGE* graphics =
	    (IlvGraphic* ILVHUGE*)input.readObjects(container->getDisplay(),
						    count);
	if(count) {
	    IlvGraphic* newimage;
	    if(count == 1) newimage =graphics[0];
	    else {
		newimage = new IlvGraphicSet();
		for(IlvUInt i=0;i<count;i++)
		    ((IlvGraphicSet*)newimage)->addObject(graphics[i]);
	    }
	    if(!newimage->isSubtypeOf("IlvTransformedGraphic"))
		newimage = new IlvTransformedGraphic(newimage,IlvTrue);
	    if (old) {
		IlvDim w, h;
		IlvBoolean selected = grid->isSelected(old);
		grid->objectPosition(old, icol, irow, w, h);
		grid->add(icol, irow, newimage, IlvFalse,
			  grid->getCallback(old),
			  grid->getObjectArg(old),
			  w, h);
		if (selected) grid->makeSelected(newimage);
	    }
	    else grid->add(icol, irow, newimage);
	    grid->reDrawObj(newimage, container, container->getTransformer());
	}
    }
}

// --------------------------------------------------------------------------
void
IlvGridView::initCutAndPaste()
{
    addAccelerator(GCopyToClipboard,IlvKeyUp,IlvCtrlChar('C'));
    addAccelerator(GCopyFromClipboard,IlvKeyUp,IlvCtrlChar('V'));
#if defined(WINDOWS)
    addAccelerator(GCopyToClipboard,  IlvKeyDown,IlvInsKey,IlvCtrlModifier);
    addAccelerator(GCopyFromClipboard,IlvKeyDown,IlvInsKey,IlvShiftModifier);
#endif /* WINDOWS */
}
