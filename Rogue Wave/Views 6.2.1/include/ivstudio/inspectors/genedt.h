// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/genedt.h
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
// Declaration of generic editor classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Genedt_H
#define __IlvSt_Inspectors_Genedt_H

#if !defined(__IlvSt_Inspectors_Genprop_H)
#  include <ivstudio/inspectors/genprop.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif

// --------------------------------------------------------------------------
#if !defined(__IlvSt_Genacces_H)
class IlvStIAccessor;
class IlvStIPropertyAccessor;
class IlvStIListAccessor;
#endif

class IlvStIEditor;
class IlvStIProxyListGadget;
class IlvGraphicHolder;
class IlvGraphic;
class IlvGadget;
class IlvGadgetItem;
class IlvDisplay;
class IlvTextField;
class IlvToggle;
class IlvSlider;
class IlvPalette;

#define __BUG_CALLBACK_CALLED_ON_INIT

class ILVINSPCLASS IlvStIEditor : public IlvStNamedObject 
{
    IlvDeclareInspClassInfo();
public:
    virtual ~IlvStIEditor();

    virtual IlBoolean	initialize() = 0;

    virtual IlBoolean	apply() = 0;

    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);

    enum State { 
	Active, 
	Unactive, 
	Unsensitive 
    };

    virtual void	setState(State state = Active,
				 IlBoolean redraw = IlTrue);

    virtual void	empty();

    virtual void	setFocus(IlBoolean focus = IlTrue);

    virtual void	setVisible(IlBoolean visible = IlTrue);

    virtual IlBoolean	isVisible() const;

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void	createEditorObjects(IlvDisplay*,
					    IlArray&,
					    IlArray&)
    {}

    IlvStIEditor*	getOwner() const;

    void		setOwner(IlvStIEditor* editor);

    enum NotificationMode { 
	AsOwner = 0, 
	Default = 1, 
	Immediate = 2 
    };

    NotificationMode	getNotificationMode() const;
    void		setNotificationMode(NotificationMode mode);

    IlBoolean		isReadOnly() const { return _readOnly; }
    void		setReadOnly(IlBoolean val) { _readOnly = val; }

    virtual IlBoolean	isModified() const;
    virtual void	setModified(IlBoolean modified = IlTrue);

    const IlvStIEditor*	findEditor(const char* name) const;

    IlvStIEditor*	findEditor(const char* name);

    const IlvStIEditor*	getRootEditor() const;

    IlAny		getProperty(const IlSymbol* name) const;

    IlAny*		getProperties(const IlSymbol* name,
				      IlUInt& count) const;

    void		setProperty(const IlSymbol* name, IlAny property);

    void		addProperty(const IlSymbol* name, IlAny property);

    IlBoolean		propertyExists(const IlSymbol* name) const;

    IlBoolean		removeProperties(const IlSymbol* name);

    virtual IlvStIPropertyAccessor*	getAccessor() const;

    virtual void	setAccessor(IlvStIPropertyAccessor*){}

    virtual IlvStIPropertyAccessor*	getPreviewAccessor() const { return 0; }
    virtual void	setPreviewAccessor(IlvStIPropertyAccessor*){}
    void		setPreviewValueAccessor(IlvStIPropertyAccessor*,
						const IlSymbol*);

    // ----------------------------------------------------------------------
    virtual IlvDisplay* getDisplay() const { return 0; }

protected:
    IlvStIEditor(const char* name = 0, NotificationMode mode = AsOwner);

    // ----------------------------------------------------------------------
    // Data
    IlvStIEditor*	_owner;
    NotificationMode	_notifMode;
    IlBoolean		_readOnly;
    IlvHashTable	_properties;

    void		setCallbackProperty(const IlSymbol* cbValue,
					    IlAny callback,
					    const IlSymbol* cbParamValue = 0,
					    IlAny param = 0);

protected:
    virtual IlvStIEditor*	_getEditor(const char*) const;

    static void		SetState(State, IlvGraphic*);
};

