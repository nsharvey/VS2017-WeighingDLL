// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/states/ivsread.h
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
// Declaration of ivs reader
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_States_Ivsread_H
#define __Ilv_States_Ivsread_H

#if !defined(__Ilv_States_Macros_H)
#  include <ilviews/states/macros.h>
#endif
#if !defined(__Ilv_States_Gendefs_H)
#  include <ilviews/states/gendefs.h>
#endif
#if !defined(__Ilv_States_Mstate_H)
#  include <ilviews/states/mstate.h>
#endif

// --------------------------------------------------------------------------
class ILVSTATESEXPORTED IlvStateParser
{
    // parse related definitions
    char* buffer;	    // a pointer to dynamic array where file is copied
    IlInt	 size;	    // the size of the buffer above
    char* current; 	    // a pointer to current location in buffer
    IlInt	 lineCount; // the line counter for errors
    char* currentLine;	    // a pointer to the beginning of current line
    char* nameBuffer;	    // a buffer for reading names
    char* fileName;
    // state model related definitions
    IlvSdManager* theStateManager;
    IlvSdManager* theMostRecentManager;
    IlvSdState*	  theState;
    IlBoolean	  isInitial;
    char*	  stateName;
    char*	  parentName;
    char*	  subsetName;
    char*	  panelName;
    char*	  objectName;
    char*	  reqName;
    char*	  reqValue;
    IlInt	  errorCode;
    char*	  errorBuffer;  // a buffer for storing error text
    IlvDisplay*	  _display;

public: // accessors
    IlInt	  getErrorCode() { return errorCode; }
    const char*	  getErrorBuffer() { return errorBuffer; }
    IlvSdManager* getTheStateManager() { return theStateManager; }
    IlvDisplay*	  getDisplay() const { return _display; }
public: // constructors
    IlvStateParser(IlvDisplay*,
		   const char*,
		   IlInt = 80,
		   IlInt = 500);
    virtual ~IlvStateParser();
public: // interface
    IlvSdManager* parseFile();
private: // features
    IlBoolean	  isWhiteOrLine();
    IlBoolean	  isWhiteOrLineOrSeparator();
    void	  skipWhites();
    void	  skipWhitesAndLines();
    void	  readIdent();
    void	  readSimpleIdent();
    char*	  readAndCopyIdent();
    IlBoolean	  reservedWord();
    IlBoolean	  readToken(const char*);
    IlBoolean	  readRequirement();
    IlBoolean	  readProcedure();
    IlBoolean	  readPanel();
    IlBoolean	  readObject();
    IlBoolean	  readOptions();
    IlBoolean	  readState();
    IlInt	  getFileSize();

    void	  readStateName();
    void	  readParentName();
    void	  readSubsetName();
    void	  readReqValue();
    void	  readReqName();
    void	  readPanelName();
    void	  readObjectName();
};
#endif /* !__Ilv_States_Ivsread_H */
