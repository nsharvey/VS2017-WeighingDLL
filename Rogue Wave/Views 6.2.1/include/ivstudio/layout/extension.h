// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/extension.h
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
// Declaration of the IlvStLayoutExtension class
// Defined in library ilvstlayout
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Extension_H
#define __IlvSt_Layout_Extension_H

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Studext_H)
#include <ivstudio/studext.h>
#endif /* __IlvSt_Studext_H */

#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif /* __Ilv_Gadcont_H */

#if !defined(__IlvSt_Layout_Insppnl_H)
#include <ivstudio/layout/insppnl.h>
#endif /* __IlvSt_Layout_Insppnl_H */

class ILVSTLAYEXPORTED IlvStLayoutExtension
: public IlvStExtension
{
public:
    IlvStLayoutExtension(IlvStudio*);
    ~IlvStLayoutExtension();

    virtual IlBoolean	initializeCommandDescriptors();
    virtual IlBoolean	initializePanels();
    virtual IlBoolean	postInitialize();

    IlvGadgetContainer*	getLayoutPanel() { return _inspPanel; }
    void		registerLayoutInterface(const char*,
						IlvLayoutInspectorInterface*);
    void		resetFromBuffer();

    static IlvStLayoutExtension*	Get(IlvStudio*);
    static IlvStLayoutExtension*	Make(IlvStudio*);

    IlvDeclareClassInfo();

private:
    IlvLayoutInspectorPanel*	_inspPanel;
    IlAList* 	_layoutItf;
};

ILVSTLAYMODULEINIT(l_extension)
#endif /* __IlvSt_Layout_Extension_H */
