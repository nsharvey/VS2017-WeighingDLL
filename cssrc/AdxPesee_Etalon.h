// AdxPesee_Etalon.h
// -----------------
// project : Adonix X3 Scales
// author : SR
// V130 : SR 2001.11.27

#ifndef __AdxPesee_Etalon__header__
#define __AdxPesee_Etalon__header__

#include "Pesee_Etalon.h"

class AdxInterface;
class AdxBalance;

class AdxPesee_Etalon
: public Pesee_Etalon {
public:
   AdxPesee_Etalon(IlvDisplay* display,
                    const char* name,
                    const char* title,
					AdxInterface* m_interface,
                    IlvRect*    size            = 0,
                    IlvBoolean  useAccelerators = IlvFalse,
                    IlvBoolean  visible         = IlvFalse,
                    IlvUInt     properties      = 0,
                    IlvSystemView transientFor  = 0)
      : Pesee_Etalon(display,
                     name,
                     title,
                     size,
                     useAccelerators,
                     visible,
                     properties,
                     transientFor)
        {init(m_interface);}
   /*
    AdxPesee_Etalon(IlvAbstractView* parent,
                    IlvRect* size = 0,
                    IlvBoolean useacc = IlvFalse,
                    IlvBoolean visible = IlvTrue)
      : Pesee_Etalon(parent,
                     size,
                     useacc,
                     visible)
        {}
    AdxPesee_Etalon(IlvDisplay* display,
                    IlvSystemView parent,
                    const IlvRect& rect,
                    IlvBoolean useacc = IlvFalse,
                    IlvBoolean visible = IlvTrue)
      : Pesee_Etalon(display, parent, rect, useacc, visible)
        {}
	*/
    // ____________________________________________________________
    virtual void validerCB(IlvGraphic*);
	virtual void peserCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void poidsPeseCB(IlvGraphic*);
    virtual void mettreAZeroCB(IlvGraphic*);
    virtual void tactileCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void listerEtalonCB(IlvGraphic*);
	virtual void EntreeNumberFieldCB(IlvGraphic* g);

	void quitter();
	void reaffichage();
	void afficherEtalonLigne();
	void afficherPesee();
	void chargement();
	CString formatMessage(CString texte);
	void evolutionPoids();
	void adaptationEchelle();
//	void setChampsAlphaEditable(bool editable);
	bool envoieMessage(CString mess, bool OUINON);


	AdxInterface* getInterface() {return _interface;};

	AdxInterface*		_interface;
	AdxBalance*			_balance;

	bool                _miseAZeroOK;
	bool                _peseeOK;
	bool                _etalonnageOK;

	bool                _attentePesee;
	bool				_balanceBegin;

// zones de calcul des poids de la transaction de pesee


	double				_poidsPese;
	double				_poidsAPeser;
	double				_poidsPeseTotal;
	double				_TotalAPeserInitial;
	double				_ecartPoids;
	double				_tolerance;

	void init(AdxInterface* m_interface);
	bool initClavier_Tactile();

// gbe 10.08 pour savoir quand on est en pesée
	bool				_enPesee;
};
#endif
