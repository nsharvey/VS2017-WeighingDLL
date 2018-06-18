// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/object.h
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
// Declaration of the IlvStObject class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Object_H
#define __IlvSt_Object_H

#if !defined(__Ilv_Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#  include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#  include <ilviews/base/iostream.h>
#endif
#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#  include <ilviews/base/value.h>
#endif

class IlvClassInfo;
class IlvStCommand;
class IlvStudio;
class IlvStError;
class IlvStCommandDescriptor;
class IlvStMessage;
class IlvStCommandHistory;
class IlvStErrorHistory;
class IlvStBuffer;
class IlvStMessage;

typedef IlvStCommand* (*IlvStCommandConstructor)(IlvStudio* editor);

typedef IlvStError* (*IlvStCommandFunction)(IlvStudio*, IlAny);
typedef void (*IlvStMessageCallbackType) (IlAny receiver,
					  IlvStudio*,
					  const IlvStMessage*,
					  IlAny arg);
typedef IlBoolean (* IlvStCallbackChecker)(IlSymbol*);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStString
{
public:
    IlvStString(const char* str = 0) : _str(IlCopyString(str)) {}
    IlvStString(const char* str, int len);
    IlvStString(int nNum);
    IlvStString(IlFloat f);
    IlvStString(IlUInt u);
    IlvStString(const IlvStString& src) : _str(0) { (*this) = src; }

    virtual ~IlvStString() { delete [] _str; }

    IlvStString&	append(const char* str1, const char* str2 = 0);
    IlvStString&	prepend(const char* str1, const char* str2 = 0);
    inline		operator const char*() const { return _str; }
    char*		get() const { return _str; }
    inline void		set(const char* str, IlBoolean copy = IlTrue)
			{
			    if (copy) {
				IlvStSetString(_str, str);
			    } else {
				_str = (char*)str;
			    }
			}
    inline IlBoolean	operator!() const { return IlvStIsBlank(_str); }
    inline IlBoolean	operator==(const IlvStString& op) const
			{
			    return IlvStEqual(op, _str);
			}
    inline IlBoolean	operator==(const char* str) const
			{
			    return IlvStEqual(_str, str);
			}
    inline IlBoolean	operator!=(const IlvStString& op) const
			{
			    return !IlvStEqual(op, _str);
			}
    inline IlBoolean	operator!=(const char* str) const
			{
			    return !IlvStEqual(str, _str);
			}
    inline IlvStString&	operator=(const char* str)
			{
			    IlvStSetString(_str, str);
			    return *this;
			}
    inline IlvStString&	operator=(const IlvStString& op)
			{
			    IlvStSetString(_str, op.get());
			    return *this;
			}
    inline IlvStString&	operator+=(const char* str)
			{
			    return append(str);
			}
    inline IlvStString&	operator+(const char* str) { return append(str); }
    IlvStString&	makeSpaces(size_t len);

    inline IlBoolean	isEmpty() const { return !_str || !*_str; }
    int			getLength() const;

protected:
    char*		_str;
}; // class IlvStString

// --------------------------------------------------------------------------
// Assert macros
#if defined(ILVDEBUG) && defined(_WINDOWS)
#  undef NDEBUG
#  include <assert.h>
#  define ILVST_ASSERT(exp) assert(exp)
#else
#  define ILVST_ASSERT(exp)
#endif

// --------------------------------------------------------------------------
// Casting macros
#if defined(sgi) || (defined(__alpha) && !defined(WIN32))
#define IlvStDeclareDownCasting() \
public: \
    virtual IlAny downCast(const IlvClassInfo* classInfo) const
#define IlvStDefineCast(classname, superclass) \
IlAny classname::downCast(const IlvClassInfo* classInfo) const \
{ return (classname::ClassInfo() == classInfo? (IlAny)this : superclass::downCast(classInfo)); }
#else  /* !sgi */
#  if defined(__HP_aCC) && (__HP_aCC >= 60000)
     // Remove warnings issued by HP aCC6.17
#    pragma diag_suppress 2815,2191
#  endif /* __HP_aCC >= 60000 */
#define IlvStDeclareDownCasting() \
public: \
    virtual IlAny downCast(const IlvClassInfo* classInfo); \
    virtual const IlAny downCast(const IlvClassInfo* classInfo) const
