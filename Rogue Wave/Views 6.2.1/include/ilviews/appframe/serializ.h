// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/serializ.h
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
// Declaration of the IlvDvSerializable class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Serializ_H)
#define __Ilv_Appframe_Serializ_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Base_Value_H)
#include <ilviews/base/value.h>
#endif
#if !defined(__Ilv_Itf_Value_H)
#include <ilviews/intrface/value.h>
#endif

class IlvClassInfo;
class IlvDvStream;
class IlvDvDynClassInfo;

// --------------------------------------------------------------------------
// IlvDvSerializable class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvSerializable
{
public:
    virtual IlvDvDynClassInfo* getDynClassInfo() const { return 0; }
public:
    IlvDvSerializable() {}
    IlvDvSerializable(const IlvDvSerializable&) {}
    virtual ~IlvDvSerializable();

    // ____________________________________________________________
    // Casting methods

    IlvDvDeclareDownCasting();

    // Statics
public:
    static IlAny	DownCast(const IlvClassInfo* classInfo,
				 IlvDvSerializable*);
    static const void*	ConstDownCast(const IlvClassInfo* classInfo,
				      const IlvDvSerializable*);

    // ____________________________________________________________
    // Input / output
    virtual void	serialize(IlvDvStream& stream);

    IlvDeclarePropRootClassInfo();

#ifdef ILVALLOCCHECK
public:
    void* operator	new(size_t stAllocateBlock,
			    const char* filename = 0,
			    int line = 0);
    void operator	delete(void*);
    static void		Delete(const char* filename,
			       int line,
			       IlvDvSerializable*);
    virtual void	dump(ILVSTDPREF ostream&);

    static IlvArray	_Blocs;
    static IlBoolean	IsValid(const IlvDvSerializable*);
    static void		ScanMemoryLeaks();
#endif
};

// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvNamedObject : public IlvDvSerializable
{
public:
    IlvDvNamedObject(const char* name): _name(name) {}
    IlvDvNamedObject(const IlvDvNamedObject& src)
	: IlvDvSerializable(src), _name(src._name) {}

    virtual void	setName(const char*);
    inline const char*	getName() const { return _name; }

#ifdef ILVALLOCCHECK
    virtual void	dump(ILVSTDPREF ostream&);
#endif

private:
    IlvString		_name;

    IlvDeclarePropClassInfo();
}; // class IlvDvNamedObject

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITDVCLASS(serializ);
#endif /* IlvDECLAREINITCLASS */
// --------------------------------------------------------------------------

#endif /* ! __Ilv_Appframe_Serializ_H */
