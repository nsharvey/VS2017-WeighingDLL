// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/nodb/src/usercall.cpp
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
// Define global User Callback in IlvGadgetContainer and load/save a table
// --------------------------------------------------------------------------
#include <usercall.h>

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

#include <ilviews/dataccess/gcallbak.h>

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// This function saves data from a memory table
// --------------------------------------------------------------------------
void
saveDataFromMemoryTable(ofstream &file, IliMemoryTable *table) {
  file << table->getRowsCount();
  file << ' ';
  file << table->getColumnsCount();
  file << '\n';

  for (IlvInt i = 0; i < table->getRowsCount(); i++) {
    for (IlvInt j = 0; j < table->getColumnsCount(); j++) {
      IlvWriteString(file, table->at(i, j).getFormatted());
      if (j < (table->getColumnsCount() - 1))
	file << ' ';
      else
	file << '\n';
    }
  }
}

// --------------------------------------------------------------------------
// This callback saves data from a data source memory
// --------------------------------------------------------------------------
void ILVCALLBACK
SaveGlobalCallBack(IlvGraphic *g,IlvAny,IlvInt paramsCount,
		   const char* const* params) {
  char sName[256];

  UserCall* cont = (UserCall*)IlvContainer::getContainer(g);

  IlvGraphic *gr;
  
  if (paramsCount != 1) {
    IlvPrint("Error : bad number params %d", paramsCount);
    return;
  }
 
  strcpy(sName, params[0]);
  if ((gr = cont->getObject(sName)) == NULL) {
    IlvPrint("Error : Object not found");
    return;
  }
  if (gr->isSubtypeOf("IliMemoryDataSource") == IlvFalse) {
    IlvPrint("Error : Bad type");
    return;
  }
  
  //---- Defines the file name to save ----
  cont->getFileDialog(DlgSave)->reset();
  const char* filename = cont->getFileDialog(DlgSave)->get();
  if (filename) {
    ofstream stream(filename);
    if (!stream) {
      IlvFatalError("Couldn't open %s for writing", filename);
      return;
    }
    
    //---- Save data ----
    IliMemoryTable *table = ((IliMemoryDataSource*)gr)->getMemoryTable();
    saveDataFromMemoryTable(stream, table);
  }
}

// --------------------------------------------------------------------------
// This function loads data from a file
// --------------------------------------------------------------------------
void
loadDataFromMemoryTable(ifstream &file, IliMemoryTable *table) {
  IlvInt nbRows;
  IlvInt nbColumns;

  file >> nbRows;
  file >> nbColumns;

  if (nbColumns != table->getColumnsCount()) return;

  table->clearRows();

  //---- load data for the table ----
  IliTableBuffer *buff = table->getBuffer();
  for (IlvInt i = 0; i < nbRows; i++) {
    for (IlvInt j = 0; j < nbColumns; j++) {
      const char *str = IlvReadString(file);
      buff->at(j) = str;
    }
    table->appendRow(buff);
  }
  table->releaseBuffer(buff);
}

// --------------------------------------------------------------------------
// This callback loads data from a data source memory
// --------------------------------------------------------------------------
void ILVCALLBACK
LoadGlobalCallBack(IlvGraphic *g,IlvAny,IlvInt paramsCount,
		   const char* const* params) {
  char sName[256];

  UserCall* cont = (UserCall*)IlvContainer::getContainer(g);

  IlvGraphic *gr;
  
  if (paramsCount != 1) {
    IlvPrint("Error : bad number params %d", paramsCount);
    return;
  }
 
  strcpy(sName,params[0]);
  if ((gr = cont->getObject(sName)) == NULL) {
    IlvPrint("Error : Object not found");
    return;
  }
  if (gr->isSubtypeOf("IliMemoryDataSource") == IlvFalse) {
    IlvPrint("Error : Bad type");
    return;
  }
  
  //---- Selects the file name ----
  cont->getFileDialog(DlgLoad)->reset();
  const char* filename = cont->getFileDialog(DlgLoad)->get();
  if (filename) {
    ifstream stream(filename);
    if (!stream) {
      IlvFatalError("Couldn't open %s for writing", filename);
      return;
    }
      
    //---- Load data ----
    IliMemoryTable *table = ((IliMemoryDataSource*)gr)->getMemoryTable();
    loadDataFromMemoryTable(stream, table);
  }
}

// --------------------------------------------------------------------------
// Panel class for sample UserCall
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
UserCall::UserCall(IlvAbstractView* view, const char* filename)
  : PageNoteBook(view, filename) {
    initUserCall();
}

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
UserCall::~UserCall()
{
  for(IlvInt i = 0; i < NbDialog; i++)
    if(_pFileDialog[i] == NULL)
      delete _pFileDialog[i];
}

// --------------------------------------------------------------------------
// Sets the global callbacks
// --------------------------------------------------------------------------
void
UserCall::initUserCall() {
  IliCallbackManager& manager = IliGetCallbackManager();
  
  manager.registerCallback(IlvGetSymbol("Save"), SaveGlobalCallBack);
  manager.registerCallback(IlvGetSymbol("Load"), LoadGlobalCallBack);

  //---- create dialog for load and save tables ----
  IlPathName dataPath(getDisplay()->getHomePath());
  dataPath.addDirectory("samples/dataccess/nodb/data");
  for(IlvInt i = 0; i < NbDialog; i++)
    _pFileDialog[i] = new IlvIFileSelector(getDisplay(), dataPath, "*.mem");
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageUserCall(Pan* mainPanel) {
  UserCall* panel = new UserCall(mainPanel,"usercall.ilv");
  mainPanel->addPageNoteBook(panel, "UserCall", "usercall.txt");
}

