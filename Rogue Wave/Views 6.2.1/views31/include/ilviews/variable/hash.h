// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: views31/include/ilviews/variable/hash.h
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
//
// Defined in library ilvvar31
// --------------------------------------------------------------------------
#ifndef __Ilv31_Variable_Hash_H
#define __Ilv31_Variable_Hash_H

#if !defined(__Ilv31_Macros_H)
#include <ilviews/macros31.h>
#endif
#if !defined(__Ilv31_Variable_Compilrs_H)
#include <ilviews/variable/compilrs.h>
#endif
#if !defined(__Ilv31_Variable_Boolean_H)
#include <ilviews/variable/boolean.h>
#endif
#if !defined(__Ilv31_Variable_Mlk_H)
#include <ilviews/variable/mlk.h>
#endif

#if defined(__GNUC__) || defined(WINDOWS)
#define ILVV_HASH_DEFAULT_MAX_BUCKET_LENGTH 12
#define ILVV_HASH_DEFAULT_GROWING_THRESHOLD (ILVV_HASH_DEFAULT_MAX_BUCKET_LENGTH/2)
#define ILVV_HASH_DEFAULT_GROWING_FACTOR 1.6
#define ILVV_HASH_DEFAULT_SHRINKING_THRESHOLD 2
#define ILVV_HASH_DEFAULT_SHRINKING_FACTOR 2.0
#define ILVV_HASH_DEFAULT_BIGGEST_SIZE 9239
#define ILVV_HASH_DEFAULT_LOWEST_SIZE 17
#else  /* !__GNUC__ && !WINDOWS */
extern const int   ILVV_HASH_DEFAULT_MAX_BUCKET_LENGTH;
extern const int   ILVV_HASH_DEFAULT_GROWING_THRESHOLD;
extern const float ILVV_HASH_DEFAULT_GROWING_FACTOR;
extern const int   ILVV_HASH_DEFAULT_SHRINKING_THRESHOLD;
extern const float ILVV_HASH_DEFAULT_SHRINKING_FACTOR;
extern const int   ILVV_HASH_DEFAULT_BIGGEST_SIZE;
extern const int   ILVV_HASH_DEFAULT_LOWEST_SIZE;
#endif /* !__GNUC__ && !WINDOWS */

extern "C" long IlvvIntHash(int tag, int size);
extern "C" long IlvvLongHash(long tag, int size);
extern "C" long IlvvULongHash(unsigned long tag,  int size);
extern "C" long IlvvVoidPHash(const void* tag, int size);
extern "C" long IlvvStringHash(const char* s, int size);
extern "C" int IlvvGoodPrimeNumber(int number);
extern "C" IlvvBoolean IlvvStringMatch(char* s1, char* s2);

// --------------------------------------------------------------------------
//    IlvvHashTable
// --------------------------------------------------------------------------

#define ILVV_HASH_DESC(TableType) TableType##Desc

