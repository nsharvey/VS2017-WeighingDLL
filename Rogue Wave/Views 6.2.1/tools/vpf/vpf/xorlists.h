// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/vpf/xorlists.h
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
// Declaration of the XorLists class
// --------------------------------------------------------------------------
#ifndef _XORLISTS_H
#define _XORLISTS_H_H

#include <ilviews/gadgets/slist.h>

// --------------------------------------------------------------------------
class XorLists {
public:
    XorLists(long nMaxLabels);
    ~XorLists();
    // ____________________________________________________________
    void		setGadgets(IlvStringList* from,
				   IlvStringList* to,
				   IlvGadget*     fromToTo = 0,
				   IlvGadget*     toToFrom = 0);
    void		addLabel(const char* label, IlAny data, int fromOrTo);
    inline long		getCardinal() const { return _nLabels; }
    inline const char*	getLabel(long idx) const { return _labels[idx]; }
    inline IlvStringList*	getFromList() const { return _fromList; }
    inline IlvStringList*	getToList() const { return _toList;   }
    inline IlvGadget*	getFromToToGadget() const { return _fromToToGadget; }
    inline IlvGadget*	getToToFromGadget() const { return _toToFromGadget; }
    inline void		moveInTo(IlBoolean lastOnly)
			{
			    moveItems(lastOnly,
				      _nInFrom,
				      _inFrom,
				      _fromList,
				      _nInTo,
				      _inTo,
				      _toList);
			}
    inline void		moveInFrom(IlBoolean lastOnly)
			{
			    moveItems(lastOnly,
				      _nInTo,
				      _inTo,
				      _toList,
				      _nInFrom,
				      _inFrom,
				      _fromList);
			}
    void		selectAll(int fromOrTo);
    inline IlUShort	getSelectionInFrom(const char*** strings = 0,
					   IlAny**       data = 0)
			{
			    return getSelection(_nInFrom,
						_inFrom,
						strings,
						data);
			}
    inline IlUShort	getSelectionInTo(const char*** strings = 0,
					 IlAny**       data = 0)
			{
			    return getSelection(_nInTo, _inTo, strings, data);
			}
    void		rebuildLists(IlBoolean redraw = IlTrue);

private:
    IlUShort		getSelection(IlUShort      n,
				     IlUShort*     idxs,
				     const char*** strings,
				     IlAny**       data);
    void		moveItems(IlBoolean      lastOnly,
				  IlUShort&      nInFrom,
				  IlUShort*      inFrom,
				  IlvStringList* fromList,
				  IlUShort&      nInTo,
				  IlUShort*      inTo,
				  IlvStringList* toList);
    void		selectAll(IlUShort& nSrc,
				  IlUShort& nDest,
				  IlUShort* dest);
    IlUShort		_nLabels;
    IlUShort		_nMaxLabels;
    char**		_labels;
    IlAny*		_data;
    IlUShort		_nInFrom;
    IlUShort*		_inFrom;
    IlUShort		_nInTo;
    IlUShort*		_inTo;
    IlvStringList*	_fromList;
    IlvStringList*	_toList;
    IlvGadget*		_fromToToGadget;
    IlvGadget*		_toToFromGadget;
};

#endif /* _XORLISTS_H */
