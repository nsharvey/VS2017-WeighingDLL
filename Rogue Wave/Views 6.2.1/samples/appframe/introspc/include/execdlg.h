// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/include/execdlg.h
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
// IlogViews 4 generated header file
// File generated Thu Aug 26 16:39:39 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
// Declaration of the ExecuteMethodDlg class
// --------------------------------------------------------------------------
#if !defined(Execdlg__header__)
#define Execdlg__header__

#if !defined(__Ilv_Appframe_Dialog_H)
#include <ilviews/appframe/dialog/dialog.h>
#endif /* !__Ilv_Appframe_Document_H */

class ILVDVCLASS IlvDvMethodMember;
// --------------------------------------------------------------------------
// ExecuteMethodDlg class
// --------------------------------------------------------------------------

class ExecuteMethodDlg
: public IlvDvDialog
{
    IlvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ExecuteMethodDlg(IlvDisplay* display,
		     IlvDvInterface* interf,
		     IlvDvMethodMember* method);

    // ----------------------------------------------------------------------
    void execute();

protected:
    IlvDvInterface*    _interf;
    IlvDvMethodMember* _method;

public:
    static void ExecuteCB(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
IL_MODULEINIT(execdlg, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !Execdlg__header__ */
