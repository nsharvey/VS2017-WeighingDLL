// AdxSelection_Balance.cpp
// ------------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "AdxSelection_Balance.h"
#include "AdxBalance.h"

#include "AdxInterface.h"
#include "AdxChoix_OF.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_LOT.h"
#include "AdxPesee_OF.h"
#include "AdxOrder.h"
#include "AdxData.h"
#include "AdxDate.h"

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxSelection_Balance::monterCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionBalance()->firstRow();
// si index premiere balance de la matrice < 8 positionnement sur premiere balance
	if (_n1 < 9)
		setListeSelectionBalance(0);
	else
// sinon remonter de 8
		setListeSelectionBalance(_n1 - 8);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::descendreCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionBalance()->firstRow();
// s'il y a des balances sur l'ecran suivant
	if (_n1 < (getInterface()->getDonnees()->getNbBalances() - 8))
		setListeSelectionBalance(_n1 + 8);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::validerCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxPesee_OF* pesee_OF = m_interface->getPesee_OF();
	IlvUShort c;
	IlvUShort r;
	if (getlisteSelectionBalance()->getFirstSelected(c,r))
	{
		// _n1 (numero de la premiere balance du tableau) 
		// + r (numero de ligne selectionnee commence a 1) - 1
		if (r-1 < m_interface->getDonnees()->getNbBalances())		
		{
			if (_panneauAppelant == pesee_OF)
			{
				if (pesee_OF->getSaisieBalance()->isEditable())
				{
					AdxBalance* balanceSvg = pesee_OF->_balanceChoisie;
					IlList* balanceList = m_interface->getDonnees()->getBalanceList();
					pesee_OF->_balanceChoisie = (AdxBalance*)(*balanceList)[r-1];
					if (pesee_OF->controleBalance(true))
					{
						// mm 02.09 - changement de balance : on recommence le tarage avec la nouvelle balance !
						if (balanceSvg->getBalance() != pesee_OF->_balanceChoisie->getBalance()) 
							pesee_OF->_poidsTare = 0 ;					
						pesee_OF->getSaisieBalance()->setLabel(
							pesee_OF->_balanceChoisie->getBalance());
						pesee_OF->getLibSaisieBalance()->setLabel(
							pesee_OF->_balanceChoisie->getLibBalance());
						pesee_OF->suiteChoixBalance();
					}
					else
					{
						pesee_OF->_balanceChoisie = balanceSvg;
					}
				}
			}
		}
	}
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxSelection_Balance* m_selection_Balance = m_interface->getSelection_Balance();

 	m_selection_Balance->hide();
	_panneauAppelant->show();
}
void AdxSelection_Balance::clearMatrix()
{
	// On vide la matrice si besoin
	IlvUShort wnNbRow = this->getlisteSelectionBalance()->rows();
	if(wnNbRow>0)
	{
		// suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getlisteSelectionBalance()->removeRow(wni);
		}
	}
}
void AdxSelection_Balance::loadMatrix()
{
	char* szTemp   = new char[40];
	IlvUShort wnNbBalance = getInterface()->getDonnees()->getNbBalances();
	IlvLabelMatrixItem* item = NULL;
	IlList* balanceList = getInterface()->getDonnees()->getBalanceList();
	IlvUShort wnj = 0; // index des balances !
	IlvDim rowHeight = 0;

	// On recr� les row 
	getlisteSelectionBalance()->insertRow(1,wnNbBalance);
	IlvRect matrixBBox;

	getlisteSelectionBalance()->boundingBox(matrixBBox,this->getTransformer());
	rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
    getlisteSelectionBalance()->sameHeight(IlvTrue);
	getlisteSelectionBalance()->setYgrid(rowHeight);

	for ( int i = 1; i <= wnNbBalance; i++)
	{
		// pour compenser le fait que la premi�re ligne de la liste est
		// une ligne de libell�.
		wnj = i-1;
		//--------

		AdxBalance* balance = (AdxBalance*)(*balanceList)[wnj];

		item = new IlvLabelMatrixItem(balance->getBalance());
		getlisteSelectionBalance()->set(0,i,item);

		item = new IlvLabelMatrixItem(balance->getLibBalance());
		getlisteSelectionBalance()->set(1,i,item);

		sprintf (szTemp, "%.3f", balance->getPorteeMini());
		item = new IlvLabelMatrixItem(szTemp);
		getlisteSelectionBalance()->set(2,i,item);

		sprintf (szTemp, "%.3f", balance->getPorteeMaxi());
		item = new IlvLabelMatrixItem(szTemp);
		getlisteSelectionBalance()->set(3,i,item);

		sprintf (szTemp, "%.3f", balance->getTareMaxi());
		item = new IlvLabelMatrixItem(szTemp);
		getlisteSelectionBalance()->set(4,i,item);

		item = new IlvLabelMatrixItem(balance->getUnite());
		getlisteSelectionBalance()->set(5,i,item);
	}
	getlisteSelectionBalance()->deSelect();
	for(IlvUShort wni = 0;wni<getlisteSelectionBalance()->columns();wni++)
	{
		// On boucle sur tous les rows de la colonne pour connaitre le plus long
		IlvDim maxColWidth = getlisteSelectionBalance()->getColumnFittingSize(wni);
		getlisteSelectionBalance()->setColumnSize(wni,maxColWidth+10);
	}
	delete [] szTemp;
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fen�tres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	getlisteSelectionBalance()->showScrollBar(IlvHorizontal);
	getlisteSelectionBalance()->showScrollBar(IlvVertical);

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

// redimensionne la largeur des colonnes (122 par d�faut)
	//IlvMatrix* matrix = getlisteSelectionBalance();
	//matrix->resizeColumn(1,100);
	//matrix->resizeColumn(2,190);
	//matrix->resizeColumn(3,127);
	//matrix->resizeColumn(4,127);
	//matrix->resizeColumn(5,127);
	//matrix->resizeColumn(6,61);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
	//setMaximumSize (sizeScreenW, sizeScreenH);
}

//---------------------------------------------------------------------------
void AdxSelection_Balance::setListeSelectionBalance(int index)
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
	getlisteSelectionBalance()->scrollToRow(index);
}

void AdxSelection_Balance::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// Si on se trouve sur la matrice, on r�percute le mouse wheel
			// et on enregistre le premier �l�ment affich� dans _n1
			Selection_Balance::handleInput(event);
			_n1 = this->getlisteSelectionBalance()->firstRow();
			break;
		case IlvDoubleClick:
			// Si on se trouve sur la matrice, on prends la ligne en cours
			if(getlisteSelectionBalance()->pointToPosition(event.getLocation(),
													  col,
													  row,
													  this->getTransformer()))
			{
				if(row != 0)
				{
					hide();
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
            Selection_Balance::handleInput(event);
			break;
		default:
			Selection_Balance::handleInput(event);
			break;
	}
}