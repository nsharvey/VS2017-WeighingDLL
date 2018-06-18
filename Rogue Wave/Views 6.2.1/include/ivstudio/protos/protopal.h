// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/protos/protopal.h
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
// Declarations for Prototype palette.
// --------------------------------------------------------------------------
#ifndef __IlvSt_Protos_Protopal_H
#define __IlvSt_Protos_Protopal_H

#include <ivstudio/panel.h>
#include <ivstudio/ddpalet.h>
#include <ivstudio/protos/stproto.h>
#include <ilviews/protos/proto.h>
#include <ilviews/base/iostream.h>

extern ILVSTPREXPORTEDVAR(const char*) IlvNmNewProtoLibrary;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmOpenProtoLibrary;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmSaveProtoLibrary;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmSaveProtoLibraryAs;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmCloseProtoLibrary;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmNewPrototype;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmEditPrototype;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmLoadPrototype;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmReplacePrototype;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmRenamePrototype;
extern ILVSTPREXPORTEDVAR(const char*) IlvNmDeletePrototype;

// ---------------------------------------------------------------------------
// IlvPrototypePalette		Prototype Palette class.
// ---------------------------------------------------------------------------

class ILVSTPRCLASS IlvPrototypePalette
{
public:
    IlvPrototypePalette(IlvStudio* editor);
    ~IlvPrototypePalette();
    // ____________________________________________________________
    void postInitialize();
    void show();
    IlvStudio* getEditor() { return(_editor); }
    IlvDisplay* getDisplay() { return(_editor->getDisplay()); }
    IlvProtoLibrary* newLibrary(const char* name = 0);
    IlvProtoLibrary* loadLibrary(IL_STDPREF istream* str,
				 const char* libname,
				 const char* libfile = 0);
    IlBoolean saveLibrary(IL_STDPREF ostream* str);
    IlBoolean closeLibrary();
    void setCurrentLibrary(IlvProtoLibrary* library,
			   IlBoolean update = IlTrue);
    IlvProtoLibrary* getCurrentLibrary() { return(_currentLibrary); }
    void setCurrentLibraryName(const char* name);
    IlvProtoLibrary* getLibrary(const char* name);
    const char** getLibraryNames(IlUInt& count);
    IlvProtoLibrary** getLibraries(IlUInt& count);
    void selectPrototype(IlvPrototype* prototype);
    IlvPrototype* getSelectedPrototype();
    IlvGroup* getSelectedGroup();
    IlvPrototype* replacePrototype(IlvPrototype* oldPrototype,
				   IlvGroup* group,
				   IlBoolean save = IlFalse);
    void createProtoInstance(IlvPrototype* proto,
			     IlvView* target,
			     const IlvPoint& position,
			     IlBoolean doProtoGraphic);
    IlvStDdPalettePanel* getDDPalette() { return(_ddPalette); }
    void paletteContainerInitialized(IlvStPaletteDescriptor* pdesc);
    void paletteSelected(IlvStPaletteDescriptor* pdesc);

    static void LoadLibraryCallback(IlvAbstractProtoLibrary* lib, IlAny arg);
inline IlvContainer* getContainer() const { return _currentContainer; }
    void updateProtoGraphics(IlvContainer* cont, IlvProtoLibrary* library);

    IlAList& getCache() { return _libCache; }
    static IlvDim XMargin;
    static IlvDim YMargin;
    static IlvDim SelectionMargin;
    static IlBoolean DontUseIcons;

protected:
    IlvStudio* _editor;
    IlvProtoLibrary* _currentLibrary;
    IlAList _libraries;
    IlAList _libCache;
    IlvStDdPalettePanel* _ddPalette;
    IlvTreeGadgetItem* _rootProtoItem;
    IlvInteractor* _ddInter;
    IlvContainer* _currentContainer;

    void addLibrary(IlvProtoLibrary* library);
    void removeLibrary(IlvProtoLibrary* library);
    char* makePaletteName(const char* libName);
};

#endif /* !__IlvSt_Protos_Protopal_H */
