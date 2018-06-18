// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/base/smartptr.h
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
// Declaration of the IlvSmartData and IlvSmartPointer classes
// --------------------------------------------------------------------------
#ifndef __Ilv_Base_Smartptr_H
#define __Ilv_Base_Smartptr_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if defined(ILVSTD)
#  include <cstdlib>
// cstdlib included for definition of size_t
#else
#  include <stdlib.h>
#endif

class ILVVWSEXPORTED IlvSmartData
{
public:
    enum CheckType {
	NoCheck,
	OnlyDynamic,
	Warn,
	Abort
    };

#if defined ( _MSC_VER ) || !defined(ILVSTD)
    void*		operator new (size_t);
#elif defined(sgi) && defined(_STANDARD_C_PLUS_PLUS)
       // <cstddef> seems to be as buggy on sgi as on msvc6
    void*		operator new (size_t);
#else
    void*		operator new(ILVSTDPREF size_t);
#endif
#if defined ( __hpux ) && ( __cplusplus < 199707L )
    // HPUX CC generates a warning when delete is not defined
    // along with new.
    // Later versions of aCC are able to detect
    // that the delete operator cannot be implemented here and 
    // will raise an error if you try to define it.
    void		operator delete(void* me) { ::delete me; }
#endif
    IlvSmartData();
    IlvSmartData(const IlvSmartData& data);
    virtual		~IlvSmartData();
    // ____________________________________________________________
    static CheckType	setCheck(CheckType);
    inline int		refCount() { return _state/2; }
    inline void		incrRef() { _state += 2; }
    void		decrRef();

protected:
    static int		_NextCreatedIsDynamic;

private:
    static CheckType	_Check;
    int			_state;
    inline int		isDynamic() const { return !(_state & 1); }
};


#define IlvPointerClass(SmartClass, DataClass, EXPORT)		\
class EXPORT SmartClass { 					\
public:								\
	DataClass* _data;					\
inline	void decrDataRef() const { if(_data) _data->decrRef(); }\
inline	void incrDataRef() const { if(_data) _data->incrRef(); }\
public: 							\
inline	SmartClass(): _data(0)	{}				\
inline	SmartClass(DataClass* d): _data(d) { incrDataRef(); } 	\
inline	SmartClass(const SmartClass& p)				\
		: _data(p._data) { incrDataRef(); }		\
inline	~SmartClass() { decrDataRef(); _data = 0; }		\
inline	SmartClass& operator = (DataClass* d)			\
	{ if (d != _data) { decrDataRef(); _data = d; incrDataRef(); }\
	  return *this;}					\
inline	int operator == (const DataClass* d) const { return _data == d;}\
inline	int operator != (const DataClass* d) const { return _data != d;}\
inline	int operator == (const SmartClass & p) const 		\
	{ return _data == p._data;} 				\
inline	int operator != (const SmartClass& p) const 		\
	{ return _data !=  p._data;} 				\
inline	DataClass* operator -> () const	{ return _data; } 	\
inline	DataClass& operator * () const	{ return *_data; } 	\
inline	operator DataClass* () const	{ return _data; } 	\
}; 								\


#define IlvDerivedPointerClass(SmartClass,BaseSmartClass,DataClass,EXPORT) \
class EXPORT SmartClass : public BaseSmartClass {			\
public:									\
  SmartClass() : BaseSmartClass ()			{}		\
  SmartClass(const SmartClass& p) : BaseSmartClass(p)	{}		\
  SmartClass(DataClass* d) : BaseSmartClass(d)		{}		\
  SmartClass& operator=(DataClass* d) {					\
      if (d != _data)	{						\
	  decrDataRef();						\
	  _data = d;							\
	  incrDataRef();						\
      }									\
      return *this;							\
  }									\
  DataClass* operator->() const { return IL_CAST(DataClass*,_data); }	\
  DataClass& operator*() const  { return *(IL_CAST(DataClass*,_data));} \
  operator DataClass*() const   { return IL_CAST(DataClass*,_data); }}

#endif	/* __Ilv_Base_Smartptr_H */
