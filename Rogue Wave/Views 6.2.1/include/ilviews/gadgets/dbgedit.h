// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/dbgedit.h
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
// Declaration of the IlvDebuggerEditor class
// Defined in library ilvadvgdt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Dbgedit_H
#define __Ilv_Gadgets_Dbgedit_H

#include <ilviews/gadgets/codeedit.h>
#include <set>

const IlvDim IlvDefaultDebuggerMargin = 15;

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvDebuggerEditor : public IlvCodeEditor
{
public:
    // Documented public API
    IlvDebuggerEditor(IlvDisplay*	display,
		      const IlvRect&	rect,
		      const char*	text,
		      IlUShort		thickness = IlvDefaultGadgetThickness,
		      StyleSheet*	sheet = 0,
		      Binding::Mode	mode = Binding::MSVCMode,
		      IlvDim		marginWidth = IlvDefaultDebuggerMargin,
		      Parser*		parser = 0);
    virtual ~IlvDebuggerEditor();

    // Current statement
    IlBoolean		setCurrentLine(IlInt line);
    void		eraseCurrentLine();
    // Breakpoints management
    IlBoolean		hasBreakPoint(IlInt line) const;
    // Subclasses can get notifications of break request(+).
    virtual IlBoolean	setBreakPoint(IlInt line);
    // Subclasses can get notifications of break request(-).
    virtual void	removeBreakPoint(IlInt line);
    virtual void	removeAllBreakPoints();
    std::set<IlInt>::const_iterator getBreakPointIterator() const;

    // -------------------------------------------------------------
    // Syntax error notification, specific way of setting error line symbol
    // and of colorizing error locations.
    IlBoolean		setErrorLine(IlInt line);
    IlBoolean		setErrorLocation(IlInt beginLine,
					 IlInt beginColumn,
					 IlInt endLine,
					 IlInt endColumn);
    IlBoolean		unsetAllErrorLines();
    const std::set<IlInt>& getErrorLines() const { return *_errorLines; }

 private:
    std::set<IlInt>*		_errorLines;
    mutable std::set<IlInt>*	_breakPointsSet;
    IlInt			_currentLine;
    // Default markers
    IlvCEdtMarker*		_errorMarginSymbol;
    IlvCEdtMarker*		_currentStatementSymbol;
    IlvCEdtMarker*		_breakPointSymbol;
};

#endif /* !__Ilv_Gadgets_Dbgedit_H */
