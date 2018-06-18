// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/src/folio.cpp
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
// How to create a custom Folio object
// --------------------------------------------------------------------------
#include <folio.h>

#ifdef IL_STD
#include <fstream>
#else
#include <fstream.h>
#endif

#ifdef IL_STD
#  include <strstream>
#else
#ifdef ILVFATFILENAMES
#  include <strstrea.h>
#else
#  include <strstream.h>
#endif
#endif

IL_STDUSE

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Load a file
// --------------------------------------------------------------------------
static void ILVCALLBACK
_bnClickedLoad(IlvGraphic* g, IlvAny) {
  Folio* o = (Folio*)IlvContainer::getContainer(g);
  o->bnClickedLoad();
}

// --------------------------------------------------------------------------
// Save a file
// --------------------------------------------------------------------------
static void ILVCALLBACK
_bnClickedSave(IlvGraphic* g, IlvAny) {
  Folio* o = (Folio*)IlvContainer::getContainer(g);
  o->bnClickedSave();
}

// --------------------------------------------------------------------------
// Computes the parity of a row
// --------------------------------------------------------------------------
RowParity
GetRowParity (IlvInt rowno) {
  return ((rowno % 2) == 0)? EvenRow : OddRow;
}

// --------------------------------------------------------------------------
// This callback computes the colors of the rows
// --------------------------------------------------------------------------
void ILVCALLBACK
MyGetCellPaletteCallBack(IlvGraphic* g, IlvAny any) {
  IliTableGadget* tbl = (IliTableGadget*)g;
  Folio* panel = (Folio*)any;

  IliCellPaletteStruct *cell = tbl->getCellPaletteStruct();
  RowParity parity = GetRowParity(cell->rowno);

  if (!cell->selected) {
    if (panel->getPalette(FillPalette, parity) != NULL)
      cell->fillPalette = panel->getPalette(FillPalette, parity);
    
    IliValue value = tbl->at(cell->rowno, cell->tblColno);
    if (value.asDouble() >= 0.0) {
      if (panel->getPalette(TextPosPalette, parity) != NULL)
	cell->textPalette = panel->getPalette(TextPosPalette, parity);
    }
    else {
      if (panel->getPalette(TextNegPalette, parity) != NULL)
	cell->textPalette = panel->getPalette(TextNegPalette, parity);
    }
  }
}

// --------------------------------------------------------------------------
// Panel class for sample Folio
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Folio::Folio(IlvAbstractView* view,const char* filename)
  :PageNoteBook(view, filename) {
    initFolio();
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
Folio::~Folio()
{
  delete _pFileSave;
  delete _pFileLoad;
  // Unlock palettes
  for (IlvInt usage = 0; usage < PaletteUsageCount; ++usage)
    for (IlvInt parity = 0; parity < RowParityCount; ++parity) {
      IlvPalette* palette = _allPalettes [usage] [parity];
      if (palette != 0)
        palette->unLock();
    }
}

// --------------------------------------------------------------------------
// Connect the table with the GadgetTable
// --------------------------------------------------------------------------
void
Folio::initFolio() {
  registerCallback("bnClickedLoad", _bnClickedLoad);
  registerCallback("bnClickedSave", _bnClickedSave);

  //---- create the table ----
  _folioTable = new FolioTable(getDisplay());
  _pDataSource = new IliDataSource(getDisplay(), IlvPoint(0,0));

  //---- Connect the table ----
  _pDataSource->setTable(_folioTable);
  addObject("FOLIO_TBL", _pDataSource);

  //---- create dialog for load and save tables ----  
  IlPathName dataPath(getDisplay()->getHomePath());
  dataPath.addDirectory("samples/dataccess/nodb/data");
  _pFileSave = new IlvIFileSelector(getDisplay(), dataPath, "*.pfl");
  _pFileLoad = new IlvIFileSelector(getDisplay(), dataPath, "*.pfl");

  //---- set callback for computing the rows colors ----
  getGadgetPortFolio()->setCallback(IliTableGadget::GetCellPaletteSymbol(),
				    MyGetCellPaletteCallBack,this);

  //---- define the palettes needed by the callbacks ----    
  definePalette(FillPalette,    EvenRow,  "white");
  definePalette(FillPalette,    OddRow,   "gray");
  definePalette(TextPosPalette, EvenRow,  "blue");
  definePalette(TextPosPalette, OddRow,   "blue");
  definePalette(TextNegPalette, EvenRow,  "red");
  definePalette(TextNegPalette, OddRow,   "red");
}

// --------------------------------------------------------------------------
// Load a table from a file
// --------------------------------------------------------------------------
void
Folio::bnClickedLoad() {
  _pFileLoad->reset(); // reset file selector dialog
  const char* filename = _pFileLoad->get();
  if (filename && *filename) {
    ifstream stream(filename);
    if (stream) {
      FolioTable *tmp = new FolioTable(getDisplay(), stream);
      _folioTable = tmp;
      _pDataSource->setTable(_folioTable);
      _pDataSource->gotoLast();
    }
    else
      IlvFatalError("Couldn't open %s for reading", filename);
  }
}

// --------------------------------------------------------------------------
// Save the current table in a file
// --------------------------------------------------------------------------
void
Folio::bnClickedSave() {
  _pFileSave->reset();
  const char* filename = _pFileSave->get();
  if (filename && *filename) {
    ofstream stream(filename);
    if (stream) 
      _folioTable->write(stream);
    else
      IlvFatalError("Couldn't open %s for writing", filename);
  }
}


// --------------------------------------------------------------------------
// Define a palette
// --------------------------------------------------------------------------
void
Folio::definePalette (PaletteUsage usage,
		      RowParity parity,
		      const char* colorName)
{
  IlvDisplay* disp = getDisplay();
  IlvPalette* palette = disp->getPalette(disp->getColor("white"),
                                         disp->getColor(colorName));
  if (palette != NULL)
    palette->lock();
  _allPalettes [usage] [parity] = palette;
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageFolio(Pan* mainPanel) {
  Folio* panel = new Folio(mainPanel,"folio.ilv");
  mainPanel->addPageNoteBook(panel, "Folio", "folio.txt");
}


