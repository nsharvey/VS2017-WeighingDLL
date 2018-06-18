// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\selection_LOT.h
// IlogViews 5 generated header file
// File generated Wed Feb 02 09:04:46 2011
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __selection_LOT__header__
#define __selection_LOT__header__

#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/textfd.h>
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
class Selection_LOT
: public AdxGadgetContainer {
public:
    Selection_LOT(IlvDisplay* display,
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
    Selection_LOT(IlvAbstractView* parent,
                  IlvRect* size = 0,
                  IlBoolean useacc = IlFalse,
                  IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 742, 545),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void aideCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void monterCB(IlvGraphic*);
    virtual void consultationStockDetailleCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void desallouerCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void imprimerCB(IlvGraphic*);
    virtual void allouerCB(IlvGraphic*);
    IlvMatrix* getlisteSelectionLot() const
	{ return (IlvMatrix*)getObject("listeSelectionLot"); }
    IlvMatrix* getlisteSelectionCuve() const
	{ return (IlvMatrix*)getObject("listeSelectionCuve"); }
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
    IlvZoomableTransparentIcon* getimprimer() const
	{ return (IlvZoomableTransparentIcon*)getObject("imprimer"); }
    IlvZoomableTransparentIcon* getallouer() const
	{ return (IlvZoomableTransparentIcon*)getObject("allouer"); }
    IlvTextField* getAffComposant() const
	{ return (IlvTextField*)getObject("AffComposant"); }
    IlvMessageLabel* getAffUS() const
	{ return (IlvMessageLabel*)getObject("AffUS"); }
    IlvNumberField* getAffQuantite() const
	{ return (IlvNumberField*)getObject("AffQuantite"); }
    IlvZoomableTransparentIcon* getdesallouer() const
	{ return (IlvZoomableTransparentIcon*)getObject("desallouer"); }
    IlvZoomableTransparentIcon* getconsultationStockDetaille() const
	{ return (IlvZoomableTransparentIcon*)getObject("consultationStockDetaille"); }
protected:
    void initialize();
};

#endif /* !__selection_LOT__header__*/
