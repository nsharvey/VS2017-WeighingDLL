// AdxPhrase_Secu.h
// ----------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#ifndef __AdxPhrase_Secu__header__
#define __AdxPhrase_Secu__header__

#include "phrase_Secu.h"

class AdxInterface;
class AdxPesee_OF;

class AdxPhrase_Secu
: public Phrase_Secu {
public:
   AdxPhrase_Secu(IlvDisplay* display,
                       const char* name,
                       const char* title,
					   AdxInterface* m_interface,
                       IlvRect*    size            = 0,
                       IlvBoolean  useAccelerators = IlvFalse,
                       IlvBoolean  visible         = IlvFalse,
                       IlvUInt     properties      = 0,
                       IlvSystemView transientFor  = 0)
      : Phrase_Secu(display,
                        name,
                        title,
                        size,
                        useAccelerators,
                        visible,
                        properties,
                        transientFor)
        {init(m_interface);}
/*
    AdxPhrase_Secu(IlvAbstractView* parent,
					   AdxInterface* m_interface,
                       IlvRect* size = 0,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Phrase_Secu(parent,
                        size,
                        useacc,
                        visible)
        {init(m_interface);}

    AdxPhrase_Secu(IlvDisplay* display,
                       IlvSystemView sview,
					   AdxInterface* m_interface,
                       IlvBoolean useacc = IlvFalse)
      : Phrase_Secu(display, sview, useacc)
        {init(m_interface);}
    AdxPhrase_Secu(IlvDisplay* display,
                       IlvSystemView parent,
                       const IlvRect& rect,
					   AdxInterface* m_interface,
                       IlvBoolean useacc = IlvFalse,
                       IlvBoolean visible = IlvTrue)
      : Phrase_Secu(display, parent, rect, useacc, visible)
        {init(m_interface);}
*/
//--------------------------------------------------------------
    virtual void monterCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void descendreCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
	AdxInterface* getInterface() {return _interface;};
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}

protected:
	AdxInterface*				_interface;
	AdxGadgetContainer*			_panneauAppelant;
	void quitter();
	void init(AdxInterface* m_interface);

};
#endif
