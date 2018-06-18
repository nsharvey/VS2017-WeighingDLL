// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/clselec.h
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
// Declaration of generic panel selector
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Clselec_H)
#define __IlvSt_Inspectors_Clselec_H

#if !defined(__IlvSt_Inspectors_Genacces_H)
#  include <ivstudio/inspectors/genacces.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#  include <ilviews/base/link.h>
#endif
#if !defined(__IlvSt_Inspectors_Genedt_H)
#  include <ivstudio/inspectors/genedt.h>
#endif

class IlvSelector;
class IlvToggle;
class IlvGadgetItemHolder;
class IlvStICheckedStringList;
class IlvStICheckedListHolder;

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIObjectClassAccessor : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIObjectClassAccessor(IlvStIPropertyAccessor* accessor = 0,
			      UpdateMode = NoUpdate,
			      BuildMode = None,
			      const char* name = 0);
    ~IlvStIObjectClassAccessor();

    virtual IlBoolean	initialize();

    virtual void		setType(const IlSymbol*);
    void			setTypeByName(const char* typeName);
    const IlSymbol*		getType() const { return _type; }
    IlAny			getObject(const IlSymbol*) const;
    const char*			getTypeName(const IlSymbol*) const;
    IlvStIPropertyAccessor*	createTypeNameAccessor();
    IlvStICombinedAccessor*	getTypedAccessor(const IlSymbol*) const;
    void			cleanObjects();

    void			addType(const IlSymbol*, const char*);

public:
    class FilterAccessor : public IlvStICombinedAccessor
    {
    public:
	FilterAccessor(IlvStIObjectClassAccessor* objClassAcc,
		       const IlSymbol* pType);

    protected:
	const IlSymbol*		_type;
	virtual IlvStIProperty*	getOriginalValue();
	virtual void		applyValue(IlvStIProperty* property);
    };

    class TypeNameAccessor : public IlvStICombinedAccessor
    {
    public:
	TypeNameAccessor(IlvStIObjectClassAccessor* objClassAcc);

    protected:
	const IlSymbol*		_type;
	virtual IlvStIProperty*	getOriginalValue();
	virtual void		applyValue(IlvStIProperty* property);
    };

    typedef struct ObjectInfoTag {
	const IlSymbol*		_type;
	IlString		_listValue;
	IlBoolean		_canDelete;
	IlAny			_object;
	IlvStICombinedAccessor*	_accessor;
	ObjectInfoTag(const IlSymbol* pType,
		      const char* listValue,
		      IlvStICombinedAccessor* accessor):
	    _type(pType),
	    _listValue(listValue),
	    _canDelete(IlTrue),
	    _object(0),
	    _accessor(accessor)
	{
	    _accessor->lock();
	}
	~ObjectInfoTag() { _accessor->unLock(); }
    } ObjectInfo;

protected:
    IlBoolean		isCopyMode() const;
    ObjectInfo*		getObjectInfo(const IlSymbol*) const;
    ObjectInfo*		getObjectInfoByName(const char*) const;
    virtual
    IlAny		getObjectFromProperty(const IlvStIProperty*) const;
    virtual void	setObjectToProperty(IlvStIProperty*, IlAny);
    virtual
    const IlSymbol*	getObjectType(IlAny) const = 0;
    virtual IlAny	createObject(const IlSymbol*) const = 0;
    virtual void	deleteObject(IlAny) const = 0;
    virtual IlAny	copyObject(IlAny) const;
    virtual void	objectTypeChanged(const IlSymbol* newType,
					  const IlSymbol* oldType);
    IlAny		ensureObject(IlvStIProperty* property);
    void		clear();
    virtual
    IlvStIProperty*	getOriginalValue();
    virtual void	applyValue(IlvStIProperty* property);

    IlArray		_objects;
    const IlSymbol*	_type;
};

