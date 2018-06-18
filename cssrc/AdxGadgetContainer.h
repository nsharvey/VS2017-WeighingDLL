// AdxGadgetContainer.h
// --------------------
// project : Adonix X3 Centrale de Pesee
// author : EP		28/05/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant les Gadget Container chez Adonix
//--------------------------------------------------------------
#ifndef __adxGadgetContainer__header__
#define __adxGadgetContainer__header__

//#include <ilviews/gadgets/numfield.h>
//#include <ilviews/gadgets/msglabel.h>
//#include <ilviews/graphics/zicon.h>
#include <ilviews/gadgets/textfd.h>
#include <ilviews/gadgets/gadcont.h>
#include <ilviews/graphics/zicon.h>
#include "stdafx.h"
//#include "AdxInterface.h"

class AdxInterface;

//--------------------------------------------------------------
class AdxGadgetContainer
: public IlvGadgetContainer {
public:
	
    AdxGadgetContainer(IlvDisplay*    display,
		       const char*    name,
		       const char*    title,
                       const IlvRect& rect,
                       IlvBoolean     useacc = IlvFalse,
                       IlvBoolean     visible = IlvTrue)
		: IlvGadgetContainer(display,
							 name,
							 title,
							 rect,
							 useacc ,
							 visible)
	{
		init();
	}

    AdxGadgetContainer(IlvDisplay*    display,
		       const char*    name,
		       const char*    title,
                       const IlvRect& rect,
		       IlvUInt        properties,
                       IlvBoolean     useacc       = IlvFalse,
                       IlvBoolean     visible      = IlvTrue,
		       IlvSystemView  transientFor = 0)
		: IlvGadgetContainer( display,
							  name,
							  title,
							  rect,
							  properties,
						      useacc ,
                              visible ,
							  transientFor )
	{
		init();
	}

    AdxGadgetContainer(IlvAbstractView* parent,
                       const IlvRect&   rect,
                       IlvBoolean       useacc  = IlvFalse,
                       IlvBoolean       visible = IlvTrue)
		: IlvGadgetContainer(parent,
							 rect,
                             useacc ,
                             visible)
	{
		init();
	}

    AdxGadgetContainer(IlvDisplay*    display,
                       IlvSystemView  parent,
                       const IlvRect& rect,
                       IlvBoolean     useacc  = IlvFalse,
                       IlvBoolean     visible = IlvTrue)
		: IlvGadgetContainer( display,
							  parent,
							  rect,
                              useacc ,
                              visible)
	{
		init();
	}

    AdxGadgetContainer(IlvDisplay*   display,
		       IlvSystemView window,
                       IlvBoolean    useacc = IlvFalse)
		: IlvGadgetContainer( display,
							  window,
                              useacc)
    {
		init();
	}
//--------------------------------------------------------------
AdxInterface* getInterface () const {return _interface;}
void setChampAppelant(IlvTextField* champ) { _champAppelant = champ;}  
IlvTextField* getChampAppelant()const {return _champAppelant;}
void setBoutonAppelant(IlvZoomableTransparentIcon* bouton) { _boutonAppelant = bouton;}  
IlvZoomableTransparentIcon* getBoutonAppelant()const {return _boutonAppelant;}
//bool envoieMessage(CString mess, bool OUINON);
// gbe test
virtual void show();
virtual void hide();
IlvBoolean IsDisplayed();

// GBE 19/04/20013
// Fonction pour supprimer le bouton de fermeture de la fenêtre
void disableTitleBarButtons();
// Fin GBE 19/04/2013

private:
void init();
protected:
	AdxInterface*			_interface;
	IlvTextField*			_champAppelant;
	IlvZoomableTransparentIcon*		_boutonAppelant;
	void init(AdxInterface* m_interface);
	IlvBoolean				_displayed;
};

#endif /* !__adxGadgetContainer__header__*/
