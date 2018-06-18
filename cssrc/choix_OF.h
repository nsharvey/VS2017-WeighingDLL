// -------------------------------------------------------------- -*- C++ -*-
// File: C:\MyDevelopment\Centrale V6\cssrc\choix_OF.h
// IlogViews 5 generated header file
// File generated Tue Mar 20 19:40:07 2012
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __choix_OF__header__
#define __choix_OF__header__

#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/gadcont.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Choix_OF
: public AdxGadgetContainer {
public:
    Choix_OF(IlvDisplay* display,
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
    Choix_OF(IlvAbstractView* parent,
             IlvRect* size = 0,
             IlBoolean useacc = IlFalse,
             IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 742, 545),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void quitterCB(IlvGraphic*);
    virtual void ValidationCB(IlvGraphic*);
    virtual void listeComposantCB(IlvGraphic*);
    virtual void EntreeTextFieldCB(IlvGraphic*);
    virtual void AllouerCB(IlvGraphic*);
    virtual void listePhaseCB(IlvGraphic*);
    virtual void VideBoxCB(IlvGraphic*);
    virtual void SaisieComposantCB(IlvGraphic*);
    virtual void TactileCB(IlvGraphic*);
    virtual void listeOFCB(IlvGraphic*);
    virtual void SaisiePhaseCB(IlvGraphic*);
    virtual void EntreeNumberFieldCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void SaisieNOFCB(IlvGraphic*);
    IlvTextField* getSaisieNOF() const
	{ return (IlvTextField*)getObject("SaisieNOF"); }
    IlvZoomableTransparentIcon* getBoutonListeOF() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeOF"); }
    IlvZoomableTransparentIcon* getBoutonListePhase() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListePhase"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvZoomableTransparentIcon* getaide() const
	{ return (IlvZoomableTransparentIcon*)getObject("aide"); }
    IlvZoomableTransparentIcon* getValider() const
	{ return (IlvZoomableTransparentIcon*)getObject("Valider"); }
    IlvZoomableTransparentIcon* getTactile() const
	{ return (IlvZoomableTransparentIcon*)getObject("Tactile"); }
    IlvZoomableTransparentIcon* getVideBox() const
	{ return (IlvZoomableTransparentIcon*)getObject("VideBox"); }
    IlvTextField* getSaisieComposant() const
	{ return (IlvTextField*)getObject("SaisieComposant"); }
    IlvZoomableTransparentIcon* getBoutonListeComposant() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeComposant"); }
    IlvZoomableTransparentIcon* getAllouer() const
	{ return (IlvZoomableTransparentIcon*)getObject("Allouer"); }
    IlvZoomableTransparentIcon* getBoutonListeComposant_Art() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeComposant_Art"); }
    IlvZoomableTransparentIcon* getBoutonListePhase_Art() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListePhase_Art"); }
    IlvTextField* getSaisieNOF_Art() const
	{ return (IlvTextField*)getObject("SaisieNOF_Art"); }
    IlvZoomableTransparentIcon* getBoutonListeOF_Art() const
	{ return (IlvZoomableTransparentIcon*)getObject("BoutonListeOF_Art"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvMessageLabel* getEtiquetteNoOF() const
	{ return (IlvMessageLabel*)getObject("EtiquetteNoOF"); }
    IlvMessageLabel* getEtiquettePhase() const
	{ return (IlvMessageLabel*)getObject("EtiquettePhase"); }
    IlvMessageLabel* getEtiquetteArtLance() const
	{ return (IlvMessageLabel*)getObject("EtiquetteArtLance"); }
    IlvMessageLabel* getEtiquetteLotLance() const
	{ return (IlvMessageLabel*)getObject("EtiquetteLotLance"); }
    IlvTextField* getAffLot() const
	{ return (IlvTextField*)getObject("AffLot"); }
    IlvTextField* getAffArticle() const
	{ return (IlvTextField*)getObject("AffArticle"); }
    IlvMessageLabel* getEtiquetteQteAllouee() const
	{ return (IlvMessageLabel*)getObject("EtiquetteQteAllouee"); }
    IlvMessageLabel* getAffUniteComp() const
	{ return (IlvMessageLabel*)getObject("AffUniteComp"); }
    IlvTextField* getAffLibArticle() const
	{ return (IlvTextField*)getObject("AffLibArticle"); }
    IlvMessageLabel* getEtiquetteComposant() const
	{ return (IlvMessageLabel*)getObject("EtiquetteComposant"); }
    IlvTextField* getAffLibComposant() const
	{ return (IlvTextField*)getObject("AffLibComposant"); }
    IlvMessageLabel* getLibQuantiteAPeser() const
	{ return (IlvMessageLabel*)getObject("LibQuantiteAPeser"); }
    IlvMessageLabel* getAffUniteComposant() const
	{ return (IlvMessageLabel*)getObject("AffUniteComposant"); }
    IlvNumberField* getAffQuantite() const
	{ return (IlvNumberField*)getObject("AffQuantite"); }
    IlvNumberField* getAffQuantiteAPeser() const
	{ return (IlvNumberField*)getObject("AffQuantiteAPeser"); }
    IlvNumberField* getSaisiePhase() const
	{ return (IlvNumberField*)getObject("SaisiePhase"); }
    IlvMessageLabel* getEtiquetteComposant_Art() const
	{ return (IlvMessageLabel*)getObject("EtiquetteComposant_Art"); }
    IlvTextField* getAffLibComposant_Art() const
	{ return (IlvTextField*)getObject("AffLibComposant_Art"); }
    IlvMessageLabel* getEtiquettePhase_Art() const
	{ return (IlvMessageLabel*)getObject("EtiquettePhase_Art"); }
    IlvNumberField* getSaisiePhase_Art() const
	{ return (IlvNumberField*)getObject("SaisiePhase_Art"); }
    IlvMessageLabel* getEtiquetteNoOF_Art() const
	{ return (IlvMessageLabel*)getObject("EtiquetteNoOF_Art"); }
    IlvTextField* getSaisieComposant_Art() const
	{ return (IlvTextField*)getObject("SaisieComposant_Art"); }
protected:
    void initialize();
};

#endif /* !__choix_OF__header__*/
