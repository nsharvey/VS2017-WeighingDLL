// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/observer.h
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
// Declaration of the IlvManagerObserver class
// Defined in library ilvmgr
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Observer_H
#define __Ilv_Manager_Observer_H

#if !defined(__Ilv_Manager_Macros_H)
#include <ilviews/manager/macros.h>
#endif
#if !defined(__Ilv_Base_Observer_H)
#include <ilviews/base/observer.h>
#endif
#if !defined(__Ilv_Base_Resource_H)
#include <ilviews/base/resource.h>
#endif

// --------------------------------------------------------------------------
class IlvTransformer;
class IlvGraphic;
class IlvManager;
class IlvMgrView;
class IlvManagerViewInteractor;
class IlvRect;

// --------------------------------------------------------------------------
#define IlvMgrMsgUndefined		0

// __ Notification on the manager itself		[ 1 - 15]
#define IlvMgrMsgGeneralMask		0x00000001

#define IlvMgrMsgDelete			1

#define IlvMgrMsgUndo			2
#define IlvMgrMsgGrid			3

// __ Notification on manager view			[16 - 31]
#define IlvMgrMsgViewMask		0x00000002

#define IlvMgrMsgAddView		16

#define IlvMgrMsgRemoveView		17

#define IlvMgrMsgSetInteractor		18

#define IlvMgrMsgSetTransformer		19

// __ Notification on manager layer			[32 - 47]
#define IlvMgrMsgLayerMask		0x00000004

#define IlvMgrMsgAddLayer		32

#define IlvMgrMsgRemoveLayer		33

#define IlvMgrMsgMoveLayer		34

#define IlvMgrMsgSwapLayer		35

#define IlvMgrMsgLayerName		36

#define IlvMgrMsgLayerVisibility	37

#define IlvMgrMsgLayerSelectability	38

#define IlvMgrMsgLayerAlpha	39

#define IlvMgrMsgLayerAntialiasing	40

// __ Notification on manager contents			[48 - 63]
#define IlvMgrMsgContentsMask		0x00000008

#define IlvMgrMsgAddObject		48

#define IlvMgrMsgRemoveObject		49

#define IlvMgrMsgObjectLayer		50

// __ Notification on object geometry			[64 - 79]
#define IlvMgrMsgObjectGeometryMask	0x00000010	

#define IlvMgrMsgObjectGeometry		64

#define IlvMgrMsgAllMask		0xFFFFFFFF

