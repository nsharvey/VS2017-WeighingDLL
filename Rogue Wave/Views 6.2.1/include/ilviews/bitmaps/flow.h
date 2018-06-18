// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bitmaps/flow.h
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
// Declaration of bitmap data filter flow 
// --------------------------------------------------------------------------
#ifndef __Ilv_Bitmaps_Flow_H
#define __Ilv_Bitmaps_Flow_H

#if !defined(__Ilv_Bitmaps_Filter_H)
#include <ilviews/bitmaps/filter.h>
#endif
#if !defined(__Il_String_H)
#include <ilog/string.h>
#endif


class IlXmlElement;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvFilterFlow : public IlvBitmapFilter
{
 public:
    IlvFilterFlow();
    IlvFilterFlow(IlXmlElement* element);
    IlvFilterFlow(ILVSTDPREF istream& stream, const IlString& name);
    virtual ~IlvFilterFlow();
    virtual IlvBitmapFilter*	getFilter(const char* name) const;
    virtual IlvBitmapFilter* const*	getFilters(IlUInt& count) const;
    virtual IlUInt	getFiltersCardinal() const;
    virtual IlUInt	getBitmapDatasCardinal() const;
    virtual void	addFilter(IlvBitmapFilter* filter);
    virtual void	addBitmapData(IlvBitmapData* data);
    virtual void	removeFilter(IlvBitmapFilter* filter);
    IlvBitmapData*	apply(IlUInt count = 0, 
			      const IlvBitmapData** datas = 0);
    virtual
    IlvBitmapData*	getBitmapData(const char* name) const;
    virtual void	removeBitmapData(const char* name);
    void		loadFromXml(IlXmlElement* element);
    void		invalidate(IlvBitmapFilter* filter = 0);
    static
    IlvFilterFlow**	Read(ILVSTDPREF istream& stream, IlUInt& count);
    inline
    const IlString&	getDescription() const { return _description; }
    void		setDescription(const IlString& desc);

    IlvDeclareClassInfo();
    DeclareValueAccessors();

    static IlSymbol*	_sourceValue;

 protected:
    IlString		_source;
    IlString		_description;
    IlList*		_filters;
    IlList*		_bitmaps;
    IlvBitmapFilter*	_firstinvalid;
};

ILVDSPMODULETERM(bitmaps_flow);

#endif /* __Ilv_Bitmaps_Flow_H */