// --------------------------------------------------------------------------
// IlvStIFlagArray class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIFlagArray : public IlArray
{
public:
    IlvStIFlagArray(IlBoolean combinedMode = IlFalse,
		    IlUInt startLength = 4);
    ~IlvStIFlagArray();

    void		addNamedMode(IlUInt mode, const char* name);

    // ----------------------------------------------------------------------
    // Basic properties
    inline IlBoolean	isCombinedMode() const { return _combinedMode; }
    inline void		setCombinedMode(IlBoolean combined)
			{
			    _combinedMode = combined;
			}

    // ----------------------------------------------------------------------
    class NamedMode
    {
    public:
	NamedMode(IlUInt nMode, const char* name)
	    : _mode(nMode),
	      _name(name)
	{}
	IlUInt		_mode;
	IlString	_name;
    };

    NamedMode*		getNamedMode(IlUInt iMode) const;
    NamedMode*		findNamedMode(IlUInt iMode) const;
    NamedMode*		getNamedMode(const char*) const;

protected:
    IlUInt    _modeMask;
    IlBoolean _combinedMode;
};

// --------------------------------------------------------------------------
// IlvStINamedModeAccessor class
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStINamedModeAccessor
    : public IlvStICombinedAccessor, public IlvStIFlagArray
{
    IlvDeclareInspClassInfo();

public:
    typedef void (*ModeCallback)(IlBoolean bInput, IlAny, IlUInt&, IlAny);

    IlvStINamedModeAccessor(IlvStIPropertyAccessor* accessor = 0,
			    ModeCallback	callback = 0,
			    IlAny		calbackParam = 0,
			    const char*		name = 0,
			    IlBoolean		combinedMode = IlFalse,
			    UpdateMode = NoUpdate,
			    BuildMode = None);
    ~IlvStINamedModeAccessor();

    void		setModeCallback(ModeCallback, IlAny = 0);

protected:
    ModeCallback	_callback;
    IlAny		_callbackParam;

    virtual IlUInt		getMode() const;
    virtual void		setMode(IlUInt);
    virtual IlUInt		getNullMode() const;
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty* property);
};

// --------------------------------------------------------------------------
// IlvStICheckedListEditor
// --------------------------------------------------------------------------
typedef void (*CheckedFillerCallback)(IlvStICheckedStringList&, IlAny);

class ILVINSPCLASS IlvStICheckedListEditor
    : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStICheckedListEditor(const char* name = 0,
			    IlvStIPropertyAccessor* accessor = 0,
			    NotificationMode = AsOwner);
    ~IlvStICheckedListEditor();

    // ----------------------------------------------------------------------
    // Main overridables

    // ----------------------------------------------------------------------
    void		setFillerCallback(CheckedFillerCallback,
					  IlAny param = 0);

    void		setFillAlways(IlBoolean = IlTrue);
    IlBoolean		getFillAlways() const;

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	_DefaultWidth;
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    IlvStICheckedStringList*	getCheckedStringList() const;
    IlUShort			getLabelIndex(const char*);
    virtual void		setGraphic(IlvGraphic* graphic,
					   IlvGraphicHolder* holder);

    virtual const char*		getGraphicClassName() const;
    virtual IlSymbol*		getCallbackType() const;
    virtual void		createEditorObject(IlvDisplay* display,
						   IlArray& labels,
						   IlArray& editors);
    virtual IlvGraphic*		createGraphic(IlvDisplay* display,
					      const char* label);
    virtual void		empty();

    virtual void		fillListGadget();

public:
    static void			ItemCheckedCallback(IlvGadgetItemHolder*,
						    IlvGadgetItem*,
						    IlBoolean,
						    IlBoolean,
						    IlAny);
    virtual void		itemChecked(IlvGadgetItemHolder*,
					    IlvGadgetItem*,
					    IlBoolean,
					    IlBoolean);
};

