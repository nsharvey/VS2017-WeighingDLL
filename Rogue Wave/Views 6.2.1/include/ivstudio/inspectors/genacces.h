// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/genacces.h
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
// Declaration of IlvStIPropertyAccessor classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Genacces_H
#define __IlvSt_Inspectors_Genacces_H

#if !defined(__IlvSt_Inspectors_Genprop_H)
#  include <ivstudio/inspectors/genprop.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif

class IlvStIPropertyAccessor;
class IlvStIPropertyEditor;
class IlvStIValidator;
class IlvStIEditor;
class IlvStIPrecondition;
class IlvStIError;
class IlvStIErrorManager;

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIAccessor
    : public IlvStNamedObject
{
    IlvDeclareInspClassInfo();

public:
    virtual ~IlvStIAccessor();

    virtual IlBoolean	initialize();

    virtual IlBoolean	apply();

    void		lock();
    void		unLock();

    enum BuildMode {
	None     = 0,
	Create   = 16,
	Copy     = 32,
	CreateAndCopy = 48
    };

    BuildMode		getBuildMode() const;
    void		setBuildMode(BuildMode mode);

    enum UpdateMode {
	NoUpdate  = 0,
	OnApply   = 1,
	Immediate = 2,
	Inherited = 4
    };
    virtual UpdateMode	getUpdateMode() const;
    void		setUpdateMode(UpdateMode updateMode);

    IlBoolean		isModified() const;
    IlBoolean		hadBeenModified() const;
    void		setModified(IlBoolean = IlTrue,
				    IlBoolean = IlFalse);

    enum DependencyMode {
	InitializeAfter  = 1,
	InitializeBefore = 2,
	ApplyBefore      = 4,
	ApplyAfter       = 8,
	NoApply          = 16,
	Default          = 5,
	InitializeAndApplyBefore = 6
    };
    void		addDependentAccessor(IlvStIAccessor* acc,
					     DependencyMode mode = Default);
    IlBoolean		removeDependentAccessor(IlvStIAccessor* acc);

    DependencyMode	getDependencyMode(const IlvStIAccessor*) const;
    IlBoolean		setDependencyMode(const IlvStIAccessor*,
					  DependencyMode);

    IlvStIAccessor*	getDependentAccessor(const char* name) const;
    IlvStIAccessor*	findDependentAccessor(const char* name) const;
    IlvStIAccessor**	getDependentAccessors(IlUInt& count) const;

    void		addEditor(IlvStIEditor* edt);
    IlBoolean		removeEditor(IlvStIEditor* edt);
    IlUInt		getNumberOfEditors() const;
    IlvStIEditor*	getEditor(IlUInt index) const;
    IlvStIEditor*	findEditor(const char* name) const;
    virtual IlvStIEditor*	findFirstEditor() const;

    virtual IlvStIError*	check() const;
    virtual IlvStIError*
			checkAll(const IlvStIAccessor** accessor,
				 IlBoolean modifiedOnly = IlTrue) const;

    virtual void	displayError(IlvStIError*,
				     IlBoolean = IlTrue) const;

protected:
    IlvStIAccessor(const char* name = 0,
		   UpdateMode mode = NoUpdate,
		   BuildMode build = None);

    IlUInt		_nLocks;
    IlInt		_mode;
    IlAny		_unamed;

    // ----------------------------------------------------------------------
    // Modification flag
    enum ModifFlag { NONE = 0, MODIFIED = 1, HAD_BEEN_MODIFIED } _modified;
    void		cleanHadBeenModified();

    // ----------------------------------------------------------------------
    // Dependent accessor's managment
    class DependentNode {
    public:
	IlvStIAccessor* _accessor;
	DependencyMode  _mode;

	DependentNode(IlvStIAccessor* accessor, DependencyMode mode):
	    _accessor(accessor), _mode(mode) {}
    };

    DependentNode*	getDependentNode(IlUInt index) const
			{
			    return (DependentNode*)_dependentAccessors[index];
			}

    // Must returns an IlAny instead of a DependentNode* (some unix
    // compilers)
    IlAny		getDependentNode(const char*) const;

    // Must returns an IlAny instead of a DependentNode* (some unix
    // compilers)
    IlAny		getDependentNode(const IlvStIAccessor*) const;
    IlvStIAccessor*	getAccessorFromIndex(IlUInt index) const
	{ return getDependentNode(index)->_accessor; }

    IlArray		_dependentAccessors;
    void		initializeDependentAccessors();

    // ----------------------------------------------------------------------
    // Depedent editors managment
    IlArray		_editors;
    void		initializeEditors(IlvStIEditor* = 0);
    void		updateEditorModifiedState(IlvStIEditor* = 0);

    void		initializeDepedencies(IlvStIEditor* = 0);

    // ----------------------------------------------------------------------
    // Protected methods to be overriden
    virtual void	modified(IlvStIAccessor*, IlvStIAccessor*);

    // Called by initialize and doApply: initialize _current and
    // _original members
    virtual IlBoolean	doInitialize() = 0;
    // _intialize + doInitialize of depedences
    IlBoolean		doInitializeAll();
    // Called by apply to apply specifics data
    virtual void	doApply() = 0;

    virtual IlvStIErrorManager*	getErrorManager() const;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyAccessor
    : public IlvStIAccessor
{
    IlvDeclareInspClassInfo();

public:
    virtual ~IlvStIPropertyAccessor();

    virtual IlBoolean	initialize();
    virtual IlBoolean	isInitialized() const;

    virtual IlvStIProperty*	get();
    virtual void	set(const IlvStIProperty* prop,
			    IlvStIEditor* editor);

    enum PropertyStatus {
	Uninitialized = -1,
	Inaccessible = 0,
	ReadWrite = 1,
	ReadOnly = 2
    };
    PropertyStatus	getPropertyStatus() const;

    virtual IlBoolean	isReadWrite() const;
    virtual IlBoolean	isReadOnly() const;

    IlvStIValidator*	getValidator() const;
    void		setValidator(IlvStIValidator* validator);

    virtual IlvStIError*	checkValue(const IlvStIProperty* prop) const;

    virtual IlvStIError*	check() const;

    IlvStIPrecondition*		getPrecondition() const;
    void		setPrecondition(IlvStIPrecondition* precond);

    IlvStIPropertyAccessor*	getPreviewAccessor() const;
    void		setPreviewAccessor(IlvStIPropertyAccessor* accessor);
    void		setPreviewValueAccessor(IlvStIPropertyAccessor*,
						const IlSymbol*);

protected:
    IlvStIPropertyAccessor(const char* name = 0,
			   UpdateMode updateMode = NoUpdate,
			   BuildMode buildMode = None);

    // Methods used in mode != Copy, values used in inspected objects can
    // directly be used and modified in editors (as IlvValue, integers, ...)
    // In most cases, those two methods needs to be overriden
    virtual IlvStIProperty*	getOriginalValue();

    virtual void		applyValue(IlvStIProperty* prop);

    // Methods used in mode == Copy, values used in inspected objects can
    // not directly be used and modified in editors.
    // For example, some values stored in protected pointers, have to be copied
    // and replaced when applying, as studio properties.
    //
    // By default calls getOriginalValue
    virtual const IlvStIProperty*	safeGetOriginalValue();

    virtual
    IlvStIProperty*	copyProperty(const IlvStIProperty* property);

    // By default calls applyValue
    virtual void	replaceValue(IlvStIProperty*,
				     IlvStIProperty*);

    // Called by apply and set methods
    virtual void	applyProperty(const IlvStIProperty* = 0);

    virtual
    IlvStIProperty*	createDefaultProperty() const;

    // Called by initialize and doApply: initialize _current and
    // _original members
    virtual IlBoolean	doInitialize();

    // Called by apply and set methods
    virtual void	doApply() { applyProperty(); }
    virtual IlBoolean	getValidateOnApply() const;

    friend class IlvStICombinedAccessor;

    IlvStIProperty*		_original;
    IlvStIProperty*		_current;
    PropertyStatus		_propertyStatus;
    IlvStIValidator*		_validator;
    IlvStIPrecondition*		_precondition;
    IlvStIPropertyAccessor*	_previewAccessor;

#ifdef ILVALLOCCHECK
public:
    virtual void	dump(ILVSTDPREF ostream&);
#endif
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICombinedAccessor
    : public IlvStIPropertyAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStICombinedAccessor(IlvStIPropertyAccessor* accessor = 0,
			   UpdateMode updateMode = NoUpdate,
			   BuildMode buildMode = None,
			   const char* name = 0);
    virtual ~IlvStICombinedAccessor();

    // ----------------------------------------------------------------------
    virtual IlBoolean	initialize();
    virtual void	set(const IlvStIProperty*, IlvStIEditor*);
    virtual UpdateMode	getUpdateMode() const;

    IlvStIPropertyAccessor*	getObjectAccessor() const;

    void		setObjectAccessor(IlvStIPropertyAccessor*);

protected:
    IlAny		getInspectedObject();

    // Need to override in most cases
    virtual IlvStIProperty*	getOriginalValue();
    virtual IlvStIProperty*	createDefaultProperty() const;
    virtual void		modified(IlvStIAccessor*, IlvStIAccessor*);

    virtual
    IlvStIErrorManager*	getErrorManager() const;

    IlvStIPropertyAccessor*	_accessor;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIValueInterAccessor
    : public IlvStIPropertyAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIValueInterAccessor(const char* = 0,
			     UpdateMode = Inherited,
			     BuildMode = None);
    virtual ~IlvStIValueInterAccessor();

    // ----------------------------------------------------------------------
    // Value Interface managment
    virtual IlvValueInterface*	getValueInterface() const
	{ return 0; }

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIGraphicContainerAccessor class
class IlvGraphic;
class IlvGraphicHolder;

class ILVINSPCLASS IlvStIGraphicContainerAccessor
    : public IlvStIValueInterAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIGraphicContainerAccessor(IlvGraphicHolder* holder = 0,
				   const char* name = 0,
				   UpdateMode updateMode = Inherited,
				   BuildMode buildMode = None)
    : IlvStIValueInterAccessor(name, updateMode, buildMode),
      _holder(holder),
      _graphic(0) {}

    // ----------------------------------------------------------------------
    // Value Interface managment
    virtual IlvValueInterface*	getValueInterface() const;

    virtual IlvGraphic*		getGraphic();

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);

    IlvGraphicHolder* _holder;
    IlvGraphic*       _graphic;
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStICombinedValueInterAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStICombinedValueInterAccessor(IlvStIPropertyAccessor* = 0,
				     const char* = 0,
				     UpdateMode = Inherited,
				     BuildMode = None);
    virtual ~IlvStICombinedValueInterAccessor();

protected:
    virtual IlvValueInterface*	getValueInterface() const;
    virtual IlvStIProperty*	getOriginalValue();
    virtual void		applyValue(IlvStIProperty*);
};

