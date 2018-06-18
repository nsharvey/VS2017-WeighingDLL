// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/protos/stproto.h
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

#ifndef __IlvSt_Protos_Stproto_H
#define __IlvSt_Protos_Stproto_H

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// stproto.h		declarations for IlvPrototypeStudio class
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

#include <ilviews/protos/macros.h>
#include <ilviews/base/iostream.h>
#include <ivstudio/stbuffer.h>
#include <ivstudio/studio.h>
#include <ivstudio/grapher/grapher.h>
#include <ivstudio/error.h>
#include <ivstudio/studext.h>
#include <ivstudio/stselect.h>

#include <ilviews/gadgets/idialog.h>
#include <ilviews/gadgets/stdialog.h>

#include <ilviews/protos/connint.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/valuesrc.h>
// DLL macros
//
#if defined(ILVSTPRLIB)
#define ILVSTPREXPORTEDDEF ILVBASEEXPORTED
#define ILVSTPREXPORTEDFUNCTION(type) ILVBASEEXPORTEDFUNCTION(type)
#else
#define ILVSTPREXPORTEDDEF ILVBASEIMPORTED
#define ILVSTPREXPORTEDFUNCTION(type) ILVBASEIMPORTEDFUNCTION(type)
#endif
#define ILVSTPRCLASS ILVSTPREXPORTEDDEF
#define ILVSTPREXPORTEDVAR(type) ILVSTPREXPORTEDDEF type
#define IlvDECLAREINITSTPRCLASS(m) IL_MODULEINIT(m, ILVSTPRCLASS);

extern ILVSTPREXPORTEDVAR(const char*) IlvNmNewPrototypeGrapherBuffer;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmNewPrototypeEditionBuffer;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmGroupSelection;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmSelectGroupSelectionMode;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmGroupGraphSelection;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmSelectGroupGraphSelectionMode;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmNodeSelection;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmSelectNodeSelectionMode;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmGroupConnection;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmSelectGroupConnectionMode;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmEditPrototypes;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmShowPrototypeEditor;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmShowGroupInspector;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmShowPrototypePalette;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmGroupIntoGroup;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmPrGroupIntoGraphicSet;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmPrGroupIntoSmartSet;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmPrGroupIntoSelector;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmUngroupIlvGroups;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmProtoOpenDocument;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmOpenPrototypeBuffer;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmUpdatePrototype;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmMakePrototypeNode;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmProtoSelectAll;

// ---------------------------------------------------------------------------
// IlvPrototypeStudio (Obsolete -- create an IlvStPrototypeExtension instead).
// ---------------------------------------------------------------------------

class IlvGroup;
class IlvPrototypePalette;
class IlvStPrototypeExtension;

// ---------------------------------------------------------------------------
// IlvStPrototypeExtension
// ---------------------------------------------------------------------------

class ILVSTPRCLASS IlvStPrototypeExtension
: public IlvStExtension {
public:
    IlvStPrototypeExtension(IlvStudio* editor);
    ~IlvStPrototypeExtension();
    virtual IlBoolean	preInitialize();
    virtual IlBoolean	initializeBuffers();
    virtual IlBoolean	initializeModes();
    virtual IlBoolean	initializeCommandDescriptors();
    virtual IlBoolean	initializePanels();
    virtual IlBoolean	postInitialize();

    static IlvStPrototypeExtension* Get(IlvStudio* editor);

    IlvPrototypePalette* getPrototypePalette() { return(_prototypePalette); }
    virtual void selectGroup(IlvGroup* group,
			     IlBoolean update = IlTrue,
			     IlBoolean selected = IlTrue,
			     IlBoolean unselectAll = IlFalse);
    virtual IlvGroup* getSelectedGroup(IlBoolean top = IlTrue);
#if 0
    IlvGraphic* getGroupGraphic(IlvGroup* group);
#endif
protected:
    IlvPrototypePalette* _prototypePalette;
};


// ---------------------------------------------------------------------------
// IlvStIsAPrototypeManagerBuffer
// ---------------------------------------------------------------------------

extern ILVSTPREXPORTEDFUNCTION(IlBoolean)
    IlvStIsAPrototypeManagerBuffer(IlvStBuffer* buffer);
extern ILVSTPREXPORTEDFUNCTION(IlBoolean)
    IlvStIsAPrototypeGadgetManagerBuffer(IlvStBuffer* buffer);
extern ILVSTPREXPORTEDFUNCTION(IlvStBuffer*)
CheckEditedProtos(IlvStudio*		editor,
		  const char*		msg,
		  IlvProtoLibrary*	library,
		  IlvPrototype*		proto,
		  IlBoolean		warn = IlTrue);

