// AdxChoix_OF.h
// -------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#ifndef __Adxchoix_OF__header__
#define __Adxchoix_OF__header__

#include <ilviews/gadgets/datfield.h>
#include "choix_OF.h"
#include <fstream>								// 06.04 TRACE

using std::endl;

#include "AdxOrder.h"

class AdxChoix_OF
: public Choix_OF {
public:
   AdxChoix_OF(IlvDisplay* display,
                const char* name,
                const char* title,
				AdxInterface* m_interface,
                IlvRect*    size            = 0,
                IlvBoolean  useAccelerators = IlvFalse,
                IlvBoolean  visible         = IlvFalse,
                IlvUInt     properties      = 0,
                IlvSystemView transientFor  = 0)
      : Choix_OF(display,
                 name,
                 title,
                 size,
                 useAccelerators,
                 visible,
                 properties,
                 transientFor)
        {init(m_interface);}
/*
   	AdxChoix_OF(IlvDisplay* display,
				  IlvSystemView sview,
				  AdxInterface* m_interface,
				  IlvBoolean useacc = IlvFalse)
	  : Choix_OF(display, sview, useacc)
        {init(m_interface);}
    AdxChoix_OF(IlvAbstractView* parent,
				AdxInterface* m_interface,
                IlvRect* size = 0,
                IlvBoolean useacc = IlvFalse,
                IlvBoolean visible = IlvTrue)
      : Choix_OF(parent,
                 size,
                 useacc,
                 visible)
        {init(m_interface);}
*/
//--------------------------------------------------------------
    virtual void listeOFCB(IlvGraphic*);
	virtual void SaisiePhaseCB(IlvGraphic* g);
	virtual void SaisieComposantCB(IlvGraphic* g);
	virtual void EntreeTextFieldCB(IlvGraphic* g);
	virtual void EntreeNumberFieldCB(IlvGraphic* g);
    virtual void quitterCB(IlvGraphic*);
    virtual void TactileCB(IlvGraphic*);
	virtual void SaisieNOFCB(IlvGraphic* g);
    virtual void ValidationCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void listePhaseCB(IlvGraphic*);
    virtual void VideBoxCB(IlvGraphic*);
    virtual void AllouerCB(IlvGraphic*);
    virtual void listeComposantCB(IlvGraphic*);

 	void quitter();
	void afficherOrdre(long numo,long nump,long numc);
	AdxInterface* getInterface() {return _interface;};
	bool controleChangementOF(int nouvelIndex);	
	bool controleChangementPhase(int nouvelIndex);
	bool changementPhase_Art(int nouvelIndexComposant, int nouvelIndexPhase);
	bool controleChangementComposant(int nouvelIndex);
	void changementComposant_Art();
	void changementOF_Art();
	bool controleNouveauComposant(int nouvelIndex);
	void interruptionOF();
	void interruptionPhase();
	void interruptionComposant();
	void changementOFNonPese(AdxOrder* newOrder);
	void chargement();
	void validationPeseeAutomatique();
	void chargementZonesAVide();


protected:
	AdxInterface*		_interface;
	void init(AdxInterface* m_interface);
	void initClavier_Tactile();
	bool envoieMessage(CString mess, bool OUINON);

};
#endif