// --------------------------------------------------------------------------
// IlvStIAgregateFieldAccessor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIAgregateFieldAccessor
    : public IlvStICombinedAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIAgregateFieldAccessor(IlvStIPropertyAccessor* = 0,
	                        const char* = 0,
			        UpdateMode = Inherited,
				BuildMode = None);
    virtual ~IlvStIAgregateFieldAccessor();

protected:
    virtual IlvStIProperty*	getOriginalValue();
    virtual void	      replaceValue(IlvStIProperty*, IlvStIProperty*);

    virtual const IlSymbol*	getFieldName() const;
    IlvStIAgregateProperty*	getAgragegateProperty();
};

// --------------------------------------------------------------------------
// IlvStIAccessorSet
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIAccessorSet
    : public IlvStIAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIAccessorSet(const char* = 0,
		      UpdateMode = Inherited,
		      BuildMode = None);
    virtual ~IlvStIAccessorSet();

    // ----------------------------------------------------------------------
    // Adding removing accessors
    void		addAccessor(IlvStIAccessor*);
    IlvStIAccessor*	getAccessor(const char*) const;
    void		removeAccessor(IlvStIAccessor*);

protected:
    virtual IlBoolean	doInitialize();
    virtual void	doApply();
};

// --------------------------------------------------------------------------
// class IlvStIAnyAccessor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIAnyAccessor
    : public IlvStIPropertyAccessor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIAnyAccessor(IlAny,
		      const char* = 0,
		      UpdateMode = NoUpdate,
		      BuildMode = None);

