// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/filelst.h
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
// Declaration of IlvDvRecentFileList
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Filelst_H)
#define __Ilv_Appframe_Filelst_H

#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif
#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#include <ilviews/gadgets/macros.h>
#endif

class IlvAbstractMenu;
class IlvDvApplication;
class IlvMenuItem;
class IlvDvOptions;

// --------------------------------------------------------------------------
// IlvDvCommandListMenu class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvCommandListMenu
{
public:
    typedef IlBoolean (* ActivateMenuItemCallback)(IlAny, IlAny);
    // ____________________________________________________________
    // Constructor / destructor
    IlvDvCommandListMenu(int size,
			 const char* emptyMessage,
			 IlvDvApplication* application,
			 const IlSymbol* cmdName,
			 ActivateMenuItemCallback callback,
			 IlAny callbackParam = 0,
			 IlUInt start = 1);
    virtual ~IlvDvCommandListMenu();

    // ----------------------------------------------------------------------
    virtual void	updateMenu(IlvAbstractMenu* menu) const;

    // ----------------------------------------------------------------------
    // Basic properties
    inline
    const IlSymbol*	getCommandName() const { return _cmdName; }
    inline void		setCommandName(const IlSymbol* name)
			{
			    _cmdName = name;
			}
    inline void		setDvApplication(IlvDvApplication* app)
			{
			    _application = app;
			}
    inline
    IlvDvApplication*	getDvApplication() const
			{
			    return _application;
			}
    virtual IlUInt	getCardinal() const = 0;

protected:
    int			_size;
    IlvDvApplication*	_application;
    IlvString		_strEmptyMessage; // string drawn when no files in the list
    const IlSymbol*	_cmdName;
    IlUInt		_start;              // for displaying
    ActivateMenuItemCallback _callback;
    IlAny		_callbackParam;

    virtual
    IlvMenuItem*	createMenuItem(IlvDisplay*, IlUInt nItem) const;
    virtual IlUShort	cleanMenu(IlvAbstractMenu*& menu,
				  IlvMenuItem* menuItem) const;
    virtual IlBoolean	itemActivated(IlAny item, IlAny data) const;

    // Overridables
    virtual IlAny	getClientItemData(IlUInt nItem) const = 0;
    virtual const char*	getItemString(IlUInt nItem, IlvString&) const = 0;
    virtual void	removeItem(IlAny);

public:
    static void		MenuItemCallback(IlvGraphic* g, IlAny param);
};


// --------------------------------------------------------------------------
// IlvDvRecentFileList class
// --------------------------------------------------------------------------
#define ILVDV_ABBREV_FILENAME_LEN 30
class ILVDVCLASS IlvDvRecentFileList : public IlvDvCommandListMenu
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvRecentFileList(ActivateMenuItemCallback callback,
			IlAny recentFileCallbackData = 0,
			int size = 4,
			IlvDvApplication* application = 0,
			const char* emptyMessage = "&EmptyRecentFileList",
			int maxDispLen = ILVDV_ABBREV_FILENAME_LEN,
			IlUInt start = 1);
    virtual ~IlvDvRecentFileList();

    // ----------------------------------------------------------------------
    // Accessors
    IlvString& operator	[](IlUInt index);

    // ----------------------------------------------------------------------
    // Adding / removing files
    void		removePathName(IlUInt index);
    void		addPathName(const char* strPathName);

    // ----------------------------------------------------------------------
    // Menu managment
    IlBoolean		getMenuString(IlvString& strName,
				      IlUInt index,
				      IlBoolean atLeastName = IlTrue) const;

    // ----------------------------------------------------------------------
    // Basic properties
    void		setName(const char* name);
    const char*		getName() const;
    virtual IlUInt	getCardinal() const;

    // ----------------------------------------------------------------------
    // Input / output
    void		readRegistries(const char* = 0);
    void		writeRegistries(const char* = 0);
    virtual void	readOptions(IlvDvOptions* options,
				    const IlSymbol* = 0);
    virtual void	updateOptions(IlvDvOptions* options,
				      const IlSymbol* = 0);

    static IlSymbol*	_DefaultFileListName;
    static IlSymbol*	_OptionFileListClass;

protected:

    int			_maxDisplayLength;
    const IlSymbol*	_name;
    IlvDvStringArray	_paths;

    virtual const char*	getItemString(IlUInt nItem, IlvString&) const;
    virtual IlAny	getClientItemData(IlUInt nItem) const;
    virtual IlBoolean	itemActivated(IlAny item, IlAny data) const;

public:
    static void		OpenRecentFileCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(filelst);
// --------------------------------------------------------------------------

#endif /* __Ilv_Appframe_Filelst_H */
