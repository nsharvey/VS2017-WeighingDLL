// AdxClavier_tactile.h
// --------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#ifndef __Adxclavier_Tactile__header__
#define __Adxclavier_Tactile__header__

#include "clavier_tactile.h"

class AdxInterface;
class AdxChoix_OF;

class AdxClavier_Tactile
: public Clavier_tactile {
public:
   virtual ~AdxClavier_Tactile();
   AdxClavier_Tactile(IlvDisplay* display,
                       const char* name,
                       const char* title,
					   AdxInterface* m_interface,
                       IlvRect*    size            = 0,
                       IlvBoolean  useAccelerators = IlvFalse,
                       IlvBoolean  visible         = IlvFalse,
                       IlvUInt     properties      = 0,
                       IlvSystemView transientFor  = 0)
      : Clavier_tactile(display,
                        name,
                        title,
                        size,
                        useAccelerators,
                        visible,
                        properties,
                        transientFor)
        {init(m_interface);}
/*
    AdxClavier_Tactile(IlvDisplay* display,
				  IlvSystemView sview,
				  AdxInterface* m_interface,
				  IlvBoolean useacc = IlvFalse)
	  : Clavier_tactile(display, sview, useacc)
        {init(m_interface);}
    AdxClavier_Tactile(IlvAbstractView* parent,
                       IlvRect* size = 0,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Clavier_tactile(parent,
                        size,
                        useacc,
                        visible)
        {}
*/
//--------------------------------------------------------------
    virtual void arriereCB(IlvGraphic*);
    virtual void validationCB(IlvGraphic*);
    virtual void toucheCB(IlvGraphic*);
    virtual void retourCB(IlvGraphic*);
//	AdxInterface* getInterface () const {return _interface;}
	const char * getSaisie() const { return _saisie;}
	void setSaisie(const char * string) { _saisie = string;}
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	void quitter();
	void setAlpha(const IlvBoolean b); 
	AdxInterface* getInterface() {return _interface;};

protected:
	CString						_saisie;
	IlvBoolean					_alpha;
	int							_nbSepar;
	int							_posSepar;
	double						_saisieNum;
	int							_diviseur;
	AdxGadgetContainer*			_panneauAppelant;

	AdxInterface*		_interface;
	void init(AdxInterface* m_interface);
	void plus(int i);
	void moins(int i);
};
#endif
