// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/stprop.h
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
// Declaration of Studio's property classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Stprop_H
#define __IlvSt_Stprop_H

#ifndef __Ilv_Base_Value_H
#  include <ilviews/base/value.h>
#endif
#ifndef __IlvSt_Object_H
#  include <ivstudio/object.h>
#endif

// --------------------------------------------------------------------------
class IlvStProperty;
class IlvStPropertySet;
class IlvStPropSetDescriptor;

typedef IlvStProperty* (*IlvStPropertyConstructor)(const IlSymbol*,
						   const IlvStPropertySet*);

typedef IlBoolean (*IlvStPropertySetFitler)(IlvStProperty*, IlAny);

IL_DEFINEFPTRTOANYCAST(IlvStPropertyConstructor);

class ILVSTUDIOCLASS IlvStProperty
: public IlvStObject 
{
public:
  const IlSymbol*	getKeyWordSymbol() const { return _keyword; }
  void		setKeyWordSymbol(const IlSymbol* kword)
    { _keyword = kword; }
  const char*		getKeyWordString() const
    { return _keyword ? _keyword->name() : 0; }
  void		setKeyWordString(const char* str)
    { _keyword = IlvGetSymbol(str); }
  IlBoolean		isPersistent() const { return _persistent; }
  void		setPersistent(IlBoolean val) { _persistent = val; }

  virtual const char* getName() const;

  virtual void	setName(const char* str);

  virtual const IlSymbol* getNameSymbol() const;

  virtual void	setNameSymbol(const IlSymbol* str);

  virtual void	writeValue(IL_STDPREF ostream&) const = 0;
  virtual IlBoolean	readValue(IL_STDPREF istream&) = 0;
  virtual IlvStProperty* copy() const = 0;
  virtual void copyFrom(const IlvStProperty*) = 0;
  virtual void resetFrom(const IlvStProperty*); // Different from copy from for property set
  virtual void	addedToSet(IlvStPropertySet*);
  virtual IlBoolean	isShared() const;

  virtual IlvValue& getValue(IlvValue& value) const;

  virtual void	setValue(const IlvValue& value);

  virtual const char*	getString() const;
  virtual void	setString(const char*);
  virtual const IlSymbol* getSymbol() const;
  virtual void	setSymbol(const IlSymbol*);
  virtual IlBoolean	getBoolean() const;
  virtual void	setBoolean(IlBoolean val);
  virtual IlInt	getInt() const;
  virtual void	setInt(IlInt val);
  virtual IlDouble	getDouble() const;
  virtual void	setDouble(IlDouble val);
  virtual IlAny	getAny() const;
  virtual void	setAny(IlAny val);

  virtual IlBoolean	isASet() const;

  static IlSymbol*	StringType()		{ return _S_String; }
  static IlSymbol*	SymbolType()		{ return _S_Symbol; }
  static IlSymbol*	IdentifierType()	{ return _S_Identifier; }
  static IlSymbol*	PathNameType()		{ return _S_PathName; }
  static IlSymbol*	IntType()		{ return _S_Int; }
  static IlSymbol*	BooleanType()		{ return _S_Boolean; }
  static IlSymbol*	DoubleType()		{ return _S_Double; }
  static IlSymbol*	SimpleListType()	{ return _S_SimpleList; }
  static IlSymbol*	BracketedListType()	{ return _S_BracketedList; }
  static IlSymbol*	PropertySetType()	{ return _S_PropertySet; }
  static IlSymbol*	PropertySetDefinitionType()
    { return _S_PropertySetDefinition; }

  static void		RegisterConstructor(const IlSymbol*,
					    IlvStPropertyConstructor);
  static IlvStPropertyConstructor GetConstructor(const IlSymbol*);
  static void	RegisterDescriptor(const IlSymbol*,
				   IlvStPropSetDescriptor*);
  static IlvStPropSetDescriptor* GetDescriptor(const IlSymbol*);
  static IlvStPropSetDescriptor* RemoveDescriptor(const IlSymbol*);
  static void AddObjectToDelete(IlvStObject*);

  static int		GlobalInit();
  static int		GlobalClean();

protected:
  IlvStProperty(const IlSymbol* name);
  IlvStProperty(const IlvStProperty& src);
  IlvStProperty(const char*);

  const IlSymbol* _keyword;
  IlBoolean	    _persistent;

  static IlBoolean	 _Initialized;
  static IlHashTable* _Constructors;
  static IlHashTable* _PropsDefs;
  static IlArray*	 _ObjectsToDelete;
  static IlSymbol* _S_String;
  static IlSymbol* _S_Identifier;
  static IlSymbol* _S_PathName;
  static IlSymbol* _S_Symbol;
  static IlSymbol* _S_Int;
  static IlSymbol* _S_Boolean;
  static IlSymbol* _S_Double;
  static IlSymbol* _S_SimpleList;
  static IlSymbol* _S_SimpleStructure;
  static IlSymbol* _S_BracketedList;
  static IlSymbol* _S_PropertySet;
  static IlSymbol* _S_PropertySetDefinition;

  static IlSymbol* _S_fields;
  static IlSymbol* _S_declarative;
  static IlSymbol* _S_structured;
  static IlSymbol* _S_bracketed;
  static IlSymbol* _S_separator;
  static IlSymbol* _S_headerSeparator;
  static IlSymbol* _S_stopCharacter;
  static IlSymbol* _S_indentLevelIncrement;
  static IlSymbol* _S_inheritFrom;

  static IlSymbol* _S_Default;
  static IlvStProperty* _IgnoredProperty;

  static IlvStPropSetDescriptor* _DefaultDef;
  static IlvStPropSetDescriptor* _SimpleListDef;
  static IlvStPropSetDescriptor* _SimpleStructureDef;
  static IlvStPropSetDescriptor* _BracketedListDef;

  static IlvValue*	_TmpValue;
}; // class IlvStProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStValueProperty
: public IlvStProperty {
public:
    IlvStValueProperty(const IlSymbol* name);
    IlvStValueProperty(const IlvStValueProperty&);

    virtual void	writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	readValue(IL_STDPREF istream&);
    virtual IlvStProperty* copy() const;
    virtual void copyFrom(const IlvStProperty*);

    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual const char* getString() const;
    virtual void	setString(const char* str);
    virtual IlBoolean	getBoolean() const;
    virtual void	setBoolean(IlBoolean val);
protected:
    IlvValue	_value;
}; // class IlvStValueProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStStringProperty
: public IlvStProperty {
public:
    IlvStStringProperty(const IlSymbol* name);
    IlvStStringProperty(const IlvStStringProperty&);

    virtual void	writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	readValue(IL_STDPREF istream&);
    virtual IlvStProperty* copy() const;
    virtual void copyFrom(const IlvStProperty*);

    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual const char* getString() const;
    virtual void	setString(const char* str);
    virtual IlBoolean	getBoolean() const;
    virtual void	setBoolean(IlBoolean val);
protected:
    IlvStString	_string;
}; // class IlvStStringProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStIdentifier
: public IlvStStringProperty {
public:
    IlvStIdentifier(const IlSymbol* name);
    IlvStIdentifier(const IlvStIdentifier&);

    virtual IlvStProperty*  copy() const;
    virtual void	    writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	    readValue(IL_STDPREF istream&);
}; // class IlvStIdentifier

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPathNameProperty
: public IlvStStringProperty {
public:
    IlvStPathNameProperty(const IlSymbol* name);
    IlvStPathNameProperty(const IlvStPathNameProperty&);
    virtual void	    writeValue(IL_STDPREF ostream&) const;
}; // class IlvStPathNameProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStIntProperty
: public IlvStProperty {
public:
    IlvStIntProperty(const IlSymbol* name);
    IlvStIntProperty(const IlvStIntProperty&);

    virtual IlvStProperty*  copy() const;
    virtual void copyFrom(const IlvStProperty*);
    virtual void	    writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	    readValue(IL_STDPREF istream&);

    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual IlInt	getInt() const;
    virtual void	setInt(IlInt);
protected:
    IlInt  _value;
}; // class IlvStIntProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStBooleanProperty
: public IlvStProperty {
public:
    IlvStBooleanProperty(const IlSymbol* name): IlvStProperty(name),
			_value(IlFalse) {}
    IlvStBooleanProperty(const IlvStBooleanProperty& src)
	: IlvStProperty(src), _value(src._value) {}

    virtual void	writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	readValue(IL_STDPREF istream&);
    virtual IlvStProperty* copy() const;
    virtual void copyFrom(const IlvStProperty*);

    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual const char*	getString() const;
    virtual void	setString(const char*);
    virtual IlBoolean	getBoolean() const;
    virtual void	setBoolean(IlBoolean val);
    virtual IlInt	getInt() const;
    virtual void	setInt(IlInt val);

protected:
    IlBoolean	_value;
}; // class IlvStBooleanProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSymbolProperty
: public IlvStProperty {
public:
    IlvStSymbolProperty(const IlSymbol* name);
    IlvStSymbolProperty(const IlvStSymbolProperty& src)
	: IlvStProperty(src), _value(src._value) {}

    virtual void	writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	readValue(IL_STDPREF istream&);
    virtual IlvStProperty* copy() const;
    virtual void copyFrom(const IlvStProperty*);

    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual const char*	getString() const;
    virtual void	setString(const char*);
    virtual const IlSymbol* getSymbol() const;
    virtual void	setSymbol(const IlSymbol*);
protected:
    const IlSymbol* _value;
}; // class IlvStSymbolProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDoubleProperty
: public IlvStProperty {
public:
    IlvStDoubleProperty(const IlSymbol* name);
    IlvStDoubleProperty(const IlvStDoubleProperty&);

    virtual IlvStProperty*  copy() const;
    virtual void copyFrom(const IlvStProperty*);
    virtual void	    writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	    readValue(IL_STDPREF istream&);

    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual IlDouble	getDouble() const;
    virtual void	setDouble(IlDouble);

protected:
    IlDouble _value;
}; // class IlvStDoubleProperty

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStAnyProperty
: public IlvStProperty {
public:
    IlvStAnyProperty(const IlSymbol* name) : IlvStProperty(name), _value(0)
	{ _persistent = IlFalse; }
    IlvStAnyProperty(const IlvStAnyProperty& src)
	: IlvStProperty(src), _value(src._value) {}
    IlvStAnyProperty(const char* name)
	: IlvStProperty(name), _value(0) { _persistent = IlFalse; }
    virtual void	writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean	readValue(IL_STDPREF istream&);
    virtual IlvStProperty* copy() const;
    virtual void copyFrom(const IlvStProperty*);
    virtual IlvValue&	getValue(IlvValue& value) const;
    virtual void	setValue(const IlvValue& value);
    virtual IlAny	getAny() const;
    virtual void	setAny(IlAny value);
protected:
    IlAny	_value;
}; // class IlvStAnyProperty

