// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/printer.h
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
// Definition of IlvPrinter class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Printer_H
#define __Ilv_Printing_Printer_H

#if !defined(__Ilv_Printing_Macros_H)
#include <ilviews/printing/macros.h>
#endif

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif

// --------------------------------------------------------------------------
// Forward declarations.
class IlvPort;
class IlvPaperFormat;
class IlvDisplay;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrinter
{
public:
    enum Orientation {
	Uninitialized = 0,
	Portrait = 1,
	Landscape
    };
    IlvPrinter(IlvDisplay* display);
    virtual ~IlvPrinter();
    Orientation getOrientation() const;
    IlvPaperFormat const& getPaperFormat() const;
    virtual IlvRect getUsableArea() const = 0;
    void getMargins(IlvDim& left,
		    IlvDim& right,
		    IlvDim& top,
		    IlvDim& bottom) const;
    void setOrientation(Orientation orientation);
    void setPaperFormat(IlvPaperFormat const& format);
    void setMargins(IlvDim left,
		    IlvDim right,
		    IlvDim top,
		    IlvDim bottom);
    IlvPort* getPort() const;
    void setPort(IlvPort* port);
    virtual IlvPort* makePort() const = 0;
    IlvDisplay* getDisplay() const;
    IlString getDocumentName() const;
    void setDocumentName(IlString const& name);
    IlvRegion const* getClip() const;
    void setClip(IlvRegion const* newClip);
    void setClip(IlvRect const& newClip);
    IlvRect const* getInitClip() const;
    void initClip(IlvRect const& newClip);
    IlvTransformer const& getTransformer() const;
    void setTransformer(IlvTransformer const& newTransformer);
     IlBoolean isDumping() const;
    IlBoolean initialize();
    void end();
     virtual IlBoolean checkErrorStatus() const = 0;
    virtual IlvDim getPaperHeight() const = 0;
    virtual IlvDim getPaperWidth() const = 0;
    virtual IlvRect getPaperSize() const = 0;
    virtual IlBoolean initializeSettings() = 0;
    IlBoolean isDialogDisplayForced() const;
    void forceDialogDisplay(IlBoolean force);

protected:
    virtual IlBoolean internalInitialize() = 0;
    virtual void internalSetOrientation(Orientation orient) = 0;
    virtual void internalSetPaperFormat(IlvPaperFormat const& format) = 0;
    virtual void internalSetMargins(IlvDim left,
				    IlvDim right,
				    IlvDim top,
				    IlvDim bottom) = 0;
    virtual void internalSetClip(IlvRegion const* newClip) = 0;
    virtual void internalInitClip(IlvRect const& newClip) = 0;
    virtual void internalSetTransformer(IlvTransformer const& transformer) = 0;
     void setDumpingStatus(IlBoolean status);

private:
    IlBoolean isInitialized() const;
    void auxiliarySetClip(IlvRegion* region);

    IlvDisplay*			_display;
    Orientation			_orientation;
    IlvPaperFormat const*	_paperFormat;
    IlvDim			_leftMargin;
    IlvDim			_rightMargin;
    IlvDim			_topMargin;
    IlvDim			_bottomMargin;
    IL_MUTABLE IlvPort*		_port;
    IlString			_documentName;
    IlvRegion*			_clip;
    IlvRect*			_initClip;
    IlvTransformer		_transformer;
    IlBoolean			_isDumping;
    IlBoolean			_isInitialized;
    IlBoolean			_forceDialogDisplay;
};

// --------------------------------------------------------------------------
// Inlined functions.
// --------------------------------------------------------------------------
inline IlBoolean
IlvPrinter::isInitialized() const
{
    return _isInitialized;
}

// --------------------------------------------------------------------------
inline IlvPrinter::Orientation
IlvPrinter::getOrientation() const
{
    return _orientation;
}

// --------------------------------------------------------------------------
inline IlvPaperFormat const&
IlvPrinter::getPaperFormat() const
{
    return *_paperFormat;
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::getMargins(IlvDim& left,
		       IlvDim& right,
		       IlvDim& top,
		       IlvDim& bottom) const
{
    if (Landscape == getOrientation()) {
	top	= _leftMargin;
	bottom	= _rightMargin;
	left	= _topMargin;
	right	= _bottomMargin;
    } else {
	left	= _leftMargin;
	right	= _rightMargin;
	top	= _topMargin;
	bottom	= _bottomMargin;
    }
}

// --------------------------------------------------------------------------
inline IlvDisplay*
IlvPrinter::getDisplay() const
{
    return _display;
}

// --------------------------------------------------------------------------
inline IlString
IlvPrinter::getDocumentName() const
{
    return _documentName;
}

// --------------------------------------------------------------------------
inline IlvRegion const*
IlvPrinter::getClip() const
{
    return _clip;
}

// --------------------------------------------------------------------------
inline IlvRect const*
IlvPrinter::getInitClip() const
{
    return _initClip;
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvPrinter::isDumping() const
{
    return _isDumping;
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::auxiliarySetClip(IlvRegion* newClip)
{
    if (_clip) {
	delete _clip;
    }
    _clip = newClip;
    if (isInitialized()) {
	internalSetClip(_clip);
    }
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::setClip(IlvRegion const* newClip)
{
    auxiliarySetClip(newClip ? new IlvRegion(*newClip) : 0);
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::setClip(IlvRect const& newClip)
{
    auxiliarySetClip(new IlvRegion(newClip));
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::initClip(IlvRect const& newClip)
{
    if (_initClip) {
	delete _initClip;
    }
    _initClip = new IlvRect(newClip);
    if (isInitialized()) {
	internalInitClip(*_initClip);
    }
}

// --------------------------------------------------------------------------
inline IlvTransformer const&
IlvPrinter::getTransformer() const
{
    return _transformer;
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::setTransformer(IlvTransformer const& newTransformer)
{
    _transformer = newTransformer;
    if (isInitialized()) {
	internalSetTransformer(_transformer);
    }
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::setDumpingStatus(IlBoolean status)
{
    _isDumping = status;
}

// --------------------------------------------------------------------------
inline IlvPort*
IlvPrinter::getPort() const
{
    if (!_port) {
	IL_ACCESSMUTABLE(IlvPrinter, _port) = makePort();
    }
    return _port;
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::end()
{
    if (isDumping()) {
	setDumpingStatus(IlFalse);
	getPort()->end();
    }
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvPrinter::initialize()
{
    setDumpingStatus(IlTrue);
    IlBoolean result = internalInitialize();
    // _isInitialized is true when trying to modify the current settings.
    // Then, if result is false that means it was canceled.
    if (!result && !_isInitialized) {
	end();
    } else {
	_isInitialized = IlTrue;
    }
    return result;
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::setPort(IlvPort* port)
{
    if (_port)
	delete _port;
    _port = port;
}

// --------------------------------------------------------------------------
inline void   
IlvPrinter::setOrientation(Orientation orientation)
{
    if (_orientation != orientation) {
	_orientation = orientation;
	if (isInitialized()) {
	    internalSetOrientation(_orientation);
	}
    }
}

// --------------------------------------------------------------------------
inline void    
IlvPrinter::setPaperFormat(IlvPaperFormat const& format)
{
    _paperFormat = &format;
    if (isInitialized()) {
	internalSetPaperFormat(format);
    }
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvPrinter::isDialogDisplayForced() const
{
    return _forceDialogDisplay;
}

// --------------------------------------------------------------------------
inline void
IlvPrinter::forceDialogDisplay(IlBoolean force)
{
    _forceDialogDisplay = force;
}

#endif /* __Ilv_Printing_Printer_H */
