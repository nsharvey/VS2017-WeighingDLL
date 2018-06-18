// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/reposit.h
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
// Declaration of the IliRepository class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Reposit_H
#define __Ili_Reposit_H

#if !defined(__Ilv_Graphics_Holder_H)
#  include <ilviews/graphics/holder.h>
#endif
#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ili_Module_H)
#  include <ilviews/dataccess/module.h>
#endif
#if !defined(__Ili_Datasrc_H)
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

class IliRepositoryIpl;

// --------------------------------------------------------------------------
typedef void (*IliDataSourceCallback)(IliDataSource* dataSource,
				      IlvGraphic* subscriber,
				      IlAny userData);
IL_DEFINEFPTRTOANYCAST(IliDataSourceCallback);

typedef void (*IliDataSourceObserver)(IliDataSource*, IlBoolean, IlAny);
IL_DEFINEFPTRTOANYCAST(IliDataSourceObserver);

typedef void (*IliApplyDataSource)(IliDataSource*, IlAny);
IL_DEFINEFPTRTOANYCAST(IliApplyDataSource);

typedef void (*IliTableContextCallback)(IliTableContext*, IlvGraphic*, IlAny);
IL_DEFINEFPTRTOANYCAST(IliTableContextCallback);

typedef void (*IliTableContextObserver)(IliTableContext*, IlBoolean, IlAny);
IL_DEFINEFPTRTOANYCAST(IliTableContextObserver);

typedef void (*IliApplyTableContext)(IliTableContext*, IlAny);
IL_DEFINEFPTRTOANYCAST(IliApplyTableContext);

// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliRepository
{
public:
    static IlInt GetDataSourcesCount();
    static IliDataSource* GetDataSource(IlInt index);

    static IliDataSource* FindDataSource(const char* name,
					 IlvGraphicHolder* holder);
    static IlBoolean IsDataSourceInScope(const IliDataSource*,
					 IlvGraphicHolder*);
    static void SubscribeToDataSource(const char* dataSourceName,
				      IliDataSourceCallback cb,
				      IlvGraphic* subscriber,
				      IlAny userData);
    static void UnSubscribeToDataSource(const char* dataSourceName,
					IliDataSourceCallback cb,
					IlvGraphic* subscriber,
					IlAny userData);

    static void AddDataSource(IliDataSource*);
    static void RemoveDataSource(IliDataSource*);

    static void AddDataSourceObserver(IliDataSourceObserver, IlAny);
    static void RemoveDataSourceObserver(IliDataSourceObserver, IlAny);

    static void MapDataSources(IliApplyDataSource, IlAny,
			       IlvGraphicHolder* = 0, IlBoolean = IlFalse);

    static IlInt GetTableContextCount();
    static IliTableContext* GetTableContext(IlInt);

    static IliTableContext* FindTableContext(const char*, IlvGraphicHolder*);
    static IlBoolean IsTableContextInScope(const IliTableContext*,
					   IlvGraphicHolder*);
    static void SubscribeToTableContext(const char*,
					IliTableContextCallback,
					IlvGraphic*, IlAny);
    static void UnSubscribeToTableContext(const char*,
					  IliTableContextCallback,
					  IlvGraphic*, IlAny);
    static void AddTableContext(IliTableContext*);
    static void RemoveTableContext(IliTableContext*);

    static void AddTableContextObserver(IliTableContextObserver, IlAny);
    static void RemoveTableContextObserver(IliTableContextObserver, IlAny);

    static void MapTableContexts(IliApplyTableContext, IlAny,
				 IlvGraphicHolder* = 0, IlBoolean = IlFalse);

    static IlvSymbol* GetScopeClass(IlvContainer* cont);

    static void SetScopeClass(IlvContainer* cont, IlvSymbol* scopeClass);

    static IlBoolean IsBadLicense();

    static void AddStudioPalette(IlvPort*);
    static IlBoolean IsStudioPalette(IlvPort*);

    static IlBoolean IsInAStudioBuffer(IlvGraphic*);
    static IlBoolean IsInAValidContainer(IlvGraphic*);

    static void AtInit();
    static void AtExit ();

    static IliRepository& Instance ();

protected:
    IliRepositoryIpl* _dsIpl;
    static IliRepository* _instance;
    static IliDataSource* _booleanDataSource;
    static IlvList* _listPalettes;
    static IlvAList* _tableContextObservers;
    static IlvAList* _dataSourceObservers;

    IliRepository ();
    virtual ~IliRepository ();
    static IliRepositoryIpl& DsIpl ();
    static void Init (IlvDisplay*);

    friend class IliModuleCLASS(IliRepository);
};

#if !defined(__Ili_Repositf_H)
#  include <ilviews/dataccess/intrface/repositf.h>
#endif

IliModuleDECL_exp(ILV_INF_EXPORTED, IliRepository);

#endif /* !__Ili_Reposit_H */
