// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/protos/connint.h
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
// Declaration of the group connection interactor.
// --------------------------------------------------------------------------
#ifndef __Ilv_Protos_Connint_H
#define __Ilv_Protos_Connint_H

#if !defined(__Ilv_Protos_Group_H)
#include <ilviews/protos/group.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif

class IlvProtoHolderInterface;

// ---------------------------------------------------------------------------
// IlvGroupConnectInteractor    Interactor for connecting two groups
//				through a value subcription.
// ---------------------------------------------------------------------------
class ILVPROEXPORTED IlvGroupConnectInteractor
    : public IlvManagerViewInteractor {
 public:
    IlvGroupConnectInteractor(IlvManager* manager, IlvView* view)
	: IlvManagerViewInteractor(manager, view),
	  _from(0),
	  _to(0),
	  _first(0, 0),
	  _prev(0, 0),
	  _visible(IlTrue),
	  _lineCount(0),
	  _maxLines(0),
	  _fromPoints(0),
	  _toPoints(0),
	  _fromGroups(0),
	  _toGroups(0),
	  _detailsBBox(),
	  _showSelfConnections(IlFalse),
	  _protoHolder(0) {}

    IlvGroupConnectInteractor()
	: IlvManagerViewInteractor(),
	  _from(0),
	  _to(0),
	  _first(0, 0),
	  _prev(0, 0),
	  _visible(IlTrue),
	  _lineCount(0),
	  _maxLines(0),
	  _fromPoints(0),
	  _toPoints(0),
	  _fromGroups(0),
	  _toGroups(0),
	  _detailsBBox(),
	  _showSelfConnections(IlFalse),
	  _protoHolder(0) {}

    virtual IlBoolean	handleEvent(IlvEvent& event);
    virtual void	handleExpose(IlvRegion* = 0);
    virtual void	init();
    virtual void	abort();
    virtual void	drawGhost();
    virtual void	doIt(IlvAccessible* from, IlvAccessible* to);

    inline
    IlvProtoHolderInterface* getProtoHolder() const { return _protoHolder; }
    inline void		setProtoHolder(IlvProtoHolderInterface* protoHolder)
			{
			    _protoHolder = protoHolder;
			}

    virtual IlBoolean	isConnectable(IlvGraphic* obj);
    virtual void	getConnectableBBox(IlvValueInterface* obj,
					   IlvRect& bbox);
    virtual
    IlvAccessible*	getConnectableObject(IlvValueInterface* obj,
					     IlvProtoHolderInterface* h);

protected:
    IlvValueInterface*	_from;
    IlvValueInterface*	_to;
    IlvPoint		_first;
    IlvPoint		_prev;
    IlBoolean		_visible;
    IlUInt		_lineCount;
    IlUInt		_maxLines;
    IlvPoint*		_fromPoints;
    IlvPoint*		_toPoints;
    IlvAccessible**	_fromGroups;
    IlvAccessible**	_toGroups;
    IlvRect		_detailsBBox;
    IlBoolean		_showSelfConnections;
    IlvProtoHolderInterface* _protoHolder;

    virtual IlSymbol*	getFromValue(IlvAccessible* from,
				     IlUInt count,
				     IlSymbol** sourceValues) = 0;
    virtual IlSymbol*	getToValue(IlvAccessible* to,
				   IlUInt count,
				   IlSymbol** subscrValues) = 0;
    virtual IlSymbol**	getFromToValues(IlvAccessible* from,
					IlvAccessible* to,
					IlUInt countfrom,
					IlUInt countto,
					IlSymbol** sourceValues,
					IlSymbol** subscrValues) = 0;
    virtual IlInt	selectConnection(IlvAccessible* from,
					 IlvAccessible* to,
					 IlUInt count,
					 IlSymbol** sourceValues,
					 IlSymbol** subscrValues) = 0;

    void		cleanLines();
    IlBoolean		showDetails(IlvPoint& p);
    IlBoolean		deleteConnection(IlvPoint& p);
    void		eraseDetails();
    void		drawConnections(IlvRegion* clip);
    void		drawConnections(IlvAccessible* from,
					IlvAccessible* to,
					IlUInt count,
					IlSymbol** sourceValues,
					IlSymbol** subscrValues,
					IlvPalette* palette);
    IlvPalette*		getPalette();
};

#endif /* __Ilv_Protos_Connint_H */
