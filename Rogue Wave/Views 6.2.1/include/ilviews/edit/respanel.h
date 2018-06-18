// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/respanel.h
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
// Declaration of the IlvResourcePanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Respanel_H
#define __Ilv_Edit_Respanel_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Edit_Paled_H)
#include <ilviews/edit/paled.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Manager_Manager_H)
#include <ilviews/manager/manager.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Gadgets_Colorch_H)
#include <ilviews/gadgets/colorch.h>
#endif
#if !defined(__Ilv_Gadgets_Fontsel_H)
#include <ilviews/gadgets/fontsel.h>
#endif
#if !defined(__Ilv_Gadgets_Iprompt_H)
#include <ilviews/gadgets/iprompt.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#include <ilviews/contain/inter.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Graphics_Arc_H)
#include <ilviews/graphics/arc.h>
#endif
#if !defined(__Ilv_Graphics_Polyline_H)
#include <ilviews/graphics/polyline.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#include <ilviews/graphics/rectangl.h>
#endif
#if !defined(__Ilv_Graphics_Line_H)
#include <ilviews/graphics/line.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Toggle_H)
#include <ilviews/gadgets/toggle.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Gadgets_Scombo_H)
#include <ilviews/gadgets/scombo.h>
#endif
#if !defined(__Ilv_Gadgets_Slider_H)
#include <ilviews/gadgets/slider.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#include <ilviews/graphics/attach.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#include <ilviews/gadgets/stdialog.h>
#endif

class IlvManager;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvResourcePanel
    : public IlvDialog
{
public:
    IlvResourcePanel(IlvManager*,
		     IlvSystemView transientFor = 0);
    ~IlvResourcePanel();
    // ____________________________________________________________
    IlvManager*         getManager()      const { return _manager;    }
    void                setManager(IlvManager* mgr) { _manager = mgr; }
    IlvColorSelector*   getFgSelector()          const { return _foreground; }
    IlvColorSelector*   getBgSelector()          const { return _background; }
    IlvFontSelector*    getFontSelector()        const { return _font;       }
    IlvPatternSelector* getColPatternSelector()  const { return _colPattern; }
    IlvPatternSelector* getGradPatternSelector() const { return _gradPattern; }
    virtual void        reset(const IlvGraphic* g = 0);
    IlvPalette*         getPalette() const;
    virtual void        setPalette(const IlvPalette* p = 0);
    virtual void        applyForeground(IlvColor* c = 0) const;
    IlvColor*           getSelectedForeground() const;
    virtual void        applyBackground(IlvColor* c = 0) const;
    IlvColor*           getSelectedBackground() const;
    virtual void        applyFont(IlvFont* f = 0) const;
    IlvFont*            getSelectedFont() const;
    virtual void        applyFillStyle(IlvFillStyle fs = IlvFillPattern) const;
    IlvFillStyle        getSelectedFillStyle() const;
    virtual void        applyPattern(IlvPattern* p = 0) const;
    IlvPattern*         getSelectedPattern() const;
    virtual void        applyColorPattern(IlvColorPattern* p = 0) const;
    IlvColorPattern*    getSelectedColorPattern() const;
    virtual void        applyGradientPattern(IlvGradientPattern* p = 0) const;
    IlvGradientPattern* getSelectedGradientPattern() const;
    virtual void        applyLineStyle(IlvLineStyle* l = 0) const;
    IlvLineStyle*       getSelectedLineStyle() const;
    virtual void        applyLineWidth(IlUShort = (IlUShort)-1) const;
    IlUShort            getSelectedLineWidth() const;
    IlvIntensity        getSelectedAlpha() const;
    virtual void        applyAlpha(IlvIntensity alpha) const;
    IlvAntialiasingMode getSelectedAntialiasingMode() const;
    virtual void        applyAntialiasingMode(IlvAntialiasingMode mode) const;

    virtual void        apply();
    virtual void        show();
    virtual void        updatePaletteNames();
    virtual void        applyName(const char*);
    IlvIPromptString*   getNameSelector() const { return _name; }
    const char*	        getSelectedName() const;
    virtual void        updateNameField(const IlvPalette* p = 0);
    virtual void        setBackground(IlvColor* c);

    virtual void        applyArcMode(IlvArcMode m = (IlvArcMode)(-1)) const;
    IlvArcMode          getSelectedArcMode() const;

    virtual void        applyFillRule(IlvFillRule m = (IlvFillRule)(-1)) const;
    IlvFillRule         getSelectedFillRule() const;

protected:
    IlvManager*         _manager;
    IlvColorSelector*   _foreground;
    IlvColorSelector*   _background;
    IlvFontSelector*    _font;
    IlvPatternSelector* _colPattern;
    IlvPatternSelector* _gradPattern;
    IlvIPromptString*   _name;
};

#endif /* !__Ilv_Edit_Respanel_H */
