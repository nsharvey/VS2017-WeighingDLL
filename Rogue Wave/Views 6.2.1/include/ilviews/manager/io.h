// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/io.h
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
// Declaration of the IlvManagerOutputFile and IlvManagerInputFile classes
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Io_H
#define __Ilv_Manager_Io_H

#if !defined(__Ilv_Graphics_Io_H)
#  include <ilviews/graphics/io.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#  include <ilviews/manager/manager.h>
#endif

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerOutputFile : public IlvOutputFile
{
public:
    IlvManagerOutputFile(ILVSTDPREF ostream& stream,
			 const IlvManager*   manager = 0);
    // ____________________________________________________________
    // 1.0 compatibility
    inline
    const IlvManager*	manager()    const { return _manager; }
    inline
    const IlvManager*	getManager() const { return _manager; }
    virtual void	saveAll(const IlvManager*  manager,
				IlUInt             count   = 0,
				IlvGraphic* const* objects = 0);
    virtual void	saveMoreInfo(IlUInt count, IlvGraphic* const* objs);
    virtual void	writeObject(const IlvGraphic* object);
    virtual const char*	typeOf() const;
    inline IlBoolean	isSavingEnvironment() const  { return _saveEnv; }
    inline void		saveEnvironment(IlBoolean e) { _saveEnv = e; }
    inline IlBoolean	isSavingViews() const        { return _saveViews; }
    inline void		saveViews(IlBoolean s)       { _saveViews = s; }
    inline IlBoolean	isSavingLayers() const       { return _saveLayers; }
    inline void		saveLayers(IlBoolean s)      { _saveLayers = s; }

protected:
    void		writeProperties(const IlvManager*,
					const IlvGraphic* obj);

    const IlvManager*	_manager;
    IlBoolean		_saveEnv;
    IlBoolean		_saveLayers;
    IlBoolean		_saveViews;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerInputFile : public IlvInputFile
{
public:
    IlvManagerInputFile(ILVSTDPREF istream& stream, IlvManager* manager = 0);
    // ____________________________________________________________
    // 1.0 compatibility
    inline IlvManager*	manager()    const { return _manager; }
    IlvManager*		getManager() const { return _manager; }
    virtual void	readAll(IlvManager* manager);
    virtual
    IlvGraphic* const*	readObjects(IlvDisplay*, IlUInt& count);
    virtual IlvGraphic*	readObject();
    virtual IlBoolean	parseBlock(const char* blockName);
    virtual void	readLayer(int layer);
    virtual void	readView(IlUInt    currentNViews,
				 IlvView** currentViews);
    virtual const char*	typeOf() const;

protected:
    void		readProperties(IlvManager*, IlvGraphic* obj);

    IlvManager*		_manager;
};

#endif /* !__Ilv_Manager_Io_H */
