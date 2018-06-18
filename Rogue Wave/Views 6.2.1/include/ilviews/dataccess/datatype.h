// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/datatype.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliDatatype class and
//                the variables IliNullType,
//                              IliStringType,
//                              IliLongStringType,
//                              IliBooleanType,
//                              IliByteType,
//                              IliIntegerType,
//                              IliFloatType,
//                              IliDoubleType,
//                              IliDecimalType,
//                              IliDateType,
//                              IliTimeType,
//                              IliBinaryType,
//                              IliLongBinaryType,
//                              IliAnyType
// Defined in library dataccess
// --------------------------------------------------------------------------

#ifndef __Ili_Datatype_H
#define __Ili_Datatype_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ili_Module_H)
#  include <ilviews/dataccess/module.h>
#endif
#if !defined(__Ili_String_H)
#  include <ilviews/dataccess/string.h>
#endif
#if !defined(__Ili_Date_H)
#  include <ilviews/dataccess/date.h>
#endif
#if !defined(__Ili_Decimal_H)
#  include <ilviews/dataccess/decimal.h>
#endif
#if !defined(__Ili_Format_H)
#  include <ilviews/dataccess/format.h>
#endif

#if defined(IL_STD)
#  include <iostream>
#  include <strstream>
#else
#  include <iostream.h>
#  if defined(ILVFATFILENAMES)
#    include <strstrea.h>
#  else
#    include <strstream.h>
#  endif
#endif

class ILV_INF_EXPORTED IliValue;
class ILV_INF_EXPORTED IliSchema;
class ILV_INF_EXPORTED IliTable;
class ILV_INF_EXPORTED IliSession;
class ILV_INF_EXPORTED IliDatatype;

const IlUInt IliNTS = (IlUInt)-1;

// --------------------------------------------------------------------------
typedef unsigned char IliByte;

