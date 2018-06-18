// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/pspnl.h
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
// Declaration of the IlvStpsPropertiesPanel class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Inspectors_Pspnl_H
#define __IlvSt_Inspectors_Pspnl_H

#if !defined(__IlvSt_Panel_H)
#  include <ivstudio/panel.h>
#endif
#if !defined(__IlvSt_Inspectors_Genbase_H)
#  include <ivstudio/inspectors/genbase.h>
#endif

class  IlvStpsPropertySheet;

class ILVSTUDIOCLASS IlvStpsPropertiesPanel : public IlvStPanelHandler 
{
public:
  IlvStpsPropertiesPanel(IlvStudio* ed);

  virtual void reset();
  virtual void apply(); 
  virtual void show();
  virtual void hide();
  virtual void connect();
  virtual void setUpContainer(IlvGadgetContainer*);

  void addToInspectedObjects(IlvGraphic* g);

  virtual IlBoolean isPanable() const {return IlTrue; }

  void setPropertiesModified(IlBoolean);
  IlvStpsPropertySheet* getPropertySheet() const { return _propSheet; }

  static void MakePropertiesPanel(IlvStudio* ed);

  void displayerChanged();
  void objectValueChanged(IlvValueInterface*);

protected:        
  IlvStpsPropertySheet* _propSheet;
};

#endif /* !__IlvSt_Inspectors_Pspnl_H */
