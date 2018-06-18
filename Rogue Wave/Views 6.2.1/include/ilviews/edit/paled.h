// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/paled.h
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
// Compact palette/attribute editor
// --------------------------------------------------------------------------
#ifndef __Ilv_Edit_Paled_H
#define __Ilv_Edit_Paled_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Command_H)
#include <ilviews/base/command.h>
#endif
#if !defined(__Ilv_Base_Resource_H)
#include <ilviews/base/resource.h>
#endif
#if !defined(__Ilv_Gadgets_Toolbar_H)
#include <ilviews/gadgets/toolbar.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Manager_Selhook_H)
#include <ilviews/manager/selhook.h>
#endif


class IlvAttributeEditorSet;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvAttributeEditor
{
public:
    IlvAttributeEditor(const IlvValue&);
    virtual ~IlvAttributeEditor();
    // ____________________________________________________________
    virtual void		targetChanged(const IlvValue&);
    virtual void		valueChanged(const IlvValue&);

    inline const IlSymbol*	getName() const { return _attribute; }
    inline const IlvValue&	getValue() const { return _currentValue; }

    inline void			setAttributeEditorSet(IlvAttributeEditorSet* e)
				{
				    _editorSet = e;
				}
    inline IlvAttributeEditorSet*	getAttributeEditorSet() const
					{
					    return _editorSet;
					}

    inline IlvMenuItem*		getEditor(IlvDisplay* d)
				{
				    if (!_editor)
					_editor = makeEditor(d);
				    return _editor;
				}
protected:
    static void			ChangeValue(IlvGraphic*, IlAny);
    virtual IlvMenuItem*	makeEditor(IlvDisplay*);

    IlvAttributeEditorSet*	_editorSet;
    const IlSymbol*		_attribute;
    IlvValue			_currentValue;
    IlvMenuItem*		_editor;
};

// --------------------------------------------------------------------------
// Attribute editors are built via a factory:
class ILVEDTEXPORTED IlvAttributeEditorFactory
{
public:
    IlvAttributeEditorFactory(const IlvValueTypeClass* c,
			      const char*              symb = 0)
	: _attributeSymb(0),
	  _class(c),
	  _attributeName(symb)
	{
	    _builders.add(this);
	}
    virtual ~IlvAttributeEditorFactory();
    // ____________________________________________________________
    static IlvAttributeEditor*	MakeEditor(const IlvValueTypeClass*,
					   const IlSymbol* = 0);
    inline static IlArray&	getBuilders() { return _builders; }
    inline const char*		getName() { return _attributeName; }
protected:
    virtual IlvAttributeEditor*	makeEditor(const IlvValueTypeClass*,
					   const IlSymbol* = 0);
    static IlArray		_builders;
    const IlSymbol*		_attributeSymb;
    const IlvValueTypeClass*	_class;
    const char*			_attributeName;
};

#define IlvDefineAttributeEditorFactory(NAME,TYPE,CONSTRUCTION,MODULE) \
class MODULE NAME : public IlvAttributeEditorFactory 		\
{ 								\
public:								\
    NAME(const char* n=0): IlvAttributeEditorFactory(TYPE,n) {} \
    inline IlvAttributeEditor*					\
			makeEditor(const IlvValueTypeClass*, 	\
                                   const IlSymbol* = 0)	\
	{ 							\
		return new CONSTRUCTION;			\
	}							\
}

// ---------------- predefined attribute editor types:
// most attributes are enum. thus we make a class for those:

class ILVEDTEXPORTED IlvEnumAttributeEditor: public IlvAttributeEditor
{
public:
    IlvEnumAttributeEditor(const IlvValue&,
			   IlBoolean    editable   = IlTrue,
    			   IlBoolean    hasChooser = IlFalse,
			   IlvDim       w          = 0,
			   const char** values     = 0,
			   IlUInt       c          = 0);
    ~IlvEnumAttributeEditor();
    IlvMenuItem*		makeEditor(IlvDisplay*);
    void			targetChanged(const IlvValue&);

    virtual void		makeEnumeration(IlvDisplay*);
    virtual IlvValue		selectValue(IlvDisplay*);
    virtual IlvGraphic*		makeGraphic(IlvDisplay*, const IlvValue&);

protected:

    static void			ChangeValueCallback(IlvGraphic*, IlAny);
    static void			ChooserCallback(IlvGraphic*, IlAny);
    IlArray			_strings;
    IlBoolean			_editable;
    IlBoolean			_hasChooser;
    IlvDim			_width;
};

IlvDefineAttributeEditorFactory(IlvEnumAttributeEditorFactory,
		IlvValueStringType,
		IlvEnumAttributeEditor(IlvValue(getName(),(const char*)0)),
		ILVEDTEXPORTED);

