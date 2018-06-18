// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/introspc/src/introcmd.cpp
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
// IlogViews 4 generated source file
// File generated Thu Aug 26 16:39:40 1999
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <introcmd.h>
#include <IntroDocument.h>
#include <ilviews/appframe/command.h>
#include <ilviews/appframe/interf.h>

// --------------------------------------------------------------------------
// ChangeFieldValueCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
ChangeFieldValueCommand::ChangeFieldValueCommand(
						 IntroDocument* document,
						 const IlvSymbol* fieldName,
						 const IlvDvValue& value)
: IlvDvCommand(),
  _document(document),
  _value(value),
  _name(fieldName)
{
    _document->getFieldValue(fieldName, _origValue);
}

// --------------------------------------------------------------------------
ChangeFieldValueCommand::ChangeFieldValueCommand(
				    const ChangeFieldValueCommand& src)
: IlvDvCommand(src),
  _document(src._document),
  _value(src._value),
  _origValue(src._origValue),
  _name(src._name)
{
}

// --------------------------------------------------------------------------
ChangeFieldValueCommand::~ChangeFieldValueCommand()
{
}

// --------------------------------------------------------------------------
IlvDvCommand*
ChangeFieldValueCommand::copy() const
{
    return new ChangeFieldValueCommand(*this);
}

// --------------------------------------------------------------------------
void
ChangeFieldValueCommand::doIt()
{
    setValue(_value);
}

// --------------------------------------------------------------------------
void
ChangeFieldValueCommand::undo()
{
    setValue(_origValue);
}

// --------------------------------------------------------------------------
void
ChangeFieldValueCommand::setValue(const IlvDvValue& value)
{
    _document->setFieldValue(_name, value);
    _document->refreshValues();
}
// --------------------------------------------------------------------------
// Static initializations

IL_BEGINMODULEINITDEF(introcmd)
IL_ENDMODULEINITDEF(introcmd)

#if !defined(ILVBUILDLIBS)
static int introcmd_ini = (IL_MODINIT(introcmd)(), 0);
#endif
