// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/rectangl.h
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
// Declaration of the IlvManagerRectangle class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Rectangl_H
#define __Ilv_Manager_Rectangl_H

#if !defined(__Ilv_Graphics_Rectview_H)
#include <ilviews/graphics/rectview.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerRectangle
: public IlvViewRectangle
{
public:
    IlvManagerRectangle(IlvDisplay*    display,
			const IlvRect& rect,
			IlvPalette*    palette = 0);
    ~IlvManagerRectangle();
    // ____________________________________________________________
    inline IlBoolean	isOwner() const           { return _owner;  }
    inline void		setOwner(IlBoolean owner) { _owner = owner; }
    inline const char*	getFilename() const       { return _filename; }
    void		setFilename(const char* name,
				    IlBoolean   redraw = IlFalse);
    inline IlvManager*	getManager() const         { return _manager; }
    virtual void	setManager(IlvManager* manager,
				   IlBoolean   owner = IlTrue);
    virtual void	setView(IlvView*);
    void		drawContents(IlvPort*         dst,
				     const IlvRect&   size,
				     const IlvRegion* clip) const;
    virtual void	setBackground(IlvColor* bgcolor);
    virtual void	setPalette(IlvPalette* palette);
    virtual void	setHolder(IlvGadgetHolder* holder);

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvManagerRectangle);
    DeclareGraphicAccessors();

    static IlSymbol*	_managerValue;
protected:
    IlvManager*		_manager;
    IlBoolean		_owner;
    char*		_filename;
};

ILVMGRMODULEINIT(m0_rectangl);
#endif /* __Ilv_Manager_Rectangl_H */
