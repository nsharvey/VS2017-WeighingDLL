// AdxSelection_EtalonLigne.h
// --------------------------
// project : Adonix X3 Scales
// author : SR
// V130 : SR 2001.12.10

#ifndef __Adxselection_EtalonLigne__header__
#define __Adxselection_EtalonLigne__header__

#include "selection_EtalonLigne.h"

class AdxInterface;

class AdxSelection_EtalonLigne
: public Selection_EtalonLigne {
public:
   AdxSelection_EtalonLigne(IlvDisplay* display,
                             const char* name,
                             const char* title,
							 AdxInterface* m_interface,
                             IlvRect*    size            = 0,
                             IlvBoolean  useAccelerators = IlvFalse,
                             IlvBoolean  visible         = IlvFalse,
                             IlvUInt     properties      = 0,
                             IlvSystemView transientFor  = 0)
      : Selection_EtalonLigne(display,
                              name,
                              title,
                              size,
                              useAccelerators,
                              visible,
                              properties,
                              transientFor)
        {init(m_interface);}
   /*
    AdxSelection_EtalonLigne(IlvAbstractView* parent,
                             IlvRect* size = 0,
                             IlvBoolean useacc = IlvFalse,
                             IlvBoolean visible = IlvTrue)
      : Selection_EtalonLigne(parent,
                              size,
                              useacc,
                              visible)
        {}
    AdxSelection_EtalonLigne(IlvDisplay* display,
                             IlvSystemView parent,
                             const IlvRect& rect,
                             IlvBoolean useacc = IlvFalse,
                             IlvBoolean visible = IlvTrue)
      : Selection_EtalonLigne(display, parent, rect, useacc, visible)
        {}
	*/
    // ____________________________________________________________
    virtual void descendreCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
    virtual void monterCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);

	void setListeSelectionEtalonLigne(int index);
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	void clearMatrix();
	void loadMatrix();
	virtual void handleInput(IlvEvent& event);

protected:
// index de la ligneetalon de la premiere ligne de la matrice dans la liste AdxCurrentEtalon()->_etalonLigneList
	AdxInterface*				_interface;
	int							_n1;
	AdxGadgetContainer*			_panneauAppelant;
	void quitter();
	void init(AdxInterface* m_interface);
	IlvUShort                   _nbDsiplayRows;
};
#endif

