// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildtuple.h
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
// Results and Parameters Set Class
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDTUPLE_H
#define __ILD_ILDTUPLE_H

#ifdef IL_STD
# ifndef _CSTRING_
#  include <cstring>
# endif
#else
# ifndef _STRING_H
#  include <string.h>
# endif
#endif

#ifndef __ILD_ILDCONST_H
#include <ildblink/ildconst.h>
#endif
#ifndef __ILD_ILDENT_H
#include <ildblink/ildent.h>
#endif
#ifndef __ILD_ILDDESC_H
# include <ildblink/ilddesc.h>
#endif

class IldRequest;

// ============================================================================
// Client side descriptor
// Kinda SQL99 APD & ARD, /!\ extends the IPD/IRD
// ============================================================================
class ILD_EXPORTED IldAppDescriptor : public IldDescriptor {

protected:
    IlUInt		_bufferSize;	// individual value size
    char*		_intVal;	// internaly managed value
    char*		_extVal;	// external
    char*		_refVal;	// original pointer (array usage)
    short*		_intNulls;	// indicators (internal)
    short*		_extNulls;	// external 
    short*		_refNulls;	// original pointer (array usage)
    int			_nullSize;	// null value size (unit is short)
    IlAny		_nativeVal;	// native value e.g OCIDateTime*

public:
    IldAppDescriptor	();
    virtual
	~IldAppDescriptor	();
    void	set			(IldAppDescriptor*);
    void	init			();

    void	setValue		(char* v,
					 IlBoolean ext = IlFalse);

    inline
    IlBoolean	isExtValue		() const;

    void	reset			();
    void	getRelativeRow		(IlInt idx);
    inline
    void	nextValue		();
    void	setNulls		(short* nulls,
					 IlBoolean ext = IlFalse);

    inline
    short*	getNulls		() const;

    inline
    IlBoolean	isExtNulls		() const;

    inline
    IlUInt	getBufferSize		() const;

    inline
    void	setBufferSize		(IlUInt size);

	// INTERNAL USE ONLY: do not use any of these
    inline
    void	setNullSize		(int size);
    inline
    IlUInt*	getBufferSizeAddr	();
    inline
    char**	getValueAddr		();
    inline
    short**	getNullsAddr		();
    inline
    IlUInt*	getSizeAddr		();

    char*	getValue		(IlUInt r = 0) const;

    IlUChar	getByteValue		(IlUInt r = 0) const;
    IlInt	getIntegerValue		(IlUInt r = 0) const;
    double	getRealValue		(IlUInt r = 0) const;
    const char*	getStringValue		(IlUInt r = 0) const;
    // INTERNAL USE ONLY: Infx driver, do not use any of these
    // IMPORTANT: driver is responsible for deletion
    inline
	void		setNativeValue	(IlAny v);
    inline 
	IlAny		getNativeValue	() const;
};

// ----------------------------------------------------------------------------
// Inlines
// ----------------------------------------------------------------------------

inline IlBoolean 
IldAppDescriptor::isExtValue () const
{
  return (IlBoolean)(_extVal != 0);
}

inline void 
IldAppDescriptor::nextValue ()
{
  getRelativeRow(1);
}

inline short*
IldAppDescriptor::getNulls () const
{
  return (_intNulls ? _intNulls : _extNulls);
}

inline IlBoolean
IldAppDescriptor::isExtNulls () const
{
  return (IlBoolean)(_extNulls != 0);
}

inline IlUInt
IldAppDescriptor::getBufferSize () const 
{
  return _bufferSize;
}

inline void
IldAppDescriptor::setBufferSize (IlUInt s)
{
  _bufferSize = s;
}

inline void 
IldAppDescriptor::setNullSize (int s)
{
  _nullSize = s;
}

inline IlUInt*
IldAppDescriptor::getBufferSizeAddr ()
{
  return &_bufferSize;
}

inline char**
IldAppDescriptor::getValueAddr ()
{
  return (_extVal ? &_extVal : &_intVal);
}

inline short**
IldAppDescriptor::getNullsAddr ()
{
  return (_extNulls ? &_extNulls : &_intNulls);
}

