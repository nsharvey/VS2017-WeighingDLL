// AdxSelection_EtalonLigne.cpp
// ----------------------------
// project : Adonix X3 Scales
// author : SR
// V130 : SR 2001.12.10
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "Adxselection_EtalonLigne.h"
#include "AdxEtalon.h"
#include "AdxEtalonLigne.h"

#include "AdxInterface.h"
#include "AdxPesee_Etalon.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxData.h"

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::monterCB(IlvGraphic* g)
{
	_n1 = this->getListeSelectionLigne()->firstRow();
// si index premiere ligne de la matrice < 8 positionnement sur premiere ligne
	if (_n1 < 9)
		setListeSelectionEtalonLigne(0);
	else
// sinon remonter de 8
		setListeSelectionEtalonLigne(_n1 - 8);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::descendreCB(IlvGraphic* g)
{
	_n1 = this->getListeSelectionLigne()->firstRow();
// s'il y a des lignes sur l'ecran suivant
	if (_n1 < (getInterface()->getDonnees()->getCurrentEtalon()->getNbLignes() - 8))
		setListeSelectionEtalonLigne(_n1 + 8);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::validerCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	IlvUShort c;
	IlvUShort r;
	if (getListeSelectionLigne()->getFirstSelected(c,r))
	{
		// _n1 (numero de la premiere ligne du tableau) 
		// + r (numero de ligne selectionnee commence a 1) - 1
		if (r-1 < getInterface()->getDonnees()->getCurrentEtalon()->getNbLignes())		
		{
     		m_interface->getDonnees()->getCurrentEtalon()->setCurrentEtalonLigneIndex(r-1);
		}
	}
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxSelection_EtalonLigne* m_selection_EtalonLigne = 
		m_interface->getSelection_EtalonLigne();
 	m_selection_EtalonLigne->hide();
	_panneauAppelant->show();
}
void AdxSelection_EtalonLigne::clearMatrix()
{
	// On vide la matrice si besoin
	IlvUShort wnNbRow = this->getListeSelectionLigne()->rows();
	if(wnNbRow>0)
	{
		// suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getListeSelectionLigne()->removeRow(wni);
		}
	}
}
void AdxSelection_EtalonLigne::loadMatrix()
{
	char* szTemp   = new char[40];
	IlvUShort wnNbEtalon = getInterface()->getDonnees()->getCurrentEtalon()->getNbLignes();
	IlvLabelMatrixItem* item = NULL;
	IlList* EtalonLigneList = getInterface()->getDonnees()->getCurrentEtalon()->getEtalonLigneList();
	IlvUShort wnj = 0; // index des ordres !
	IlvDim rowHeight = 0;

	// On recré les row 
	getListeSelectionLigne()->insertRow(1,wnNbEtalon);
	IlvRect matrixBBox;

	getListeSelectionLigne()->boundingBox(matrixBBox,this->getTransformer());
	rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
    getListeSelectionLigne()->sameHeight(IlvTrue);
	getListeSelectionLigne()->setYgrid(rowHeight);

	for ( int i = 1; i <= wnNbEtalon; i++)
	{
		// pour compenser le fait que la première ligne de la liste est
		// une ligne de libellé.
		wnj = i-1;
		//--------

		AdxEtalonLigne* etalonLigne = (AdxEtalonLigne*)(*EtalonLigneList)[wnj];

		sprintf (szTemp, "%.3f",etalonLigne->getPoids());
		item = new IlvLabelMatrixItem(szTemp);
		getListeSelectionLigne()->set(0,i,item);

		item = new IlvLabelMatrixItem(etalonLigne->getLibTypPesee());
		getListeSelectionLigne()->set(1,i,item);

	}
	getListeSelectionLigne()->deSelect();
	for(IlvUShort wni = 0;wni<getListeSelectionLigne()->columns();wni++)
	{
		// On boucle sur tous les rows de la colonne pour connaitre le plus long
		IlvDim maxColWidth = getListeSelectionLigne()->getColumnFittingSize(wni);
		getListeSelectionLigne()->setColumnSize(wni,maxColWidth+10);
	}
	delete [] szTemp;
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	getListeSelectionLigne()->showScrollBar(IlvHorizontal);
	getListeSelectionLigne()->showScrollBar(IlvVertical);

	_nbDsiplayRows = 9;

	char szFileIcons[_MAX_PATH];

	// bouton valider
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	IlvBitmap* bitmap = getDisplay()->readBitmap(szFileIcons);
	getvalider()->setBitmap(bitmap);

	// bouton Descendre
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowdown.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getdescendre()->setBitmap(bitmap);

	// bouton Monter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowup.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getmonter()->setBitmap(bitmap);

	// bouton Aide
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\question_mark.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getaide()->setBitmap(bitmap);

	// bouton Quitter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getquitter()->setBitmap(bitmap);

// redimensionne la largeur des colonnes (122 par défaut)

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
//	setMaximumSize (sizeScreenW, bbox.h());
	//setMaximumSize (sizeScreenW, sizeScreenH);
}

//---------------------------------------------------------------------------
void AdxSelection_EtalonLigne::setListeSelectionEtalonLigne(int index)
{
	_n1 = index;
	if(index <0)
	{
		_n1 = 0;
	}

	// purge de la matrice
	this->clearMatrix();
	// chargement de la matrice 
	this->loadMatrix();
	getListeSelectionLigne()->scrollToRow(index);

}

void AdxSelection_EtalonLigne::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// Si on se trouve sur la matrice, on répercute le mouse wheel
			// et on enregistre le premier élément affiché dans _n1
			Selection_EtalonLigne::handleInput(event);
			_n1 = this->getListeSelectionLigne()->firstRow();
			break;
		case IlvDoubleClick:
			// Si on se trouve sur la matrice, on prends la ligne en cours
			if(getListeSelectionLigne()->pointToPosition(event.getLocation(),
													  col,
													  row,
													  this->getTransformer()))
			{
				if(row != 0)
				{
					this->validerCB(NULL);
				}
			}
			break;
		case IlvButtonDown:
			if (event.button() == IlvLeftButton)				
			{
			}
            if (event.button() == IlvRightButton)
            {
            }
            Selection_EtalonLigne::handleInput(event);
			break;
		default:
			Selection_EtalonLigne::handleInput(event);
			break;
	}
}