#define ILVV_HASH_DEF(IlvvHashTable,ValueType,TagType) \
ILVV_TMPL_HASH_DEF(IlvvHashTable,IlvvHashTable##Entry,IlvvHashTable##Bucket,ILVV_HASH_DESC(IlvvHashTable),ValueType,TagType)

#define ILVV_HASH_BODY1(IlvvHashTable,ValueType,TagType,NullValue) \
ILVV_TMPL_HASH_BODY1(IlvvHashTable,IlvvHashTable##Entry,IlvvHashTable##Bucket,ILVV_HASH_DESC(IlvvHashTable),ValueType,TagType,NullValue)
#define ILVV_HASH_BODY2(IlvvHashTable,ValueType,TagType,NullValue) \
ILVV_TMPL_HASH_BODY2(IlvvHashTable,IlvvHashTable##Entry,IlvvHashTable##Bucket,ILVV_HASH_DESC(IlvvHashTable),ValueType,TagType,NullValue)
#define ILVV_HASH_BODY3(IlvvHashTable,ValueType,TagType,NullValue) \
ILVV_TMPL_HASH_BODY3(IlvvHashTable,IlvvHashTable##Entry,IlvvHashTable##Bucket,ILVV_HASH_DESC(IlvvHashTable),ValueType,TagType,NullValue)

#define ILVV_TMPL_HASH_DEF(IlvvHashTable,HashEntry,HashBucket,IlvvHashDesc,ValueType,TagType)\
class ILV31VAREXPORTED HashEntry \
{ \
 public: \
   ValueType _value; \
   HashEntry* _next; \
   ~HashEntry(); \
   HashEntry(ValueType value,HashEntry* next = 0); \
   ILVV_MLK_GDECL(); \
}; \
class ILV31VAREXPORTED HashBucket \
{ \
 public: \
   int _count; \
   HashEntry *_first; \
   HashBucket(); \
   ~HashBucket(); \
   ILVV_MLK_GDECL(); \
}; \
class ILV31VAREXPORTED IlvvHashTable{ \
    friend class IlvvHashDesc; \
 protected: \
    HashBucket* _buckets; \
    int     _size; \
    int     _count; \
    int     _links; \
    void growingRehash(); \
    void shrinkingRehash(); \
    void rehash(int newp); \
    void insert(long hash, \
		ValueType value, \
		TagType tag, \
		IlvvBoolean force_flag); \
    void remove(long hash,\
		TagType tag, \
		IlvvBoolean force_flag); \
    virtual void extraInsert(ValueType); \
    virtual void extraRemove(ValueType); \
 private: \
    IlvvHashTable(const IlvvHashTable&); \
    void connect(); \
    void disconnect(); \
    IlvvHashTable& operator = (const IlvvHashTable&); \
 public: \
    IlvvHashTable(int maxentries = ILVV_HASH_DEFAULT_LOWEST_SIZE); \
    virtual ~IlvvHashTable(); \
    virtual void clear(); \
    IlvvHashTable& operator<<(ValueType value); \
    int count() const; \
    int links() const; \
    void getNextEntry(int& hash,HashEntry*& entry) const; \
    void getFirstEntry(int& hash,HashEntry*& entry) const; \
    ValueType* tableToArray(int& i); \
    IlvvBoolean isPresent(ValueType value) const; \
    IlvvBoolean isIn(TagType tag) const; \
    IlvvHashTable& put(ValueType value); \
    IlvvHashTable& putF(ValueType value); \
    IlvvHashTable& suppress(TagType tag); \
    IlvvHashTable& remove(ValueType value); \
    IlvvHashTable& suppressF(TagType tag); \
    IlvvHashTable& removeF(ValueType value); \
    ValueType get(TagType tag) const; \
}; \
class ILV31VAREXPORTED IlvvHashDesc  \
{ \
  private:  \
    IlvvHashTable &_table; \
    IlvvBoolean _opened;  \
    IlvvBoolean _eot; \
    int _hash; \
    IlvvHashDesc(const IlvvHashDesc&); \
    HashEntry *_entry; \
  public: \
    IlvvHashDesc(IlvvHashTable& table); \
    ~IlvvHashDesc(); \
    IlvvHashDesc& operator>>(ValueType& value);\
    ValueType read(); \
    IlvvBoolean eot(); \
    void open(); \
    void close(); \
    IlvvHashTable& getTable() const {return _table;} \
};

// a dummy copy constructor is defined only for g++
// in the hash table ctor, the _buckets data member is not initialized
// in the initialization list because of a bug in visual C++ 1.0
#define ILVV_TMPL_HASH_BODY1(HashTable,HashEntry,HashBucket,IlvvHashDesc,ValueType,TagType,ValueTypeNull) \
ILVV_MLK_GDEF(HashEntry) \
ILVV_MLK_GDEF(HashBucket) \
HashEntry::HashEntry(ValueType value, HashEntry* next): _value(value), _next(next){} \
HashEntry::~HashEntry() { delete _next; } \
HashBucket::HashBucket(): _count(0), _first(0){} \
HashBucket::~HashBucket() { delete _first; } \
HashTable::HashTable(int c) : _size(c), _count(0), _links(0) \
{ \
    _buckets = (HashBucket*)new char[c*sizeof(HashBucket)]; \
    for (int i = 0; i < c; i++) { \
	_buckets[i]._count = 0; \
	_buckets[i]._first = 0; \
    } \
} \
HashTable::HashTable(const HashTable&){} \
HashTable::~HashTable(){ delete [] (char*)_buckets; } \
void HashTable::clear(){ \
  if(_links) IlvFatalError("vvHashTable::clear: opened table"); \
  delete [] (char*)_buckets; \
  _buckets = (HashBucket*)new char[ILVV_HASH_DEFAULT_LOWEST_SIZE*sizeof(HashBucket)]; \
    for (int i = 0; i < ILVV_HASH_DEFAULT_LOWEST_SIZE; i++) { \
	_buckets[i]._count = 0; \
	_buckets[i]._first = 0; \
    } \
  _count = 0; \
  _size = ILVV_HASH_DEFAULT_LOWEST_SIZE; \
} \
IlvvBoolean HashTable::isPresent(ValueType value)const{return isIn(ILVV_GET_TAG(value));} \
IlvvBoolean HashTable::isIn(TagType tag)const{ \
  HashEntry* entry = _buckets[ILVV_HASH(tag,_size)]._first; \
  while(entry){ \
   if(ILVV_MATCH(tag,ILVV_GET_TAG(entry->_value))) return IlvvTrue; \
   entry = entry->_next; \
  } \
  return IlvvFalse; \
} \
void HashTable::insert(long hash,ValueType value,TagType tag,IlvvBoolean force_flag){ \
  if(!force_flag){ \
    HashEntry* entry = _buckets[hash]._first; \
    while(entry){\
     if(ILVV_MATCH(tag,ILVV_GET_TAG(entry->_value))) \
	IlvFatalError("vvHashTable::insert: element already in table"); \
     entry = entry->_next; \
    } \
  } \
  HashEntry* newHashEntry = new HashEntry(value, _buckets[hash]._first); \
  _buckets[hash]._first = newHashEntry; \
  (_buckets[hash]._count)++; \
  _count++; \
  int ratio = _count/_size; \
  if((((_buckets[hash]._count>ILVV_HASH_DEFAULT_MAX_BUCKET_LENGTH)&&(ratio>2))||(ratio>ILVV_HASH_DEFAULT_GROWING_THRESHOLD))&&(_size != ILVV_HASH_DEFAULT_BIGGEST_SIZE)) growingRehash(); \
  extraInsert(value); \
} \
void HashTable::getFirstEntry(int& hash,HashEntry*&entry)const{ \
  hash = 0; \
  entry = (HashEntry*)0; \
  for(int i = 0;i<_size;i++)  \
    if(_buckets[i]._first){ \
      hash = i; \
      entry = _buckets[i]._first; \
      break;  \
    } \
} \
void HashTable::getNextEntry(int& hash,HashEntry*&entry)const{ \
  if(entry->_next) entry = entry->_next; \
  else{ \
    hash++; \
    entry = (HashEntry*)0; \
    for (int i = hash;i<_size;i++)  \
    if (_buckets[i]._first){ \
     hash = i; \
     entry = _buckets[i]._first; \
     break; \
    } \
  } \
} \
ValueType* HashTable::tableToArray(int& nb){ \
  nb = 0;  \
  if (!_count) { return 0; } \
  ValueType* array = new ValueType[_count]; \
  HashBucket* buckets = _buckets; \
  HashEntry* entry; \
  for (int i = 0; i < _size; i++) { \
   entry = buckets[i]._first; \
   while(entry){ \
     array[nb] = entry->_value; \
     nb++; \
     entry = entry->_next; \
   }\
  }\
  return array; \
}

#define ILVV_TMPL_HASH_BODY2(HashTable,HashEntry,HashBucket,IlvvHashDesc,ValueType,TagType,ValueTypeNull) \
int HashTable::count()const{return _count;} \
int HashTable::links()const{return _links;} \
void HashTable::connect(){_links++;} \
void HashTable::disconnect(){_links--;} \
HashTable& HashTable::put(ValueType value){ \
  if (_links) IlvFatalError("vvHashTable::put: element in opened table"); \
  TagType tag = ILVV_GET_TAG(value); \
  insert(ILVV_HASH(tag,_size),value,tag,IlvvFalse); \
  return *this; \
} \
HashTable& HashTable::putF(ValueType value){ \
  if(_links) IlvFatalError("vvHashTable::putF: element in opened table"); \
  TagType tag = ILVV_GET_TAG(value); \
  insert(ILVV_HASH(tag,_size),value,tag,IlvvTrue); \
  return *this; \
} \
HashTable& HashTable::operator<<(ValueType value){return put(value);} \
HashTable& HashTable::suppress(TagType tag){remove(ILVV_HASH(tag,_size),tag,IlvvFalse);return *this;} \
HashTable& HashTable::remove(ValueType value){remove(ILVV_HASH(ILVV_GET_TAG(value),_size),ILVV_GET_TAG(value),IlvvFalse);return *this;} \
void HashTable::extraInsert(ValueType){} \
void HashTable::extraRemove(ValueType){} \
HashTable& HashTable::suppressF(TagType tag){remove(ILVV_HASH(tag,_size),tag,IlvvTrue);return *this;} \
HashTable& HashTable::removeF(ValueType value){remove(ILVV_HASH(ILVV_GET_TAG(value),_size),ILVV_GET_TAG(value),IlvvTrue);return *this;} \
void HashTable::growingRehash(){ \
  int newmaxentries = (int)((float)_size * ILVV_HASH_DEFAULT_GROWING_FACTOR); \
  int newsize = IlvvGoodPrimeNumber(newmaxentries); \
  rehash(newsize); \
} \
ValueType HashTable::get(TagType tag)const{ \
  long hashval = ILVV_HASH(tag,_size); \
  for(HashEntry* entry = _buckets[hashval]._first;entry != (HashEntry*)0;entry = entry->_next) if(ILVV_MATCH(tag,ILVV_GET_TAG(entry->_value))) return entry->_value; \
  return ValueTypeNull; \
}

// a dummy copy constructor for the table descriptor is defined for g++
#define ILVV_TMPL_HASH_BODY3(HashTable,HashEntry,HashBucket,IlvvHashDesc,ValueType,TagType,ValueTypeNull) \
void HashTable::remove(long hash,TagType  tag, IlvvBoolean force_flag){ \
  if(_links) IlvFatalError("vvHashTable::remove: element in opened table"); \
  HashEntry* entry = _buckets[hash]._first; \
  HashEntry* prev = (HashEntry*)0; \
  while(entry){ \
   if(ILVV_MATCH(tag,ILVV_GET_TAG(entry->_value))) break; \
   else{ \
    prev = entry; \
    entry = entry->_next; \
   } \
  } \
  if(entry){ \
   extraRemove(entry->_value); \
   if(prev) prev->_next = entry->_next; \
   else _buckets[hash]._first = entry->_next; \
   entry->_next = 0; \
   delete entry; \
   (_buckets[hash]._count)--; \
   _count--; \
   shrinkingRehash(); \
  } else \
  if (!force_flag) IlvFatalError("vvHashTable::remove: element not in table"); \
} \
void HashTable::rehash(int newsize){ \
  int oldsize = _size; \
  _size = newsize; \
  HashBucket* oldbuckets = _buckets; \
  _buckets = (HashBucket*)new char[_size*sizeof(HashBucket)]; \
  int i; \
  for (i = 0; i < _size; i++) { \
      _buckets[i]._count = 0; \
      _buckets[i]._first = 0; \
  } \
  HashEntry* p,*next; \
  long hashval; \
  for(i = 0;i<oldsize;i++){ \
    p = oldbuckets[i]._first; \
    while(p){ \
      next = p->_next; \
      hashval = ILVV_HASH(ILVV_GET_TAG(p->_value),_size); \
      p->_next = _buckets[hashval]._first; \
      _buckets[hashval]._first = p; \
      _buckets[hashval]._count++; \
      p = next; \
    } \
  } \
  for(i = 0;i<oldsize;i++) oldbuckets[i]._first = (HashEntry*)0; \
  delete [] (char*)oldbuckets; \
} \
void HashTable::shrinkingRehash() \
{ \
  if(!(((_count/_size)<ILVV_HASH_DEFAULT_SHRINKING_THRESHOLD)&&(_size<ILVV_HASH_DEFAULT_LOWEST_SIZE))) return; \
  int newmaxentries = (int)(_size/ILVV_HASH_DEFAULT_SHRINKING_FACTOR); \
  int newsize = IlvvGoodPrimeNumber(newmaxentries); \
  rehash(newsize); \
} \
 \
IlvvHashDesc::IlvvHashDesc(HashTable& table): _table(table),_opened(IlvvFalse),_eot(IlvvFalse),_hash(0),_entry(0){} \
IlvvHashDesc::~IlvvHashDesc(){close();} \
IlvvHashDesc& IlvvHashDesc::operator>>(ValueType& value){value = read();return *this;} \
ValueType IlvvHashDesc::read(){ \
  ValueType v = ValueTypeNull; \
  if(!_opened) open(); \
  if(!_entry) _eot = IlvvTrue;\
  else{ \
    v = _entry->_value; \
    _table.getNextEntry(_hash,_entry); \
    if(!_entry) _eot = IlvvTrue; \
  } \
  return v; \
} \
IlvvHashDesc::IlvvHashDesc(const IlvvHashDesc& rhs): _table(rhs.getTable()){} \
IlvvBoolean IlvvHashDesc::eot(){if(!_opened) open(); return _eot;} \
void IlvvHashDesc::open(){ \
  if(_opened) IlvFatalError("vvHashDesc::open: already opened table"); \
  _table.connect(); \
  _opened = IlvvTrue; \
  _table.getFirstEntry(_hash,_entry); \
  if(!_entry) _eot = IlvvTrue; \
} \
void IlvvHashDesc::close(){ \
  if(!_opened) return; \
  _table.disconnect(); \
  _opened = IlvvFalse; \
  _eot = IlvvFalse; \
  _entry = 0; \
}

ILVV_HASH_DEF(IlvvVoidPTable,void*,void*)
ILVV_HASH_DEF(IlvvCharPTable,char*,char*)

#endif
