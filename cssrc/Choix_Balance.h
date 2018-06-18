// -------------------------------------------------------------- -*- C++ -*-
// File: C:\e\MyDevelopment\centrale sarto modif\cssrc\Choix_Balance.h
// IlogViews 5 generated header file
// File generated Tue May 11 17:33:38 2010
//      by IBM ILOG Views Studio
// --------------------------------------------------------------------------
#ifndef __Choix_Balance__header__
#define __Choix_Balance__header__

#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/button.h>

// --------------------------------------------------------------------------
// --- Inserted code

#ifdef ILVNOSTATICDATA
#undef ILVNOSTATICDATA
#endif
#include "AdxGadgetContainer.h"
// --- End of Inserted code

// --------------------------------------------------------------------------
class Choix_Balance
: public AdxGadgetContainer {
public:
    Choix_Balance(IlvDisplay* display,
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
    Choix_Balance(IlvAbstractView* parent,
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
    virtual void BalanceCB(IlvGraphic*);
    IlvButton* getBalance1() const
	{ return (IlvButton*)getObject("Balance1"); }
    IlvButton* getBalance2() const
	{ return (IlvButton*)getObject("Balance2"); }
    IlvButton* getBalance3() const
	{ return (IlvButton*)getObject("Balance3"); }
    IlvButton* getBalance4() const
	{ return (IlvButton*)getObject("Balance4"); }
    IlvButton* getBalance5() const
	{ return (IlvButton*)getObject("Balance5"); }
    IlvButton* getBalance7() const
	{ return (IlvButton*)getObject("Balance7"); }
    IlvButton* getBalance8() const
	{ return (IlvButton*)getObject("Balance8"); }
    IlvZoomableTransparentIcon* getquitter() const
	{ return (IlvZoomableTransparentIcon*)getObject("quitter"); }
    IlvButton* getBalance6() const
	{ return (IlvButton*)getObject("Balance6"); }
    IlvMessageLabel* getMessage() const
	{ return (IlvMessageLabel*)getObject("Message"); }
    IlvReliefDiamond* getDiamond1() const
	{ return (IlvReliefDiamond*)getObject("Diamond1"); }
    IlvReliefRectangle* getDiamond1G() const
	{ return (IlvReliefRectangle*)getObject("Diamond1G"); }
    IlvReliefRectangle* getDiamond1D() const
	{ return (IlvReliefRectangle*)getObject("Diamond1D"); }
    IlvReliefDiamond* getDiamond2() const
	{ return (IlvReliefDiamond*)getObject("Diamond2"); }
    IlvReliefRectangle* getDiamond2G() const
	{ return (IlvReliefRectangle*)getObject("Diamond2G"); }
    IlvReliefRectangle* getDiamond2D() const
	{ return (IlvReliefRectangle*)getObject("Diamond2D"); }
    IlvReliefDiamond* getDiamond3() const
	{ return (IlvReliefDiamond*)getObject("Diamond3"); }
    IlvReliefRectangle* getDiamond3G() const
	{ return (IlvReliefRectangle*)getObject("Diamond3G"); }
    IlvReliefRectangle* getDiamond3D() const
	{ return (IlvReliefRectangle*)getObject("Diamond3D"); }
    IlvReliefDiamond* getDiamond4() const
	{ return (IlvReliefDiamond*)getObject("Diamond4"); }
    IlvReliefRectangle* getDiamond4G() const
	{ return (IlvReliefRectangle*)getObject("Diamond4G"); }
    IlvReliefRectangle* getDiamond4D() const
	{ return (IlvReliefRectangle*)getObject("Diamond4D"); }
    IlvReliefDiamond* getDiamond5() const
	{ return (IlvReliefDiamond*)getObject("Diamond5"); }
    IlvReliefRectangle* getDiamond5G() const
	{ return (IlvReliefRectangle*)getObject("Diamond5G"); }
    IlvReliefRectangle* getDiamond5D() const
	{ return (IlvReliefRectangle*)getObject("Diamond5D"); }
    IlvReliefDiamond* getDiamond7() const
	{ return (IlvReliefDiamond*)getObject("Diamond7"); }
    IlvReliefRectangle* getDiamond7G() const
	{ return (IlvReliefRectangle*)getObject("Diamond7G"); }
    IlvReliefRectangle* getDiamond7D() const
	{ return (IlvReliefRectangle*)getObject("Diamond7D"); }
    IlvReliefDiamond* getDiamond8() const
	{ return (IlvReliefDiamond*)getObject("Diamond8"); }
    IlvReliefRectangle* getDiamond8G() const
	{ return (IlvReliefRectangle*)getObject("Diamond8G"); }
    IlvReliefRectangle* getDiamond8D() const
	{ return (IlvReliefRectangle*)getObject("Diamond8D"); }
    IlvReliefDiamond* getDiamond6() const
	{ return (IlvReliefDiamond*)getObject("Diamond6"); }
    IlvReliefRectangle* getDiamond6G() const
	{ return (IlvReliefRectangle*)getObject("Diamond6G"); }
    IlvReliefRectangle* getDiamond6D() const
	{ return (IlvReliefRectangle*)getObject("Diamond6D"); }
    IlvZoomableTransparentIcon* getLighton1() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton1"); }
    IlvZoomableTransparentIcon* getLighton2() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton2"); }
    IlvZoomableTransparentIcon* getLighton3() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton3"); }
    IlvZoomableTransparentIcon* getLighton4() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton4"); }
    IlvZoomableTransparentIcon* getLighton5() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton5"); }
    IlvZoomableTransparentIcon* getLighton6() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton6"); }
    IlvZoomableTransparentIcon* getLighton7() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton7"); }
    IlvZoomableTransparentIcon* getLighton8() const
	{ return (IlvZoomableTransparentIcon*)getObject("Lighton8"); }
    IlvRectangle* getEtalon3() const
	{ return (IlvRectangle*)getObject("Etalon3"); }
    IlvRectangle* getEtalon1() const
	{ return (IlvRectangle*)getObject("Etalon1"); }
    IlvRectangle* getEtalon2() const
	{ return (IlvRectangle*)getObject("Etalon2"); }
    IlvRectangle* getEtalon4() const
	{ return (IlvRectangle*)getObject("Etalon4"); }
    IlvRectangle* getEtalon5() const
	{ return (IlvRectangle*)getObject("Etalon5"); }
    IlvRectangle* getEtalon6() const
	{ return (IlvRectangle*)getObject("Etalon6"); }
    IlvRectangle* getEtalon7() const
	{ return (IlvRectangle*)getObject("Etalon7"); }
    IlvRectangle* getEtalon8() const
	{ return (IlvRectangle*)getObject("Etalon8"); }
protected:
    void initialize();
};

#endif /* !__Choix_Balance__header__*/
