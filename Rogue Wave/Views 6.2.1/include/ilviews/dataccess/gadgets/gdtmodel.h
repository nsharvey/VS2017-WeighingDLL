// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/gdtmodel.h
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
#ifndef __Ili_Gdtmodel_H
#define __Ili_Gdtmodel_H

#ifdef IL_STD
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef __Ili_Table_H
#  include <ilviews/dataccess/table.h>
#endif

class IliModelManager;
class IliProperty;
class IliMappingInspectorModel;

// --------------------------------------------------------------------------
// IliPropertiesManager
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliPropertiesManager
{
public:
    IliPropertiesManager();
    virtual ~IliPropertiesManager();

    void		read(IL_STDPREF istream&);
    void		write(IL_STDPREF ostream&) const;

    //---- Properties ----
    IlInt		declareProperty(const IliDatatype*, const char*);
    IlInt		declareProperty(const IliDatatype*,
					const char*,
					const char*,
					IlBoolean = IlTrue);
    const char*		getName(IlInt) const;
    const char*		getTitle(IlInt) const;
    IlBoolean		isPublic(IlInt) const;
    const IliDatatype*	getType(IlInt) const;
    IlInt		getIndex(const char*) const;
    IlInt		getCount() const;
    void		removeAll();
    void		remove(IlInt);

    void		set(IlInt, const IliValue&);
    void		set(IlInt, const char*);
    void		set(IlInt, IlDouble);
    void		set(IlInt, IlInt);
    void		set(IlInt, IlBoolean);

    const IliValue&	get(IlInt) const;
    const char*		getString(IlInt) const;
    IlDouble		getDouble(IlInt) const;
    IlInt		getInteger(IlInt) const;
    IlBoolean		getBoolean(IlInt) const;

    virtual void	propertyChanged(IlInt);

    void		importValues(const IliPropertiesManager&);

    IliPropertiesManager& operator=(const IliPropertiesManager&);

protected:
    IliProperty**	_properties;
    IlInt		_propertyCount;
};

// --------------------------------------------------------------------------
// IliModel
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliModel
{
public:
    IliModel();
    virtual ~IliModel();

    //---- Basic methods ----
    virtual const char*	getName() const;
    virtual const char*	getLabel() const = 0;

    virtual IlBoolean	isSubtypeOf(const IliString&) const;
    virtual IliModel*	clone() const = 0;

    //---- Inspector ----
    virtual IlBoolean	isPublic() const;

    //---- Properties ----
    void		setPropertiesManager(IliPropertiesManager*) const;
    virtual void	defineProperties();
    IlInt		declareProperty(const IliDatatype* typ,
					const char* name,
					const char* title,
					IlBoolean pub);
    IlInt		getPropertyCount() const;
    IlInt		getPropertyIndex(const char* name) const;
    const char*		getPropertyName(IlInt index) const;
    const IliValue&	getPropertyValue(const char* name) const;
    const IliValue&	getPropertyValue(IlInt index) const;
    void		setPropertyValue(const char* name,
					 const IliValue& val);
    void		setPropertyValue(IlInt index, const IliValue& val);

    virtual const char*	getMappingInspectorModelName() const;

protected:
    //---- Link ----
    IliModel*		_previous;
    IliModel*		_next;

private:
    //---- Managers ----
    IliPropertiesManager* _propMgr;

    friend class IliModelManager;
};

class IliMappingDSInspector;

