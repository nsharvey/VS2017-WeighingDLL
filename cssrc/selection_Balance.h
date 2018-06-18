// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\selection_Balance.h
// RogueWaveViews 5 generated header file
// File generated Thu Sep 03 16:57:04 2015
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------
#ifndef __selection_Balance__header__
#define __selection_Balance__header__

#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/matrix.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Selection_Balance
: public AdxGadgetContainer {
public:
    Selection_Balance(IlvDisplay* display,
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
                           size ? *size : IlvRect(0, 0, 742, 545),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Selection_Balance(IlvAbstractView* parent,
                      IlvRect* size = 0,
                      IlBoolean useacc = IlFalse,
                      IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 742, 545),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void monterCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    IlvMatrix* getlisteSelectionBalance() const
	{ return (IlvMatrix*)getObject("listeSelectionBalance"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvZoomableTransparentIcon* getDescendre() const
	{ return (IlvZoomableTransparentIcon*)getObject("Descendre"); }
    IlvZoomableTransparentIcon* getMonter() const
	{ return (IlvZoomableTransparentIcon*)getObject("Monter"); }
    IlvZoomableTransparentIcon* getvalider() const
	{ return (IlvZoomableTransparentIcon*)getObject("valider"); }
    IlvZoomableTransparentIcon* getQuitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("Quitter"); }
    IlvZoomableTransparentIcon* getAide() const
	{ return (IlvZoomableTransparentIcon*)getObject("Aide"); }
protected:
    void initialize();
};

#endif /* !__selection_Balance__header__*/
