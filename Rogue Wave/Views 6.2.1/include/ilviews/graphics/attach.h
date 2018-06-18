// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/attach.h
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
// Declaration of the attachement related functions
// Defined in library views
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Attach_H
#define __Ilv_Graphics_Attach_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif

#if !defined(__Ilv_Base_View_H)
#include <ilviews/base/view.h>
#endif

class IlvGraphicHolder;

// --------------------------------------------------------------------------
class ILVVWSEXPORTED IlvAttachmentsHandler : public IlvViewHandler
{
public:
    IlvAttachmentsHandler();
    // ____________________________________________________________
    IlvGraphicHolder*	getGraphicHolder() const;

    virtual void	handleResize(const IlvRect& rect);
    virtual void	applyResize(IlFloat   sx,
				    IlFloat   sy,
				    IlBoolean redraw = IlTrue);
    virtual void	applyResize(IlvGraphic* graphic,
				    IlFloat   sx,
				    IlFloat   sy,
				    IlBoolean redraw = IlTrue);

    static
    IlvAttachmentsHandler* Get(const IlvView* view);

    static
    IlvAttachmentsHandler* Set(IlvView* view, IlvAttachmentsHandler* handler);

    virtual void	setView(IlvView* view);

protected:
    IlvDim		_previousWidth;
    IlvDim		_previousHeight;
};

// --------------------------------------------------------------------------
enum IlvGraphicAttachment {
    IlvNoAttach,
    IlvFixedAttach,
    IlvElasticAttach,
    IlvFixAndElasticAttach
};

ILVVWSEXPORTEDFUNCTION(void)
IlvSetAttachment(IlvGraphic* graphic,
		 IlvPosition position,
		 IlvGraphicAttachment attachment,
		 IlvDim distance = 0);

ILVVWSEXPORTEDFUNCTION(void)
IlvRemoveAttachment(IlvGraphic* graphic, IlvPosition position);

ILVVWSEXPORTEDFUNCTION(IlvGraphicAttachment)
IlvGetAttachment(const IlvGraphic* graphic, IlvPosition position);

ILVVWSEXPORTEDFUNCTION(IlvDim)
IlvGetAttachmentDistance(const IlvGraphic* graphic, IlvPosition position);

ILVVWSEXPORTEDFUNCTION(void)
IlvSaveAttachments(const IlvGraphic*, ILVSTDPREF ostream&);

ILVVWSEXPORTEDFUNCTION(void)
IlvReadAttachments(IlvGraphic*, ILVSTDPREF istream&, IlUInt attachs);

ILVVWSEXPORTEDFUNCTION(void)
IlvReadAttachments(IlvGraphic*, ILVSTDPREF istream&);

ILVVWSEXPORTEDFUNCTION(void)
IlvRemoveAttachments(IlvGraphic*);

ILVVWSEXPORTEDFUNCTION(void)
IlvCopyAttachments(IlvGraphic* dst, const IlvGraphic* src);

ILVVWSEXPORTEDFUNCTION(void)
IlvComputeAttachs(const IlvGraphic* g, IlUInt& attachs);

ILVVWSEXPORTEDFUNCTION(IlBoolean)
IlvApplyAttachments(const IlvGraphic*,
		    IlvRect& objectBBox,
		    IlFloat,
		    IlFloat,
		    const IlvRect&);

ILVVWSEXPORTEDFUNCTION(IlBoolean)
IlvApplyAttachments(const IlvGraphic*,
		    IlvRect& objectBBox,
		    const IlvRect& oldSize,
		    const IlvRect& newSize);

ILVVWSMODULEINIT(attach);

#endif /* !__Ilv_Graphics_Attach_H */
