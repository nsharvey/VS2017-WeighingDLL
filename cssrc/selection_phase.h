// -------------------------------------------------------------- -*- C++ -*-
// File: D:\MyDevelopment\centraleX3\cssrc\selection_phase.h
// IlogViews 5 generated header file
// File generated Fri Jun 04 13:03:47 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __selection_phase__header__
#define __selection_phase__header__

#include "ilviews/graphics/zicon.h"
#include "ilviews/gadgets/msglabel.h"
#include "ilviews/gadgets/matrix.h"

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Selection_phase
: public AdxGadgetContainer {
public:
    Selection_phase(IlvDisplay* display,
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
    Selection_phase(IlvAbstractView* parent,
                    IlvRect* size = 0,
                    IlBoolean useacc = IlFalse,
                    IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 742, 545),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void descendreCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void monterCB(IlvGraphic*);
    IlvMatrix* getlisteSelectionPhase() const
	{ return (IlvMatrix*)getObject("listeSelectionPhase"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvZoomableTransparentIcon* getdescendre() const
	{ return (IlvZoomableTransparentIcon*)getObject("descendre"); }
    IlvZoomableTransparentIcon* getmonter() const
	{ return (IlvZoomableTransparentIcon*)getObject("monter"); }
    IlvZoomableTransparentIcon* getvalider() const
	{ return (IlvZoomableTransparentIcon*)getObject("valider"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvZoomableTransparentIcon* getaide() const
	{ return (IlvZoomableTransparentIcon*)getObject("aide"); }
protected:
    void initialize();
};

#endif /* !__selection_phase__header__*/
