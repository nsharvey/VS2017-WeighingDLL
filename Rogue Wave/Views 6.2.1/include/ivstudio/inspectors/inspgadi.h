// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/inspgadi.h
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
// Declaration of the IlvStIScrollGadgetInspectorPanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Inspgadi_H
#define __IlvSt_Inspectors_Inspgadi_H

#if !defined(__IlvSt_Inspectors_Insppnl_H)
#  include <ivstudio/inspectors/insppnl.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif
#if !defined(__IlvSt_Inspectors_Listedt_H)
#  include <ivstudio/inspectors/listedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif

class IlvStIValueInterAccessor;
class IlvGadgetItem;
class IlvListGadgetItemHolder;
class IlvStIProperty;
class IlvValue;
class IlvStIProxyListGadget;

// --------------------------------------------------------------------------
// IlvStIGadgetItemValue
class ILVINSPCLASS IlvStIGadgetItemValue
    : public IlvStIProperty
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGadgetItemValue(IlvGadgetItem* = 0);
    IlvStIGadgetItemValue(const IlvStIGadgetItemValue&);
    virtual ~IlvStIGadgetItemValue();

    virtual IlvStIProperty* copy() const;
    virtual void clean();

    virtual void       set(const IlvStIProperty&);
    virtual IlvValue&  getValue(IlvValue&) const;
    virtual void       setValue(const IlvValue&);

    virtual const char* getString() const;
    virtual void        setString(const char*);

    virtual IlAny      getPointer() const { return (IlAny)_gadgetItem; }
    virtual void       setPointer(IlAny);

    // ----------------------------------------------------------------------
    // Specific gadget item methods
    IlvGadgetItem* getGadgetItem() const { return _gadgetItem; }
    IlvGadgetItem* detachGadgetItem();
    void protectGadgetItem(IlBoolean); // Protect from being deleted

protected:
    IlvGadgetItem* _gadgetItem;
    IlBoolean     _canDeleteItem;
};

// --------------------------------------------------------------------------
// IlvStIGadItemPictureTypeAccessor class
// --------------------------------------------------------------------------
class IlvStIGadItemPictureTypeAccessor
    : public IlvStICombinedAccessor
{
public:
    IlvStIGadItemPictureTypeAccessor(IlvStIPropertyAccessor* = 0,
				     IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				     const char* =
					       "GadItemPictureTypeAccessor");
    virtual ~IlvStIGadItemPictureTypeAccessor();

protected:
    IlvGadgetItem* _savedBitmapGadgetItem;
    IlvGraphic* _savedGraphic;

    void saveGadgetItemPicture();
    void restoreGadgetItemPicture(IlUShort);

    // ----------------------------------------------------------------------
    // Overridens
    virtual IlvStIProperty* getOriginalValue();
    virtual void          applyValue(IlvStIProperty*);

    // ----------------------------------------------------------------------
    // Gadget item access
    IlvGadgetItem* getGadgetItem() const;
    IlUShort getGadgetItemPictureType() const;
    void setGadgetItemPictureType(IlUShort);
};


// --------------------------------------------------------------------------
// IlvStIGadgetItemAccessor
class ILVINSPCLASS IlvStIGadgetItemAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGadgetItemAccessor(IlvStIPropertyAccessor* accessor = 0,
			     const char* name = 0,
			     IlvStIAccessor::UpdateMode updateMode =
						   IlvStIAccessor::Inherited,
			     IlvStIAccessor::BuildMode buildMode =
							IlvStIAccessor::None)
    : IlvStICombinedAccessor(accessor, updateMode, buildMode, name)
    {}

    IlvGadgetItem* getGadgetItem() const;
};

// --------------------------------------------------------------------------
// IlvStIGadgetItemEditor
class ILVINSPCLASS IlvStIGadgetItemEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGadgetItemEditor(const char* = 0,
		           IlvStIPropertyAccessor* = 0,
			   IlvStIEditor::NotificationMode =
						      IlvStIEditor::AsOwner);
    virtual ~IlvStIGadgetItemEditor();

protected:
    void initializeGadgetItemEditors();
};

