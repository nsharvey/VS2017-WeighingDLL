// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/schema.h
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
// Declaration of the IliSchema class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Schema_H
#define __Ili_Schema_H

#if !defined(__Ili_Common_H)
#  include <ilviews/dataccess/common.h>
#endif
#if !defined(__Ili_Datatype_H)
#  include <ilviews/dataccess/datatype.h>
#endif
#if !defined(__Ili_Tblhook_H)
#  include <ilviews/dataccess/tblhook.h>
#endif
#if !defined(__Ili_Inpmask_H)
#  include <ilviews/dataccess/inpmask.h>
#endif

class ILV_INF_EXPORTED IliSchema;

// --------------------------------------------------------------------------
class IliName
{
public:
    IliName(const char* name) { _name = name; }

    operator const char*() { return _name; }

protected:
    const char* _name;
};

// --------------------------------------------------------------------------
enum IliIndexMode {
    IliIndexNever,
    IliIndexAsNeeded,
    IliIndexAlways
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliColumn
: public IliCollectable
{
public:
    IliColumn();
    IliColumn(const IliColumn&);
    IliColumn(IL_STDPREF istream&);
    ~IliColumn();

    IliDeclareTypeInfo(IliColumn);
    virtual void	write(IL_STDPREF ostream&) const;
    int operator==(const IliColumn&) const;

    IlInt		getIndex() const { return _index; }
    void		setIndex(IlInt);

    IlInt		getToken() const { return _token; }
    void		setToken(IlInt);

    const char*		getName() const { return _name; }
    void		setName(const char*);

    const IliDatatype*	getType() const { return _type; }
    void		setType(const IliDatatype*);

    IlInt		getMaxlen() const { return _maxlen; }
    void		setMaxlen(IlInt);

    IlBoolean		isNullable() const { return _nullable; }
    void		setNullable(IlBoolean);

    IlBoolean		isPartOfKey() const { return _partOfKey; }
    void		setPartOfKey(IlBoolean);

    IlBoolean		isReadOnly() const { return _readOnly; }
    void		setReadOnly(IlBoolean);

    IlBoolean		isVisible() const { return _visible; }
    void		setVisible(IlBoolean);

    const char*		getDefaultValue() const { return _defaultValue; }
    void		setDefaultValue(const char*);

    const IliFormat&	getFormat() const { return _format; }
    void		setFormat(const IliFormat&);

    const IliInputMask& getMask() const { return _mask; }
    void		setMask(const IliInputMask&);

    IlvAlignment	getAlignment() const { return _align; }
    void		setAlignment(IlvAlignment);

    IlInt		getWidth() const { return _width; }
    void		setWidth(IlInt);

    const char*		getTitle() const { return _title; }
    void		setTitle(const char*);

    const char*		getLabel() const { return _label; }
    void		setLabel(const char*);

    IliColumn*		getHomonym() const { return _homonym; }
    void		setHomonym(IliColumn*);

    IlvValueInterface*	getItf() const;
    void		setItf(IlvValueInterface*);

protected:
    IlInt		_index;
    IlInt		_token;
    IliString		_name;
    const IliDatatype*	_type;
    IlInt		_maxlen;

    IlBoolean		_nullable;
    IlBoolean		_partOfKey;
    IlBoolean		_readOnly;
    IlBoolean		_visible;

    IliString		_defaultValue;
    IliFormat		_format;
    IliInputMask	_mask;
    IlvAlignment	_align;
    IlInt		_width;
    IliString		_title;
    IliString		_label;
    IlvValueInterface*	_itf;
    IliColumn*		_homonym;
};

IliDeclareTypeInit_exp(ILV_INF_EXPORTED, IliColumn);

IliDeclareCollection(INF, IliColumnCollection, IliColumn);

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliAttributePathIpl
: public IliRefCounted
{
public:
    IliAttributePathIpl();
    IliAttributePathIpl(const IliAttributePathIpl&);
    ~IliAttributePathIpl();

    void		read(IL_STDPREF istream&);
    void		write(IL_STDPREF ostream&) const;

    int operator==(const IliAttributePathIpl&) const;

    IlInt		getAttributeCount() const;
    const char*		getAttributeAt(IlInt) const;
    void		appendAttribute(const char*);
    void		removeAttribute(IlInt);

    void		emit(IliString&) const;

protected:
    IlvArray		_path;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED	IliAttributePath
{
public:
    IliAttributePath();
    IliAttributePath(const IliAttributePath&);
    ~IliAttributePath();

    void		read(IL_STDPREF istream& input);
    void		write(IL_STDPREF ostream& output) const;
    IliAttributePath& operator=(const IliAttributePath& path);
    int operator==(const IliAttributePath&) const;
    int operator!=(const IliAttributePath&) const;
    IlInt		getAttributeCount() const;
    const char*		getAttributeAt(IlInt idx) const;
    void		appendAttribute(const char* name);
    void		removeAttribute(IlInt idx);
    void		emit(IliString& dest) const;
    static
    IliAttributePath	Parse(const char* seq);

protected:
    void		makeSingle();

    IliAttributePathIpl* _ipl;
};

class IliSchemaPtrIpl;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliSchemaPtr
{
public:
    IliSchemaPtr();
    IliSchemaPtr(const IliSchemaPtr&);
    ~IliSchemaPtr();

    IliSchemaPtr& operator =(const IliSchemaPtr&);

    const IliSchema*	getSchema() const;
    IliSchema*		getSchema();

protected:
    IliSchemaPtr(IliSchemaPtrIpl*);

    IliSchemaPtrIpl*	_ipl;

    friend class IliSchema;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliSchema
: public IliCollectable, public IliRefCounted
{
public:
    IliSchema(IlvDisplay* display);
    IliSchema(const IliSchema&);
    IliSchema(IlvDisplay* display, IL_STDPREF istream& input);

protected:
    virtual ~IliSchema();

public:
    IliDeclareDTypeInfo(IliSchema);
    virtual void	write(IL_STDPREF ostream& output) const;
    int operator	==(const IliSchema&) const;
    IliSchema& operator =(const IliSchema&);

    IlvDisplay*		getDisplay() const;

    IliSchemaPtr	getSchemaPtr() const;
    IliSchemaPtr	getSchemaPtr();

    IlBoolean		hasASchemaName() const;
    const char*		getSchemaName() const;
    void		setSchemaName(const char* name);

    IlInt		isSchemaIdFresh() const;

    IlInt		getSchemaId() const;
    void		setSchemaId(IlInt id);

    const char*		getElementTypeName() const;
    void		setElementTypeName(const char* name);
    IlBoolean		isACollection() const;
    void		setAsCollection(IlBoolean flag);
    IlBoolean		isASimpleCollection() const;
    void		setAsSimpleCollection(IlBoolean flag);

    IlInt		getDatatypeToken() const;
    void		setDatatypeToken(IlInt);
    const IliDatatype*	asDatatype() const;

    const IliSchema*	getNestedSchema(const IliAttributePath& path) const;
    IliSchema*		getNestedSchema(const IliAttributePath& path);

    IlBoolean		pathTraversesCollection(const IliAttributePath&) const;

    // -- columns
    IlInt		getColumnsCount() const;
    IlInt		getColumnIndex(const char* name) const;
    IlInt		getColumnIndex(IlInt token) const;
    IlInt		getColumnToken(IlInt colno) const;
    const char*		getColumnName(IlInt colno) const;
    virtual void	setColumnName(IlInt colno, const char* colname);
    const IliDatatype*	getColumnType(IlInt colno) const;
    virtual void	setColumnType(IlInt colno, const IliDatatype* type);
    const IliSchema*	getColumnSchema(IlInt colno);
    IlInt		getColumnMaxLength(IlInt colno) const;
    virtual void	setColumnMaxLength(IlInt colno, IlInt maxlen);
    IlBoolean		isColumnNullable(IlInt colno) const;
    virtual void	setColumnNullable(IlInt colno, IlBoolean nullable);
    IlBoolean		isColumnPartOfKey(IlInt colno) const;
    virtual void	setColumnPartOfKey(IlInt colno, IlBoolean partOfKey);
    IlBoolean		isColumnReadOnly(IlInt colno) const;
    virtual void	setColumnReadOnly(IlInt colno, IlBoolean readOnly);
    const char*		getColumnDefault(IlInt colno) const;
    virtual void	setColumnDefault(IlInt colno, const char* val);
    const IliFormat&	getColumnFormat(IlInt colno) const;
    virtual void	setColumnFormat(IlInt colno, const IliFormat& fmt);
    const IliInputMask& getColumnMask(IlInt colno) const;
    virtual void	setColumnMask(IlInt colno, const IliInputMask& mask);
    IlvAlignment	getColumnAlignment(IlInt colno) const;
    virtual void	setColumnAlignment(IlInt colno, IlvAlignment align);
    IlInt		getColumnDisplayWidth(IlInt colno) const;
    virtual void	setColumnDisplayWidth(IlInt colno, IlInt width);
    IlBoolean		isColumnVisible(IlInt colno) const;
    virtual void	setColumnVisible(IlInt colno, IlBoolean visible);
    const char*		getColumnTitle(IlInt colno) const;
    virtual void	setColumnTitle(IlInt colno, const char* title);
    const char*		getColumnLabel(IlInt colno) const;
    virtual void	setColumnLabel(IlInt colno, const char* label);

    IlInt		getPrimaryKeyCount() const;
    const IliColumn*	getPrimaryKeyColumnAt(IlInt idx) const;
    IlBoolean		isPrimaryKeyDefined() const;

    virtual IlBoolean	insertColumn(IlInt colno,
				     const char* colname,
				     const IliDatatype* type,
				     IlInt maxlen = -1);
    IlInt		appendColumn(const char* name,
				     const IliDatatype* type,
				     IlInt maxlen = -1);
    virtual IlBoolean	deleteColumn(IlInt colno);
    virtual IlBoolean	moveColumn(IlInt from, IlInt to);

    virtual void	deleteAllColumns();
    virtual void	deleteEverything(IlBoolean delColsToo = IlTrue);
    virtual IlBoolean	allowColumnMove() const;

    // -- optim
    void		startOfBatch();
    void		endOfBatch();

    IlBoolean		hasIndexOnColumnName() const;
    IliIndexMode	getIndexOnColumnNameMode() const;
    void		setIndexOnColumnNameMode(IliIndexMode mode);

    IlBoolean		hasIndexOnColumnToken() const;
    IliIndexMode	getIndexOnColumnTokenMode() const;
    void		setIndexOnColumnTokenMode(IliIndexMode mode);

    enum Tag {
	DefaultNameIndexColumnCountThreshold  = 16,
	DefaultTokenIndexColumnCountThreshold = 32
    };

    static IlInt	NameIndexColumnCountThreshold;
    static IlInt	TokenIndexColumnCountThreshold;

    // -- hooks

    IlBoolean		areHooksDisabled() const { return _hooksDisabled; }
    IlBoolean		disableHooks(IlBoolean f);
    void		addHook(IliTableHook* hook);
    void		removeHook(IliTableHook* hook);
    IlBoolean		hasHook(IliTableHook* hook) const;

    virtual void	defineUsing(const IliSchema*);

    IlvValueInterface*	getItf() const;
    IlvValueInterface*	getColumnItf(IlInt colno) const;

    const IliColumnCollection& getColumnCollection() const { return _columns; }

    IlBoolean		hasStructuredColumns() const;

    static void		AtInit();
    static void		AtExit();

protected:
    IlBoolean		_hooksDisabled;
    IlvList		_hooks;
    IlvDisplay*		_display;
    IlvValueInterface*	_itf;
    IliSchemaPtrIpl*	_ptrIpl;

    IliColumnCollection _columns;
    IliColumnCollection _primaryKey;
    IlInt		_nextToken;
    IliIndexMode	_columnsByNameMode;
    IlvStringHashTable* _columnsByName;
    IliIndexMode	_columnsByTokenMode;
    IlvHashTable *	_columnsByToken;
    const IliClassInfo* _columnClassInfo;
    IliString		_schemaName;
    IlInt		_schemaId;
    IlBoolean		_isSchemaIdFresh;
    IliString		_elementTypeName;
    IlBoolean		_isACollection;
    IlBoolean		_isASimpleCollection;
    IlInt		_datatypeToken;
    IlInt		_structuredColumnCount;

    IliSchema(IlvDisplay*, const IliClassInfo*);
    IliSchema(const IliSchema&, const IliClassInfo*);
    IliSchema(IlvDisplay*, IL_STDPREF istream&, const IliClassInfo*);

    virtual
    IlvValueInterface*	makeItf() const;
    virtual
    IlvValueInterface*	makeColumnItf(IlInt) const;

    const IliColumn*	getColumnAt(IlInt) const;
    IliColumn*		getColumnAt(IlInt);

    void		init(const IliClassInfo* = 0);
    void		init(const IliSchema&, const IliClassInfo* = 0);
    void		init(IL_STDPREF istream&, const IliClassInfo* = 0);
    void		appendSchema(const IliSchema&);
    void		copySchema(const IliSchema&);

    IlBoolean		insertColumnAt(IlInt, IliColumn*);
    IlBoolean		clearColumn(IlInt);
    void		fillPrimaryKey();
    void		renumberColumns();
    void		countStructuredColumns();

    void		deepCopy(const IliSchema&);

    virtual IliColumn*	newColumn();
    IlBoolean		checkCol(IlInt) const;

    inline const IliClassInfo* getColumnClass() const
	{ return _columnClassInfo; }

    void		checkColumnNameIndex();
    void		checkColumnTokenIndex();

    void		indexColumnOnName(IliColumn*);
    void		indexColumnOnToken(IliColumn*);
    void		indexColumn(IliColumn*);

    void		unIndexColumnOnName(IliColumn*);
    void		unIndexColumnOnToken(IliColumn*);
    void		unIndexColumn(IliColumn*);

    void		pushContext() const;
    const IliSchema*	popContext() const;
    static
    const IliSchema*	topContext();

    friend class IliModuleCLASS(IliSchemaModule);

    void		tidyPtr();

    // Hooks
    virtual void	schemaNameChanged();
    virtual void	elementTypeNameChanged();

    virtual void	columnInserted(IlInt);
    virtual void	columnChanged(IlInt);
    virtual void	columnToBeDeleted(IlInt);
    virtual void	columnDeleted(IlInt);
    virtual void	columnMoved(IlInt, IlInt);

    virtual void	columnNameChanged(IlInt);
    virtual void	columnDisplayWidthChanged(IlInt);

    virtual void	sqlTextChanged(IlInt);

    friend class IliColumn;
    friend class IliSQLQueryBase;
    friend class IliHookForSchema;
};

// --------------------------------------------------------------------------
#if !defined(__Ili_Schemitf_H)
#  include <ilviews/dataccess/intrface/schemitf.h>
#endif

IliDeclareTypeInit_exp(ILV_INF_EXPORTED, IliSchema);
IliDeclareCollection(INF, IliSchemaCollection, IliSchema);

#endif /* !__Ili_Schema_H */
