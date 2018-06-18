// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/dbgrpnl.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliDbGrapherPanel class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Dbgrpnl_H
#define __Ili_Dbgrpnl_H

#ifndef __Ili_Dbgraphe_H
#  include <ilviews/dataccess/gadgets/dbgraphe.h>
#endif

#ifndef __Ili_Inspbook_H
#  include <ilviews/dataccess/inspect/inspbook.h>
#endif

enum IliDbGrapherPage {
  IliDbGrapherNodePage = 0,
  IliDbGrapherLinkPage,
  IliDbGrapherPropPage,
  IliDbGrapherEvenPage,
  IliDbGrapherPageCount
};

class IliDbGrapher;

// --------------------------------------------------------------------------
// IliDbGrapherPanel
// --------------------------------------------------------------------------
class ILV_DBSGRAPH_EXPORTED IliDbGrapherPanel
  : public IliInspectorProperties {
public:
  IliDbGrapherPanel(IlvDisplay* display, IlvSystemView transientFor = 0);
  ~IliDbGrapherPanel();

  //---- Defines pages ----
  virtual void pagesDefine();

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  //---- Pages ----
  virtual void pageCustomGeneralPage(IlInt);

  //---- Events ----
  void dataSourceHasChanged(IliInspectorGadget*,IlBoolean node);
protected:
  void initBookNode(IliDbGadgetPanel*);
  void initBookLink(IliDbGadgetPanel*);
  void initBookProp(IliDbGadgetPanel*);
  void initBookEven(IliDbGadgetPanel*);

  void initFromBookNode(IliDbGadgetPanel*,IliDbGrapher*);
  void initFromBookLink(IliDbGadgetPanel*,IliDbGrapher*);
  void initFromBookProp(IliDbGadgetPanel*,IliDbGrapher*);
  void initFromBookEven(IliDbGadgetPanel*,IliDbGrapher*);

  IlBoolean validateBookNode(IliDbGadgetPanel*);
  IlBoolean validateBookLink(IliDbGadgetPanel*);
  IlBoolean validateBookProp(IliDbGadgetPanel*);
  IlBoolean validateBookEven(IliDbGadgetPanel*);
private:
  //---- Data source ----
  IliString _nodeDsName;
  IliString _linkDsName;
  IliString _columns[IliGrapherColumnNbTag];

  //---- Look
  IliColorComboBox* _colorCombo[IliGrapherColorNbTag];
  IliDialogComboBox* _fileCombo[2];

  IliString _colors[IliGrapherColorNbTag];
  IliString _backgroundPicture;
  IliString _defaultNodeBitmap;
  IlBoolean _displayName;
  IlInt _defaultLinkType;
  IlBoolean _defaultLinkOriented;

  //---- Event ----
  IlBoolean _propagateDelete;
  IlBoolean _propagateRename;
  IlBoolean _outOfOrder;
  IlBoolean _readOnly;
};

#endif
