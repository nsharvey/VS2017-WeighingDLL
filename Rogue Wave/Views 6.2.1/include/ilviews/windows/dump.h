// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/dump.h
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
// Declaration of the Windows dump device class
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Dump_H
#define __Ilv_Windows_Dump_H

#if !defined(__Ilv_Base_Port_H)
#include <ilviews/base/port.h>
#endif

#if !defined(STRICT)
#  define STRICT
#endif /* !STRICT */

#include <windows.h>
#include <commdlg.h>

class IlvWindowsPrinterDCFactory;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsVirtualDevice : public IlvSystemPort
{
public:
    IlvWindowsVirtualDevice(IlvDisplay*);
    ~IlvWindowsVirtualDevice();
    virtual IlBoolean	isADevice() const;
    // ____________________________________________________________
    // Specific
    HDC getHDC() const;
    void setHDC(HDC hdc);
    int getMapMode() const;
    void setMapMode(int mode);
    IlUInt getCompatibility() const;
    void setCompatibility(IlUInt version);

    IlBoolean getError() const;
    void setError(IlBoolean value);

    // ____________________________________________________________
    // Inherited
    virtual IlBoolean initDevice(const char*, IlvRect* = 0);
    virtual IlBoolean isBad() const;
    virtual void end();

    virtual void	fillRectangle(const IlvPalette* palette,
				      const IlvRect&    rect) const;

    virtual IlBoolean newPage() const;
    virtual void setTransformer(const IlvTransformer&);
    virtual void clip(const IlvRect*) const;
    virtual void clip(const IlvRegion*) const;
    void initClip(IlvRect const&);

protected:
    virtual IlvWindowsHandle	computeDC();
    virtual void		deleteDC();
    virtual void		initIlvDC();

