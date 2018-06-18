// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/cursor.h
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
// Declaration of the IlvATCursor class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Cursor_H
#define __Ilv_Annotext_Cursor_H

#if !defined(__Ilv_Annotext_Rope_H)
#  include <ilviews/annotext/rope.h>
#endif

class ILVATEXPORTED IlvATRope;
class ILVATEXPORTED IlvATLine;
class ILVATEXPORTED IlvATLineCursor;
class ILVATEXPORTED IlvATFlyingCursor;

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATCursor
: public IlvATRope {
public:
    IlvATCursor(const IlvAnnoText* atext);
    virtual ~IlvATCursor();

    // Moving cursors around
    virtual void	moveTo(IlvATRope*, IlvPosition = IlvLeft);

    virtual IlBoolean	moveTo(const IlvPoint&		point,
			       const IlvTransformer*	t = 0);
    void		moveForward(IlBoolean	jumpcursor = IlTrue,
				    IlBoolean	visible    = IlTrue);
    void		moveBackward(IlBoolean	jumpcursor = IlTrue,
				     IlBoolean	visible    = IlTrue);
    void		moveNextWord(IlBoolean visible = IlTrue);
    void		movePreviousWord(IlBoolean visible = IlTrue);
    void		moveStartParagraph(IlBoolean visible = IlTrue);
    void		moveEndParagraph(IlBoolean visible = IlTrue);
    void		moveStartText();
    void		moveEndText();
    void		moveStartLine();
    void		moveEndLine();
    void		moveStartZone(IlvATZone* zone,
				      IlvPosition pos = IlvRight);
    void		moveEndZone(IlvATZone* zone,
				    IlvPosition pos = IlvLeft);

    // Inquiring about cursor position
    virtual IlBoolean	isAtWordBoundary() const;
    IlBoolean		startsParagraph(IlBoolean visible = IlTrue) const;
    IlBoolean		startsLine() const;
    IlBoolean		endsLine() const;

    ////////////////////////////////////
    // Not documented
    ////////////////////////////////////
    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;
    // Moving cursors around
    virtual void	moveTo(IlvATFlyingCursor& fc);
    void		moveNextWrapUnit(IlBoolean visible = IlTrue);
    void		movePreviousWrapUnit(IlBoolean visible = IlTrue);
    virtual IlBoolean	isAtWrapBoundary(IlvATWrap wordWrap,
					 IlvATPos  pos,
					 IlBoolean towardNext=IlTrue) const;
    IlvATLineCursor*	getStartLine();
    IlvATLineCursor*	getEndLine();

    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATInsertionCursor
: public IlvATCursor {
public:
    IlvATInsertionCursor(IlvAnnoText* text);
    // ____________________________________________________________
    inline IlBoolean	isVisible() const { return _visible; }
    inline void		setVisible(IlBoolean visible)
	{ _visible = visible;   }
    inline IlvPos	getXOffset() const { return _xOffset; }
    inline void		setXOffset(IlvPos newOffset)
	{ _xOffset = newOffset; }
    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;
    virtual IlvDim	ascent() const;
    virtual IlvDim	descent() const;

    IlvDeclareClassInfo();
private:
    IlBoolean		_visible;
    IlvPos		_xOffset;
};

// --------------------------------------------------------------------------
// Not documented
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATLineCursor
: public IlvATCursor {
public:
    IlvATLineCursor(IlvAnnoText* text);
    // ____________________________________________________________
    inline IlvATLine*	getLine() const { return _line; }
    inline void		setLine(IlvATLine* line) { _line = line; }

    IlvDeclareClassInfo();
private:
    IlvATLine*		_line;
};

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATEndCursor
: public IlvATLineCursor {
public:
    IlvATEndCursor(IlvAnnoText* text);
    virtual ~IlvATEndCursor();
    virtual IlBoolean	isLineRope() const;

    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATStartCursor
: public IlvATLineCursor {
public:
    IlvATStartCursor(IlvAnnoText* text);
    virtual IlBoolean	isLineRope() const;

    IlvDeclareClassInfo();
};
#endif /* !__Ilv_Annotext_Cursor_H */
