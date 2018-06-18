// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/inspectors/sheetedt.h
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
// Declaration of properties edited in sheets
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Inspectors_Sheetedt_H)
#define __IlvSt_Inspectors_Sheetedt_H

#if !defined(__IlvSt_Inspectors_Listedt_H)
#  include <ivstudio/inspectors/listedt.h>
#endif
#if !defined(__IlvSt_Inspectors_Listacc_H)
#  include <ivstudio/inspectors/listacc.h>
#endif

class IlvAbstractMatrixItem;
class IlvSheet;
class IlvMatrix;

#define _PATCH_INSERT_LIST_EDITOR_NOT_VIRTUAL

// --------------------------------------------------------------------------
// IlvStIPropertySheetAccessor class
// --------------------------------------------------------------------------
class ILVINSPCLASS IlvStIPropertySheetAccessor
    : public IlvStIPropertyListAccessor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertySheetAccessor(IlvStIPropertyAccessor* = 0,
			        IlvStIAccessor::UpdateMode =
						   IlvStIAccessor::Inherited,
			        IlvStIAccessor::BuildMode =
							IlvStIAccessor::None,
			        const char* = 0);
    virtual ~IlvStIPropertySheetAccessor();

    // ----------------------------------------------------------------------
    virtual IlvAbstractMatrixItem* createMatrixItem(const IlvStIProperty*,
						    IlUInt, IlUInt) const;
    virtual void matrixItemChanged(IlUInt, IlUInt, IlvAbstractMatrixItem*);
#ifdef _PATCH_INSERT_LIST_EDITOR_NOT_VIRTUAL
    virtual void insertProperty(IlUInt, IlAny);
#endif

protected:
    virtual void propertyFieldChanged(IlvStIProperty*, IlUInt,
				      IlvAbstractMatrixItem*);
};

// --------------------------------------------------------------------------
// class IlvStIPropertySheetEditor
// --------------------------------------------------------------------------
typedef IlvAbstractMatrixItem* (*IlvStIMatrixItemConstructor)
    (const IlvStIProperty*, IlUInt, IlUInt, IlAny);

class ILVINSPCLASS IlvStIPropertySheetEditor
    : public IlvStIPropertyListEditor
{
    IlvDeclareInspClassInfo();
public:
    IlvStIPropertySheetEditor(IlvStIPropertySheetAccessor* = 0,
			      const char* = 0);
    virtual ~IlvStIPropertySheetEditor();

    // ----------------------------------------------------------------------
    void declareSheetGadgets(const char*,
			     const char* = 0,
			     const char* = 0,
			     const char* = 0,
			     const char* = 0,
			     const char* = 0,
			     const char* = 0);
    // ----------------------------------------------------------------------
    // Overridables
    virtual IlBoolean  connectHolder(IlvGraphicHolder*);
    virtual void        empty();

    // ----------------------------------------------------------------------
    // Methods called by list accessor
#ifdef _PATCH_INSERT_LIST_EDITOR_NOT_VIRTUAL
    virtual void insertRow(IlUInt index, const IlvStIProperty*);
#else
    virtual void insert(IlUInt index, const IlvStIProperty*);
#endif

    virtual void remove(IlUInt);
    virtual void moveItem(IlUInt, IlUInt);
    virtual void setItemSelected(IlUInt);

    virtual IlvGadget*  getListGadget() const;
    virtual IlBoolean   isEmpty() const;
    virtual IlvDisplay* getDisplay() const;

    void setMatrixItemConstructor(IlvStIMatrixItemConstructor, IlAny = 0);

protected:

    // Gadgets used to edit list
    IlvSheet*		   _sheetGadget;
    IlString              _sheetName;
    IlvStIMatrixItemConstructor _constructor;
    IlAny                      _constructorParam;

    // gadget list accessors
    virtual void       refreshSelection();
    virtual IlvAbstractMatrixItem* createMatrixItem(const IlvStIProperty*,
						    IlUInt, IlUInt) const;
    void fillRow(IlUInt row, const IlvStIProperty*);
    IlUInt getNumberOfRows() const;
    virtual void fillGadget();

public: // Due to some Unix compilers
    // ----------------------------------------------------------------------
    //Internal callbacks
    virtual void selectedItemCallback();
    virtual void moveUpDownCallback(IlBoolean up);
    static void MatrixItemValidateCallback(IlvMatrix*,
					   IlUShort, IlUShort, IlAny);
    virtual void callbackValueEdited(IlUShort, IlUShort);
};

// --------------------------------------------------------------------------
IlvDECLAREINITINSPCLASS(sti_sheetedt)
#endif /* !__IlvSt_Inspectors_Sheetedt_H */
