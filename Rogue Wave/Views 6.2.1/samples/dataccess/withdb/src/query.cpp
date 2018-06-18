// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/src/query.cpp
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
// Add a condition to a query
// --------------------------------------------------------------------------
#include <query.h>

#ifdef IL_STD
#include <cstring>
#else
#include <string.h>
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
static void ILVCALLBACK
_bnClickedSelect(IlvGraphic* g, IlvAny) {
  Query* o = (Query*)IlvContainer::getContainer(g);
  o->bnClickedSelect(g);
}

// --------------------------------------------------------------------------
// Panel class for sample Query
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructeur
// --------------------------------------------------------------------------
Query::Query(IlvAbstractView* view, const char* filename) 
  : PageNoteBook(view, filename) {
    initQuery();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Query::initQuery() {
  registerCallback("bnClickedSelect", _bnClickedSelect);
}

// --------------------------------------------------------------------------
// Called when the Select button is clicked
// --------------------------------------------------------------------------
void
Query::bnClickedSelect(IlvGraphic*) {
  const char *emp = getEDTEmployee()->getLabel();
  const char *dep = getEDTDept()->getLabel();
  const char *man = getEDTManager()->getLabel();

  char cond[256];
 
  strcpy(cond, "");
  if (strlen(emp) > 0) {
    strcat(cond, "(I_EMP.NAME LIKE '");
    strcat(cond, emp);
    strcat(cond, "%')");
    if ((strlen(dep) > 0) || (strlen(man) > 0))
      strcat(cond, " AND ");
  }
  if (strlen(dep) > 0) {
    strcat(cond, "(I_DEPT.NAME LIKE '");
    strcat(cond, dep);
    strcat(cond, "%')");
    if (strlen(man) > 0)
      strcat(cond, " AND ");
  }
  if (strlen(man) > 0) {
    strcat(cond, "(I_DEPT.MANAGER LIKE '");
    strcat(cond, man);
    strcat(cond, "%')");
  }
  IliSQLTable *table = getEMP_DS()->getSQLTable();
  if (table != NULL) {
    if (strlen(cond) > 0)
      table->setQueryConjunct(cond);
    else
      table->setQueryConjunct("");
    table->select();
  }
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageQuery(Pan* mainPanel) {
  Query* panel = new Query(mainPanel,"query.ilv");
  mainPanel->addPageNoteBook(panel, "Query", "query.txt");
}
