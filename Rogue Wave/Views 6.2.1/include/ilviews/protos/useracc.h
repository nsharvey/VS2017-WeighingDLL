// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/useracc.h
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
// Declaration of the IlvUserAccessor class, accessors defined by the
// prototype designer.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Useracc_H
#define __Ilv_Protos_Useracc_H

#if !defined(__Ilv_Protos_Macros_H)
#  include <ilviews/protos/macros.h>
#endif
#if !defined(__Ilv_Protos_Group_H)
#  include <ilviews/protos/group.h>
#endif
#if !defined(__Ilv_Protos_Groupio_H)
#  include <ilviews/protos/groupio.h>
#endif
#if defined(IL_STD)
#  include <cstdarg>
#else  /* !IL_STD */
#  include <stdarg.h>
#endif /* !IL_STD */

// --------------------------------------------------------------------------
// IlvUserAccessor	Base class for peristent accessors
//			(can be loaded/saved).
// --------------------------------------------------------------------------

// Flag values: dont forget to add accessor methods "isXxx" and "setXxx"
// and to update the "::read" and ::write" methods if you add new values.
//
typedef enum IlvUserAccessorFlag {
    IlvUserAccessorRuntime	= 0x1,	// runtime only, i.e.. not persistent.
    IlvUserAccessorPrivate	= 0x2,	// private: dont list when editing.
    IlvUserAccessorOutput	= 0x4,	// output: can be subscribed to.
    IlvUserAccessorInitialized  = 0x8
} _IlvUserAccessorFlag;

class ILVPROEXPORTED IlvUserAccessor
: public IlvAccessor {
    friend class IlvAccessorHolder;
    friend class IlvGroup;
public:
    IlvUserAccessor(const char*              name,
		    const IlvValueTypeClass* type,
		    IlUInt                   flags = 0);
    IlvUserAccessor(const IlvUserAccessor&);
    IlvUserAccessor(IlvDisplay*, IlvGroupInputFile&);
    virtual ~IlvUserAccessor();

    static
    IlvUserAccessor*	read(IlvGroupInputFile&, IlvDisplay*);
    virtual void	write(IlvGroupOutputFile&) const;
    virtual
    IlvUserAccessor*	copy() const;

#define TEST_FLAG(flag) ((_flags&flag)?IlTrue:IlFalse)
    inline IlBoolean	isRuntime() const
			{
			    return(TEST_FLAG(IlvUserAccessorRuntime));
			}
    inline IlBoolean	isPrivate() const
			{
			    return(TEST_FLAG(IlvUserAccessorPrivate));
			}
    inline IlBoolean	isOutput() const
			{
			    return(TEST_FLAG(IlvUserAccessorOutput));
			}
#undef TEST_FLAG
#define SET_FLAG(set, flag) if(set) _flags |= flag; else _flags &= ~flag
    inline void		setRuntime(IlBoolean runTime)
			{
			    SET_FLAG(runTime, IlvUserAccessorRuntime);
			}
    inline void		setPrivate(IlBoolean val)
			{ SET_FLAG(val, IlvUserAccessorPrivate);
			}
    inline void		setOutput(IlBoolean set)
			{
			    SET_FLAG(set, IlvUserAccessorOutput);
			}
#undef SET_FLAG
    virtual IlBoolean	isOutputValue(const IlSymbol*) const;
    virtual IlBoolean	isPrivateValue(const IlSymbol*) const;
    virtual void	initialize(const IlvAccessorHolder* object);

    IlvDeclarePropRootClassInfo();
protected:
    IlUInt		_flags;	// See defines above for possible values.
    IlBoolean		getValue(IlvValue& val,
				 const IlvAccessorHolder* object,
				 IlvDisplay*		display,
				 IlvValueTypeClass*	typeClass = 0,
				 IlSymbol*		typeVal = 0,
				 const IlvValue*	arg = 0) const;

    virtual IlUInt	compareValues(const IlvAccessorHolder* object,
				      const IlvAccessible* ref,
				      IlvValue* values,
				      IlUShort count,
				      IlvValueArray& diffs) const;
};

