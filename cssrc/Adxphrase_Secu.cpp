// AdxPhrase_Secu.cpp
// ------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#include "stdafx.h"
#include "AdxPhrase_Secu.h"

#include "AdxInterface.h"
#include "AdxPesee_OF.h"
#include "AdxData.h"
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxPhrase_Secu::monterCB(IlvGraphic* g)
{
}

//---------------------------------------------------------------------------
void AdxPhrase_Secu::descendreCB(IlvGraphic* g)
{
}

//---------------------------------------------------------------------------
void AdxPhrase_Secu::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxPhrase_Secu::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxPhrase_Secu::quitter()
{
	AdxInterface* m_interface = this->getInterface();
	AdxPhrase_Secu* m_phrase_Secu = m_interface->getPhrase_Secu();

 	m_phrase_Secu->hide();
	_panneauAppelant->show();
}

//---------------------------------------------------------------------------
void AdxPhrase_Secu::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	char szFileIcons[_MAX_PATH];

	// bouton sécurité
	sprintf (szFileIcons, "%s\\defaut.jpg",
		_interface->getPathCACHE());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	getsecu()->setBitmap(bitmap);

	// bouton Descendre
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowdown.png",
		_interface->getPathX3());
	bitmap =	getDisplay()->readBitmap(szFileIcons);
	getDescendre()->setBitmap(bitmap);

	// bouton Monter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowup.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getMonter()->setBitmap(bitmap);

	// bouton Aide
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\question_mark.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getAide()->setBitmap(bitmap);

	// bouton Quitter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getQuitter()->setBitmap(bitmap);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
	//setMaximumSize (sizeScreenW, sizeScreenH);

	// masque boutons monter et descendre
    setVisible(getDescendre(),IlvFalse, IlvFalse);
    setVisible(getMonter(),IlvFalse, IlvFalse);
}
