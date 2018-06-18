// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/appframe/bitmaped/step5/src/drawcmd.cpp
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
// Definition of the DrawRectangleCommand class.
// --------------------------------------------------------------------------
#include <drawcmd.h>

// --------------------------------------------------------------------------
DrawRectangleCommand::DrawRectangleCommand(BitmapDocument* 	document,
					   const IlvPoint& 	point,
					   IlvDim 		size,
					   IlvPalette* 		palette,
					   const char* 		name)
: IlvDvCommand(name),
  _document(document),
  _bitmap(0),
  _rect(),
  _palette(palette)
{
    // Compute the size of the area that will be modified in the bitmap
    _rect.moveResize(point.x(), point.y(), 1, 1);
    _rect.expand(size);
    // Create the bitmap that will be used to keep the initial area, to allow
    // undo.
    _bitmap = new IlvBitmap(_document->getBitmap()->getDisplay(),
			    _rect.w(),
			    _rect.h(),
			    _document->getBitmap()->depth());
    // If no palette has been provided, use the document one
    if (!_palette)
	_palette = document->getPalette();
    _palette->lock();
}

// --------------------------------------------------------------------------
DrawRectangleCommand::~DrawRectangleCommand()
{
    delete _bitmap;
    _palette->unLock();
}

// --------------------------------------------------------------------------
IlvDvCommand*
DrawRectangleCommand::copy() const
{
    return (IlvDvCommand *)(new IlvAny); 
}

// --------------------------------------------------------------------------
void
DrawRectangleCommand::doIt()
{
    // Save the initial bitmap
    _bitmap->drawBitmap(_document->getPalette(),
			_document->getBitmap(),
			_rect,
			IlvPoint(0,0));
    // Then draw in the document's bitmap
    _document->getBitmap()->fillRectangle(_palette, _rect);
    // Finally, refresh all the views connected to the document
    _document->refreshViews(_rect);
}

// --------------------------------------------------------------------------
void
DrawRectangleCommand::undo()
{
    // Restore the bitmap saved in _bitmap into the document's bitmap
    _document->getBitmap()->drawBitmap(_document->getPalette(),
				       _bitmap,
				       IlvRect(0,
					       0,
					       _bitmap->width(),
					       _bitmap->height()),
				       IlvPoint(_rect.x(), _rect.y()));
    // Then, refresh all the views connected to the document
    _document->refreshViews(_rect);
}

// --------------------------------------------------------------------------
// Static initializations
IlvDvPreRegisterClass(DrawRectangleCommand, IlvDvCommand);

IL_BEGINMODULEINITDEF(drawcmd)
  IlvDvPostRegisterClass(DrawRectangleCommand, IlvDvCommand);
IL_ENDMODULEINITDEF(drawcmd)

#if !defined(ILVBUILDLIBS)
static int command_ini = (IL_MODINIT(drawcmd)(), 0);
#endif
