// AdxAccueil.h
// ------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#ifndef __Adxaccueil__header__
#define __Adxaccueil__header__

#include <ilviews/bitmaps/jpg.h>
#include <ilviews/bitmaps/bmp.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/graphics/rectangl.h>
#include <ilviews/gadgets/datfield.h>
#include "accueil.h"

class AdxDate;

class AdxAccueil
: public Accueil {
public:
   AdxAccueil(IlvDisplay* display,
               const char* name,
               const char* title,
			   AdxInterface* m_interface,
               IlvRect*    size            = 0,
               IlvBoolean  useAccelerators = IlvFalse,
               IlvBoolean  visible         = IlvFalse,
               IlvUInt     properties      = 0,
               IlvSystemView transientFor  = 0)
      : Accueil(display,
                name,
                title,
				size,
                useAccelerators,
                visible,
                properties,
                transientFor)
        {init(m_interface);}

	AdxAccueil(	  IlvDisplay* display,
				  IlvSystemView sview,
				  AdxInterface* m_interface,
				  IlvBoolean useacc = IlvFalse)
	  : Accueil(display, sview, useacc)
        {init(m_interface);}

    ~AdxAccueil()
	{}
//--------------------------------------------------------------
    virtual void quitterCB(IlvGraphic*);
    virtual void peserOFCB(IlvGraphic*);
    virtual void peserFabricationCB(IlvGraphic*);
    virtual void testerBalanceCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void peserArticleCB(IlvGraphic*);
	virtual void reconcilierCB(IlvGraphic*);
	// sr 11.02 réactualisation des données
	virtual void refreshCB(IlvGraphic*);
	void showDate(AdxDate* date,IlvDateField* dfield);
	IlvRectangle* getAccueilRectangle() const
		{ return (IlvRectangle*)getObject("accueil"); }
 	void quitter();
	void afficherPoste();
	void reafficherBalances();
	void lancerPesee();
	AdxInterface* getInterface() {return _interface;};
	bool envoieMessage(CString mess, bool OUINON);
	void setNbConnecte(const int value) {_nbConnecte = value;}		// 11.07 mm 
	int  getNbConnecte (){ return _nbConnecte;}		// 11.07 mm 

	int _nbConnecte ;	// 11.07 mm 
	bool _balanceEtalonne ;	//03.09 mm
	virtual void show();
protected:
	void init(AdxInterface* m_interface);
	AdxInterface* _interface;
};
#endif
