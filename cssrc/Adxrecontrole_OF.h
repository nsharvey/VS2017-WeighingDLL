// AdxRecontrole_OF.h
// ------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#ifndef __AdxRecontrole_OF__header__
#define __AdxRecontrole_OF__header__

#include "recontrole_OF.h"

class AdxInterface;
class AdxPesee_OF;
class AdxBalance; //APCPRD-2636 mm 08.2013

class AdxRecontrole_OF
: public Recontrole_OF {
public:
   AdxRecontrole_OF(IlvDisplay* display,
                       const char* name,
                       const char* title,
					   AdxInterface* m_interface,
                       IlvRect*    size            = 0,
                       IlvBoolean  useAccelerators = IlvFalse,
                       IlvBoolean  visible         = IlvFalse,
                       IlvUInt     properties      = 0,
                       IlvSystemView transientFor  = 0)
      : Recontrole_OF(display,
                        name,
                        title,
                        size,
                        useAccelerators,
                        visible,
                        properties,
                        transientFor)
        {init(m_interface);}
/*
    AdxRecontrole_OF(IlvAbstractView* parent,
					   AdxInterface* m_interface,
                       IlvRect* size = 0,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Recontrole_OF(parent,
                        size,
                        useacc,
                        visible)
        {init(m_interface);}

    AdxRecontrole_OF(IlvDisplay* display,
                       IlvSystemView sview,
					   AdxInterface* m_interface,
                       IlvBoolean useacc = IlvFalse)
      : Recontrole_OF(display, sview, useacc)
        {init(m_interface);}
    AdxRecontrole_OF(IlvDisplay* display,
                       IlvSystemView parent,
                       const IlvRect& rect,
					   AdxInterface* m_interface,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Recontrole_OF(display, parent, rect, useacc, visible)
        {init(m_interface);}
*/
//--------------------------------------------------------------
    virtual void ValiderCB(IlvGraphic*);
    virtual void QuitterCB(IlvGraphic*);
    virtual void TactileCB(IlvGraphic*);
    virtual void SaisieComposantCB(IlvGraphic*);
    virtual void SaisieLotCB(IlvGraphic*);
	virtual void SaisieSousLotCB(IlvGraphic*);		//  mm 03.10 - modification du recontrole OF
	virtual void EntreeTextFieldCB(IlvGraphic* g);
	virtual void SaisiContenuCabCB(IlvGraphic* g);
	bool controleComposant();
	bool controleLot();
	bool controleSousLot() ;			//  mm 03.10 - modification du recontrole OF
	// mm 01.2015 - Lecture CAB et recontrole OF
	void alimentationZones(char *, char *, char *);
	void alimentationZonesLF(int , int , int);
	void suppressionBlancs(char **, char **, char **);
	void controleValiditeZones();
	void validiteComposantKo(char **);
	void validiteLotKo(char **);
	void validiteSloKo(char **);
	void validiteComposantLotKO(char **);
	void validiteLotSloKo(char **);
	void validiteComposantSloKo(char **);
	void validiteComposantLotSloKO(char **);
	void reinitialiseEcran();
	void separateurNonTrouve();
	//
	void setComposantOK(bool composantOK) { _composantOK = composantOK;}
	bool getComposantOK() const { return _composantOK;}
	void setLotOK(bool lotOK) { _lotOK = lotOK;}
	bool getLotOK() const { return _lotOK;}
	void setSousLotOK(bool souslotOK) { _souslotOK = souslotOK; }
	bool getSousLotOK() const { return _souslotOK ; }
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	void retourOK();
	void quitter();

protected:
	bool						_composantOK;
	bool						_lotOK;
	bool						_souslotOK ;	// mm 03.10 - modification du recontrôle
	bool						_controleFait;
	AdxInterface*				_interface;
	AdxGadgetContainer*			_panneauAppelant;
//	void quitter();
	void init(AdxInterface* m_interface);
	void initClavier_Tactile();

};
#endif
