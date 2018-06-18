// AdxSelection_OF.h
// -----------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#ifndef __Adxselection_OF__header__
#define __Adxselection_OF__header__

//#include <ilviews/gadgets/datfield.h>
#include "selection_OF.h"

class AdxInterface;

class AdxSelection_OF
: public Selection_OF {
public:
   AdxSelection_OF(IlvDisplay* display,
                    const char* name,
                    const char* title,
					AdxInterface* m_interface,
                    IlvRect*    size            = 0,
                    IlvBoolean  useAccelerators = IlvFalse,
                    IlvBoolean  visible         = IlvFalse,
                    IlvUInt     properties      = 0,
                    IlvSystemView transientFor  = 0)
      : Selection_OF(display,
                     name,
                     title,
                     size,
                     useAccelerators,
                     visible,
                     properties,
                     transientFor)
        {init(m_interface);}
/*
    AdxSelection_OF(IlvDisplay* display,
				  IlvSystemView sview,
				  AdxInterface* m_interface,
				  IlvBoolean useacc = IlvFalse)
	  : Selection_OF(display, sview, useacc)
        {init(m_interface);}

    AdxSelection_OF(IlvAbstractView* parent,
                    IlvRect* size = 0,
                    IlvBoolean useacc = IlvFalse,
                    IlvBoolean visible = IlvTrue)
      : Selection_OF(parent,
                     size,
                     useacc,
                     visible)
        {}
*/
//--------------------------------------------------------------
    virtual void validerCB(IlvGraphic*);
    virtual void monterCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
	bool setListeSelectionOF(int index);
	void selectionSuivante();
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	void clearMatrix();
	bool loadMatrix();
	virtual void handleInput(IlvEvent& event);


protected:
// index de l'OF de la premiere ligne de la matrice dans la liste AdxData->_orderList
	AdxInterface*				_interface;
	int							_n1;
	AdxGadgetContainer*			_panneauAppelant;
	void quitter();
	void init(AdxInterface* m_interface);
	IlvUShort                   _nbDsiplayRows;

};
#endif
