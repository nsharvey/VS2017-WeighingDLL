// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/chklist.h
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
// Declaration of the IlvStICheckedStringList class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Chklist_H
#define __IlvSt_Inspectors_Chklist_H

#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#  include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Tree_H)
#  include <ilviews/gadgets/tree.h>
#endif

class IlvToggle;

// --------------------------------------------------------------------------
// IlvStICheckedListHolder
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICheckedListHolder
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStICheckedListHolder();
    ~IlvStICheckedListHolder();

    // ----------------------------------------------------------------------
    void checkItem(IlvGadgetItem*,
		   IlBoolean = IlTrue,
		   IlBoolean invalidate = IlFalse);
    // ----------------------------------------------------------------------
    typedef void (*ItemCheckedCallback)(IlvGadgetItemHolder*,
				        IlvGadgetItem*,
					IlBoolean,
					IlBoolean,
					IlAny);
    void setItemCheckedCallback(ItemCheckedCallback, IlAny = 0);
    void addItemCheckedCallback(ItemCheckedCallback, IlAny = 0);
    virtual void addCheckToGadget(IlvGadgetItem*) const;

    virtual IlBoolean       handleCheckEvent(IlvEvent& e);
    virtual IlvGadgetItemHolder* getGadgetItemHolder() = 0;
    IlvToggle* getToggle(IlvGadgetItem*) const;

protected:
    IlvToggle* _toggleCaptured;
    IlArray _checkCallbacks;
    void razCheckCallback();
    virtual void itemChecked(IlvGadgetItem*, IlBoolean, IlBoolean);

    virtual IlvGadgetItem* getSelectedItem() = 0;
    virtual IlvGadgetItem* pointToGadgetItem(const IlvPoint&,
					     IlvRect&) const = 0;

public:
    static void ToggleCheckedcallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
// IlvStICheckedStringList
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICheckedStringList
: public IlvStringList, public IlvStICheckedListHolder
{
public:
    IlvStICheckedStringList(IlvDisplay*        display,
			    const IlvPoint&    point,
			    const char* const* labels    = 0,
			    IlUShort          count     = 0,
			    IlUShort          thickness = IlvDefaultGadgetThickness,
			    IlvPalette*        palette   = 0);
    IlvStICheckedStringList(IlvDisplay*        display,
		  const IlvRect&     rect,
		  const char* const* labels    = 0,
		  IlUShort          count     = 0,
		  IlUShort          thickness = IlvDefaultGadgetThickness,
		  IlvPalette*        palette   = 0);
    IlvStICheckedStringList(IlvDisplay*        display,
		  const IlvPoint&    point,
		  const char* const* labels,
		  IlAny const*	     itemData,
		  IlUShort          count,
		  IlUShort          thickness = IlvDefaultGadgetThickness,
		  IlvPalette*        palette   = 0);
    IlvStICheckedStringList(IlvDisplay*        display,
		  const IlvRect&     rect,
		  const char* const* labels,
		  IlAny const*	     itemData,
		  IlUShort          count,
		  IlUShort          thickness = IlvDefaultGadgetThickness,
		  IlvPalette*        palette   = 0);
    virtual ~IlvStICheckedStringList();

    // ____________________________________________________________
    // Overridables
    virtual IlvGadgetItem*    createItem(const char* label,
					 IlvGraphic* g       = 0,
					 IlvBitmap*  bitmap  = 0,
					 IlvBitmap*  sbitmap = 0,
					 IlBoolean  copy    = IlTrue) const;
    // ____________________________________________________________
    // Adding new items
    void insertcheckedItem(const char* label,
			   IlBoolean state = IlFalse,
			   IlShort pos = -1,
			   IlvBitmap* = 0);
    // ____________________________________________________________
    // Checking items
    IlBoolean getItemCheckState(IlUShort) const;
    IlBoolean getItemIndeterminateCheckState(IlUShort iItem) const;
    void       setItemCheckState(IlUShort,
			         IlBoolean = IlTrue,
				 IlBoolean = IlFalse);

    // ____________________________________________________________
    void copyListAttributes(const IlvStringList&);
    // ____________________________________________________________
    // Specific callbacks
    static IlSymbol* ItemCheckedSymbol()   { return _itemCheckedSymbol;   }
    static IlSymbol* _itemCheckedSymbol;

    virtual IlUInt          getCallbackTypes(const char*      const**,
					      const IlSymbol* const**) const;

    DeclareGraphicAccessors();
    virtual IlBoolean       handleEvent(IlvEvent& e);
    virtual IlBoolean       getValueDescriptor(IlvValue& value) const;

    DeclareTypeInfo();
    DeclareIOConstructors(IlvStICheckedStringList);
protected:
    IlvToggle* getItemToggle(IlUShort) const;
    virtual IlvGadgetItemHolder* getGadgetItemHolder();
    virtual IlvGadgetItem* getSelectedItem();
    virtual IlvGadgetItem* pointToGadgetItem(const IlvPoint&,
					     IlvRect&) const;

public:
    static  IlSymbol* _getItemCheckMethod;
    static  IlSymbol* _setItemCheckMethod;
    static  IlSymbol* _itemCheckedMethod;
    static  IlSymbol* ItemCheckedCallbackType()
	{ return _itemCheckedMethod; }
};

// --------------------------------------------------------------------------
// IlvStICheckedTreeGadget class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICheckedTreeGadget
: public IlvTreeGadget, public IlvStICheckedListHolder
{
public:
    IlvStICheckedTreeGadget(IlvDisplay*    display,
			    const IlvRect& rect,
			    IlUShort      thickness = IlvDefaultGadgetThickness,
			    IlvPalette*    palette   =0);
    ~IlvStICheckedTreeGadget();

    // ____________________________________________________________
    // Overridables
    virtual IlvGadgetItem*    createItem(const char* label,
					 IlvGraphic* g       = 0,
					 IlvBitmap*  bitmap  = 0,
					 IlvBitmap*  sbitmap = 0,
					 IlBoolean  copy    = IlTrue) const;
    virtual IlBoolean       handleEvent(IlvEvent& e);
    void copyTreeGadgetAttributes(const IlvTreeGadget&);

protected:
    virtual IlvGadgetItemHolder* getGadgetItemHolder();
    virtual IlvGadgetItem* getSelectedItem();
    virtual IlvGadgetItem* pointToGadgetItem(const IlvPoint&,
					     IlvRect&) const;

    virtual IlvTreeGadgetItem* createItem(IlvTreeGadgetItem* parent,
					  const char* label,
					  IlvBitmap* bitmap,
					  IlvBitmap* selectionBitmap);
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_chklist)
// --------------------------------------------------------------------------

#endif /* !__IlvSt_Inspectors_Chklist_H */
