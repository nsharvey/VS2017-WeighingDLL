// AdxSelection_Recipient.cpp
// --------------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "AdxSelection_Recipient.h"
#include "AdxRecipient.h"

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
void AdxSelection_Recipient::validerCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	IlvUShort c;
	IlvUShort r;
	
	if (getlisteSelectionRecipient()->getFirstSelected(c,r))
	{
		// _n1 (numero du premier recipient du tableau) 
		// + r (numero de ligne selectionnee commence a 1) - 1
		if (r-1 < getInterface()->getDonnees()->getNbRecipients())
		{
			if (_panneauAppelant == m_interface->getPesee_OF())
			{
				if (m_interface->getPesee_OF()->getSaisieRecipient()->isEditable())
				{
					AdxRecipient* recipientSvg = m_interface->getPesee_OF()->_recipientChoisi;
					bool recipientOKSvg = m_interface->getPesee_OF()->_recipientOK;
					// 11.07 mm - modif mode de pesee en emb.mixte 
					bool _peseeParEcartSvg = m_interface->getPesee_OF()->_peseeParEcart ;
					IlList* recipientList = 
						m_interface->getDonnees()->getRecipientList();
					m_interface->getPesee_OF()->_recipientChoisi = 
						(AdxRecipient*)(*recipientList)[r-1];
					if (m_interface->getPesee_OF()->controleRecipient())
					{
						m_interface->getPesee_OF()->getSaisieRecipient()->setLabel(
							m_interface->getPesee_OF()->_recipientChoisi->getRecipient());
						m_interface->getPesee_OF()->getLibSaisieRecipient()->setLabel(
							m_interface->getPesee_OF()->_recipientChoisi->getLibRecipient());
/*						m_interface->getPesee_OF()->setFocus(
							m_interface->getPesee_OF()->getSaisieRecipient());*/
/*						m_interface->getPesee_OF()->historisationChgtRecipient( 
							recipientSvg, 
							m_interface->getPesee_OF()->_recipientChoisi);*/
						m_interface->getPesee_OF()->suiteChoixRecipient();
					}
					else
					{
						m_interface->getPesee_OF()->_recipientChoisi = recipientSvg;
						m_interface->getPesee_OF()->_recipientOK = recipientOKSvg;
						// 11.07 mm - modif mode de pesee en emb.mixte
						m_interface->getPesee_OF()->_peseeParEcart = _peseeParEcartSvg ;

						m_interface->getPesee_OF()->setFocus(
							m_interface->getPesee_OF()->getSaisieRecipient());
					}
				}
			}
		}
	}
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_Recipient::monterCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionRecipient()->firstRow();
// si index premier recipient de la matrice < 9 positionnement sur premier ordre
	if (_n1 < 10)
		setListeSelectionRecipient(0);
	else
// sinon remonter de 9
		setListeSelectionRecipient(_n1 - 9);
	reDraw();

}

//---------------------------------------------------------------------------
void AdxSelection_Recipient::descendreCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionRecipient()->firstRow();
// s'il y a des recipients sur l'ecran suivant
	if (_n1 < (getInterface()->getDonnees()->getNbRecipients() - 9))
		setListeSelectionRecipient(_n1 + 9);
	reDraw();

}