// --------------------------------------------------------------------------
// IlvStIFlagsListEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIFlagsListEditor
    : public IlvStICheckedListEditor, public IlvStIFlagArray
{
    IlvDeclareInspClassInfo();

public:
    IlvStIFlagsListEditor(const char* name = 0,
			  IlvStIPropertyAccessor* accessor = 0,
			  NotificationMode = AsOwner);
    ~IlvStIFlagsListEditor();

    // ----------------------------------------------------------------------
    // Overridables
    IlBoolean		initialize();

    // ----------------------------------------------------------------------
protected:
    virtual void	fillListGadget();
    virtual IlvValue&	queryGraphicValue(IlvValue& value) const;
    IlUInt		getListFlag(IlvStICheckedStringList*) const;
    virtual void	itemChecked(IlvGadgetItemHolder*,
				    IlvGadgetItem*,
				    IlBoolean,
				    IlBoolean);
};

// --------------------------------------------------------------------------
// class IlvStIIndexedListEditor
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Listedt_H)
#include <ivstudio/inspectors/listedt.h>
#endif

class ILVINSPCLASS IlvStIIndexedListEditor
    : public IlvStIPropertyListEditor
{
public:
    IlvStIIndexedListEditor(IlvStIPropertyListAccessor* accessor,
			    const char* fmt,
			    const char* name = 0,
			    IlUInt startingIndex = 1);

    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);

protected:
    IlString		_fmt;
    IlUInt		_startingIndex;
    virtual void	getLabel(IlUInt, IlString&) const;
    virtual IlvGadgetItem* createGadgetItem(const IlvStIProperty* prop) const;
    virtual void	propertyCountChanged(IlUInt count, int flag); // flag = 1: adding, flag = 0: initializing, flag = -1: removing
};

// --------------------------------------------------------------------------
// class IlvStIPropertyPaletteEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyPaletteEditor :
    public IlvStIPropertyColorEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIPropertyPaletteEditor(const char* name = 0,
			        IlvStIPropertyAccessor* accessor = 0,
#ifndef NO_SHOWHIDE_PATCH
				IlBoolean replaceGadget = IlTrue,
#endif
			        NotificationMode = AsOwner);
    ~IlvStIPropertyPaletteEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean initialize();
    virtual void setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() { return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;
    IlvPalette*		_palette;
#ifndef NO_SHOWHIDE_PATCH
    IlBoolean		_replaceGadget;
#endif

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvValue&	queryGraphicValue(IlvValue& value) const;
    virtual void	onGraphicNotification();
    virtual void	onButtonPushed();
    void		updateTextFieldPalette();
    virtual void	setGraphic(IlvGraphic*, IlvGraphicHolder* = 0);
    virtual IlBoolean	hasChanged(IlBoolean = IlTrue);
};

// --------------------------------------------------------------------------
#define ILVST_PROPERTY_ACCESSOR_EXP(classname, inspectedObjectType, inspectedObjectVar, ilvValueVar, expression_get, expression_set) \
class classname : \
public IlvStICombinedAccessor \
{ \
public: \
    classname(IlvStIPropertyAccessor* accessor = 0, \
	      const char* name = 0, \
	      UpdateMode updateMode = NoUpdate, \
	      BuildMode buildMode = None ): \
	   IlvStICombinedAccessor(accessor, updateMode, buildMode, name) {} \
\
protected: \
    inspectedObjectType* _getInspectedObject() \
    {   IlvStIProperty* property = (_accessor? _accessor->get() : 0); \
	return (property? (inspectedObjectType*)property->getPointer() : 0); } \
    virtual IlvStIProperty* getOriginalValue() \
    { \
	inspectedObjectType* inspectedObjectVar = _getInspectedObject(); \
	if (!inspectedObjectVar) return 0; \
	IlvStValue ilvValueVar; \
	expression_get; \
	return ILVI_NEW IlvStIValueProperty(ilvValueVar, "value"); \
    } \
    virtual void applyValue(IlvStIProperty* property) \
    { \
	inspectedObjectType* inspectedObjectVar = _getInspectedObject(); \
	if (!inspectedObjectVar) return; \
	IlvValue ilvValueVar; \
	property->getValue(value); \
	expression_set; \
    } \
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_clselec)
#endif /* !__IlvSt_Inspectors_Clselec_H */