inline IlUInt*
IldAppDescriptor::getSizeAddr ()
{
  return &_size;
}

inline void
IldAppDescriptor::setNativeValue	(IlAny v)
{
	_nativeVal = v;
}

inline IlAny
IldAppDescriptor::getNativeValue	() const
{
	return _nativeVal;
}

// ============================================================================
// IldTuple class.
//
// Warning: This class is intentionnaly not documented. Only the interface of 
//          the wrapping class IldRequest should be used to access the contents
//          of instances of this class.
//	    All getter/setter functions assume the given values are legitimate:
//	    behavior is unpredictable if it is not the case.
//
// Instances of this class hold descriptions, values, and nulls either for a
// results set or for a parameters set.
// As number of columns in a results set or number of parameters in a request
// are always limited to rather small numbers, the count of columns/parameters
// and the actual size of the tuple holder are restricted to unsigned shorts.
// But number of returned rows, number of affected rows, and number of rows
// in the result set or parameter set have no limits; thus long or long long 
// are preferably used.
// ============================================================================
class ILD_EXPORTED IldTuple {

private:
    IlUShort			_count;
    IlUShort			_size;
    IldAppDescriptor*	_columns;
    IlUInt				_arraySize;	// Default is 1
    IlUInt				_rowCount;
    IlUInt				_curRow;	// !! SQL convention: starts at 1
    IlUInt              _firstPos;
    IlUInt              _lastPos;
    IlBoolean           _realPos;
    IlBoolean           _bufChanged;

public:
    IldTuple		();
    virtual
    ~IldTuple		();
    inline
    IldAppDescriptor*	getDescriptor		(IlUShort i) const;

    // Overall managment
    // -----------------
    inline
    void		setCount		(IlUShort card);
    inline
    IlUShort		getCount		() const;
    inline
    IlUShort		getSize			() const;
    inline
    IlBoolean		setArraySize		(IlUInt count);
    inline
    IlUInt		getArraySize		() const;
    inline
    void		setDataLines		(IlUInt count);
    inline
    IlUInt		getDataLines		() const;
    inline
    IlUInt		getCurrentLine		() const;
    inline
    IlUInt		setCurrentLine		(IlUInt r);
    inline
    IlUInt		getArrayFirstPos	() const;
    inline
    IlUInt		setLastPos		(IlUInt lastPos);
    inline
    void		setBufChanged		(IlBoolean bufChanged);
    inline
    IlBoolean		isBufChanged		();
    IlBoolean		resize			(IlBoolean = IlFalse,
						 IlUShort size = 0,
						 IlBoolean = IlFalse);
    IlBoolean		moveToNextLine		();
    IlBoolean		moveToLine		(IlInt = IldFetchDirectionNext,
						 IlInt = 0);
    void		reset			();

    // Column headers
    // --------------
    void		setDescriptor		(IlUShort c,
						 IlBoolean nullable,
						 IldColumnType type,
						 IlUInt size,
						 short sqlType,
						 const char* sqlTName,
						 short prec = 0,
						 short scale = 0,
						 const char* tOwner = 0);
    short		getIndex		(const char*) const;
    void		setName			(IlUShort,
						 const char*);
    inline
    const char*		getName			(IlUShort c) const;
    inline
    IldColumnType	getType			(IlUShort c) const;
    inline
    void		setType			(IlUShort c,
						 IldColumnType t);
    inline
    short		getSqlType		(IlUShort c) const;
    inline
    void		setSqlType		(IlUShort c,
						 const short t);
    inline
    const char*		getSqlTypeName		(IlUShort c) const;
    inline
    void		setSqlTypeName		(IlUShort c,
						 const char* name);
    inline
    short		getPrecision		(IlUShort c) const;
    inline
    void		setPrecision		(IlUShort c,
						 short prec);
    inline
    short		getScale		(IlUShort c) const;
    inline
    void		setScale		(IlUShort c,
						 short sca);
    inline
    IlUInt		getSize			(IlUShort c) const;
    inline
    void		setSize			(IlUShort c,
						 IlUInt size);
    inline
    IlBoolean		isNullable		(IlUShort c) const;
    inline
    void		setNullable		(IlUShort c,
						 IlBoolean flag);