typedef enum IlvAccessorCategory {
    Data = 0,
    Control = 1,
    Trigger = 2,
    Display = 3,
    Animation = 4,
    Miscellaneous = 5,
    Obsolete = 6
} _IlvAccessorCategory;

// ---------------------------------------------------------------------------
// IlvAccessorDescriptor	Provides information about a subclass of
//				IlvUserAccessor used by PrototypeStudio to
//				edit accessors of this class.
// ---------------------------------------------------------------------------
class IlvAccessorParameter;
class IlvUserAccessorClassInfo;
class ILVPROEXPORTED IlvAccessorDescriptor
{
public:
    IlvAccessorDescriptor(IlvAccessorCategory = Miscellaneous);
    IlvAccessorDescriptor(const char*         description,
			  IlvAccessorCategory category,
			  IlUInt              parameterCount,
			  IlBoolean           variableCount ...);
    IlvAccessorDescriptor(const char*         description,
			  IlvAccessorCategory category,
			  const char*         label,
			  IlvValueTypeClass** defaultType,
			  IlUInt              parameterCount,
			  IlBoolean           variableCount ...);
    IlvAccessorDescriptor(const char*		description,
			  IlvAccessorCategory	category,
			  const char*		label,
			  IlBoolean		defaultValues,
			  IlvValueTypeClass**	defaultType,
			  IlUInt		parameterCount,
			  IlInt			variableCount,
			  ...);
    // compatibility constructors
    IlvAccessorDescriptor(const char*,
			  IlUInt,
			  IlBoolean,
			  ...);
    IlvAccessorDescriptor(const char*,
			  const char*,
			  IlvValueTypeClass**,
			  IlUInt,
			  IlBoolean,
			  ...);
    IlvAccessorDescriptor(const char*,
			  const char*,
			  IlBoolean,
			  IlvValueTypeClass**,
			  IlUInt,
			  IlInt,
			  ...);
    virtual ~IlvAccessorDescriptor();

    inline
    const IlvValueTypeClass*	getDefaultType() const
				{
				    return(_defaultType
					   ? *_defaultType
					   : 0);
				}
    const char*		getDescription() const;
    const char*		getLabel() const;
    IlvUserAccessor*	buildAccessor(IlvDisplay*,
				      IlvUserAccessorClassInfo*,
				      const char*,
				      IlBoolean,
				      IlBoolean,
				      IlvValueTypeClass* = 0,
				      IlvArray*          = 0) const;
    inline IlUInt	getParameterCount() const
	{ return(_parameterCount); }
    inline IlBoolean	hasVariableParameterCount() const
	{ return _variableCount ? IlTrue : IlFalse; }
    inline
    IlvAccessorCategory getCategory () const { return _category; }
    IlBoolean		isMultiLineParameter(IlUInt) const;
    const char*		getParameterLabel(IlUInt) const;
    IlvAccessorParameter* getParameterType(IlUInt)const;
    const char*		getParameterDefaultValue(IlUInt) const;
    const char*		getCategoryString () const;
    inline IlFloat	getVersion() const { return _version; }
    IlUInt		getParameters(const IlvUserAccessor*,
				      IlvArray&) const;
    virtual IlString	makeLabel(const IlvUserAccessor* a) const;
protected:
    const char*			_description;
    const char*			_label;
    IlvValueTypeClass**		_defaultType;
    IlUInt			_parameterCount;
    IlInt			_variableCount;
    const char**		_parameterLabels;
    IlvAccessorParameter***	_parameterTypes;
    const char**		_defaultValues;
    IlvAccessorCategory		_category;
    IlFloat			_version;
};

extern ILVPROEXPORTEDFUNCTION(IlvAccessorDescriptor*)
IlvGetAccessorDescriptor(const char*);

