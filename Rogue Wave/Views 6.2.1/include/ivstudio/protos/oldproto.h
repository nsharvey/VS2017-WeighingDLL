// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/protos/oldproto.h
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

#ifndef __IlvSt_Protos_Oldproto_H
#define __IlvSt_Protos_Oldproto_H

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// stproto.h		declarations for IlvPrototypeStudio class
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------


#include <ivstudio/stbuffer.h>
#include <ivstudio/protos/stproto.h>
#include <ilviews/protos/grphnint.h>
#include <ivstudio/gadgets/gadbuf.h>

// DLL macros
//
#if defined(ILVSTOLDPRLIB)
#define ILVSTOLDPREXPORTEDDEF ILVBASEEXPORTED
#define ILVSTOLDPREXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTOLDPREXPORTEDDEF ILVBASEIMPORTED
#define ILVSTOLDPREXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTOLDPRCLASS ILVSTOLDPREXPORTEDDEF
#define ILVSTOLDPREXPORTEDVAR(type) ILVSTOLDPREXPORTEDDEF type
#define IlvDECLAREINITSTOLDPRCLASS(m) IL_MODULEINIT(m, ILVSTOLDPRCLASS);

extern ILVSTOLDPREXPORTEDVAR(const char*) IlvNmNewPrototypeGadgetManagerBuffer;
extern ILVSTOLDPREXPORTEDVAR(const char*) IlvNmNewPrototypeManagerBuffer;

// ---------------------------------------------------------------------------
// IlvStPrototypeGrapherBuffer
// ---------------------------------------------------------------------------

class ILVSTOLDPRCLASS IlvStPrototypeGrapherBuffer
: public IlvStGrapherBuffer
{
public:
    IlvStPrototypeGrapherBuffer(IlvStudio*, const char* name, IlvManager* = 0);

    virtual const char* getType () const;
    virtual const char* getTypeLabel () const;
    virtual IlBoolean  isA2DBuffer() const;
    virtual void setView(IlvView*);
    virtual void select();
    virtual void unSelect();
    virtual void codeHeaderFile(IL_STDPREF ostream&, IlvStPanelClass*) const;
    virtual void setUpPanelClass(IlvStPanelClass*) const;
};

extern ILVSTOLDPREXPORTEDFUNCTION(IlBoolean)
    IlvStIsAPrototypeGrapherBuffer(IlvStBuffer* buffer);

// ---------------------------------------------------------------------------
// IlvStPrototypeEditionBuffer
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Interactors used in prstudio
// ---------------------------------------------------------------------------

class ILVSTOLDPRCLASS IlvStGroupSelectInteractor
    	: public IlvGroupSelectInteractor {
public:
	IlvStGroupSelectInteractor(IlvStudio* ed,
				   IlvManager* mgr,
				   IlvView* view)
	    : IlvGroupSelectInteractor(mgr, view), _editor(ed) {}
	IlvStGroupSelectInteractor(IlvStudio* ed)
	    : IlvGroupSelectInteractor(), _editor(ed) { useGhostRectangle(IlTrue); }

	virtual IlBoolean handleEvent(IlvEvent& event);

	virtual void objectReshaped(IlvGraphic*);
	virtual void addedToSelection(IlvGraphic*);
	virtual void removedFromSelection(IlvGraphic*);
	virtual void doSelect();
	virtual void init();
	virtual void abort();

protected:
	IlvStudio* _editor;
};

class ILVSTOLDPRCLASS IlvStGroupGraphSelectInteractor
	: public IlvGroupGraphSelectInteractor {
public:
	IlvStGroupGraphSelectInteractor(IlvStudio* ed,
					IlvManager* mgr,
					IlvView* view)
	    : IlvGroupGraphSelectInteractor(mgr, view), _editor(ed) {}
	IlvStGroupGraphSelectInteractor(IlvStudio* ed)
	    : IlvGroupGraphSelectInteractor(), _editor(ed) { useGhostRectangle(IlTrue); }

	virtual IlBoolean handleEvent(IlvEvent& event);

	virtual void objectReshaped(IlvGraphic*);
	virtual void addedToSelection(IlvGraphic*);
	virtual void removedFromSelection(IlvGraphic*);
	virtual void doSelect();
	virtual void init();
	virtual void abort();

protected:
	IlvStudio* _editor;
};

class ILVSTOLDPRCLASS IlvStNodeSelectInteractor
	: public IlvStSelectInteractor {
public:
	IlvStNodeSelectInteractor(IlvStudio* ed,
				  IlvManager* mgr,
				  IlvView* view)
	    : IlvStSelectInteractor(ed, mgr, view) {}
	IlvStNodeSelectInteractor(IlvStudio* ed)
	    : IlvStSelectInteractor(ed) {}

	virtual void removedFromSelection(IlvGraphic*);
	virtual void addedToSelection(IlvGraphic*);
	virtual void doSelect();
};

class IlvPrototype;
// ---------------------------------------------------------------------------
// IlvStPrototypeManagerBuffer
// ---------------------------------------------------------------------------

class ILVSTOLDPRCLASS IlvStPrototypeManagerBuffer
: public IlvStBuffer
{
public:
    IlvStPrototypeManagerBuffer(IlvStudio*, const char* name, IlvManager* = 0);

    virtual const char* getType () const;
    virtual const char* getTypeLabel () const;
    virtual void select();
    virtual void unSelect();
    virtual void codeHeaderFile(IL_STDPREF ostream&, IlvStPanelClass*) const;
    virtual void setUpPanelClass(IlvStPanelClass*) const;
};

// ---------------------------------------------------------------------------
// IlvStPrototypeGadgetManagerBuffer
// ---------------------------------------------------------------------------

class ILVSTOLDPRCLASS IlvStPrototypeGadgetManagerBuffer
: public IlvStGadgetBuffer
{
public:
    IlvStPrototypeGadgetManagerBuffer(IlvStudio*, const char* name,
				      IlvManager* = 0);

    virtual const char* getType () const;
    virtual const char* getTypeLabel () const;
    virtual void setView(IlvView*);
    virtual void select();
    virtual void unSelect();
    virtual void codeHeaderFile(IL_STDPREF ostream&, IlvStPanelClass*) const;
    virtual void setUpPanelClass(IlvStPanelClass*) const;
    virtual char* save(IlBoolean restoreModified = IlFalse);
};

class ILVSTOLDPRCLASS IlvStPrototypeCompatExtension
: public IlvStExtension {
public:
    IlvStPrototypeCompatExtension(IlvStudio* editor);

    virtual IlBoolean	preInitialize();
    virtual IlBoolean	initializeCommandDescriptors();
    virtual IlBoolean	initializePanels();
    virtual IlBoolean	initializeBuffers();
    virtual IlBoolean initializeModes();
    virtual IlBoolean	postInitialize();

    static IlvStPrototypeCompatExtension* Get(IlvStudio* editor);
};

class ILVSTOLDPRCLASS IlvPrototypeStudio
: public IlvStudio
{
    friend class IlvStPrototypeExtension;
public:
    IlvPrototypeStudio(IlvDisplay*, int argc = 0, char** argv = 0);

    virtual void initialize();
};

#endif
