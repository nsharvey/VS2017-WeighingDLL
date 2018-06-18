// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/grapher/nodesel.h
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
// Declaration of the IlvGraphNodeSelection class
// --------------------------------------------------------------------------
#ifndef __Ilv_Grapher_Nodesel_H
#define __Ilv_Grapher_Nodesel_H

#if !defined(__Ilv_Graphics_Select_H)
#include <ilviews/graphics/select.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Base_Inter_H)
#include <ilviews/base/inter.h>
#endif
#if !defined(__Ilv_Grapher_Macros_H)
#include <ilviews/grapher/macros.h>
#endif
#if !defined(__Ilv_Grapher_Pin_H)
#include <ilviews/grapher/pin.h>
#endif

class IlvGraphic;
class IlvGrapherPin;
class IlvGenericPin;

// --------------------------------------------------------------------------
class ILVGRAPHEXPORTED IlvGraphNodeSelection
: public IlvDrawSelection {
public:
    IL_MLK_DECL();
    IlvGraphNodeSelection(IlvDisplay* display,
			  IlvGraphic* object,
			  IlvDim      size    = 0,
			  IlvPalette* palette = 0);

    virtual void drawHandle(IlvPort* dst, 
			    IlUInt idx,
			    const IlvRect& rect,
			    const IlvRegion* clip = 0) const;

    virtual void draw(IlvPort* dst, const IlvTransformer* t,
		      const IlvRegion* clip = 0) const;
    virtual void computeRegion(IlvRegion& r,
			       const IlvTransformer* t = 0) const;
    virtual void boundingBox(IlvRect& r, const IlvTransformer* t = 0) const;

    virtual IlUInt getHandlesCount(const IlvTransformer* t=0) const;
    virtual IlBoolean getHandleLocation(IlUInt idx, 
					 IlvPoint& p,
					 const IlvTransformer* t) const;
    virtual IlUInt whichHandle(const IlvPoint& p,
			       const IlvTransformer* t = 0) const;

    inline IlvGrapherPin* getPin() const
	{ return IlvGrapherPin::Get(getObject()); }

    inline IlvGenericPin* getGenericPin() const
	{ 
	    IlvGrapherPin* pin = getPin();
	    return (pin && pin->isSubtypeOf(IlvGenericPin::ClassInfo())) 
		? ILVCAST(IlvGenericPin*,pin)
		: 0;
	}

    inline void setActivePinIdx(IlUInt idx) { _activePinIdx=idx; }

    inline IlUInt getActivePinIdx() const { return _activePinIdx; }

    inline void drawFrame(IlBoolean b) { _drawFrame = b; }
    inline IlBoolean isDrawingFrame() const { return _drawFrame; }

    static void SetBorderPalette(IlvPalette* palette);
    static IlvPalette* GetBorderPalette(IlvDisplay* dpy);

    DeclareLazyTypeInfoRO();
    DeclareIOConstructors(IlvGraphNodeSelection);
protected:
    IlUInt _activePinIdx;
    IlBoolean _drawFrame;
    static IlAList* _borderPalettes;
};

ILVGRAPHMODULEINIT(gnodesel);
#endif /* !__Ilv_Grapher_nodesel_H */
