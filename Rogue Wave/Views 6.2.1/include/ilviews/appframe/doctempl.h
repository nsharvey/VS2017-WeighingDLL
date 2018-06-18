// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/doctempl.h
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
// Declaration of the IlvDvDocTemplate class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Doctempl_H)
#define __Ilv_Appframe_Doctempl_H

#if !defined(__Ilv_Appframe_Serializ_H)
#  include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#  include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#  include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#  include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#  include <ilviews/appframe/utils.h>
#endif
#if !defined(__Ilv_Gadgets_Macros_H)
#  include <ilviews/gadgets/macros.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#  include <ilviews/util/proplist.h>
#endif

class IlvDvDocTemplate;
class IlvDvStream;
class IlvDvDocument;
class IlvDvDocViewInterface;
class IlvDvMainContainer;
class IlvDvDynClassInfo;
class IlvDvContainerHandler;
class IlvDvDocManager;
class IlvDvViewContainerInterface;
class IlvDvDynClassInfo;
class IlvDvGadgetViewClassInfo;
class IlvDvApplication;
class IlvDvOptions;
class IlvDvNodeValue;
class IlvToolBar;
class IlvAbstractMenu;
class IlvDvRecentFileList;
class IlvDvModule;
class IlvDvDocViewBuilder;
class IlvGadgetContainer;
class IlvDvMainWindowInterface;
class IlvDvBarSet;
class IlvPane;

// --------------------------------------------------------------------------
// IlvDvDocViewFactory class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocumentViewFactory
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDocumentViewFactory(IlvDvDocTemplate* tpl,
			     IlUInt viewTemplateIndex = 0);
    virtual ~IlvDvDocumentViewFactory();

    // ----------------------------------------------------------------------
    virtual IlvDvDocViewInterface*
		create(IlvDvViewContainerInterface* parent,
		       IlUInt tplIndex) const;

    // -----------------------------------------------------------------------
    // Properties
    IlUInt	getCardinalOfDocumentViewInfo() const;
    void	setDocViewBuilder(IlvDvDocViewBuilder* builder,
				  IlUInt nBuilder = 0);
    void	setDocViewClassInfo(const IlvDvDynClassInfo*,
				    IlUInt nBuilder = 0);
    void	setDocGadgetViewClassInfo(const IlvDvGadgetViewClassInfo* blds,
					  IlUInt nBlds = 0);

protected:
    IlvDvDocTemplate*	_docTemplate;
    IlvArray		_viewBuilders;

    virtual IlvDvDocViewBuilder*
		createViewBuilder(const char*,
				  IlvDvDocTemplate* tpl,
				  IlUInt nBuilder) const;
};

// --------------------------------------------------------------------------
// IlvDvDocViewBuilder class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocViewBuilder
{
public:
    virtual ~IlvDvDocViewBuilder() {}

    virtual IlvDvDocViewInterface*
		create(IlvDvViewContainerInterface* parent) = 0;
};

// --------------------------------------------------------------------------
// IlvDvDocViewClassInfoBuilder class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocViewClassInfoBuilder : public IlvDvDocViewBuilder
{
public:
    IlvDvDocViewClassInfoBuilder(const IlvDvDynClassInfo* classInfo);
    virtual IlvDvDocViewInterface*
		create(IlvDvViewContainerInterface* parent);

protected:
    const IlvDvDynClassInfo*	_classInfo;
};

// --------------------------------------------------------------------------
// IlvDvDocGadgetViewBuilder class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocGadgetViewBuilder : public IlvDvDocViewBuilder
{
public:
    IlvDvDocGadgetViewBuilder(const IlvDvGadgetViewClassInfo*,
			      const IlvDvDocTemplate*);
    virtual IlvDvDocViewInterface*
				create(IlvDvViewContainerInterface* parent);

protected:
    const IlvDvGadgetViewClassInfo*	_classInfo;
    const IlvDvDocTemplate*		_template;
};

// --------------------------------------------------------------------------
// IlvDvViewBuilder class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvViewClassInfo;

class ILVDVCLASS IlvDvViewBuilder : public IlvDvDocViewBuilder
{
public:
    IlvDvViewBuilder(const IlvDvViewClassInfo*, const IlvDvDocTemplate*);
    virtual IlvDvDocViewInterface*
		create(IlvDvViewContainerInterface* parent);

protected:
    const IlvDvViewClassInfo*	_classInfo;
    const IlvDvDocTemplate*	_template;
};

