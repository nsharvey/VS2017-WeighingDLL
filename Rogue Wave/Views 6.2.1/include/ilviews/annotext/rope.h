// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/annotext/rope.h
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
// Declaration of the IlvATRope class
// Defined in library ilvatext
// --------------------------------------------------------------------------
#ifndef __Ilv_Annotext_Rope_H
#define __Ilv_Annotext_Rope_H

#if !defined(__Ilv_Annotext_Palette_H)
#  include <ilviews/annotext/palette.h>
#endif
#if !defined(__Ilv_Base_Clssinfo_H)
#  include <ilviews/base/clssinfo.h>
#endif

class ILVATEXPORTED  IlvATZone;
class ILVATEXPORTED  IlvATPalette;
class ILVATEXPORTED  IlvAnnoText;
class ILVATEXPORTED  IlvATBuffer;
class ILVATEXPORTED  IlvATLine;
class ILVVWSEXPORTED IlvGraphic;
class IlvATRopeExtension;

typedef enum IlvATRopeType {
    IlvATTextRopeType,
    IlvATGraphicRopeType,
    IlvATStartRopeType,
    IlvATEndRopeType,
    IlvATParagraphRopeType,
    IlvATCursorRopeType,
    IlvATInsertionRopeType,
    IlvATLineRopeType,
    IlvATTabulationRopeType,
    IlvATBreakRopeType,
    IlvATSeparatorRopeType
} _IlvATRopeType;

// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATRope
{
public:
    IlvATRope(const IlvAnnoText* text);
    virtual ~IlvATRope();

    // Documented in cursors
    inline IlBoolean	isConnected() const
			{
			    return _previous ? IlTrue : IlFalse;
			}
    inline IlvATZone*	getZone() const { return _zone; }
    virtual void	extract();

    // Not documented
    inline IlvATRope*	getPrevious()          const { return _previous; }
    inline void		setPrevious(IlvATRope* prev) { _previous = prev; }
    inline IlvATRope*	getNext()              const { return _next;     }
    inline void		setNext(IlvATRope* next)     { _next = next;     }
    inline IlvATPos	getLength()            const { return _length;   }
    inline void		setLength(IlvATPos length)   { _length = length; }
    inline void		setZone(IlvATZone* zone)     { _zone = zone;     }
    inline IlvAnnoText*	getAnnoText()          const { return _atext;    }
    inline IlvATRopeType getType()             const { return _type;     }
    inline void		setType(IlvATRopeType type)  { _type = type;     }
    IlvATPalette*	getTextPalette() const;
    IlvATInteractor*	getInteractor() const;
    IlBoolean		firstInParagraph();
    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const=0;

    // Copies zone, tpalette info from given rope
    void		copyZoneInfo();

    // Compute geometry of a rope
    virtual IlvDim	width(IlvATPos, IlvATPos, IlvPos) const;
    virtual IlvDim	ascent() const;
    virtual IlvDim	descent() const;

    // Operations on ropes
    virtual void	insertRope(IlvATRope* insrope,
				   IlvPosition = IlvLeft);
    virtual void	appendRope(IlvATRope* rope);
    virtual IlBoolean	isAtWrapBoundary(IlvATWrap,
					 IlvATPos,
					 IlBoolean = IlFalse) const;
    virtual IlBoolean	scanTillBoundary(IlvATRope** currentRope,
					 IlBoolean   todNext = IlTrue) const;
    virtual IlvATRope*	cutRope(IlvATPos pos);
    virtual IlBoolean	transfert(IlvATRope*, IlvATPos = 0);

    // Rope location
    IlBoolean		where(IlvPoint&             point,
			      const IlvTransformer* t         = 0,
			      IlBoolean             drawnOnly =IlTrue) const;
    IlvATLine*		whichLine() const;

    IlBoolean		isBefore(const IlvATRope* rope) const;

    // Invertion for selection
    inline IlBoolean	isInverted()          const { return _inverted;     }
    inline void		setInverted(IlBoolean b)    { _inverted = b;        }
    inline IlAny	getUserData()         const { return _userData;     }
    inline void		setUserData(IlAny userData) { _userData = userData; }

    // on type member functions
    virtual IlBoolean	isLineRope()		const;
    virtual IlBoolean	isEndRope()		const;
    virtual IlBoolean	isStartRope()		const;
    virtual IlBoolean	isSeparatorRope()	const;
    virtual IlBoolean	isTextRope()		const;
    virtual IlBoolean	isCursorRope()		const;
    virtual IlBoolean	isInsertionRope()	const;
    virtual IlBoolean	isGraphicRope()		const;
    virtual IlBoolean	isTabulationRope()	const;
    virtual IlBoolean	isSpecialRope()		const;
    virtual IlBoolean	isParagraphRope()	const;
    virtual IlBoolean	isBreakRope()		const;

    virtual IlUInt	getStringRepresentationLength();
    virtual IlBoolean	selfWriting(char** bufferLocation, IlUInt freeSpace);

    inline
    IlvATRopeExtension*	getExtension()		const { return _extension; }

    IlvDeclareClassInfo();
protected:
    friend class IlvATRopeExtension;

    IlvATRope*		_previous;
    IlvATRope*		_next;
    IlvATRopeType	_type;
    IlvATPos		_length; // Length of the rope
    IlvATZone*		_zone;   // Inner zone containing this rope
    IlvAnnoText*	_atext;
    IlBoolean		_inverted;
    IlAny		_userData;
    IlvATRopeExtension*	_extension;
};

