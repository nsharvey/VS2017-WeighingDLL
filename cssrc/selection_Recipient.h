// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\selection_Recipient.h
// IlogViews 5 generated header file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __selection_Recipient__header__
#define __selection_Recipient__header__

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
class Selection_Recipient
: public AdxGadgetContainer {
public:
    Selection_Recipient(IlvDisplay* display,
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
    Selection_Recipient(IlvAbstractView* parent,
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
    virtual void quitterCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void monterCB(IlvGraphic*);
    IlvMatrix* getlisteSelectionRecipient() const
	{ return (IlvMatrix*)getObject("listeSelectionRecipient"); }
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

#endif /* !__selection_Recipient__header__*/