class ILVINSPCLASS IlvStIEditorSet : public IlvStIEditor 
{
    IlvDeclareInspClassInfo();
public:
    IlvStIEditorSet(const char* name = 0, NotificationMode mode = AsOwner);
    ~IlvStIEditorSet();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();
    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);
    virtual void	setState(State = Active, IlBoolean bRedraw = IlTrue);
    virtual void	empty();
    virtual void	setFocus(IlBoolean bFocus = IlTrue);
    virtual void	setVisible(IlBoolean = IlTrue);
    virtual IlBoolean	isVisible() const;

    // ----------------------------------------------------------------------
    // Mode managment
    virtual IlBoolean	isModified() const;

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void	createEditorObjects(IlvDisplay* display,
					    IlArray& labels,
					    IlArray& editors);
    // ----------------------------------------------------------------------
    // Editor managment
    virtual void	addEditor(IlvStIEditor* editor);
    virtual IlBoolean	removeEditor(const char* name,
				     IlBoolean del = IlTrue);
    virtual IlBoolean	removeEditor(IlvStIEditor* editor,
				     IlBoolean del = IlTrue);
    IlvStIEditor* const*	getEditors(IlUInt& count) const;

    IlvStIEditor*	link(const char* gadgetName,
			     IlvStIPropertyAccessor* graphicAccessor,
			     const IlSymbol* valueName,
			     IlvStIEditor::NotificationMode mode =
			     IlvStIEditor::AsOwner);
    IlvStIEditor*	link(const char* gadgetName,
			     IlvStIPropertyAccessor* accessor,
			     IlvStIEditor::NotificationMode mode =
			     IlvStIEditor::AsOwner);

    // ----------------------------------------------------------------------
    virtual IlvGraphic*	createObject(IlvDisplay*, const char* lable = 0);
    virtual IlvDisplay*	getDisplay() const;

protected:
    virtual IlvStIEditor*	_getEditor(const char*) const;

    IlArray		_editors;

};

// --------------------------------------------------------------------------
// class IlvStIPropertyEditor
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStIPropertyEditor : public IlvStIEditor
{
    IlvDeclareInspClassInfo();
public:
    ~IlvStIPropertyEditor();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();

    // ----------------------------------------------------------------------
    // Automatic editor generation
    virtual void	createEditorObjects(IlvDisplay* display,
					    IlArray& labels,
					    IlArray& editors);

    // ----------------------------------------------------------------------
    // Mode managment
    virtual IlBoolean	isModified() const;

    // ----------------------------------------------------------------------
    // Accessor managment
    virtual IlvStIPropertyAccessor*	getAccessor() const;
    virtual void	setAccessor(IlvStIPropertyAccessor* accessor);

    virtual IlvStIPropertyAccessor*	getPreviewAccessor() const;
    virtual void	setPreviewAccessor(IlvStIPropertyAccessor*);

    // ----------------------------------------------------------------------
    // State callback managment
    typedef State (*StateCallback)(const IlvStIProperty* property, IlAny);

    IL_DEFINEFPTRTOANYCAST(StateCallback);

    void		setStateCallback(StateCallback, IlAny = 0);
    StateCallback	getStateCallback() const;
    IlAny		getStateCallbackParam() const;

    // ----------------------------------------------------------------------
    // Properties symbols
    static IlSymbol*	_StateCallbackSymbol;
    static IlSymbol*	_StateParamSymbol;

protected:
    IlvStIPropertyEditor(const char* name = 0,
			 IlvStIPropertyAccessor* accessor = 0,
			 NotificationMode = AsOwner);

    IlvStIPropertyAccessor*	_accessor;

    virtual void	createEditorObject(IlvDisplay*,
					   IlArray&,
					   IlArray&){}
    virtual void	empty(){}
    virtual State	getStateFromProperty(const IlvStIProperty* p) const;
};

// --------------------------------------------------------------------------
// class IlvStIPropertyGraphicEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyGraphicEditor : public IlvStIPropertyEditor
{
    IlvDeclareInspClassInfo();

public:
    ~IlvStIPropertyGraphicEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();
    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);
    virtual void	setState(State = Active, IlBoolean bRedraw = IlTrue);
    virtual void	setFocus(IlBoolean bFocus = IlTrue);
    virtual void	setVisible(IlBoolean = IlTrue);
    virtual IlBoolean	isVisible() const;

    // ----------------------------------------------------------------------
    typedef IlBoolean (*TranslatorValueCallback)(IlvStIProperty* property,
						 IlvValue&,
						 IlBoolean,
						 IlAny);
    // Bool param = true if input, false if output

    IL_DEFINEFPTRTOANYCAST(TranslatorValueCallback);

    void		setTranslatorCallback(TranslatorValueCallback tcb,
					      IlAny param = 0);

    // ----------------------------------------------------------------------
    // Specific accessors
    IlvGraphic*		getGraphic() const { return _graphic; }
    IlvGadget*		getGadget() const;
    IlvPalette*		getPalette() const;

    virtual IlvDisplay*	getDisplay() const;

    void		setValueName(IlSymbol* name) { _valueName = name; }

    // ----------------------------------------------------------------------
    // Properties symbols
    static IlSymbol*	_TranslatorCallbackValue;
    static IlSymbol*	_TranslatorParamValue;