// --------------------------------------------------------------------------
// Sub-class for Texts
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATTextRope
: public IlvATRope {
public:
    IlvATTextRope(const IlvAnnoText* text);

    inline const char*	getStart() const            { return _start;  }
    void		setStart(const char* start);

    // Draws rope, from character start, from position pos on screen.
    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;

    // Geometry
    virtual IlvDim	width(IlvATPos	start,
			      IlvATPos	end,
			      IlvPos	x = 0) const;
    virtual IlvDim	ascent() const;
    virtual IlvDim	descent() const;

    // Operations
    virtual IlvATRope*	cutRope(IlvATPos pos);
    virtual IlBoolean	isAtWrapBoundary(IlvATWrap	wrap,
					 IlvATPos	pos,
					 IlBoolean	beg = IlFalse) const;
    virtual IlBoolean	transfert(IlvATRope*	rope,
				  IlvATPos	pos = 0);

    IlvDeclareClassInfo();
private:
    const char*		_start; // Pointer to the first character of the rope
};

// --------------------------------------------------------------------------
// Sub-class for Graphics
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATGraphicRope
: public IlvATRope {
public:
    IlvATGraphicRope(const IlvAnnoText*	text,
		     IlvGraphic*	graphic	= 0,
		     IlBoolean		owner	= IlFalse);
    ~IlvATGraphicRope();

    inline IlvGraphic*	getGraphic() const
	{ return _graphic;    }
    inline void		setGraphic(IlvGraphic* graphic)
	{ _graphic = graphic; }
    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;
    // Geometry
    virtual IlvDim	width(IlvATPos	start,
			      IlvATPos	end,
			      IlvPos	x = 0) const;
    virtual IlvDim	ascent() const;
    virtual IlvDim	descent() const;
    IlvPos		alignmentOffset() const;
    // accessors
    inline IlBoolean	isOwner()         const { return _owner; }
    inline void		setOwner(IlBoolean own) { _owner = own;  }

    IlvDeclareClassInfo();
protected:
    IlvGraphic*		_graphic;
    IlBoolean		_owner;
};
// --------------------------------------------------------------------------
// Sub-class for Tabulation
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATTabulationRope
: public IlvATRope {
public:
    IlvATTabulationRope(const IlvAnnoText* text);

    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;
    // Geometry
    virtual IlvDim	width(IlvATPos	start,
			      IlvATPos	end,
			      IlvPos	x = 0) const;
    virtual IlUInt	getStringRepresentationLength();
    virtual IlBoolean	selfWriting(char** bufferLocation, IlUInt freeSpace);

    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
// Sub-class for Separator
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATSeparatorRope
: public IlvATRope {
public:
    IlvATSeparatorRope(const IlvAnnoText*	text,
		       IlvDim			size,
		       IlFloat			width);

    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;
    // Geometry
    virtual IlvDim	width(IlvATPos	start,
			      IlvATPos	end,
			      IlvPos	x = 0) const;
    virtual IlvDim	ascent()	const;
    virtual IlvDim	descent()	const;
    inline IlvDim	getSize()	const { return _size; }
    inline IlFloat	getWidth()	const { return _width; }

    IlvDeclareClassInfo();
protected:
    IlvDim		_size;
    IlFloat		_width;
};

// --------------------------------------------------------------------------
// Sub-class for special markers Paragraph, Cursor
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATSpecialRope
: public IlvATRope {
public:
    IlvATSpecialRope(const IlvAnnoText* text, IlvATRopeType type);

    virtual void	draw(IlvPort*		dst,
			     const IlvTransformer* t,
			     const IlvRegion*	clip,
			     IlvPoint&		point,
			     IlvATPos		start,
			     IlvATPos		len,
			     IlBoolean		inXORmode = IlFalse) const;
    virtual IlvDim	ascent()	const;
    virtual IlvDim	descent()	const;
    virtual IlUInt	getStringRepresentationLength();
    virtual IlBoolean	selfWriting(char** buffer, IlUInt freeSpace);

    IlvDeclareClassInfo();
};

// --------------------------------------------------------------------------
// Sub-class for Break
// --------------------------------------------------------------------------
class ILVATEXPORTED IlvATBreakRope
: public IlvATSpecialRope {
public:
    IlvATBreakRope(const IlvAnnoText* text);

    virtual IlvDim	ascent()	const;
    virtual IlvDim	descent()	const;

    IlvDeclareClassInfo();
};

ILVATMODULEINIT(ilvat_rope);
#endif /* !__Ilv_Annotext_Rope_H */
