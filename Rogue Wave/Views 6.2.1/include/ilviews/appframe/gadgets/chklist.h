// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/gadgets/chklist.h
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
// Declaration of the IlvCheckedStringList class
// --------------------------------------------------------------------------
#ifndef __Ilv_Appframe_Gadgets_Chklist_H
#define __Ilv_Appframe_Gadgets_Chklist_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#include <ilviews/gadgets/tree.h>
#endif

class ILVGDTEXPORTED IlvToggle;
class ILVVWSEXPORTED IlvGadget;
class IlvDvItemCheck;
// --------------------------------------------------------------------------
// IlvCheckedListHolder
// --------------------------------------------------------------------------
class ILVDVCLASS IlvCheckedListHolder
{
public:
    typedef enum { Normal, Explorer } CheckLook;
    static CheckLook	_DefaultCheckLook;

    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvCheckedListHolder(CheckLook = _DefaultCheckLook);
    IlvCheckedListHolder(IlvInputFile& is, IlvPalette* palette);
    IlvCheckedListHolder(const IlvCheckedListHolder&);
    virtual ~IlvCheckedListHolder();

    // ----------------------------------------------------------------------
    void		checkItem(IlvGadgetItem*,
				  IlBoolean = IlTrue,
				  IlBoolean invalidate = IlFalse);
    // ----------------------------------------------------------------------
    typedef void (*ItemCheckedCallback)(IlvGadgetItemHolder*,
				        IlvGadgetItem*,
					IlBoolean,
					IlBoolean,
					IlAny);
    void		setItemCheckedCallback(ItemCheckedCallback, IlAny = 0);
    void		addItemCheckedCallback(ItemCheckedCallback, IlAny = 0);
    virtual IlvGadget*	addCheckToItem(IlvGadgetItem*,
				       IlBoolean state = IlTrue) const;

    static IlvGadget*	AddCheckToItem(IlvGadgetItem*,
				       IlvDisplay*,
				       IlBoolean state = IlFalse,
				       CheckLook = _DefaultCheckLook);
    virtual IlBoolean	handleCheckEvent(IlvEvent& e);
    virtual IlvGadgetItemHolder*	getGadgetItemHolder() = 0;
    IlvToggle*		getToggle(IlvGadgetItem*) const;

protected:
    CheckLook		_look;
    IlvToggle*		_toggleCaptured;
    IlArray		_checkCallbacks;

    void		razCheckCallback();
    virtual void	itemChecked(IlvGadgetItem*, IlBoolean, IlBoolean);