    // Column data and nulls space
    // ---------------------------
    inline
    IlUInt		getBufferSize		(IlUShort c) const;
    inline
    void		setBufferSize		(IlUShort c,
						 IlUInt size);
    inline
    char*		getValuesBuffer		(IlUShort c) const;
    inline
    void		setValuesBuffer		(IlUShort c,
						 char* buff);
    inline
    short*		getNullsBuffer		(IlUShort c) const;
    inline
    void		setNullsBuffer		(IlUShort c,
						 short* nullsBuffer);  

    // Column/Row data handling
    // ------------------------
    inline
    void		putValue		(char v,
						 IlUShort c,
						 IlUInt r);
    inline
    void		putValue		(IlInt v,
						 IlUShort c,
						 IlUInt r);
    inline
    void		putValue		(double v,
						 IlUShort c,
						 IlUInt r);
    void		putValue		(const char*,
						 IlUShort,
						 IlUInt);
    void		putValue		(IldBytes&,
						 IlUShort,
						 IlUInt);
    inline
    IlUChar		getByteValue		(IlUShort c,
						 IlUInt r = 0) const;
    inline
    IlInt		getIntegerValue		(IlUShort c,
						 IlUInt r = 0) const;
    inline
    double		getRealValue		(IlUShort c,
						 IlUInt r = 0) const;
    inline
    const char*		getStringValue		(IlUShort c,
						 IlUInt r) const;
    // Suppress blanks on the right
    inline
    const char*		getPurgedStringValue	(IlUShort c,
						 IlUInt r = 0);
    // Suppress blanks only if char type, NOP for varchar type
    inline
    const char*		getRTrimedStringValue	(IlUShort c,
						 IlUInt r = 0);
    inline
    const char*		getLongTextValue	(IlUShort c,
						 IlUInt r = 0) const;
};

// ---------------------------------------------------------------------------
// Inlines 
// ---------------------------------------------------------------------------
inline IldAppDescriptor*
IldTuple::getDescriptor (IlUShort i) const
{
    return (i >= _count) ? 0 : &_columns[i];
}

inline void
IldTuple::setCount (IlUShort card)
{
    _count = card;
    setBufChanged(IlTrue);
}

inline IlUShort
IldTuple::getCount () const
{
    return _count;
}

inline IlUShort
IldTuple::getSize () const
{
    return _size;
}

inline IlBoolean
IldTuple::setArraySize (IlUInt count)
{
    if (_arraySize != count) {
	_arraySize = count;
	return IlTrue;
    } else
	return IlFalse;
}

inline IlUInt
IldTuple::getArraySize () const
{
    return _arraySize;
}

inline void
IldTuple::setDataLines (IlUInt count)
{
    _rowCount = count;
}

inline IlUInt
IldTuple::getDataLines () const
{
    return _rowCount;
}

inline IlUInt
IldTuple::getCurrentLine () const
{
    return _curRow;
}

inline IlUInt
IldTuple::setCurrentLine (IlUInt r)
{
    return _curRow = (r > _rowCount) ? _rowCount : r;
}

// Returns the position in the results set of the first row loaded
// in memory.
inline IlUInt
IldTuple::getArrayFirstPos () const
{
    return _firstPos;
}

inline IlUInt
IldTuple::setLastPos (IlUInt lastPos)
{
    return _lastPos = lastPos;
}

inline void
IldTuple::setBufChanged(IlBoolean bufChanged)
{
    _bufChanged = bufChanged;
}

inline IlBoolean
IldTuple::isBufChanged()
{
    return _bufChanged;
}

inline const char*
IldTuple::getName (IlUShort c) const
{
    return _columns[(int)c].getName();
}

inline IldColumnType
IldTuple::getType (IlUShort c) const
{
    return _columns[c].getType();
}

inline void
IldTuple::setType (IlUShort c,
		   IldColumnType t)
{
    _columns[c].setType(t);
}