// --------------------------------------------------------------------------
// IlvStIGadItemBitmapValue
class ILVINSPCLASS IlvStIGadItemBitmapValue
    : public IlvStIValueProperty
{
public:
    IlvStIGadItemBitmapValue(IlvGadgetItem*, IlSymbol*, IlvDisplay*);
    IlvStIGadItemBitmapValue(const IlvStIGadItemBitmapValue&);
    virtual IlvStIProperty* copy() const
	{ return ILVI_NEW IlvStIGadItemBitmapValue(*this); }
    virtual void clean();
    virtual void       modified();

    IlvBitmap* getBitmap() const;
    const char* getName() const;
protected:
    IlSymbol*     _name;
    IlvGadgetItem* _item;
    IlvDisplay*    _display;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGadItemListBitmapAccessor
    : public IlvStIPropertyListAccessor
{
public:
    IlvStIGadItemListBitmapAccessor(IlvStIPropertyAccessor* = 0,
				    IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				    const char* = 0,
				    IlvStIAccessor::BuildMode =
						       IlvStIAccessor::None);
    virtual ~IlvStIGadItemListBitmapAccessor();


    virtual const char* getPropertyString(const IlvStIProperty*) const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;

protected:
    IlvDisplay* getDisplay() const;

    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    IlvGadgetItem* getGadgetItem() const;
};

// --------------------------------------------------------------------------
// IlvStIListGadgetItemHolderAccessor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIListGadgetItemHolderAccessor
    : public IlvStICombinedValueInterAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIListGadgetItemHolderAccessor(IlvStIPropertyAccessor* = 0,
				       IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				       const char* = 0);
    virtual ~IlvStIListGadgetItemHolderAccessor();

    virtual IlvListGadgetItemHolder* getListGadgetItemHolder() const;

protected:
    virtual IlvStIProperty* getOriginalValue();
};

// --------------------------------------------------------------------------
// IlvStIListGadgetItemAccessor
class ILVINSPCLASS IlvStIListGadgetItemAccessor
    : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIListGadgetItemAccessor(IlvStIPropertyAccessor* = 0,
				 IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
				 IlBoolean = IlFalse,
				 const char* = 0);
    virtual ~IlvStIListGadgetItemAccessor();

    // ----------------------------------------------------------------------
    // Main overridables
    IlvListGadgetItemHolder* getListGadgetItemHolder() const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;

protected:
    IlBoolean _buildMenuItem;

    virtual IlvStIProperty** getInitialProperties(IlUInt&);
    virtual void	     replaceValue(IlvStIProperty*, IlvStIProperty*);
    virtual IlvStIProperty*  createDefaultProperty() const;

    virtual void addProperty(IlvStIProperty*, IlUInt);
    virtual void deleteNewProperty(IlvStIProperty*);
    virtual void deleteProperty(IlvStIProperty*, IlUInt);
    virtual void replaceProperty(IlvStIProperty*, IlvStIProperty*, IlUInt);
    virtual void moveProperty(IlvStIProperty*, IlUInt, IlUInt);
};

// --------------------------------------------------------------------------
// class IlvStIGadgetItemListEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGadgetItemListEditor
    : public IlvStIPropertyListEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGadgetItemListEditor(IlvStIPropertyAccessor* = 0,
			       IlBoolean = IlFalse,
			       const char* = 0,
			       IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIGadgetItemListEditor();

    // ----------------------------------------------------------------------
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty*) const;
};

// --------------------------------------------------------------------------
// class IlvStIGadgetItemListEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIListGadgetItemEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIListGadgetItemEditor(IlvStIPropertyAccessor* = 0,
			       IlBoolean = IlFalse,
			       const char* = 0,
			       IlvStIAccessor::UpdateMode =
						  IlvStIAccessor::Inherited);
    virtual ~IlvStIListGadgetItemEditor();
};

// --------------------------------------------------------------------------
// class IlvStIGadgetItemHolderEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIGadgetItemHolderEditor
    : public IlvStIPropertyEditorSet
{
    IlvDeclareInspClassInfo();
public:
    IlvStIGadgetItemHolderEditor(IlvStIPropertyAccessor* = 0,
			         IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			         const char* = 0);
    ~IlvStIGadgetItemHolderEditor();
};

// --------------------------------------------------------------------------
ILVINSPEXPORTEDFUNC(IlBoolean)
TranslatorAlignValueCallback(IlvStIProperty*, IlvValue&, IlBoolean, IlAny);

ILVINSPEXPORTEDFUNC(IlBoolean)
TranslatorAlignementCallback(IlvStIProperty*, IlvStIProxyListGadget*,
			     IlBoolean, IlAny);

ILVINSPEXPORTEDFUNC(void)
FillLabelAlignment(IlvStIProxyListGadget&, IlvDisplay*);

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_inspgadi)
#endif /* !__IlvSt_Inspectors_Inspgadi_H */
