// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/composite.h
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
// Definition of the IlvPrintableComposite classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Composite_H
#define __Ilv_Printing_Composite_H

#ifndef __Ilv_Printing_Printable_H
#include <ilviews/printing/printable.h>
#endif

// --------------------------------------------------------------------------
// Forward declarations.
// --------------------------------------------------------------------------
class IlvPrintableCompositeList;
class IlvPrintableCompositeListIterator;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableComposite : public IlvPrintable
{
public:
    class SegmentCoordinates;
    class ILVPRINTINGEXPORTED PositionCoordinate
    {
	friend class SegmentCoordinates;
    public:
	class Parameters
	{
	public:
	    inline
	    Parameters(IlvPos			 first,
		       IlvPos			 last,
		       SegmentCoordinates const& callerSegment)
		: _first(first),
		  _last(last),
		  _callerSegment(callerSegment)
	    {}

	    inline IlvPos	getFirst() const { return _first; }
	    inline IlvPos	getLast() const { return _last; }
	    inline IlvDim	getLength() const
				{
				    return IL_CAST(IlvDim, _last - _first);
				}
	    inline IlBoolean	computeLength(IlvDim& length) const
	    {
		return _callerSegment.computeLength(getFirst(),
						    getLast(),
						    length);
	    }
	    inline PositionCoordinate const&
	    getOtherPosition(PositionCoordinate const& position) const
	    {
		return _callerSegment.getOtherPosition(position);
	    }

	private:
	    IlvPos			_first;
	    IlvPos			_last;
	    SegmentCoordinates const&	_callerSegment;
	};
	PositionCoordinate();
	/*
	 * The default copy constructor and assignment operator are used.
	 */
	virtual ~PositionCoordinate();

	inline IlBoolean computePosition(Parameters const& params,
					 IlvPos& position) const
	{
	    return internalComputePosition(params, position);
	}
	virtual
	PositionCoordinate*	clone() const = 0;

    protected:
	virtual int		getType() const = 0;
	virtual IlBoolean internalComputePosition(Parameters const& params,
						  IlvPos& position) const = 0;

    };

    class ILVPRINTINGEXPORTED RelativePositionCoordinate
	: public PositionCoordinate
    {
    public:
	RelativePositionCoordinate(IlvPos	position,
				   IlBoolean	isRelativeToFirst = IlTrue);
	/*
	 * The default destructor is used.
	 */
	RelativePositionCoordinate(RelativePositionCoordinate const& other);
	RelativePositionCoordinate& operator=(
		RelativePositionCoordinate const& other);
	inline IlvPos	getPosition() const { return _position; }
	inline
	IlBoolean	isRelativeToFirstReferencePosition() const
			{
			    return _isRelativeToFirstReferencePosition;
			}
	inline void	setPosition(IlvPos newPosition)
			{
			    _position = newPosition;
			}
	inline void	setRelativeToFirstReferencePosition(IlBoolean val)
			{
			    _isRelativeToFirstReferencePosition = val;
			}

    private:
	IlvPos		_position;
	IlBoolean	_isRelativeToFirstReferencePosition;
    };

    class ILVPRINTINGEXPORTED DeducedPositionCoordinate
	: public PositionCoordinate
    {
    public:
	DeducedPositionCoordinate();
	/*
	 * The default destructor, copy constructor, and assignment operator
	 * are used.
	 */

	virtual PositionCoordinate* clone() const;

    protected:
	virtual int	getType() const;
	virtual IlBoolean internalComputePosition(
		PositionCoordinate::Parameters const&	params,
		IlvPos&					position) const;
    };

    class ILVPRINTINGEXPORTED DeltaRelativePositionCoordinate
	: public RelativePositionCoordinate
    {
    public:
	DeltaRelativePositionCoordinate(
		IlvPos		position,
		IlBoolean	isRelativeToFirst = IlTrue);
	/*
	 * The default destructor, copy constructor, and assignment operator
	 * are used.
	 */

	virtual PositionCoordinate* clone() const;

   protected:
	virtual int	getType() const;
	virtual IlBoolean internalComputePosition(
		PositionCoordinate::Parameters const&	params,
		IlvPos&					position) const;
    };

