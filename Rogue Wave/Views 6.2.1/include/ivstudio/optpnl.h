// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/optpnl.h
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
// Declaration of editor of studio's options
// --------------------------------------------------------------------------
#ifndef __IlvSt_Optpnl_H
#define __IlvSt_Optpnl_H

#ifndef __IlvSt_Util_H
#include <ivstudio/util.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#include <ilviews/gadgets/notebook.h>
#endif

#ifndef __IlvSt_PropAcc_H
#include <ivstudio/propacc.h>
#endif

#ifndef __IlvSt_Optacc_H
#include <ivstudio/optacc.h>
#endif

#ifndef __IlvSt_Studio_H
#include <ivstudio/studio.h>
#endif

#ifndef __Ilv_Base_Hash_H
#include <ilviews/base/hash.h>
#endif

#ifndef __IlvSt_Panel_H
#include <ivstudio/panel.h>
#endif

#ifndef __IlvSt_Mainedt_H
#include <ivstudio/inspectors/mainedt.h>
#endif

#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/slist.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/optmenu.h>

// --------------------------------------------------------------------------
class IlvStudio;
class IlvFileSelectorField;
class IlvStCommandDescriptor;

// --------------------------------------------------------------------------
// class IlvStOptionPanel
// --------------------------------------------------------------------------

class ILVSTUDIOCLASS IlvStOptionPanel
: public IlvStPanelHandler {
public:
    IlvStOptionPanel(IlvStudio* studio);

    virtual void doReset();
    IlBoolean resetBeforeShowing() const { return IlTrue; }
    // ____________________________________________________________
    virtual void cancelCallback(IlvGraphic*);
    virtual void applyCallback(IlvGraphic*, IlBoolean bSave);

    // ____________________________________________________________
    void linkPropertyToGadget(const char* szProperty,
			      const char* szGadget);
    void linkPropertyToDirGadget(const char* szProperty,
				 const char* szGadget,
				 IlBoolean bKeepLastSeparator = IlFalse);

    IlvStIMainEditor& getMainEditor() { return(_inspector); }

protected:
    IlvStIMainEditor             _inspector;
    IlvStStudioOptionsAccessor*  _studioOptAcc;
    IlvStCmdDescriptorsAccessor* _cmdsDescAccessor;
    IlvStNameRefCounter          _cmdCategories;
    IlBoolean                   _connectedToHolder;

    void initPropertyLinks();

    void initApplicationOptions();
    void initBufferOptions();
    void initCommandOptions();
    void initDirectoriesOptions();
    void initCodeOptions();
    void initFilesOptions();
    void initRessourcesOptions();
    void initLanguagesOptions();
    void initToolbarOptions();
    void initPanelsOptions();
    void initMiscOptions();
};

// --------------------------------------------------------------------------
#endif /* __IlvSt_Optpnl_H */
