// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/valuesrc.h
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
// Declaration of the IlvValueSource class and predefined subclasses
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Valuesrc_H
#define __Ilv_Protos_Valuesrc_H

#if !defined(__Ilv_Protos_Value_H)
#include <ilviews/protos/value.h>
#endif
#if !defined(__Ilv_Protos_Group_H)
#include <ilviews/protos/group.h>
#endif
#if !defined(__Ilv_Base_List_H)
#include <ilviews/base/list.h>
#endif
#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif
#if !defined(__Ilv_Graphics_Io_H)
#include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Graphics_All_Holder_H)
#include <ilviews/graphics/holder.h>
#endif
#if defined(IL_STD)
#include <fstream>
#else  /* !IL_STD */
#include <fstream.h>
#endif /* !IL_STD */

// ---------------------------------------------------------------------------
// IlvValueSource	Abstract base class for value sources.
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvValueSourceInputFile;
class ILVPROEXPORTED IlvValueSourceOutputFile;

typedef enum IlvValueSourceState {
    IlvValueSourceBadState,
    IlvValueSourceStopped,
    IlvValueSourceRunning,
    IlvValueSourceSuspended
} _IlvValueSourceState;

class ILVPROEXPORTED IlvValueSource : public IlvAccessible
{
public:
    IlvValueSource(const char* name = 0);
    IlvValueSource(IlvDisplay*, IlvValueSourceInputFile&);
    IlvValueSource(const IlvValueSource&);
    virtual ~IlvValueSource();

    static
    IlvValueSource*	read(IlvValueSourceInputFile&, IlvDisplay*);
    virtual void	write(IlvValueSourceOutputFile&) const;
    virtual
    IlvValueSource*	copy() const;
    virtual const char*	getName() const;
    void		setName(const char* name);

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    virtual void	start();
    virtual void	stop();
    virtual void	suspend();

    IlvDeclarePropRootClassInfo();

protected:
    char*		_name;
    IlvValueSourceState	_state;

    static int		NextIndex;
};

// ---------------------------------------------------------------------------
// Class info macros for IlvValueSource.
// ---------------------------------------------------------------------------
typedef IlvValueSource*
(* IlvValueSourceConstructor)(IlvValueSourceInputFile&, IlvDisplay*);

class ILVPROEXPORTED IlvValueSourceClassInfo : public IlvPropClassInfo
{
public:
    inline
    IlvValueSourceConstructor getConstructor() const { return _constructor; }
    static
    IlvValueSourceClassInfo* Create(const char*,
				    IlvClassInfo**,
				    IlvValueSourceConstructor);
protected:
    IlvValueSourceClassInfo(const char*			className,
			    IlvClassInfo**		superClass,
			    IlvValueSourceConstructor	constructor)
	: IlvPropClassInfo(className, superClass),
	  _constructor(constructor) {}
    IlvValueSourceConstructor _constructor;
};


#define DeclareValueSourceInfoRO() IlvDeclarePropClassInfo();	\
    static IlvValueSource* read(IlvValueSourceInputFile&, IlvDisplay*); \
    virtual IlvValueSource* copy() const

#define DeclareValueSourceInfo() DeclareValueSourceInfoRO(); \
    virtual void write(IlvValueSourceOutputFile&) const

#define DeclareValueSourceIOConstructors(classname) public: \
    classname(IlvDisplay*, IlvValueSourceInputFile&); \
    classname(const classname&)

#define IlvPreRegisterValueSourceClass(classname) \
ILVPREDEFINECLASSINFOMEMBERS(classname)

#define IlvRegisterValueSourceClass(classname, superclass)		\
ILVDEFINECLASSINFOMEMBERS(classname,			\
 IlvValueSourceClassInfo::Create(#classname,	\
				 &superclass::_classinfo,\
				 (IlvValueSourceConstructor)classname::read))

#define IlvPostRegisterValueSourceClass(classname, superclass) \
ILVPOSTDEFINECLASSINFOMEMBERS(classname, \
IlvValueSourceClassInfo::Create(#classname, \
				&superclass::_classinfo,\
				(IlvValueSourceConstructor)classname::read))

#define IlvPredefinedValueSourceIOMembers(classname) \
inline IlvValueSource* classname::copy() const{return new classname(*this);} \
inline IlvValueSource* classname::read(IlvValueSourceInputFile& i,	     \
			       IlvDisplay* d) { return new classname(d, i); }

