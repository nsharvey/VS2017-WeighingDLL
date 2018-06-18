// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/continfo.h
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
// Declaration of container info classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Continfo_H
#define __IlvSt_Continfo_H

#if !defined(__IlvSt_Object_H)
#  include <ivstudio/object.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#  include <ilviews/gadgets/gadcont.h>
#endif

class ILVSTUDIOCLASS IlvStContainerInfo : public IlvStNamedObject 
{
public:
  virtual IlvContainer* createContainer(IlvAbstractView* parent,
					const IlvRect& bbox,
					IlBoolean useacc,
					IlBoolean visible) = 0;

  virtual IlvContainer* createContainer(IlvDisplay* display,
					const char* name,
					const char* title,
					const IlvRect& bbox,
					IlUInt properties,
					IlBoolean useacc,
					IlBoolean visible,
					IlvSystemView transientFor) = 0;

  virtual const char* getFileCreatorClass() const = 0;
protected:
  IlvStContainerInfo(const char* name);

}; // class IlvStContainerInfo

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCiContainer
    : public IlvStContainerInfo {
public:
    IlvStCiContainer();

    virtual IlvContainer* createContainer(IlvAbstractView* parent,
					  const IlvRect&   bbox,
					  IlBoolean       useacc,
					  IlBoolean       visible);
    virtual IlvContainer* createContainer(IlvDisplay*,
					  const char*      name,
					  const char*      title,
					  const IlvRect&   bbox,
					  IlUInt          properties,
					  IlBoolean       useacc,
					  IlBoolean       visible,
					  IlvSystemView    transientFor);
    virtual const char* getFileCreatorClass() const;
}; // class IlvStCiContainer

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCiGadgetContainer
    : public IlvStContainerInfo {
public:
    IlvStCiGadgetContainer();

    virtual IlvContainer* createContainer(IlvAbstractView* parent,
					  const IlvRect&   bbox,
					  IlBoolean       useacc,
					  IlBoolean       visible);
    virtual IlvContainer* createContainer(IlvDisplay*,
					  const char*      name,
					  const char*      title,
					  const IlvRect&   bbox,
					  IlUInt          properties,
					  IlBoolean       useacc,
					  IlBoolean       visible,
					  IlvSystemView    transientFor);
    virtual const char* getFileCreatorClass() const;
}; // class IlvStCiGadgetContainer

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStContainerInfoSet
{
public:
    IlvStContainerInfoSet();
    virtual ~IlvStContainerInfoSet();

    void		add(IlvStContainerInfo*);
    void		remove(IlvStContainerInfo*);

    IlvStContainerInfo* getByClassName(const char*) const;
    IlvStContainerInfo* getByFileCreatorClass(const char*) const;
    IlvStContainerInfo* const* getAll(IlUInt& count) const {
	count = _cinfos.getLength();
	return (IlvStContainerInfo* const*)_cinfos.getArray();
    }
    IlvStContainerInfo*	getDefault() const { return _defaultci; }
    void		setDefault(IlvStContainerInfo* dci)
	{ _defaultci = dci; }
private:
    IlvArray	_cinfos;
    IlvStContainerInfo* _defaultci;

}; // class IlvStContainerInfoSet

// --------------------------------------------------------------------------
#endif /* __IlvSt_Continfo_H */

