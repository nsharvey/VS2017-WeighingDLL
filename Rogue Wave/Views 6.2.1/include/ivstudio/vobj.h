// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/vobj.h
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
// Declaration of Views extension for Studio
// --------------------------------------------------------------------------
#ifndef __IlvSt_Vobj_H
#define __IlvSt_Vobj_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Tree_H
#include <ilviews/gadgets/tree.h>
#endif

class IlvPopupMenu;

class ILVSTUDIOCLASS IlvStTreeGadget : public IlvTreeGadget
{
public:
    IlvStTreeGadget(IlvDisplay*		display,
		    const IlvRect&	rect,
		    IlUShort		thickness = IlvDefaultGadgetThickness,
		    IlvPalette*		palette   = 0);
    DeclareTypeInfo();
    DeclareIOConstructors(IlvStTreeGadget);
    virtual IlBoolean		handleTreeEvent(IlvEvent&);

protected:
    virtual IlvPopupMenu*	getMenu(const IlvTreeGadgetItem*) const;
    virtual IlBoolean		leaveItem(IlvTreeGadgetItem*);

    IlvTreeGadgetItem*		_buttonDownItem;
    IlBoolean			_ignoreButtonUp;
}; // class IlvStTreeGadget

// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Sheet_H
#include <ilviews/gadgets/sheet.h>
#endif

class IlvStSheet;

// --------------------------------------------------------------------------
typedef IlBoolean (*IlvStSheetHook)(IlvStSheet*,
				    int hookType,
				    IlUShort posx,
				    IlUShort posy,
				    IlvEvent*);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSheet : public IlvSheet
{
public:
    IlvStSheet(IlvDisplay*	display,
	       const IlvRect&	rect,
	       IlUShort		nbcol,
	       IlUShort		nbrow,
	       IlvDim		xgrid = IlvDefaultMatrixWidth,
	       IlvDim		ygrid = IlvDefaultMatrixWidth,
	       IlvDim		thickness = IlvDefaultGadgetThickness,
	       IlBoolean	showVSB = IlTrue,
	       IlBoolean	showHSB = IlTrue,
	       IlvPalette*	palette = 0);
    ~IlvStSheet();

    DeclareTypeInfo();
    DeclareIOConstructors(IlvStSheet);

    virtual IlBoolean	handleMatrixEvent(IlvEvent&);
    virtual void	insertRow(IlUShort pos = 0, IlUShort count = 1);
    virtual void	validate();
    virtual void	focusOut();

    const char*		getLabel(IlUShort posx, IlUShort posy) const;
    void		setLabel(IlUShort posx, IlUShort posy, const char*);
    IlBoolean		getBoolean(IlUShort posx, IlUShort posy) const;
    void		setBoolean(IlUShort posx, IlUShort posy, IlBoolean);
    inline IlvPosition	getDefaultItemAlignment() const
			{
			    return _defaultItemAlignment;
			}
    inline void		setDefaultItemAlignment(IlvPosition pos)
			{
			    _defaultItemAlignment = pos;
			}
    // hook
    enum {
	BeforeValidatingHook,
	AfterValidatingHook,
	BeforeRemovingRowHook,
	AfterRemovingRowHook,
	BeforeInsertingRowHook,
	AfterInsertingRowHook,
	MenuButtonHook,
	LeaveRowHook,
	DoubleClickHook
    };
    inline void		setHook(IlvStSheetHook hook) { _hook = hook; }
    inline
    IlvStSheetHook	getHook() const { return _hook; }
    IlBoolean		callHook(int hookType,
				 IlUShort posx,
				 IlUShort posy,
				 IlvEvent*);
    IlvAbstractMatrixItem*	replaceItem(IlUShort posx,
					    IlUShort posy,
					    IlvAbstractMatrixItem* newItem,
					    IlBoolean = IlTrue);
    IlvAbstractMatrixItem*	pushItem(IlUShort posx,
					 IlUShort posy,
					 IlvAbstractMatrixItem* newItem,
					 IlBoolean = IlTrue);
    inline IlBoolean	hasSavedItem() const { return _hasSavedItem; }
    inline IlUShort	getSavedX() const { return _savedX; }
    inline IlUShort	getSavedY() const { return _savedY; }

    IlvAbstractMatrixItem*	restoreItem(const char* label = 0,
					    IlBoolean = IlTrue);

    inline IlBoolean	isRowInsertionAllowed() const
			{
			    return _rowInsertionAllowed;
			}
    inline void		allowRowInsertion(IlBoolean val)
			{
			    _rowInsertionAllowed = val;
			}
    inline IlBoolean	isRowDeletionAllowed() const
			{
			    return _rowDeletionAllowed;
			}
    inline void		allowRowDeletion(IlBoolean val)
			{
			    _rowDeletionAllowed = val;
			}

protected:
    void		initializeStSheet();
    virtual IlBoolean	handleKeyDown(IlvEvent&);

    IlvPosition			_defaultItemAlignment;
    IlvStSheetHook		_hook;
    IlBoolean			_hasSavedItem;
    IlvAbstractMatrixItem*	_savedItem;
    IlUShort			_savedX;
    IlUShort			_savedY;
    IlBoolean			_rowInsertionAllowed	ILVSTBF;
    IlBoolean			_rowDeletionAllowed	ILVSTBF;
}; // class IlvStSheet

