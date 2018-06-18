// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/withdb/src/session.cpp
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
// How to use the IliSQLSession and IliSQLCursor classes
// --------------------------------------------------------------------------
#include <session.h>
 
#ifdef IL_STD
#include <cstring>
#include <cstdio>
#else
#include <string.h>
#include <stdio.h>
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
_bnClickedApply(IlvGraphic* g, IlvAny) {
  Session* o = (Session*)IlvContainer::getContainer(g);
  o->bnClickedApply(g);
}

// --------------------------------------------------------------------------
// Panel class for sample Session
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Session::Session(IlvAbstractView* view,const char* filename)
  : PageNoteBook(view, filename) {
    initSession();
}

// --------------------------------------------------------------------------
// Initialize
// --------------------------------------------------------------------------
void
Session::initSession() {
  registerCallback("bnClickedApply", _bnClickedApply);
}

// --------------------------------------------------------------------------
// Function called when the user pushes the Apply button
// --------------------------------------------------------------------------
void
Session::bnClickedApply(IlvGraphic*)
{
  IliSQLCursor  *cursor;
  IliSQLSession *dbSession;
  char            requete[256];
  IlvInt          val;
  const  char     *bonus;
  const  char     *common = "UPDATE I_EMP SET SALARY = SALARY";

  //---- Get and check bonus salary ----
  bonus = getEDTBonus()->getLabel();
  if (strlen(bonus) < 1) {
    getEMP_DS()->getSQLTable()->select();
    return;
  }
  
  //---- connect with the SQL session ----
  dbSession = IliSQLSession::GetRegisteredSession("Main");
  dbSession->lock();
  if (dbSession->isConnected() == IlvFalse) {
    IlvPrint("you are not connected");
    return;
  }
  cursor = dbSession->newCursor();

  //---- build SQL statement ----
  val = atoi(bonus);
  if (bonus[strlen(bonus) - 1] == '%')
    sprintf(requete, "%s + ((SALARY * %d)/100)", common, val);
  else {
    if (val < 0L)
      sprintf(requete,"%s %d", common, val);
    else
      sprintf(requete, "%s + %d", common, val);
  }

  //---- execute SQL statement ----
  cursor->execute(requete);

  //---- display result ----
  getEMP_DS()->getSQLTable()->select();

  //---- disconnect with the SQL session
  dbSession->commit();
  dbSession->releaseCursor(cursor);
  dbSession->unLock();
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageSession(Pan* mainPanel) {
  Session* panel = new Session(mainPanel,"session.ilv");
  mainPanel->addPageNoteBook(panel, "Session", "session.txt");
}


