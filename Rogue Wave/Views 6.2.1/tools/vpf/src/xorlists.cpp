// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vpf/src/xorlists.cpp
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
// Definition of the XorLists class
// --------------------------------------------------------------------------

#include <ilviews/graphics/holder.h>
#include <vpf/xorlists.h>

#if defined(VPFSTD)
#include <cstdlib>
#include <cstring>
VPFSTDUSE
#else
#include <stdlib.h>
#include <string.h>
#endif

// --------------------------------------------------------------------------
XorLists::XorLists(long nMaxLabels)
: _nLabels(0),
  _nMaxLabels((IlUShort)nMaxLabels),
  _labels(0),
  _data(0),
  _nInFrom(0),
  _inFrom(0),
  _nInTo(0),
  _inTo(0),
  _fromList(0),
  _toList(0),
  _fromToToGadget(0),
  _toToFromGadget(0)
{
    _labels = new char*    [nMaxLabels];
    _data   = new IlAny    [nMaxLabels];
    _inFrom = new IlUShort [nMaxLabels];
    _inTo   = new IlUShort [nMaxLabels];
    for (long loop = 0; loop < nMaxLabels; loop++) {
	_labels[loop] = 0;
	_inFrom[loop] = 0xFFFF;
	_inTo[loop]   = 0xFFFF;
    }
}

