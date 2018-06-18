// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/layout.h
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
// Definition of the IlvPrintableLayout classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Layout_H
#define __Ilv_Printing_Layout_H

#if !defined(__Ilv_Printing_Macros_H)
#  include <ilviews/printing/macros.h>
#endif
#if !defined(__Ilv_Printing_Units_H)
#  include <ilviews/printing/units.h>
#endif
#if !defined(__Ilv_Base_Geometry_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Il_Array_H)
#  include <ilog/array.h>
#endif

#if defined(_MSC_VER) && defined(IL_DLL)
#  if (_MSC_VER >= 1200)
#    pragma warning( push )
#  endif /* _MSC_VER >= 1200 */
#  pragma warning( disable : 4251 )
#endif /* _MSC_VER && IL_DLL */

// --------------------------------------------------------------------------
// Forward declarations.
class IlvPrinter;
class IlvPrintable;
class IlvPrintableJob;
class IlvPrintableLayout;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableArea
{
public:
    IL_EXPLICIT IlvPrintableArea(IlvPrintableLayout const& layout);
    virtual ~IlvPrintableArea();

    virtual
    IlvPrintableArea*	clone() const = 0;

    inline
    IlvPrintableLayout const& getPrintableLayout() const
			{
			    return _layout;
			}
    virtual IlBoolean	print(IlvPrintableJob&	job,
			      IlvPrintable*	printable) const = 0;
    virtual void	setBBox(IlvRect const& bbox) = 0;
    virtual void	setTransformer(IlvTransformer const& transformer) = 0;

private:
    IlvPrintableLayout const&	_layout;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableNullArea : public IlvPrintableArea
{
public:
    IL_EXPLICIT IlvPrintableNullArea(IlvPrintableLayout const& layout);

    virtual
    IlvPrintableArea*	clone() const;

    virtual IlBoolean	print(IlvPrintableJob&	job,
			      IlvPrintable*	printable) const;
    virtual void	setBBox(IlvRect const& bbox);
    virtual void	setTransformer(IlvTransformer const& transformer);
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableActualArea : public IlvPrintableArea
{
public:
    IlvPrintableActualArea(IlvPrintableLayout const&	layout,
			   IlvRect const&		bbox,
			   IlvTransformer const&	transformer);
    virtual
    IlvPrintableArea*	clone() const;

    virtual IlBoolean	print(IlvPrintableJob&	job,
			      IlvPrintable*	printable) const;
    virtual void	setBBox(IlvRect const& bbox);
    virtual void	setTransformer(IlvTransformer const& transformer);

protected:
    IlvRect		getBBox() const;
    IlvTransformer	getTransformer() const;

private:
    IlvRect		_bbox;
    IlvTransformer	_transformer;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableLayout
{
public:
    IlvPrintableLayout();
    virtual ~IlvPrintableLayout();
    inline IlvDim	getLeftMargin() const { return _leftMargin; }
    inline IlvDim	getRightMargin() const { return _rightMargin; }
    inline IlvDim	getTopMargin() const { return _topMargin; }
    inline IlvDim	getBottomMargin() const { return _bottomMargin; }
    inline IlvDim	getGutterMargin() const { return _gutterMargin; }
    inline void		getMargins(IlvDim& left,
				   IlvDim& right,
				   IlvDim& top,
				   IlvDim& bottom,
				   IlvDim& gutter) const
			{
			    left = _leftMargin;
			    right = _rightMargin;
			    top = _topMargin;
			    bottom = _bottomMargin;
			    gutter = _gutterMargin;
			}
    IlvRect		getUsableArea(IlvPrinter const&	printer,
				      IlBoolean isGutterOnLeft = IlTrue) const;
    virtual IlvDim	getHeaderAreaHeight() const = 0;
    virtual IlvDim	getFooterAreaHeight() const = 0;
    virtual void	setHeaderAreaHeight(IlvDim height) = 0;
    virtual void	setFooterAreaHeight(IlvDim height) = 0;
    inline IlBoolean	isRatioKept() const { return _keepRatio; }
    inline void		setLeftMargin(IlvDim margin) { _leftMargin = margin; }
    inline void		setRightMargin(IlvDim margin) { _rightMargin=margin; }
    inline void		setTopMargin(IlvDim margin) { _topMargin = margin; }
    inline void		setBottomMargin(IlvDim margin)
			{
			    _bottomMargin = margin;
			}
    inline void		setGutterMargin(IlvDim margin)
			{
			    _gutterMargin = margin;
			}
    inline void		setMargins(IlvDim left,
				   IlvDim right,
				   IlvDim top,
				   IlvDim bottom,
				   IlvDim gutter)
			{
			    _leftMargin = left;
			    _rightMargin = right;
			    _topMargin = top;
			    _bottomMargin = bottom;
			    _gutterMargin = gutter;
			}
    inline void		setKeepingRatio(IlBoolean keepRatio)
			{
			    _keepRatio = keepRatio;
			}
    inline void		lock() { ++_refCount; }
    inline void		unlock() { if (--_refCount == 0) delete this; }
    inline IlUInt	getRefCount() const { return _refCount; }
    IlBoolean		print(IlvPrintableJob& job, int copyNumber) const;
    IlvPrintableArea const& getBackgroundArea(IlvPrintableJob& job,
					      int pageIndex) const;
    IlvPrintableArea const& getHeaderArea(IlvPrintableJob& job,
					  int pageIndex) const;
    IlvPrintableArea const& getMainArea(IlvPrintableJob& job,
					int pageIndex) const;
    IlvPrintableArea const& getFooterArea(IlvPrintableJob& job,
					  int pageIndex) const;
    IlvPrintableArea const& getForegroundArea(IlvPrintableJob& job,
					      int pageIndex) const;
    inline
    IlvPrintable*	getBackgroundPrintable() const
			{
			    return _backgroundPrintable;
			}
    inline
    IlvPrintable*	getHeaderPrintable() const
			{
			    return _headerPrintable;
			}
    inline
    IlvPrintable*	getFooterPrintable() const
			{
			    return _footerPrintable;
			}
    inline
    IlvPrintable*	getForegroundPrintable() const
			{
			    return _foregroundPrintable;
			}
    inline void		setBackgroundPrintable(IlvPrintable* printable)
			{
			    _backgroundPrintable = printable;
			}
    inline void		setHeaderPrintable(IlvPrintable* printable)
			{
			    _headerPrintable = printable;
			}
    inline void		setFooterPrintable(IlvPrintable* printable)
			{
			    _footerPrintable = printable;
			}
    inline void		setForegroundPrintable(IlvPrintable* printable)
			{
			    _foregroundPrintable = printable;
			}

    // --------------------------------------------------------------------
    class ILVPRINTINGEXPORTED IlvPrintableAreaPtr
    {
    public:
	inline
	IlvPrintableAreaPtr(): _area(0) {}
	~IlvPrintableAreaPtr() { if (_area) delete _area; }

	IlvPrintableAreaPtr(IlvPrintableAreaPtr const& other)
	    : _area(other->clone())
	{}

	inline
	IlvPrintableAreaPtr& operator	=(IlvPrintableAreaPtr const& other)
					{
					    if (&other != this) {
						set(other->clone());
					    }
					    return *this;
					}
	inline
	IlvPrintableAreaPtr& operator	=(IlvPrintableArea* area)
					{
					    set(area);
					    return *this;
					}
	inline
	IlvPrintableArea& operator	*() const { return *_area; }
	inline
	IlvPrintableArea* operator	->() const { return _area; }

	inline operator			IlvPrintableArea*() const
					{
					    return _area;
					}


	inline void			set(IlvPrintableArea* area)
					{
					    if (_area) {
						delete _area;
					    }
					    _area = area;
					}


    private:
	IlvPrintableArea*		_area;
    };

    // --------------------------------------------------------------------
    class ILVPRINTINGEXPORTED IlvPrintablePtr
    {
    public:
	IlvPrintablePtr() : _printable(0) {}

	~IlvPrintablePtr();
	IlvPrintablePtr(IlvPrintablePtr const& other);

	inline
	IlvPrintablePtr& operator	=(IlvPrintablePtr const& other)
					{
					    set(other);
					    return *this;
					}

	IlvPrintablePtr& operator	=(IlvPrintable* printable)
					{
					    set(printable);
					    return *this;
					}

	inline IlvPrintable& operator	*() const { return *_printable; }
	inline IlvPrintable* operator	->() const { return _printable; }

	inline operator			IlvPrintable const*() const
					{
					    return _printable;
					}
	inline operator			IlvPrintable*() const
					{
					    return _printable;
					}

	void				set(IlvPrintable* printable);

    private:
	IlvPrintable*			_printable;
    };
    int			computePageNumber(IlvPrintableJob& job) const;

protected:
    virtual int		getPageNumber(IlvPrintableJob& job) const = 0;
    virtual void	initializeBackgroundArea(IlvPrintableJob& job)const=0;
    virtual void	initializeHeaderArea(IlvPrintableJob& job) const = 0;
    virtual void	initializeMainArea(IlvPrintableJob& job) const = 0;
    virtual void	initializeFooterArea(IlvPrintableJob& job) const = 0;
    virtual void	initializeForegroundArea(IlvPrintableJob& job)const=0;
    inline
    IlvPrintableArea&	getBackgroundArea() const { return *_backgroundArea; }
    inline
    IlvPrintableArea&	getHeaderArea() const { return *_headerArea; }
    inline
    IlvPrintableArea&	getMainArea() const { return *_mainArea; }
    inline
    IlvPrintableArea&	getFooterArea() const { return *_footerArea; }
    inline
    IlvPrintableArea&	getForegroundArea() const { return *_foregroundArea; }
    inline void		setBackgroundArea(IlvPrintableArea* area) const
			{
			    IL_ACCESSMUTABLE(IlvPrintableLayout,
					     _backgroundArea) = area;
			}
    inline void		setHeaderArea(IlvPrintableArea* area) const
			{
			    IL_ACCESSMUTABLE(IlvPrintableLayout,
					     _headerArea) = area;
			}
    inline void		setMainArea(IlvPrintableArea* area) const
			{
			    IL_ACCESSMUTABLE(IlvPrintableLayout,
					     _mainArea) = area;
			}
    inline void		setFooterArea(IlvPrintableArea* area) const
			{
			    IL_ACCESSMUTABLE(IlvPrintableLayout,
					     _footerArea) = area;
			}
    inline void		setForegroundArea(IlvPrintableArea* area) const
			{
			    IL_ACCESSMUTABLE(IlvPrintableLayout,
					     _foregroundArea) = area;
			}
    virtual void	updateBackgroundArea(IlvPrintableJob& job,
					     int pageIndex) const = 0;
    virtual void	updateHeaderArea(IlvPrintableJob& job,
					 int pageIndex) const = 0;
    virtual void	updateMainArea(IlvPrintableJob& job,
				       int pageIndex) const = 0;
    virtual void	updateFooterArea(IlvPrintableJob& job,
					 int pageIndex) const = 0;
    virtual void	updateForegroundArea(IlvPrintableJob& job,
					     int pageIndex) const = 0;

private:
    void		initializeAreas(IlvPrintableJob& job) const;
    void		resetAreas() const;
    IlBoolean		printAreas(IlvPrintableJob& job, int pageIndex) const;

    IlvDim				_leftMargin;
    IlvDim				_rightMargin;
    IlvDim				_topMargin;
    IlvDim				_bottomMargin;
    IlvDim				_gutterMargin;
    IlBoolean				_keepRatio;
    IlUInt				_refCount;
    IlvPrintablePtr			_backgroundPrintable;
    IlvPrintablePtr			_headerPrintable;
    IlvPrintablePtr			_footerPrintable;
    IlvPrintablePtr			_foregroundPrintable;
    IL_MUTABLE IlvPrintableAreaPtr	_backgroundArea;
    IL_MUTABLE IlvPrintableAreaPtr	_headerArea;
    IL_MUTABLE IlvPrintableAreaPtr	_mainArea;
    IL_MUTABLE IlvPrintableAreaPtr	_footerArea;
    IL_MUTABLE IlvPrintableAreaPtr	_foregroundArea;
};

#if defined(_MSC_VER) && defined(IL_DLL) && (_MSC_VER >= 1200)
#pragma warning( pop )
#endif /* _MSC_VER && IL_DLL && (_MSC_VER >= 1200) */

#endif /* __Ilv_Printing_Layout_H */
