// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbstrlst.h
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
// Declaration of the IliDbStringList class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbstrlst_H
#define __Ili_Dbstrlst_H

#if !defined(__Ilv_Gadgets_Slist_H)
#  include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ili_Fielditf_H)
#  include <ilviews/dataccess/fielditf.h>
#endif
#if !defined(__Ili_Datasrc_H)
#  include <ilviews/dataccess/gadgets/datasrc.h>
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbStringList
: public IlvStringList, public IliFieldItf
{
public:
    IliDbStringList(IlvDisplay* display,
		    const IlvRect& rect,
		    const char* const* labels = 0,
		    IlUShort count = 0,
		    IlUShort thickness = IlvDefaultGadgetThickness,
		    IlvPalette* palette = 0);
    virtual ~IliDbStringList();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbStringList);

    virtual void	setHolder(IlvGadgetHolder*);
    virtual IlBoolean	handleEvent(IlvEvent&);
    virtual void	doIt();

    // Implements IliFieldItf
    virtual const IliValue& f_getValue(IlBoolean = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue&, IlBoolean = IlFalse);
    virtual void	f_refresh();
    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();
    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean);

    virtual void	f_setForeignTable(IliTable*, IlBoolean = IlFalse);
    virtual void	f_setForeignValueColumnName(const char*);
    virtual void	f_setForeignDisplayColumnName(const char*);
    void		setForeignBitmapColumnName(const char* col);
    const char*		getForeignBitmapColumnName() const;

    virtual void	select(IlUShort);
    virtual void	unSelect(IlUShort);
    virtual void	doSelect();

    virtual
    const IlvValueTypeClass* getValueType(const IlvSymbol*) const;
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const;
    static IlBoolean	F_supportsAccessor(IliFieldAccessorTag);

protected:
    IliValue		_value;
    IlBoolean		_readOnly;
    IliTableHook*	_tableHook;
    IlUInt		_batchCount;
    IlBoolean		_refreshRequested;
    IliString		_bmpColumnName;

    IlBoolean		strListRemoveItem(IlInt);
    IlBoolean		strListAppendItem(const char*);
    IlBoolean		strListInsertItem(IlInt, const char*);
    IlBoolean		strListSetItem(IlInt, const char*);
    const char*		strListGetLabel(IlInt, IlInt = -1);

    void		init();
    void		startOfBatch();
    void		endOfBatch();
    IlInt		posInTable(const IliValue&, IlInt) const;
    IlInt		getValueColumn() const;
    IlInt		getDisplayColumn() const;
    IlInt		getBitmapColumn() const;
    IlvBitmap*		computeBitmap(const char*);
    void		refreshValuesList();

    friend class IliDbStringListHook;
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbStringList);

#endif /* !__Ili_Dbstrlst_H */
