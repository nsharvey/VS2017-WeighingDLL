// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/print.h
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
// Declaration of the Printing classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Print_H)
#define __Ilv_Appframe_Print_H

#if !defined(__Ilv_Appframe_Dialog_Dialog_H)
#include <ilviews/appframe/dialog/dialog.h>
#endif

#if !defined(__Il_Pathname_H)
#include <ilog/pathname.h>
#endif

class IlvWindowsDevice;
class IlvPSDevice;
class ILVDVCLASS IlvDvPageSetupDialog;
class ILVDVCLASS IlvDvPostScriptDialog;
class ILVDVCLASS IlvDvApplication;
class ILVDVCLASS IlvDvPrintInfo;
class ILVDVCLASS IlvDvOptions;
class ILVDVCLASS IlvDvNodeValue;

// --------------------------------------------------------------------------
// IlvDvPrintedObjectInterface class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvPrintedObjectInterface
{
public:
    virtual ~IlvDvPrintedObjectInterface();
    virtual IlvTransformer*	getTransformer() const = 0;
    virtual IlvRect&		getVisibleRect(IlvRect&) const = 0;
    virtual IlvRect&		computeBBox(IlvRect&) const = 0;
    virtual IlvView*		getView() const;
    virtual void		print(IlvPort*, const IlvDvPrintInfo& pi) = 0;
    virtual void		dragDumpRect(IlvDvPageSetupDialog*) const = 0;
};

// --------------------------------------------------------------------------
// IlvDvActiveAppPrintedObject class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvActiveAppPrintedObject
: public IlvDvPrintedObjectInterface
{
public:
    IlvDvActiveAppPrintedObject(IlvDvApplication* app);

    virtual IlvTransformer*	getTransformer() const;
    virtual IlvRect&		getVisibleRect(IlvRect&) const;
    virtual IlvRect&		computeBBox(IlvRect&) const;
    virtual IlvView*		getView() const;
    virtual void		print(IlvPort*, const IlvDvPrintInfo& pi);
    virtual void		dragDumpRect(IlvDvPageSetupDialog*) const;

protected:
    IlvDvApplication*		_app;
};

