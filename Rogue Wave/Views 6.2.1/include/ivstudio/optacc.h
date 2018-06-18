// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/optacc.h
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
// Declaration of the accessor classes used to access studio options
// --------------------------------------------------------------------------

#ifndef __IlvSt_Optacc_H
#define __IlvSt_Optacc_H

#ifndef __IlvSt_PropAcc_H
#include <ivstudio/propacc.h>
#endif

#ifndef __IlvSt_Studio_H
#include <ivstudio/studio.h>
#endif

#ifndef __Ilv_Base_Hash_H
#include <ilviews/base/hash.h>
#endif

// --------------------------------------------------------------------------
class IlvStudio;
class IlvFileSelectorField;
class IlvStCommandDescriptor;
class IlvStIProxyListGadget;
// --------------------------------------------------------------------------
// class IlvStNameRefCounter
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStNameRefCounter :
    public IlHashTable {
public:
    IlvStNameRefCounter(IlUInt nBuckets = IlHashDefaultLowestSize) :
	IlHashTable(nBuckets), _names(0), _namesCount(0) {}
    ~IlvStNameRefCounter();

    IlBoolean addName(const IlSymbol*); // return IlTrue if the name was not present
    IlBoolean addName(const char* name) // return IlTrue if the name was not present
    {	return addName(IlvGetSymbol(name, IlTrue)); }
    IlBoolean removeName(const IlSymbol*); // return IlTrue if name keeps not present in table
    IlBoolean removeName(const char* name) // return IlTrue if name keeps not present in table
    {	return removeName(IlvGetSymbol(name, IlTrue)); }
    const char** getNames(IlUInt& count);
 protected:
    const char** _names;
    IlUInt      _namesCount;
};

// --------------------------------------------------------------------------
// class IlvStStudioOptionsAccessor
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStStudioOptionsAccessor
    : public IlvStIPropertyAccessor {
 public:
    IlvStStudioOptionsAccessor(IlvStudio* studio);
    virtual void	   set(const IlvStIProperty*, IlvStIEditor* edt);

    IlvStudio* getStudio()const { return _studio; }
 protected:
    IlvStudio* _studio;

    virtual IlvStIProperty* getOriginalValue();
};

// --------------------------------------------------------------------------
// class IlvStCmdDescriptorsAccessor
// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStCmdDescriptorsAccessor
    : public IlvStIPropertyListAccessor {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStCmdDescriptorsAccessor(IlvStStudioOptionsAccessor*,
			        const char* name,
			        IlvStIAccessor::UpdateMode = IlvStIAccessor::Inherited,
				IlvStIAccessor::BuildMode = IlvStIAccessor::Copy);
    ~IlvStCmdDescriptorsAccessor();

protected:
    IlvStudio* _studio;
    virtual IlvStIProperty* createProperty(IlUInt, IlAny) const;
    virtual IlvStIProperty* copyProperty(const IlvStIProperty* property);
    virtual void deleteProperty(IlvStIProperty* prop, IlUInt);
    virtual void addProperty(IlvStIProperty* prop, IlUInt index);
    virtual void replaceProperty(IlvStIProperty* origProperty,
				 IlvStIProperty* newProperty, IlUInt);
    virtual const char* getPropertyString(const IlvStIProperty* prop)const;
    virtual IlvGadgetItem*   createGadgetItem(const IlvStIProperty*)const;
    virtual IlvStIProperty** getInitialProperties(IlUInt&);

    IlvStCommandDescriptor* getCommandDescriptor(const IlvStIProperty*)const;
};

// --------------------------------------------------------------------------
// class IlvStStartupCmdArgumentAccessor
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStStartupCmdArgumentAccessor
: public IlvStPropertySetIndFieldAccessor {
public:
    IlvStStartupCmdArgumentAccessor(IlvStudio*,
			    IlvStIPropertyAccessor* cmdAccessor,
			    IlvStIAccessor::UpdateMode =
					    IlvStIAccessor::Inherited,
			    IlvStIAccessor::BuildMode =
					    IlvStIAccessor::None);

    ~IlvStStartupCmdArgumentAccessor();

protected:
    IlvStudio* _studio;

    IlBoolean needArguement()const;
    virtual IlvStIProperty* getOriginalValue();
    virtual IlvStIProperty* createDefaultProperty()const;
};

// --------------------------------------------------------------------------
// class IlvStCategoryAccessor
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStCategoryAccessor
: public IlvStRepeatablePropertyAccessor {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStCategoryAccessor(IlvStIPropertyAccessor* accessor,
			  IlvStNameRefCounter* refCounter,
			  IlvStudio*,
			  IlvStIAccessor::UpdateMode = Inherited);
    ~IlvStCategoryAccessor();

protected:
    IlvStNameRefCounter* _refCounter;
    IlvStString _defaultCategoryName;

    virtual void deleteProperty(IlvStIProperty* prop, IlUInt);
    virtual void addProperty(IlvStIProperty* prop, IlUInt index);
    virtual IlvStIProperty* createProperty(IlUInt, IlAny) const;
};

// --------------------------------------------------------------------------
// Declaration of callbacks used for accessor / editors of options

// Callbacks used by IlvStIProperyListAccessor to build a new property (in insert method)
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) StartUpCommandBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) CommandFileBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) CommandFileLoaderBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) BaseClassHeaderBuilder(IlAny);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) FileBrowserTypeBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) FontNameBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) FontFoundryBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) ToolbarCmdBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) PropToolbarBuilder(IlAny studio);
extern ILVSTEXPORTEDFUNC(IlvStIProperty*) PropLanguageBuilder(IlAny pStudio);

// Callbacks used by IlvStIProperyListAccessor to get a name of a property to draw in a list
extern ILVSTEXPORTEDFUNC(const char*)
	FileLoaderPropertyNameCallback(const IlvStIProperty* property, IlAny);
extern ILVSTEXPORTEDFUNC(const char*)
	FirstPropSetNamer(const IlvStIProperty* property, IlAny);

// Callbacks used by IlvStIProperiesListEditor to fill its list gadget
extern ILVSTEXPORTEDFUNC(void)
	CallbackLanguageFiller(IlvStIProxyListGadget& list, IlAny pStudio);
extern ILVSTEXPORTEDFUNC(void)
	SystemFiller(IlvStIProxyListGadget& list, IlAny param);
extern ILVSTEXPORTEDFUNC(void)
	CategoryFiller(IlvStIProxyListGadget& list, IlAny param);
extern ILVSTEXPORTEDFUNC(void)
	FillCommands(IlvStIProxyListGadget& list, IlvStudio* studio);

extern ILVSTEXPORTEDFUNC(IlBoolean)
    TranslatorLangCallback(IlvStIProperty* property, IlvStIProxyListGadget* list,
			   IlBoolean bInput, IlAny pStudio);

extern ILVSTEXPORTEDFUNC(IlvGadgetItem*)
GIStartupCmdBuilder(const IlvStIProperty* property, IlAny pStudio);

// --------------------------------------------------------------------------
IlvDECLAREINITSTUDIOCLASS(st_optacc)
#endif /* !__IlvSt_Optacc_H */
