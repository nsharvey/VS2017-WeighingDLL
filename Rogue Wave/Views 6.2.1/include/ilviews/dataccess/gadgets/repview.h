// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/repview.h
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
// Declaration of the IliRepositoryView class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Repview_H
#define __Ili_Repview_H

#ifndef __Ilv_Gadgets_Tree_H
#  include <ilviews/gadgets/tree.h>
#endif

#ifndef __Ili_Reposit_H
#  include <ilviews/dataccess/reposit.h>
#endif

#ifndef __Ili_Mdatasrc_H
#  include <ilviews/dataccess/gadgets/mdatasrc.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

typedef char** (*IliGetClassesListCallback)(IlInt& count, IlAny arg);

typedef char** (*IliGetDataListCallback)(const char* cl,
					 IlInt& count,
					 IlAny arg);

typedef const char* (*IliHolderToNameCallback)(IlvGraphicHolder* hoder);
typedef void (*IliTreeEventCallback)(IlvGraphic*, IlvEvent&, IlAny);

enum IliRepositFilterOn {
    IliFilterOnContainer = 0,
    IliFilterOnComposite,
    IliFilterOnManager,
    IliFiltersCount
};

// --------------------------------------------------------------------------
// IliRepositoryService
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliRepositoryService
{
public:
    IliRepositoryService();
    IliRepositoryService(IlBoolean autoBuild);
    IliRepositoryService(const IliRepositoryService&);
    virtual ~IliRepositoryService();

    //---- Holder name ----
    static IliHolderToNameCallback GetHolderToNameCallback();
    static void		SetHolderToNameCallback(IliHolderToNameCallback cb);
    const char*		holderToName(IlvGraphicHolder* holder);

    //---- filter ----
    void		filterOn(IliRepositFilterOn filter);

    IlBoolean		isFilterOn(IliRepositFilterOn filter) const;
    IlBoolean		isValidHolder(IlvGraphicHolder*,
				      IlBoolean = IlTrue) const;

    //---- Build ----
    void		firstBuild() { if (_autoBuild) build(); }
#ifdef DOXYGEN_GENERATION
    virtual void	build();
#else
    virtual void	build(IliDataSource* ds = 0);
#endif
    virtual void	justBeforeBuild();
    virtual void	justAfterBuild();
    virtual void	addDataSource(IliDataSource* ds);

    //---- read/write ----
    void		read(IlvInputFile& input);
    void		write(IlvOutputFile& output) const;

    //---- Other ----
    IlBoolean		isAutoBuild() const { return _autoBuild; }
    static const char*	GetUntitledString(IlvDisplay*);

    virtual
    IlvGraphicHolder*	getSelectedHolder();

protected:
    IliRepositFilterOn	_filterOn;
    IlBoolean		_autoBuild;

    static IliHolderToNameCallback _HolderToNameFn;
    static IliString	_unTitled;

    static IlvBitmap*	GetHolderBitmap(IlvDisplay*);
    static IlvBitmap*	GetDataSourceBitmap(IlvDisplay*);
    static IlvBitmap*	GetGlobalDataSourceBitmap(IlvDisplay*);
};

// --------------------------------------------------------------------------
// IliTreeRepositoryGadget
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTreeRepositoryGadget
    : public IlvTreeGadget, public IliRepositoryService
{
public:
    IliTreeRepositoryGadget(IlvDisplay* display,
			    const IlvRect& rect,
			    IlUShort thickness = IlvDefaultGadgetThickness,
			    IlvPalette* palette = 0);
    IliTreeRepositoryGadget(IlvDisplay* display,
			    const IlvRect& rect,
			    IlBoolean autoBuild,
			    IlUShort thickness = IlvDefaultGadgetThickness,
			    IlvPalette* palette = 0);
    virtual ~IliTreeRepositoryGadget();

    DeclareTypeInfo();
    DeclareIOConstructors(IliTreeRepositoryGadget);

    //---- TreeGadget ----
    virtual void	expand(IlvTreeGadgetItem* item);

    //---- holder ----
    IlvTreeGadgetItem*	addHolderItem(IlvGraphicHolder*);
    IlvTreeGadgetItem*	findHolderItem(IlvGraphicHolder*);
    IlInt		getIndexForInsertHolder(const char*);

    //---- dataSource ----
    virtual void	addDataSource(IliDataSource*);
    void		addDataSourceItem(IlvTreeGadgetItem*, IliDataSource*);
    void		removeDataSource(IliDataSource*);
    IlvTreeGadgetItem*	findDataSourceItem(IlvTreeGadgetItem*, IliDataSource*);
    IlInt		getIndexForInsertDataSource(IlvTreeGadgetItem*,
						    const char*);

    //---- column ----
    void		addColumnItem(IlvTreeGadgetItem*, const char*);
    IlvTreeGadgetItem*	findColumnItem(IlvTreeGadgetItem*, const char*);
    IlInt		getIndexForInsertColumn(IlvTreeGadgetItem*,
						const char*);

    //---- Other ----
    virtual void	justBeforeBuild();
    virtual void	justAfterBuild();
    virtual
    IlvGraphicHolder*	getSelectedHolder();

protected:
    void		initializeService();
};

