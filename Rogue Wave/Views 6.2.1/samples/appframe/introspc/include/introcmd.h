// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/include/introcmd.h
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
// Declaration of the ChangeFieldValueCommand class
// --------------------------------------------------------------------------
#if !defined(Introcmd__header__)
#define Introcmd__header__

#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif /* !__Ilv_Appframe_Command_H */

#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif /* !__Ilv_Appframe_Interf_H */

class IntroDocument;
// --------------------------------------------------------------------------
// ChangeFieldValueCommand class
// --------------------------------------------------------------------------

class ChangeFieldValueCommand
: public IlvDvCommand
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    ChangeFieldValueCommand(IntroDocument* document,
			    const IlvSymbol* fieldName,
			    const IlvDvValue& value);
    ChangeFieldValueCommand(const ChangeFieldValueCommand&);
    virtual ~ChangeFieldValueCommand();
    virtual IlvDvCommand* copy() const;

    // ----------------------------------------------------------------------
    // Overridables
    virtual void doIt();
    virtual void undo();

    // ----------------------------------------------------------------------
    void setValue(const IlvDvValue& value);

protected:
    IntroDocument*   _document;
    IlvDvValue       _value;
    IlvDvValue       _origValue;
    const IlvSymbol* _name;
};

// --------------------------------------------------------------------------
IL_MODULEINIT(introcmd, IL_EMPTYMACRO);
// --------------------------------------------------------------------------
#endif /* !Introcmd__header__ */
