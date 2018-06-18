// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/utils.h
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
// Declaration of usefull functions and classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Utils_H)
#define __Ilv_Appframe_Utils_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif
#if !defined(__Ilv_Appframe_Studio_Object_H)
#include <ilviews/appframe/studio/object.h>
#endif


class IlvGraphicHolder;
class IlvGraphic;
class IlvBitmap;
class IlvCursor;
class IlvDvStream;

// --------------------------------------------------------------------------
// IlvDvStringArray class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvStringArray : public IlvArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvStringArray(IlUInt initialLength = 8);
    IlvDvStringArray(const IlvDvStringArray&);
    virtual ~IlvDvStringArray();

    // ____________________________________________________________
    void		set(const char*, ...);
    void		copy(const IlvDvStringArray&);
    void		addString(const char* s)
			{
			    add((IlAny)new IlvString(s));
			}
    void		insertString(IlUInt rank, const char* s)
			{
			    insert(rank, (IlAny)new IlvString(s));
			}
    IlBoolean		removeString(const char*);
    IlBoolean		removeString(IlUInt);
    IlUInt		findString(const char*) const;
    inline IlvString&	getString(IlUInt iString) const
			{
			    return *(IlvString*)(*this)[iString];
			}

    void		emptyStrings();

    // ____________________________________________________________
    // Serialization
    virtual void	serialize(IlvDvStream& stream);
    void		serializeQuoted(IlvDvStream& stream);

protected:
    virtual void	_serialize(IlvDvStream& stream,
				   IlBoolean    quoted = IlFalse);
};

// --------------------------------------------------------------------------
// Usefull functions
ILVDVEXPORTEDFUNCTION(IlvGraphic*)
IlvDvFindGraphic(IlvGraphicHolder*,
		 const char* name,
	         IlvGraphicHolder** prealCont = 0);

ILVDVEXPORTEDFUNCTION(IlvGraphic*)
IlvDvFindGraphic(IlvGraphicHolder*,
		 IlvDvStudioObject*);

// --------------------------------------------------------------------------
ILVDVEXPORTEDFUNCTION(IlvBitmap*)
IlvDvLoadBitmap(IlvDisplay*, const char*);

ILVDVEXPORTEDFUNCTION(IlvCursor*)
IlvDvLoadCursor(IlvDisplay*,
		const char*,
		const char* bitmapPath,
		IlvPos,
		IlvPos);

ILVDVEXPORTEDFUNCTION(const IlvString&)
IlvDvFormatString(IlvString&, const char* fmt, ...);

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(utils);
// --------------------------------------------------------------------------
#endif /* __Ilv_Appframe_Utils_H */
