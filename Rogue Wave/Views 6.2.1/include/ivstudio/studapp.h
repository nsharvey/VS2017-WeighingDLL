// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/studapp.h
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
// Declaration of IlvStApplicationReader
// --------------------------------------------------------------------------
#ifndef __IlvSt_Studapp_H
#define __IlvSt_Studapp_H

#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if !defined(__Ilv_Appli_H)
#include <ilviews/gadgets/appli.h>
#endif
#if defined(ILVSTD)
#include <iostream>
#else /* !ILVSTD */
#include <iostream.h>
#endif

class IlvSdManager;
class IlvState;
class IlvStPanelInstance;
class IlvStPanelClass;
class IlvStAppDescriptor;
class IlvStudioApplication;
class IlvStContainerInfoSet;

// --------------------------------------------------------------------------
typedef IlvContainer*
(* IlvStContainerConstructor)(IlvDisplay*,
			      const char* name,
			      const char* title,
			      const IlvRect& bbox,
			      IlUInt properties,
			      IlBoolean useAccel,
			      IlBoolean visible,
			      IlvSystemView transiFor,
			      IlAny arg);
IL_DEFINEFPTRTOANYCAST(IlvStContainerConstructor);

typedef void (*IlvStQuitApplicationCallback)(IlvStudioApplication*);
IL_DEFINEFPTRTOANYCAST(IlvStQuitApplicationCallback);

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStudioApplication
: public IlvApplication
{
public:
    IlvStudioApplication(const char* name,
			 const char* displayName,
			 int argc = 0,
			 char** argv = 0,
			 IlvStAppDescriptor* appdesc = 0,
			 IlBoolean appdescOwner = IlFalse);
    IlvStudioApplication(IlvDisplay* display,
			 const char* name,
			 IlBoolean  owner = IlFalse,
			 IlvStAppDescriptor* appdesc = 0,
			 IlBoolean	     appdescOwner = IlFalse);
    virtual ~IlvStudioApplication();

    virtual void	quit();
    IlBoolean		read(const char* fname, IlBoolean realize = IlFalse);
    virtual IlBoolean	read(ILVSTDPREF istream&);
    virtual void	realize();
    virtual void	makePanels();
    virtual void	makeSubPanels(IlvContainer* parcont,
				      IlvStPanelInstance* parinst);
    virtual void	makeStates();
    virtual void	readStateFile();
    virtual void	reset();

    virtual IlvGraphicCallback getCallback(const char*) const;
    void		setCallbacks(IlvHashTable*, IlBoolean = IlFalse);
    void		registerCallback(const char*, IlvGraphicCallback);
    void		unregisterCallback(const char*);
    IlvGraphicCallback	getRegisteredCallback(const char*) const;
    IlvGraphicCallback	getDefaultCallback() const { return _defaultCallback; }
    void		setDefaultCallback(IlvGraphicCallback cback)
	{ _defaultCallback = cback; }


    IlvStAppDescriptor* getDescriptor() const { return _appdesc; }
    void		setDescriptor(IlvStAppDescriptor*, IlBoolean owner);
    char*		makeDataFileName(const IlvStPanelClass*) const;
     // --- creating containers ---
    void		setContainerInfoSet(IlvStContainerInfoSet* cbuilder,
					    IlBoolean owner);
    IlvStContainerInfoSet* getContainerInfoSet() const
	{ return _containerInfoSet; }
    IlvStContainerInfoSet& containerInfoSet();
    virtual IlvContainer* createContainer(const IlvStPanelInstance*,
					 const IlvStPanelClass*);
    virtual IlvContainer* createSubContainer(IlvContainer* parent,
					     const IlvStPanelInstance*,
					     const IlvStPanelClass*);
    virtual void		setUpContainer(IlvContainer* cont,
			               const IlvStPanelInstance*,
			 	       const IlvStPanelClass*);
    void		registerCallbacks(IlvContainer*);
    void		registerContainerConstructor(
	const char* className,
	IlvStContainerConstructor func,
	IlAny funcArg = 0);
    IlvStContainerConstructor getContainerConstructor(
	const char* className) const;
    IlAny		getContainerConstructorArg(const char*) const;
    void		registerDestroyCallback(const char* name,
					        IlvDestroyCallback,
						IlAny data = 0);
    IlvDestroyCallback	getDestroyCallback(const char* name) const;
    IlAny		getDestroyCallbackData(const char* name) const;
    IlvSdManager*	getStateManagerDescriptor() const
	{ return _stateManagerDescriptor; }
    void		setStateManagerDescriptor(IlvSdManager* mgr)
	{ _stateManagerDescriptor = mgr; }
    virtual IlvStateManager* getRootState() const;
    virtual IlBoolean setState(const char* stateName);
    IlvStQuitApplicationCallback getQuitCallback() const { return _quitCb; }
    void setQuitCallback(IlvStQuitApplicationCallback cb) { _quitCb = cb; }
    IlAny getOwner() const { return _owner; }
    void setOwner(IlAny owner) { _owner = owner; }
protected:
    IlvStContainerInfoSet*	_containerInfoSet;
    IlBoolean			_containerInfoSetOwner;
    IlvStHash			_containerConstructors;
    IlvStHash			_containerConstructorArgs;
    IlvStHash			_destroyCallbacks;
    IlvStHash			_destroyCallbackData;
    IlvStAppDescriptor*		_appdesc;
    IlvSdManager*		_stateManagerDescriptor;
    IlvStateManager*		_rootState;
    IlvHashTable*		_callbacks;
    IlBoolean			_callbacksOwner;
    IlvGraphicCallback		_defaultCallback;
    IlBoolean			_appdescOwner;
    IlvStQuitApplicationCallback _quitCb;
    IlAny			_owner;

    void		initStudioApplication(IlvStAppDescriptor*, IlBoolean);
}; // class IlvStudioApplication

// --------------------------------------------------------------------------
#endif /* __IlvSt_Studapp_H */
