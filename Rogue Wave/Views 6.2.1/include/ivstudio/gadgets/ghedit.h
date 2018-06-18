// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/gadgets/ghedit.h
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
//  Declaration of Geometry handler editors
// --------------------------------------------------------------------------
#ifndef __IlvSt_Ghedit_H
#define __IlvSt_Ghedit_H

#if      !defined(__Ilv_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if      !defined(__Ilv_Graphics_Holder_H)
#include <ilviews/graphics/holder.h>
#endif

#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif

class IlvGuideHandler;

class IlvGHGuide;
class IlvStGuideInspector;
class IlvStObjGHInspector;
class IlvStudio;

// --------------------------------------------------------------------------
class ILVSTGADGETCLASS IlvStGHEdit
{
public:
    IlvStGHEdit(IlvStudio* editor, IlvGadgetHolder* holder);
    virtual ~IlvStGHEdit();

    inline IlvStudio*	getEditor() const { return _editor; }
    void 		reset(IlvGadgetHolder*);
    inline
    IlvGadgetHolder* 	getHolder() const { return _holder;}
    inline void 	setHolder(IlvGadgetHolder* holder) { _holder = holder;}
    inline
    IlvGuideHandler* 	getGuideHandler(IlvDirection dir) const
			{
			    return getHolder()->getGuideHandler(dir);
			}
    IlUInt		findGuide(const IlvPoint&,
				  IlvDirection,
				  IlBoolean& onGuideLine);
    IlBoolean		findGuide(const IlvPoint& where,
				  IlvDirection& dir,
				  IlUInt& ndx,
				  IlBoolean& onGuideLine);
    IlUInt		findGuideLine(const IlvPoint&, IlvDirection);
    inline IlUShort	getTolerance() const { return _tolerance; }
    inline void		setTolerance(IlUShort val) { _tolerance = val; }
    void		draw(const IlvRegion* = 0);
    void		drawGuideLine(IlvDirection,
				      IlUInt ndx,
				      const IlvPalette*);
    void		drawWeights(IlvDirection, const IlvRegion* = 0);
    void		weightBBox(IlvDirection, IlUInt, IlvRect&);
    void		drawWeight(IlvDirection, IlUInt,
				   const IlvPalette*,
				   const IlvRegion* = 0);
    void		drawAttachment(const IlvGraphic*, const IlvPalette*);
    void		drawAttachment(const IlvGraphic*,
				       const IlvPalette*,
				       IlvDirection);
    IlBoolean		attachmentBBox(IlvRect&,
				       const IlvGraphic*,
				       IlvDirection) const;
    IlvPosition		getAttachmentPart(const IlvGraphic*,
					  const IlvPoint&) const;
    IlvPalette*		getPalette();
    void		setPalette(IlvPalette* palette);
    IlvPalette*		getSelectionPalette();
    void 		setSelectionPalette(IlvPalette*);
    inline IlUInt	getSelectionIndex() const { return _guideNdx; }
    inline void		setSelectionIndex(IlUInt val) { _guideNdx = val; }
    inline
    IlvDirection	getSelectionDirection() const { return _guideDir; }
    inline void		setSelectionDirection(IlvDirection dir)
			{
			    _guideDir = dir;
			}
    void		select(IlvDirection,
			       IlUInt ndx,
			       IlBoolean redraw = IlTrue);
    inline IlBoolean	isVisible() const { return _visible; }
    inline void		setVisible(IlBoolean val) { _visible = val; }
    inline IlBoolean	isWeightVisible() const { return _weightVisible; }
    inline void		setWeightVisible(IlBoolean val)
			{
			    _weightVisible = val;
			}
    inline IlvDisplay*	getDisplay() const
			{
			    return getHolder()->getDisplay();
			}
    IlvStGuideInspector* queryGuideInspector();
    inline
    IlvStGuideInspector* getGuideInspector() const { return _guideInsp; }
    IlBoolean		moveGuide(IlvDirection, IlUInt ndx, IlvPos);
    IlBoolean		resizeGuide(IlvDirection, IlUInt ndx, IlInt size);
    IlvStObjGHInspector* queryObjGHInspector();
    inline
    IlvStObjGHInspector* getObjGHInspector() const { return _objGHInsp; }
    void		inspect(IlvGHGuide*);
    void		updateInspector(IlvGHGuide*);
    void		inspect(IlvGraphic*);
    void		updateInspector(IlvGraphic*);
    void		hideInspectors();

protected:
    IlvStudio*		_editor;
    IlvGadgetHolder*    _holder;
    IlvPalette*		_palette;
    IlvPalette*		_selpalette;
    IlUShort		_tolerance;
    IlUInt		_guideNdx;
    IlvDirection	_guideDir;
    IlvStGuideInspector* _guideInsp;
    IlvStObjGHInspector* _objGHInsp;
    IlBoolean		_visible	ILVSTBF;
    IlBoolean		_weightVisible	ILVSTBF;
}; // class IlvStGHEdit

// --------------------------------------------------------------------------
#endif /* __IlvSt_Ghedit_H */