// --------------------------------------------------------------------------
XorLists::~XorLists()
{
    delete [] _inTo;
    delete [] _inFrom;
    delete [] _data;
    for (long loop = 0; loop < _nLabels; loop++)
	delete [] _labels[loop];
    delete [] _labels;
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
MoveItems(IlvGraphic* g,
	  IlAny arg)
{
    XorLists* xorList = (XorLists*)arg;
    if (g->isSubtypeOf(IlvStringList::ClassInfo())) {
	if (g == (IlvGadget*)xorList->getFromList()) xorList->moveInTo(1);
	else                                         xorList->moveInFrom(1);
    } else {
	if (g == xorList->getFromToToGadget()) xorList->moveInTo(0);
	else                                   xorList->moveInFrom(0);
    }
}

// --------------------------------------------------------------------------
static void ILVCALLBACK
SelectInList(IlvGraphic* g,
	     IlAny arg)
{
    XorLists* xorList = (XorLists*)arg;
    IlvStringList* list = (IlvStringList*)g;
    IlvGadget* gadget = (list == xorList->getFromList()) ?
	xorList->getFromToToGadget() : xorList->getToToFromGadget();
    IlBoolean one = (IlBoolean)(list->getFirstSelectedItem() >= 0);
    if (gadget && one != gadget->isSensitive()) {
	gadget->setSensitive(one);
	gadget->reDraw();
    }
}

// --------------------------------------------------------------------------
void
XorLists::setGadgets(IlvStringList* from, IlvStringList* to,
		     IlvGadget* fromToTo, IlvGadget* toToFrom)
{
    if (_fromList) {
	_fromList->removeCallback(IlvGraphic::CallbackSymbol(),  MoveItems);
	_fromList->removeCallback(IlvGraphic::SCallbackSymbol(), SelectInList);
    }
    _fromList = from;
    from->addCallback(IlvGraphic::CallbackSymbol(),   MoveItems, this);
    from->addCallback(IlvGraphic::SCallbackSymbol(),  SelectInList, this);
    if (_toList) {
	_toList->removeCallback(IlvGraphic::CallbackSymbol(),  MoveItems);
	_toList->removeCallback(IlvGraphic::SCallbackSymbol(), SelectInList);
    }
    _toList = to;
    to->addCallback(IlvGraphic::CallbackSymbol(),   MoveItems, this);
    to->addCallback(IlvGraphic::SCallbackSymbol(),  SelectInList, this);
    if (_fromToToGadget)
	_fromToToGadget->removeCallback(IlvGraphic::CallbackSymbol(), MoveItems);
    if ((_fromToToGadget = toToFrom) != 0) {
	_fromToToGadget->setSensitive(IlFalse);
	_fromToToGadget->addCallback(IlvGraphic::CallbackSymbol(),
				     MoveItems, this);
    }
    if (_toToFromGadget)
	_toToFromGadget->removeCallback(IlvGraphic::CallbackSymbol(), MoveItems);
    if ((_toToFromGadget = fromToTo) != 0) {
	_toToFromGadget->setSensitive(IlFalse);
	_toToFromGadget->addCallback(IlvGraphic::CallbackSymbol(),
				     MoveItems, this);
    }
}

// --------------------------------------------------------------------------
void
XorLists::addLabel(const char* label, IlAny data, int fromOrTo)
{
    _labels[_nLabels] = strcpy(new char[strlen(label)+1], label);
    _data[_nLabels]   = data;
    if (fromOrTo)
	_inFrom[_nInFrom++] = _nLabels;
    else
	_inTo[_nInTo++] = _nLabels;
    _nLabels++;
}

// --------------------------------------------------------------------------
#if defined(__SUNPRO_CC_COMPAT) && (__SUNPRO_CC_COMPAT >= 5)
extern "C" { static int SortShorts(const void*, const void*); }
#endif /* Sun C++ 5.0 */
static int
SortShorts(const void* ii, const void* jj)
{
    IlUShort i = *(IlUShort*)ii;
    if (i == 0xFFFF) return  1;
    IlUShort j = *(IlUShort*)jj;
    if (j == 0xFFFF) return -1;
    return (int)i - (int)j;
}

// --------------------------------------------------------------------------
void
XorLists::rebuildLists(IlBoolean redraw)
{
    getFromList()->setLabels(0, 0);
    getToList()->setLabels(0, 0);
    if (_nInFrom)
	qsort((void*)_inFrom, _nLabels, sizeof(IlUShort), SortShorts);
    if (_nInTo)
	qsort((void*)_inTo,   _nLabels, sizeof(IlUShort), SortShorts);
    IlUShort loop;
    for (loop = 0; loop < _nInFrom; loop++)
	_fromList->addLabel(_labels[_inFrom[loop]]);
    for (loop = 0; loop < _nInTo; loop++)
	_toList->addLabel(_labels[_inTo[loop]]);
    _fromToToGadget->setSensitive(IlFalse);
    _toToFromGadget->setSensitive(IlFalse);
    if (redraw)
	_fromList->getHolder()->reDraw();
}

// --------------------------------------------------------------------------
IlUShort
XorLists::getSelection(IlUShort n,
		       IlUShort* idxs,
		       const char*** strings,
		       IlAny** data)
{
    if (strings) {
	*strings = new const char*[n];
	for (IlUShort loop = 0; loop < n; loop++)
	    (*strings)[loop] = _labels[idxs[loop]];
    }
    if (data) {
	*data = new IlAny[n];
	for (IlUShort loop = 0; loop < n; loop++)
	    (*data)[loop] = _data[idxs[loop]];
    }
    return n;
}

// --------------------------------------------------------------------------
void
XorLists::moveItems(IlBoolean lastOnly,
		    IlUShort& nInFrom,
		    IlUShort* inFrom,
		    IlvStringList* fromList,
		    IlUShort& nInTo,
		    IlUShort* inTo,
		    IlvStringList* /* toList */)
{
    if (!nInFrom) return;
    IlUShort loop;
    if (lastOnly) {
	IlShort item = fromList->getFocusItem();
	if (item >= 0) {
	    IlBoolean* selected = new IlBoolean[nInFrom-1];
	    IlUShort count = 0;
	    for (loop = 0; loop < nInFrom; loop++)
		if (loop != (IlUShort)item)
		    selected[count++] = fromList->isSelected(loop);
	    inTo[nInTo++] = inFrom[item];
	    inFrom[item] = 0xFFFF;
	    nInFrom--;
	    rebuildLists();
	    for (loop = 0; loop < nInFrom; loop++)
		if (selected[loop])
		    fromList->setSelected(loop, IlTrue);
	    delete [] selected;
	}
    } else
	if (fromList->getFirstSelectedItem() >= 0) {
	    IlUShort oldnInFrom = nInFrom;
	    for (loop = 0; loop < oldnInFrom; loop++) {
		if (fromList->isSelected(loop)) {
		    inTo[nInTo++] = inFrom[loop];
		    inFrom[loop] = 0xFFFF;
		    nInFrom--;
		}
	    }
	    rebuildLists();
	}
}

// --------------------------------------------------------------------------
void
XorLists::selectAll(int fromOrTo)
{
    if (fromOrTo) selectAll(_nInFrom, _nInTo,   _inTo);
    else          selectAll(_nInTo,   _nInFrom, _inFrom);
}

// --------------------------------------------------------------------------
void
XorLists::selectAll(IlUShort& nSrc,
		    IlUShort& nDest,
		    IlUShort* dest)
{
    for (IlUShort loop = 0; loop < _nLabels; loop++) dest[loop] = loop;
    nDest = _nLabels;
    nSrc  = 0;
    rebuildLists();
}
