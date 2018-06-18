// -------------------------------------------------------------- -*- C++ -*-
// File: D:\X3SOURCES\X3Centr3\cssrc\AdxChoix_Balance.h
// --------------------------------------------------------------------------
#ifndef __AdxChoix_Balance__header__
#define __AdxChoix_Balance__header__

#include "Choix_Balance.h"

class AdxChoix_Balance
: public Choix_Balance {
public:
   AdxChoix_Balance(IlvDisplay* display,
                     const char* name,
                     const char* title,
 					 AdxInterface* m_interface,
					 IlvRect*    size            = 0,
                     IlvBoolean  useAccelerators = IlvFalse,
                     IlvBoolean  visible         = IlvFalse,
                     IlvUInt     properties      = 0,
                     IlvSystemView transientFor  = 0)
      : Choix_Balance(display,
                      name,
                      title,
                      size,
                      useAccelerators,
                      visible,
                      properties,
                      transientFor)
		{init(m_interface);}
   /*
    AdxChoix_Balance(IlvAbstractView* parent,
                     IlvRect* size = 0,
                     IlvBoolean useacc = IlvFalse,
                     IlvBoolean visible = IlvTrue)
      : Choix_Balance(parent,
                      size,
                      useacc,
                      visible)
        {}
    AdxChoix_Balance(IlvDisplay* display,
                     IlvSystemView parent,
                     const IlvRect& rect,
                     IlvBoolean useacc = IlvFalse,
                     IlvBoolean visible = IlvTrue)
      : Choix_Balance(display, parent, rect, useacc, visible)
        {}
	*/
    // ____________________________________________________________
    virtual void BalanceCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
	void quitter();
	void afficherBalances();
	AdxInterface* getInterface() {return _interface;};
	void chargement();

	// gbe 12.08 la classe ne dérivant pas de AdxGagetContainer on n'avait pas 
	//           la surcharge du show ...
	virtual void show();

	protected:
	AdxInterface*		_interface;
	void init(AdxInterface* m_interface);
};
#endif
