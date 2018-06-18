// -------------------------------------------------------------- -*- C++ -*-
// File: C:\MyDevelopment\Centrale V6\cssrc\pesee_OF.h
// IlogViews 5 generated header file
// File generated Tue Mar 20 19:17:39 2012
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __pesee_OF__header__
#define __pesee_OF__header__

#include <ilviews/graphics/scale.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/graphics/gauge.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/textfd.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Pesee_OF
: public AdxGadgetContainer {
public:
    Pesee_OF(IlvDisplay* display,
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
                           size ? *size : IlvRect(0, 0, 743, 545),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Pesee_OF(IlvAbstractView* parent,
             IlvRect* size = 0,
             IlBoolean useacc = IlFalse,
             IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 743, 545),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void SaisieRecipientCB(IlvGraphic*);
    virtual void secu7CB(IlvGraphic*);
    virtual void tactileCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void AideCB(IlvGraphic*);
    virtual void SaisieSousLotCB(IlvGraphic*);
    virtual void FocusOutLotCB(IlvGraphic*);
    virtual void secu8CB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void tarerCB(IlvGraphic*);
    virtual void FocusOutBalanceCB(IlvGraphic*);
    virtual void ListeLotCB(IlvGraphic*);
    virtual void SaisieEmplacementCB(IlvGraphic*);
    virtual void SaisieBalanceCB(IlvGraphic*);
    virtual void secu10CB(IlvGraphic*);
    virtual void secu3CB(IlvGraphic*);
    virtual void validerPlusCB(IlvGraphic*);
    virtual void EntreeTextFieldCB(IlvGraphic*);
    virtual void SaisiePoidsPeseCB(IlvGraphic*);
    virtual void FocusOutRecipientCB(IlvGraphic*);
    virtual void secu2CB(IlvGraphic*);
    virtual void secu1CB(IlvGraphic*);
    virtual void ListeRecipientCB(IlvGraphic*);
    virtual void secu6CB(IlvGraphic*);
    virtual void SaisieLotCB(IlvGraphic*);
    virtual void secu9CB(IlvGraphic*);
    virtual void mettreAZeroCB(IlvGraphic*);
    virtual void FocusOutEmplacementCB(IlvGraphic*);
    virtual void peserCB(IlvGraphic*);
    virtual void SaisieVanneCB(IlvGraphic*);
    virtual void FocusOutSousLotCB(IlvGraphic*);
    virtual void SaisieCuveCB(IlvGraphic*);
    virtual void EntreeNumberFieldCB(IlvGraphic*);
    virtual void ListeBalanceCB(IlvGraphic*);
    virtual void secu5CB(IlvGraphic*);
    virtual void ListeEmplacementCB(IlvGraphic*);
    virtual void secu4CB(IlvGraphic*);
    IlvTextField* getSaisieBalance() const
	{ return (IlvTextField*)getObject("SaisieBalance"); }
    IlvZoomableTransparentIcon* getvaliderPlus() const
	{ return (IlvZoomableTransparentIcon*)getObject("validerPlus"); }
    IlvZoomableTransparentIcon* gettarer() const
	{ return (IlvZoomableTransparentIcon*)getObject("tarer"); }
    IlvZoomableTransparentIcon* getvalider() const
	{ return (IlvZoomableTransparentIcon*)getObject("valider"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvZoomableTransparentIcon* getmettreAZero() const
	{ return (IlvZoomableTransparentIcon*)getObject("mettreAZero"); }
    IlvZoomableTransparentIcon* gettactile() const
	{ return (IlvZoomableTransparentIcon*)getObject("tactile"); }
    IlvZoomableTransparentIcon* getsecu3() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu3"); }
    IlvZoomableTransparentIcon* getpeser() const
	{ return (IlvZoomableTransparentIcon*)getObject("peser"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvZoomableTransparentIcon* getsecu1() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu1"); }
    IlvZoomableTransparentIcon* getsecu7() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu7"); }
    IlvZoomableTransparentIcon* getsecu2() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu2"); }
    IlvZoomableTransparentIcon* getsecu4() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu4"); }
    IlvZoomableTransparentIcon* getsecu8() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu8"); }
    IlvZoomableTransparentIcon* getsecu9() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu9"); }
    IlvTextField* getAffNOF() const
	{ return (IlvTextField*)getObject("AffNOF"); }
    IlvMessageLabel* getUniteTotalAPeser() const
	{ return (IlvMessageLabel*)getObject("UniteTotalAPeser"); }
    IlvMessageLabel* getUniteTare() const
	{ return (IlvMessageLabel*)getObject("UniteTare"); }
    IlvRectangularGauge* getJaugePesee() const
	{ return (IlvRectangularGauge*)getObject("JaugePesee"); }
    IlvMessageLabel* getUnitePoidsPese() const
	{ return (IlvMessageLabel*)getObject("UnitePoidsPese"); }
    IlvMessageLabel* getUnitePoidsAPeser() const
	{ return (IlvMessageLabel*)getObject("UnitePoidsAPeser"); }
    IlvTextField* getSaisieRecipient() const
	{ return (IlvTextField*)getObject("SaisieRecipient"); }
    IlvTextField* getAffComposant() const
	{ return (IlvTextField*)getObject("AffComposant"); }
    IlvMessageLabel* getEtiquetteLot() const
	{ return (IlvMessageLabel*)getObject("EtiquetteLot"); }
    IlvTextField* getSaisieLot() const
	{ return (IlvTextField*)getObject("SaisieLot"); }
    IlvZoomableTransparentIcon* getBoutonListeBalance() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeBalance"); }
    IlvMessageLabel* getEtiquetteEmplacement() const
	{ return (IlvMessageLabel*)getObject("EtiquetteEmplacement"); }
    IlvTextField* getSaisieEmplacement() const
	{ return (IlvTextField*)getObject("SaisieEmplacement"); }
    IlvZoomableTransparentIcon* getsecu6() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu6"); }
    IlvNumberField* getAffNPhase() const
	{ return (IlvNumberField*)getObject("AffNPhase"); }
    IlvZoomableTransparentIcon* getAffConnection() const
	{ return (IlvZoomableTransparentIcon*)getObject("AffConnection"); }
    IlvNumberField* getSaisiePoidsPese() const
	{ return (IlvNumberField*)getObject("SaisiePoidsPese"); }
    IlvNumberField* getAffTotalAPeser() const
	{ return (IlvNumberField*)getObject("AffTotalAPeser"); }
    IlvNumberField* getAffTare() const
	{ return (IlvNumberField*)getObject("AffTare"); }
    IlvNumberField* getAffPoidsAPeser() const
	{ return (IlvNumberField*)getObject("AffPoidsAPeser"); }
    IlvZoomableTransparentIcon* getBoutonListeEmplacement() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeEmplacement"); }
    IlvZoomableTransparentIcon* getBoutonListeRecipient() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeRecipient"); }
    IlvZoomableTransparentIcon* getBoutonListeLot() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeLot"); }
    IlvRectangularScale* getJaugeScale() const
	{ return (IlvRectangularScale*)getObject("JaugeScale"); }
    IlvZoomableTransparentIcon* getsecu5() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu5"); }
    IlvZoomableTransparentIcon* getsecu10() const
	{ return (IlvZoomableTransparentIcon*)getObject("secu10"); }
    IlvMessageLabel* getEtiquetteCuve() const
	{ return (IlvMessageLabel*)getObject("EtiquetteCuve"); }
    IlvTextField* getSaisieCuve() const
	{ return (IlvTextField*)getObject("SaisieCuve"); }
    IlvMessageLabel* getEtiquetteVanne() const
	{ return (IlvMessageLabel*)getObject("EtiquetteVanne"); }
    IlvTextField* getSaisieVanne() const
	{ return (IlvTextField*)getObject("SaisieVanne"); }
    IlvZoomableTransparentIcon* getBoutonListeCuve() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeCuve"); }
    IlvTextField* getSaisieSousLot() const
	{ return (IlvTextField*)getObject("SaisieSousLot"); }
    IlvMessageLabel* getEtiquetteSousLot() const
	{ return (IlvMessageLabel*)getObject("EtiquetteSousLot"); }
    IlvTextField* getLibSaisieCuve() const
	{ return (IlvTextField*)getObject("LibSaisieCuve"); }
    IlvTextField* getLibSaisieEmplacement() const
	{ return (IlvTextField*)getObject("LibSaisieEmplacement"); }
    IlvTextField* getLibSaisieRecipient() const
	{ return (IlvTextField*)getObject("LibSaisieRecipient"); }
    IlvTextField* getLibSaisieBalance() const
	{ return (IlvTextField*)getObject("LibSaisieBalance"); }
    IlvTextField* getLibAffComposant() const
	{ return (IlvTextField*)getObject("LibAffComposant"); }
    IlvZoomableTransparentIcon* getAide() const
	{ return (IlvZoomableTransparentIcon*)getObject("Aide"); }
    IlvMessageLabel* getUnitePoidsCumuleCible() const
	{ return (IlvMessageLabel*)getObject("UnitePoidsCumuleCible"); }
    IlvNumberField* getAffPoidsCumuleCible() const
	{ return (IlvNumberField*)getObject("AffPoidsCumuleCible"); }
    IlvMessageLabel* getEtiquettePoidsCumuleCible() const
	{ return (IlvMessageLabel*)getObject("EtiquettePoidsCumuleCible"); }
    IlvNumberField* getAffPoidsCumule() const
	{ return (IlvNumberField*)getObject("AffPoidsCumule"); }
    IlvMessageLabel* getEtiquettePoidsCumule() const
	{ return (IlvMessageLabel*)getObject("EtiquettePoidsCumule"); }
    IlvMessageLabel* getUnitePoidsCumule() const
	{ return (IlvMessageLabel*)getObject("UnitePoidsCumule"); }
protected:
    void initialize();
};

#endif /* !__pesee_OF__header__*/
