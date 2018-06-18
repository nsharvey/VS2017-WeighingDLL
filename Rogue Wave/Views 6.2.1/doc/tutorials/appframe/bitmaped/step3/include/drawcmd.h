// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/appframe/bitmaped/step3/include/drawcmd.h
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
// Declaration of the DrawRectangleCommand class
// --------------------------------------------------------------------------
#if !defined(__drawcmd_H)
#define __drawcmd_H

#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif

#include <BitmapDocument.h>

class IlvContainer;
class IlvBitmap;

// --------------------------------------------------------------------------
class DrawRectangleCommand
  : public IlvDvCommand
{
  IlvDvDeclareClassInfo();

public:
    // ------------------------------------------------------------------------
    DrawRectangleCommand(BitmapDocument* 	document,
			 const IlvPoint& 	point,
			 IlvDim 		size,
			 IlvPalette*		palette = 0,
			 const char* 		name = 0);
    ~DrawRectangleCommand();
    // ________________________________________________________________________
    IlvDvCommand* copy() const;
    void doIt();
    void undo();
    
    BitmapDocument* getBitmapDocument() const { return _document; }
    IlvBitmap* getBitmap() const { return _bitmap; }
    IlvPalette* getPalette() const { return _palette; }

protected:
    BitmapDocument*       _document;
    IlvBitmap*            _bitmap;
    IlvRect               _rect;
    IlvPalette*           _palette;
}; 

// --------------------------------------------------------------------------
IL_MODULEINIT(drawcmd, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !__drawcmd_H */