    virtual IlvGadgetItem*	getSelectedItem() = 0;
    virtual IlvGadgetItem*	pointToGadgetItem(const IlvPoint&,
						  IlvRect&) const = 0;
    virtual void	gadgetItemBBox(const IlvGadgetItem*,
				       IlvRect&) const = 0;
    IlvDvItemCheck*	getItemCheck(const IlvGadgetItem*) const;

public:
    static void		ToggleCheckedcallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
// IlvCheckedStringList
// --------------------------------------------------------------------------
class ILVDVCLASS IlvCheckedStringList
: public IlvStringList, public IlvCheckedListHolder
{
public:
    IlvCheckedStringList(IlvDisplay* display,
			 const IlvPoint& point,
			 CheckLook look            = _DefaultCheckLook,
			 const char* const* labels = 0,
			 IlUShort count            = 0,
			 IlUShort thickness        = IlvDefaultGadgetThickness,
			 IlvPalette* palette       = 0);
    IlvCheckedStringList(IlvDisplay* display,
			 const IlvRect& rect,
			 CheckLook look            = _DefaultCheckLook,
			 const char* const* labels = 0,
			 IlUShort count            = 0,
			 IlUShort thickness        = IlvDefaultGadgetThickness,
			 IlvPalette* palette       = 0);
    IlvCheckedStringList(IlvDisplay* display,
			 const IlvPoint& point,
			 const char* const* labels,
			 IlAny const* itemData,
			 IlUShort count,
			 CheckLook look      = _DefaultCheckLook,
			 IlUShort thickness  = IlvDefaultGadgetThickness,
			 IlvPalette* palette = 0);
    IlvCheckedStringList(IlvDisplay* display,
			 const IlvRect& rect,
			 const char* const* labels,
			 IlAny const* itemData,
			 IlUShort count,
			 CheckLook look      = _DefaultCheckLook,
			 IlUShort thickness  = IlvDefaultGadgetThickness,
			 IlvPalette* palette = 0);
    virtual ~IlvCheckedStringList();

    // ____________________________________________________________
    // Overridables
    virtual IlvGadgetItem*	createItem(const char* label,
					   IlvGraphic* g       = 0,
					   IlvBitmap*  bitmap  = 0,
					   IlvBitmap*  sbitmap = 0,
					   IlBoolean  copy    = IlTrue) const;
    // ____________________________________________________________
    // Adding new items
    void		insertcheckedItem(const char* label,
					  IlBoolean state = IlFalse,
					  IlShort pos = -1,
					  IlvBitmap* = 0);
    // ____________________________________________________________
    // Checking items
    IlBoolean		getItemCheckState(IlUShort) const;
    IlBoolean		getItemIndeterminateCheckState(IlUShort iItem) const;
    void		setItemCheckState(IlUShort,
					  IlBoolean = IlTrue,
					  IlBoolean = IlFalse);

    // ____________________________________________________________
    void		copyListAttributes(const IlvStringList&);
    // ____________________________________________________________
    // Specific callbacks
    static IlSymbol*	ItemCheckedSymbol()   { return _itemCheckedSymbol;   }

    static IlSymbol*	_itemCheckedSymbol;

    virtual IlUInt	getCallbackTypes(const char*      const**,
					 const IlSymbol* const**) const;

    DeclareGraphicAccessors();
    virtual IlBoolean	handleEvent(IlvEvent& e);
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    DeclareTypeInfo();
    DeclareIOConstructors(IlvCheckedStringList);

protected:
    IlvToggle*				getItemToggle(IlUShort) const;
    virtual IlvGadgetItemHolder*	getGadgetItemHolder();
    virtual IlvGadgetItem*		getSelectedItem();
    virtual IlvGadgetItem*		pointToGadgetItem(const IlvPoint&,
							  IlvRect&) const;
    virtual void			gadgetItemBBox(const IlvGadgetItem*,
						       IlvRect&) const;

public:
    static IlSymbol*		_getItemCheckMethod;
    static IlSymbol*		_setItemCheckMethod;
    static IlSymbol*		_itemCheckedMethod;
    static inline IlSymbol*	ItemCheckedCallbackType()
				{
				    return _itemCheckedMethod;
				}
};

// --------------------------------------------------------------------------
// IlvCheckedTreeGadget class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvCheckedTreeGadget
: public IlvTreeGadget, public IlvCheckedListHolder
{
public:
    IlvCheckedTreeGadget(IlvDisplay*    display,
			 const IlvRect& rect,
			 CheckLook      look      = _DefaultCheckLook,
			 IlUShort       thickness = IlvDefaultGadgetThickness,
			 IlvPalette*    palette   =0);
    ~IlvCheckedTreeGadget();

    // ____________________________________________________________
    // Checking items
    IlBoolean	getItemCheckState(IlvTreeGadgetItem*) const;
    IlBoolean	getItemIndeterminateCheckState(IlvTreeGadgetItem*) const;
    void	setItemCheckState(IlvTreeGadgetItem*,
				  IlBoolean = IlTrue,
				  IlBoolean = IlFalse);
    // ____________________________________________________________
    // Overridables
    virtual IlvGadgetItem*	createItem(const char* label,
					   IlvGraphic* g       = 0,
					   IlvBitmap*  bitmap  = 0,
					   IlvBitmap*  sbitmap = 0,
					   IlBoolean  copy    = IlTrue) const;
    virtual IlBoolean		handleEvent(IlvEvent& e);
    void			copyTreeGadgetAttributes(const IlvTreeGadget&);

    DeclareGraphicAccessors();
    DeclareTypeInfo();
    DeclareIOConstructors(IlvCheckedTreeGadget);

    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual IlUInt	getCallbackTypes(const char* const**,
					 const IlSymbol* const**) const;

protected:
    virtual IlvGadgetItemHolder*	getGadgetItemHolder();
    virtual IlvGadgetItem*		getSelectedItem();
    virtual IlvGadgetItem*		pointToGadgetItem(const IlvPoint&,
							  IlvRect&) const;
    virtual void			gadgetItemBBox(const IlvGadgetItem*,
						       IlvRect&) const;

    virtual IlvTreeGadgetItem*		createItem(IlvTreeGadgetItem* parent,
						   const char* label,
						   IlvBitmap* bitmap,
						   IlvBitmap* selectionBitmap);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(chklist);
// --------------------------------------------------------------------------

#endif /* !__Ilv_Appframe_Gadgets_Chklist_H */