// ---------------------------------------------------------------------------
// IlvValueSourceNode		Subclass of IlvGroupNode for holding
//				a valueSource object.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvValueSourceNode : public IlvGroupNode
{
public:
    IlvValueSourceNode(IlvValueSource* source,
		       const char* name = 0);
    virtual ~IlvValueSourceNode();

    virtual const char*	getName() const;

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    inline
    IlvValueSource*	getSource() { return _source; }

    // Subscription interface:
    //
    virtual void	subscribe(IlvAccessible* subscriber,
				  IlSymbol* sourceValue,
				  IlSymbol* subscriberValue,
				  IlvValueTypeClass* type,
				  IlvValueSubscriptionMode mode
				  = IlvValueSubscriptionChange);
    virtual void	subscribeByName(const char* subscriber,
					IlSymbol* sourceValue,
					IlSymbol* subscriberValue,
					IlvValueTypeClass* type,
					IlvValueSubscriptionMode mode
					= IlvValueSubscriptionChange);

    virtual void	unSubscribe(IlvAccessible* subscriber,
				    IlSymbol* sourceValue = 0,
				    IlSymbol* subscriberValue = 0);
    virtual void	unSubscribeByName(const char* subscriber,
					  IlSymbol* sourceValue = 0,
					  IlSymbol* subscriberValue = 0);

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    virtual
    IlvGroupNode*	copy(IlBoolean shared) const;
    IlvAccessible*	getActualSubscriber();

    DeclareGroupNodeInfo();

protected:
    IlvValueSource*	_source;
};

// ---------------------------------------------------------------------------
// IlvValueSourceStateTypeClass		Value type for the "state" accessor
//					of a value source.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvValueSourceStateTypeClass : public IlvValueTypeClass
{
public:
    IlvValueSourceStateTypeClass();

    virtual const char*	toString(const IlvValue& val) const;
    virtual IlBoolean	isPersistent() const;
    virtual IlUInt	getCapacities() const;
    virtual IlBoolean	fromString(IlvValue&, const char*, IlAny = 0) const;
    virtual IlInt	compareValues(const IlvValue& v1,
				      const IlvValue& v2) const;
};

extern ILVPROEXPORTEDVAR(IlvValueSourceStateTypeClass*)
IlvValueSourceStateType;

// ---------------------------------------------------------------------------
// IlvValueSourceInputFile	Input context for value sources.
// ---------------------------------------------------------------------------

class IlvProtoHolderInterface;

class ILVPROEXPORTED IlvValueSourceInputFile : public IlvSubscriptionInputFile
{
public:
    IlvValueSourceInputFile(ILVSTDPREF istream& stream)
	: IlvSubscriptionInputFile(stream) {}

    virtual
    IlvValueSource*	readValueSource(IlvDisplay* d);
    inline
    IlvInputFile*	getInputFile() { return(_inputFile); }
    inline void		setInputFile(IlvInputFile* i) { _inputFile = i; }

protected:
    IlvInputFile*	_inputFile;
};

// ---------------------------------------------------------------------------
// IlvValueSourceOutputFile	Output context for value sources.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvValueSourceOutputFile
    : public IlvSubscriptionOutputFile
{
public:
    IlvValueSourceOutputFile(ILVSTDPREF ostream& stream)
	: IlvSubscriptionOutputFile(stream) {}

    virtual void	writeValueSource(IlvValueSource* source);
    void		writeValueSources(IlvValueSource** sources,
					  IlUInt count);
    inline
    IlvOutputFile*	getOutputFile() { return(_outputFile); }
    inline void		setOutputFile(IlvOutputFile* o) { _outputFile = o; }

protected:
    IlvOutputFile*	_outputFile;
};

// ---------------------------------------------------------------------------
// IlvClockValueSource	A value source which generates a time value
//			at a specified interval.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvClockValueSource : public IlvValueSource
{
public:
    IlvClockValueSource(IlvDisplay* display,
			const char* name = 0,
			int secs = 1,
			int millisecs = 0,
			IlUInt initialTime = 0);
    virtual ~IlvClockValueSource();

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;
    virtual void	start();
    virtual void	stop();
    virtual void	suspend();
    inline IlUInt	getCurrentTime() { return _currentTime; }
    inline void		setCurrentTime(IlUInt t) { _currentTime = t; }
    inline IlUInt	getInitialTime() { return _initialTime; }
    inline void		setInitialTime(IlUInt t) { _initialTime = t; }

    DeclareValueSourceInfo();
    DeclareValueSourceIOConstructors(IlvClockValueSource);

protected:
    IlvTimer*		_timer;
    IlUInt		_currentTime;
    IlUInt		_initialTime;

    virtual void	tick(IlvValue* values, IlUShort& count, IlUShort max);
    void		sendTime();

    static void		TimerProc(IlvTimer* timer, IlAny arg);
};

