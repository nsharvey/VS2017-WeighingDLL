// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/manager/managdoc.h
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
// Declaration of the IlvDvManagerDocument class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Manager_Managdoc_H)
#define __Ilv_Appframe_Manager_Managdoc_H

#if !defined(__Ilv_Appframe_Document_H)
#include <ilviews/appframe/document.h>
#endif

#if !defined(__Ilv_Appframe_Manager_Macros_H)
#include <ilviews/appframe/manager/macros.h>
#endif

#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
// --------------------------------------------------------------------------
// IlvDvManagerDocument class
// --------------------------------------------------------------------------
class ILVDVMGREXPORTED IlvDvManagerDocument : public IlvDvDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvManagerDocument();
    virtual ~IlvDvManagerDocument();

    // ----------------------------------------------------------------------
    virtual IlBoolean	initializeDocument(IlAny = 0);

    virtual void	clean();

    // ----------------------------------------------------------------------
    // Basic properties
    inline IlvManager*	getManager() const { return _manager; }

    // ----------------------------------------------------------------------
    // IO
    virtual void	serialize(IlvDvStream& stream);

    // ----------------------------------------------------------------------
    // Query / apply values
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    IlvDvDeclareInterface();

protected:
    IlvManager*		_manager;

    virtual void	setUndoUI(IlvDvActionDescriptor*);
    virtual void	callUndo();
    virtual void	callRedo();

    virtual void	setCutUI(IlvDvActionDescriptor*) const;
    virtual void	setPasteUI(IlvDvActionDescriptor*) const;
    virtual void	deleteSelection();
    virtual void	addAccelerators();
    virtual void	cutToClipboard();
    virtual void	copyToClipboard();
    virtual IlvManager*	createManager(IlvDisplay*);
    virtual void	initializeManager(IlvManager*);
};

// --------------------------------------------------------------------------
ILVDVMGRMODULEINIT(managdoc);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Manager_Managdoc_H */
