// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/prevdisplayer.h
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
// Definition of the IlvPreviewDisplayer class.
// --------------------------------------------------------------------------

#ifndef __Ilv_Printing_PreviewDisplayer_H
#define __Ilv_Printing_PreviewDisplayer_H

#if !defined(__Ilv_Printing_Preview_H)
#include <ilviews/printing/preview.h>
#endif

#if !defined(__Ilv_Graphics_rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif

// --------------------------------------------------------------------------
//
// Forward declarations.
//
// --------------------------------------------------------------------------
class IlvContainer;

// --------------------------------------------------------------------------
//
// Class IlvPrinterPreviewDisplayer.
//
// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrinterPreviewDisplayer
{
public:
    enum Mode {
	OnePage,
	TwoPages,
	TiledPages
    };

    IlvPrinterPreviewDisplayer(IlvPrinterPreview&	printerPreview,
			       IlvContainer*		container);
    virtual ~IlvPrinterPreviewDisplayer();

    virtual void refresh() const = 0;
    virtual Mode getMode() const = 0;
    virtual IlBoolean isSameMode(Mode mode) const = 0;
    virtual IlInt getDisplayedPageNumber() const = 0;
    virtual IlvRect computeSize(IlInt		index,
				IlBoolean	redraw = IlTrue) const = 0;
    virtual void updateSizes() = 0;
    virtual void clean() = 0;

    static IlvPrinterPreviewDisplayer* Factory(Mode		  mode,
					       IlvPrinterPreview& preview,
					       IlvContainer*	  container);
    virtual IlBoolean isDisplayed(IlInt page) const = 0;
    IlvPrinterPreview& getPrinterPreview() const;
    IlvContainer* getContainer() const;
    IlInt getFirstDisplayedPage() const;
    void setFirstDisplayedPage(IlInt page);
    IlvRect const& getVisibleSize() const;
    void setVisibleSize(IlvRect const& newVisibleSize);
    void center();

    class GraphicalPage : public IlvFilledRectangle
    {
    public:
	GraphicalPage(IlvDisplay*		display,
		      IlvRect const&		drawRect,
		      IlvPrinterPreview&	printerPreview,
		      IlInt			page,
		      IlvPalette*		palette = 0);
	~GraphicalPage();
	virtual void draw(IlvPort*		dst,
			  IlvTransformer const*	t = 0,
			  IlvRegion const*	clip = 0) const;
	void setPage(IlInt page);

    private:
	void drawBackground(IlvPort*			dst,
			    IlvTransformer const*	t,
			    IlvRegion const*		clip) const;
	void drawMarges(IlvPort*		dst,
			IlvTransformer const*	t,
			IlvTransformer const&	actualTransformer,
			IlvRect const&		usableArea) const;

	IlvPrinterPreview&	_printerPreview;
	IlInt			_page;
	IlvPalette*		_margePalette;
    };

protected:
    IlInt getPageNumber() const;
    virtual void updatePages() = 0;

private:
    static void ContainerDeleteCB(IlvView* container, IlAny userArg);
    static void ContainerResizeCB(IlvView*	container,
				  IlvRect&	size,
				  IlAny		userArg);

    IlvPrinterPreview&	_printerPreview;
    IlvContainer*	_container;
    IlvRect		_visibleSize;
    IlInt		_firstDisplayedPage;
};

// --------------------------------------------------------------------------
//
// IlvPrinterPreviewDisplayer inlined member functions. 
//
// --------------------------------------------------------------------------
inline IlvPrinterPreview&
IlvPrinterPreviewDisplayer::getPrinterPreview() const
{
    return _printerPreview;
}

// --------------------------------------------------------------------------
inline IlvContainer*
IlvPrinterPreviewDisplayer::getContainer() const
{
    return _container;
}

// --------------------------------------------------------------------------
inline IlInt
IlvPrinterPreviewDisplayer::getFirstDisplayedPage() const
{
    return _firstDisplayedPage;
}

// --------------------------------------------------------------------------
inline void
IlvPrinterPreviewDisplayer::setFirstDisplayedPage(IlInt page)
{
    if (page != _firstDisplayedPage) {
	_firstDisplayedPage = page;
	updatePages();
    }
}

// --------------------------------------------------------------------------
inline IlvRect const&
IlvPrinterPreviewDisplayer::getVisibleSize() const
{
    return _visibleSize;
}

// --------------------------------------------------------------------------
inline void
IlvPrinterPreviewDisplayer::setVisibleSize(IlvRect const& newVisibleSize)
{
    if (_visibleSize != newVisibleSize) {
	_visibleSize = newVisibleSize;
	updateSizes();
    }
}

// --------------------------------------------------------------------------
inline IlInt
IlvPrinterPreviewDisplayer::getPageNumber() const
{
    return _printerPreview.getPageNumber();
}

// --------------------------------------------------------------------------
//
// IlvPrinterPreviewDisplayer::GraphicalPage inlined member functions. 
//
// --------------------------------------------------------------------------
inline
IlvPrinterPreviewDisplayer::GraphicalPage::GraphicalPage(
	IlvDisplay*		display,
	IlvRect const&		drawRect,
	IlvPrinterPreview&	printerPreview,
	IlInt			page,
	IlvPalette*		palette)
: IlvFilledRectangle(display,
		     drawRect,
		     (palette
		      ? palette
		      : display->getPalette(display->getColor("gray"),
					    display->getColor("white")))),
  _printerPreview(printerPreview),
  _page(page),
 _margePalette(display->getPalette(display->defaultBackground(),
				   display->getColor("lightgray")))
{
    _margePalette->lock();
}

// --------------------------------------------------------------------------
inline void
IlvPrinterPreviewDisplayer::GraphicalPage::setPage(IlInt page)
{
    _page = page;
}

#endif /* !__Ilv_Printing_PreviewDisplayer_H */