class ILVSTPRCLASS IlvStPrototypeEditionBuffer
: public IlvStBuffer
{
public:
    IlvStPrototypeEditionBuffer(IlvStudio*, const char* name, IlvManager* = 0);
    virtual ~IlvStPrototypeEditionBuffer();

    // Overriden virtuals
    //

    virtual const char*	getDataFileExtension() const;
    virtual const char* getType () const;
    virtual const char* getTypeLabel () const;
    virtual void select();
    virtual void unSelect();

    virtual IlvStError* doSaveCommand(IlAny arg);
    virtual IlvStError* doSaveAsCommand(IlAny arg);

    virtual void setUpPanelClass(IlvStPanelClass* pl) const;

    // Prototype management methods
    //
    IlvPrototype* getPrototype() { return(_prototype); }
    IlvPrototype* getEditedPrototype() { return(_editedPrototype); }
    void editPrototype(IlvPrototype* prototype,
		       IlBoolean fromLib = IlTrue,
		       const char* filename = 0);
    void setPrototypeName(const char* filename, const char* name = 0);

    IlBoolean makeNewNodes();
    void renameNode();

    void setEditMode(IlBoolean editMode);

    IlvStError* saveScripts();
    IlvStError* loadScripts();

    static void RenameNode(IlAny receiver,
			   IlvStudio*,
			   const IlvStMessage*,
			   IlAny arg);

    IlBoolean enableHook(IlBoolean enabled);

protected:
    IlvPrototype* _prototype;
    IlvPrototype* _editedPrototype;
    IlvManagerViewHook* _hook;
};

extern ILVSTPREXPORTEDFUNCTION(IlBoolean) IlvStIsAPrototypeEditionBuffer(IlvStBuffer* buffer);


class ILVSTPRCLASS IlvStGroupConnectInteractor
	: public IlvGroupConnectInteractor {
public:
    IlvStGroupConnectInteractor(IlvStudio* ed,
				IlvManager* manager,
				IlvView*   view)
	: IlvGroupConnectInteractor(manager, view), _editor(ed) {}
    IlvStGroupConnectInteractor(IlvStudio* ed)
	: IlvGroupConnectInteractor(), _editor(ed) {}

    virtual IlSymbol* getFromValue(IlvAccessible* from,
				   IlUInt count,
				   IlSymbol** sourceValues);
    virtual IlSymbol* getToValue(IlvAccessible* to,
				 IlUInt count,
				 IlSymbol** subscrValues);
    virtual IlSymbol** getFromToValues(IlvAccessible* from,
				       IlvAccessible* to,
				       IlUInt countfrom,
				       IlUInt countto,
				       IlSymbol** sourceValues,
				       IlSymbol** subscrValues);
    virtual IlInt selectConnection(IlvAccessible* from,
				   IlvAccessible* to,
				   IlUInt count,
				   IlSymbol** sourceValues,
				   IlSymbol** subscrValues);
    virtual void init();
    virtual void abort();
protected:
    IlvStudio* _editor;
};

// ---------------------------------------------------------------------------
// Utilities
// ---------------------------------------------------------------------------

// YesNoDialog:
//
// A sub-class of IlvIQuestionDialog for a yes/no/cancel question box.
//
class ILVSTPRCLASS IlvStProtoYesNoDialog : public IlvIQuestionDialog {
public:
    IlvStProtoYesNoDialog(IlvDisplay* display, const char* msg,
		const char* ylbl=0, const char* nlbl=0);

    IlBoolean isNo() { return(_no); }

    virtual void apply();
    virtual void no();
    virtual void handleResize(IlvRect& rect);

protected:
    IlBoolean _no;
};

// disable script execution in prototypes during its lifespan.
class ILVSTPRCLASS IlvStProtoScriptsDisabler {
public:
    int _wasDisabled;
    IlvStProtoScriptsDisabler();
    ~IlvStProtoScriptsDisabler();
};

// kludge *do not use the functions or symbols defined below.*

extern ILVSTPREXPORTEDFUNCTION(IlBoolean)
	IlvStDependsOnProto(IlvGroup* group, IlvPrototype* proto);
extern ILVSTPREXPORTEDFUNCTION(IlvProtoHolderInterface*)
	IlvStGetProtoHolder(IlvStBuffer* buffer);

extern IlvPrototype* IlvStSavedProto;
extern IlvAbstractProtoLibrary* IlvStSavedProtoLib;
extern const char* IlvStProtoStudioCmdFile;

#define _ILV_PROTO_DISABLE_HOOK(buffer) \
	    hookWasEnabled = \
	        ((IlvStPrototypeEditionBuffer*)buffer)->enableHook(IlFalse)

#define _ILV_PROTO_ENABLE_HOOK(buffer) \
	    ((IlvStPrototypeEditionBuffer*)buffer)->enableHook(hookWasEnabled)

#endif /* __IlvSt_Protos_Stproto_H */
