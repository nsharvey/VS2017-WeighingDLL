// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\phrase_Secu.h
// IlogViews 5 generated header file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __phrase_Secu__header__
#define __phrase_Secu__header__

#include <ilviews/gadgets/text.h>
#include <ilviews/graphics/zicon.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Phrase_Secu
: public AdxGadgetContainer {
public:
    Phrase_Secu(IlvDisplay* display,
                const char* name, 
                const char* title,
                IlvRect*    size           = 0,
                IlBoolean  useAccelerators = IlFalse,
                IlBoolean  visible         = IlFalse,
                IlUInt     properties      = 0,
                IlvSystemView transientFor = 0)
      : AdxGadgetContainer(display,
                           name,
                           title,
                           size ? *size : IlvRect(0, 0, 655, 424),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Phrase_Secu(IlvAbstractView* parent,
                IlvRect* size = 0,
                IlBoolean useacc = IlFalse,
                IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 655, 424),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void descendreCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void monterCB(IlvGraphic*);
    IlvZoomableTransparentIcon* getsecu() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu"); }
    IlvZoomableTransparentIcon* getDescendre() const
	{ return (IlvZoomableTransparentIcon*)getObject("Descendre"); }
    IlvZoomableTransparentIcon* getMonter() const
	{ return (IlvZoomableTransparentIcon*)getObject("Monter"); }
    IlvZoomableTransparentIcon* getAide() const
	{ return (IlvZoomableTransparentIcon*)getObject("Aide"); }
    IlvZoomableTransparentIcon* getQuitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("Quitter"); }
    IlvText* getPhraseSecu() const
	{ return (IlvText*)getObject("PhraseSecu"); }
protected:
    void initialize();
};

#endif /* !__phrase_Secu__header__*/
