// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/gadgets/gadgets.h
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
// Declaration of redefined gadgets classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Gadgets_Gadgets_H)
#define __Ilv_Appframe_Gadgets_Gadgets_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif

// --------------------------------------------------------------------------
// IlvDvInsDelProcessor class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvInsDelProcessor
{
public:
    IlBoolean handleInsDelEvent(IlvEvent& event);

    // AddItem callbacks
    inline IlSymbol* getAddItemCallbackName() const
	{ return _getGraphic()->getCallbackName(AddItemSymbol());}
    inline IlvGraphicCallback getAddItemCallback() const
	{ return _getGraphic()->getCallback(AddItemSymbol());}
    inline void setAddItemCallback(IlvGraphicCallback callback)
	{ _getGraphic()->setCallback(AddItemSymbol(), callback); }
    inline void setAddItemCallback(IlSymbol* callbackName)
	{ _getGraphic()->setCallback(AddItemSymbol(), callbackName); }
    inline void addAddItemCallback(IlvGraphicCallback callback)
	{ _getGraphic()->addCallback(AddItemSymbol(), callback); }
    inline void setAddItemCallback(IlvGraphicCallback callback, IlAny arg)
	{ _getGraphic()->setCallback(AddItemSymbol(), callback, arg); }
    inline void addAddItemCallback(IlvGraphicCallback callback, IlAny arg)
	{ _getGraphic()->addCallback(AddItemSymbol(), callback, arg); }
    inline void addAddItemCallback(IlSymbol* callbackName)
	{ _getGraphic()->addCallback(AddItemSymbol(), callbackName); }
    inline void setAddItemCallback(IlSymbol* callbackName, IlAny arg)
	{ _getGraphic()->setCallback(AddItemSymbol(), callbackName, arg); }
    inline void addAddItemCallback(IlSymbol* callbackName, IlAny arg)
	{ _getGraphic()->addCallback(AddItemSymbol(), callbackName, arg); }

    // DelItem callbacks
    inline IlSymbol* getDelItemCallbackName() const
	{ return _getGraphic()->getCallbackName(DelItemSymbol());}
    inline IlvGraphicCallback getDelItemCallback() const
	{ return _getGraphic()->getCallback(DelItemSymbol());}
    inline void setDelItemCallback(IlvGraphicCallback callback)
	{ _getGraphic()->setCallback(DelItemSymbol(), callback); }
    inline void setDelItemCallback(IlSymbol* callbackName)
	{ _getGraphic()->setCallback(DelItemSymbol(), callbackName); }
    inline void addDelItemCallback(IlvGraphicCallback callback)
	{ _getGraphic()->addCallback(DelItemSymbol(), callback); }
    inline void setDelItemCallback(IlvGraphicCallback callback, IlAny arg)
	{ _getGraphic()->setCallback(DelItemSymbol(), callback, arg); }
    inline void addDelItemCallback(IlvGraphicCallback callback, IlAny arg)
	{ _getGraphic()->addCallback(DelItemSymbol(), callback, arg); }
    inline void addDelItemCallback(IlSymbol* callbackName)
	{ _getGraphic()->addCallback(DelItemSymbol(), callbackName); }
    inline void setDelItemCallback(IlSymbol* callbackName, IlAny arg)
	{ _getGraphic()->setCallback(DelItemSymbol(), callbackName, arg); }
    inline void addDelItemCallback(IlSymbol* callbackName, IlAny arg)
	{ _getGraphic()->addCallback(DelItemSymbol(), callbackName, arg); }

   static IlSymbol*		_AddItemSymbol;
   static IlSymbol*		_DelItemSymbol;

   static IlSymbol*		AddItemSymbol();
   static IlSymbol*		DelItemSymbol();

protected:
    virtual IlvGraphic*		_getGraphic() = 0;
    virtual const IlvGraphic*	_getGraphic() const = 0;
};

// --------------------------------------------------------------------------
// IlvDvStringList class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvStringList
: public IlvStringList, public IlvDvInsDelProcessor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvStringList(IlvDisplay*        display,
		    const IlvRect&     rect,
		    const char* const* labels    = 0,
		    IlUShort           count     = 0,
		    IlUShort           thickness = IlvDefaultGadgetThickness,
		    IlvPalette*        palette   = 0);
    IlvDvStringList(const IlvStringList* = 0);
    ~IlvDvStringList();

    // ----------------------------------------------------------------------
    virtual IlBoolean		handleGadgetEvent(IlvEvent& event);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvDvStringList);

protected:
    virtual IlvGraphic*		_getGraphic();
    virtual const IlvGraphic*	_getGraphic() const;
};

// --------------------------------------------------------------------------
// IlvDvTreeGadget class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTreeGadget
: public IlvTreeGadget, public IlvDvInsDelProcessor
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTreeGadget(IlvDisplay*    display,
		    const IlvRect& rect,
		    IlUShort       thickness = IlvDefaultGadgetThickness,
		    IlvPalette*    palette   =0);
    IlvDvTreeGadget(const IlvTreeGadget* = 0);
    ~IlvDvTreeGadget();

    // ----------------------------------------------------------------------
    virtual IlBoolean		handleTreeEvent(IlvEvent& event);

    DeclareTypeInfo();
    DeclareIOConstructors(IlvDvTreeGadget);

protected:
    virtual IlvGraphic*		_getGraphic();
    virtual const IlvGraphic*	_getGraphic() const;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(gadgets);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Gadgets_Gadgets_H */
