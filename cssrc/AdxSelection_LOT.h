// AdxSelection_LOT.h
// ------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#ifndef __AdxSelection_LOT__header__
#define __AdxSelection_LOT__header__

#include "selection_LOT.h"

class AdxInterface;

class AdxSelection_LOT
: public Selection_LOT {
public:
   AdxSelection_LOT(IlvDisplay* display,
                     const char* name,
                     const char* title,
					 AdxInterface* m_interface,
                     IlvRect*    size            = 0,
                     IlvBoolean  useAccelerators = IlvFalse,
                     IlvBoolean  visible         = IlvFalse,
                     IlvUInt     properties      = 0,
                     IlvSystemView transientFor  = 0)
      : Selection_LOT(display,
                      name,
                      title,
                      size,
                      useAccelerators,
                      visible,
                      properties,
                      transientFor)
        {init(m_interface);}

//--------------------------------------------------------------
	virtual ~AdxSelection_LOT();
    virtual void monterCB(IlvGraphic*);
    virtual void imprimerCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void desallouerCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void allouerCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
	virtual void consultationStockDetailleCB(IlvGraphic*);
	void setModifiable(bool b) { _modifiable = b;};
	bool getModifiable(){return _modifiable;};
	void chargement(bool modifiable);
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	bool envoieMessage(CString mess, bool OUINON);
	void clearMatrix();
	void loadMatrix();
	virtual void handleInput(IlvEvent& event);

protected:
// index du lot de la premiere ligne de la matrice dans la liste AdxData->_lotList
	AdxInterface*				_interface;
	int							_n1;
	IlList*						_lotListSvg;
	AdxGadgetContainer*			_panneauAppelant;
	bool						_modifiable;
	IlvMatrix*					_matriceCourante;
	void quitter();
	void init(AdxInterface* m_interface);
	void setListeSelectionLot(int index);
	void setField();
	void setButtons();
	void saveLotList();
	IlvMatrix* getMatriceCourante() {return	_matriceCourante;}
	void setMatriceCourante(IlvMatrix* matrice) {_matriceCourante = matrice;}
	IlvUShort                   _nbDsiplayRows;
};
#endif
