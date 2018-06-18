// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/mode.h
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
// Declaration of the IlvStMode class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Mode_H
#define __IlvSt_Mode_H

#if !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if      !defined(__IlvSt_Command_H)
#include <ivstudio/command.h>
#endif

class IlvManagerViewInteractor;
class IlvView;
class IlvManager;
class IlvStudio;
class IlvStCommand;

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDVAR(const char*) IlvNmActive;
extern ILVSTEXPORTEDVAR(const char*) IlvNmArc;
extern ILVSTEXPORTEDVAR(const char*) IlvNmArrowLine;
extern ILVSTEXPORTEDVAR(const char*) IlvNmClosedSpline;
extern ILVSTEXPORTEDVAR(const char*) IlvNmFilledArc;
extern ILVSTEXPORTEDVAR(const char*) IlvNmFilledSpline;
extern ILVSTEXPORTEDVAR(const char*) IlvNmGadgetContainerRectangle;
extern ILVSTEXPORTEDVAR(const char*) IlvNmLabel;
extern ILVSTEXPORTEDVAR(const char*) IlvNmLabelList;
extern ILVSTEXPORTEDVAR(const char*) IlvNmLine;
extern ILVSTEXPORTEDVAR(const char*) IlvNmModeChanged;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPolygon;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPolySelection;
extern ILVSTEXPORTEDVAR(const char*) IlvNmPolyline;
extern ILVSTEXPORTEDVAR(const char*) IlvNmReliefLine;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectArcMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectArrowLineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectClosedSplineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectFilledArcMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectFilledSplineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectGadgetContainerRectangleMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectLabelListMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectLabelMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectLineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectPolySelectionMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectPolygonMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectPolylineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectReliefLineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectRotateMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectSCGadgetContainerRectangleMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectSelectionMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectSplineMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectTranslateMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectUnZoomMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectZoomMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSelectActiveMode;
extern ILVSTEXPORTEDVAR(const char*) IlvNmSpline;

class ILVSTUDIOCLASS IlvStMode : public IlvStNamedObject 
{
public:
  IlvStMode(IlvStudio* editor,const char* name,const char* cmdname,
	    IlvManagerViewInteractor* inter,
	    IlBoolean inspectable = IlTrue,IlBoolean editable = IlTrue);

  virtual ~IlvStMode();

  IlvStudio* getEditor() const;

  virtual void selected();

  virtual void unSelected();


  IlvManagerViewInteractor* getInteractor() const;

  void setInteractor(IlvManagerViewInteractor* inter) { _inter = inter; }

  virtual IlBoolean isDefault() const;
  virtual void setOpaqueMoving(IlBoolean);
  virtual void bufferSelected();


  const char* getCommandName() const;

  IlBoolean isEditable() const;

  IlBoolean isInspectable() const;

protected:
  IlvStudio*                  _editor;
  IlvManagerViewInteractor* 	_inter;
  const char*			_command;
  IlBoolean			_inspectable	ILVSTBF;
  IlBoolean			_editable	ILVSTBF;
}; // class IlvStMode

// --------------------------------------------------------------------------
class IlvSelectInteractor;

class ILVSTUDIOCLASS IlvStSelectionMode: public IlvStMode 
{
public:
  IlvStSelectionMode(IlvStudio* ed,
		     const char* name,
		     const char* cmdname,
		     IlvSelectInteractor* inter);
  virtual IlBoolean isDefault() const { return IlTrue; }
  virtual void setOpaqueMoving(IlBoolean val);
}; // class IlvStSelectionMode

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStSetMode : public IlvStCommand 
{
public:
  IlvStSetMode(const char* name);

  virtual ~IlvStSetMode();

  virtual IlvStError* doIt(IlvStudio* editor, IlAny arg);
protected:
  char* _name;
}; // class IlvStSetMode

class ILVSTUDIOCLASS IlvStModes 
{
public:
  IlvStModes(IlvStudio*);
  ~IlvStModes();
  // ____________________________________________________________
  IlvStudio* getEditor() const { return _editor; }

  void add(IlvStMode* mode);

  IlvStMode* getCurrent() const;

  void setCurrent(IlvStMode* mode);

  void setCurrent(const char* name);

  IlvStMode* get(const char* name) const;

  IlvManagerViewInteractor* getInteractor() const
    { return _current ? _current->getInteractor(): 0; }
  void       setDefault(IlvStMode* mode) { _default = mode; }
  IlvStMode* getDefault() const { return _default; }
  void       callDefault();
  void setOpaqueMoving(IlBoolean);
private:
  void	select(IlvStMode*);
  void	unSelect(IlvStMode*);
  IlvStudio*  _editor;
  IlvStHash  	_table;
  IlvStMode* 	_current;
  IlvStMode* 	_default;
};

// --------------------------------------------------------------------------
#include <ilviews/manager/dragrin.h>
class IlvViewRectangle;

class ILVSTUDIOCLASS IlvStMakeXxxRectangle: public IlvDragRectangleInteractor
{
public:
    IlvStMakeXxxRectangle(IlvStudio* editor): _editor(editor) {};
    virtual void doIt(IlvRect&);
    virtual IlvViewRectangle* makeObject(IlvDisplay*, IlvRect&) const = 0;
private:
    IlvStudio* _editor;
};

// --------------------------------------------------------------------------
#ifndef ILVSTNO31COMPAT
extern ILVSTGADGETEXPORTEDVAR (const char*) IlvNmAttachment;
#endif

// --------------------------------------------------------------------------
#endif /* __IlvSt_Mode_H */
