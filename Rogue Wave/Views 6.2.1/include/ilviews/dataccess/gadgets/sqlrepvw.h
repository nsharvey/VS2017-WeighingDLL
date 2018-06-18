// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/sqlrepvw.h
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
// Declaration of the IliSQLTablesUsesGadget class
// Defined in library dbsqlgad
// --------------------------------------------------------------------------
#ifndef __Ili_Sqlrepvw_H
#define __Ili_Sqlrepvw_H

#ifndef __Ili_Repview_H
#  include <ilviews/dataccess/gadgets/repview.h>
#endif

#ifndef __Ili_Sqldtsrc_H
#  include <ilviews/dataccess/gadgets/sqldtsrc.h>
#endif

// --------------------------------------------------------------------------
// IliSQLTablesUsesGadget
// --------------------------------------------------------------------------
class ILV_DBSQLG_EXPORTED IliSQLTablesUsesGadget
    : public IlvTreeGadget, public IliRepositoryService
{
public:
    IliSQLTablesUsesGadget(IlvDisplay* display,
			   const IlvRect& rect,
			   IlUShort thickness = IlvDefaultGadgetThickness,
			   IlvPalette* palette = 0);
    IliSQLTablesUsesGadget(IlvDisplay* display,
			   const IlvRect& rect,
			   IlBoolean autoBuild,
			   IlUShort thickness = IlvDefaultGadgetThickness,
			   IlvPalette* palette = 0);
    virtual ~IliSQLTablesUsesGadget();

    DeclareTypeInfo();
    DeclareIOConstructors(IliSQLTablesUsesGadget);

    //---- TreeGadget ----
    virtual void	expand(IlvTreeGadgetItem* item);

    //---- TableRef ----
    IlvTreeGadgetItem*	addTableRefItem(const char*);
    IlvTreeGadgetItem*	findTableRefItem(const char*);
    IlInt		getIndexForInsertTableRef(const char*);

    //---- dataSource ----
    virtual void	addDataSource(IliDataSource*);
    void		addDataSourceItem(IlvTreeGadgetItem*,
					  IliDataSource*,
					  IlInt);
    void		removeDataSource(IliDataSource*);
    IlvTreeGadgetItem*	findDataSourceItem(IlvTreeGadgetItem*,
					   IliDataSource*);
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
    void		getTableName(IliSQLTable*, IlInt, IliString&);
    IlInt		getIndexTable(IliSQLTable*, IliString&);
    IlInt		getColumnsCount(IliSQLTable*, IlInt);
};

// --------------------------------------------------------------------------
// IliTreeSQLTablesGadget
// --------------------------------------------------------------------------
class ILV_DBSQLG_EXPORTED IliTreeSQLTablesGadget : public IlvTreeGadget
{
public:
    IliTreeSQLTablesGadget(IlvDisplay* display,
			   const IlvRect& rect,
			   IliSQLSession* session = 0,
			   const char* owner = 0,
			   IlUShort thickness = IlvDefaultGadgetThickness,
			   IlvPalette* palette = 0);
    virtual ~IliTreeSQLTablesGadget();

    DeclareTypeInfo();
    DeclareIOConstructors(IliTreeSQLTablesGadget);

    //---- TreeGadget ----
    virtual void	expand(IlvTreeGadgetItem* item);

    //---- Tables ----
    void		addTableItem(const char*);
    IlvTreeGadgetItem*	findTableItem(const char*);
    IlInt		getIndexForInsertTable(const char*);

    //---- column ----
    void		addColumnItem(IlvTreeGadgetItem*, const char*);
    IlvTreeGadgetItem*	findColumnItem(IlvTreeGadgetItem*, const char*);
    IlInt		getIndexForInsertColumn(IlvTreeGadgetItem*,
						const char*);

    //---- Properties ----
    void		setSession(IliSQLSession* session);

    IliSQLSession*	getSession() const;

    void		setOwner(const char* name);

    const char*		getOwner() const;

    //---- Drag and drop ----
    IliTreeEventCallback getDragDropCallback();
    IlAny		getDragDropCallbackData();
    void		setDragDropCallback(IliTreeEventCallback, IlAny = 0);

    //---- Other ----
    virtual void	build();
    virtual IlBoolean	handleEvent(IlvEvent& event);

    inline IlBoolean	isSynonym(const char* name) const
			{
			    return (_hashSynonyms &&
				    _hashSynonyms->find(IL_CONSTCAST(char*,
								     name)));
			}

protected:
    IliSQLSession*		_session;
    IliString			_owner;

    IliTreeEventCallback	_dragDropCallback;
    IlAny			_dragDropData;

    IlStringHashTable*		_hashSynonyms;
    IlvBitmap*			_synBitmap;
    char**			_synonyms;
    IlInt			_synCount;
};

IliModuleDECL_exp(ILV_DBSQLG_EXPORTED, IliSQLTablesUsesGadget);

#endif
