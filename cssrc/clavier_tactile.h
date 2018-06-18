// -------------------------------------------------------------- -*- C++ -*-
// File: C:\GitHub\VS2017-WeighingDLL\cssrc\clavier_tactile.h
// RogueWaveViews 6 generated header file
// File generated Mon Jun 18 12:06:28 2018
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------
#ifndef __clavier_tactile__header__
#define __clavier_tactile__header__

#include <ilviews/gadgets/text.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/graphics/relfrect.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/graphics/scale.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/graphics/gauge.h>
#include <ilviews/gadgets/matrix.h>
#include <ilviews/gadgets/datfield.h>
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
class Clavier_tactile
: public AdxGadgetContainer {
public:
    Clavier_tactile(IlvDisplay* display,
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
                           size ? *size : IlvRect(0, 0, 751, 543),
                           properties,
                           useAccelerators,
                           visible,
                           transientFor)
        { initialize(); }
    Clavier_tactile(IlvAbstractView* parent,
                    IlvRect* size = 0,
                    IlBoolean useacc = IlFalse,
                    IlBoolean visible = IlTrue)
      : AdxGadgetContainer(parent,
                           size ? *size : IlvRect(0, 0, 751, 543),
                           useacc,
                           visible)
        { initialize(); }
// --------------------------------------------------------------------------
    virtual void validationCB(IlvGraphic*);
    virtual void toucheCB(IlvGraphic*);
    virtual void arriereCB(IlvGraphic*);
    virtual void retourCB(IlvGraphic*);
    IlvTextField* getchampSaisie() const
	{ return (IlvTextField*)getObject("champSaisie"); }
    IlvZoomableTransparentIcon* getE() const
	{ return (IlvZoomableTransparentIcon*)getObject("E"); }
    IlvZoomableTransparentIcon* getK() const
	{ return (IlvZoomableTransparentIcon*)getObject("K"); }
    IlvZoomableTransparentIcon* getQ() const
	{ return (IlvZoomableTransparentIcon*)getObject("Q"); }
    IlvZoomableTransparentIcon* getW() const
	{ return (IlvZoomableTransparentIcon*)getObject("W"); }
    IlvMessageLabel* getchampMessage() const
	{ return (IlvMessageLabel*)getObject("champMessage"); }
    IlvZoomableTransparentIcon* getA5() const
	{ return (IlvZoomableTransparentIcon*)getObject("A5"); }
    IlvZoomableTransparentIcon* getB() const
	{ return (IlvZoomableTransparentIcon*)getObject("B"); }
    IlvZoomableTransparentIcon* getA6() const
	{ return (IlvZoomableTransparentIcon*)getObject("A6"); }
    IlvZoomableTransparentIcon* getM() const
	{ return (IlvZoomableTransparentIcon*)getObject("M"); }
    IlvZoomableTransparentIcon* getH() const
	{ return (IlvZoomableTransparentIcon*)getObject("H"); }
    IlvZoomableTransparentIcon* getN() const
	{ return (IlvZoomableTransparentIcon*)getObject("N"); }
    IlvZoomableTransparentIcon* getT() const
	{ return (IlvZoomableTransparentIcon*)getObject("T"); }
    IlvZoomableTransparentIcon* gettoucheArriere() const
	{ return (IlvZoomableTransparentIcon*)getObject("toucheArriere"); }
    IlvZoomableTransparentIcon* getO() const
	{ return (IlvZoomableTransparentIcon*)getObject("O"); }
    IlvZoomableTransparentIcon* getP() const
	{ return (IlvZoomableTransparentIcon*)getObject("P"); }
    IlvZoomableTransparentIcon* getA3() const
	{ return (IlvZoomableTransparentIcon*)getObject("A3"); }
    IlvZoomableTransparentIcon* getA1() const
	{ return (IlvZoomableTransparentIcon*)getObject("A1"); }
    IlvZoomableTransparentIcon* getA2() const
	{ return (IlvZoomableTransparentIcon*)getObject("A2"); }
    IlvZoomableTransparentIcon* getA() const
	{ return (IlvZoomableTransparentIcon*)getObject("A"); }
    IlvZoomableTransparentIcon* getA4() const
	{ return (IlvZoomableTransparentIcon*)getObject("A4"); }
    IlvZoomableTransparentIcon* getG() const
	{ return (IlvZoomableTransparentIcon*)getObject("G"); }
    IlvZoomableTransparentIcon* getC() const
	{ return (IlvZoomableTransparentIcon*)getObject("C"); }
    IlvZoomableTransparentIcon* getD() const
	{ return (IlvZoomableTransparentIcon*)getObject("D"); }
    IlvZoomableTransparentIcon* getI() const
	{ return (IlvZoomableTransparentIcon*)getObject("I"); }
    IlvZoomableTransparentIcon* getJ() const
	{ return (IlvZoomableTransparentIcon*)getObject("J"); }
    IlvZoomableTransparentIcon* getA7() const
	{ return (IlvZoomableTransparentIcon*)getObject("A7"); }
    IlvZoomableTransparentIcon* getA9() const
	{ return (IlvZoomableTransparentIcon*)getObject("A9"); }
    IlvZoomableTransparentIcon* getA8() const
	{ return (IlvZoomableTransparentIcon*)getObject("A8"); }
    IlvZoomableTransparentIcon* getA0() const
	{ return (IlvZoomableTransparentIcon*)getObject("A0"); }
    IlvZoomableTransparentIcon* getS() const
	{ return (IlvZoomableTransparentIcon*)getObject("S"); }
    IlvZoomableTransparentIcon* getA11() const
	{ return (IlvZoomableTransparentIcon*)getObject("A11"); }
    IlvZoomableTransparentIcon* getU() const
	{ return (IlvZoomableTransparentIcon*)getObject("U"); }
    IlvZoomableTransparentIcon* getY() const
	{ return (IlvZoomableTransparentIcon*)getObject("Y"); }
    IlvZoomableTransparentIcon* getV() const
	{ return (IlvZoomableTransparentIcon*)getObject("V"); }
    IlvZoomableTransparentIcon* getZ() const
	{ return (IlvZoomableTransparentIcon*)getObject("Z"); }
    IlvZoomableTransparentIcon* getF() const
	{ return (IlvZoomableTransparentIcon*)getObject("F"); }
    IlvZoomableTransparentIcon* getL() const
	{ return (IlvZoomableTransparentIcon*)getObject("L"); }
    IlvZoomableTransparentIcon* getR() const
	{ return (IlvZoomableTransparentIcon*)getObject("R"); }
    IlvZoomableTransparentIcon* getX() const
	{ return (IlvZoomableTransparentIcon*)getObject("X"); }
    IlvZoomableTransparentIcon* getvalidation() const
	{ return (IlvZoomableTransparentIcon*)getObject("validation"); }
    IlvZoomableTransparentIcon* getretour() const
	{ return (IlvZoomableTransparentIcon*)getObject("retour"); }
    IlvZoomableTransparentIcon* gettiret() const
	{ return (IlvZoomableTransparentIcon*)getObject("tiret"); }
protected:
    void initialize();
};

#endif /* !__clavier_tactile__header__*/
