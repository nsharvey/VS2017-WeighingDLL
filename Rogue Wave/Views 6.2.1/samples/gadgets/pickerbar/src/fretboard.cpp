// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gadgets/pickerbar/src/fretboard.cpp
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
// Definition of the FretBoard graphic object class.
// --------------------------------------------------------------------------
#include <fretboard.h>
#include <palettechanger.h>
#include <ilviews/bitmaps/jpg.h>
#include <fstream>
#include <strstream>

// --------------------------------------------------------------------------
FretBoard::FretBoard(IlvDisplay* display, const IlvRect& location)
: IlvFilledRectangle(display, location),
  _nFingers(0),
  _nBarres(0),
  _fretOffset(0),
  _invertedPalette(0)
{
    IlvPalette* palette = getPalette();
    _invertedPalette = display->getInvertedPalette(getPalette());
    _invertedPalette->lock();
    // Apply a background pattern on the fretboard
    display->prependToPath(".");
    display->prependToPath("..");
    display->prependToPath("../..");
    const char* path = display->findInPath("data/board.jpg");
    if (path) {
	IlvJPGStreamer jpegStream;
	std::ifstream stream(path, IlvBinaryInputStreamMode);
	IlvBitmap* background = new IlvBitmap(display,
					      jpegStream.read(stream));
	_invertedPalette = PaletteChanger(_invertedPalette)
			   .setColorPattern(new IlvColorPattern(background))
			   .replace();
    }
}

// --------------------------------------------------------------------------
FretBoard::~FretBoard()
{
    _invertedPalette->unLock();
}

// --------------------------------------------------------------------------
void
FretBoard::setChord(int nFingers, int fingers[],
		    int nBarres, int barres[],
		    int fretOffset)
{
    _nFingers = nFingers;
    if (nFingers != 0) {
	IlMemMove(_fingers, fingers, nFingers*sizeof(int) * 2);
    }
    _nBarres = nBarres;
    if (nBarres != 0) {
	IlMemMove(_barres, barres, nBarres*sizeof(int) * 3);
    }
    _fretOffset = fretOffset;
}

// --------------------------------------------------------------------------
void
FretBoard::setAntialiasingMode(IlvAntialiasingMode mode)
{
    IlvFilledRectangle::setAntialiasingMode(mode);
    _invertedPalette = PaletteChanger(_invertedPalette)
		       .setAntialiasingMode(mode).replace();
}

// --------------------------------------------------------------------------
void
FretBoard::setBackground(IlvColor* background)
{
    IlvFilledRectangle::setBackground(background);
    _invertedPalette = PaletteChanger(_invertedPalette)
		       .setForeground(background).replace();
}

// --------------------------------------------------------------------------
#define nFrets 5
void
FretBoard::draw(IlvPort*	      dst,
		const IlvTransformer* t,
		const IlvRegion*      clip) const
{
    IlvRect area;
    boundingBox(area, t);
    IlvDim xW, xH, xD;
    getFont()->sizes("X", 1, xW, xH, xD);
    IlvDim margin = IlMin(6, (int)xW);
    IlvDim nutHeight = (_fretOffset == 0) ? 5 : 0;
    IlvDim interString = (area.w() - 2 * margin) / 6;
    IlvDim interFret = (area.w() - xH - nutHeight) / (nFrets - 1);
    if ((interString > 2) &&
	(interFret > 2)) {
	IlvPoint origin(area.x() + margin + interString / 2,
		        area.y() + xH + nutHeight);
	IlvDim boardWidth  = interString * 5;
	IlvDim boardHeight = interFret * (nFrets - 1);
	IlvPos x = origin.x();
	IlvPos y = origin.y();
	// Background
	dst->fillRectangle(_invertedPalette,
			   IlvRect(x, y, boardWidth, boardHeight));
	for (int string = 0; string < 6; string++, x += interString) {
	    dst->drawLine(getPalette(),
			  IlvPoint(x,  y), IlvPoint(x, y+ boardHeight));
	}
	x = origin.x();
	int fret = 0;
	int fretOffset = 0;
	if (_fretOffset == 0) {
	    // Draw nut
	    dst->fillRectangle(getPalette(),
			       IlvRect(origin.x(), origin.y()-nutHeight,
			       boardWidth+1, nutHeight));
	    y += interFret;
	    fret = 1;
	}
	else {
	    fretOffset = _fretOffset - 1;
	    char fretString[16];
	    std::strstream stream(fretString, 16, std::ios_base::out);
	    stream << _fretOffset << std::ends;
	    IlvDim w, h, d;
	    getPalette()->getFont()->sizes(fretString, -1, w, h, d);
	    dst->drawString(getPalette(),
			    IlvPoint(origin.x()-w-4, origin.y()+h/2-d),
			    fretString, -1);
	}
	for (; fret < 6; fret++, y += interFret) {
	    dst->drawLine(getPalette(),
			  IlvPoint(x, y), IlvPoint(x + boardWidth, y));
	}
	// Draw finger locations
	IlvDim fingerSize = IlMin(interString, interFret) - 5 /* margin */;
	IlvPoint o(origin.x() - (IlvPos)fingerSize / 2,
		   origin.y() + ((IlvPos)interFret-(IlvPos)fingerSize) / 2);
	if (_nFingers) {
	    int const* fp = _fingers;
	    for (int finger = 0; finger < _nFingers; finger++, fp += 2) {
		int string = fp[0];
		int fret = fp[1] - fretOffset;
		if (fret == -1) { // Un-played string
		    dst->drawString(getPalette(),
				    IlvPoint(origin.x() - xW / 2
					     + (6 - string) * interString,
					     origin.y() - nutHeight - 1),
				    "X", 1);
		}
		else {
		    dst->fillArc(getPalette(),
				 IlvRect(o.x() + (6 - string) * interString,
					 o.y() + (fret - 1) * interFret,
					 fingerSize, fingerSize),
				 0., 360.);
		}
	    }
	}
	// Draw barres
	if (_nBarres) {
	    int const* bp = _barres;
	    for (int barre = 0; barre < _nBarres; barre++, bp += 3) {
		int fret = bp[0] - fretOffset;
		int stringStart = bp[1];
		int stringEnd = bp[2];
		if (stringStart > stringEnd) {
		    int string = stringStart;
		    stringStart = stringEnd;
		    stringEnd = string;
		}
		// Start finger
		IlvPos fingerY = o.y() + (fret - 1) * interFret;
		dst->fillArc(getPalette(),
			     IlvRect(o.x() + (6-stringStart) * interString,
				     fingerY,
				     fingerSize, fingerSize),
			     0., 360.);
		// End finger
		IlvPos startFingerX = o.x() + (6 - stringEnd) * interString;
		dst->fillArc(getPalette(),
			     IlvRect(startFingerX, fingerY,
				     fingerSize, fingerSize),
			     0., 360.);
		// Barré itself
		startFingerX += interString / 2;
		dst->fillRectangle(getPalette(),
				   IlvRect(startFingerX, fingerY,
					   interString *
					   (stringEnd - stringStart),
					   fingerSize));

	    }
	}
    }
    else {
	// Area too small to draw anything
	dst->fillRectangle(_invertedPalette, area);
	dst->drawRectangle(getPalette(), area);
    }
}
