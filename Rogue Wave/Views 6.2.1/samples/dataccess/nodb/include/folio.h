// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/include/folio.h
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
// How to create a custom IliTable object
// --------------------------------------------------------------------------
#ifndef __Sample_Folio__H__
#define __Sample_Folio__H__

#include <ilviews/dataccess/gadgets/dbfield.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/dataccess/gadgets/dbnavig.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/filesel.h>
#include <ilviews/gadgets/gadcont.h>

#include <app.h>
#include <foliotbl.h> 

enum RowParity {
  EvenRow,
  OddRow,
  RowParityCount
};

enum PaletteUsage {
  FillPalette,
  TextPosPalette,
  TextNegPalette,
  PaletteUsageCount
};


// --------------------------------------------------------------------------
// Panel class for sample Folio
// --------------------------------------------------------------------------
class Folio
  : public PageNoteBook 
{
public:
  Folio(IlvAbstractView* view,const char* filename);
  ~Folio();

  virtual void bnClickedLoad();
  virtual void bnClickedSave();

  IliTableGadget* getGadgetPortFolio() const
  { return (IliTableGadget*)getObject("GadgetPortFolio"); }

  inline IlvPalette* getPalette (PaletteUsage usage, RowParity parity);
protected:
  void initFolio();
  void definePalette(PaletteUsage, RowParity, const char*);
  
  FolioTable*        _folioTable;
  IlvPalette*       _allPalettes [PaletteUsageCount] [RowParityCount];
  IliDataSource*  _pDataSource;
  IlvIFileSelector* _pFileSave;
  IlvIFileSelector* _pFileLoad;
};

inline IlvPalette*
Folio::getPalette (PaletteUsage usage, RowParity parity) {
  return _allPalettes[usage][parity];
}

#endif /* !__Sample_Folio__H__*/