// --------------------------------------------------------------------------
// IlvManagerMessage and subclasses
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerMessage
{
public:
    IlvManagerMessage(IlUInt reason, IlUInt mask, IlAny data = 0)
	: _reason(reason),
	  _mask(mask),
	  _data(data)
    {}

    IlUInt	_reason;
    IlUInt	_mask;
    IlAny	_data;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerViewMessage : public IlvManagerMessage
{
public:
    inline IlvMgrView*	getMgrView() const { return (IlvMgrView*) _data; }

protected:
    IlvManagerViewMessage(IlUInt reason, IlvMgrView* mgrview)
	: IlvManagerMessage(reason, IlvMgrMsgViewMask, mgrview)
    {}
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerAddViewMessage : public IlvManagerViewMessage
{
public:
    IlvManagerAddViewMessage(IlvMgrView* mgrview)
	: IlvManagerViewMessage(IlvMgrMsgAddView, mgrview)
    {}
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerRemoveViewMessage
    : public IlvManagerViewMessage
{
public:
    IlvManagerRemoveViewMessage(IlvMgrView* mgrview)
	: IlvManagerViewMessage(IlvMgrMsgRemoveView, mgrview)
    {}
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerSetInteractorMessage
    : public IlvManagerViewMessage
{
public:
    IlvManagerSetInteractorMessage(IlvMgrView* mgrview,
				   IlvManagerViewInteractor* oldInteractor)
	: IlvManagerViewMessage(IlvMgrMsgSetInteractor, mgrview),
	  _oldInteractor(oldInteractor)
    {}
    IlvManagerViewInteractor*	_oldInteractor;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerSetTransformerMessage
    : public IlvManagerViewMessage
{
public:
    IlvManagerSetTransformerMessage(IlvMgrView* mgrview,
				    IlvTransformer* oldTransformer)
	: IlvManagerViewMessage(IlvMgrMsgSetTransformer, mgrview),
	  _oldTransformer(oldTransformer)
    {}
    IlvTransformer*	_oldTransformer;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayerMessage : public IlvManagerMessage
{
public:
    IlvManagerLayerMessage(IlUInt reason, int layer)
	: IlvManagerMessage(reason,
			    IlvMgrMsgLayerMask,
			    IlCastIntToIlAny(layer))
    {}
    inline int	getLayer() const { return IlCastIlAnyToInt(_data); }
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerMoveLayerMessage
    : public IlvManagerLayerMessage
{
public:
    IlvManagerMoveLayerMessage(int layer, int oldIndex)
	: IlvManagerLayerMessage(IlvMgrMsgMoveLayer, layer),
	  _oldIndex(oldIndex)
    {}
    int		_oldIndex;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerSwapLayerMessage
    : public IlvManagerLayerMessage
{
public:
    IlvManagerSwapLayerMessage(int layer1, int layer2)
	: IlvManagerLayerMessage(IlvMgrMsgSwapLayer, layer1),
	  _layer2(layer2)
    {}
    int		_layer2;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayerVisibilityMessage
    : public IlvManagerLayerMessage
{
public:
     IlvManagerLayerVisibilityMessage(int layer, IlvMgrView* mgrview = 0)
	 : IlvManagerLayerMessage(IlvMgrMsgLayerVisibility, layer),
	   _mgrview(mgrview)
    {}
    IlvMgrView*	_mgrview;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayerNameMessage
    : public IlvManagerLayerMessage
{
public:
    IlvManagerLayerNameMessage(int layer, const char* oldName)
	: IlvManagerLayerMessage(IlvMgrMsgLayerName, layer),
	  _oldName(oldName)
    {}
    const char*	_oldName;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayerAlphaMessage
    : public IlvManagerLayerMessage
{
public:
    IlvManagerLayerAlphaMessage(int layer, IlvIntensity oldAlpha)
	: IlvManagerLayerMessage(IlvMgrMsgLayerAlpha, layer),
	  _oldAlpha(oldAlpha)
    {}
    IlvIntensity	_oldAlpha;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLayerAntialiasingMessage
    : public IlvManagerLayerMessage
{
public:
    IlvManagerLayerAntialiasingMessage(int layer,
				       IlvAntialiasingMode oldAntialiasing)
	: IlvManagerLayerMessage(IlvMgrMsgLayerAntialiasing, layer),
	  _oldAntialiasing(oldAntialiasing)
    {}
    IlvAntialiasingMode _oldAntialiasing;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerObjectMessage : public IlvManagerMessage
{
public:
    IlvManagerObjectMessage(IlUInt reason, IlvGraphic* obj, IlUInt mask)
	: IlvManagerMessage(reason, mask, obj)
    {}
    inline IlvGraphic*	getObject() const { return (IlvGraphic*) _data; }
};

class ILVMGREXPORTED IlvManagerContentsMessage
    : public IlvManagerObjectMessage
{
public:
    IlvManagerContentsMessage(IlUInt reason, 
			      IlvGraphic* obj, 
			      int layer = -1,
			      IlUInt mask = IlvMgrMsgContentsMask)
	: IlvManagerObjectMessage(reason, obj, mask),
	  _layer(layer)
    {}
    int			_layer;
};

class ILVMGREXPORTED IlvManagerObjectLayerMessage
    : public IlvManagerContentsMessage
{
public:
    IlvManagerObjectLayerMessage(IlvGraphic* obj,
				 int         newLayer,
				 int         oldLayer = -1)
	: IlvManagerContentsMessage(IlvMgrMsgObjectLayer, obj, newLayer),
	  _oldLayer(oldLayer)
    {}
    int	_oldLayer;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerObjectGeometryMessage
    : public IlvManagerObjectMessage
{
public:
    IlvManagerObjectGeometryMessage(IlvGraphic*	   obj,
				    const IlvRect& oldBBox,
				    IlvRect&	   newBBox,
				    IlUInt mask = IlvMgrMsgObjectGeometryMask)
	: IlvManagerObjectMessage(IlvMgrMsgObjectGeometry, obj, mask), 
	  _newBBox(newBBox),
	  _oldBBox(oldBBox)
    {}
    IlvRect&	    _newBBox;
    const IlvRect&  _oldBBox;
};

// --------------------------------------------------------------------------
// IlvManagerObservable
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerObservable : public IlvObservable
{
public:
    IlvManagerObservable(IlvManager* manager)
	: IlvObservable(),
	  _manager(manager),
	  _disabledMask(0),
	  _observersMask(0)
    {}

    inline IlBoolean	mustNotify(IlUInt mask)
			{
			    return (this &&
				    !(_disabledMask & mask)
				    && (_observersMask & mask));
			}
    virtual void	notify(IlAny arg = 0);

    inline void		notify(IlvManagerMessage& msg)
			{
			    if (mustNotify(msg._mask))
				notify(&msg);
			}
    inline IlvManager*	getManager()           const { return _manager;       }
    inline IlUInt	getDisabledMask()      const { return _disabledMask;  }
    inline void		setDisabledMask(IlUInt mask) { _disabledMask = mask;  }
    inline void		disable(IlUInt mask)         { _disabledMask |= mask; }
    inline void		enable(IlUInt mask)          { _disabledMask &= ~mask;}
    void		subscriptionChanged();

protected:
    IlvManager*		_manager;
    IlUInt		_disabledMask;
    IlUInt		_observersMask;
};

// --------------------------------------------------------------------------
// IlvManagerObserver
// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerObserver : public IlvObserver 
{
    friend class IlvManagerObservable;
public:
    IlvManagerObserver(IlvManager* manager,
		       IlUInt      interestMask = IlvMgrMsgAllMask);

    inline IlUInt	getInterestMask()      const { return _interestMask; }
    void		setInterestMask(IlUInt mask);

    virtual void	attach(IlvObservable* o);
    virtual void	detach(IlvObservable* o);

protected:
    IlUInt		_interestMask;

    void		updateObservable(IlvManagerObservable* =0);
};

#endif /* __Ilv_Manager_Observer_H */
