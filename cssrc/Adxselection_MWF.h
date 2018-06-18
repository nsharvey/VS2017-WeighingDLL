// AdxSelection_MWF.h
// ------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#ifndef __Adxselection_MWF__header__
#define __Adxselection_MWF__header__

#include "selection_MWF.h"

class AdxInterface;

class AdxSelection_MWF
: public Selection_MWF {
public:
   AdxSelection_MWF(IlvDisplay* display,
                     const char* name,
                     const char* title,
					 AdxInterface* m_interface,
                     IlvRect*    size            = 0,
                     IlvBoolean  useAccelerators = IlvFalse,
                     IlvBoolean  visible         = IlvFalse,
                     IlvUInt     properties      = 0,
                     IlvSystemView transientFor  = 0)
      : Selection_MWF(display,
                      name,
                      title,
                      size,
                      useAccelerators,
                      visible,
                      properties,
                      transientFor)
        {init(m_interface);}
/*
    AdxSelection_MWF(IlvAbstractView* parent,
					 AdxInterface* m_interface,
                     IlvRect* size = 0,
                     IlvBoolean useacc = IlvFalse,
                     IlvBoolean visible = IlvTrue)
      : Selection_MWF(parent,
                      size,
                      useacc,
                      visible)
        {init(m_interface);}
    AdxSelection_MWF(IlvDisplay* display,
                     IlvSystemView sview,
					 AdxInterface* m_interface,
                     IlvBoolean useacc = IlvFalse)
      : Selection_MWF(display, sview, useacc)
        {init(m_interface);}
    AdxSelection_MWF(IlvDisplay* display,
                     IlvSystemView parent,
                     const IlvRect& rect,
					 AdxInterface* m_interface,
                     IlvBoolean useacc = IlvFalse,
                     IlvBoolean visible = IlvTrue)
      : Selection_MWF(display, parent, rect, useacc, visible)
        {init(m_interface);}
*/
//--------------------------------------------------------------
    virtual void monterCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
	void setListeSelectionMWF(int index);
	void selectionSuivante();
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	void clearMatrix();
	void loadMatrix();
	//void loadLine(int ,char*, char* ,char* ,double , double);			// mm 03.2013 Performances
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