// ---------------------------------------------------------------------------
// IlvRandomValueSource	A value source which generates a time value
//			at a specified interval.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvRandomValueSource : public IlvClockValueSource
{
public:
    IlvRandomValueSource(IlvDisplay* display,
			 const char* name = 0,
			 IlFloat min = 0.0,
			 IlFloat max = 100.0,
			 const char* valueName = "random",
			 int secs = 1,
			 int millisecs = 0,
			 IlUInt initialTime = 0);

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    DeclareValueSourceInfo();
    DeclareValueSourceIOConstructors(IlvRandomValueSource);

protected:
    IlSymbol*		_valueName;
    IlFloat		_min;
    IlFloat		_max;

    virtual void	tick(IlvValue* values, IlUShort& count, IlUShort max);
};

// ---------------------------------------------------------------------------
// IlvFileValueSource		A source that reads values from a stream
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvFileValueSource : public IlvValueSource
{
public:
    IlvFileValueSource(IlvDisplay* display,
		       const char* filename,
		       const char* name = 0);
    virtual ~IlvFileValueSource();

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;
    void		setFileName(const char* n);
    const char*		getFileName() const { return(_filename); }
    virtual void	start();
    virtual void	stop();
    virtual void	suspend();

    DeclareValueSourceInfo();
    DeclareValueSourceIOConstructors(IlvFileValueSource);

protected:
    char*		_filename;
    IL_STDPREF ifstream* _str;
    IlUInt		_count;
    IlSymbol**		_names;
    IlvValueTypeClass** _types;
    IlvTimer*		_timer;
    IlvValue		_nextValue;

    void		initStream();

    ILVSTDPREF ifstream& getStream() { return(*_str); }
    void		readNextValue();
    IlBoolean		readValue(IlUInt& interval,
				  IlSymbol*& name,
				  IlvValueTypeClass*& type,
				  char* value = 0,
				  IlUInt size = 0);
    void		sendValue();

    static void		TimerProc(IlvTimer* timer, IlAny arg);
};

// ---------------------------------------------------------------------------
// IlvGraphicValueSource    A source for connecting prototypes to IlvGraphics.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGraphicValueSource : public IlvValueSource
{
public:
    IlvGraphicValueSource(IlvGraphic* graphic, const char* name = 0);
    ~IlvGraphicValueSource();

    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	changeValue(const IlvValue& val);
    virtual IlBoolean	changeValues(const IlvValue* vals, IlUShort count);
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;

    virtual void	subscribe(IlvAccessible* subscriber,
				  IlSymbol* sourceValue,
				  IlSymbol* subscriberValue,
				  IlvValueTypeClass* type,
				  IlvValueSubscriptionMode mode
				  = IlvValueSubscriptionChange);
    virtual void	unSubscribe(IlvAccessible* subscriber,
				    IlSymbol* sourceValue = 0,
				    IlSymbol* subscriberValue = 0);
    virtual IlBoolean	isOutputValue(const IlSymbol* valueName) const;

    IlSymbol**		getOutputValues(IlUInt& count) const;
    IlSymbol**		getInputValues(IlUInt& count) const;

    inline IlvGraphic*	getGraphic() { return _graphic; }

    static
    IlvGraphicValueSource* MakeSource(IlvGraphic* obj,
				      IlvProtoHolderInterface* protoHolder);
    static void		CleanSource(IlvGraphic* obj,
				    IlvProtoHolderInterface* protoHolder);

    DeclareValueSourceInfo();
    DeclareValueSourceIOConstructors(IlvGraphicValueSource);

protected:

    static void		CallbackProc(IlvGraphic* obj, IlAny arg);

    IlvValueInterface*	getConnectionInterface() const;

    void		initCallbacks(IlBoolean remove = IlFalse);
    void		initProperty();

    IlvGraphic*		_graphic;
};

// ---------------------------------------------------------------------------
// Static initialization of module.
IlvDECLAREINITPROCLASS(valuesrc)

#endif /* __Ilv_Protos_Valuesrc_H */
