// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\message.h
// IlogViews 5 generated header file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __message__header__
#define __message__header__

#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/gadcont.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Message
: public IlvGadgetContainer {
public:
    Message(IlvDisplay* display,
            const char* name, 
            const char* title,
            IlvRect*    size           = 0,
            IlBoolean  useAccelerators = IlFalse,
            IlBoolean  visible         = IlFalse,
            IlUInt     properties      = 0,
            IlvSystemView transientFor = 0)
      : IlvGadgetContainer(display,
                           name,
                           title,
                           size ? *size : IlvRect(0, 0, 646, 190),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Message(IlvAbstractView* parent,
            IlvRect* size = 0,
            IlBoolean useacc = IlFalse,
            IlBoolean visible = IlTrue)
      : IlvGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 646, 190),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void BoutonCB(IlvGraphic*);
    IlvZoomableTransparentIcon* getsecu() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu"); }
    IlvMessageLabel* getMessage() const
	{ return (IlvMessageLabel*)getObject("Message"); }
    IlvButton* getBoutonOui() const
	{ return (IlvButton*)getObject("BoutonOui"); }
    IlvButton* getBoutonNon() const
	{ return (IlvButton*)getObject("BoutonNon"); }
    IlvButton* getBoutonOK() const
	{ return (IlvButton*)getObject("BoutonOK"); }
protected:
    void initialize();
};

#endif /* !__message__header__*/
