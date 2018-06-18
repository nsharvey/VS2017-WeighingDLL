// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/flcursor.h
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
// Declaration of the IlvATFlyingCursor class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Flcursor_H
#define __Ilv_Annotext_Flcursor_H

#if !defined(__Ilv_Annotext_Atmacros_H)
#  include <ilviews/annotext/atmacros.h>
#endif

class ILVATEXPORTED IlvAnnoText;
class ILVATEXPORTED IlvATRope;
class ILVATEXPORTED IlvATLine;
class ILVATEXPORTED IlvATLineCursor;
class ILVATEXPORTED IlvATZone;

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATFlyingCursor
{
public:
    IlvATFlyingCursor();
    ~IlvATFlyingCursor();

    inline IlvATRope*	getRope()                const { return _rope; }
    inline void		setRope(IlvATRope* rope)       { _rope = rope; }
    inline IlvATPos	getPos()                 const { return _pos;  }
    inline void		setPos(IlvATPos pos)           { _pos = pos;   }
    inline void		incPos()                       { _pos++;       }
    inline void		decPos()                       { _pos--;       }
    // Moving cursors around
    inline void		moveTo(const IlvATFlyingCursor* fc)
			{
			    _rope = fc->_rope;
			    _pos  = fc->_pos;
			}
    inline void		moveTo(IlvATRope* rope, IlvATPos pos = 0)
			{
			    _rope = rope;
			    _pos = pos;
			}
    void		moveForward(IlBoolean jumpcursor	= IlTrue,
				    IlBoolean visible		= IlTrue);
    void		moveBackward(IlBoolean jumpcursor	= IlTrue,
				     IlBoolean visible		= IlTrue);
    void		moveNextWrapUnit(IlBoolean visible	= IlTrue);
    void		movePreviousWrapUnit(IlBoolean visible	= IlTrue);
    void		moveNextWord(IlBoolean visible		= IlTrue);
    void		movePreviousWord(IlBoolean visible	= IlTrue);
    void		movePreviousParagraph(IlBoolean visible	= IlTrue);
    void		moveNextParagraph(IlBoolean visible	= IlTrue);
    void		moveStartText(const IlvAnnoText* atext);
    void		moveEndText(const IlvAnnoText* atext);
    void		jumpCursorsForward(IlBoolean jumlines	= IlTrue);
    void		jumpCursorsBackward(IlBoolean jumlines	= IlTrue);
    IlvATLineCursor*	getStartLine();
    IlvATLineCursor*	getEndLine();
    void		moveStartZone(const IlvATZone*);
    void		moveEndZone(const IlvATZone*);

    // Inquiring about cursor position
    IlBoolean		isAtWrapBoundary(IlBoolean beg = IlFalse) const;
    IlBoolean		isAtWordBoundary(IlBoolean beg = IlFalse) const;
    IlBoolean		isAtSamePosition(const IlvATFlyingCursor* fc) const;
    IlBoolean		startsParagraph(IlBoolean visible = IlTrue) const;
    IlBoolean		startsLine() const;
    IlBoolean		endsLine(IlvATRope*& lastRopeFound) const;
    IlInt		comparePosition(const IlvATFlyingCursor*) const;
    IlInt		comparePosition(const IlvATRope*) const;

    // Length computations
    IlvDim		wrapUnitLength(IlvPos pos) const;
    IlvDim		computeUntil(IlvATFlyingCursor&	end,
				     IlvDim&		ascent,
				     IlvDim&		descent,
				     IlBoolean&		linebreak,
				     IlvPos		position) const;
private:
    IlvATRope*		_rope;
    IlvATPos		_pos;
};

#endif /* !__Ilv_Annotext_Flcursor_H */