inline short
IldTuple::getSqlType (IlUShort c) const
{
    return _columns[c].getSqlType();
}

inline void
IldTuple::setSqlType (IlUShort c,
		      const short t)
{
    _columns[c].setSqlType(t);
}

inline const char*
IldTuple::getSqlTypeName (IlUShort c) const
{
    return _columns[c].getSqlTypeName();
}

inline void
IldTuple::setSqlTypeName (IlUShort c,
			  const char* n)
{
    _columns[c].setTypeName(n);
}

inline short
IldTuple::getPrecision (IlUShort c) const
{
    return _columns[c].getPrecision();
}

inline void
IldTuple::setPrecision (IlUShort c,
			short p)
{
    _columns[c].setPrecision(p);
}

inline short
IldTuple::getScale (IlUShort c) const
{
    return _columns[c].getScale();
}

inline void
IldTuple::setScale (IlUShort c,
		    short s)
{
    _columns[c].setScale(s);
}

inline IlUInt
IldTuple::getSize (IlUShort c) const
{
    return _columns[c].getSize();
}

inline void
IldTuple::setSize (IlUShort c,
		   IlUInt s)
{
    _columns[c].setSize(s);
}

inline IlBoolean
IldTuple::isNullable (IlUShort c) const
{
    return _columns[c].isNullable();
}

inline void
IldTuple::setNullable (IlUShort c,
		       IlBoolean f)
{
    _columns[c].setNullable(f);
}

inline IlUInt
IldTuple::getBufferSize (IlUShort c) const
{
    return _columns[c].getBufferSize();
}

inline void
IldTuple::setBufferSize (IlUShort c,
			 IlUInt s)
{
    _columns[c].setBufferSize(s);
}

inline char*
IldTuple::getValuesBuffer (IlUShort c) const
{
    return _columns[c].getValue();
}

inline void
IldTuple::setValuesBuffer (IlUShort c,
			   char* b)
{
    _columns[c].setValue(b);
}

inline short*
IldTuple::getNullsBuffer (IlUShort c) const
{
    return _columns[c].getNulls();
}

inline void
IldTuple::setNullsBuffer (IlUShort c,
			  short* n)
{
    _columns[c].setNulls(n);
}

inline void
IldTuple::putValue (char v,
		    IlUShort c,
		    IlUInt r)
{
    _columns[c].getValue()[r] = v;
}

inline void
IldTuple::putValue (IlInt v,
		    IlUShort c,
		    IlUInt r)
{
    ((IlInt*)_columns[c].getValue())[r] = v;
}

inline void
IldTuple::putValue (double v,
		    IlUShort c,
		    IlUInt r)
{
    ((double*)_columns[c].getValue())[r] = v;
}

inline IlUChar
IldTuple::getByteValue (IlUShort c,
			IlUInt r) const
{
    return _columns[c].getByteValue(r);
}

inline IlInt
IldTuple::getIntegerValue (IlUShort c,
			   IlUInt r) const
{
    return _columns[c].getIntegerValue(r);
}

inline double
IldTuple::getRealValue (IlUShort c,
			IlUInt r) const
{
    return _columns[c].getRealValue(r);
}

inline const char*
IldTuple::getStringValue (IlUShort c,
			  IlUInt r) const
{
    return _columns[c].getStringValue(r);
}

inline const char*
IldTuple::getPurgedStringValue (IlUShort c,
				IlUInt r)
{
    return (const char*)IldStrRTrim((char*)getStringValue(c, r),
				    _columns[c].getBufferSize() + 1);
}

inline const char*
IldTuple::getRTrimedStringValue (IlUShort c,
				 IlUInt r)
{
    return (const char*)((_columns[c].getSqlType() == IldSQLChar) ?
			 IldStrRTrim((char*)getStringValue(c, r),
				     getBufferSize(c)) :
			 getStringValue(c, r));
}

inline const char*
IldTuple::getLongTextValue (IlUShort c,
			    IlUInt r) const
{
    return _columns[c].getValue()
	+ (r * _columns[c].getBufferSize());
}

#endif // __ILD_ILDTUPLE_H