class ILVSTUDIOCLASS IlvStPropertySet
  : public IlvStProperty {
public:
  IlvStPropertySet(const IlSymbol* name);

  IlvStPropertySet(const char* name);

  IlvStPropertySet(const IlvStPropertySet&);
  virtual ~IlvStPropertySet();

  virtual const char*	getName() const;
  virtual void	setName(const char* str);

  virtual IlvStProperty*  createProperty(const IlSymbol* name)const;

  virtual IlBoolean getPropertyValue(const IlSymbol* name, IlvValue& value);

  virtual IlBoolean setPropertyValue(const IlSymbol* name,
				     const IlvValue& value);
  IlBoolean	getPropertyBoolean(const IlSymbol* name) const;
  IlBoolean	getPropertyBoolean(const char* name) const
    { return getPropertyBoolean(IlvGetSymbol(name)); }
  void	setPropertyBoolean(const IlSymbol*, IlBoolean);
  void	setPropertyBoolean(const char* name, IlBoolean value)
    { setPropertyBoolean(IlvGetSymbol(name), value); }
  const char*	getPropertyString(const IlSymbol* name) const;
  const char*	getPropertyString(const char* name) const
    { return getPropertyString(IlvGetSymbol(name)); }
  void	setPropertyString(const IlSymbol* name, const char*);
  void	setPropertyString(const char* name, const char* str)
    { setPropertyString(IlvGetSymbol(name), str); }
  IlInt	getPropertyInt(const IlSymbol* name) const;
  IlInt	getPropertyInt(const char* name) const
    { return getPropertyInt(IlvGetSymbol(name)); }
  void	setPropertyInt(const IlSymbol* name, IlInt);
  void	setPropertyInt(const char* name, IlInt value)
    { setPropertyInt(IlvGetSymbol(name), value); }
  IlAny	getPropertyAny(const IlSymbol* name) const;
  IlAny	getPropertyAny(const char* name) const
    { return getPropertyAny(IlvGetSymbol(name)); }
  void	setPropertyAny(const IlSymbol* name, IlAny value);
  void	setPropertyAny(const char* name, IlAny value)
    { setPropertyAny(IlvGetSymbol(name), value); }
  IlDouble	getPropertyDouble(const IlSymbol* name) const;
  IlDouble   getPropertyDouble(const char* name) const
    { return getPropertyDouble(IlvGetSymbol(name)); }
  void	setPropertyDouble(const IlSymbol* name, IlDouble val);
  void	setPropertyDouble(const char* name, IlDouble val)
    { setPropertyDouble(IlvGetSymbol(name), val); }
  virtual IlBoolean	isASet() const;
  virtual IlBoolean	isRepeatable(const IlSymbol*) const;

  virtual void		write(IL_STDPREF ostream& ostm) const;
  virtual void		writeHeader(IL_STDPREF ostream& ostm) const;
  virtual void		writeProperties(IL_STDPREF ostream& ostm) const;
  virtual void		writeValue(IL_STDPREF ostream&) const;
  virtual IlBoolean		read(IL_STDPREF istream& istm);
  virtual IlBoolean		readValue(IL_STDPREF istream&);
  virtual IlBoolean		readHeader(IL_STDPREF istream& istm);

  virtual IlvStProperty*  copy() const;
  virtual void copyFrom(const IlvStProperty*);
  virtual void resetFrom(const IlvStProperty*);
  void		    copyHeaders(const IlvStPropertySet&);
  virtual IlvStProperty*  readProperty(IL_STDPREF istream& istm, const IlSymbol*);
  IlvStProperty* makeProperty(const IlSymbol* pname)const;

  void	    clean();
  IlvStProperty*  take(IlUInt);
  IlUInt	    takeAll(IlArray&);

  IlUInt	    getLength() const { return _properties.getLength(); }
  IlUInt	    getIndex(const IlvStProperty*) const;
  IlUInt	    getFirstIndex(const IlSymbol* name,
	                          IlUInt start = 0) const;
  IlUInt	    getLastIndex(const IlSymbol* name,
				 IlUInt start = (IlUInt)-1) const;
  IlvStProperty*  getProperty(const IlSymbol* name) const;
  IlvStProperty*  getProperty(const char* name) const
    { return getProperty(IlvGetSymbol(name)); }
  IlvStProperty*  getProperty(IlUInt ndx) const
    { return (IlvStProperty*)_properties[ndx];}
  IlvStProperty*  operator[](IlUInt ndx) const
    { return (IlvStProperty*)_properties[ndx];}
  virtual void     addProperty(IlvStProperty* prop,
			       IlUInt ndx = (IlUInt)-1);
  virtual void     removeProperty(IlvStProperty* prop);
  virtual void     replaceProperty(const IlSymbol* name,
				   IlvStProperty* prop,
				   IlBoolean bDeletePrevious = IlTrue);
  IlvStProperty* const* getProperties(IlUInt& count) const;
  void getProperties(const IlSymbol*, IlArray&) const;

  IlUInt	    getHeaderLength() const
    { return _headerProps.getLength(); }
  IlvStProperty*  getHeader(IlUInt ndx) const
    { return (IlvStProperty*)_headerProps[ndx]; }
  void	    setHeader(IlUInt ndx, IlvStProperty* prop)
    { _headerProps[ndx] = prop; }
  void	    removeHeader(IlUInt ndx)
    { _headerProps.remove(ndx); }
  void	    insertHeader(IlUInt ndx, IlvStProperty* prop)
    { _headerProps.insert(ndx, prop); }

  virtual const IlSymbol* nameToType(const IlSymbol*) const;
  virtual IlBoolean isValidName(const IlSymbol*) const;
  IlUShort	    getIndentLevel() const { return _indentLevel; }
  void	    setIndentLevel(IlUShort ilevel) { _indentLevel = ilevel; }

  IlvStPropSetDescriptor* getDescriptor() const { return _descriptor; }
  void setDescriptor(IlvStPropSetDescriptor* def) { _descriptor = def; }

  IlBoolean		isStructured() const;
  IlBoolean		isDeclarative() const;
  IlBoolean		isBracketed() const;
  char		getSeparator() const;
  char		getHeaderSeparator() const;
  char		getStopCharacter() const;
  IlUShort		getIndentLevelIncrement() const;

  static IlvStProperty* MakeProperty(IL_STDPREF istream&,
				     const IlSymbol*,
				     IlvStPropertySet* parent = 0);
  static IlvStPropertySet* CreateSimpleList(const IlSymbol* name,
					    const IlvStPropertySet* parent = 0);
  static IlvStPropertySet* CreateSimpleStructure(const IlSymbol* name,
						 const IlvStPropertySet* = 0);
  static IlvStPropertySet* CreateBracketedList(const IlSymbol* name,
					       const IlvStPropertySet* parent = 0);
  static IlvStProperty* CreatePredefinedProperty(const IlSymbol* type,
						 const IlSymbol* name,
						 const IlvStPropertySet* = 0);
protected:
  IlArray	    _headerProps;
  IlArray	    _properties;
  IlUShort	    _indentLevel;
  IlvStPropSetDescriptor* _descriptor;

  void	initialize();
  int		getMaxLabelWidth() const;
  void        cleanHeaders();
}; // class IlvStPropertySet

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStFieldDescriptor
: public IlvStIdentifier {
public:
    ~IlvStFieldDescriptor();
    IlvStFieldDescriptor(const IlSymbol* name);
    IlvStFieldDescriptor(const IlvStFieldDescriptor& src);

    virtual void		writeValue(IL_STDPREF ostream&) const;
    virtual IlBoolean		readValue(IL_STDPREF istream&);
    virtual IlvStProperty*	copy() const;
    virtual void copyFrom(const IlvStProperty*);

    const char* getFieldType() const { return _string; }
    void	setFieldType(const char* type) { _string = type; }
    IlBoolean	isRepeatable() const { return _repeatable; }
    void	setRepeatable(IlBoolean val) { _repeatable = val; }
    IlvValue*	getDefaultValue() const { return _default; }
    void	setDefaultValue(IlvValue* value) { _default = value; }
protected:
    IlBoolean	_repeatable;
    IlvValue*	_default;
}; // class IlvStFieldDescriptor

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStFieldDescriptorList
: public IlvStPropertySet {
public:
    IlvStFieldDescriptorList(const IlSymbol* name) : IlvStPropertySet(name) {}
    IlvStFieldDescriptorList(const IlvStFieldDescriptorList& src)
	: IlvStPropertySet(src) {}

    virtual IlvStProperty* copy() const;
    virtual IlvStProperty*  createProperty(const IlSymbol* name)const;
    virtual IlBoolean isValidName(const IlSymbol*) const;
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPropSetDescriptor
: public IlvStPropertySet {
public:
    IlvStPropSetDescriptor(const IlSymbol* name);
    ~IlvStPropSetDescriptor();

    virtual IlvStProperty*  createProperty(const IlSymbol* name)const;
    virtual IlBoolean	    read(IL_STDPREF istream& istm);
    virtual IlvStProperty*  readProperty(IL_STDPREF istream& istm, const IlSymbol*);
    virtual IlBoolean	    isValidName(const IlSymbol*) const;
    virtual IlBoolean	    isShared() const;
    virtual void resetFrom(const IlvStProperty*);

    IlBoolean	isStructured() const
	{ return getPropertyBoolean(_S_structured); }
    void	setStructured(IlBoolean val)
	{ setPropertyBoolean(_S_structured, val); }
    IlBoolean	isDeclarative() const
	{ return getPropertyBoolean(_S_declarative); }
    void	setDeclarative(IlBoolean val)
	{ setPropertyBoolean(_S_declarative, val); }
    IlBoolean	isBracketed() const
	{ return getPropertyBoolean(_S_bracketed); }
    void	setBracketed(IlBoolean val)
	{ setPropertyBoolean(_S_bracketed, val); }
    char	getSeparator() const;
    void	setSeparator(char sep);
    char	getHeaderSeparator() const;
    void	setHeaderSeparator(char sep);
    char	getStopCharacter() const;
    void	setStopCharacter(char sep);
    IlUShort	getIndentLevelIncrement() const;
    void	setIndentLevelIncrement(IlUShort ili)
	{ setPropertyInt(_S_indentLevelIncrement, (IlInt)ili); }
    IlvStFieldDescriptor* const* getFieldDescriptors(IlUInt&) const;
    IlvStFieldDescriptor* getFieldDescriptor(const IlSymbol*) const;
    IlBoolean isRepeatableField(const IlSymbol*) const;
protected:
    void	initialize();
}; // class IlvStPropSetDescriptor

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStTopPropertySet
: public IlvStPropertySet {
public:
    IlvStTopPropertySet(const IlSymbol* name);

    IlBoolean		readFile(const char* fname);
    void		writeFile(const char* fname) const;
    void		write(IL_STDPREF ostream& ostm) const;
    virtual IlBoolean	isRepeatable(const IlSymbol*) const;
protected:
    static IlvStPropSetDescriptor* _Descriptor;
}; // class IlvStTopPropertySet

// --------------------------------------------------------------------------

#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_stprop)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Stprop_H */
