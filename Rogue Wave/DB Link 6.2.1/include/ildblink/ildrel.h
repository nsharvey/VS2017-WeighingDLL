// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildrel.h
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
// Schema tables descriptor classes
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDREL_H
#define __ILD_ILDREL_H

#ifndef __Il_Array_H
#   include <ilog/array.h>
#endif

#ifndef __ILD_ILDENT_H
# include <ildblink/ildent.h>
#endif
#ifndef __ILD_ILDDESC_H
# include <ildblink/ilddesc.h>
#endif

class IldRelation;

// ============================================================================
// IldColumn class.
// ============================================================================
class ILD_EXPORTED IldColumn : public IldDescriptor {

protected:
    IldRelation*	_relation;


public:
    IldColumn  (const char* name,
		IldColumnType type,
		const char* tName,		short sqlType,
		IlUInt size,
		short precision,
		short scale,
		IlBoolean nullable,
		IldRelation* rel = 0);

    IldColumn  ()
    {}

    virtual
    ~IldColumn ()
    {}

    inline
    const IldRelation& getRelation () const;
    inline void		setRelation(IldRelation*);
};

// ----------------------------------------------------------------------------
// Inlines
// ----------------------------------------------------------------------------
inline const IldRelation&
IldColumn::getRelation () const
{
    return *_relation;
}

inline void
IldColumn::setRelation (IldRelation* rel)
{
    _relation = rel;
}

class ILD_EXPORTED
IlDeclareArrayWithoutEquality(IldColumn*, IldColumnArray);

// ============================================================================
// IldKey class.
// ============================================================================
class ILD_EXPORTED IldKey {

protected:
    IldKeyType		_type;
    char*		_name;
    IldColumnArray	_colMgr;

public:
    IldKey          (IldKeyType type,
		     const char* name = 0);
    virtual
    ~IldKey         ();
    inline
    IldColumnArray&	getColumnsMgr   ();

    inline
    IlUShort		getCount        () const;

    inline
    const char*		getName         () const;

    inline
    const IldColumn*	getColumn       (IlUShort index) const;

    inline
    IlBoolean		isPrimary       () const;

    inline
    IlBoolean		isForeign       () const;

    inline
    IlBoolean		isSpecialColumn () const;

    inline
    IldKeyType		getKeyType      () const;
};

// ----------------------------------------------------------------------------
// Inlines for IldKey class
// ----------------------------------------------------------------------------
inline IldColumnArray&
IldKey::getColumnsMgr ()
{
    return _colMgr;
}

inline IlUShort
IldKey::getCount () const
{
    return (IlUShort)_colMgr.getLength();
}

inline const
char* IldKey::getName () const
{
    return _name;
}

inline const IldColumn*
IldKey::getColumn (IlUShort i) const
{
    return ((((IlUInt)i) >= _colMgr.getLength()) ? 0 : _colMgr[i]);
}

inline IlBoolean
IldKey::isPrimary () const
{
    return (IlBoolean)(_type == IldPrimaryKey);
}

inline IlBoolean
IldKey::isForeign () const
{
    return (IlBoolean)(_type == IldForeignKey);
}

inline IlBoolean
IldKey::isSpecialColumn () const
{
    return (IlBoolean)(_type == IldSpecialColumn);
}

inline IldKeyType
IldKey::getKeyType () const
{
    return _type;
}

class ILD_EXPORTED
IlDeclareArrayWithoutEquality(char*, IldPColumnArray);

// ============================================================================
// IldFKey class.
// ============================================================================
class ILD_EXPORTED IldFKey : public IldKey {

protected:
    IlInt		_id;
    char*		_pName;
    char*		_pTable;
    char*		_pOwner;
    IldPColumnArray	_pcolsMgr;

public:
    // Internal use only!
    IlBoolean		addPCol            (const char* colName);
    void		setPTable          (const char*);
    void		setPOwner          (const char*);
    void		setPName           (const char*);

    IldFKey            (IlInt id, 
			const char* name = 0);
    IldFKey            (const char* pTabName,
			const char* pTabOwner,
			const char* name = 0,
			const char* pName = 0);
    virtual
    ~IldFKey           ();

    inline
    IlInt		getId              () const;

    inline
    const char*		getPName           () const;

    inline
    const char*		getPTable          () const;

    inline
    const char*		getPOwner          () const;

    inline
    IlUShort		getPrimaryColCount () const;

    inline
    const char*		getPrimaryColumn   (IlUShort i) const;
};

// ----------------------------------------------------------------------------
// Inlines for IldFKey class
// ----------------------------------------------------------------------------
inline IlInt
IldFKey::getId () const
{
    return _id;
}

inline const char*
IldFKey::getPName () const
{
    return _pName;
}

inline const char*
IldFKey::getPTable () const
{
    return _pTable;
}

inline const char*
IldFKey::getPOwner () const
{
    return _pOwner;
}

inline IlUShort
IldFKey::getPrimaryColCount () const
{
    return (IlUShort)_pcolsMgr.getLength();
}

inline const char*
IldFKey::getPrimaryColumn (IlUShort i) const
{
    return (( ((IlUInt) i) >= _pcolsMgr.getLength()) ? 0 : _pcolsMgr[i]);
}

