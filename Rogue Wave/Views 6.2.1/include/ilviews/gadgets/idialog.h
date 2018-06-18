// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/idialog.h
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
// Declaration of the IlvDialog class
// Defined in library ilvgadgt
// --------------------------------------------------------------------------

#ifndef __Ilv_Gadgets_Idialog_H
#define __Ilv_Gadgets_Idialog_H

#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif

// --------------------------------------------------------------------------
class ILVGDTEXPORTED IlvDialog : public IlvGadgetContainer
{
public:

    IlvDialog(IlvDisplay*    display,
	      const char*    name,
	      const char*    title,
	      const IlvRect& rect,
	      IlUInt         properties   = 0,
	      IlvSystemView  transientFor = 0);

    IlvDialog(IlvDisplay*    display,
	      const char*    name,
	      const char*    title,
	      const char*    filename,
	      const IlvRect* rect = 0);

    IlvDialog(IlvDisplay*    display,
	      const char*    name,
	      const char*    title,
	      const char*    filename,
	      IlUInt         properties,
	      const IlvRect* rect         = 0,
	      IlvSystemView  transientFor = 0);

    virtual ~IlvDialog();
    // ____________________________________________________________
    virtual void	handleInput(IlvEvent&);
    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual IlBoolean	handleKeyUp(IlvEvent&);

    // ____________________________________________________________

    virtual void	apply();

    virtual void	cancel();

    virtual void	show();
    virtual void	hide();
    void		fill(const char* fileordata);

    virtual void	wait(IlBoolean grab = IlFalse, IlvCursor* cursor = 0);

    IlBoolean		wasCanceled() const { return _canceled; }

protected:
    IlBoolean		handleEnterKeyDown(IlvEvent&);
    IlBoolean		handleEnterKeyUp(IlvEvent&);
    IlBoolean		handleEscapeKeyDown(IlvEvent&);
    IlBoolean		handleEscapeKeyUp(IlvEvent&);

private:
    IlBoolean		_canceled;
};

#endif /* !__Ilv_Gadgets_Idialog_H */