protected:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPropertyGraphicEditor(const char* name = 0,
			        IlvStIPropertyAccessor* accessor = 0,
			        NotificationMode = AsOwner);

    // ----------------------------------------------------------------------
    // Graphic managment
    IlvGraphicHolder*	_holder;
    IlvGraphic*		_graphic;
    IlvValue		_initialValue;
    IlSymbol*		_valueName;
#ifdef __BUG_CALLBACK_CALLED_ON_INIT
    IlBoolean		_initializingGadget;
#endif
    virtual void	setGraphic(IlvGraphic*, IlvGraphicHolder* = 0);
    virtual
    const IlvStIProperty* readGraphicProperty(IlvStIPropertyAccessor*);
    virtual IlvValue&	queryGraphicValue(IlvValue&) const;
    virtual const char*	getGraphicClassName() const = 0;
    virtual IlSymbol*	getCallbackType() const = 0;
    virtual IlSymbol*	getValueName() const { return _valueName; }
    virtual IlBoolean	hasChanged(IlBoolean = IlTrue);

    virtual const char*	getGraphicName() const;

    static IlvDisplay*	GetGraphicDisplay(IlvGraphic*, IlvGraphicHolder*);
    static IlvPalette*	GetGraphicPalette(IlvGraphic*, IlvGraphicHolder*);
    static void		GraphicNotificationCallback(IlvGraphic*, IlAny arg);
    static void		GraphicNotificationCallback2(IlvGraphic*, IlAny arg);
    static void		GraphicNotificationCallback3(IlvGraphic*, IlAny arg);
    virtual void	onGraphicNotification();

    // ----------------------------------------------------------------------
    virtual void	getPropertyValue(IlvStIProperty*, IlvValue&);
    virtual void	setPropertyValue(IlvStIProperty*, IlvValue&);

    // ----------------------------------------------------------------------
    // Graphic generation
    virtual void	createEditorObject(IlvDisplay* display,
					   IlArray& labels,
					   IlArray& editors);
    virtual IlvGraphic*	createGraphic(IlvDisplay* display,
				      const char* label) = 0;
};

// --------------------------------------------------------------------------
// class IlvStIPropertyTextEditor
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStIPropertyTextEditor
    : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIPropertyTextEditor(const char* name = 0,
			     IlvStIPropertyAccessor* accessor = 0,
			     NotificationMode = AsOwner);
    ~IlvStIPropertyTextEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Specific accessors
    const char*		getLabel() const;
    void		setLabel(const char*);
    IlvTextField*	getTextField() const;

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual IlSymbol*	getCallbackType() const;
    virtual void	empty();

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
// class IlvStINumberFieldEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStINumberFieldEditor : public IlvStIPropertyTextEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStINumberFieldEditor(const char* name = 0,
			    IlvStIPropertyAccessor* accessor = 0,
		   	    NotificationMode = AsOwner);
    ~IlvStINumberFieldEditor();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual void	empty();
    virtual IlvValue&	queryGraphicValue(IlvValue&) const;

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
// class IlvStIPropertyColorEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyColorEditor : public IlvStIPropertyTextEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIPropertyColorEditor(const char* name = 0,
			      IlvStIPropertyAccessor* accessor = 0,
			      NotificationMode = AsOwner);
    ~IlvStIPropertyColorEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	initialize();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
    virtual void	onGraphicNotification();
    void		updateTextFieldColors();
    virtual void	setGraphic(IlvGraphic*, IlvGraphicHolder* = 0);

    static void		ButtonPushedCallback(IlvGraphic*, IlAny);
    virtual void	onButtonPushed();
};

