// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/fbrowser.h
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
// Declaration of the classes IlvFileBrowser
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Fbrowser_H
#define __Ilv_Gadgets_Fbrowser_H

#if !defined(__Ilv_Gadgets_Filechoo_H)
#include <ilviews/gadgets/filechoo.h>
#endif
#if !defined(__Ilv_Gadgets_Filesel_H)
#include <ilviews/gadgets/filesel.h>
#endif
#if !defined(__Ilv_Util_Dialogs_H)
#include <ilviews/util/dialogs.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#include <ilviews/gadgets/macrosadv.h>
#endif

class IlvBitmap;
class IlvFileSelectorField;

// --------------------------------------------------------------------------
enum IlvFileBrowserOption
{
    IlvNotSet   = -1,
    IlvUseDefault  = 0,
    IlvUseAlwaysSystemDialog,
    IlvUseAlwaysViewsDialog
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileBrowser
{
public:
    IlvFileBrowser(IlvDisplay*		display,
		   IlvSystemView	transientFor,
		   const char*		dir          = 0,
		   IlInt		nb	     = 0,
		   const char* const*	filters      = 0,
		   const char* const*	messages     = 0,
		   IlvFileBrowserOption useSystemDlg = IlvUseDefault);
    virtual ~IlvFileBrowser();
    // ____________________________________________________________
    virtual void	show();
    void		moveToView(IlvView*	view,
				   IlvDirection justification  = IlvCenter,
				   IlvPos	dx = 0,
				   IlvPos	dy = 0,
				   IlBoolean	ensureInScreen = IlTrue);
    void		moveToMouse(IlvDirection justification  = IlvCenter,
				    IlvPos	 dx = 0,
				    IlvPos	 dy = 0,
				    IlBoolean	 ensureInScreen = IlTrue);
    void		moveToScreen(IlvDirection justification  = IlvCenter,
				     IlvPos	  dx = 0,
				     IlvPos	  dy = 0,
				     IlBoolean	  ensureInScreen = IlTrue);
    void		ensureInScreen(IlvPos xMargin = 0, IlvPos yMargin = 0);
    inline const char*	get() { show(); return getPathName(); }
    IlInt		setPatterns(IlInt count,
				    const char* const* filters,
				    const char* const* messages);

    inline const char*	getFilter() const { return _filter; }
    void		setFilter(const char*);
    inline IlInt	getIndex() const { return _index; }
    inline void		setIndex(IlInt index)
			{
			    _index = index;
			    _patternsModified = IlTrue;
			}
    inline const char*	getTitle() const { return _title; }
    void		setTitle(const char* title);
    const char*		getDirectory() const;
    inline void		setDirectory(const char* dir) 
			{
			    _pathInit.setDirName(dir);
			}
    const char*		getFileName() const;
    inline void		setFileName(const char* filename)
			{
			    _pathInit.setFileName(filename);
			}
    const char*		getPathName() const;
    inline void		setPathName(const char* path) { _pathInit = path; }
    inline
    IlvFileSelectorType	getType() const	{ return _type;	}
    inline void		setType(IlvFileSelectorType t)	{ _type = t; }
    inline
    IlvFileBrowserOption getOption() const { return _option; }
    void		setOption(IlvFileBrowserOption option);
    void		setSortMode(IlPathName::SortMode mode);
    inline IlvDisplay*	getDisplay() const { return _display; }
    IlInt		getIndexFromFilter(const char* filter)  const;
    IlInt		getIndexFromMessage(const char* message) const;

    inline IlAny	getDialog() const	{ return _dialog;	}
    inline IlBoolean	useSystemDialog() const	{ return _useSystemDlg; }
    inline IlBoolean	needsInputContext() const
			{
			    return _needsInputContext;
			}
    void		setNeedsInputContext(IlBoolean);
    inline void		cleanDialogMember()	{ _dialog = 0;		}

    inline static void	SetInitOption(IlvFileBrowserOption option)
			{
			    _InitOption = option;
			}
    inline static
    IlvFileBrowserOption GetInitOption() { return _InitOption; }

protected:
    char*		computeString(IlList&,
				      IlInt,
				      IlBoolean = IlFalse) const;

    IlvDisplay*		_display;
    IlvSystemView	_transientView;
    char*		_result;
    int			_resultLength;
    IlAny		_dialog;
    IlvFileBrowserOption _option;
    IlBoolean		_useSystemDlg;
    IlInt		_index;
    IlBoolean		_patternsModified;
    char*		_title;
    IlBoolean		_titleModified;
    IlInt		_messagesLength;
    IlInt		_filtersLength;
    IlUInt		_count;
    char*		_filter;
    IlBoolean		_filterModified;
    IlBoolean		_noResult;
    IlvFileSelectorType _type;
    IlList		_messages;
    IlList		_filters;
    IlvPathName		_pathInit;
    IlvPathName		_pathResult;
    IlBoolean		_needsInputContext;

    static IlvFileBrowserOption	_InitOption;

private:
    enum IlvMoveToType {
	IlvMoveToNone,
	IlvMoveToView,
	IlvMoveToMouse,
	IlvMoveToScreen
    };
    IlvMoveToType	_moveToType;
    IlvView*		_refView;
    IlvDirection	_justification;
    IlvPos		_dx;
    IlvPos		_dy;
    IlBoolean		_ensureInScreen;
    IlPathName::SortMode _sortMode;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileSelectorFieldLFHandler
    : public IlvObjectLFHandler
{
public:
    IlvFileSelectorFieldLFHandler(IlvLookFeelHandler* lf);

    virtual void	drawSeparation(const IlvFileSelectorField*,
				       IlvPort*,
				       const IlvRegion*,
				       const IlvRect&,
				       IlvPalette*) const = 0;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvFileSelectorField : public IlvTextField
{
public:
    IlvFileSelectorField(IlvDisplay*	display,
			 const char*	label,
			 const IlvRect& rect,
			 IlUShort	thickness = IlvDefaultGadgetThickness,
			 IlvPalette*	palette   = 0);
    IlvFileSelectorField(IlvDisplay*	display,
			 const IlvPoint& at,
			 const char*	label,
			 IlUShort	thickness = IlvDefaultGadgetThickness,
			 IlvPalette*	palette   = 0);
    ~IlvFileSelectorField();

    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	getTextBBox(IlvRect& bbox) const;
    virtual void	selectFile();

    // Specific callbacks
    IlvDefineCallback(ButtonPressed);
    inline static
    IlSymbol*		ButtonPressedSymbol()
			{
			    return _buttonPressedSymbol;
			}
    static IlSymbol*	_buttonPressedSymbol;

    IlvDefineCallback(FileSelected);

    inline static
    IlSymbol*		FileSelectedSymbol()
			{
			    return _fileSelectedSymbol;
			}
    static IlSymbol*	_fileSelectedSymbol;

    // File browser
    inline
    IlvFileBrowser*	getBrowser() const { return _selector; }
    void		setBrowser(IlvFileBrowser* browser);
    inline
    IlvFileSelectorType	getBrowserType() { return _browserType; }
    void		setBrowserType(IlvFileSelectorType type);

    // Bitmap
    void		setBitmap(IlvBitmap*);
    IlvBitmap*		getBitmap()const;

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvFileSelectorField);

    void		buttonBBox(IlvRect&, const IlvTransformer*) const;

    static void		ButtonPressedCB(IlvGraphic*, IlAny arg);

protected:
    int			getButtonSize() const;

    IlvFileBrowser*	_selector;
    IlvFileSelectorType	_browserType;
    IlBoolean		_buttonInverted;
    IlvBitmap*		_bitmap;
    IlBoolean		_buttonVisible;

    virtual void	buttonPressed();
    virtual void	fileSelected();
    virtual IlvBitmap*	createBitmap()const;
};

ILVADVGDTMODULEINIT(filesel);
#if defined(ILVMOTIFLOOK)
#include <ilviews/gadgets/motif/filesel.h>
#endif
#if defined(ILVWINDOWSLOOK)
#include <ilviews/gadgets/windows/filesel.h>
#endif
#endif /* !__Ilv_Gadgets_Fbrowser_H */
