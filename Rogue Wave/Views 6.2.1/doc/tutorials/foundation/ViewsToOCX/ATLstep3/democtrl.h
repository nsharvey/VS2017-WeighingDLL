// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: doc/tutorials/foundation/ViewsToOCX/ATLstep3/democtrl.h
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
#if !defined(DemoCtrl_H)
#define DemoCtrl_H

#include <atlbase.h>

#if !defined(Ctrl_H)
#  include <ctrl.h>
#endif

// --------------------------------------------------------------------------
class DemoCtrl
    : public Ctrl
{
public:
    DemoCtrl(HWND hWnd);
    virtual ~DemoCtrl();

    void setFileName(CComBSTR&);
    void setBackground(OLE_COLOR);
    static IlvDisplay* getDisplay() throw() { return _Display; }
    static bool InitDisplay(HINSTANCE hInstance) throw();
    static void CleanDisplay();

private:
    DemoCtrl(const DemoCtrl&); // No default copy constructor.
    DemoCtrl();		       // No default constructor.
    static IlvDisplay*	_Display;
};
#endif /* !DemoCtrl_H */