// --------------------------------------------------------------------------
// IlvDvDocTemplate class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocTemplate
    : public IlvDvSerializable, public IlvDvInterface
{
    IlvDvDeclareClassInfo();
public:
    IlvDvDocTemplate(const char* name = 0);
    virtual ~IlvDvDocTemplate();

    virtual
    IlvDvDocument*	openDocument(const IlvPathName& pathname,
				     IlBoolean createWindow = IlTrue,
				     IlBoolean addToMRU = IlTrue,
				     IlAny data = 0);
    virtual
    IlvDvDocument*	newDocument(IlBoolean createWindow = IlTrue,
				    IlAny data = 0);
    void		promptAndOpenDocument(const char* msg = 0);
    virtual IlBoolean	matchPathName(const IlvPathName& pathName);
    IlUInt		getOpenedDocumentCount() const;
    IlvDvDocument*	getOpenedDocument(IlUInt) const;
    IlvDvDocument*	getOpenedDocumentFromPath(const IlvPathName&) const;
    IlUInt		addOpenedDocument(IlvDvDocument*);
    IlBoolean		removeOpenedDocument(IlvDvDocument*,
					     IlBoolean del = IlFalse);
    virtual void	addToRecentFileList(const IlvPathName&);
    virtual IlBoolean	saveAllModifiedDocs();
    virtual IlBoolean	saveDocument(IlvDvDocument*);
    virtual IlBoolean	saveAsDocument(IlvDvDocument*);
    virtual IlBoolean	closeAllDocuments(IlBoolean endSession);
    virtual IlBoolean	saveModifications();
    virtual IlvDvViewContainerInterface* 
			newWindow(IlvDvDocument* document,
				  IlBoolean createViews = IlTrue,
				  IlBoolean initializeViews = IlTrue,
				  IlBoolean canDeleteDoc = IlFalse,
				  IlUInt viewTemplateIndex = (IlUInt)-1);
    virtual IlBoolean	attachContainer(IlvDvViewContainerInterface* container,
					IlvDvDocument* document,
					IlBoolean createViews = IlTrue,
					IlBoolean initializeViews = IlTrue,
					IlBoolean canDeleteDoc = IlFalse,
					IlUInt viewTemplateIndex = 0);

    virtual void	setDefaultTitle(IlvDvDocument*,
					IlBoolean update = IlTrue);
    virtual void	activateDocumentView(IlvDvDocument*, IlUInt iView = 0);
    // ----------------------------------------------------------------------
    // Main overridables
    virtual
    IlvDvDocument*	createDocument();

    // ----------------------------------------------------------------------
    // Menu operations
    IlBoolean		alwaysShowMenu() const;
    virtual IlBoolean	completeMenu(IlvDvMainWindowInterface*,
				     IlvAbstractMenu*);
    virtual IlBoolean	cleanBars(IlvDvMainWindowInterface*);
    virtual void	updateRecentFileListMenu(IlvAbstractMenu*) const;
    virtual void	insertBars(IlvDvMainWindowInterface*);
    virtual void	removeBars(IlvDvMainWindowInterface*);
    void		addBar(const char* name, IlvToolBar* bar);
    void		addPane(const char* name, IlvPane* pane);
    void		removePaneByName(const char* name);
    void		removePane(IlvPane* pane);

    // Only call by the customization dialog
    void		removeBar(IlvToolBar* bar);
    IlvToolBar*		getToolBar(const char* name) const;

    // ----------------------------------------------------------------------
    // Basic properties
    inline
    const IlSymbol*	getNameSymbol() const { return _name; }
    void		setNameSymbol(const IlSymbol* name);
    inline
    const char*		getName() const
			{
			    return _name? _name->name() : 0;
			}
    void		setName(const char* name);
    inline
    IlvDvDynClassInfo*	getDocumentClassInfo() const
			{
			    return _docClassInfo;
			}
    void		setDocumentClassInfo(IlvDvDynClassInfo*);

    void		set(const char* shortName,
			    const char* filter,
			    const char* filterMsg,
			    const char* description);
    const char*		getShortName() const;
    void		setShortName(const char* name);

    // Filters
    IlUInt		getFiltersCount() const;
    const char*		getFilter(IlUInt nFilter = 0) const;
    void		setFilter(const char* filter,
				  IlUInt nFilter = 0); // As "txt"
    IlvString&		getFilterExt(IlvString&, IlUInt nFilter = 0) const;
    const char*		getFilterMessage(IlUInt nFilter = 0) const;
    void		setFilterMessage(const char*, IlUInt nFilter = 0);
    void		fillFilterArrays(const char** filters,
					 const char** messages,
					 IlUInt& index) const;
    inline IlBoolean	appearsInLoadFileFilters() const
			{
			    return _appearsInLoadFileFilters;
			}
    inline void		setAppearsInLoadFileFilters(IlBoolean appears)
			{
			    _appearsInLoadFileFilters = appears;
			}

    const char*		getDescription() const;
    void		setDescription(const char*);
    const char*		getDefaultName() const;
    void		setDefaultName(const char*);
    inline
    IlvDvDocManager*	getDocManager() const { return _docManager; }
    inline void		setDocManager(IlvDvDocManager* docManager)
			{
			    _docManager = docManager;
			}
    IlBoolean		isMDI() const;
    void		setMDI(IlBoolean mdi = IlTrue);
    IlBoolean		isManagingRecentOpenedFileList() const;

    virtual void	initializeMainWindow(IlvDvMainWindowInterface*);
    IlUInt		getContainerFactoriesCount() const;
    IlvDvContainerHandler*	getContainerHandler(IlUInt index = 0) const;
    IlUInt		getContainerHandlerIndex(IlvDvContainerHandler*) const;
    void		setContainerHandler(IlvDvContainerHandler* handler,
					    IlUInt viewTemplateIndex = 0);

    IlvDvContainerHandler*    getActiveViewHandler(const IlvDvDocument*) const;

    IlvDvApplication*	getDvApplication() const;
    IlvDisplay*		getDisplay() const;
    inline IlvDvModule*	getModule() const { return _module; }
    void		setModule(IlvDvModule*);

    typedef IlvDvDocument* (*CreateDocCallback)(IlvDvDocTemplate*, IlAny);
    void		setCreateDocCallback(CreateDocCallback, IlAny = 0);

    // ----------------------------------------------------------------------
    // Action processing
    virtual IlBoolean	processAction(const IlSymbol* actionName);
    virtual IlBoolean	isProcessingAction(const IlSymbol* methodName) const;

    IlvDvDeclareInterface();

    // ----------------------------------------------------------------------
    virtual void	readRegistries();
    virtual void	writeRegistries();
    void		readFileListOptions(IlvDvOptions*);
    void		updateFileListOptions(IlvDvOptions*);
    virtual void	serialize(IlvDvStream&);
    IlBoolean		readOptions(IlvDvOptions* options,
				    const char* docTemplateName);
    IlBoolean		readDynMenuOptions(const IlvDvOptions* options,
					   IlvDvNodeValue* templateVar);
    inline
    IlvDvNodeValue*	getTemplateNode() const
			{
			    return _templateVar;
			}
    inline
    IlvDvOptions*	getOptions() const { return _options; }
    static IlSymbol*	_OptionDocTemplateClassSymbol;
    static IlSymbol*	_OptionDocTemplateBarsClassSymbol;
    static IlSymbol*	_RemovedItemIndexSymbol;
    static IlSymbol*	_RemovedItemPathSymbol;

    // ----------------------------------------------------------------------
    IlvDeclareBasePropertyListOwner();

protected:
    IlBoolean		_isMDI; // or is SDI
    IlUInt		_untitledCount;
    IlvDvDynClassInfo*	_docClassInfo;
    IlvString		_shortName;
    IlvArray		_filters;
    IlvString		_description;
    IlvString		_defaultName;
    IlvArray		_openedDocuments;
    IlvDvDocManager*	_docManager;
    IlvDvBarSet*	_barSet;
    IlBoolean		_appearsInLoadFileFilters;
    IlvDvRecentFileList* _recentFileList;
    const IlSymbol*	_recentFileListCommand;
    const IlSymbol*	_name;
    IlvDvModule*	_module;
    CreateDocCallback	_createDocCallback;
    IlAny		_createDocParam;
    IlvPathName		_lastOpenedFile;

    // Option data
    IlvDvOptions*	_options;
    IlvDvNodeValue*	_templateVar;

    const char*		getFieldValue(const char* fieldName,
				      const IlvString* defaultS= 0) const;
    IlBoolean		setFieldValue(const char* fieldName,
				      const char* value, 
				      IlvString* defaultS= 0);
    IlvString**		ensureFilter(IlUInt);
    void		cleanFilters();

    // ----------------------------------------------------------------------
    // Holding views
    IlvArray _containerFactories;
    virtual IlvDvViewContainerInterface*
			createContainer(IlUInt viewTemplateIndex = 0);
    void		cleanContainerFactories();
    // ----------------------------------------------------------------------
    // Toolbars
    void		emptyBars();
    IlvToolBar*		getToolBar(IlUInt) const;

public:
    static IlBoolean	OpenCallback(IlAny itemData, IlAny param);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(doctempl);

#endif /* !__Ilv_Appframe_Doctempl_H */