// --------------------------------------------------------------------------
// IliMappingInspectorModel
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliMappingInspectorModel : public IliModel
{
public:
    IliMappingInspectorModel();
    virtual ~IliMappingInspectorModel();

    //---- Basic methods ----
    virtual const char*	getName() const;
    virtual IlBoolean	isSubtypeOf(const IliString&) const;

    //---- Defines ----
    virtual IlInt	getDataSourceMaximum() const;

    virtual IlInt	getDataSourceMinimum() const;

    virtual const char* getDataSourceLabel(IlInt dsi) const;

    virtual IlBoolean	isMandatoryDataSource(IlInt dsi) const;

    virtual IlInt	getColumnMaximum(IlInt dsi) const;

    virtual IlInt	getColumnMinimum(IlInt dsi) const;

    virtual const char*	getColumnLabel(IlInt dsi, IlInt colno) const;

    virtual IlBoolean	isMandatoryColumn(IlInt dsi, IlInt colno) const;

    virtual IlBoolean	isValidColumnType(IlInt dsi,
					  IlInt colno,
					  IliDatatype* typ) const;

    //---- Validation ----
    virtual IlBoolean	isValidDefinition(IliString& msg) const;

    //---- Choices ----
    void		setDataSourceCount(IlInt count);
    IlInt		getDataSourceCount() const;

    void		addDataSourceName(const char* name);
    void		removeDataSourceName(IlInt dsi);
    void		setDataSourceName(IlInt dsi, const char* name);
    const char*		getDataSourceName(IlInt dsi) const;

    void		setColumnCount(IlInt dsi, IlInt count);
    IlInt		getColumnCount(IlInt) const;

    void		addColumnName(IlInt dsi, const char* name);
    void		removeColumnName(IlInt dsi, IlInt colno);
    void		setColumnName(IlInt dsi,
				      IlInt colno,
				      const char* name);
    const char*		getColumnName(IlInt dsi, IlInt colno) const;  

    //---- Register ----
    static IlBoolean	RegisterModel(IliMappingInspectorModel*); 
    static IlInt	GetModelCount(); 
    static IlInt	GetModelIndex(const char*); 
    static const char*	GetModelName(IlInt); 
    static const char*	GetModelLabel(IlInt); 
    static const IliMappingInspectorModel* GetModel(IlInt); 
    static const IliMappingInspectorModel* GetModel(const char*); 
    static IliMappingInspectorModel* CreateModel(IlInt); 
    static IliMappingInspectorModel* CreateModel(const char*); 
    static IliTable*	CreateTable(IlvDisplay*);

protected:
    IliMappingDSInspector** _ds;
    IlInt		_dsCount;
};

// --------------------------------------------------------------------------
// Macro for mapping inspector model
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IliRegisterMappingInspectorModel(cl);
#else
#define IliRegisterMappingInspectorModel(cl)		\
    IliMappingInspectorModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
// IliModelManager
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliModelManager
{
public:
    IliModelManager();
    virtual ~IliModelManager();

    IlInt		registerModel(IliModel*, IlBoolean = IlTrue);
    IlInt		getModelCount() const;
    IlInt		getModelIndex(const char*) const;
    const char*		getModelName(IlInt) const;
    const char*		getModelLabel(IlInt) const;
    const IliModel*	getModel(IlInt) const;
    const IliModel*	getModel(const char*) const;
    IliModel*		createModel(IlInt) const;
    IliModel*		createModel(const char*) const;
    void		removeAllModels();
    void		removeModel(IlInt);

    IliTable*		createTable(IlvDisplay*);

protected:
    IliModel*		_models;
    IlInt		_modelCount;
};

// -------------------------------------------------------------------------
// IliModelHookInfo
// -------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliModelHookInfo
{
public:
    IliModelHookInfo();
    IliModelHookInfo(const IliModelHookInfo&);

    void		setRow(IlInt);
    IlInt		getRow() const;

    void		setColumn(IlInt);
    IlInt		getColumn() const;

    void		setFrom(IlInt);
    IlInt		getFrom() const;

    void		setTo(IlInt);
    IlInt		getTo() const;

    void		setDataSourceIndex(IlInt);
    IlInt		getDataSourceIndex() const;

    void		setReceiver(IlAny);
    IlAny		getReceiver() const;

    void		setAny(IlAny);
    IlAny		getAny() const;

protected:
    IlInt		_row1; // or from,
    IlInt		_row2; // or to, column
    IlInt		_dsIndex;
    IlAny		_receiver;
    IlAny		_any;
};

