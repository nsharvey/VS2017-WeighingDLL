// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/line.h
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
// Declaration of the IlvATLine class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Line_H
#define __Ilv_Annotext_Line_H

#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif
#if !defined(__Ilv_Base_Geometry_H)
#  include <ilviews/base/geometry.h>
#endif
#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif

class ILVATEXPORTED IlvATRope;
class ILVATEXPORTED IlvATBuffer;
class ILVATEXPORTED IlvATFlyingCursor;
class ILVATEXPORTED IlvATLineCursor;
class ILVATEXPORTED IlvATZone;
class ILVATEXPORTED IlvAnnoText;

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATLine
{
public:
    IlvATLine(IlvAnnoText*);
    ~IlvATLine();

    inline IlvDim	getAscent() const		{ return _ascent;   }
    inline void		setAscent(IlvDim ascent)
			{
			    _ascent = ascent;
			    _height = _ascent + _descent;
			}
    inline IlvDim	getDescent() const		{ return _descent;  }
    inline void		setDescent(IlvDim descent)
			{
			    _descent = descent;
			    _height = _ascent + _descent;
			}
    inline IlvDim	getHeight() const		{ return _height;   }
    inline IlvDim	getOffset() const		{ return _offset;   }
    inline void		setOffset(IlvDim offset)	{ _offset = offset; }
    inline IlvDim	getLength() const		{ return _length;   }
    inline void		setLength(IlvDim l)		{ _length = l;      }
    inline
    IlvATLineCursor*	getStart() const		{ return _start;    }
    IlvATLineCursor*	getEnd() const;
    inline IlvATLine*	getPrevious() const		{ return _prev;     }
    inline void		setPrevious(IlvATLine* line)	{ _prev = line;     }
    inline IlvATLine*	getNext() const			{ return _next;     }
    inline void		setNext(IlvATLine* line)	{ _next = line;     }
    // Computes a line limits and geometry
    void		computeLine(IlvDim width, IlvATFlyingCursor& curs);
    void		moveCursorToPoint(const IlvPoint&,
					  const IlvTransformer*,
					  IlvATFlyingCursor&);
    IlvATRope*		whichRope(const IlvPoint&, const IlvTransformer*);

    IlBoolean		getAbsX(const IlvATRope* rope, IlvPos& x) const;

    // not documented
    IlvATLine(IlvATLineCursor*);
protected:
    IlvATLineCursor*	_start;       // cursor to first char of line
    IlvATLine*		_prev;
    IlvATLine*		_next;
    IlvDim		_ascent;
    IlvDim		_descent;
    IlvDim		_height;
    IlvDim		_offset;      // first character horizontal offset
    IlvDim		_length;
};

#endif /* !__Ilv_Annotext_Line_H */
