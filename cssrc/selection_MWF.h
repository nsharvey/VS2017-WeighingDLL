// -------------------------------------------------------------- -*- C++ -*-
// File: D:\MyDevelopment\centraleX3\cssrc\selection_MWF.h
// IlogViews 5 generated header file
// File generated Thu Aug 19 16:56:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __selection_MWF__header__
#define __selection_MWF__header__

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
class Selection_MWF
: public AdxGadgetContainer {
public:
    Selection_MWF(IlvDisplay* display,
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
    Selection_MWF(IlvAbstractView* parent,
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
    virtual void quitterCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    IlvMatrix* getlisteSelectionMWF() const
	{ return (IlvMatrix*)getObject("listeSelectionMWF"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvZoomableTransparentIcon* getdescendre() const
	{ return (IlvZoomableTransparentIcon*)getObject("descendre"); }
    IlvZoomableTransparentIcon* getmonter() const
	{ return (IlvZoomableTransparentIcon*)getObject("monter"); }
    IlvZoomableTransparentIcon* getvalider() const
	{ return (IlvZoomableTransparentIcon*)getObject("valider"); }
    IlvZoomableTransparentIcon* getaide() const
	{ return (IlvZoomableTransparentIcon*)getObject("aide"); }
protected:
    void initialize();
};

#endif /* !__selection_MWF__header__*/
