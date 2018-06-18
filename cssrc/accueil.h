// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\accueil.h
// IlogViews 5 generated header file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __accueil__header__
#define __accueil__header__

#include <ilviews/gadgets/datfield.h>
#include <ilviews/gadgets/textfd.h>
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
class Accueil
: public AdxGadgetContainer {
public:
    Accueil(IlvDisplay* display,
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
                           size ? *size : IlvRect(0, 0, 741, 543),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Accueil(IlvAbstractView* parent,
            IlvRect* size = 0,
            IlBoolean useacc = IlFalse,
            IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 741, 543),
                           useacc,
                           visible)
        { initialize(); }
	Accueil(IlvDisplay* display,
            IlvSystemView sview,
            IlvBoolean useacc = IlvFalse)
      : AdxGadgetContainer(display, sview, useacc)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void quitterCB(IlvGraphic*);
    virtual void reconcilierCB(IlvGraphic*);
    virtual void peserOFCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void refreshCB(IlvGraphic*);
    virtual void testerBalanceCB(IlvGraphic*);
    virtual void peserFabricationCB(IlvGraphic*);
    virtual void peserArticleCB(IlvGraphic*);
    IlvZoomableTransparentIcon* getpeserOF() const
	{ return (IlvZoomableTransparentIcon*)getObject("peserOF"); }
    IlvZoomableTransparentIcon* getpeserFabrication() const
	{ return (IlvZoomableTransparentIcon*)getObject("peserFabrication"); }
    IlvZoomableTransparentIcon* getreconcilier() const
	{ return (IlvZoomableTransparentIcon*)getObject("reconcilier"); }
    IlvZoomableTransparentIcon* getaide() const
	{ return (IlvZoomableTransparentIcon*)getObject("aide"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvZoomableTransparentIcon* getpeseeArticle() const
	{ return (IlvZoomableTransparentIcon*)getObject("peseeArticle"); }
    IlvZoomableTransparentIcon* gettesterBalance() const
	{ return (IlvZoomableTransparentIcon*)getObject("testerBalance"); }
    IlvZoomableTransparentIcon* getrefresh() const
	{ return (IlvZoomableTransparentIcon*)getObject("refresh"); }
    IlvMessageLabel* getmessage() const
	{ return (IlvMessageLabel*)getObject("message"); }
    IlvMessageLabel* getLibUtilisateur() const
	{ return (IlvMessageLabel*)getObject("LibUtilisateur"); }
    IlvTextField* getChampUtilisateur() const
	{ return (IlvTextField*)getObject("ChampUtilisateur"); }
    IlvTextField* getChampApplication() const
	{ return (IlvTextField*)getObject("ChampApplication"); }
    IlvMessageLabel* getLibDate() const
	{ return (IlvMessageLabel*)getObject("LibDate"); }
    IlvMessageLabel* getLibLieu() const
	{ return (IlvMessageLabel*)getObject("LibLieu"); }
    IlvTextField* getChampLieu() const
	{ return (IlvTextField*)getObject("ChampLieu"); }
    IlvMessageLabel* getLibBox() const
	{ return (IlvMessageLabel*)getObject("LibBox"); }
    IlvTextField* getChampBox() const
	{ return (IlvTextField*)getObject("ChampBox"); }
    IlvMessageLabel* getLibConnection() const
	{ return (IlvMessageLabel*)getObject("LibConnection"); }
    IlvTextField* getChampConnection() const
	{ return (IlvTextField*)getObject("ChampConnection"); }
    IlvMessageLabel* getLibEtalonnage() const
	{ return (IlvMessageLabel*)getObject("LibEtalonnage"); }
    IlvTextField* getChampEtalonnage() const
	{ return (IlvTextField*)getObject("ChampEtalonnage"); }
    IlvDateField* getChampDate() const
	{ return (IlvDateField*)getObject("ChampDate"); }
    IlvMessageLabel* getLibApplication() const
	{ return (IlvMessageLabel*)getObject("LibApplication"); }
protected:
    void initialize();
};

#endif /* !__accueil__header__*/
