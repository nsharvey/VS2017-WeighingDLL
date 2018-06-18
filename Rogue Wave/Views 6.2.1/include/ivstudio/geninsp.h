// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/geninsp.h
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
// Declaration of the IlvStGenericInspector class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Geninsp_H
#define __IlvSt_Geninsp_H

#if !defined(__Ilv_Macros_H)
#include <ilviews/macros.h>
#endif

#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

#ifndef __IlvSt_Object_H
#include <ivstudio/object.h>
#endif

#ifndef __IlvSt_Stprop_H
#include <ivstudio/stprop.h>
#endif

#ifndef __Ilv_Base_Gadget_H
#include <ilviews/base/gadget.h>
#endif

#ifndef __IlvSt_Command_H
#include <ivstudio/command.h>
#endif

class IlvStudio;
class IlvGadgetContainer;
class IlvGraphic;
class IlvManager;
class IlvSmartSet;

// --------------------------------------------------------------------------
// IlvStMoveObject class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStMoveObject: public IlvStCommand
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStMoveObject(IlvGraphic*, IlvPos newx, IlvPos newy);

    // ----------------------------------------------------------------------
    virtual IlvStError* doIt(IlvStudio*, IlAny);
protected:
    IlvGraphic* _object;
    IlvPos _dx;
    IlvPos _dy;
};


// --------------------------------------------------------------------------
// IlvStResizeObject class
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStResizeObject:
public IlvStCommand
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStResizeObject(IlvGraphic*, IlvDim neww, IlvDim newh);

    // ----------------------------------------------------------------------
    virtual IlvStError* doIt(IlvStudio*, IlAny);
private:
    IlvGraphic* _object;
    IlvPos      _dw;
    IlvPos      _dh;
};

// --------------------------------------------------------------------------
// IlvStSetObjectName class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStSetObjectName:
public IlvStCommand {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStSetObjectName(IlvGraphic* obj, const char* name);
    ~IlvStSetObjectName();

    // ----------------------------------------------------------------------
    virtual IlvStError* doIt(IlvStudio*, IlAny);
protected:
    IlvGraphic* _object;
    char* _name;
};

// --------------------------------------------------------------------------
// IlvStSetObjectCallback class
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStSetObjectCallback:
public IlvStCommand {
public:
    // ----------------------------------------------------------------------
    // Constructor
    IlvStSetObjectCallback(IlvGraphic*, const char*, const IlSymbol*);

    // ----------------------------------------------------------------------
    virtual IlvStError* doIt(IlvStudio*, IlAny);
private:
    IlvGraphic* _object;
    IlSymbol*  _callback;
    const IlSymbol*  _language;
};

/*
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPropertyInspector
: public IlvStNamedObject {
public:
    IlvStPropertyInspector(const char* name);
    ~IlvStPropertyInspector();

    void setObject(IlAny obj,
		   const char* type = 0,
		   IlBoolean refresh = IlFalse);
    IlAny getObject() const { return _object; }
    const char* getType() const { return _type; }
    void refresh();
    void apply();

    void addAccessor(IlvStPropertyAccessor* acc);
    void removeAccessor(IlvStPropertyAccessor* acc);
    IlvStPropertyAccessor* getAccessor(const char* name) const;
    IlvStPropertyAccessor* const* getAccessors(IlUInt& count) const;

    // labels and editors
    virtual IlBoolean	    connectContainer(IlvGadgetContainer* cont);
    void		    makeVerticalPanel(IlvGadgetContainer* cont,
					      IlvPos dx = 0,
					      IlvPos dy = 0);
    virtual void	    createGraphicObjects(IlvDisplay*,
						 IlvArray& labels,
						 IlvArray& editors);
    virtual void	    verticalLayout(const IlvArray& labels,
					   const IlvArray& editors,
					   IlvPos dx,
					   IlvPos dy);
    virtual void	    horizontalLayout(const IlvArray& labels,
					     const IlvArray& editors,
					     IlvPos dx,
					     IlvPos dy);
    virtual void	    getPanelSize(const IlvArray& labels,
					 const IlvArray& editors,
					 IlvDim& width,
					 IlvDim& height);
    virtual void	    addObjects(IlvGadgetContainer* cont,
				       const IlvArray& labels,
				       const IlvArray& editors);
    virtual void	    attachObjects(IlvGadgetContainer* cont,
				          const IlvArray& labels,
				          const IlvArray& editors);

    static IlvStPropertyInspector* Make(IlvValueInterface*);

    // internal functions
    IlvArray& accessors() { return _accessors; }


protected:
    IlvArray	    _accessors;
    IlAny	    _object;
    IlvStString	    _type;
    static int	    _vSpacing;
    static int	    _hSpacing;
}; // IlvStPropertyInspector class
*/

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStGenericInspector {
public:
    IlvStGenericInspector(IlvStudio*, IlvGadgetContainer*);
    // ____________________________________________________________
    IlvStudio* 	getEditor() const        { return _editor; }
    void   	setEditor(IlvStudio* editor) { _editor = editor; }
    IlvGadgetContainer* getContainer() const { return _container; }
    void 	setContainer(IlvGadgetContainer* cont) { _container = cont; }
    void 	clear();
    void 	refresh();
    void 	setObject(IlvGraphic*);
    void	setRectangle(const IlvRect&);
    IlvGraphic* getObject() const { return _object; }
    IlBoolean 	noSelection() const;
    IlvManager* getManager() const;
    void 	connect();
    const char* getLabelValue(const char* name) const;
    void 	setLabelValue(const char* name, const char* label);
    IlInt 	getIntValue(const char* name) const;
    void 	setIntValue(const char* name, IlInt);
    IlvSmartSet* getSmartSet() const { return _smartset; }

private:
    IlvStudio* 		_editor;
    IlvGadgetContainer* _container;
    IlvGraphic*         _object;
    IlvSmartSet*	_smartset;
};

// --------------------------------------------------------------------------
// Some uselfull functions

extern ILVSTEXPORTEDFUNC(void) IlvStEnsureTextVisible(IlvGadget*);

// --------------------------------------------------------------------------
#endif /* __IlvSt_Geninsp_H */