// ============================================================================
// IldTableIndex class.
// ============================================================================
class ILD_EXPORTED IldTableIndex: public IldKey {

protected:
    char*	_owner;
    IlBoolean	_unique;

public:
    IldTableIndex	(const char* name,
			 const char* owner,
			 IlBoolean uniq);
    virtual
    ~IldTableIndex	();

    inline
    const char*	getOwner       () const;

    inline
    IlBoolean	isUnique       () const;
};

// ----------------------------------------------------------------------------
// Inlines for IldTableIndex class
// ----------------------------------------------------------------------------
inline const char*
IldTableIndex::getOwner () const
{
    return _owner;
}

inline IlBoolean
IldTableIndex::isUnique () const
{
    return _unique;
}

// We want our array to end with an empty element.
// This way, when calling getArray() member function, we detect that the
// returned array has no more element when we reach the NULL pointer.
#define ILDARRAY(ArrayType, ElemType)                                    \
public:                                                                  \
  inline void add(const ElemType elem)     {                             \
    pop();                                                              \
    ArrayType::add(elem);                                               \
    ArrayType::add(0);                                                  \
  }                                                                      \
  inline IlUInt getLength() {                                            \
    return ArrayType::getLength() > 0 ? ArrayType::getLength() - 1 : 0; \
  };

class ILD_EXPORTED
IlDeclareArrayWithoutEquality(IldFKey*, IldFKeyA);

class ILD_EXPORTED
IlDeclareArrayWithoutEquality(IldTableIndex*, IldTableIndexA);

class ILD_EXPORTED IldFKeyArray : public IldFKeyA {
    ILDARRAY(IldFKeyA, IldFKey*)
	};

class ILD_EXPORTED IldTableIndexArray : public IldTableIndexA {
    ILDARRAY(IldTableIndexA, IldTableIndex*)
	};

// ============================================================================
// IldRelation class.
// ============================================================================
#define ILD_K_NOREAD 0
#define ILD_K_NOPK   1
#define ILD_K_HASPK  (1 << 1)
#define ILD_K_NOFK   (1 << 2)
#define ILD_K_HASFK  (1 << 3)
#define ILD_K_NOIND  (1 << 4)
#define ILD_K_HASIND (1 << 5)
#define ILD_K_NOSCOL (1 << 6)
#define ILD_K_HASSCL (1 << 7)

class ILD_EXPORTED IldRelation : public IldSchemaEntity {

protected:
    IldColumnArray      _columnsMgr;
    IldKey*		_pkey;
    IldFKeyArray        _fkeysMgr;
    IldTableIndexArray	_idxMgr;
    IldKey*             _scols;
    short		_keysMask;	// ORed values of defines

    IldRelation       ()
	: IldSchemaEntity(),
	  _pkey(0),
	  _scols(0),
	  _keysMask(0)
    {};
    IldRelation       (IldRelation&);
    IldRelation&        operator=         (IldRelation&)
    { return *this; }

public:
    IldRelation       (const char* name,
		       const char* owner,
		       IlInt id,
		       IldEntityType kind);
    virtual
    ~IldRelation      ();
    inline
    IldColumnArray&     getColumnsMgr     ();
    inline
    IldFKeyArray&       getFKeysMgr       ();
    inline
    IldTableIndexArray& getIndexesMgr     ();

    IldColumn*          getColumn         (const char* colName) const;

    IldColumn*          getColumn         (IlUShort index) const;

    inline
    IlUShort            getCount          () const;

    const char*         getColName        (IlUShort index) const;

    short               getColIndex       (const char* name) const;

    IldColumnType       getColType        (IlUShort index) const;

    const char*         getColSQLType     (IlUShort index) const;

    IlUInt              getColSize        (IlUShort index) const;

    IlBoolean           isColNullable     (IlUShort index) const;

    inline
    void                setPrimaryKey     (IldKey* pkey);
    IldKey*             getPrimaryKey     ();

    IldFKey**           getForeignKeys    ();

    IldTableIndex**     getIndexes        ();

    inline
    void                setSpecialColumns (IldKey* sc);
    IldKey*             getSpecialColumns ();

};

// ----------------------------------------------------------------------------
// Inlines for IldRelation class
// ----------------------------------------------------------------------------
inline IldColumnArray&
IldRelation::getColumnsMgr ()
{
    return _columnsMgr;
}

inline IldFKeyArray&
IldRelation::getFKeysMgr ()
{
    return _fkeysMgr;
}

inline IldTableIndexArray&
IldRelation::getIndexesMgr ()
{
    return _idxMgr;
}

inline IlUShort
IldRelation::getCount () const
{
    return (IlUShort)_columnsMgr.getLength();
}

inline void
IldRelation::setPrimaryKey (IldKey* pkey)
{
    if (pkey) {
	_pkey = pkey;
	_keysMask |= ILD_K_HASPK;
    } else
	_keysMask |= ILD_K_NOPK;
}

inline void
IldRelation::setSpecialColumns(IldKey* sc)
{
    if (sc) {
	_scols = sc;
	_keysMask |= ILD_K_HASSCL;
    } else
	_keysMask |= ILD_K_NOSCOL;
}

#endif // __ILD_ILDREL_H
