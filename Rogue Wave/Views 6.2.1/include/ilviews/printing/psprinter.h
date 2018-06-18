// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/psprinter.h
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
// Definition of IlvPSPrinter class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_PSPrinter_H
#define __Ilv_Printing_PSPrinter_H

#if !defined(__Ilv_Printing_Printer_H)
#include <ilviews/printing/printer.h>
#endif

class IlvPSDevice;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPSPrinter : public IlvPrinter
{
public:
    class ILVPRINTINGEXPORTED DialogHandle {
    public:
	class ILVPRINTINGEXPORTED Factory {
	public:
	    virtual ~Factory();
	    virtual DialogHandle* get(IlvDisplay* display) const = 0;
	};
	virtual ~DialogHandle();
	virtual void setPaperFormat(IlString const& format) = 0;
	virtual IlvPaperFormat const& getPaperFormat() const = 0;
	virtual void setOrientation(IlvPrinter::Orientation orientation) = 0;
	virtual IlvPrinter::Orientation getOrientation() const = 0;
	virtual void setColorMode(IlBoolean useColor) = 0;
	virtual IlBoolean isColorModeOn() const = 0;
	virtual void setCollate(IlBoolean collate) = 0;
	virtual IlBoolean isCollateOn() const = 0;
	virtual void setCopiesNumber(IlUInt copies) = 0;
	virtual IlUInt getCopiesNumber() const = 0;
	virtual void getMargins(IlvDim& left,
				IlvDim& right, 
				IlvDim& top,
				IlvDim& bottom) const = 0;
	virtual void setFilename(IlString const& name) = 0;
	virtual IlString getFilename() const = 0;
	virtual IlBoolean get() = 0;
	static void SetFactory(Factory* factory);
	static Factory* GetFactory();

    private:
	static Factory* _Factory;
    };
    IlvPSPrinter(IlvDisplay* display);
   ~IlvPSPrinter();
    virtual IlvRect getUsableArea() const;
    IlvPort* makePort() const;
     virtual IlBoolean checkErrorStatus() const;
    virtual IlvDim getPaperHeight() const;
    virtual IlvDim getPaperWidth() const;
    virtual IlvRect getPaperSize() const;
    virtual IlBoolean initializeSettings();
    static IlvDim DefaultMargin;
    void setDialogHandle(DialogHandle* dialogHandle, IlBoolean owner = IlTrue);
    DialogHandle* getDialogHandle(IlvDisplay* display) const;

protected:
    virtual IlBoolean internalInitialize();
    virtual void internalSetOrientation(Orientation orient);
    virtual void internalSetPaperFormat(IlvPaperFormat const& format);
    virtual void internalSetMargins(IlvDim left,
				    IlvDim right,
				    IlvDim top,
				    IlvDim bottom);
    virtual void internalSetClip(IlvRegion const* newClip);
    virtual void internalInitClip(IlvRect const& newClip);
    virtual void internalSetTransformer(IlvTransformer const& transformer);

private:
    IL_MUTABLE DialogHandle*	_dialogHandle;
    IlBoolean			_owner;
};

// --------------------------------------------------------------------------
//
// Inlined functions.
//
// --------------------------------------------------------------------------
inline void
IlvPSPrinter::DialogHandle::SetFactory(
	IlvPSPrinter::DialogHandle::Factory* factory)
{
    _Factory = factory;
}

// --------------------------------------------------------------------------
inline IlvPSPrinter::DialogHandle::Factory*
IlvPSPrinter::DialogHandle::GetFactory()
{
    return _Factory;
}

// --------------------------------------------------------------------------
inline void
IlvPSPrinter::setDialogHandle(IlvPSPrinter::DialogHandle* dialogHandle,
			      IlBoolean			 owner)
{
    if (_dialogHandle != dialogHandle) {
	if (_owner) {
	    delete _dialogHandle;
	}
    }
    _dialogHandle = dialogHandle;
    _owner = owner;
}

// --------------------------------------------------------------------------
inline IlvPSPrinter::DialogHandle*
IlvPSPrinter::getDialogHandle(IlvDisplay* display) const
{
    if (!_dialogHandle && DialogHandle::GetFactory()) {
	IL_ACCESSMUTABLE(IlvPSPrinter, _dialogHandle) =
	    DialogHandle::GetFactory()->get(display);
    }
    return _dialogHandle;
}

#endif /* __Ilv_Printing_PSPrinter_H */