union IliValueRecord {
    IlBoolean		_boolData;
    IliByte		_byteData;
    IlInt		_intData;
    IlFloat		_floatData;
    IlDouble		_doubleData;
    IliDecimalIpl*	_decimalData;
    IliDateRecord	_dateData;
    IliTimeRecord	_timeData;
    IlAny		_anyData;
    IlShort		_fill[8];
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliBinary 
{
public:
    IlUInt		_size;
    IliByte*		_data;

    IliBinary() : _size(0), _data(0) {}

    // read() assumes _size is correct and _data already allocated
    void		read(IL_STDPREF istream&);
    // write() writes only data.
    void		write(IL_STDPREF ostream&) const;

    static
    const IliBinary&	GetDefault();
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatypeReader
{
public:
    IliDatatypeReader(const char*);
    virtual ~IliDatatypeReader();

    const char*		getName() const;

    virtual const IliDatatype*
	readDefinition(const char*, IL_STDPREF istream&) const = 0;

    IlBoolean		isDefault() const;

private:
    IliString		_name;
};

// --------------------------------------------------------------------------
typedef void (*IliDatatypeCallback)(const IliDatatype* type,
				    IlBoolean enter,
				    IlAny userData);
IL_DEFINEFPTRTOANYCAST(IliDatatypeCallback);

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatype
: public IliRefCounted
{
public:
    inline const char*	getName() const { return _name; }

    const char*		getPrettyName(IlvDisplay* display) const;

    virtual const char*	getPrettyKeyword() const;
    inline IlBoolean	isRegistered() const { return _isRegistered; }

    virtual IlBoolean	isAnonymous() const;

    const char*		getOwnerName() const;
    void		setOwnerName(const char*);

    static IlInt	GetDatatypeCount();
    static const IliDatatype*	GetDatatypeAt(IlInt);
    static const IliDatatype*	GetDatatypeByName(const char* name);

    static const IliDatatype*	GetDatatypeByPrettyName(IlvDisplay* disp,
							const char* name);
    static const IliDatatype*	ReadType(IL_STDPREF istream& input);

    void		writeType(IL_STDPREF ostream& output) const;

    virtual
    IlvAlignment	getDefaultAlign() const;

    virtual void	init(IliValue&) const = 0;
    virtual void	free(IliValue&) const = 0;
    virtual void	nullify(IliValue&) const;
    virtual void	copy(const IliValue&,IliValue&) const = 0;

    virtual IlBoolean	equal(const IliValue&, const IliValue&) const = 0;
    virtual int		compare(const IliValue&, const IliValue&) const = 0;

    virtual IlBoolean	isSearchable() const;

    virtual
    IliFormatType	getFormatType() const;
    virtual void	format(const IliValue&,
			       IliString&,
			       const IliFormat&) const;

    virtual IlBoolean	getString(const IliValue&, const char*&) const;
    virtual IlBoolean	getBoolean(const IliValue&, IlBoolean&) const;
    virtual IlBoolean	getByte(const IliValue&, IliByte&) const;
    virtual IlBoolean	getInteger(const IliValue&, IlInt&) const;
    virtual IlBoolean	getFloat(const IliValue&, IlFloat&) const;
    virtual IlBoolean	getDouble(const IliValue&, IlDouble&) const;
    virtual IlBoolean	getDecimal(const IliValue&, IliDecimal&) const;
    virtual IlBoolean	getDate(const IliValue&, IliDate&) const;
    virtual IlBoolean	getTime(const IliValue&, IliTime&) const;
    virtual IlBoolean	getBinary(const IliValue&, IliBinary&) const;
    virtual IlBoolean	getAny(const IliValue&, IlAny&) const;
    virtual IlBoolean	getTable(const IliValue&, const IliTable*&) const;

    virtual IlBoolean	setString(IliValue&, const char*, IlUInt) const;
    virtual IlBoolean	setBoolean(IliValue&, IlBoolean) const;
    virtual IliByte	setByte(IliValue&, IliByte) const;
    virtual IlBoolean	setInt(IliValue&, IlInt) const;
    virtual IlBoolean	setFloat(IliValue&, IlFloat) const;
    virtual IlBoolean	setDouble(IliValue&, IlDouble) const;
    virtual IlBoolean	setDecimal(IliValue&, const IliDecimal&) const;
    virtual IlBoolean	setDate(IliValue&, const IliDate&) const;
    virtual IlBoolean	setTime(IliValue&, const IliTime&) const;
    virtual IlBoolean	setBinary(IliValue&, const IliBinary&) const;
    virtual IlBoolean	setAny(IliValue&, IlAny) const;
    virtual IlBoolean	setTable(IliValue&, const IliTable*) const;

    virtual void	write(const IliValue&, IL_STDPREF ostream&) const;
    virtual void	read(IliValue&, IL_STDPREF istream&) const;
    virtual IlBoolean	emit(const IliValue&, IliString&,
			     const IliSession*) const;
    virtual IlBoolean	isNumericType() const;

    virtual IlBoolean	isIntegralType() const;

    virtual IlBoolean	isFractionalType() const;

    virtual IlBoolean	isDecimalType() const;

    virtual IlBoolean	isStringType() const;

    virtual IlBoolean	isBinaryType() const;

    virtual IlBoolean	isLargeObjectType() const;

    virtual IlBoolean	isDateTimeType() const;

    virtual IlBoolean	isStructuredType() const;

    virtual IlBoolean	isTableType() const;

    virtual IlBoolean	isObjectType() const;
    virtual IlBoolean	isReferenceType() const;

    virtual IliSchema*	getNestedSchema() const;

    virtual IlBoolean	shareTable(IliValue&, IliTable*) const;

    virtual IliTable*	makeTable() const;

    virtual IlBoolean	supportsNestedSQLStatements() const;

    virtual IlBoolean	hasConstSize() const;
    virtual IlBoolean	checkMaxLength(const IliValue&, IlInt) const;
    virtual IlUInt	getBufferSize(const IliValue&) const;

    virtual void	writeDefinition(IL_STDPREF ostream&) const;
    static const IliDatatype*	ReadDefinition(IL_STDPREF istream&);

    const IliDatatype*	close();
    IlBoolean		isClosed() const;

    static IlInt	GetClosedDatatypeCount();
    static const IliDatatype*	GetClosedDatatypeAt(IlInt);
    static const IliDatatype*	GetClosedDatatypeByToken(IlInt);

    static void		AddDatatypeCallback(IliDatatypeCallback, IlAny);
    static void		RemoveDatatypeCallback(IliDatatypeCallback, IlAny);

    IlInt		getToken() const;

    static void		AtInit();
    static void		AtExit();

protected:
    IliString		_name;
    IliString		_canonicalForm;
    IlBoolean		_isClosed;
    IlInt		_token;
    IliString		_ownerName;
    IlBoolean		_isRegistered;

    static IlvStringHashTable*		_allTypes;
    static IlvStringHashTable*		_allClosedTypes;
    static IlvHashTable*		_allClosedTypesByToken;
    static IlvStringHashTable*		_allReaders;
    static IlvArray*			_callbacks;
    static IlvArray*			_callbackData;
    static IlInt			_nextToken;

    static IliString*			_tempBuf;
    static IL_STDPREF strstream*	_tempStrStream;

    IliDatatype(const char*);
    virtual ~IliDatatype();
    void		doRegister();

    void		unRegister();

    virtual void	setToken(IlInt token);

    static void		RegisterReader(IliDatatypeReader*);
    static void		UnRegisterReader(IliDatatypeReader*);
    void		callCallbacks(IlBoolean);

    static
    IliDatatypeReader*	GetReader(const char* name);

    IliDatatypeReader*	getReader() const;
    virtual const char* getReaderName() const;

    inline const IliValueRecord& getValueRecord(const IliValue&) const;
    inline
    IliValueRecord&	getValueRecord(IliValue&) const;

    inline void		clearNullFlag(IliValue&) const;

    static const char*	FormatDouble(IlDouble);
    static const char*	FormatFloat(IlFloat);
    static const char*	FormatDecimal(const IliDecimal&);

    friend class IliModuleCLASS(IliDatatype);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatypePtr
{
public:
    IliDatatypePtr(const IliDatatype*);
    IliDatatypePtr(const IliDatatypePtr&);
    ~IliDatatypePtr();

    const IliDatatypePtr& operator =(const IliDatatypePtr&);

    operator const IliDatatype*() const;
    operator IliDatatype*();

private:
    IliDatatype*	_ptr;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatypeCollection
{
public:
    IliDatatypeCollection();
    IliDatatypeCollection(const IliDatatypeCollection&);
    ~IliDatatypeCollection();

    const IliDatatypeCollection& operator =(const IliDatatypeCollection&);

    IlInt		getTypeCount() const;
    const IliDatatype*	getTypeAt(IlInt) const;

    void		addType(const IliDatatype*);
    void		removeType(const IliDatatype*);

    void		sort();
    void		empty();

    void		read(IL_STDPREF istream&);
    void		write(IL_STDPREF ostream&) const;

private:
    IlvArray		_array;

    void		tidy();
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliPointerTypeClass
: public IliDatatype
{
public:
    virtual void	init(IliValue&) const;
    virtual void	free(IliValue&) const;
    virtual void	copy(const IliValue&, IliValue&) const;

    virtual IlBoolean	equal(const IliValue&,const IliValue&) const;
    virtual int		compare(const IliValue&,const IliValue&) const;

    virtual IlBoolean	getAny(const IliValue&, IlAny&) const;
    virtual IlBoolean	setAny(IliValue&, IlAny) const;

protected:
    IliPointerTypeClass(const char* name);
    IlAny&		value(const IliValue&) const;
    virtual IlAny	lockAny(IlAny any) const;
    virtual void	unLockAny(IlAny any) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliStructuredTypeClass
: public IliPointerTypeClass
{
public:
    typedef IliTable* (*MakeTableFn)(IliSchema*, IlAny);

    IliStructuredTypeClass(const char*, IliSchema*);

    virtual IlBoolean	isAnonymous() const;

    virtual void	format(const IliValue&, IliString&,
			       const IliFormat&) const;
    virtual void	write(const IliValue&, IL_STDPREF ostream&) const;
    virtual void	read(IliValue&, IL_STDPREF istream&) const;

    virtual IlBoolean	isStructuredType() const;

    const IliSchema*	getSchema() const;
    virtual IliSchema*	getNestedSchema() const;

    virtual IlBoolean	getTable(const IliValue&, const IliTable*&) const;
    virtual IlBoolean	setTable(IliValue&, const IliTable*) const;
    virtual IlBoolean	shareTable(IliValue&, IliTable*) const;

    MakeTableFn		getMakeTableFn() const;
    void		setMakeTableFn(MakeTableFn);

    IlAny		getUserData() const;
    void		setUserData(IlAny);

    virtual IliTable*	makeTable() const;

    virtual void	emitType(IliString&) const = 0;
    void		setElaboratedName(const char*);

    enum Family {
	DefaultFamily,
	OracleFamily,
	InformixFamily
    };

    Family		getFamily() const;
    void		setFamily(Family);

    void		setAnonymous(IlBoolean);

protected:
    IliSchema*		_schema;
    MakeTableFn		_makeTableFn;
    IlAny		_userData;
    Family		_family;
    IlBoolean		_anonymous;

    virtual void	emitElements(IliString&) const;

    virtual void	setToken(IlInt);

    virtual IlAny	lockAny(IlAny) const;
    virtual void	unLockAny(IlAny) const;
    IliTable*		getTable(const IliValue&) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliTableTypeClass
: public IliStructuredTypeClass
{
public:
    IliTableTypeClass(const char* name, IliSchema* schema)
	: IliStructuredTypeClass(name, schema),
	  _containerType(TableContainer)
    {}

    virtual IlBoolean	setString(IliValue&, const char*, IlUInt) const;

    virtual IlBoolean	isTableType() const;
    virtual IlBoolean	emit(const IliValue&, IliString&,
			     const IliSession*) const;

    virtual void	writeDefinition(IL_STDPREF ostream&) const;

    enum ContainerType {
	TableContainer,
	ArrayContainer,
	ListContainer,
	SetContainer,
	MultiSetContainer
    };

    ContainerType	getContainerType() const;
    void		setContainerType(ContainerType);

    virtual IlBoolean	supportsNestedSQLStatements() const;

    virtual void	emitType(IliString&) const;

    void		emitTypePrefix(IliString&) const;
    void		emitTypeSuffix(IliString&) const;

    void		emitElementTypePrefix(IliString&) const;
    void		emitElementTypeSuffix(IliString&) const;

protected:
    ContainerType	_containerType;

    virtual const char*	getReaderName() const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliObjectTypeClass
: public IliStructuredTypeClass
{
public:
    IliObjectTypeClass(const char* name, IliSchema* schema)
	: IliStructuredTypeClass(name, schema)
    {}

    virtual IlBoolean	setString(IliValue&, const char*, IlUInt) const;

    virtual IlBoolean	isObjectType() const;
    virtual IlBoolean	emit(const IliValue&, IliString&,
			     const IliSession*) const;

    virtual void	writeDefinition(IL_STDPREF ostream&) const;

    virtual void	emitType(IliString&) const;
    void		emitTypePrefix(IliString&) const;
    void		emitTypeSuffix(IliString&) const;

protected:
    virtual const char*	getReaderName() const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliBinaryTypeClass
: public IliDatatype
{
public:
    IliBinaryTypeClass();
    IliBinaryTypeClass(const char* typeName);

    const char*		getPrettyKeyword() const;

    virtual
    IlvAlignment	getDefaultAlign() const;

    virtual void	init(IliValue&) const;
    virtual void	free(IliValue&) const;
    virtual void	nullify(IliValue&) const;
    virtual void	copy(const IliValue&, IliValue&) const;

    virtual IlBoolean	equal(const IliValue&, const IliValue&) const;
    virtual int		compare(const IliValue&, const IliValue&) const;

    virtual
    IliFormatType	getFormatType() const;
    virtual void	format(const IliValue&, IliString&,
			       const IliFormat&) const;

    virtual void	write(const IliValue&, IL_STDPREF ostream&) const;
    virtual void	read(IliValue&, IL_STDPREF istream&) const;
    virtual IlBoolean	emit(const IliValue&, IliString&,
			     const IliSession*) const;

    IlBoolean		setString(IliValue&, const char*, IlUInt) const;

    IlBoolean		getBinary(const IliValue&, IliBinary&) const;
    IlBoolean		setBinary(IliValue&, const IliBinary&) const;

    IlBoolean		isBinaryType() const;
    IlBoolean		hasConstSize() const;

    virtual IlBoolean	checkMaxLength(const IliValue&, IlInt) const;
    IlUInt		getBufferSize(const IliValue&) const;

    IlUInt		getOffset() const;

protected:
    inline void		unlockValue(const IliValue&) const;
    inline IlUInt	size(const IliValue&) const;
    inline IliBinary	value(const IliValue&) const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliReferenceTypeClass
: public IliBinaryTypeClass
{
public:
    IliReferenceTypeClass(const char*, IliObjectTypeClass* refrencedType);
    virtual ~IliReferenceTypeClass();

    virtual IlBoolean	isReferenceType() const;
    const char*		getPrettyKeyword() const;

    const IliObjectTypeClass* getReferenceType() const;

    virtual void	writeDefinition(IL_STDPREF ostream&) const;

private:
    IliObjectTypeClass*	_refrencedType;

    virtual const char*	getReaderName() const;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliDatatypeTypeClass
: public IliPointerTypeClass
{
public:
    IliDatatypeTypeClass();

    virtual int		compare(const IliValue&,const IliValue&) const;
    virtual void	format(const IliValue&,
			       IliString&,
			       const IliFormat&) const;
    virtual void	write(const IliValue&, IL_STDPREF ostream&) const;
    virtual void	read(IliValue&, IL_STDPREF istream&) const;

    virtual IlBoolean	setString(IliValue&, const char*, IlUInt) const;

    virtual IlBoolean	getDatatype(const IliValue&,
				    const IliDatatype*&) const;

    virtual IlBoolean	setDatatype(IliValue&, const IliDatatype* type) const;

protected:

    virtual IlAny	lockAny(IlAny) const;
    virtual void	unLockAny(IlAny) const;

    const IliDatatype*	getDatatype(const IliValue&) const;
};

// --------------------------------------------------------------------------
#if defined(ILICOMPAT_20)
#  define IliObjectDatatype IliPointerTypeClass
#endif

#ifdef DOXYGEN_GENERATION
const IliDatatype* IliNullType;
const IliDatatype* IliStringType;
const IliDatatype* IliLongStringType;
const IliDatatype* IliBooleanType;
const IliDatatype* IliByteType;
const IliDatatype* IliIntegerType;
const IliDatatype* IliFloatType;
const IliDatatype* IliDoubleType;
const IliDatatype* IliDecimalType;
const IliDatatype* IliDateType;
const IliDatatype* IliTimeType;
const IliDatatype* IliBinaryType;
const IliDatatype* IliAnyType;
#else
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliNullType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliStringType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliLongStringType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliBooleanType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliByteType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliIntegerType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliFloatType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliDoubleType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliDecimalType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliDateType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliTimeType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliBinaryType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliLongBinaryType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliAnyType;
extern ILV_INF_EXPORTEDVAR(const IliDatatype*) IliBitmapType;
extern ILV_INF_EXPORTEDVAR(const IliDatatypeTypeClass*) IliDatatypeType;
#endif

IliModuleDECL_exp(ILV_INF_EXPORTED,IliDatatype);

#endif /* !__Ili_Datatype_H */