#define IlvStDefineCast(classname, superclass) \
IlAny classname::downCast(const IlvClassInfo* classInfo) \
{ return (classname::ClassInfo() == classInfo? (IlAny)this : superclass::downCast(classInfo)); } \
const IlAny classname::downCast(const IlvClassInfo* classInfo)const \
{ return (classname::ClassInfo() == classInfo? (const IlAny)this : superclass::downCast(classInfo)); }
#endif /* !sgi */

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStObject
{
public:
    IlvStObject() {}
    IlvStObject(const IlvStObject&) {}
    virtual ~IlvStObject();

    // ____________________________________________________________
    // Casting methods

    IlvStDeclareDownCasting();

    // Statics
public:
    static IlAny DownCast(const IlvClassInfo* classInfo, IlvStObject*);
    static
#if !defined(sgi)
	const
#endif /* !sgi */
	   IlAny ConstDownCast(const IlvClassInfo* classInfo,
			       const IlvStObject*);

    // ____________________________________________________________
    // Input / output
    virtual IlBoolean read(ILVSTDPREF istream&);
    virtual void write(ILVSTDPREF ostream&) const;

    IlvDeclarePropRootClassInfo();

#ifdef ILVALLOCCHECK
public:
    void* operator new(size_t stAllocateBlock,
		       const char* filename = 0,
		       int line = 0);
    void operator delete(void*);
    static void Delete(const char* filename, int line, IlvStObject*);
    virtual void dump(ILVSTDPREF ostream&);

    static IlArray _Blocs;
    static IlBoolean IsValid(const IlvStObject*);
    static void ScanMemoryLeaks();
#endif

};

ILVSTDPREF istream& operator>>(ILVSTDPREF istream&, IlvStObject&);
ILVSTDPREF ostream& operator<<(ILVSTDPREF ostream&, const IlvStObject&);

class ILVSTUDIOCLASS IlvStNamedObject
: public IlvStObject {
public:
  IlvStNamedObject(const char* name): _name(name) {}
  IlvStNamedObject(const IlvStNamedObject& src)
    : IlvStObject(src), _name(src._name) {}

  virtual void setName(const char* name);

  const char* getName() const;

#ifdef ILVALLOCCHECK
  virtual void dump(ILVSTDPREF ostream&);
#endif

private:
  IlvStString _name;

  IlvDeclarePropClassInfo();
}; // class IlvStNamedObject

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStHash
: public IlvStringHashTable {
public:
    IlvStHash() : IlvStringHashTable(17) {}
    // ____________________________________________________________
    void add(const IlvStNamedObject* obj);
    void add(const char*, const void*);
};

// --------------------------------------------------------------------------
typedef void (*IlvStCommandHistoryFunction)(IlvStCommand*, IlAny);
typedef void (*IlvStErrorHistoryFunction)(IlvStError*, IlAny);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStStringArray
: public IlArray {
public:
    virtual ~IlvStStringArray(); // deletes the strings
    // ____________________________________________________________
    void		addString(const char* str, IlUInt ndx = (IlUInt)-1);
    void		appendStrings(const IlvStStringArray&);
    void		setStrings(const IlvStStringArray&);
    inline const char*	operator[](IlUInt rank) const
			{
			    return (const char*)getArray()[rank];
			}
    IlBoolean		isBlank() const;
    IlBoolean		contains(const char*) const;
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCallback
{
public:
    virtual ~IlvStCallback() {}
    virtual IlvStError* doIt(IlvStudio*, IlvValue* arg = 0) = 0;
};

class ILVSTUDIOCLASS IlvStValue
: public IlvValue {
public:
  IlvStValue();
  IlvStValue(const IlvValue& src);
  IlvStValue(IlAny p);
  IlvStValue(IlInt n);
  IlvStValue(IlUInt n);
  IlvStValue(IlFloat f);
  IlvStValue(IlDouble d);
  IlvStValue(const ILV_TM_PREF tm* time);
  IlvStValue(const char* s);
  IlvStValue(IlBoolean b);
  IlvStValue(IlvColor* c);
  IlvStValue(IlvFont* f);
  IlvStValue(IlvPattern* p);
  IlvStValue(IlvColorPattern* p);
  IlvStValue(IlvLineStyle* l);
  IlvStValue(IlvFillStyle  f);
  IlvStValue(IlvFillRule  f);
  IlvStValue(IlvArcMode  f);
  IlvStValue(IlvAntialiasingMode f);
  IlvStValue(IlvDirection d);
  IlvStValue(IlvBitmap* b);
  IlvStValue(IlvValueInterface* v);
};

#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_object)
#endif /* IlvDECLAREINITCLASS */
#endif /* !__IlvSt_Object_H */