// --------------------------------------------------------------------------
// IliTableRepositoryGadget
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliTableRepositoryGadget
    : public IliTableGadget, public IliRepositoryService
{
public:
    IliTableRepositoryGadget(IlvDisplay* display,
			     const IlvRect& rect,
			     IlUShort thickness = IlvDefaultGadgetThickness,
			     IlvPalette* palette = 0);
    IliTableRepositoryGadget(IlvDisplay* display,
			     const IlvRect& rect,
			     IlBoolean autoBuild,
			     IlUShort thickness = IlvDefaultGadgetThickness,
			     IlvPalette* palette = 0);
    virtual ~IliTableRepositoryGadget();

    DeclareTypeInfo();
    DeclareIOConstructors(IliTableRepositoryGadget);

    //---- dataSource ----
    virtual void	addDataSource(IliDataSource*);
    void		addDataSourceItem(const char*, IliDataSource*);

    //---- Other ----
    virtual void	justBeforeBuild();
    virtual void	justAfterBuild();
    virtual
    IlvGraphicHolder*	getSelectedHolder();

protected:
    virtual IliTable*	createTable();
    void		initializeService();

    IliTableBuffer*	_buffer;
};

// --------------------------------------------------------------------------
// IliDataSourcesUsesGadget
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDataSourcesUsesGadget
    : public IlvTreeGadget, public IliRepositoryService
{
public:
    IliDataSourcesUsesGadget(IlvDisplay* display,
			     const IlvRect& rect,
			     IlUShort thickness = IlvDefaultGadgetThickness,
			     IlvPalette* palette = 0);
    IliDataSourcesUsesGadget(IlvDisplay* display,
			     const IlvRect& rect,
			     IlBoolean autoBuild,
			     IlUShort thickness = IlvDefaultGadgetThickness,
			     IlvPalette* palette = 0);
    virtual ~IliDataSourcesUsesGadget();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDataSourcesUsesGadget);

    //---- holder ----
    IlvTreeGadgetItem*	addHolderItem(IlvTreeGadgetItem*, IlvGraphicHolder*);
    IlvTreeGadgetItem*	findHolderItem(IlvTreeGadgetItem*, IlvGraphicHolder*);
    IlInt		getIndexForInsertHolder(IlvTreeGadgetItem*,
						const char*);

    //---- dataSource ----
    virtual void	addDataSource(IliDataSource*);
    IlvTreeGadgetItem*	addDataSourceItem(IliDataSource*);
    void		removeDataSource(IliDataSource*);
    IlvTreeGadgetItem*	findDataSourceItem(IliDataSource*);
    IlInt		getIndexForInsertDataSource(const char*);

    //---- gadget ----
    void		addGadgetItem(IliDataSource*, IlvGraphic*);
    IlvTreeGadgetItem*	findGadgetItem(IlvTreeGadgetItem*, IlvGraphic*);
    IlInt		getIndexForInsertGadget(IlvTreeGadgetItem*,
						const char*);

    //---- Other ----
    virtual void	justBeforeBuild();
    virtual void	justAfterBuild();
    virtual
    IlvGraphicHolder*	getSelectedHolder();
};

// --------------------------------------------------------------------------
// IliTreeClassesGadget
// --------------------------------------------------------------------------

class ILV_DBG_EXPORTED IliTreeClassesGadget : public IlvTreeGadget
{
public:
    IliTreeClassesGadget(IlvDisplay* display,
			 const IlvRect& rect,
			 IlBoolean enableExpand = IlFalse,
			 IlUShort thickness = IlvDefaultGadgetThickness,
			 IlvPalette* palette = 0);
    virtual ~IliTreeClassesGadget();

    DeclareTypeInfo();
    DeclareIOConstructors(IliTreeClassesGadget);

    //---- building ----
    virtual void	build();

    virtual char**	getClassesList(IlInt& count);

    void		setClassesListCallback(IliGetClassesListCallback cb,
					       IlAny any = 0);

    IliGetClassesListCallback getClassesListCallback() const;

    IlAny		getClassesListCallbackData() const;

    virtual char**	getDataList(const char* cl, IlInt& count);

    void		setDataListCallback(IliGetDataListCallback cb,
					    IlAny any = 0);

    IliGetDataListCallback getDataListCallback() const;

    IlAny		getDataListCallbackData() const;

    //---- Classes ----
    void		addClassItem(const char*);
    IlvTreeGadgetItem*	findClassItem(const char*);
    IlInt		getIndexForInsertClass(const char*);

    //---- Data ----
    IlvTreeGadgetItem*	addDataItem(IlvTreeGadgetItem*, const char*);
    IlvTreeGadgetItem*	findDataItem(IlvTreeGadgetItem*, const char*);
    IlInt		getIndexForInsertData(IlvTreeGadgetItem*,
					      const char*);

    //---- TreeGadget ----
    virtual void	expand(IlvTreeGadgetItem* item);
    virtual IlBoolean	handleTreeEvent(IlvEvent&);

    //---- Drag and drop ----
    IliTreeEventCallback getDragDropCallback();

    IlAny		getDragDropCallbackData();

    void		setDragDropCallback(IliTreeEventCallback cb,
					    IlAny any = 0);

    //---- Other ----
    void		enableExpand(IlBoolean enable);

    IlBoolean		isExpandEnabled() const;

    void		enableMultiSelectData(IlBoolean enable);
    IlBoolean		isMultiSelectDataEnabled() const;

    virtual IlBoolean	handleEvent(IlvEvent& event);

protected:
    IliGetClassesListCallback	_classesListCallback;
    IlAny			_classesListData;

    IliGetDataListCallback	_dataListCallback;
    IlAny			_dataListData;

    IliTreeEventCallback	_dragDropCallback;
    IlAny			_dragDropData;

    IlBoolean			_enableExpand;
    IlBoolean			_enableMultiSelect;

    void		initializeData();
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliTreeRepositoryGadget);

#endif
