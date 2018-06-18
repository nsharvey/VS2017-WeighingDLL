// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/psfacto.h
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
// Declaration of the IlvStpsEditorFactory class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Psfacto_H
#define __IlvSt_Inspectors_Psfacto_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Gadgets_Fbrowser_H)
#  include <ilviews/gadgets/fbrowser.h> 
#endif
#if !defined(__Ilv_Gadgets_Combo_H)
#  include <ilviews/gadgets/combo.h>
#endif
#if !defined(__Ilv_Edit_Respanel_H)
#  include <ilviews/edit/respanel.h> 
#endif
#if !defined(__IlvSt_Vobj_H)
#  include <ivstudio/vobj.h>
#endif
#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif
#if !defined(__IlvSt_Inspectors_Psrules_H)
#  include <ivstudio/inspectors/psrules.h>
#endif

// --------------------------------------------------------------------------
// IlvStpsEditorFactory
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsEditorFactory : public IlvStpsRefCount
{
public:
    IlvStpsEditorFactory();

    //---- Edition field ----
    virtual IlvMatrixItemEditor* createEditor(IlvMatrix*,
					      IlUShort col,
					      IlUShort row,
					      IlvValueTypeClass*,
					      IlSymbol*,
					      IlvGraphic*) const;

    virtual void	resetCache();

};

// --------------------------------------------------------------------------
// IlvStpsEditorFactoryByClass
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsEditorFactoryByClass : public IlvStpsRefCount
{
public:
    IlvStpsEditorFactoryByClass();

    void			setAccessorFactory(IlvClassInfo*,
						   IlvStpsEditorFactory*);

    virtual
    IlvMatrixItemEditor*	createEditor(IlvMatrix*,
					     IlUShort col,
					     IlUShort row,
					     IlvValueTypeClass*,
					     IlSymbol*,
					     IlvGraphic*) const;

    IlvStpsEditorFactory*	getFactory(IlvGraphic*) const;

    virtual void		resetCache();

protected:
    virtual ~IlvStpsEditorFactoryByClass();

    IlHashTable			_classes;
};

// --------------------------------------------------------------------------
// IlvStpsEditorFactoryList
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsEditorFactoryList
{
public:
    IlvStpsEditorFactoryList();
    virtual ~IlvStpsEditorFactoryList();

    //---- Rules ----
    IlvMatrixItemEditor*	createEditor(IlvMatrix*,
					     IlUShort col,
					     IlUShort row,
					     IlvValueTypeClass*,
					     IlSymbol*,
					     IlvGraphic*) const;
    IlvStpsEditorFactory*	get(IlSymbol*) const;

    //---- Register the rules ----
    void			setTypeFactory(IlvValueTypeClass*,
					       IlvStpsEditorFactory*);
    void			setAccessorFactory(IlSymbol*,
						   IlvStpsEditorFactory*);
    void			setClassFactory(IlvClassInfo*,
						IlSymbol*,
						IlvStpsEditorFactory*);

    void			resetCache();

private:
    IlHashTable			_byType;
    IlHashTable			_byAccessor;
    IlHashTable			_byClass;
};

// --------------------------------------------------------------------------
// IlvStpsEditorFactories
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsEditorFactories
{
public:
    static IlvStpsEditorFactories& GetInstance();

    static void			SetTypeFactory(IlvValueTypeClass*,
					       IlvStpsEditorFactory*);
    static void			SetAccessorFactory(IlSymbol*,
						   IlvStpsEditorFactory*);
    static void			SetClassFactory(IlvClassInfo*,
						IlSymbol*,
						IlvStpsEditorFactory*);

    static
    IlvMatrixItemEditor*	CreateEditor(IlvMatrix*,
					     IlUShort col,
					     IlUShort row,
					     IlvValueTypeClass*,
					     IlSymbol*,
					     IlvGraphic*);
    static void			ResetCache();

protected:
    IlvStpsEditorFactories();

    IlvStpsEditorFactoryList	_factoryList;
};


#define IlvStpsSetTypeFactory(typ,fac) \
IlvStpsEditorFactories::SetTypeFactory(typ,new fac)

#define IlvStpsSetAccessorFactory(acc,fac) \
IlvStpsEditorFactories::SetAccessorFactory(IlGetSymbol(acc),new fac)

#define IlvStpsSetClassAccessorFactory(cl,acc,fac) \
IlvStpsEditorFactories::SetClassFactory(cl::ClassInfo(),IlGetSymbol(acc),new fac)