// --------------------------------------------------------------------------
// IlvDvPrintInfo class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvPrintInfo
{
public:
    // ____________________________________________________________
    // Constructor / destructor
    IlvDvPrintInfo(const IlSymbol* name,
		   const IlvDvPrintedObjectInterface* obj,
		   IlvDim paperWidth = (IlvDim)0,
		   IlvDim paperHeight = (IlvDim)0);
    IlvDvPrintInfo(const IlvDvPrintInfo& src);
    virtual ~IlvDvPrintInfo();

    void		copy(const IlvDvPrintInfo& src);

    // ____________________________________________________________
    inline IlBoolean	isPortrait() const { return _portrait; }
    inline void		setPortrait(IlBoolean portrait)
			{
			    _portrait = portrait;
			}

    // ____________________________________________________________
    // Paper Info
    inline IlvDim	getPaperWidth() const { return _paperWidth; }
    inline IlvDim	getPaperHeight() const { return _paperHeight; }
    void		setPaperSize(IlvDim width, IlvDim height);

    inline IlvDim	getDefaultPaperWidth() const
			{
			    return _defaultPaperWidth;
			}
    inline IlvDim	getDefaultPaperHeight() const
			{
			    return _defaultPaperHeight;
			}
    void		setDefaultPaperSize(IlvDim width, IlvDim height);

    enum PaperFormat { Default = 0, A4, USLetter, USLegal, A3, B5 };
    inline void		setPaperFormat(PaperFormat fmt) { _paperFormat = fmt; }
    inline PaperFormat	getPaperFormat() const { return _paperFormat; }
    void		getPageSize(PaperFormat fmt, IlvDim& w, IlvDim& h);

    inline
    const IlvRect&	getDumpSelection() const
			{
			    return _dumpSelection;
			}
    inline void		setDumpSelection(const IlvRect& rect)
			{
			    _dumpSelection = rect;
			}

    inline
    const IlvRect&	getPageArea() const { return _pageArea; }
    inline void		setPageArea(const IlvRect& rect) { _pageArea = rect; }
    // ____________________________________________________________
    inline
    const IlvRect&	getDeviceClipRect() const
			{
			    return _deviceClipRect;
			}
    inline void		setDeviceClipRect(const IlvRect& rect)
			{
			    _deviceClipRect = rect;
			    /* psdevice->init(filename, &clip)) */
			}

    inline
    const IlvRect&	getSourceRect() const { return _sourceRect; }
    inline void		setSourceRect(const IlvRect& rect)
			{
			    _sourceRect = rect;
			}

    inline
    const IlvRect&	getSourceClipRect() const
			{
			    return _sourceClipRect;
			}
    inline void		setSourceClipRect(const IlvRect& rect)
			{
			    _sourceClipRect = rect;
			}

    inline
    IlvTransformer*	getSourceTransformer() const
			{
			    return _sourceTransformer;
			}
    void		setSourceTransformer(const IlvTransformer* t);

    inline
    IlvTransformer*	getDeviceTransformer() const
			{
			    return _deviceTransformer;
			}
    void		setDeviceTransformer(const IlvTransformer* t);

    const IlString&	getPrinterDescription() const;
    void		setPrinterDescription(const IlString&);

    enum DumpPartMode { Visible = 0, All = 1, Selection = 2 };
    void		setDumpPartMode(DumpPartMode mode,
					const IlvRect* = 0);
    inline DumpPartMode	getDumpPartMode() const { return _dumpPartMode; }

    enum ScalingMode {
	KeepAsIs = 0,
	WholePage = 1,
	PageArea = 2,
	FitToPages = 3
    };
    void		setScalingMode(ScalingMode mode,
				       const IlvRect* rect = 0);
    void		setFitPages(IlUInt wide = 1, IlUInt tall = 1);
    inline ScalingMode	getScalingMode() const { return _scalingMode; }

    IlUInt		getPagesCardinal() const;
    IlUInt		getSubPagesCardinal() const;

    inline IlUInt	getFitWidePages() const { return _fitWidePages; }
    inline IlUInt	getFitTallPages() const { return _fitTallPages; }


    void		set(IlBoolean portrait,
			    PaperFormat paperFormat = Default,
			    const IlvRect* margins = 0,
			    ScalingMode scalingMode = KeepAsIs,
			    const IlvRect* pageArea = 0,
			    DumpPartMode dumpPart = Visible,
			    const IlvRect* sourceRect = 0);
    // ----------------------------------------------------------------------

    void		initializeOnObject();
    void		initializeOnPage(IlUInt nPage, IlUInt nSubPage = 0);
    IlBoolean		initializeWindowsDevice(IlvWindowsDevice* wdv);
    // ----------------------------------------------------------------------
    inline void		setPrintedObject(const IlvDvPrintedObjectInterface* o)
			{
			    _obj = o;
			}
    inline
    const IlvDvPrintedObjectInterface*	getPrintedObject() const
					{
					    return _obj;
					}
    inline
    const IlvRect&	getMargins() const { return _margins; }
    inline void		setMargins(const IlvRect& margins)
			{
			    _margins = margins;
			}

    inline
    const IlSymbol*	getName() const { return _name; }
    inline void		setName(const IlSymbol* name) { _name = name; }

    inline void		setModified() { _modified = IlTrue; }

    inline IlUInt	getCurrentPage() const { return _currentPage; }
    inline void		setCurrentPage(IlUInt page) { _currentPage = page; }
    inline IlUInt	getCurrentSubPage() const { return _currentSubPage; }
    inline void		setCurrentSubPage(IlUInt page)
			{
			    _currentSubPage = page;
			}

    // ----------------------------------------------------------------------
    // Options managment
    virtual IlBoolean	readOptions(IlvDvOptions*);
    virtual IlBoolean	updateOptions(IlvDvOptions*);

protected:
    const IlSymbol*			_name;
    const IlvDvPrintedObjectInterface*	_obj;
    IlBoolean				_portrait;
    IlvRect				_pageArea;
    IlvRect				_dumpSelection;
    IlvRect				_deviceClipRect;
    IlvRect				_sourceRect;
    IlvRect				_sourceClipRect;
    IlvTransformer*			_sourceTransformer;
    IlvTransformer*			_deviceTransformer;
    IlvDim				_paperWidth;
    IlvDim				_paperHeight;
    IlvDim				_defaultPaperWidth;
    IlvDim				_defaultPaperHeight;
    IlString				_printerDescription;
    IlvRect				_margins;
    DumpPartMode			_dumpPartMode;
    ScalingMode				_scalingMode;
    PaperFormat				_paperFormat;
    IlUInt				_fitWidePages;
    IlUInt				_fitTallPages;

    // Internal parameters
    IlBoolean				_modified;
    IlUInt				_currentPage;
    IlUInt				_currentSubPage;
    IlAny				_patch;
    IlvRect				_screenSourceRect;

    virtual IlBoolean	readFromNode(IlvDvNodeValue*);
    virtual IlBoolean	updateNodeValue(IlvDvNodeValue*);

    void		computeSourceRect(IlvRect&) const;
    void		moveSourceTransformer(IlvPos, IlvPos);
};

