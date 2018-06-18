// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/groupholder.h
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
// Definition of the macros that are used by Prototypes-enables managers
// --------------------------------------------------------------------------

#ifndef __Ilv_Protos_Groupholder_H
#define __Ilv_Protos_Groupholder_H

#if !defined(__Ilv_Base_Clssinfo_H)
#include <ilviews/base/clssinfo.h>
#endif
#if !defined(__Ilv_Graphics_Holder_H)
#include <ilviews/graphics/holder.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Contain_Contain_H)
#include <ilviews/contain/contain.h>
#endif
#if !defined(__Ilv_Protos_Macros_H)
#include <ilviews/protos/macros.h>
#endif
#if defined(ILVSTD)
#include <cstring>
#else  /* !ILVSTD */
#include <string.h>
#endif /* !ILVSTD */

class IlvProtoGraphic;
class IlvGroup;
class IlvAccessible;

class ILVPROEXPORTED IlvGroupHolder : public IlvNamedProperty
{
public:
    IlvGroupHolder(IlvGraphicHolder*);
    ~IlvGroupHolder();
    // ____________________________________________________________
    virtual void	addGroup(IlvGroup* group, IlBoolean unique = IlTrue);
    virtual void	removeGroup(IlvGroup* group,
				    IlBoolean destroy = IlFalse);
    virtual IlvGroup*	getGroup(const char* name) const;
    virtual IlvGroup**	getGroups(IlUInt& count) const;
    virtual
    IlvProtoGraphic*	getProtoGraphic(IlvGroup* group);

    virtual IlUInt	checkUniqueName(const char* name) const;
    inline static
    IlvGroupHolder*	Get(IlvContainer* ctn)
			{
			    return Get((IlvGraphicHolder*)(IlAny)
				       ctn->getHolder());
			}
    inline static
    IlvGroupHolder*	Get(IlvManager* mgr)
			{
			    return Get((IlvGraphicHolder*)(IlAny)
				       mgr->getHolder());
			}
    static
    IlvGroupHolder*	Get(IlvGraphicHolder* holder);    

    DeclarePropertyInfo();
    DeclarePropertyIOConstructors(IlvGroupHolder);

protected:
    IlvGraphicHolder*	_holder;
};

class IlvGroupGraphic;
class IlvValueSource;

// ---------------------------------------------------------------------------
// IlvProtoHolderInterface	Abstract class defining the interface of
//				all IlvPrototype*Manager subclasses.
// ---------------------------------------------------------------------------

class ILVPROEXPORTED IlvProtoHolderInterface
{
public:
    IlvProtoHolderInterface() {}
    virtual ~IlvProtoHolderInterface();
    // ____________________________________________________________
    virtual void	addGroup(IlvGroup* group) = 0;
    virtual void	removeGroup(IlvGroup* group) = 0;
    virtual IlvGroup*	getGroup(const char* name) const = 0;
    virtual IlvGroup**	getGroups(IlUInt& count) const = 0;
    virtual IlvGroup**	getSelectedGroups(IlUInt& count) = 0;
    virtual
    IlvGroupGraphic**	getGroupGraphics(IlUInt& count) = 0;
    virtual void	selectGroup(IlvGroup* group,
				    IlBoolean selectIt = IlTrue,
				    IlBoolean deselectAll = IlTrue) =0;
    virtual IlBoolean	isGroupSelected(IlvGroup* group) = 0;
    virtual
    IlvGroupGraphic*	getGroupGraphic(IlvGroup* group) = 0;
    virtual void	addValueSource(IlvValueSource* source) = 0;
    virtual void	removeValueSource(IlvValueSource* source) = 0;
    virtual
    IlvValueSource*	getValueSource(const char* name) const = 0;
    virtual
    IlvValueSource**	getValueSources(IlUInt& count) const = 0;
    virtual
    IlvAccessible*	getValueSourceSubscriber(const char* name) = 0;
};

// ---------------------------------------------------------------------------
// Static initialization of module.
IlvDECLAREINITPROCLASS(groupholder)

#endif
