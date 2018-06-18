// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/util/dialogs.h
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
// Definition of the various dialog-related class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Ilv_Util_Dialogs_H
#define __Ilv_Util_Dialogs_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_View_H)
// To get correct IlvSystemView definition.
#  include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Util_Fseltype_H)
#  include <ilviews/util/fseltype.h>
#endif

#if defined(WINDOWS)
#  include <windows.h>
#  include <commdlg.h>
#  if defined(_MSC_VER) && (_MSC_VER >= 1300) /* msvc7 */
#    if defined(IL_STD)
#      include <cstddef>
#    else  /* !IL_STD */
#      include <stddef.h>
#    endif /* !IL_STD */
#  endif /* >= msvc7 */
#endif /* WINDOWS */

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPromptDialog
{
public:
    IlvPromptDialog(IlvSystemView parent,
		    const char*   message,
		    IlUInt        count   = 0,
		    const char**  strings = 0);
    ~IlvPromptDialog();
    // ____________________________________________________________
    void		setTitle(const char* title);
    const char*		show();
    const char*		show(IlvPos x, IlvPos y);
    void		hide();
    void		setString(const char* string);
    void		setStrings(IlUInt count, const char** strings);
#if defined(WINDOWS)
    inline IlUInt	getCount()   { return _count; }
    inline const char**	getStrings() { return (const char**)_strings; }
    inline char*	getString()  { return _returned; }
    void		updateTitleAndPosition(HWND);
#endif /* WINDOWS */
private:
    IlvSystemView	_parent;
#if defined(WINDOWS)
    HANDLE		_mem;
#if defined(_MSC_VER) && (_MSC_VER >= 1300) /* msvc7 */
    ptrdiff_t		_heightoffset;
    ptrdiff_t		_styleoffset;
    ptrdiff_t		_classoffset;
#else  /* < msvc7 */
    long		_heightoffset;
    long		_styleoffset;
    long		_classoffset;
#endif /* < msvc7 */
    char*		_title;
    IlBoolean		_moved;
    IlvPos		_x, _y;
    IlUInt		_count;
    char**		_strings;
    char*		_returned;
#endif /* WINDOWS */
#if defined(X11)
    IlvSystemView	_widget;
#endif /* X11 */
};

// --------------------------------------------------------------------------
class IlvInformationDialog;

typedef void (* IlvDialogCallback)(IlvInformationDialog* dialog,
				   IlBoolean             result,
				   IlAny                 userArg);

typedef enum IlvDialogStyle {
    IlvDialogStyleQuestion,
    IlvDialogStyleInformation,
    IlvDialogStyleWarning
} _IlvDialogStyle;

class ILVDSPEXPORTED IlvInformationDialog
{
public:
    IlvInformationDialog(IlvSystemView     parent,
			 const char*       message,
			 IlvDialogStyle    style   = IlvDialogStyleInformation,
			 IlvDialogCallback ok      = 0,
			 IlvDialogCallback cancel  = 0,
			 IlAny             userArg = 0);
    ~IlvInformationDialog();
    // ____________________________________________________________
    void		setTitle(const char* title);
    inline void		callOk()
			{
			    if (_okcallback)
				_okcallback(this, IlTrue, _userarg);
			}
    inline void		callCancel()
			{
			    if (_cancelcallback)
				_cancelcallback(this, IlFalse, _userarg);
			}
    void		show(IlBoolean blocking = IlTrue);
    void		show(IlvPos x, IlvPos y, IlBoolean blocking = IlTrue);
    void		hide();

private:
    IlvSystemView	_parent;
    IlvDialogCallback	_okcallback;
    IlvDialogCallback	_cancelcallback;
    IlAny		_userarg;
    IlvDialogStyle	_style;
#if defined(WINDOWS)
    char*		_message;
    char*		_title;
#endif /* WINDOWS */
#if defined(X11)
    IlvSystemView	_widget;
#endif /* X11 */
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvQuestionDialog
{
public:
    IlvQuestionDialog(IlvSystemView parent, const char* message);
    ~IlvQuestionDialog();
    // ____________________________________________________________
    void		setTitle(const char* title);
    IlBoolean		show();
    IlBoolean		show(IlvPos x, IlvPos y);
    void		hide();

private:
    IlvSystemView	_parent;
#if defined(WINDOWS)
    char*		_message;
    char*		_title;
#endif /* WINDOWS */
#if defined(X11)
    IlvSystemView	_widget;
#endif /* X11 */
};

// --------------------------------------------------------------------------
#if defined(WINDOWS)
class ILVDSPEXPORTED IlvWindowsDialogWrapper
{
public:
    IlvWindowsDialogWrapper(IlvSystemView parent,
			    char const*   initialValue = 0);
    virtual ~IlvWindowsDialogWrapper();

    void		setInitialValue(char const* initialValue);
    virtual void	setTitle(char const* title) = 0;