// --------------------------------------------------------------------------
// IlvDvPSPrintInfo class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvPSPrintInfo : public IlvDvPrintInfo
{
public:
    // ____________________________________________________________
    // Constructor / destructor
    IlvDvPSPrintInfo(const IlSymbol* name,
		     const IlvDvPrintedObjectInterface* obj,
		     IlvDim paperWidth = (IlvDim)0,
		     IlvDim paperHeight = (IlvDim)0);
    IlvDvPSPrintInfo(const IlvDvPrintInfo& src);

    // ____________________________________________________________
    IlBoolean		initializePSDevice(IlvPSDevice*);

    // ____________________________________________________________
    inline IlBoolean	useColor() const { return _useColor; }
    inline void		setUseColor(IlBoolean color) { _useColor = color; }

protected:
    IlBoolean		_useColor;

    // ----------------------------------------------------------------------
    // Options managment
    virtual IlBoolean	readFromNode(IlvDvNodeValue*);
    virtual IlBoolean	updateNodeValue(IlvDvNodeValue*);
};

// --------------------------------------------------------------------------
// IlvDvPrintManager class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvPrintManager
{
public:
    // ____________________________________________________________
    // Constructor / destructor
    IlvDvPrintManager(IlvDvApplication* app);
    virtual ~IlvDvPrintManager();

    // ____________________________________________________________
    void		print(IlBoolean forceDialog = IlTrue);
    IlBoolean		printerSetup();
    IlBoolean		pageSetup();
    IlBoolean		editPageSettings(IlvDvPrintInfo*);
    void		printPostScript(IlBoolean forceDialog = IlTrue);

    void		setPrintedObject(IlvDvPrintedObjectInterface* obj,
					 IlBoolean canDelete = IlFalse);
    const IlvDvPrintedObjectInterface*	getPrintedObject() const;

    // ____________________________________________________________
    // Options managment
    void		readOptions(IlvDvOptions*);
    void		updateOptions(IlvDvOptions*);

    // ____________________________________________________________
    // Statics
    static IlSymbol*		_OptionsPrinterInfoClass;
    static IlSymbol*		_OptionsDefaultPrinterInfoName;
    static IlSymbol*		_OptionsPosctScriptPrinterInfoName;

protected:
    IlvDvApplication*		_app;
    IlvDvPrintedObjectInterface* _printedObject;
    IlBoolean			_deletePrintedObject;
    IlvDvPrintInfo*		_printInfo;
    IlvDvPSPrintInfo*		_psPrintInfo;
    IlAny			_patch;

    IlvDvPageSetupDialog*	_pageSetupDialog;
    IlvDvPostScriptDialog*	_postScriptDialog;

    IlBoolean		savePostScript(IlBoolean lpr = IlFalse);

private:
    IlvDvPrintInfo*	ensurePrintInfo(IlBoolean ensurePrinter);
    IlvDvPSPrintInfo*	ensurePSPrintInfo(IlBoolean forceDialog);
};