class IlvUserAccessorClassInfo;

extern ILVPROEXPORTEDFUNCTION(IlvAccessorDescriptor**)
IlvGetAllAccessorDescriptors(IlUInt&, IlvUserAccessorClassInfo*** = 0);

// --------------------------------------------------------------------------
// IlvAccessorParameter		Describes an accessor parameter type.
// --------------------------------------------------------------------------

class IlvAccessorParameterTypeFetcher;
class ILVPROEXPORTED IlvAccessorParameter
{
public:
    IlvAccessorParameter(IlvAccessorParameterTypeFetcher** fetcher = 0);
    IlvAccessorParameter(IlUInt count,
			 ...);
    virtual ~IlvAccessorParameter();

    virtual
    const char**	getChoices(IlvAccessorHolder*        object,
				   const char**              params,
				   IlUInt                    paramIndex,
				   IlBoolean                 matchType,
				   const IlvValueTypeClass*& type,
				   IlUInt&                   count);
    virtual
    const IlvValueTypeClass* getType(IlvAccessorHolder* object,
				     const char**       params,
				     IlUInt             paramIndex,
				     const IlvValueTypeClass* myType);
protected:
    const char**			_choices;
    IlUInt				_count;
    IlvAccessorParameterTypeFetcher**	_fetcher;
};


// --------------------------------------------------------------------------
// IlvAccessorParameterTypeFetcher	Get the type of an accessor parameter.
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvAccessorParameterTypeFetcher
{
public:
    IlvAccessorParameterTypeFetcher();
    IlvAccessorParameterTypeFetcher(IlvValueTypeClass**);
    IlvAccessorParameterTypeFetcher(IlUInt);
    virtual ~IlvAccessorParameterTypeFetcher();

    virtual
    const IlvValueTypeClass* getType(IlvAccessorHolder*,
				     const char**,
				     IlUInt,
				     const IlvValueTypeClass*);
protected:
    IlBoolean		_myType;
    IlvValueTypeClass** _type;
    IlInt		_param;
};

extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterMine;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterString;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterFloat;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterInt;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterUInt;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterBoolean;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterColor;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterDirection;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar0;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar1;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar2;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar3;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar4;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar5;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar6;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar7;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar8;
extern ILVPROEXPORTEDVAR(IlvAccessorParameterTypeFetcher*)
    IlvAccessorParameterPar9;

// --------------------------------------------------------------------------
// Subclasses of IlvAccessorParameter.
// --------------------------------------------------------------------------
extern ILVPROEXPORTEDVAR(IlvAccessorParameter*)
IlvUnknownAccessorParameterType;

#define ILVDECLAREACCPARCLASS(clss) \
class clss : public IlvAccessorParameter { \
public: \
    clss() : IlvAccessorParameter() {} \
    clss(IlvAccessorParameterTypeFetcher** fetcher) \
	: IlvAccessorParameter(fetcher) {} \
    virtual const char** getChoices(IlvAccessorHolder* object, \
				    const char** params, \
				    IlUInt paramIndex, \
				    IlBoolean matchType, \
				    const IlvValueTypeClass*& type, \
				    IlUInt& count); \
}; \
extern ILVPROEXPORTEDVAR(clss*) clss##Type;

ILVDECLAREACCPARCLASS(IlvStringParameter)
ILVDECLAREACCPARCLASS(IlvNodeNameParameter)
ILVDECLAREACCPARCLASS(IlvNodeNameOrAllParameter)
ILVDECLAREACCPARCLASS(IlvOutputAccessorParameter)

ILVDECLAREACCPARCLASS(IlvNodeAccessorParameter)
ILVDECLAREACCPARCLASS(IlvSubAccessorParameter)
ILVDECLAREACCPARCLASS(IlvValueParameter)

extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeMine;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeString;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeFloat;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeInt;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeUInt;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeBoolean;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeColor;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypeDirection;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar0;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar1;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar2;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar3;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar4;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar5;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar6;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar7;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar8;
extern ILVPROEXPORTEDVAR(IlvNodeAccessorParameter*)
    IlvNodeAccessorParameterTypePar9;

extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeMine;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeString;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeFloat;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeInt;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeUInt;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeBoolean;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeColor;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypeDirection;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar0;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar1;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar2;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar3; 
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar4;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar5;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar6;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar7;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar8;
extern ILVPROEXPORTEDVAR(IlvSubAccessorParameter*)
    IlvSubAccessorParameterTypePar9;

extern ILVPROEXPORTEDVAR(IlvValueParameter*)
    IlvValueParameterTypeMine;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeString;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeFloat;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeInt;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeUInt;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeBoolean;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeColor;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypeDirection;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar0;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar1;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar2;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar3;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar4;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar5;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar6;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar7;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar8;
extern ILVPROEXPORTEDVAR(IlvValueParameter*) IlvValueParameterTypePar9;


extern ILVPROEXPORTEDVAR(const char*) IlvValueParameterImmediateStr;
extern ILVPROEXPORTEDVAR(const char*) IlvAccessorParameterAllStr;
extern ILVPROEXPORTEDVAR(const char*) IlvAccessorParameterMatchStr;
extern ILVPROEXPORTEDVAR(const char*) IlvAccessorParameterAllNodesStr;

// --------------------------------------------------------------------------
// Class info macros for IlvUserAccessor.
// --------------------------------------------------------------------------
typedef IlvUserAccessor* (* IlvUserAccessorConstructor)(IlvGroupInputFile&,
							IlvDisplay*);

class ILVPROEXPORTED IlvUserAccessorClassInfo
: public IlvPropClassInfo {
public:
    inline
    IlvUserAccessorConstructor	getConstructor() const
	{ return _constructor; }
    inline
    IlvAccessorDescriptor*	getDescriptor() const
	{ return(_descriptor); }
    static
    IlvUserAccessorClassInfo*	Create(const char*,
				       IlvClassInfo**,
				       IlvUserAccessorConstructor,
				       IlvAccessorDescriptor* = 0);
protected:
    IlvUserAccessorClassInfo(const char*		className,
			     IlvClassInfo**		superClass,
			     IlvUserAccessorConstructor	constructor,
			     IlvAccessorDescriptor*	descriptor = 0)
    : IlvPropClassInfo(className, superClass),
      _constructor(constructor),
      _descriptor(descriptor) {}

    IlvUserAccessorConstructor	_constructor;
    IlvAccessorDescriptor*	_descriptor;
};

#define DeclareUserAccessorInfoRO() IlvDeclarePropClassInfo();	\
    static IlvUserAccessor* read(IlvGroupInputFile&, IlvDisplay*); \
    virtual IlvUserAccessor* copy() const

#define DeclareUserAccessorInfo() DeclareUserAccessorInfoRO(); \
    virtual void write(IlvGroupOutputFile&) const
#define DeclareUserAccessorIOConstructors(classname) public: \
    classname(IlvDisplay*, IlvGroupInputFile&); \
    classname(const classname&)
#define IlvPreRegisterUserAccessorClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterUserAccessorClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,					\
	IlvUserAccessorClassInfo::Create(#classname,			\
				     &superclass::_classinfo,		\
				     (IlvUserAccessorConstructor)	\
				     classname::read,			\
				     new classname##DescriptorClass()))

#define IlvPostRegisterUserAccessorClass(classname, superclass)		\
ILVPOSTDEFINECLASSINFOMEMBERS(classname,				\
	IlvUserAccessorClassInfo::Create(#classname,			\
				     &superclass::_classinfo,		\
				     (IlvUserAccessorConstructor)	\
				     classname::read, \
				     new classname##DescriptorClass()))

#define IlvPredefinedUserAccessorIOMembers(classname) \
IlvUserAccessor* classname::copy() const { return new classname(*this); } \
IlvUserAccessor* classname::read(IlvGroupInputFile& i, IlvDisplay* d) \
{ return new classname(d, i); }

// --------------------------------------------------------------------------
// IlvValueAccessor	Predefined user accessor which simply holds a value.
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvValueAccessor
: public IlvUserAccessor {
public:
    IlvValueAccessor(const char* name,
		     const IlvValueTypeClass* type);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvValueAccessor);
protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);

    IlvValue		_value;
};

// --------------------------------------------------------------------------
// IlvToggleAccessor	Toggle a boolean value
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvToggleAccessor
: public IlvUserAccessor {
public:
    IlvToggleAccessor(const char* name,
		      const IlvValueTypeClass* type,
		      const char* toggleValue);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvToggleAccessor);
protected:
    IlSymbol*		_toggleValue;

    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
};

// --------------------------------------------------------------------------
// IlvCounterAccessor	Count times a value is changed.
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvCounterAccessor
: public IlvUserAccessor {
public:
    IlvCounterAccessor(const char*              name,
		       const IlvValueTypeClass* type,
		       const char*              counterValue,
		       const char*              maxValue);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvCounterAccessor);
protected:
    IlSymbol*		_counterValue;
    IlSymbol*		_maxValue;

    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
};

// --------------------------------------------------------------------------
// IlvDebugAccessor	Print a message for debugging
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvDebugAccessor
: public IlvUserAccessor {
public:
    IlvDebugAccessor(const char*              name,
		     const IlvValueTypeClass* type);
    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvDebugAccessor);
protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
};

// --------------------------------------------------------------------------
// IlvNodeAccessor	Predefined user accessor for accessing a value
//			of a group node.
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvNodeAccessor
: public IlvUserAccessor {
public:
    IlvNodeAccessor(const char*              name,
		    const IlvValueTypeClass* type,
		    const char*              subaccessor);

    // compatibility constructor. use deprecated.
    IlvNodeAccessor(const char*,
		    const IlvValueTypeClass*,
		    const char*,
		    const char*);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvNodeAccessor);
protected:
    IlSymbol*		_attribute;

    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
/*
    virtual void filterValues(const IlvAccessorHolder* object,
			      IlvValue* values,
			      IlUShort& count) const;
*/
};

// --------------------------------------------------------------------------
// IlvFormatAccessor	Predefined user accessor for formatting values
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvFormatAccessor
: public IlvUserAccessor {
public:
    IlvFormatAccessor(const char*              name,
		      const IlvValueTypeClass* type,
		      const char*              formatValue,
		      const char*              maxCharsValue,
		      const char*              subacc);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvFormatAccessor);
protected:
    IlSymbol*		_formatValue;
    IlSymbol*		_maxCharsValue;
    IlSymbol*		_subacc;

    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
};

// --------------------------------------------------------------------------
// IlvTriggerAccessor	Predefined user accessor for triggerting values
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvTriggerAccessor
: public IlvUserAccessor {
public:
    IlvTriggerAccessor(const char*              name,
		       const IlvValueTypeClass* type,
		       const char*              from,
		       const char*              subacc,
		       IlvDisplay*              display = 0);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvTriggerAccessor);
protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);

    IlSymbol*		_from;
    IlSymbol*		_subacc;
    IlvDisplay*		_display;
};