protected:
    virtual IlvStIProperty*	getOriginalValue();

    IlAny		_data;
};

// --------------------------------------------------------------------------
// Macros to declare default accessors

#define ILVST_DECLARE_PROPERTY_ACCESSOR(classname, inspectedObjectType) \
class ILVINSPCLASS classname : \
public IlvStICombinedAccessor \
{ \
    IlvDeclareInspClassInfo(); \
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
    virtual IlvStIProperty* getOriginalValue(); \
    virtual void applyValue(IlvStIProperty* property); \
};

#define ILVST_IMPLEMENT_GET_PROPERTY(classname, inspectedObjectType, getMethod) \
    IlvStIProperty* classname::getOriginalValue() \
    { \
	inspectedObjectType* inspectedObject = _getInspectedObject(); \
	if (!inspectedObject) return 0; \
	return ILVI_NEW IlvStIValueProperty(inspectedObject->getMethod(), "value"); \
    } \

#define ILVST_IMPLEMENT_SET_PROPERTY(classname, inspectedObjectType, setMethod) \
    void classname::applyValue(IlvStIProperty* property) \
    { \
	inspectedObjectType* inspectedObject = _getInspectedObject(); \
	if (!inspectedObject) return; \
	IlvValue value; \
	inspectedObject->setMethod(property->getValue(value)); \
    } \

#define ILVST_PROPERTY_ACCESSOR(classname, inspectedObjectType, getMethod, setMethod) \
class ILVINSPCLASS classname : \
public IlvStICombinedAccessor \
{ \
    IlvDeclareInspClassInfo(); \
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
	inspectedObjectType* inspectedObject = _getInspectedObject(); \
	if (!inspectedObject) return 0; \
	return ILVI_NEW IlvStIValueProperty(inspectedObject->getMethod(), "value"); \
    } \
    virtual void applyValue(IlvStIProperty* property) \
    { \
	inspectedObjectType* inspectedObject = _getInspectedObject(); \
	if (!inspectedObject) return; \
	IlvValue value; \
	inspectedObject->setMethod(property->getValue(value)); \
    } \
};

#define ILVST_PROPERTY_ACCESSOR_EXT(classname, inspectedObjectType, inspectedObjectVar, ilvValueVar, expression_get, expression_set) \
class ILVINSPCLASS classname : \
public IlvStICombinedAccessor \
{ \
    IlvDeclareInspClassInfo(); \
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
IlvDECLAREINITINSPCLASS(sti_genacces)
#endif /* !__IlvSt_Inspectors_Genacces_H */
