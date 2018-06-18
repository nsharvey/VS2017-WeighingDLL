// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/edit.h
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
// Declaration of basic Studio commands
// --------------------------------------------------------------------------
#ifndef __IlvSt_Edit_H
#define __IlvSt_Edit_H

#if !defined(__Ilv_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__IlvSt_Command_H)
#include <ivstudio/command.h>
#endif
#include <ilviews/bitmaps/filters/all.h>

extern ILVSTEXPORTEDVAR(const char*) IlvNmAddObject;

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStAddObject
: public IlvStCommand
{
public:
    IlvStAddObject(IlvGraphic* obj, const char* inter = 0)
    : _object(obj),
      _intername(inter) {}
    // ____________________________________________________________
    virtual IlvStError* doIt(IlvStudio*, IlAny);
    virtual IlvStError* unDo(IlvStudio*);
    IlvGraphic* getObject() const { return _object; }
protected:
    IlvGraphic* _object;
    const char* _intername;
    void doAdd(IlvStudio*, IlvGraphic*, const char*);
};

class ILVSTUDIOCLASS IlvStClickAddObject : public IlvStCommand 
{
public:
  virtual IlvStError* doIt(IlvStudio*, IlAny);
protected:
  virtual IlvStError* makeObject(IlvGraphic*& g,IlvStudio* editor, 
				 IlAny arg) = 0;
  void doAdd(IlvStudio*, IlvGraphic*);
};

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStDelete
: public IlvStCommand
{
public:
    IlvStDelete()
    : _objects(0),
      _count(0) {}
    ~IlvStDelete();
    // ____________________________________________________________
    virtual IlvStError* doIt(IlvStudio*, IlAny);
    virtual IlvStError* unDo(IlvStudio*);
private:
    IlvGraphic** _objects;
    IlUInt      _count;
};

// --------------------------------------------------------------------------
void IlvStInitializeEditCommands(IlvStudio*);

// --------------------------------------------------------------------------
#endif /* __Ilv_Edit_H */