// --------------------------------------------------------------------------
// IlvCompositeAccessor	Predefined user accessor for accessing a value
//			of a group node.
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvCompositeAccessor
: public IlvUserAccessor {
public:
    IlvCompositeAccessor(const char*              name,
			 const IlvValueTypeClass* type,
			 IlUInt                   count,
			 const char**             accnames);
    virtual ~IlvCompositeAccessor();

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvCompositeAccessor);
protected:
    IlUInt		_count;
    IlSymbol**		_accnames;

    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);

    virtual void	filterValues(const IlvAccessorHolder*,
				     IlvValue*,
				     IlUShort&) const;
    virtual IlUInt	compareValues(const IlvAccessorHolder*,
				      const IlvAccessible*,
				      IlvValue*,
				      IlUShort,
				      IlvValueArray&) const;
};

// --------------------------------------------------------------------------
// IlvGroupUserAccessor		maps a value to all the nodes of a group.
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupUserAccessor
: public IlvUserAccessor {
public:
    IlvGroupUserAccessor(const char* name, IlvValueTypeClass* type);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvGroupUserAccessor);
protected:
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;

    virtual void	filterValues(const IlvAccessorHolder*,
				     IlvValue*,
				     IlUShort&) const;

    virtual IlUInt	compareValues(const IlvAccessorHolder*,
				      const IlvAccessible*,
				      IlvValue*,
				      IlUShort,
				      IlvValueArray&) const;
};

// --------------------------------------------------------------------------
// IlvMultipleUserAccessor	A multiple accessor defines the side effects
//				of changing (or querying?) several values
//				in a single call. It can also be used to
//				set several values in a single changeValue
//				call: the IlvValue passed then contains an
//				array of IlvValues (not working yet?).
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvMultipleUserAccessor
: public IlvUserAccessor {
public:
    IlvMultipleUserAccessor(const char*         name,
			    IlUShort            count,
			    const char**        names,
			    IlvValueTypeClass** types);
    IlvMultipleUserAccessor(const char*,
			    IlUShort,
			    const char**,
			    IlvValueTypeClass***);
    ~IlvMultipleUserAccessor();

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvMultipleUserAccessor);
protected:
    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder*, const IlvValue&);
    virtual void	getAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&) const;

    virtual IlShort	matchValues(const IlvAccessorHolder*,
				    const IlvValue*,
				    IlUShort,
				    IlvValue* = 0) const;

    IlUShort		_count;
    IlSymbol**		_names;
    IlvValueTypeClass** _types;
};

// --------------------------------------------------------------------------
// IlvHookAccessor	Predefined user accessor for triggerting values
// --------------------------------------------------------------------------
class ILVPROEXPORTED IlvHookAccessor
: public IlvUserAccessor {
public:
    IlvHookAccessor(const char*,
		    const IlvValueTypeClass*,
		    const char*);

    DeclareUserAccessorInfo();
    DeclareUserAccessorIOConstructors(IlvHookAccessor);
protected:
    IlSymbol*		_nodename;

    virtual IlvValue&	queryValue(const IlvAccessorHolder*,
				   IlvValue&) const;
    virtual void	queryValues(const IlvAccessorHolder*,
				    IlvValue*,
				    IlUShort) const;
    virtual IlBoolean	changeValue(IlvAccessorHolder*,
				    const IlvValue&);
    virtual IlBoolean	changeValues(IlvAccessorHolder*,
				     const IlvValue*,
				     IlUShort);
};

typedef void (*IlvAccessorHook)(IlvAccessorHolder*,
				const IlvValue*,
				IlUShort,
				IlvGroupNode*,
				IlBoolean);

extern ILVPROEXPORTEDFUNCTION(IlvAccessorHook)
IlvSetAccessorHook(IlvAccessorHook hook);

// --------------------------------------------------------------------------
// _IlvProtoReadValue   read a value (immediate or accessor) from a stream.
// use is deprecated. use IlvGroupFile::readValue instead.
// --------------------------------------------------------------------------
extern ILVPROEXPORTEDFUNCTION(IlSymbol*)
_IlvProtoReadValue(IL_STDPREF istream&, IlBoolean = IlFalse);

IL_MODULEINIT(useracc, ILVPROEXPORTED);
#endif /* !__Ilv_Protos_Useracc_H */