    class ILVPRINTINGEXPORTED RatioRelativePositionCoordinate
	: public RelativePositionCoordinate
    {
    public:
	RatioRelativePositionCoordinate(
		IlvPos		position,
		IlBoolean	isRelativeToFirst = IlTrue);
	/*
	 * The default destructor, copy constructor, and assignment operator
	 * are used.
	 */

	virtual PositionCoordinate* clone() const;

    protected:
	virtual int	getType() const;
	virtual IlBoolean internalComputePosition(
		PositionCoordinate::Parameters const&	params,
		IlvPos&					position) const;
    };

    class ILVPRINTINGEXPORTED SegmentCoordinates
    {
    public:
	/*
	 * The constructor, copy constructor, and assignment operator are
	 * accessible only by the inherited classes.
	 */
	virtual ~SegmentCoordinates();

	inline IlBoolean isValid() const
	{
	    IlBoolean result = (_firstPosition && _lastPosition)
		? IlTrue
		: IlFalse;
	    if (result) {
		result = isValid(*_firstPosition, *_lastPosition);
	    }
	    return result;
	}
	inline
	IlBoolean isValid(PositionCoordinate const&	first,
			  PositionCoordinate const&	last) const
	{
	    // Valid when only one among the current objects and the two
	    // positions is deduced.
	    int count = getType() + first.getType() + last.getType();
	    return ((count > 3) && (count & 1)) ? IlTrue : IlFalse;
	}
	IlBoolean getCoordinates(IlvPos		referenceFirstPosition,
				 IlvPos		referenceLastPosition,
				 IlvPos&	firstPosition,
				 IlvDim&	length) const;

	inline PositionCoordinate const& getFirstPosition() const
	{
	    return *_firstPosition;
	}
	inline PositionCoordinate const& getLastPosition() const
	{
	    return *_lastPosition;
	}

	inline PositionCoordinate const&
	getOtherPosition(PositionCoordinate const& position) const
	{
	    return *((_lastPosition == &position)
		     ? _firstPosition
		     : _lastPosition);
	}

	IlBoolean setFirstPosition(PositionCoordinate const& newPosition);
	IlBoolean setLastPosition(PositionCoordinate const& newPosition);
	inline
	IlBoolean computeLength(IlvPos	referenceFirstPosition,
				IlvPos	referenceLastPosition,
				IlvDim&	length) const
		{
		    return internalComputeLength(referenceFirstPosition,
						 referenceLastPosition,
						 length);
		}

	virtual SegmentCoordinates* clone() const = 0;

    protected:
	SegmentCoordinates(PositionCoordinate const& first,
			   PositionCoordinate const& last);

	SegmentCoordinates(SegmentCoordinates const& other);
	SegmentCoordinates& operator=(SegmentCoordinates const& other);
	virtual int getType() const = 0;
	virtual IlBoolean internalComputeLength(IlvPos	referenceFirstPosition,
						IlvPos	referenceLastPosition,
						IlvDim&	length) const = 0;

    private:
	PositionCoordinate*	_firstPosition;
	PositionCoordinate*	_lastPosition;
    };

    class ILVPRINTINGEXPORTED RelativeSegmentCoordinates
	: public SegmentCoordinates
    {
    public:
	inline void setLength(IlvDim newLength)
	{
	    // The object may become invalid.
	    _length = newLength;
	}

    protected:
	RelativeSegmentCoordinates(PositionCoordinate const&	first,
				   PositionCoordinate const&	last,
				   IlvDim			length);

	RelativeSegmentCoordinates(RelativeSegmentCoordinates const& other);
	RelativeSegmentCoordinates& operator=(
		RelativeSegmentCoordinates const& other);

	inline IlvDim getLength() const { return _length; }

    private:
	IlvDim	_length;
    };

