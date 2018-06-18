// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/toolpath.h
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
// Declaration of the classes IlvToolBarPath
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Toolpath_H
#define __Ilv_Gadgets_Toolpath_H

#if !defined(__Ilv_Gadgets_Matrix_H)
#include<ilviews/gadgets/matrix.h>
#endif
#if !defined(__Ilv_Gadgets_Toolbar_H)
#include <ilviews/gadgets/toolbar.h>
#endif
#if !defined(__Il_Pathname_H)
#include <ilog/pathname.h>
#endif

typedef void (*IlvToolBarPathCallback)(const IlPathName& path, IlAny any);

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvMenuItemPath : public IlvMenuItem 
{
public:
    IlvMenuItemPath(const char* label);
    virtual ~IlvMenuItemPath();

    void		setPathName(const IlPathName& path);
    const IlPathName&	getPathName() const;

protected:
    IlPathName		_pathname;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvToolBarPath : public IlvToolBar
{
public:
    IlvToolBarPath(IlvDisplay* display, const IlvRect& rect);
    virtual ~IlvToolBarPath();

    virtual void	setPath(const IlPathName& path);
    const char*		getPath() const;

    virtual
    IlvPopupMenu*	createDirectoryMenu(const IlPathName& path);
    virtual
    IlvPopupMenu*	createDeviceMenu(const IlString& current);

    virtual
    IlvMenuItemPath*	createMenuItem(const IlString& label,
				       const IlPathName& path,
				       IlvPopupMenu* submenu = 0);

    virtual void	rewindDir(const IlPathName& path);

    virtual void	changeDir(const IlPathName& path);

    void		setRewindCallback(IlvToolBarPathCallback cb,
					  IlAny arg = 0);

    void		setChangeDirCallback(IlvToolBarPathCallback cb,
					     IlAny arg = 0);

    void		setPathForCallback(const IlPathName& path);
    const IlPathName&	getPathForCallback() const;

protected:
    IlString			_path;

    IlvToolBarPathCallback	_rewindCb;
    IlAny			_rewindInfo;

    IlvToolBarPathCallback	_changeDirCb;
    IlAny			_changeDirInfo;

    IlPathName			_pathForCallback;
};

#endif /* !__Ilv_Gadgets_Toolpath_H */
