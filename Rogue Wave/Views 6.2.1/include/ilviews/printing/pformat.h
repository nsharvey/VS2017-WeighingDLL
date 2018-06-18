// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/pformat.h
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
// Definition of IlvPaperFormat class.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_PaperFormat_H
#define __Ilv_Printing_PaperFormat_H

#if !defined(__Ilv_Printing_Macros_H)
#include <ilviews/printing/macros.h>
#endif

#if !defined(__Ilv_Base_Geometry_H)
#include <ilviews/base/geometry.h>
#endif

#if !defined(__Il_List_H)
#include <ilog/list.h>
#endif

#if !defined(__Il_String_H)
#include <ilog/string.h>
#endif

// --------------------------------------------------------------------------
class IlvPaperFormat;
IlDefineListOf(IlvPaperFormats, IlvPaperFormat*);

class ILVPRINTINGEXPORTED IlvPaperFormat
{
public:
    inline
    IlvRect const&	getPaperSize() const { return _paperSize; }
    inline IlvDim	getPaperWidth() const { return _paperSize.w(); }
    inline IlvDim	getPaperHeight() const { return _paperSize.h(); }
    inline IlString	getName() const { return _name; }
    static
    IlvPaperFormat&	Register(IlString const& name,
				 IlvDim width,
				 IlvDim height);
    static IlBoolean	UnRegister(IlvPaperFormat* format);
    static
    IlvPaperFormat*	Get(IlString const& name);
    static
    IlvPaperFormat**	GetRegisteredPaperFormats(IlUInt& count);
    static void		LoadFromXML(ILVSTDPREF istream& stream);
    static void		CleanRegisteredPaperFormats();
#if defined(WINDOWS) || DOXYGEN_GENERATION
    inline IlUShort	getDmPaperSize() const { return _dmPaperSize; }
    inline void		setDmPaperSize(IlUShort dmPaperSize)
			{
			    _dmPaperSize = dmPaperSize;
			}
    static
    IlvPaperFormat*	Get(IlUShort dmPaperSize);
#endif /* WINDOWS */

private:
    IlvPaperFormat(IlString const& name, IlvDim width, IlvDim height);

    static IlListOf(IlvPaperFormats)* _PaperFormats;
    IlString		_name;
    IlvRect		_paperSize;
#if defined(WINDOWS)
    IlUShort		_dmPaperSize;
#endif /* WINDOWS */
};

ILVPRINTINGMODULETERM(pformat);

#endif /* __Ilv_Printing_PaperFormat_H */