    class ILVPRINTINGEXPORTED DeducedSegmentCoordinates
	: public SegmentCoordinates
    {
    public:
	DeducedSegmentCoordinates(PositionCoordinate const& first,
				  PositionCoordinate const& last);
	virtual SegmentCoordinates* clone() const;

    protected:
	virtual int getType() const;
	virtual IlBoolean internalComputeLength(IlvPos	referenceFirstPosition,
						IlvPos	referenceLastPosition,
						IlvDim&	length) const;
    };

    class ILVPRINTINGEXPORTED DeltaRelativeSegmentCoordinates
    : public RelativeSegmentCoordinates
    {
    public:
	DeltaRelativeSegmentCoordinates(PositionCoordinate const& first,
					PositionCoordinate const& last,
					IlvDim			 length);
	virtual SegmentCoordinates* clone() const;

    protected:
	virtual int getType() const;
	virtual IlBoolean internalComputeLength(IlvPos	referenceFirstPosition,
						IlvPos	referenceLastPosition,
						IlvDim&	length) const;
    };

    class ILVPRINTINGEXPORTED RatioRelativeSegmentCoordinates
    : public RelativeSegmentCoordinates
    {
    public:
	RatioRelativeSegmentCoordinates(PositionCoordinate const& first,
					PositionCoordinate const& last,
					IlvDim			 length);
	virtual SegmentCoordinates* clone() const;

    protected:
	virtual int getType() const;
	virtual IlBoolean internalComputeLength(IlvPos	referenceFirstPosition,
						IlvPos	referenceLastPosition,
						IlvDim&	length) const;
    };

    class ILVPRINTINGEXPORTED Coordinates
    {
    public:
	Coordinates();
	Coordinates(SegmentCoordinates const& horizontal,
		    SegmentCoordinates const& vertical);
	~Coordinates();
	Coordinates(Coordinates const& other);
	Coordinates& operator=(Coordinates const& other);

	inline IlBoolean isValid() const
	{
	    return _horizontal->isValid() && _vertical->isValid();
	}

	IlBoolean bbox(IlvRect const& includingBox, IlvRect& bbox) const;

    private:
	SegmentCoordinates*	_horizontal;
	SegmentCoordinates*	_vertical;
    };

    class ILVPRINTINGEXPORTED Iterator
    {
	friend class IlvPrintableComposite;

    public:
	Iterator(Iterator const& other);
	~Iterator();

	Iterator& operator=(Iterator const& other);

	IlBoolean operator==(Iterator const& other) const;
	inline IlBoolean operator!=(Iterator const& other) const
	{
	    return (*this == other) ? IlFalse : IlTrue;
	}

	Iterator& operator++();
	Iterator operator++(int);

	IlvPrintable* getPrintable() const;
	Coordinates const* getCoordinates() const;

    private:
	Iterator(IlvPrintableCompositeListIterator const& internal);
	IlvPrintableCompositeListIterator* getInternal() const;

	IlvPrintableCompositeListIterator* _internal;
    };
    friend class Iterator;

    IlvPrintableComposite();
    virtual ~IlvPrintableComposite();

    virtual IlvRect	getBBox(IlvPrintableJob const& job) const;

    inline
    Iterator		append(IlvPrintable* printable,
			       Coordinates const& coordinates)
			{
			    return insert(printable, coordinates, end());
			}

    Iterator		insert(IlvPrintable* printable,
			       Coordinates const& coordinates,
			       Iterator const& iterator);

    Iterator		begin() const;
    Iterator		end() const;

protected:
    // Intentionally not defined.
    IlvPrintableComposite(IlvPrintableComposite const&);
    // Intentionally not defined.
    IlvPrintableComposite& operator=(IlvPrintableComposite const&);
    virtual IlBoolean	internalPrint(IlvPrintableJob const& job) const;

private:
    IlvPrintableCompositeList*	_components;
};

#endif /* __Ilv_Printing_Composite_H */