// --------------------------------------------------------------------------
// IliGadgetModel
// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliGadgetModel : public IliModel
{
public:
    IliGadgetModel();
    virtual ~IliGadgetModel();

    //---- Basic methods ----
    virtual const char*	getName() const;
    virtual IlBoolean	isSubtypeOf(const IliString&) const;

    //---- Read / Write ----
    virtual void	write(IL_STDPREF ostream &to);
    virtual void	read(IL_STDPREF istream &from);

    //---- Refresh ----
    virtual IlBoolean	refreshAll();

    //---- Events ----
    virtual void	startOfBatch();
    virtual void	endOfBatch();

    virtual void	tableDeleted(const IliModelHookInfo& info);
    virtual void	tableChanged(const IliModelHookInfo& info);

    virtual void	columnInserted(const IliModelHookInfo& info);
    virtual void	columnChanged(const IliModelHookInfo& info);
    virtual void	columnToBeDeleted(const IliModelHookInfo& info);
    virtual void	columnDeleted(const IliModelHookInfo& info);
    virtual void	columnMoved(const IliModelHookInfo& info);

    virtual void	allRowsDeleted(const IliModelHookInfo& info);
    virtual void	rowsInserted(const IliModelHookInfo& info);
    virtual void	rowInserted(const IliModelHookInfo& info);
    virtual void	rowToBeChanged(const IliModelHookInfo& info);
    virtual void	rowChanged(const IliModelHookInfo& info);
    virtual void	rowToBeDeleted(const IliModelHookInfo& info);
    virtual void	rowDeleted(const IliModelHookInfo& info);
    virtual void	rowMoved(const IliModelHookInfo& info);
    virtual void	rowsExchanged(const IliModelHookInfo& info);
    virtual void	rowsFetched(const IliModelHookInfo& info);
    virtual void	rowFetched(const IliModelHookInfo& info);
    virtual void	currentRowChanged(const IliModelHookInfo& info);

    virtual void	columnCellsChanged(const IliModelHookInfo& info);
    virtual void	cellChanged(const IliModelHookInfo& info);
};

// --------------------------------------------------------------------------
// Macro for model
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
void IliDeclareModel();
#else
#define IliDeclareModel()						\
    virtual const char*	getName() const;				\
    virtual const char*	getLabel() const;				\
    virtual IliModel*	clone() const;					\
    virtual IlBoolean	isSubtypeOf(const IliString& classn) const
#endif
#ifdef DOXYGEN_GENERATION
void IliDefineCodeModel(basiccl, cl, label);
#else
#define IliDefineCodeModel(basiccl, cl, label)				\
    const char* cl::getName() const { return ILVSTRING(cl); }		\
    const char* cl::getLabel() const { return label; }			\
    IliModel* cl::clone() const { return new cl; }			\
    IlBoolean cl::isSubtypeOf(const IliString& classn) const {		\
	return (classn == cl::getName())? IlTrue : basiccl::isSubtypeOf(classn); \
    } //
#endif

#define IliDeclareDataAccessorForModel(clmod)	\
    protected:					\
    clmod* _model

#define IliDeclareAccessorForModel(clmod)	\
    public:					\
    static IlBoolean RegisterModel(clmod*);	\
    static IlInt GetModelCount();		\
    static IlInt GetModelIndex(const char*);	\
    static const char* GetModelName(IlInt);	\
    static const char* GetModelLabel(IlInt);	\
    static const clmod* GetModel(IlInt);	\
    static const clmod* GetModel(const char*);	\
    static clmod* CreateModel(IlInt);		\
    static clmod* CreateModel(const char*);	\
    static IliTable* CreateTable(IlvDisplay*)

#define IliCodeForAccessorForModel(clmod, clgad)			\
    static IliModelManager* clmod##Manager = 0;				\
    IlBoolean clgad::RegisterModel(clmod* mod)				\
    { return (clmod##Manager->registerModel(mod) != -1)? IlTrue : IlFalse; } \
    IlInt clgad::GetModelCount() { return clmod##Manager->getModelCount(); } \
    IlInt clgad::GetModelIndex(const char* n)				\
    { return clmod##Manager->getModelIndex(n); }			\
    const char* clgad::GetModelName(IlInt n)				\
    { return clmod##Manager->getModelName(n); }				\
    const char* clgad::GetModelLabel(IlInt n)				\
    { return clmod##Manager->getModelLabel(n); }			\
    const clmod* clgad::GetModel(IlInt n)				\
    { return (clmod*)(clmod##Manager->getModel(n)); }			\
    const clmod* clgad::GetModel(const char* n)				\
    { return (clmod*)(clmod##Manager->getModel(n)); }			\
    clmod* clgad::CreateModel(IlInt n)					\
    { return (clmod*)(clmod##Manager->createModel(n)); }		\
    clmod* clgad::CreateModel(const char* n)				\
    { return (clmod*)(clmod##Manager->createModel(n)); }		\
    IliTable* clgad::CreateTable(IlvDisplay* disp)			\
    { return clmod##Manager->createTable(disp); } //

#define IliCodeAllocForModelManager(clmod)			\
    if (!clmod##Manager) clmod##Manager = new IliModelManager

#define IliCodeFreeForModelManager(clmod) delete clmod##Manager;	\
    clmod##Manager = 0

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliModel);

#endif
