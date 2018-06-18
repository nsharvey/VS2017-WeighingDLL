// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/grouplin.h
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
// Declaration of the IlvGroupMediator class.
// -----------------------------------------------------------------------
#ifndef __Ilv_Protos_Grouplin_H
#define __Ilv_Protos_Grouplin_H

#ifndef __Ilv_Base_Clssinfo_H
#include <ilviews/base/clssinfo.h>
#endif
#ifndef __Ilv_Graphics_Holder_H
#include <ilviews/graphics/holder.h>
#endif
#ifndef __Ilv_Protos_Group_H
#include <ilviews/protos/group.h>
#endif
#ifndef __Ilv_Protos_Proto_H
#include <ilviews/protos/proto.h>
#endif

class IlvManager;
class IlvContainer;


class ILVPROEXPORTED IlvGroupMediator : public IlvAccessible
{
public:
    IlvGroupMediator(IlvGroup* presentation, IlAny object = 0);
    ~IlvGroupMediator();
    void		queryValues(IlvValue* values, IlUShort count) const;
    IlBoolean		changeValues(const IlvValue* values, IlUShort count);

    const char*		getName() const;
    IlvValue&		queryValue(IlvValue& val) const;
    IlBoolean		changeValue(const IlvValue& val);
    void		getAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&) const;
    virtual void	update(const IlSymbol* const* symbs = 0,
			       IlUInt count = 0);
    inline IlBoolean	locked() { return _locked; }
    inline void		lock() { _locked = IlTrue; }
    inline void		unlock() { _locked = IlFalse; }
    inline IlAny	getObject() const { return _object; }
    virtual void	setObject(IlAny arg, IlBoolean refresh = IlTrue);
    inline IlvGroup*	getPresentation() const { return _group; }
    virtual void	setPresentation(IlvGroup* group,
					IlBoolean refresh = IlTrue);

protected:
    virtual void	doSubscriptions();
    virtual void	undoSubscriptions();
    virtual void	deleteNotify(IlvAccessible*);

    IlvGroup*			_group;
    IlAny			_object;
    IlBoolean			_locked;
    IlUInt			_nvalues;
    const IlSymbol**		_cached_values;
    const IlvValueTypeClass**	_cached_types;
};


class ILVPROEXPORTED IlvProtoMediator : public IlvGroupMediator
{
public:
    IlvProtoMediator(IlvDisplay* d, const char* protoName, IlAny object = 0)
	: IlvGroupMediator(instanciatePrototype(protoName, d), object)
    {}
    IlvProtoMediator(IlvDisplay* display,
		     IlvPrototype* proto,
		     IlAny object = 0)
	: IlvGroupMediator(proto->clone(0), object)
    {}
    ~IlvProtoMediator();
    void		install(IlvContainer* holder);
    void		install(IlvManager* holder);
    virtual void	install(IlvGraphicHolder* holder);
    void		setPresentation(IlvGroup* g,
					IlBoolean refresh = IlTrue);

protected:
    IlvGroup*		instanciatePrototype(const char*, IlvDisplay*);
};

#endif /* __Ilv_Protos_Grouplin_h */
