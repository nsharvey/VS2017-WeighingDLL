// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/dbtimer.h
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
// Declaration of the IliDbTimer class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbtimer_H
#define __Ili_Dbtimer_H

#if !defined(__Ilv_Base_View_H)
#  include <ilviews/base/view.h>
#endif
#if !defined(__Ili_Datagem_H)
#  include <ilviews/dataccess/gadgets/datagem.h>
#endif
#if !defined(__Ili_Ivalitf_H)
#  include <ilviews/dataccess/intrface/ivalitf.h>
#endif

class IliDbTimer;

typedef IlBoolean (* IliDbTimerCallback) (IliDbTimer*, IlAny);

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTimerItem
{
public:
    IliDbTimerItem(IlInt, IliDbTimer*);
    ~IliDbTimerItem()
    {
	_next = 0;
	_gadget = 0;
	_connected = 0;
    }

    inline  void	   next(IliDbTimerItem* n) { _next = n; }
    inline IliDbTimerItem* next() const            { return _next; }

    inline void		setPeriod(IlInt period) { _period = period; }
    inline IlInt	getPeriod() const { return _period; }

    inline void		stop() { _gadget = 0; }
    inline void		run(IliDbTimer* tim) { _gadget = tim; _count = 0; }

    inline void		connect() { _connected = IlTrue; }
    inline void		disconnect() { _connected = IlFalse; }
    inline IlBoolean	isConnected() const { return _connected; }

    void		newTopTimer();

protected:
    IlBoolean		_connected;
    IliDbTimerItem*	_next;
    IlInt		_period;
    IlInt		_count;
    IliDbTimer*		_gadget;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliDbTimer
: public IliDataGem
{
public:
    IliDbTimer(IlvDisplay* display,
	       const IlvPoint& at,
	       IlInt unitPeriod = 20,
	       IlUShort thickness = IlvDefaultGadgetThickness,
	       IlvPalette* palette = 0);
    virtual ~IliDbTimer();

    DeclareTypeInfo();
    DeclareIOConstructors(IliDbTimer);

    virtual void	setHolder(IlvGadgetHolder*);

    // Properties
    void		setPeriod(IlInt units);
    inline IlInt	getPeriod() const
	{ return _itemTimer ? _itemTimer->getPeriod() : 0; }

    // Timer
    void		connectTimer();
    void		disconnectTimer();

    // Look
    virtual IlvBitmap*	getBitmap() const;

    // Accessors
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);

    // Auto connect
    static
    IliDbTimerCallback	GetAutoConnectCallback();
    static IlAny	GetAutoConnectClientData();
    static void		SetAutoConnectCallback(IliDbTimerCallback, IlAny);

protected:
    static
    IliDbTimerCallback	_AutoConnectCallback;
    static
    IlAny		_AutoConnectClientData;

    IliDbTimerItem*	_itemTimer;

    virtual void	createTimer(IlInt period);
    virtual void	deleteTimer();
    virtual void	initTimer();
};

IliModuleDECL_exp(ILV_DBG_EXPORTED, IliDbTimer);

#endif /* !__Ili_Dbtimer_H */
