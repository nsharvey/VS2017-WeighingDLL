// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\Pesee_Etalon.h
// IlogViews 5 generated header file
// File generated Tue Sep 24 15:20:40 2013
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __Pesee_Etalon__header__
#define __Pesee_Etalon__header__

#include <ilviews/graphics/scale.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/graphics/gauge.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/zicon.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Pesee_Etalon
: public AdxGadgetContainer {
public:
    Pesee_Etalon(IlvDisplay* display,
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
                           size ? *size : IlvRect(0, 0, 749, 545),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Pesee_Etalon(IlvAbstractView* parent,
                 IlvRect* size = 0,
                 IlBoolean useacc = IlFalse,
                 IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 749, 545),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void mettreAZeroCB(IlvGraphic*);
    virtual void poidsPeseCB(IlvGraphic*);
    virtual void listerEtalonCB(IlvGraphic*);
    virtual void EntreeNumberFieldCB(IlvGraphic*);
    virtual void peserCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void tactileCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    IlvZoomableTransparentIcon* getaide() const
	{ return (IlvZoomableTransparentIcon*)getObject("aide"); }
    IlvZoomableTransparentIcon* getTactile() const
	{ return (IlvZoomableTransparentIcon*)getObject("Tactile"); }
    IlvZoomableTransparentIcon* getValider() const
	{ return (IlvZoomableTransparentIcon*)getObject("Valider"); }
    IlvZoomableTransparentIcon* getlisterEtalonLignes() const
	{ return (IlvZoomableTransparentIcon*)getObject("listerEtalonLignes"); }
    IlvZoomableTransparentIcon* getmettreAZero() const
	{ return (IlvZoomableTransparentIcon*)getObject("mettreAZero"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvMessageLabel* getMessage() const
	{ return (IlvMessageLabel*)getObject("Message"); }
    IlvMessageLabel* getLabelBalance() const
	{ return (IlvMessageLabel*)getObject("LabelBalance"); }
    IlvTextField* getAffBalance() const
	{ return (IlvTextField*)getObject("AffBalance"); }
    IlvMessageLabel* getLabelFicheEtalon() const
	{ return (IlvMessageLabel*)getObject("LabelFicheEtalon"); }
    IlvMessageLabel* getLabelPoidsType() const
	{ return (IlvMessageLabel*)getObject("LabelPoidsType"); }
    IlvMessageLabel* getLabelPctTolerance() const
	{ return (IlvMessageLabel*)getObject("LabelPctTolerance"); }
    IlvTextField* getAffFicheEtalon() const
	{ return (IlvTextField*)getObject("AffFicheEtalon"); }
    IlvRectangularGauge* getJaugePesee() const
	{ return (IlvRectangularGauge*)getObject("JaugePesee"); }
    IlvMessageLabel* getLabelPoidsPese() const
	{ return (IlvMessageLabel*)getObject("LabelPoidsPese"); }
    IlvMessageLabel* getLabelPoidsAPeser() const
	{ return (IlvMessageLabel*)getObject("LabelPoidsAPeser"); }
    IlvMessageLabel* getLabelEcartPoids() const
	{ return (IlvMessageLabel*)getObject("LabelEcartPoids"); }
    IlvMessageLabel* getLabelCompteur() const
	{ return (IlvMessageLabel*)getObject("LabelCompteur"); }
    IlvTextField* getAffCompteur() const
	{ return (IlvTextField*)getObject("AffCompteur"); }
    IlvTextField* getAffDesFiche() const
	{ return (IlvTextField*)getObject("AffDesFiche"); }
    IlvMessageLabel* getLabelUnPesee() const
	{ return (IlvMessageLabel*)getObject("LabelUnPesee"); }
    IlvMessageLabel* getLabelUnAPeser() const
	{ return (IlvMessageLabel*)getObject("LabelUnAPeser"); }
    IlvMessageLabel* getLabelUnEcart() const
	{ return (IlvMessageLabel*)getObject("LabelUnEcart"); }
    IlvZoomableTransparentIcon* getLighton() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton"); }
    IlvNumberField* getPctTolerance() const
	{ return (IlvNumberField*)getObject("PctTolerance"); }
    IlvNumberField* getPoidsAPeser() const
	{ return (IlvNumberField*)getObject("PoidsAPeser"); }
    IlvNumberField* getEcartPoids() const
	{ return (IlvNumberField*)getObject("EcartPoids"); }
    IlvRectangularScale* getJaugeScale() const
	{ return (IlvRectangularScale*)getObject("JaugeScale"); }
    IlvTextField* getLibTypPesee() const
	{ return (IlvTextField*)getObject("LibTypPesee"); }
    IlvNumberField* getPoidsEtalon() const
	{ return (IlvNumberField*)getObject("PoidsEtalon"); }
    IlvZoomableTransparentIcon* getpeser() const
	{ return (IlvZoomableTransparentIcon*)getObject("peser"); }
    IlvMessageLabel* getLabelcompteurPesees() const
	{ return (IlvMessageLabel*)getObject("LabelcompteurPesees"); }
    IlvTextField* getAffCompteurPesees() const
	{ return (IlvTextField*)getObject("AffCompteurPesees"); }
    IlvNumberField* getPoidsPese() const
	{ return (IlvNumberField*)getObject("PoidsPese"); }
    IlvTextField* getAffLibBalance() const
	{ return (IlvTextField*)getObject("AffLibBalance"); }
protected:
    void initialize();
};

#endif /* !__Pesee_Etalon__header__*/
