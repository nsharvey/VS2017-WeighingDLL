// AdxMessage.h
// ------------
// project : Adonix X3 Centrale de Pesee
// author : EP		28/05/01
//--------------------------------------------------------------
//
#ifndef __Adxmessage__header__
#define __Adxmessage__header__
#define LengthMaxMessage	124

#include "message.h"
#include "AdxInterface.h"

class AdxGadgetContainer;
//class AdxChoix_OF;

class AdxMessage
: public Message {
public:
   AdxMessage(IlvDisplay* display,
               const char* name,
               const char* title,
			   AdxInterface* m_interface,
               IlvRect*    size            = 0,
               IlvBoolean  useAccelerators = IlvFalse,
               IlvBoolean  visible         = IlvFalse,
               IlvUInt     properties      = 0,
               IlvSystemView transientFor  = 0)
      : Message(display,
                name,
                title,
                size,
                useAccelerators,
                visible,
                properties,
                transientFor)
        {init(m_interface);}
/*
    AdxMessage(IlvAbstractView* parent,
			   AdxInterface* m_interface,
               IlvRect* size = 0,
               IlvBoolean useacc = IlvFalse,
               IlvBoolean visible = IlvTrue)
      : Message(parent,
                size,
                useacc,
                visible)
        {init(m_interface);}
*/	
//--------------------------------------------------------------
    virtual void BoutonCB(IlvGraphic*);
	void setPanneauAppelant(AdxGadgetContainer* container)
		{_panneauAppelant = container;}
	bool getReponse(){return _reponse;};
	AdxInterface* getInterface() {return _interface;};
	int getMessageType(){return _messageType;};
	void setMessageType(int type){ _messageType = type;};

protected:
	void quitter();
	void init(AdxInterface* m_interface);
	AdxInterface*				_interface;
	AdxGadgetContainer*			_panneauAppelant;
	bool						_reponse;
	int							_messageType;
};
#endif
