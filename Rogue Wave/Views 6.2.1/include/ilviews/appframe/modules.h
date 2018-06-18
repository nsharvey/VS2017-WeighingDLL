// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/modules.h
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
// Declaration of Document / view macros
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Modules_H)
#define __Ilv_Appframe_Modules_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Appframe_Module_H)
#include <ilviews/appframe/module.h>
#endif

class IlvDvNodeValue;
class IlvDvOptions;
class IlvDvApplication;

// --------------------------------------------------------------------------
// IlvDvModuleInfos class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvModuleInfos
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvModuleInfos(const char* path = 0, const char* name = 0);
    IlvDvModuleInfos(const IlvDvModuleInfos&);
    virtual ~IlvDvModuleInfos();
    virtual IlvDvModuleInfos* copy() const;

    // ----------------------------------------------------------------------
    inline
    const char*		getPathName() const { return _path; }
    void		setPathName(const char*);
    inline
    const IlvString&	getName() const { return _name; }
    inline void		setName(const char* name) { _name = name; }
    inline void		setToBeLoaded(IlBoolean bLoad)
			{
			    _toBeLoaded = bLoad;
			}
    inline IlBoolean	isToBeLoaded() const { return _toBeLoaded; }
    void		copyData(const IlvDvModuleInfos&);

    inline IlvDvModule*	getModule() const { return _module; }
    void		setModule(IlvDvModule*);

    inline const char*	getOptionFilename() const
			{
			    return _optionFilename;
			}
    void		setOptionFilename(const char* filename);
    void		setDataBaseFilename(const char* filename);
    inline const char*	getDataBaseFilename() const
			{
			    return _dataBaseFilename;
			}
    inline
    IlvDvOptions*	getOptions() const { return _options; }
    inline void		setOptions(IlvDvOptions* options)
			{
			    _options = options;
			}

    // ----------------------------------------------------------------------
    virtual void	read(IlvDvNodeValue*);
    virtual void	updateOptions(IlvDvNodeValue* var);

    static IlSymbol*	_ModuleInfosClassSymbol;

protected:
    IlvString		_path;
    IlBoolean		_toBeLoaded;
    IlvDvOptions*	_options;
    IlvString		_name;
    IlvString		_optionFilename;
    IlvString		_dataBaseFilename;
    IlvDvModule*	_module;

    IlBoolean		isNameBasedOnPathName() const;
};

// --------------------------------------------------------------------------
// IlvDvModuleInfosArray class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvModuleInfosArray : public IlvArray
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvModuleInfosArray(IlvDvApplication*);
    virtual ~IlvDvModuleInfosArray();

    // ----------------------------------------------------------------------
    // Modules management
    void		loadModules();
    void		completeAppOptions();
    virtual void	completeAppOptions(IlvDvModuleInfos*);
    void		createDocTemplates(IlBoolean bUpdate);
    virtual void	createDocTemplates(IlvDvModuleInfos*,
					   IlBoolean bUpdate = IlTrue);
    IlvDvModuleInfos*	getModuleInfos(IlUInt) const;
    IlvDvModuleInfos*	getModuleInfos(const char*) const;
    IlUInt		getModuleInfosCount() const;
    void		addModuleInfos(IlvDvModuleInfos*,
				       IlUInt = (IlUInt)-1);
    virtual IlBoolean	load(IlvDvModuleInfos*);
    virtual IlBoolean	unload(IlvDvModuleInfos*);
    void		removeModuleInfos(IlvDvModuleInfos*);
    IlBoolean		editModules(IlvSystemView = 0);
    IlvDisplay*		getDisplay() const;
    IlvDvModule*	findOptionsModule(IlvDvOptions* options) const;

    // ----------------------------------------------------------------------
    // options
    virtual void	readOptions(IlvDvOptions*, const IlSymbol*);
    virtual void	updateOptions(IlvDvOptions*, const IlSymbol*);

    static IlSymbol*	_ModulesClassSymbol;

protected:
    IlvDvApplication*	_app;
    IlvRect		_dlgRect;

    void		cleanModules();
    virtual
    IlvDvModuleInfos*	createDefaultModuleInfos() const;
};

// --------------------------------------------------------------------------
// class IlvDvAppModulesDialog
// --------------------------------------------------------------------------
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif

class IlvCheckedStringList;
class IlvGadgetItem;
class IlvGraphic;
class IlvGadgetItemHolder;

class IlvDvAppModulesDialog : public IlvDialog
{
public:
    IlvDvAppModulesDialog(IlvDvModuleInfosArray* modules,
			  IlvSystemView transientFor = 0);
    ~IlvDvAppModulesDialog();
    // ____________________________________________________________
    virtual void		apply();
    virtual void		cancel();

protected:
    IlvCheckedStringList*	_checkList;
    IlvDvModuleInfosArray*	_modulesArray;

public:
    class ModuleNode
    {
    public:
	IlvDvModuleInfos*	_orig;
	IlvDvModuleInfos*	_modif;
	ModuleNode(IlvDvModuleInfos* moduleInfo)
	    : _orig(moduleInfo), _modif(0) {}
	ModuleNode(const char* path)
	    : _orig(0), _modif(new IlvDvModuleInfos(path)) {}
	~ModuleNode() { if (_modif) delete _modif; }

	inline
	IlvDvModuleInfos*	getModuleInfos()
				{
				    return _modif ? _modif : _orig;
				}
    };

protected:
    IlvArray		_moduleNodes;
    IlvArray		_removed;

    ModuleNode*		getModuleNode(IlUInt) const;
    IlUInt		findModule(const char*) const;
    void		selectionChanged();
    void		insertModule();
    void		removeModule();
    IlUShort		getSelectedModuleIndex() const;
    void		insertModuleItem(IlvDvModuleInfos* moduleInfos,
					 IlShort pos,
					 IlBoolean newCreated = IlFalse);
    void		loadUnload(ModuleNode*, IlBoolean bLoad);
    void		modified(IlBoolean = IlTrue);
    void		moduleNameChanged();
    static
    IlvDvAppModulesDialog* GetDlg(IlvGraphic*);
    static void		SetDlg(IlvGraphic*, IlvDvAppModulesDialog*);

public:
    static void		SelectionChanged(IlvGraphic* g, IlAny);
    static void		InsertModule(IlvGraphic* g, IlAny);
    static void		RemoveModule(IlvGraphic* g, IlAny);
    static void		Apply(IlvGraphic*, IlAny);
    static void		Cancel(IlvGraphic*, IlAny);
    static void		LoadUnloadCallback(IlvGadgetItemHolder*,
					   IlvGadgetItem*,
					   IlBoolean,
					   IlBoolean,
					   IlAny);
    static void		ModuleNameChanged(IlvGraphic*, IlAny);
    static IlSymbol*	_PropertyDlgSymbol;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(modules);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Modules_H */