// ------------- color attribute editor

class ILVEDTEXPORTED IlvColorAttributeEditor : public IlvAttributeEditor
{
public:
    IlvColorAttributeEditor(const IlvValue&);
    IlvMenuItem*	makeEditor(IlvDisplay*);
    void		targetChanged(const IlvValue&);
    void		updateCache(IlvColor*, IlShort = 0);

protected:
    static void		ChangeValueCallback(IlvGraphic*, IlAny);
    static void		PickColorCallback(IlvGraphic*,IlAny);
    IlUInt		_usedColors[15];
};

IlvDefineAttributeEditorFactory(IlvColorAttributeEditorFactory,
			IlvValueColorType,
			IlvColorAttributeEditor(IlvValue(getName(),
							 (IlvColor*)0)),
			ILVEDTEXPORTED);

// --------------- attribute editors are grouped in an editor set:
class ILVEDTEXPORTED IlvAttributeEditorSet : public IlvToolBar
{
public:
    IlvAttributeEditorSet(IlvDisplay*,
			  const char*      name       = 0,
			  const IlSymbol** attributes = 0,
			  IlUInt           count      = 0);
    virtual ~IlvAttributeEditorSet();
    // ____________________________________________________________
    void			setContext(IlvCommandHistory*);
    virtual void		valueChanged(const IlvValue&);
    virtual void		targetChanged(IlvValueInterface*);

    virtual IlvPalette*		getEditedPalette() const = 0;
    IlvAttributeEditor*		getEditor(const IlSymbol*) const;
    inline IlvValueInterface*	getTarget()  const { return _currentTarget; }
    inline IlvCommandHistory*	getContext() const { return _context; }

    static IlvAttributeEditorSet* GetAttributeEditorSet(const char* palName);

protected:
    static IlArray		_paletteEditors;

    IlArray			_editors;
    IlvCommandHistory*		_context;
    IlString			_paletteName;
    IlvValueInterface*		_currentTarget;
    IlvManagerSelectionHook*	_selectionHandler;
    IlvObserver*		_commandObserver;
};


// --------------------------------------------------------------------------
// The palette editor is just one instance of an attribute set
// editor that groups all the attributes of a palette: fg and bg color,
// font, line style...
class ILVEDTEXPORTED IlvPaletteEditor : public IlvAttributeEditorSet
{
public:
    IlvPaletteEditor(IlvDisplay* d, const char* n = 0);
    // ____________________________________________________________
    const IlSymbol**		getPaletteSymbols() const;
    virtual void		setEditedPalette(IlvPalette*);
    virtual IlvPalette*		getEditedPalette() const;
    void			targetChanged(IlvValueInterface*);
    void			valueChanged(const IlvValue&);

protected:
    static IlUInt		_numSymbols;
    static IlSymbol**		_Symbols;
};
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvPatternSelector : public IlvDialog
{
public:
    IlvPatternSelector(IlvDisplay* display,
		       IlvPtrnType patternType = IlvPatternType,
		       IlBoolean loadNewPatterns = IlTrue,
		       IlvSystemView trFor = 0);
    IlvGadgetItem* createPatternItem(IlvPattern* pattern) const;
    void addPattern(IlvPattern* pattern,
		    IlBoolean sort = IlTrue,
		    IlBoolean select = IlTrue);
    void fill(IlvPtrnType patternType,
	      IlBoolean loadNewPatterns);
    IlvPattern* getResult() const;
    IlvPattern* get(IlBoolean grab,
		    IlvCursor* cursor = 0);
    void set(IlvPattern* pattern);
    inline IlBoolean hasMonochromePatterns() const
		{ return _patternType == IlvPatternType; }
    inline IlBoolean hasColoredPatterns() const
		{ return _patternType == IlvColorPatternType; }
    inline IlBoolean hasGradientPatterns() const
		{ return _patternType == IlvGradientPatternType; }
    static void Destroy(IlvView* v,
			IlAny);
    static void NewPatternCB(IlvGraphic* g,
			     IlAny arg);
    static void EditOrCreateGradientPatternCB(IlvGraphic* g,
					      IlAny arg);
    static void ListCB(IlvGraphic* g,
		       IlAny arg);
    static void SelectCB(IlvGraphic* g,
		       IlAny arg);
    inline IlvPtrnType getPatternType() { return _patternType;};
    inline IlBoolean loadNewPatterns() { return _loadNewPatterns;};
    inline IlvButton* getEditButton() { return _editBtn;};
protected:
    IlvPtrnType _patternType;
    IlBoolean   _loadNewPatterns;
    IlvButton*  _editBtn;
};
#endif /* __Ilv_Edit_Paled_H */