// --------------------------------------------------------------------------
// class IlvStIPropertyToggleEditor
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyToggleEditor
    : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIPropertyToggleEditor(const char* name = 0,
			       IlvStIPropertyAccessor* accessor = 0,
			       NotificationMode = AsOwner);
    ~IlvStIPropertyToggleEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual void	setState(State = Active, IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Specifique accessors
    IlBoolean		getToggleState() const;
    void		setToggleState(IlBoolean);
    IlvToggle*		getToggle() const;

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual IlSymbol*	getCallbackType() const;
    virtual void	empty();

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
// class IlvStIPropertySliderEditor
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStISliderEditor : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStISliderEditor(const char* name = 0,
		       IlvStIPropertyAccessor* accessor = 0,
		       NotificationMode = AsOwner);
    ~IlvStISliderEditor();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

    // ----------------------------------------------------------------------
    // Specifique accessors
    IlInt		getSliderValue() const;
    void		setSliderValue(IlInt);
    IlvSlider*		getSlider() const;

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual IlSymbol*	getCallbackType() const;
    virtual void	empty();
    virtual IlvValue&	queryGraphicValue(IlvValue&) const;

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertyFileEditor : public IlvStIPropertyTextEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIPropertyFileEditor(const char* name = 0,
			     IlvStIPropertyAccessor* accessor = 0,
			     NotificationMode = AsOwner);
    ~IlvStIPropertyFileEditor();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual void	setGraphic(IlvGraphic*, IlvGraphicHolder* = 0);

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvPropertyDirectoryEditor : public IlvStIPropertyFileEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvPropertyDirectoryEditor(const char* name = 0,
			       IlvStIPropertyAccessor* accessor = 0,
			       NotificationMode = AsOwner);
    ~IlvPropertyDirectoryEditor();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);

    // ----------------------------------------------------------------------
    // Last directory separator accessor
    IlBoolean		keepLastSeparator() const { return _keepEndSeparator; }
    void		setKeepLastSeparator(IlBoolean bKeep)
			{
			    _keepEndSeparator = bKeep;
			}
    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;
    IlBoolean		_keepEndSeparator;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
typedef void (*FillerCallback)(IlvStIProxyListGadget&, IlAny);

IL_DEFINEFPTRTOANYCAST(FillerCallback);

typedef IlBoolean (*TranslatorListCallback)(IlvStIProperty* property,
					    IlvStIProxyListGadget* list,
					    IlBoolean,
					    IlAny);
// Bool param = true if input, false if output

IL_DEFINEFPTRTOANYCAST(TranslatorListCallback);

class ILVINSPCLASS IlvStIListEditor : public IlvStIPropertyEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIListEditor(const char* name = 0,
		     IlvStIPropertyAccessor* accessor = 0,
		     NotificationMode = AsOwner);
    ~IlvStIListEditor();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();
    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);
    virtual void	setState(State = Active,
				 IlBoolean bRedraw = IlTrue);
    virtual void	setFocus(IlBoolean bFocus = IlTrue);
    virtual void	setVisible(IlBoolean = IlTrue);
    virtual IlBoolean	isVisible() const;

    // ----------------------------------------------------------------------
    void		setFillerCallback(FillerCallback, IlAny param = 0);
    void		setListTranslator(TranslatorListCallback,
					  IlAny param = 0);

    void		setFillAlways(IlBoolean = IlTrue);
    IlBoolean		getFillAlways() const;

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

    // ----------------------------------------------------------------------
    // Properties symbols
    static IlSymbol*	_FillerCallbackValue;
    static IlSymbol*	_FillerParamValue;
    static IlSymbol*	_TranslatorListCallbackValue;
    static IlSymbol*	_TranslatorListParamValue;
    static IlSymbol*	_FillAlwaysValue;

