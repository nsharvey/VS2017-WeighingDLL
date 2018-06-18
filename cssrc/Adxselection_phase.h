// AdxSelection_Phase.h
// --------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#ifndef __AdxSelection_Phase__header__
#define __AdxSelection_Phase__header__

#include "selection_phase.h"

class AdxInterface;
class AdxChoix_OF;
class AdxSelection_MWF;

class AdxSelection_Phase
: public Selection_phase {
public:
   AdxSelection_Phase(IlvDisplay* display,
                       const char* name,
                       const char* title,
					   AdxInterface* m_interface,
                       IlvRect*    size            = 0,
                       IlvBoolean  useAccelerators = IlvFalse,
                       IlvBoolean  visible         = IlvFalse,
                       IlvUInt     properties      = 0,
                       IlvSystemView transientFor  = 0)
      : Selection_phase(display,
                        name,
                        title,
                        size,
                        useAccelerators,
                        visible,
                        properties,
                        transientFor)
        {init(m_interface);}
/*
    AdxSelection_Phase(IlvAbstractView* parent,
					   AdxInterface* m_interface,
                       IlvRect* size = 0,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Selection_phase(parent,
                        size,
                        useacc,
                        visible)
        {init(m_interface);}
    AdxSelection_Phase(IlvDisplay* display,
                       IlvSystemView sview,
					   AdxInterface* m_interface,
                       IlvBoolean useacc = IlvFalse)
      : Selection_phase(display, sview, useacc)
        {init(m_interface);}
    AdxSelection_Phase(IlvDisplay* display,
                       IlvSystemView parent,
                       const IlvRect& rect,
					   AdxInterface* m_interface,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Selection_phase(display, parent, rect, useacc, visible)
        {init(m_interface);}
*/
//--------------------------------------------------------------
    virtual void monterCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
	void setListeSelectionPhase(int index);
	void selectionSuivante();
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	void clearMatrix();
	void loadMatrix();
	virtual void handleInput(IlvEvent& event);

protected:
// index de la Phase de la premiere ligne de la matrice dans la liste AdxData->_phaseList
	AdxInterface*				_interface;
	int							_n1;
	AdxGadgetContainer*			_panneauAppelant;
	void quitter();
	void init(AdxInterface* m_interface);
	IlvUShort                   _nbDsiplayRows;
};
#endif
