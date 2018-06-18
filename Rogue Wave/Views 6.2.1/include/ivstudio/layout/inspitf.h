// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/layout/inspitf.h
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
// Declaration of the IlvLayoutInspectorInterface class
// Defined in library ilvstlayout
// --------------------------------------------------------------------------
#ifndef __IlvSt_Layout_Inspitf_H
#define __IlvSt_Layout_Inspitf_H

#if !defined(__IlvSt_Layout_Macros_H)
#include <ivstudio/layout/macros.h>
#endif /* __IlvSt_Layout_Macros_H */

#if !defined(__IlvSt_Layout_Insppnl_H)
#include <ivstudio/layout/insppnl.h>
#endif /* __IlvSt_Layout_Insppnl_H */

#if !defined(__Ilv_Layout_Gphlayout_H)
#include <ilviews/layout/gphlayout.h>
#endif /* __Ilv_Layout_Gphlayout_H */

class ILVSTLAYEXPORTED IlvLayoutInspectorInterface
{
public:
    IlvLayoutInspectorInterface(IlvGraphLayout*, const char*);
    virtual ~IlvLayoutInspectorInterface();

    virtual IlBoolean	buildPage(IlvLayoutInspectorPanel*) = 0;
    virtual IlBoolean	createAccessors(IlvLayoutInspectorPanel*);

    virtual IlBoolean	selectLayout(IlvLayoutInspectorPanel*);
    virtual void	objectSelected(const IlvGraphic*);

    IlvGraphLayout*	getLayout() const;
    const char*		getFileName() const;
    IlvLayoutAccessor*	getLayoutAccessor() const;

    IlvDeclareClassInfo();

protected:

private:
    IlvGraphLayout*	_layout;
    const char*		_fileName;
    IlvLayoutAccessor*	_layoutAcc;
};

// --------------------------------------------------------------------------
ILVSTLAYMODULEINIT(l_inspitf)
#endif /* !__IlvSt_Layout_Inspitf_H */