// --------------------------------------------------------------------------
// IlvDvPageSetupDialog class
// --------------------------------------------------------------------------
class IlvPSDevice;
class IlvTextField;
class IlvToggle;

class ILVDVCLASS IlvDvPageSetupDialog : public IlvDvDialog
{
public:
    // ____________________________________________________________
    // Constructor / destructor
    IlvDvPageSetupDialog(IlvDvApplication* application);
    virtual ~IlvDvPageSetupDialog();

    // ____________________________________________________________
    virtual void	apply();
    virtual void	reset();

    void		edit(IlvDvPrintInfo* printInfo);
    IlvView*		getView()    const;

    void		setFilename(const char*);
    IlBoolean		pageRect(IlvRect& rect);
    IlBoolean		sourceRect(IlvRect& rect);
    void		dragDumpRect();
    void		endDraggumpRect(const IlvRect&);
    void		refreshDumpRectDragged(const IlvRect&);
    void		updateDumpArea();

    // ____________________________________________________________
    // Accessors
    IlvTextField*	getTextField(const char*) const;
    IlvToggle*		getToggle(const char*) const;
    void		setValue(const char*, IlInt,
				 IlBoolean redraw = IlTrue);
    int			getIntValue(const char*) const;
    void		setActive(const char* name, IlBoolean active);
    IlUShort		whichSelected(const char*) const;
    IlBoolean		setSelected(const char*, IlUShort);

private:
    IlvDvApplication*	_app;
    IlvDvPrintInfo*	_printInfo;
    IlvRect		_pageArea;
    IlAny		_patch;

    void		getMargins(IlvRect&) const;
    IlBoolean		ensureRectInPage(IlvRect&) const;
    void		setGraphicCallback(const char*,
					   IlvGraphicCallback cb);
    void		resetCB();

public:
    // Callbacks
    static void		DragRectCB(IlvGraphic* g, IlAny);
    static void		ScalingCB(IlvGraphic* g, IlAny);
    static void		WhatCB(IlvGraphic* g, IlAny);
    static void		UpdateScalingFieldsCB(IlvGraphic* g, IlAny);
    static void		PageAreaChangedCB(IlvGraphic* g, IlAny);
    static void		ResetCB(IlvGraphic* g, IlAny);
    void		updateScalingFields();
    void		whatFieldState(IlBoolean state);
    void		fillPageFields(IlBoolean redraw = IlTrue);
};

// --------------------------------------------------------------------------
// IlvDvPostScriptDialog class
// --------------------------------------------------------------------------

class ILVDVCLASS IlvDvPostScriptDialog : public IlvDvDialog
{
public:
    // ____________________________________________________________
    // Constructor / destructor
    IlvDvPostScriptDialog(IlvDvApplication* app,
			  IlvDvPrintManager* mger);

    // ____________________________________________________________
    virtual void	apply();
    virtual void	reset();
    IlBoolean		editPostScriptInfo(IlvDvPSPrintInfo* psInfo);

    void		updateApplyButton();
    void		editPageSetup();

protected:
    IlvDvApplication*	_app;
    IlvDvPrintManager*	_printManager;
    IlvDvPSPrintInfo*	_psInfo;
    IlPathName		_defaultDirectory;
    IlAny		_patch;

public:
    static void		OptionsCB(IlvGraphic* g, IlAny);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(print);
// --------------------------------------------------------------------------
#endif /* ! __Ilv_Appframe_Print_H */