//---------------------------------------------------------------------------
void AdxSelection_Recipient::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_Recipient::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_Recipient::quitter()
{

	AdxInterface* m_interface = getInterface();
	AdxSelection_Recipient* m_selection_Recipient = m_interface->getSelection_Recipient();

 	m_selection_Recipient->hide();
	_panneauAppelant->show();

}
void AdxSelection_Recipient::clearMatrix()
{
	// On vide la matrice si besoin
	IlvUShort wnNbRow = this->getlisteSelectionRecipient()->rows();
	if(wnNbRow>0)
	{
		// suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getlisteSelectionRecipient()->removeRow(wni);
		}
	}
}
void AdxSelection_Recipient::loadMatrix()
{
	char* szTemp   = new char[40];
	IlvUShort wnNbRecipients = getInterface()->getDonnees()->getNbRecipients();
	IlvLabelMatrixItem* item = NULL;
	IlList* recipientList = getInterface()->getDonnees()->getRecipientList();
	IlvUShort wnj = 0; // index des ordres !
	IlvDim rowHeight = 0;

	// On recré les row 
	getlisteSelectionRecipient()->insertRow(1,wnNbRecipients);
	IlvRect matrixBBox;

	getlisteSelectionRecipient()->boundingBox(matrixBBox,this->getTransformer());
	rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
    getlisteSelectionRecipient()->sameHeight(IlvTrue);
	getlisteSelectionRecipient()->setYgrid(rowHeight);

	for ( int i = 1; i <= wnNbRecipients; i++)
	{
		// pour compenser le fait que la première ligne de la liste est
		// une ligne de libellé.
		wnj = i-1;
		//--------
		AdxRecipient* recipient = (AdxRecipient*)(*recipientList)[wnj];
		// 02.09 mm - en cas de récipient fournisseur + tare modifiable, il faut réinitialiser la tareTheo 
		if ((recipient->getTypeRecipient() == 2) && (recipient->getTareModifiable()==2 ))
			recipient->setTareTheo(recipient->getTareTheoSvg());


		item = new IlvLabelMatrixItem(recipient->getRecipient());
		getlisteSelectionRecipient()->set(0,i,item);

		item = new IlvLabelMatrixItem(recipient->getLibRecipient());
		getlisteSelectionRecipient()->set(1,i,item);

		// SR 03.12 Demande 79129
		item = new IlvLabelMatrixItem(recipient->getLibTypeRecipient());
		getlisteSelectionRecipient()->set(2,i,item);
//		sprintf (szTemp, "%d", recipient->getTypeRecipient());
//		item = new IlvLabelMatrixItem(szTemp);
//		getlisteSelectionRecipient()->set(2,i,item);

		sprintf (szTemp, "%.3f", recipient->getTareTheo());
		item = new IlvLabelMatrixItem(szTemp);
		getlisteSelectionRecipient()->set(3,i,item);

		item = new IlvLabelMatrixItem(recipient->getUnitePoids());
		getlisteSelectionRecipient()->set(4,i,item);

	}
	getlisteSelectionRecipient()->deSelect();
	for(IlvUShort wni = 0;wni<getlisteSelectionRecipient()->columns();wni++)
	{
		// On boucle sur tous les rows de la colonne pour connaitre le plus long
		IlvDim maxColWidth = getlisteSelectionRecipient()->getColumnFittingSize(wni);
		getlisteSelectionRecipient()->setColumnSize(wni,maxColWidth+10);
	}
	delete [] szTemp;
}

//---------------------------------------------------------------------------
void AdxSelection_Recipient::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	getlisteSelectionRecipient()->showScrollBar(IlvHorizontal);
	getlisteSelectionRecipient()->showScrollBar(IlvVertical);

	_nbDsiplayRows = 9;

	char szFileIcons[_MAX_PATH];

	// bouton valider
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	IlvBitmap* bitmap = getDisplay()->readBitmap(szFileIcons);
	getvalider()->setBitmap(bitmap);

	// bouton descendre
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowdown.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getdescendre()->setBitmap(bitmap);

	// bouton monter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowup.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getmonter()->setBitmap(bitmap);

	// bouton aide
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\question_mark.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getaide()->setBitmap(bitmap);

	// bouton quitter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getquitter()->setBitmap(bitmap);

// redimensionne la largeur des colonnes (147 par défaut)
	IlvMatrix* matrix = getlisteSelectionRecipient();
	matrix->resizeColumn(2,241);
	matrix->resizeColumn(3,80);
	matrix->resizeColumn(5,120);

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
void AdxSelection_Recipient::setListeSelectionRecipient(int index)
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
	getlisteSelectionRecipient()->scrollToRow(index);

}

void AdxSelection_Recipient::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// Si on se trouve sur la matrice, on répercute le mouse wheel
			// et on enregistre le premier élément affiché dans _n1
			Selection_Recipient::handleInput(event);
			_n1 = this->getlisteSelectionRecipient()->firstRow();
			break;
		case IlvDoubleClick:
			// Si on se trouve sur la matrice, on prends la ligne en cours
			if(getlisteSelectionRecipient()->pointToPosition(event.getLocation(),
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
            Selection_Recipient::handleInput(event);
			break;
		default:
			Selection_Recipient::handleInput(event);
			break;
	}
}