// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/inspgad.h
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
// Declaration of the IliInspectorGadget class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Inspgad_h
#define __Ili_Inspgad_h

#ifndef __Ili_Maptable_H
#  include <ilviews/dataccess/maptable.h>
#endif

#ifndef __Ili_Tablegad_H
#  include <ilviews/dataccess/gadgets/tablegad.h>
#endif

class IliInspectorTable;

class ILV_DBS_EXPORTED IliInspectorGadget : public IliTableGadget
{
public:
    IliInspectorGadget(IlvDisplay* display,
		       const IlvRect& rect,
		       IlUShort thickness = IlvDefaultGadgetThickness,
		       IlvPalette* palette = 0);
    ~IliInspectorGadget();

    void		defineProp(IlInt tag,
				   const char* label,
				   const IliDatatype* type);
    void		defineProp(IlInt tag,
				   const char* label,
				   const IliDatatype* type,
				   IliTable* tbl,
				   IlBoolean owner = IlFalse);
    void		defineProp(IlInt tag,
				   const char* label,
				   const IliDatatype* type,
				   const IliMapEntry* tbl,
				   IlBoolean owner = IlFalse);
    void		defineProp(IlInt tag,
				   const char* label,
				   const IliDatatype* type,
				   IliFieldItf* fld,
				   IlBoolean owner = IlFalse);
    void		defineBooleanProp(IlInt tag, const char* label);

    void		renameProp(IlInt tag, const char* name);

    void		undefineProp(IlInt tag);
    void		undefineAllProps();
    IlBoolean		isPropDefined(IlInt tag) const;

    const IliValue&	at(IlInt tag) const;
    IliValue&		at(IlInt tag);

    IlInt		getTagRow(IlInt tag) const;
    IlInt		getRowTag(IlInt rowno) const;

    IlBoolean		isModified() const { return _modified; }
    void		setModified(IlBoolean f) { _modified = f; }

    void		recomputeMarkerWidth();

    IlBoolean		setSelection(const IliTableSelection&);
    virtual void	drawMarker(IlvPort* dst,
				   IlInt rowno,
				   IlBoolean selected,
				   IlBoolean current,
				   const IlvRect& bbox,
				   const IlvRegion* clip) const;
    virtual
    IliFieldItf*	getCustomEditor(IlInt, IlInt, IliFieldItf* fld) const;
    virtual void	setHolder(IlvGadgetHolder* holder);
    virtual void	changeLanguage(const IlvSymbol*);

protected:
    IliInspectorTable*	_inspTable;
    IlBoolean		_modified;

    void		adjustMarkerWidth(const char*);

    virtual void	drawVertRule(IlvPort* dst,
				     IlvPos y1,
				     IlvPos y2,
				     IlvPos x,
				     IlInt colno,
				     IlInt rownoTop,
				     IlInt rownoBot,
				     IlvPalette* palette,
				     const IlvRegion* clip) const;
    virtual void	drawHorzRule(IlvPort* dst,
				     IlvPos x1,
				     IlvPos x2,
				     IlvPos y,
				     IlInt rowno,
				     IlInt colnoLeft,
				     IlInt colnoRight,
				     IlvPalette* palette,
				     const IlvRegion* clip) const;
};

#if defined(_MSC_VER)
#  if !defined(ILI_BUILDLIBS)
#    pragma comment(lib, "dbstudio")
#  endif
#endif

#endif
