// AdxMessage.cpp
// --------------
// project : Adonix X3 Centrale de Pesee
// author : EP		28/05/01
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "Adxmessage.h"
#include "AdxData.h"
#include "AdxPesee_OF.h"
#include "AdxPesee_Etalon.h"

class AdxInterface;
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void AdxMessage::BoutonCB(IlvGraphic* g)
{
	if (g == getBoutonOui() || g == getBoutonOK())
	{
		_reponse = IlvTrue;
	}
	else
		_reponse = IlvFalse;
	quitter();
}

//---------------------------------------------------------------------------
void AdxMessage::quitter()
{
 	hide();

// llc 04.02, faire reDraw() à la place de show()
	if (_panneauAppelant != NULL)
	{
		if (_panneauAppelant == getInterface()->getPesee_OF())
			_panneauAppelant->reDraw();
		if (_panneauAppelant == getInterface()->getPesee_Etalon())
			_panneauAppelant->reDraw();
	}
}

//---------------------------------------------------------------------------
void AdxMessage::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	_messageType = 0;

	IlvRect bbox;
	boundingBox(bbox);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();

	setMinimumSize (sizeScreenW, bbox.h());
	setMaximumSize (sizeScreenW, bbox.h());
}
