// -------------------------------------------------------------- -*- C++ -*-
// File: C:\Développement ILOG\V5.x - Révisions extraites\centrale 150 sartorius + modif SMO\cssrc\recontrole_OF.h
// RogueWaveViews 5 generated header file
// File generated Mon Dec 21 11:57:35 2015
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------
#ifndef __recontrole_OF__header__
#define __recontrole_OF__header__

#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/gadcont.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Recontrole_OF
: public AdxGadgetContainer {
public:
    Recontrole_OF(IlvDisplay* display,
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
                           size ? *size : IlvRect(0, 0, 773, 400),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Recontrole_OF(IlvAbstractView* parent,
                  IlvRect* size = 0,
                  IlBoolean useacc = IlFalse,
                  IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 773, 400),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void SaisieLotCB(IlvGraphic*);
    virtual void SaisieSousLotCB(IlvGraphic*);
    virtual void QuitterCB(IlvGraphic*);
    virtual void SaisiContenuCabCB(IlvGraphic*);
    virtual void EntreeTextFieldCB(IlvGraphic*);
    virtual void TactileCB(IlvGraphic*);
    virtual void SaisieComposantCB(IlvGraphic*);
    IlvMessageLabel* getLibelleComposant() const
	{ return (IlvMessageLabel*)getObject("LibelleComposant"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvMessageLabel* getLibelleLot() const
	{ return (IlvMessageLabel*)getObject("LibelleLot"); }
    IlvTextField* getAffNOF() const
	{ return (IlvTextField*)getObject("AffNOF"); }
    IlvMessageLabel* getLibelleSousLot() const
	{ return (IlvMessageLabel*)getObject("LibelleSousLot"); }
    IlvNumberField* getAffNPhase() const
	{ return (IlvNumberField*)getObject("AffNPhase"); }
    IlvTextField* getSaisieComposant() const
	{ return (IlvTextField*)getObject("SaisieComposant"); }
    IlvTextField* getSaisieLot() const
	{ return (IlvTextField*)getObject("SaisieLot"); }
    IlvZoomableTransparentIcon* getTactile() const
	{ return (IlvZoomableTransparentIcon*)getObject("Tactile"); }
    IlvZoomableTransparentIcon* getQuitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("Quitter"); }
    IlvTextField* getSaisieSousLot() const
	{ return (IlvTextField*)getObject("SaisieSousLot"); }
    IlvTextField* getSaisiContenuCab() const
	{ return (IlvTextField*)getObject("SaisiContenuCab"); }
protected:
    void initialize();
};

#endif /* !__recontrole_OF__header__*/