protected:
    static IlvDim	_DefaultWidth;
    IlString		_initialText;

    IlvStIProxyListGadget*	_pxyList;

    virtual void	createEditorObject(IlvDisplay* display,
					   IlArray& labels,
					   IlArray& editors);
    virtual const char*	getGraphicName() const;
    virtual void	empty();

    virtual void	fillListGadget();
    virtual void	translate(IlvStIProperty*, IlBoolean bInput);

    // ----------------------------------------------------------------------
    // Notification
    static void		ListNotificationCallback(IlvGraphic*, IlAny arg);
    virtual void	onListNotification();

    const IlvStIProperty*	readListProperty(IlvStIPropertyAccessor*);
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISelectorEditor : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStISelectorEditor(const char* name = 0,
		         IlvStIPropertyAccessor* accessor = 0,
		         NotificationMode = AsOwner);
    ~IlvStISelectorEditor();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual IlSymbol*	getCallbackType() const;
    virtual void	empty();

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStISpinBoxEditor : public IlvStIPropertyGraphicEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStISpinBoxEditor(const char* name = 0,
		        IlvStIPropertyAccessor* accessor = 0,
		        NotificationMode = AsOwner);
    ~IlvStISpinBoxEditor();

    // ----------------------------------------------------------------------
    // Default width accessors
    static IlvDim	GetDefaultWidth() {return _DefaultWidth; }
    static void		SetDefaultWidth(IlvDim dwidth)
			{
			    _DefaultWidth = dwidth;
			}

protected:
    static IlvDim	_DefaultWidth;

    // ----------------------------------------------------------------------
    // Overridables
    virtual const char*	getGraphicClassName() const;
    virtual IlSymbol*	getCallbackType() const;
    virtual void	empty();

    virtual void	setGraphic(IlvGraphic*, IlvGraphicHolder* = 0);
    virtual IlvValue&	queryGraphicValue(IlvValue&) const;
    virtual void	getPropertyValue(IlvStIProperty*, IlvValue&);

    virtual IlvGraphic*	createGraphic(IlvDisplay* display, const char* label);
};

class ILVINSPCLASS IlvStIPropertyEditorSet : public IlvStIEditorSet 
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertyEditorSet(const char* name = 0,
			    IlvStIPropertyAccessor* accessor = 0,
			    NotificationMode mode = AsOwner);
    ~IlvStIPropertyEditorSet();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();

    virtual
    IlvStIPropertyAccessor*	getAccessor() const { return _accessor; }
    virtual void	setAccessor(IlvStIPropertyAccessor*);

    virtual void	setPreviewAccessor(IlvStIPropertyAccessor*);
    virtual
    IlvStIPropertyAccessor*	getPreviewAccessor() const
				{
				    return _previewAccessor;
				}

    // ----------------------------------------------------------------------
    // Mode managment
    IlBoolean		isModified() const;

protected:
    IlvStIPropertyAccessor*	_accessor;
    IlvStIPropertyAccessor*	_previewAccessor;
};

class ILVINSPCLASS IlvStIDefaultEditorBuilder : public IlvStIPropertyEditorSet 
{
    IlvDeclareInspClassInfo();

public:
    IlvStIDefaultEditorBuilder(const char* name = 0,
			       IlvStIPropertyAccessor* accessor = 0,
			       NotificationMode mode = AsOwner);
    ~IlvStIDefaultEditorBuilder();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();
    virtual IlBoolean	connectHolder(IlvGraphicHolder* holder);

protected:
    virtual const char*	getGraphicName() const;

    virtual
    IlvStIPropertyEditor*	buildPropertyEditor(IlvGraphicHolder*) const;
};

// --------------------------------------------------------------------------
// class IlvStIExternalEditor
// --------------------------------------------------------------------------

class ILVINSPCLASS IlvStIExternalEditor : public IlvStIEditor
{
    IlvDeclareInspClassInfo();

public:
    IlvStIExternalEditor(const char* name = 0);
    ~IlvStIExternalEditor();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual IlBoolean	initialize();
    virtual IlBoolean	apply();

    // ----------------------------------------------------------------------
    // Mode managment
    virtual IlBoolean	isModified() const;
    IlBoolean		hadBeenModified() const;
    virtual void	setModified(IlBoolean = IlTrue);

    // ----------------------------------------------------------------------
    // Depend on accessor
    virtual IlvStIPropertyAccessor* getAccessor() const;
    virtual void	setAccessor(IlvStIPropertyAccessor*);

    void		setDependentOnAccessor(IlvStIAccessor*);
    IlvStIAccessor*	getDependentOnAccessor() const;

protected:
    virtual void	modified() const;

    IlvStIAccessor*	_interfaceAccessor;
    IlvStIAccessor*	_dependentOnAccessor;
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_genedt)
#endif /* !__IlvSt_Inspectors_Genedt_H */
