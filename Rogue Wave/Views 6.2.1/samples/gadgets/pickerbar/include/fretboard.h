// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/include/fretboard.h
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
// Declaration of the FretBoard class: it displays a guitar fretboard,
// potentially with indication on finger location or barres.
// --------------------------------------------------------------------------
#ifndef __Ilv_Samples_Fretboard_H
#define __Ilv_Samples_Fretboard_H

#include <ilviews/graphics/rectangl.h>

// --------------------------------------------------------------------------
class FretBoard
: public IlvFilledRectangle
{
public:
    FretBoard(IlvDisplay* display, const IlvRect& location);
    virtual ~FretBoard();

    /*
     * Setting a chord diagram.
     * 'fingers' indicates where fingers are located on the 
     *   fret board: <stringNo>, <fret>, ....
     * 'barres' optionnaly holds barres: <fret>, <startingStringNo>,
     *   <endingStringNo>, ...
     * 'fret' indicates the fret offset (0 is the nut of the guitar).
     */
    void setChord(int nFingers,    int fingers[],
		  int nBarres = 0, int barres[] = 0,
		  int fretOffset = 0);

    // IlvGraphic overloads
    virtual void	setAntialiasingMode(IlvAntialiasingMode mode);
    // IlvFilledRectangle overloads
    virtual void	setBackground(IlvColor* background);
    virtual void	draw(IlvPort*		   dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion*	   clip = 0) const;
private:
    IlvRect _location;
    int     _nFingers;
    int     _fingers[6*2];
    int     _nBarres;
    int     _barres[3*3];
    int     _fretOffset;
    IlvPalette* _invertedPalette;
};
#endif /* !__Ilv_Samples_Fretboard_H */