// --------------------------------------------------------------------------
// IlvStpsInternalEditorFactory
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsInternalEditorFactory
    : public IlvStpsEditorFactory
{
public:
    IlvStpsInternalEditorFactory();
    virtual ~IlvStpsInternalEditorFactory();

    //---- Edition field ----
    virtual 
    IlvMatrixItemEditor*	createEditor(IlvMatrix*,
					     IlUShort col,
					     IlUShort row,
					     IlvValueTypeClass*,
					     IlSymbol*,
					     IlvGraphic*) const;

    virtual void		resetCache();

    IlvTextField*		makeEditor(IlvMatrix*,
					   IlUShort col,
					   IlUShort row,
					   IlvValueTypeClass*,
					   IlSymbol*,
					   IlvGraphic*) const;

  //---- Makers ----
    virtual IlvTextField*	createStringEditor(IlvDisplay*) const;
    virtual IlvTextField*	createIntegerEditor(IlvDisplay*) const;
    virtual IlvTextField*	createFloatEditor(IlvDisplay*) const;
    virtual IlvTextField*	createBooleanEditor(IlvDisplay*) const;
    virtual IlvTextField*	createPatternEditor(IlvDisplay*) const;
    virtual IlvTextField*	createLineStyleEditor(IlvDisplay*) const;
    virtual IlvTextField*	createFillStyleEditor(IlvDisplay*) const;
    virtual IlvTextField*	createArcModeEditor(IlvDisplay*) const;
    virtual IlvTextField*	createFillRuleEditor(IlvDisplay*) const;
    virtual IlvTextField*	createDirectionEditor(IlvDisplay*) const;
    virtual IlvTextField*	createColorEditor(IlvDisplay*) const;
    virtual IlvTextField*	createFontEditor(IlvDisplay*) const;
    virtual IlvTextField*	createBitmapEditor(IlvDisplay*) const;
    virtual IlvTextField*	createXMLFileEditor(IlvDisplay*) const;
    virtual IlvTextField*	createAntialiasingEditor(IlvDisplay*) const;
    virtual IlvTextField*	createRefreshModeEditor(IlvDisplay*) const;
    virtual IlvTextField*	createDisplayModeEditor(IlvDisplay*) const;

    virtual IlvTextField*	createPositionEditor(IlvDisplay*,
						     IlBoolean left,
						     IlBoolean right,
						     IlBoolean top = IlFalse,
						     IlBoolean bottom = IlFalse,
						     IlBoolean bad = IlFalse,
						     IlBoolean center = IlFalse,
						     IlBoolean horz = IlFalse,
						     IlBoolean vert = IlFalse) const;

    //---- Tools ----
    IlvComboBox*		createComboBox(IlvDisplay*,
					       IlBoolean editable,
					       IlvGadgetItem**,
					       IlInt count) const;  

    IlvStSelectionField*	createSelectionField(IlvDisplay*,
						     const char* bmp,
						     IlvGraphicCallback) const;

    //---- Tools about items ----
    IlvGadgetItem**		allocItemArray(IlInt);
    IlvGadgetItem**		copyItemArray(IlvGadgetItem**,IlInt);
    void			freeItemArray(IlvGadgetItem**,IlInt);  
    IlvGadgetItem*		createItem(IlvDisplay*,
					   const char* label,
					   const char* bmp = 0) const;

    IlvGadgetItem*		createPatternItem(IlvDisplay*,
						  const char* label) const;
    IlvGadgetItem*		createLineStyleItem(IlvDisplay*,
						    const char* label) const;
    IlvGadgetItem*		createFillRuleItem(IlvDisplay*,
						   const char* label) const;
    IlvGadgetItem*		createArcModeItem(IlvDisplay*,
						  const char* label) const;

private:
    //---- prebuild items ----
    void			initializeItems(IlvDisplay*);

    IlvGadgetItem**		_booleanItems;
    IlvGadgetItem**		_patternItems;
    IlvGadgetItem**		_lineStyleItems;
    IlvGadgetItem**		_fillStyleItems;
    IlvGadgetItem**		_arcModeItems;
    IlvGadgetItem**		_fillRuleItems;
    IlvGadgetItem**		_directionItems;
    IlvGadgetItem**		_antialiasingItems;
    IlvGadgetItem**		_refreshModeItems;
    IlvGadgetItem**		_displayModeItems;
    IlvGadgetItem**		_tmpItems;
};

// --------------------------------------------------------------------------
// IlvStpsComboboxEditorFactory
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsComboboxEditorFactory
    : public IlvStpsEditorFactory
{
public:
    IlvStpsComboboxEditorFactory(IlUInt itemCount);
    virtual ~IlvStpsComboboxEditorFactory();

    //---- Edition field ----
    virtual IlBoolean		isEditable() const;
    virtual IlvMatrixItemEditor* createEditor(IlvMatrix*,
					      IlUShort col,
					      IlUShort row,
					      IlvValueTypeClass*,
					      IlSymbol*,
					      IlvGraphic*) const;

    virtual void		resetCache();

    //---- Items ----
    virtual IlvGadgetItem*	makeItems(IlvDisplay*,
					  IlUInt index) const = 0;

    IlvGadgetItem*		createItem(IlvDisplay*,
					   const char* label,
					   const char* bmp = 0) const;

private:
    IlUInt			_itemCount;
    IlvGadgetItem**		_items;
    IlvGadgetItem**		_tmpItems;
};

// --------------------------------------------------------------------------
// IlvStpsPictureEditorFactory
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStpsPictureEditorFactory : public IlvStpsEditorFactory
{
public:
    IlvStpsPictureEditorFactory();
    virtual ~IlvStpsPictureEditorFactory();

    //---- Edition field ----
    virtual IlvMatrixItemEditor*	createEditor(IlvMatrix*,
						     IlUShort col,
						     IlUShort row,
						     IlvValueTypeClass*,
						     IlSymbol*,
						     IlvGraphic*) const;

};

#endif /* !__IlvSt_Inspectors_Psfacto_H */
