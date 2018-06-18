// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/geomhan.h
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
// Declaration of the geometry handler
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Geomhan_H
#define __Ilv_Graphics_Geomhan_H

// --------------------------------------------------------------------------
#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

class ILVVWSEXPORTED IlvGraphicHolder;
class ILVVWSEXPORTED IlvGeometryHandler;
class ILVVWSEXPORTED IlvGuideHandler;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGHGlue
{
public:
    IlvGHGlue(IlInt initialSize, IlInt limit, IlInt weight)
	: _weight(weight),
	  _limit(limit),
	  _initialSize(initialSize)
    {};
    IlvGHGlue(IlvInputFile&, IlvDisplay*);
    virtual ~IlvGHGlue();

    inline IlInt 	getWeight() const { return _weight; }
    inline void 	setWeight(IlInt weight) { _weight = weight; }
    inline IlInt 	getLimit() const { return _limit; }
    inline void 	setLimit(IlInt minsize) { _limit = minsize; }
    inline IlInt 	getInitialSize() const { return _initialSize; }
    inline void 	setInitialSize(IlInt initialsize)
			{
			    _initialSize = initialsize;
			}
    virtual void	setValue(IlInt pos, IlInt size);
    virtual void	write(IlvOutputFile&);

protected:
    IlInt		_weight;
    IlInt		_limit;
    IlInt		_initialSize;
}; // class IlvGHGlue

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGHGraphic : public IlvGHGlue
{
public:
    IlvGHGraphic(IlvGraphic*, IlInt limit, IlInt weight, IlvDirection dir);
    IlvGHGraphic(IlvGraphic*, IlInt weight, IlvDirection dir);
    IlvGHGraphic(IlvInputFile&, IlvDisplay*);
    IlvGraphic* getGraphic() const { return _graphic; }
    virtual void	write(IlvOutputFile&);
    inline IlvPos	getCurrentPosition() const { return _currentPosition; }
    inline void 	setCurrentPosition(IlInt pos)
			{
			    _currentPosition = pos;
			}
    inline IlInt 	getCurrentSize() const { return _currentSize; }
    inline void 	setCurrentSize(IlInt size) { _currentSize = size; }
    virtual void	setValue(IlInt pos, IlInt size);

protected:
    IlvGraphic*		_graphic;
    IlInt		_currentPosition;
    IlInt		_currentSize;
}; // class IlvGHGraphic

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGHGuide : public IlvGHGlue
{
public:
    IlvGHGuide(IlvPos pos,  IlInt size, IlInt limit, IlInt weight);
    IlvGHGuide(IlvInputFile&, IlvDisplay*);
    ~IlvGHGuide();
    inline IlvPos 	getInitialPosition() const { return _initialPosition; }
    inline void 	setInitialPosition(IlvPos pos) { _initialPosition = pos; }
    void		subscribe(IlvGeometryHandler*);
    void		unSubscribe(IlvGeometryHandler*);
    inline const IlArray&	getSubscriptions() const 
				{
				    return _geometryHandlers;
				}
    inline IlArray&	subscriptions() { return _geometryHandlers; }
    virtual void	write(IlvOutputFile&);
    void		readGeometryHandler(IlvInputFile&    ifile,
					    IlvDisplay*      d,
					    IlvGuideHandler* gh);
    void		writeGeometryHandler(IlvOutputFile&   of,
					     IlvGuideHandler* gh);
    void		removeElement(IlvGraphic*);
    IlvPos		getCurrentPosition() const;
    void		setCurrentPosition(IlInt pos);
    IlInt		getCurrentSize() const;
    void		setCurrentSize(IlInt size);
    IlInt		getOffset() const;
    void		setOffset(IlInt val);
    virtual void	setValue(IlInt pos, IlInt size);
protected:
    IlvPos		_initialPosition;
    IlArray		_geometryHandlers;
    IlInt		_currentPosition;
    IlInt		_currentSize;
    IlInt		_offset;
}; // class IlvGHGuide

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGHAbstractHandler
{
public:
    virtual ~IlvGHAbstractHandler();
    IlInt			getWeights() const;
    virtual IlvDim		getInitialSize() const = 0;
    inline IlBoolean		isVertical() 
				{
				    return (IlBoolean)
					(_direction == IlvVertical);
				}
    inline IlvDirection 	getDirection() const { return  _direction; }
    virtual void		resize(IlvDim newsize, IlvGraphicHolder*) = 0;
    inline const IlArray&	getElements() const { return _elements; }
    IlUInt			getIndex(IlvGHGlue*) const;
    inline IlUInt		getLength() const 
				{
				    return _elements.getLength();
				}
    inline IlvGHGlue*		operator[](IlUInt ndx) const
				{
				    return (IlvGHGlue*)_elements[ndx];
				}

protected:
    IlvDirection		_direction;
    IlArray			_elements;

    IlvGHAbstractHandler(IlvDirection);

    void			applyVariation(IlInt begin,
					       IlInt variation,
					       IlvGraphicHolder*);
    friend class IlvGraphicHolder;
}; // class IlvGHAbstractHandler

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGuideHandler : public IlvGHAbstractHandler
{
public:
    IlvGuideHandler(IlvDim size, IlvDirection);
    IlvGuideHandler(IlvInputFile&, IlvDisplay*, IlvDirection dir);
    IlvGHGuide* 	addGuide(IlUInt num, IlvDim size,
				 IlInt limit, IlInt weight);
    IlUInt 		addGuide(IlvPos pos);
    IlBoolean 		removeGuide(IlUInt num);
    inline IlvGHGuide* 	getGuide(IlUInt i) const
			{
			    return (IlvGHGuide*)_elements[i];
			}
    IlUInt		whichGuide(IlvPos) const;
    void 		removeElement(IlvGraphic*);
    virtual IlvDim 	getInitialSize() const;
    void		resetValues();
    IlvDim		getCurrentSize() const;
    virtual void 	resize(IlvDim newsize, IlvGraphicHolder*);
    void 		write(IlvOutputFile&);
    void		draw(const IlvGraphicHolder*,
			     const IlvPalette*,
			     const IlvRegion* clip = 0) const;
    void		draw(IlvPos,
			     const IlvGraphicHolder*,
			     const IlvPalette*,
			     const IlvRegion* clip = 0) const;
    IlBoolean		isEmpty() const;

    friend class IlvGraphicHolder;
}; // class IlvGuideHandler

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvGeometryHandler : public IlvGHAbstractHandler
{
public:
    IlvGeometryHandler(IlvGHGuide* begin, IlvGHGuide* end, IlvDirection);
    IlvGeometryHandler(IlvInputFile&, IlvDisplay*, IlvGuideHandler*);
    virtual ~IlvGeometryHandler();
    virtual void	resize(IlvDim newsize, IlvGraphicHolder*);

    virtual IlvDim	getInitialSize() const;
    IlInt		getCurrentSize() const;
    inline IlInt	getElementWeight(const IlvGraphic* elt) const
			{
			    return getElement(elt)->getWeight();
			}
    inline void		setElementWeight(const IlvGraphic* elt, IlInt weight)
			{
			    getElement(elt)->setWeight(weight);
			}
    inline IlInt	getElementLimit(const IlvGraphic* elt) const
			{
			    return getElement(elt)->getLimit();
			}
    inline void		setElementLimit(const IlvGraphic* elt, IlInt minsize)
			{
			    getElement(elt)->setLimit(minsize);
			}
    inline IlInt	getElementInitialSize(const IlvGraphic* elt) const
			{
			    return getElement(elt)->getInitialSize();
			}
    inline void		setElementInitialSize(const IlvGraphic* elt,
					      IlInt             initialsize)
			{
			    getElement(elt)->setInitialSize(initialsize);
			}
    inline IlInt	getPreviousElementWeight(const IlvGraphic* elt) const
			{
			    return getPreviousElement(elt)->getWeight();
			}
    inline void		setPreviousElementWeight(const IlvGraphic* elt,
						 IlInt             weight)
			{
			    getPreviousElement(elt)->setWeight(weight);
			}
    inline IlInt	getPreviousElementLimit(const IlvGraphic* elt) const
			{
			    return getPreviousElement(elt)->getLimit();
			}
    inline void		setPreviousElementLimit(const IlvGraphic* elt,
						IlInt             minsize)
			{
			    getPreviousElement(elt)->setLimit(minsize);
			}
    inline IlInt	getPreviousElementInitialSize(const IlvGraphic* elt) const
			{
			    return getPreviousElement(elt)->getInitialSize();
			}
    inline void		setPreviousElementInitialSize(const IlvGraphic* elt,
						      IlInt initialsize)
			{
			    getPreviousElement(elt)->setInitialSize(initialsize);
			}
    inline IlInt	getNextElementWeight(const IlvGraphic* elt) const
			{
			    return getNextElement(elt)->getWeight();
			}
    inline void		setNextElementWeight(const IlvGraphic* elt,
					     IlInt             weight)
			{
			    getNextElement(elt)->setWeight(weight);
			}
    inline IlInt	getNextElementLimit(const IlvGraphic* elt) const
			{
			    return getNextElement(elt)->getLimit();
			}
    inline void		setNextElementLimit(const IlvGraphic* elt,
					    IlInt             minsize)
			{
			    getNextElement(elt)->setLimit(minsize);
			}
    inline IlInt	getNextElementInitialSize(const IlvGraphic* elt) const
			{
			    return getNextElement(elt)->getInitialSize();
			}
    inline void		setNextElementInitialSize(const IlvGraphic* elt,
						  IlInt initialsize)
			{
			    getNextElement(elt)->setInitialSize(initialsize);
			}

    inline IlvGHGuide*	getBegin() const { return _begin; }
    inline void		setBegin(IlvGHGuide* guide) { _begin = guide; }
    inline IlvGHGuide*	getEnd() const { return _end; }
    inline void		setEnd(IlvGHGuide* guide) { _end = guide; }

    void		addElement(IlvGraphic* toinsert, IlInt weight = 0);
    void		insertElementPrevious(IlvGraphic* where,
					      IlvGraphic* toinsert,
					      IlInt weight = 0);
    void		insertElementNext(IlvGraphic* where,
					  IlvGraphic* toinsert,
					  IlInt weight = 0);
    void		removeElement(IlvGraphic*);
    void		write(IlvOutputFile&, const IlvGuideHandler*);
    void		resetValues();
    void		resetInitialSizes();
    IlvGHGlue*		getElement(const IlvGraphic*) const;
    IlvGHGlue*		getPreviousElement(const IlvGraphic*) const;
    IlvGHGlue*		getNextElement(const IlvGraphic*) const;

protected:
    IlvGHGuide*		_begin;
    IlvGHGuide*		_end;

    void		insertElement(IlvGHGlue* in, IlvGHGraphic* toinsert);

    friend class IlvGraphicHolder;
    friend class IlvGHEdit;
}; // class IlvGeometryHandler

#endif /* __Ilv_Graphics_Geomhan_H */
