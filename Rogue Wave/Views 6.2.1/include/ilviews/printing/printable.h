// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/printable.h
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
// Definition of the IlvPrintable and IlvPrintableJob classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Printable_H
#define __Ilv_Printing_Printable_H

#if !defined(__Ilv_Printing_Macros_H)
#include <ilviews/printing/macros.h>
#endif

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

#if !defined(__Il_Array_H)
#include <ilog/array.h>
#endif

// --------------------------------------------------------------------------
// Forward declarations.
class IlvPrintableJob;
class IlvPrinter;
class IlvPrintableDocumentJobInitializer;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintable
{
public:

public:
    IlvPrintable();
    virtual ~IlvPrintable();
    IlvPrintable(IlvPrintable const& other);

    IlvPrintable& operator=(IlvPrintable const& other);

    IlBoolean print(IlvPrintableJob const& job) const;
    virtual IlvRect getBBox(IlvPrintableJob const& job) const = 0;
    void lock();
    void unlock();

protected:
    virtual IlBoolean internalPrint(IlvPrintableJob const& job) const = 0;

private:
    int _referenceCounter;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableScalable : public IlvPrintable
{
public:
    IlvPrintableScalable(IlvRect const&		scalableArea,
			 IlvRegion const*	clip = 0,
			 IlvTransformer const*	t = 0);
    virtual IlvRect getBBox(IlvPrintableJob const& job) const;
     IlvRect const& getScalableArea() const;
    void setScalableArea(IlvRect const& scalableArea);
    IlBoolean hasClip() const;
    IlvRegion const& getClip() const;
    void setClip(IlvRegion const& clip);
    void resetClip();
    IlBoolean hasTransformer() const;
    IlvTransformer const* getTransformer() const;
    void setTransformer(IlvTransformer const* t);
    void resetTransformer();

private:
    IlvRect		_scalableArea;
    IlBoolean		_hasClip;
    IlvRegion		_clip;
    IlBoolean		_hasTransformer;
    IlvTransformer	_t;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableJob
{
    friend class IlvPrintableDocumentJobInitializer;
public:
    IlvPrintableJob(IlvPrinter& printer);
    IlvPrintableJob(IlvPrintableJob const& other);

    IlvPrinter& getPrinter() const;
    IlvPrintable* getPrintable() const;
    void setPrintable(IlvPrintable* printable);
    int getPageIndex() const;
    void incPageIndex();
    int getAllPageNumber() const;
    int getFirstPageIndex() const;
    int getLastPageIndex() const;
    int getPageNumber() const;
    int getPageCount() const;
    IlvRect getBBox() const;
    void setBBox(IlvRect const& bbox);
    IlvTransformer getTransformer() const;
    void setTransformer(IlvTransformer const& transformer);

private:
    // Intentionally not defined.
    IlvPrintableJob& operator=(IlvPrintableJob const& other);

    void setPageIndex(int newIndex);
    void setAllPageNumber(int newNumber);
    void setFirstPageIndex(int newIndex);
    void setLastPageIndex(int newIndex);
    void setAbsoluteMode(IlBoolean newMode);

    IlvPrinter&		_printer;
    IlvPrintable*	_printable;
    int			_pageIndex;
    int			_allPageNumber;
    int			_firstPageIndex;
    int			_lastPageIndex;
    IlBoolean		_isAbsoluteMode;
    IlvRect		_bbox;
    IlvTransformer	_transformer;
};

// --------------------------------------------------------------------------
// Inline functions.
// --------------------------------------------------------------------------
inline void
IlvPrintable::lock()
{
    ++_referenceCounter;
}

// --------------------------------------------------------------------------
inline void
IlvPrintable::unlock()
{
    --_referenceCounter;
    if (_referenceCounter == 0) {
	delete this;
    }
}

// --------------------------------------------------------------------------
inline
IlvPrintableJob::IlvPrintableJob(IlvPrinter& printer)
: _printer(printer),
  _printable(0),
  _pageIndex(0),
  _allPageNumber(0),
  _firstPageIndex(0),
  _lastPageIndex(0),
  _isAbsoluteMode(IlTrue),
  _bbox(),
  _transformer()
{
}

// --------------------------------------------------------------------------
inline
IlvPrintableJob::IlvPrintableJob(IlvPrintableJob const& other)
: _printer(other._printer),
  _printable(other._printable),
  _pageIndex(other._pageIndex),
  _allPageNumber(other._allPageNumber),
  _firstPageIndex(other._firstPageIndex),
  _lastPageIndex(other._lastPageIndex),
  _isAbsoluteMode(other._isAbsoluteMode),
  _bbox(other._bbox),
  _transformer(other._transformer)
{
}

// --------------------------------------------------------------------------
inline IlvPrinter&
IlvPrintableJob::getPrinter() const
{
    return _printer;
}

// --------------------------------------------------------------------------
inline IlvPrintable*
IlvPrintableJob::getPrintable() const
{
    return _printable;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setPrintable(IlvPrintable* printable)
{
    _printable = printable;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableJob::getPageIndex() const
{
    return _pageIndex;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::incPageIndex()
{
    ++_pageIndex;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableJob::getAllPageNumber() const
{
    return _allPageNumber;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableJob::getFirstPageIndex() const
{
    return _firstPageIndex;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableJob::getLastPageIndex() const
{
    return _lastPageIndex;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableJob::getPageNumber() const
{
    int number = _pageIndex + 1;
    if (!_isAbsoluteMode) {
	number -= _firstPageIndex;
    }
    return number;
}

// --------------------------------------------------------------------------
inline int
IlvPrintableJob::getPageCount() const
{
    return _isAbsoluteMode ? _allPageNumber : _lastPageIndex - _firstPageIndex;
}

// --------------------------------------------------------------------------
inline IlvRect
IlvPrintableJob::getBBox() const
{
    return _bbox;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setBBox(IlvRect const& bbox)
{
    _bbox = bbox;
}

// --------------------------------------------------------------------------
inline IlvTransformer
IlvPrintableJob::getTransformer() const
{
    return _transformer;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setPageIndex(int newIndex)
{
    _pageIndex = newIndex;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setAllPageNumber(int newNumber)
{
    _allPageNumber = newNumber;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setFirstPageIndex(int newIndex)
{
    _firstPageIndex = newIndex;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setLastPageIndex(int newIndex)
{
    _lastPageIndex = newIndex;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setAbsoluteMode(IlBoolean newMode)
{
    _isAbsoluteMode = newMode;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableJob::setTransformer(IlvTransformer const& transformer)
{
    _transformer = transformer;
}

// --------------------------------------------------------------------------
inline IlvRect const&
IlvPrintableScalable::getScalableArea() const
{
    return _scalableArea;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableScalable::setScalableArea(IlvRect const& scalableArea)
{
    _scalableArea = scalableArea;
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvPrintableScalable::hasClip() const
{
    return _hasClip;
}

// --------------------------------------------------------------------------
inline IlvRegion const&
IlvPrintableScalable::getClip() const
{
    return _clip;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableScalable::setClip(IlvRegion const& clip)
{
    _clip	= clip;
    _hasClip	= IlTrue;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableScalable::resetClip()
{
    _hasClip = IlFalse;
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvPrintableScalable::hasTransformer() const
{
    return _hasTransformer;
}

// --------------------------------------------------------------------------
inline IlvTransformer const*
IlvPrintableScalable::getTransformer() const
{
    return _hasTransformer ? &_t : 0;
}

// --------------------------------------------------------------------------
inline void
IlvPrintableScalable::setTransformer(IlvTransformer const* t)
{
    _hasTransformer = (t ? IlTrue : IlFalse);
    if (hasTransformer()) {
	_t = *t;
    }
}

// --------------------------------------------------------------------------
inline void
IlvPrintableScalable::resetTransformer()
{
    _hasTransformer = IlFalse;
}

#endif /* __Ilv_Printing_Printable_H */
