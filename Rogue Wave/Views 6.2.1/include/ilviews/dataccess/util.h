// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/util.h
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
// Declaration of miscellaneous functions
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Util_H
#define __Ili_Util_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_H)
#  include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Graphics_Icon_H)
#  include <ilviews/graphics/icon.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#  include <ilviews/gadgets/stdialog.h>
#endif
#if !defined(__Ili_Macros_H)
#  include <ilviews/dataccess/macros.h>
#endif
#if !defined(__Ili_Cstenum_H)
#  include <ilviews/dataccess/cstenum.h>
#endif
#if !defined(__Ili_Refcount_H)
#  include <ilviews/dataccess/refcount.h>
#endif
#if defined(IL_STD)
#  include <iostream>
#else  /* !IL_STD */
#  include <iostream.h>
#endif /* !IL_STD */

class ILVDSPEXPORTED IlvRect;
class ILVGDTEXPORTED IlvDialog;
class ILVVWSEXPORTED IlvGraphic;
class ILVVWSEXPORTED IlvGadgetHolder;
class ILVVWSEXPORTED IlvGraphicHolder;

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliUtil
{
public:
    static IlvGraphicHolder* GetHolderContext();
    static void PushHolderContext(IlvGraphicHolder*);
    static IlvGraphicHolder* PopHolderContext();

    static IlBoolean IsInDesignMode();
    static void SetDesignMode(IlBoolean);

    static IlBoolean IsInAStudioBuffer(IlvGraphicHolder*);
    static IlBoolean IsHolderValid(IlvGraphicHolder*);

    typedef IlBoolean (*HolderFn)(IlvGraphicHolder*, IlAny);

    static void SetIsInStudioBufferFn(HolderFn, IlAny);
    static void SetIsHolderValidFn(HolderFn, IlAny);
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliCallback
: public IliRefCounted
{
public:
    IliCallback() {}
    virtual ~IliCallback();

    virtual void call(IlAny) = 0;
};

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliCallbackArray
{
public:
    IliCallbackArray() {}
    ~IliCallbackArray() {}

    inline IlInt count() const
	{ return _array.count(); }
    inline IliCallback* at(IlInt idx) const
	{ return (IliCallback*)_array.at(idx); }

    IlBoolean hasCallback(IliCallback*) const;

    void addCallback(IliCallback*);
    void removeCallback(IliCallback*);
    void empty();

    void call(IlAny caller);

private:
    IliRefCountedArray _array;
};

// --------------------------------------------------------------------------
// Static symbol
// --------------------------------------------------------------------------
#define IliDeclareStaticLocalSymbol(cl, name, val)			\
    static IlvSymbol* cl##name##LocalSymbol()				\
    {									\
	static IlvSymbol* cl##name = 0;					\
	if (cl##name == 0) { cl##name = IlvGetSymbol(ILVSTRING(val)); }	\
	return cl##name;						\
    }

#define IliDeclareStaticClassSymbol(cl, fct, val)			\
    IlvSymbol* cl::fct()						\
    {									\
	static IlvSymbol* sym##fct = 0;					\
	if (sym##fct == 0) { sym##fct = IlvGetSymbol(ILVSTRING(val)); }	\
	return sym##fct;						\
    }

// --------------------------------------------------------------------------
// Test
// --------------------------------------------------------------------------
#define IliBetweenInc(v, a, b) ((v >= a) && (v <= b))
#define IliBetweenExc(v, a, b) ((v > a) && (v < b))

// --------------------------------------------------------------------------
// Errors
ILV_INF_EXPORTEDFN(void)
IliOnError();

// IO
ILV_INF_EXPORTEDFN(void)
IliReadIdentifier(IL_STDPREF istream&, char*, IlUInt);

// Rects
ILV_INF_EXPORTEDFN(void)
IliShrinkRect(IlvRect&, IlvDim);
ILV_INF_EXPORTEDFN(void)
IliShrinkRect(IlvRect&, IlvDim, IlvDim);
ILV_INF_EXPORTEDFN(void)
IliSetRectRight(IlvRect&, IlvPos);
ILV_INF_EXPORTEDFN(void)
IliSetRectLeft(IlvRect&, IlvPos);
ILV_INF_EXPORTEDFN(void)
IliSetRectBottom(IlvRect&, IlvPos);
ILV_INF_EXPORTEDFN(void)
IliSetRectTop(IlvRect&, IlvPos);

// 2.1 attachments
ILV_INF_EXPORTEDFN(void)
IliCopyAttachments(IlvGraphic*, IlvGraphic*);

// Others
ILV_INF_EXPORTEDFN(void)
IliCenterInView(IlvAbstractView*, IlvAbstractView*);
ILV_INF_EXPORTEDFN(void)
IliForceButtonUp(IlvDisplay*);
ILV_INF_EXPORTEDFN(void)
IliErrorBox(IlvGadgetHolder*, const char*);
ILV_INF_EXPORTEDFN(void)
IliErrorBox(IlvDisplay*, IlvAbstractView*, const char*);
ILV_INF_EXPORTEDFN(void)
IliMessageBox(IlvGadgetHolder*, const char*);
ILV_INF_EXPORTEDFN(void)
IliMessageBox(IlvDisplay*, IlvAbstractView*, const char*);
ILV_INF_EXPORTEDFN(IlBoolean)
IliAskYesNo(IlvGadgetHolder*, const char*);
ILV_INF_EXPORTEDFN(IlBoolean)
IliAskYesNo(IlvDisplay*, IlvAbstractView*, const char*);
ILV_INF_EXPORTEDFN(IlBoolean)
IliAskYesNoCancel(IlvGadgetHolder*, const char*, IlBoolean&);
ILV_INF_EXPORTEDFN(IlBoolean)
IliAskYesNoCancel(IlvDisplay*, IlvAbstractView*, const char*,
		  IlBoolean&);
ILV_INF_EXPORTEDFN(void)
IliFillDialog(IlvDialog*, const char*);
ILV_INF_EXPORTEDFN(void)
IliSortArray(IlvArray&, int (*)(IlAny, IlAny, IlAny), IlAny = 0);

#endif /* !__Ili_Util_H */