    virtual const char* show(const char* initialValue = 0) = 0;
    virtual const char* show(IlvPos	 x,
			     IlvPos	 y,
			     const char* initialValue = 0) = 0;
    virtual const char* showToView(const IlvView* view,
				   IlvDirection	  justification  = IlvCenter,
				   IlvPos	  dx = 0,
				   IlvPos	  dy = 0,
				   IlBoolean	  ensureInScreen = IlTrue,
				   const char*	  initialValue = 0) = 0;
    virtual const char* showToMouse(IlvDisplay*	  display,
				    IlvDirection  justification  = IlvCenter,
				    IlvPos	  dx = 0,
				    IlvPos	  dy = 0,
				    IlBoolean	  ensureInScreen = IlTrue,
				    const char*	  initialValue = 0) = 0;
    virtual const char* showToScreen(IlvDisplay*  display,
				     IlvDirection justification  = IlvCenter,
				     IlvPos	  dx = 0,
				     IlvPos	  dy = 0,
				     IlBoolean	  ensureInScreen = IlTrue,
				     const char*  initialValue = 0) = 0;

protected:
    IlvSystemView	_parent;
    char*		_initialValue;
};
#endif /* WINDOWS */

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFileSelector
{
public:
    IlvFileSelector(IlvSystemView	parent,
		    const char*		message,
		    const char*		directory = 0,
		    const char*		pattern   = 0);
    ~IlvFileSelector();
    // ____________________________________________________________
    void		setType(IlvFileSelectorType type);
    void		setTitle(const char* title);
    void		setMessage(const char* message);
    const char*		show(const char* directory = 0,
			     const char* pattern   = 0);
    const char*		show(IlvPos	 x,
			     IlvPos	 y,
			     const char* directory = 0,
			     const char* pattern   = 0);
    const char*		showToView(const IlvView* view,
				   IlvDirection   justification    = IlvCenter,
				   IlvPos         dx = 0,
				   IlvPos         dy = 0,
				   IlBoolean      ensureInScreen   = IlTrue,
				   const char*    initialDirectory = 0,
				   const char*    filePattern      = 0);
    const char*		showToMouse(IlvDisplay*  display,
				    IlvDirection justification    = IlvCenter,
				    IlvPos       dx = 0,
				    IlvPos       dy = 0,
				    IlBoolean    ensureInScreen   = IlTrue,
				    const char*  initialDirectory = 0,
				    const char*  filePattern      = 0);
    const char*		showToScreen(IlvDisplay*  display,
				     IlvDirection justification    = IlvCenter,
				     IlvPos       dx = 0,
				     IlvPos       dy = 0,
				     IlBoolean    ensureInScreen   = IlTrue,
				     const char*  initialDirectory = 0,
				     const char*  filePattern      = 0);
    void		hide();
    void		setFilter(const char* filter);
    void		setInitValue(const char* fileName);
#if defined(WINDOWS)
    void		setCustFilter(const char* const*);
    void		setIndex(IlUInt);
    void		setPattern(const char*);
    void		setWindowsPattern(const char*); // Must end with 2 \0 !
    OPENFILENAME&	getOFNStruc();
#else  /* !WINDOWS */
    inline void		setCustFilter(const char* const* f)
			{
			    setFilter(f ? *f : 0);
			}
#endif /* !WINDOWS */
    static IlBoolean	IsImplemented();

private:
#if defined(WINDOWS)
    IlvWindowsDialogWrapper*	_internal;
    int			_internalType;
#else  /* !WINDOWS */
    IlvSystemView	_parent;
    IlvFileSelectorType	_type;
    char*		_initValue;
    IlvSystemView	_widget;
#endif /* !WINDOWS */
};

#if !defined(WINDOWS)
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvPromptStringsDialog
{
public:
    IlvPromptStringsDialog(IlvSystemView parent,
			   const char*   message);
    ~IlvPromptStringsDialog();
    // ____________________________________________________________
    void		setTitle(const char* title);
    void		show();
    void		show(IlvPos x, IlvPos y);
    void		hide();
    const char**	strings(IlUInt& n);
private:
    IlvSystemView	_parent;
#if defined(X11)
    IlvSystemView	_widget;
    IlvSystemView	_shell;
#endif /* X11 */
};
#endif /* !WINDOWS */

// --------------------------------------------------------------------------
#if defined(WINDOWS)
class ILVDSPEXPORTED IlvPromptFontDialog
{
public:
    IlvPromptFontDialog(IlvSystemView parent,
			const char*   title = 0);
    ~IlvPromptFontDialog();
    // ____________________________________________________________
    void		setTitle(const char* title);
    IlvFont*		show();
    IlvFont*		show(IlvPos x, IlvPos y);
    IlvFont*		showToView(const IlvView* view,
				   IlvDirection	  justification  = IlvCenter,
				   IlvPos         dx = 0,
				   IlvPos         dy = 0,
				   IlBoolean	  ensureInScreen = IlTrue);
    IlvFont*		showToMouse(IlvDisplay*	 display,
				    IlvDirection justification  = IlvCenter,
				    IlvPos       dx = 0,
				    IlvPos       dy = 0,
				    IlBoolean    ensureInScreen = IlTrue);
    IlvFont*		showToScreen(IlvDisplay*  display,
				     IlvDirection justification  = IlvCenter,
				     IlvPos	  dx = 0,
				     IlvPos       dy = 0,
				     IlBoolean	  ensureInScreen = IlTrue);
    void		hide();

private:
    IlvSystemView	_parent;
    char*		_title;
    CHOOSEFONT		_chf;
    LOGFONT		_lf;
};

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFileSelectorWrapper : public IlvWindowsDialogWrapper
{
public:
    IlvFileSelectorWrapper(IlvSystemView parent,
			   char const*	 message,
			   char const*	 dir  = 0,
			   char const*	 pat  = 0);
    ~IlvFileSelectorWrapper();
    virtual void	setTitle(char const* title);
    virtual const char* show(const char* initialValue = 0);
    virtual const char* show(IlvPos	 x,
			     IlvPos	 y,
			     const char* initialValue = 0);
    virtual const char* showToView(const IlvView* view,
				   IlvDirection	  justification  = IlvCenter,
				   IlvPos	  dx = 0,
				   IlvPos	  dy = 0,
				   IlBoolean	  ensureInScreen = IlTrue,
				   const char*	  initialValue = 0);
    virtual const char* showToMouse(IlvDisplay*	  display,
				    IlvDirection  justification  = IlvCenter,
				    IlvPos	  dx = 0,
				    IlvPos	  dy = 0,
				    IlBoolean	  ensureInScreen = IlTrue,
				    const char*	  initialValue = 0);
    virtual const char* showToScreen(IlvDisplay*  display,
				     IlvDirection justification  = IlvCenter,
				     IlvPos	  dx = 0,
				     IlvPos	  dy = 0,
				     IlBoolean	  ensureInScreen = IlTrue,
				     const char*  initialValue = 0);
    void		setType(IlvFileSelectorType type);
    void		setMessage(char const* message);
    void		setFilePattern(char const* filePattern);
    void		setFilter(char const* filter);
    void		setCustFilter(const char* const*);
    void		setIndex(IlUInt);
    void		setPattern(const char*);
    void		setWindowsPattern(const char*); // Must end with 2 \0 !
    OPENFILENAME&	getOFNStruc() { return _ofn; }

private:
    IlvFileSelectorType	_type;
    IlUInt		_index;
    char*		_message;
    char*		_fileTitle;
    IlUInt		_fileTitleSize;
    char*		_custFilter;
    char*		_filter;
    char		_dirName[512];
    char		_file[512];
    OPENFILENAME	_ofn;
};

#if !defined(__BORLANDC__)
#include <shlobj.h>
// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFolderBrowserWrapper : public IlvWindowsDialogWrapper
{
public:
    enum FolderType {
	Directory = 0,
	Computer,
	Printer
    };

    IlvFolderBrowserWrapper(IlvSystemView	parent,
			    char const*		initialFolder = 0,
			    char const*		title = 0,
			    FolderType		type = Directory);
    ~IlvFolderBrowserWrapper();

    inline FolderType	getType() const { return _type; }
    void		setType(FolderType type);
    virtual void	setTitle(char const* title);
    virtual char const* show(char const* initialFolder = 0);
    virtual char const* show(IlvPos	 x,
			     IlvPos	 y,
			     char const* initialFolder = 0);
    virtual char const* showToView(IlvView const* view,
				   IlvDirection	  justification  = IlvCenter,
				   IlvPos	  dx = 0,
				   IlvPos	  dy = 0,
				   IlBoolean	  ensureInScreen = IlTrue,
				   char const*	  initialFolder = 0);
    virtual char const* showToMouse(IlvDisplay*	  display,
				    IlvDirection  justification  = IlvCenter,
				    IlvPos	  dx = 0,
				    IlvPos	  dy = 0,
				    IlBoolean	  ensureInScreen = IlTrue,
				    char const*	  initialFolder = 0);
    virtual char const* showToScreen(IlvDisplay*  display,
				     IlvDirection justification  = IlvCenter,
				     IlvPos	  dx = 0,
				     IlvPos	  dy = 0,
				     IlBoolean	  ensureInScreen = IlTrue,
				     char const*  initialFolder = 0);

protected:
    char*		_title;
    FolderType		_type;
    char		_buffer[MAX_PATH];
    BROWSEINFO		_bif;
};
#endif /* !__BORLANDC__ */
#endif /* WINDOWS */

#endif /* !__Ilv_Util_Dialogs_H */