    IlvRect			_initClip;
    IL_MUTABLE IlvRect		_currentClip;
    IL_MUTABLE IlvWindowsHandle	_windowsClip;
    int				_horzsize;
    int				_vertsize;
    IL_MUTABLE IlvTransformer*	_t;
    int				_mapMode;
    IlvRect			_initRect;
    IlUInt			_compatibility;
    IlBoolean			_error;
    RECT			_initDPRect;
    RECT			_initLPRect;

private:
    // Intentionally not defined.
    IlvWindowsVirtualDevice(IlvWindowsVirtualDevice const&);
    // Intentionally not defined.
    IlvWindowsVirtualDevice& operator=(IlvWindowsVirtualDevice const&);
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsDevice : public IlvWindowsVirtualDevice
{
public:
    IlvWindowsDevice(IlvDisplay*			display,
		     IlvWindowsPrinterDCFactory*	factory = 0);
    ~IlvWindowsDevice();
    // ____________________________________________________________
    IlvDim getPaperWidth() const;
    IlvDim getPaperHeight() const;
    char const* getDocName() const;
    void setDocName(const char* docName);
    char const* getOutputFile() const;
    void setOutputFile(const char* outputFileName);
    IlShort getOrientation() const;
    void setOrientation(IlShort orientation);
    IlvWindowsPrinterDCFactory* getPrinterDCFactory() const;
    void setPrinterDCFactory(IlvWindowsPrinterDCFactory* factory);

    // ____________________________________________________________
    virtual IlBoolean initDevice(const char* printer, IlvRect* clip = 0);
    virtual IlBoolean newPage() const;
    virtual void end();
    virtual void send(const char*) const;

    IlBoolean setNoDoc(IlBoolean flag);

protected:
    char*	_docName;
    char*	_outputFile;
    IlShort	_orientation;

private:
    // Intentionally not defined.
    IlvWindowsDevice(IlvWindowsDevice const&);
    // Intentionally not defined.
    IlvWindowsDevice& operator=(IlvWindowsDevice const&);

    IlBoolean createDCFromFactory();
    IlBoolean createDCFromDescription(char const* printer);

    IlvWindowsPrinterDCFactory* _printerDCFactory;

    IlBoolean	_noDoc;
    char*	_printerName;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsPrinterDCFactory
{
public:
    IlvWindowsPrinterDCFactory();
    virtual ~IlvWindowsPrinterDCFactory();
    virtual HDC getHDC() const = 0;
    virtual IlBoolean initializeSettings() = 0;
    virtual void resetSettings() = 0;
    virtual short getOrientation() const = 0;
    virtual void setOrientation(short newOrientation, IlvDisplay& display) = 0;
    virtual short getPaperSize() const = 0;
    virtual void setPaperSize(short paperSize, IlvDisplay& display) = 0;
    virtual short getPaperLength() const = 0;
    virtual void setPaperLength(short length, IlvDisplay& display) = 0;
    virtual short getPaperWidth() const = 0;
    virtual void setPaperWidth(short width, IlvDisplay& display) = 0;
    virtual IlBoolean getMinMaxPageRange(IlUShort& minPage,
					 IlUShort& maxPage) const = 0;
    virtual void setMinMaxPageRange(IlUShort minPage, IlUShort maxPage) = 0;
    virtual IlBoolean getFirstLastPages(IlUShort& firstPage,
					IlUShort& lastPage) const = 0;
    virtual void setFirstLastPages(IlUShort firstPage, IlUShort lastPage) = 0;
    IlBoolean isInitialized() const;
    void setInitialized() const;
    void unsetInitialized() const;
    virtual IlBoolean isVisible() const = 0;
    virtual void setVisibility(IlBoolean isVisible) = 0;
    virtual IlBoolean hasPageSettingDialog() const = 0;
    virtual void usePageSettingDialog(IlBoolean use) = 0;

private:
    // Intentionally not defined.
    IlvWindowsPrinterDCFactory(IlvWindowsPrinterDCFactory const&);
    // Intentionally not defined.
    IlvWindowsPrinterDCFactory& operator=(IlvWindowsPrinterDCFactory const&);

    IL_MUTABLE IlBoolean	_isInitialized;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvWindowsPrinterDCDialogFactory
: public IlvWindowsPrinterDCFactory
{
public:
    IlvWindowsPrinterDCDialogFactory();

    void setTransientView(IlvSystemView view);

    // Inherited functions.
    virtual ~IlvWindowsPrinterDCDialogFactory();

    virtual HDC getHDC() const;
    virtual IlBoolean initializeSettings();
    virtual void resetSettings();
    virtual short getOrientation() const;
    virtual void setOrientation(short newOrientation, IlvDisplay& display);
    virtual short getPaperSize() const;
    virtual void setPaperSize(short paperSize, IlvDisplay& display);
    virtual short getPaperLength() const;
    virtual void setPaperLength(short length, IlvDisplay& display);
    virtual short getPaperWidth() const;
    virtual void setPaperWidth(short width, IlvDisplay& display);
    virtual IlBoolean getMinMaxPageRange(IlUShort& min, IlUShort& max) const;
    virtual void setMinMaxPageRange(IlUShort minPage, IlUShort maxPage);
    virtual IlBoolean getFirstLastPages(IlUShort& first, IlUShort& last) const;
    virtual void setFirstLastPages(IlUShort first, IlUShort last);
    virtual IlBoolean isVisible() const;
    virtual void setVisibility(IlBoolean isVisible);
    virtual IlBoolean hasPageSettingDialog() const;
    virtual void usePageSettingDialog(IlBoolean use);

protected:
    PRINTDLG& getPrintDLG() const;

private:
    // Intentionally not defined.
    IlvWindowsPrinterDCDialogFactory(IlvWindowsPrinterDCDialogFactory const&);
    // Intentionally not defined.
    IlvWindowsPrinterDCDialogFactory&
    operator=(IlvWindowsPrinterDCDialogFactory const& other);

    IlvSystemView		_transientView;
    IlBoolean			_isVisible;
    IL_MUTABLE PRINTDLG		_printDLG;
    IL_MUTABLE short		_orientation;
    IL_MUTABLE short		_paperSize;
    IL_MUTABLE short		_paperLength;
    IL_MUTABLE short		_paperWidth;
};

ILVDSPEXPORTEDFUNCTION(char const*)
IlvGetWindowsPrinter(IlBoolean     dialog	= IlTrue,
		     IlBoolean     reInit	= IlFalse,
		     IlvSystemView transient	= 0);

// --------------------------------------------------------------------------
// Inline functions.
// --------------------------------------------------------------------------
inline HDC
IlvWindowsVirtualDevice::getHDC() const
{
    return IL_REINTERPRETCAST(HDC, getDC());
}

// --------------------------------------------------------------------------
inline void
IlvWindowsVirtualDevice::setHDC(HDC hdc)
{
    _dc = IL_REINTERPRETCAST(IlvWindowsHandle, hdc);
}

// --------------------------------------------------------------------------
inline int
IlvWindowsVirtualDevice::getMapMode() const
{
    return _mapMode;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsVirtualDevice::setMapMode(int mode)
{
    _mapMode = mode;
}

// --------------------------------------------------------------------------
inline IlUInt
IlvWindowsVirtualDevice::getCompatibility() const
{
    return _compatibility;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsVirtualDevice::setCompatibility(IlUInt version)
{
    _compatibility = version;
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvWindowsVirtualDevice::getError() const
{
    return _error;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsVirtualDevice::setError(IlBoolean value)
{
   _error = value;
}

// --------------------------------------------------------------------------
inline char const*
IlvWindowsDevice::getDocName() const
{
    return _docName;
}

// --------------------------------------------------------------------------
inline const char*
IlvWindowsDevice::getOutputFile() const
{
    return _outputFile;
}

// --------------------------------------------------------------------------
inline IlvWindowsPrinterDCFactory*
IlvWindowsDevice::getPrinterDCFactory() const
{
    return _printerDCFactory;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsDevice::setPrinterDCFactory(IlvWindowsPrinterDCFactory* factory)
{
    _printerDCFactory = factory;
}

// --------------------------------------------------------------------------
inline IlBoolean
IlvWindowsPrinterDCFactory::isInitialized() const
{
    return _isInitialized;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsPrinterDCFactory::setInitialized() const
{
    IL_ACCESSMUTABLE(IlvWindowsPrinterDCFactory, _isInitialized) = IlTrue;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsPrinterDCFactory::unsetInitialized() const
{
    IL_ACCESSMUTABLE(IlvWindowsPrinterDCFactory, _isInitialized) = IlFalse;
}

// --------------------------------------------------------------------------
inline void
IlvWindowsPrinterDCDialogFactory::setTransientView(IlvSystemView view)
{
    _transientView = view;
}

// --------------------------------------------------------------------------
inline PRINTDLG&
IlvWindowsPrinterDCDialogFactory::getPrintDLG() const
{
    return IL_ACCESSMUTABLE(IlvWindowsPrinterDCDialogFactory, _printDLG);
}

#endif /* !__Ilv_Windows_Dump_H */