// --------------------------------------------------------------------------
class IlvStringList;

#ifndef __Ilv_Gadgets_Idialog_H
#include <ilviews/gadgets/idialog.h>
#endif

class ILVSTUDIOCLASS IlvStPopupList : public IlvDialog
{
public:
    IlvStPopupList(IlvDisplay*, const char* name, IlvPalette* = 0);

    inline
    IlvStringList*	getList() const { return _list; }

    void		setLabels(const char* const*,
				  IlUShort,
				  IlBoolean = IlTrue);
    inline void		setMaxVisibleItems(IlUShort max)
			{
			    _maxVisibleItems = max;
			}
    inline IlUShort	getMaxVisibleItems() const { return _maxVisibleItems; }
    inline IlUShort	getVisibleItems() const { return _visibleItems; }
    void		setVisibleItems(IlUShort);
    void		adjustListHeight();
    void		adjustSize();
    const char*		get();
    inline void		setSelected(IlShort sel) { _selected = sel; }
    inline IlShort	getSelected() const { return _selected; }
    virtual void	handleInput(IlvEvent& event);

protected:
    IlvStringList*	_list;
    IlUShort		_maxVisibleItems;
    IlUShort		_visibleItems;
    IlShort		_selected;
};  // class ILVSTUDIOCLASS IlvStPopupList

// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Textfd_H
#include <ilviews/gadgets/textfd.h>
#endif

class ILVSTUDIOCLASS IlvStSelectionField : public IlvTextField
{
public:
    IlvStSelectionField(IlvDisplay*	display,
			const char*	label,
			const IlvRect&	rect,
			IlUShort	thickness = IlvDefaultGadgetThickness,
			IlvPalette*	palette   = 0);
    IlvStSelectionField(IlvDisplay*	display,
		        const IlvPoint&	at,
			const char*	label,
			IlUShort	thickness = IlvDefaultGadgetThickness,
			IlvPalette*	palette   = 0);
    ~IlvStSelectionField();

    void		draw(IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	getTextBBox(IlvRect& bbox) const;

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStSelectionField);

    static IlSymbol*	SelectCallbackSymbol();

    inline IlvBitmap*	getBitmap() const { return _bitmap; }
    void		setBitmap(IlvBitmap* bitmap);
    void		buttonBBox(IlvRect&, const IlvTransformer*) const;
    inline IlBoolean	isTextFieldVisible() const
			{
			    return _textFieldVisible;
			};
    void		setTextFieldVisible(IlBoolean);

protected:
    int			getButtonSize() const;

    IlvBitmap*		_bitmap;
    IlBoolean		_buttonInverted;
    IlBoolean		_buttonVisible;
    IlBoolean		_textFieldVisible;
}; // class IlvStSelectionField

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSelectionColor : public IlvStSelectionField
{
public:
    IlvStSelectionColor(IlvDisplay*	display,
			const char*	label,
			const IlvRect&	rect,
			IlUShort	thickness = IlvDefaultGadgetThickness,
			IlvPalette*	palette   = 0);
    IlvStSelectionColor(IlvDisplay*	display,
		        const IlvPoint&	at,
			const char*	label,
			IlUShort	thickness = IlvDefaultGadgetThickness,
			IlvPalette*	palette   = 0);
    ~IlvStSelectionColor();

    DeclareTypeInfoRO();
    DeclareIOConstructors(IlvStSelectionColor);

    static IlSymbol*	SelectCallbackSymbol();
}; // class IlvStSelectionColor


// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Idialog_H
#include <ilviews/gadgets/idialog.h>
#endif

class ILVSTUDIOCLASS IlvStTreeItemSelector : public IlvDialog
{
public:
    IlvStTreeItemSelector(IlvDisplay*,
			  const char*	name,
			  const char*	title,
			  IlUInt	properties = 0,
			  IlvSystemView	transientFor = 0);

    const char*		getLabel() const;
    void		setLabel(const char*);
    inline
    IlvStTreeGadget*	getTree() const
			{
			    return (IlvStTreeGadget*)getObject("tree");
			}
    const IlvTreeGadgetItem*	get(IlBoolean grab = IlFalse, IlvCursor* = 0);
}; // class IlvStTreeSelector

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_vobj)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Vobj_H */
