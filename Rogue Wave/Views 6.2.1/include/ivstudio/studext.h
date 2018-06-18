// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/studext.h
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
// Declaration of Studio extension classes 
// --------------------------------------------------------------------------
#ifndef __IlvSt_Studext_H
#define __IlvSt_Studext_H

#ifndef __IlvSt_Object_H
#include <ivstudio/object.h>
#endif

#include <ilviews/base/modules.h>

// --------------------------------------------------------------------------
class IlvStPropertySet;

class ILVSTUDIOCLASS IlvStExtension : public IlvStNamedObject 
{
public:
  IlvStExtension(const char* name, IlvStudio* editor);

  IlvStudio* getEditor() const;

  virtual IlBoolean	preInitialize();

  virtual IlBoolean	afterReadingPropertyFiles();

  virtual IlBoolean	initializeBuffers();

  virtual IlBoolean	initializeCommandDescriptors();

  virtual IlBoolean	initializePanels();

  virtual IlBoolean	initializeInspectors();

  virtual IlBoolean	initializeModes();

  virtual IlBoolean	postInitialize();

protected:
  IlvStudio*		_editor;
}; // class IlvStExtension

// --------------------------------------------------------------------------
typedef IlBoolean (IlvStExtension::*IlvStExtensionFunction)();

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStExtensions
: public IlvStObject {
public:
    IlvStExtensions(IlvStudio*);
    ~IlvStExtensions();
    IlvStudio*		getEditor() const { return _editor; }
    void		addExtension(IlvStExtension*,
				     IlUInt rank = (IlUInt)-1);
    IlvStExtension*	getExtension(const char* name) const;
    IlvStExtension*	getExtension(IlUInt ndx) const
	{ return (IlvStExtension*)_extensions[ndx]; }
    IlUInt		getIndex(const char* name) const;
    IlUInt		getCardinal() const { return _extensions.getLength(); }
    void		removeExtension(IlvStExtension*);

    IlBoolean	preInitialize();
    IlBoolean	afterReadingPropertyFiles();
    IlBoolean	initializeBuffers();
    IlBoolean	initializeCommandDescriptors();
    IlBoolean	initializePanels();
    IlBoolean	initializeInspectors();
    IlBoolean	initializeModes();
    IlBoolean	postInitialize();

    IlBoolean	callExtensionFunction(IlvStExtensionFunction);

    static IlvStExtensions* Get(IlvStudio* editor);
protected:
    IlvStudio*		_editor;
    IlvArray		_extensions;
    IlvStStringArray	_loadedPlugIns;
    IlvStStringArray*	_selectedPlugIns;
    IlvStPropertySet*	_predPI;

public:
    IlvModule*		loadModule(const char* modspec);
    void		loadAllExtensions();
    void		getExtensionsDirectory(IlvPathName&) const;
    IlvStStringArray&	loadedPlugIns() { return _loadedPlugIns; }
    IlvStStringArray*	getSelectedPlugIns() { return _selectedPlugIns; }
    void		setSelectedPlugIns(IlvStStringArray*);
    IlvModule*		callModuleLoad(const char* path);
    IlBoolean		selectPlugIns(IlvArray& result,
				      const IlvStStringArray* presel = 0);
    IlvStPropertySet*	getPredefinedPlugIns() const { return _predPI; }
    IlvStPropertySet*	makePredefinedPlugInList();
}; // class IlvStExtensions

// --------------------------------------------------------------------------
#endif /* __IlvSt_Studext_H */
