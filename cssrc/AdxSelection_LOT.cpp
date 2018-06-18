// AdxSelection_LOT.cpp
// --------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#include "stdafx.h"
#include <cmath>
#include "AdxSelection_LOT.h"
#include "AdxInterface.h"

#include "AdxChoix_OF.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_LOT.h"
#include "AdxPesee_OF.h"
#include "AdxOrder.h"
#include "AdxLot.h"
#include "AdxComposant.h"
#include "AdxData.h"
#include "AdxDate.h"
#include "AdxMessage.h"


#include "AdxFicheISM.h"
//--------------------------------------------------------------
AdxSelection_LOT::~AdxSelection_LOT()
{
	if(_lotListSvg != NULL)
	{
		for (int i = 0; i < _lotListSvg->length(); i++)
		{
			delete (AdxLot*)(*_lotListSvg)[i];
		}
		_lotListSvg->empty();
		delete _lotListSvg;
	}
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxSelection_LOT::monterCB(IlvGraphic* g)
{
	_n1 = this->getMatriceCourante()->firstRow();
    // si index premier ordre de la matrice < 7 positionnement sur premier ordre
	if (_n1 < 8)
		setListeSelectionLot(0);
	else
// sinon remonter de 7
		setListeSelectionLot(_n1 -7);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::imprimerCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();

	if (_modifiable)
	{
		if(m_data->compareLotList(_lotListSvg) == false)
		{
			IlvBoolean r;
			if (getAffQuantite()->getFloatValue(r) != 0)
			{
				envoieMessage("&AllocationInvalide", false);
				return;
			}
			else
				m_data->imprimeEtAlloueLots();
		}
		else
			m_data->imprimeLots();
	}
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::quitterCB(IlvGraphic* g)
{
	if (_modifiable)
	{
		getInterface()->getDonnees()->setLotList(_lotListSvg);
	}
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::descendreCB(IlvGraphic* g)
{
	_n1 = this->getMatriceCourante()->firstRow();
    // s'il y a des ordres sur l'ecran suivant
	if (_n1 < (getInterface()->getDonnees()->getNbLots() - 7))
		setListeSelectionLot(_n1 + 7);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::consultationStockDetailleCB(IlvGraphic* g)
{
	// tunnel vers consultation stock X3 !
	AdxInterface* m_interface = getInterface();
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
	AdxData* m_data = m_interface->getDonnees();
	m_data->SendX3_ConsultationStockDetaille();
	reDraw();
} 
//---------------------------------------------------------------------------
void AdxSelection_LOT::desallouerCB(IlvGraphic* g)
{
    IlvUShort c;
	IlvUShort r;
	bool b;
	AdxComposant* composant = getInterface()->getDonnees()->getCurrentComposant();
	if (getMatriceCourante()->getFirstSelected(c,r))
	{
		// _n1 (numero du premier lot du tableau) 
		// + r (numero de ligne selectionnee commence a 1) - 1
		if (r-1 < getInterface()->getDonnees()->getNbLots())
		{
// desallouer la matiere au niveau de AdxLot, de qte alloue de AdxComposant
// raffraichir affichage
			IlList* lotList = getInterface()->getDonnees()->getLotList();
			AdxLot* lot = (AdxLot*) (*lotList)[r-1];
			double quantite;	
			if (composant->getGestionStock() == 3			// composant a titre
				&& composant->getTitreTheo() != 0)
				quantite = lot->getQuantiteAllouee() * lot->getTitre() / composant->getTitreTheo();
			else
				quantite = lot->getQuantiteAllouee();
			if (quantite != 0)
			{
				lot->setQuantiteAllouee(0);
				composant->setQuantiteAllouee(composant->getQuantiteAllouee() - 
					quantite);
				getAffQuantite()->setValue(getAffQuantite()->getFloatValue(b)	
					+ quantite);
				setListeSelectionLot(_n1);
				reDraw();
			}
		}
	}
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::allouerCB(IlvGraphic* g)
{
//on ne peut allouer si reste a allouer = 0
	IlvBoolean r;
	if (getAffQuantite()->getFloatValue(r)>0)
	{
		IlvUShort c;
		IlvUShort r;
		if (getMatriceCourante()->getFirstSelected(c,r))
		{
			// _n1 (numero du premier lot du tableau) 
			// + r (numero de ligne selectionnee commence a 1) - 1
			if (r-1 < getInterface()->getDonnees()->getNbLots())
			{

// desallouer la matiere au niveau de AdxLot, de qte alloue de AdxComposant
// raffraichir affichage
				IlList* lotList = getInterface()->getDonnees()->getLotList();
				AdxLot* lot = (AdxLot*) (*lotList)[r-1];
				AdxComposant* composant = getInterface()->getDonnees()->getCurrentComposant();
		    	// Si mélange lots interdit, il faut vérifier ici qu'il n'y a 
			    // pas déjà une allocation portant sur un autre lot
				if (getInterface()->getDonnees()->getCurrentFicheISM()->getMelangeLotCode() != 1)
				{
					AdxLot* lot2;
					for (int i = 0; i < getInterface()->getDonnees()->getNbLots(); i++)
					{
							lot2 = (AdxLot*)(*lotList)[i];
							if (lot2->getQuantiteAllouee() != 0) 
							{
								if (strcmp(lot2->getLot(),lot->getLot()) != 0)	 	
								{
									envoieMessage("&AllocationImpossible", false);
									return;
								}
							}
					}
				}
		// on ne peut allouer que si sur la ligne tout n'est pas deja alloue
				if (lot->getQuantiteAllouee() < lot->getQuantiteDisponible())
				{
					double qteDispoLigne = lot->getQuantiteDisponible() - lot->getQuantiteAllouee();
					IlvBoolean b;
					double maxAAllouer;
					if (composant->getGestionStock() == 3			// composant a titre
						&& composant->getTitreTheo() != 0)
						maxAAllouer = getAffQuantite()->getFloatValue(b) 
							* composant->getTitreTheo() / lot->getTitre();
					else
						maxAAllouer = getAffQuantite()->getFloatValue(b);
					double quantite;
					if (qteDispoLigne > maxAAllouer)
						quantite = maxAAllouer;
					else
						quantite = qteDispoLigne;
					lot->setQuantiteAllouee(lot->getQuantiteAllouee() + quantite);
					composant->setQuantiteAllouee(
							composant->getQuantiteAllouee()	+ quantite);
					if (composant->getGestionStock() == 3			// composant a titre
						&& composant->getTitreTheo() != 0)
					{
						getAffQuantite()->setValue(getAffQuantite()->getFloatValue(b)	
							- quantite * lot->getTitre() / composant->getTitreTheo());
						// mm 10.12 - APCPRD 2074 - ne pas afficher -0 - A TERMINER
						/*double _resteAAllouer = 0;
						_resteAAllouer =  atof(getAffQuantite()->getValue());
						if (_resteAAllouer< 0)
							getAffQuantite() ->setValue(- _resteAAllouer);*/
					}
					else
						getAffQuantite()->setValue(getAffQuantite()->getFloatValue(b)	
							- quantite);
					setListeSelectionLot(_n1);	
					reDraw();
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::validerCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	AdxPesee_OF* pesee_OF = getInterface()->getPesee_OF();
	// 113385 mm 03.2016
	AdxChoix_OF* choixOF = m_interface->getChoix_OF();

	int lotIndexSvg;
	int choixLotOk = 1 ; // 1 Pas de choix lot : 2 choix lot
	bool lotOKSvg;
	// SR 06.12 APCPRD-1527
	AdxLot* _savLot;
	char* _lot;
	char* _slo;
	int _chrono;
	int _lotSelOk;
	_lotSelOk = 0;

	
	// sr 02.02 Si on vient de la pesée , on positionne
	// currentlot avant  d'éventuellement allouer (sinon après allocation, 
	// ligne de la liste des lots <> ligne de la matrice pour le même lot)
	if (_panneauAppelant == pesee_OF)
	{	
		lotIndexSvg = m_data->getCurrentLotIndex();
		lotOKSvg = pesee_OF->_lotOK;
		IlvUShort c;
		IlvUShort r;
		if (getMatriceCourante()->getFirstSelected(c,r))
		{
			if (r-1 < m_data->getNbLots())
			{
				m_data->setCurrentLotIndex(r-1);
				// SR 06.12 APCPRD-1527
				_savLot = m_data->getCurrentLot();
				_lot    = new char[strlen(m_data->getCurrentLot()->getLot()) +1];
				_slo	= new char[strlen(m_data->getCurrentLot()->getSlo()) +1];
				_lotSelOk = 1;
				strcpy( _lot ,(char*)_savLot->getLot());
				strcpy( _slo ,(char*)_savLot->getSlo());
				 _chrono = _savLot->getChrono();
				 if ( !m_data->getComposantBegin() )
					 pesee_OF ->setTitreSlo(_savLot->getTitre());
				choixLotOk = 2;
			}
			else
			{
				m_data->setCurrentLotIndex(0);
				_savLot = m_data->getCurrentLot();
				if ( !m_data->getComposantBegin() )
					pesee_OF ->setTitreSlo(_savLot->getTitre());
				choixLotOk = 1;
			}
		}
	}

	if (_modifiable)
	{
		if(m_data->compareLotList(_lotListSvg) == false)
		{
			IlvBoolean r;
			// 113385 mm 03.2016 
			// Possiblility to allocate partially from weighing station from Pesee_OF screen.
			// ( before, it was possible to allocate partially only from WO)
			if (_panneauAppelant ==  choixOF )
			{
				if (getAffQuantite()->getFloatValue(r) != 0)
				{
					envoieMessage("&AllocationInvalide", false);
					return;
				}
			}
			//if (getAffQuantite()->getFloatValue(r)== 0)
			//  121455 mm 02.2017
			//  It stays impossible to allocate partially from Choix_OF screen
			if (((_panneauAppelant ==  choixOF ) && (getAffQuantite()->getFloatValue(r)== 0)) 
			|| (_panneauAppelant == pesee_OF))
			{
				m_data->alloueLots();
				// SR 06.12 APCPRD-1527 : se positionner sur le lot sélectionne ou 
				// proposer automatiquement un lot à peser
				if (_lotSelOk !=0)
				{
					AdxLot* lot;
					IlList* lotList = m_data->getLotList();
					for (int i = 0; i <m_data->getNbLots(); i++)
					{
						lot = (AdxLot*) (*lotList)[i];
						if ((strcmp(lot->getLot(),_lot)==0) &&
							(strcmp(lot->getSlo(),_slo)==0 )&&
							(lot->getChrono()==_chrono))
						{
							m_data->setCurrentLotIndex(i);
							if ( !m_data->getComposantBegin() )
								pesee_OF->setTitreSlo(lot->getTitre());
							// SR 07.12 APCPRD-1727 : Si lot sélectionne incorrect on propose en automatique
							if (pesee_OF->controleLot()==false)
							{
								pesee_OF->propositionLot();
							}
							// mm 08.2012 : pb libération de mémoire
							delete [] _lot;
							delete [] _slo;
							_savLot = NULL;
							break;
						}
					}
				}
				else
				{
					pesee_OF->propositionLot();
					if (pesee_OF->_lotOK)
						choixLotOk = 2;
				}
			}
		}
		else
		{
			if (choixLotOk != 1)
			pesee_OF->controleLot();
		}
	}
	else
	{
		if (choixLotOk != 1)
		pesee_OF->controleLot();
	}

	// pour Pesee_OF, en fabrication
	if (_panneauAppelant == pesee_OF)
	{
		if (pesee_OF->getSaisieCuve()->isEditable() == IlvTrue
			||	pesee_OF->getSaisieLot()->isEditable() == IlvTrue)
		// on est en selection
		{
			// mm 02.11 - magasin avancé 
			// allocations manuelles :  proposition automatique du lot (si possible)
			// revient à choisir une ligne allouée du tableau de sélection des lots
			if (m_data->getAllocationAutoCode() == 1 || m_data->getPrioriteAllocationCode()== 1 ) 
			{
				if (((getInterface()->getFonctionEnCours() == 3) && (strcmp(pesee_OF->getSaisieCuve()->getLabel(),"")==0))||
					(strcmp(pesee_OF->getSaisieLot()->getLabel(),"")==0))											
				{
					if (m_data->getCurrentComposant()->getQuantiteAllouee() != 0) 
						m_data->setComposantAlloue(true);
					pesee_OF->propositionLot();
					if (pesee_OF->_lotOK)
					{
						//	-> apres l'alloc on retablit ce flag à false
						pesee_OF->_stockReelInfInfo = false;
						pesee_OF->afficherLot(m_data->getCurrentLot());
						pesee_OF->setFocus(pesee_OF->getSaisieLot());
						// mm 10.11 - Pesée multi-article
						if (pesee_OF->_enPeseeMultiArticle == true)
							pesee_OF->suiteChoixLotMulti();
						else
							pesee_OF->suiteChoixLot();
							
					}
					quitter();	
					return;
				}
			}

			if (choixLotOk != 1)
			{
				if (pesee_OF->_lotOK)
				{
					pesee_OF->_stockReelInfInfo = false;
					pesee_OF->afficherLot(m_data->getCurrentLot());
					pesee_OF->setFocus(pesee_OF->getSaisieLot());
					// mm 10.11 - Pesée multi-article
					if (pesee_OF->_enPeseeMultiArticle == true)
						pesee_OF->suiteChoixLotMulti();
					else
						pesee_OF->suiteChoixLot();
					}
				else
				{
					m_data->setCurrentLotIndex(lotIndexSvg);
					pesee_OF->_lotOK = lotOKSvg;
					pesee_OF->attenteSaisieLot();
				}
			}
			else
			{
				m_data->setCurrentLotIndex(lotIndexSvg);
				pesee_OF->_lotOK = lotOKSvg;
				pesee_OF->attenteSaisieLot();
			}
		}
	}

	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxData*	  m_data	  = m_interface->getDonnees();
	AdxSelection_LOT* m_selection_LOT = m_interface->getSelection_LOT();

	// mm 12.10 - pour mise à jour du champ quantité allouée
	m_interface->getChoix_OF()->afficherOrdre(
				m_data->getCurrentOrderIndex(),
				m_data->getCurrentPhaseIndex(),
				m_data->getCurrentComposantIndex());
 	m_selection_LOT->hide();
	_panneauAppelant->show();
}
void AdxSelection_LOT::clearMatrix()
{
	// On vide la matrice si besoin
	IlvUShort wnNbRow = this->getMatriceCourante()->rows();
	if(wnNbRow>0)
	{
		// suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getMatriceCourante()->removeRow(wni);
		}
	}
}

void AdxSelection_LOT::loadMatrix()
{
	char* szTemp = new char[40]; 
	IlvUShort wnNbLots = getInterface()->getDonnees()->getNbLots();
	IlvDateField::IlvDateFieldFormat first;
	IlvDateField::IlvDateFieldFormat middle;
	IlvDateField::IlvDateFieldFormat last;
	char separator;
	IlvLabelMatrixItem* item = NULL;
	getInterface()->getAccueil()->getChampDate()->getFormat(first,middle,last,separator);
	//getDateField()->getFormat(first,middle,last,separator);
	const char* format = getInterface()->getDonnees()->getCurrentComposant()->getFormat();
	IlList* lotList = getInterface()->getDonnees()->getLotList();
	IlvUShort wnj = 0; // index des ordres !
	IlvDim rowHeight = 0;

	if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
	{

		// On recré les row 
		getlisteSelectionCuve()->insertRow(1,wnNbLots);
		IlvRect matrixBBox;

		getlisteSelectionCuve()->boundingBox(matrixBBox,this->getTransformer());
		rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
		getlisteSelectionCuve()->sameHeight(IlvTrue);
		getlisteSelectionCuve()->setYgrid(rowHeight);

		for ( int i = 1; i <= wnNbLots; i++)
		{
			// pour compenser le fait que la première ligne de la liste est
			// une ligne de libellé.
			wnj = i-1;
			//--------
			AdxLot* lot = (AdxLot*)(*lotList)[wnj];

			item = new IlvLabelMatrixItem(lot->getCuve());
			getlisteSelectionCuve()->set(0,i,item);

			item = new IlvLabelMatrixItem(lot->getVanne());
			getlisteSelectionCuve()->set(1,i,item);

			item = new IlvLabelMatrixItem(lot->getLot());
			getlisteSelectionCuve()->set(2,i,item);

			item = new IlvLabelMatrixItem(lot->getSlo());
			getlisteSelectionCuve()->set(3,i,item);

			sprintf (szTemp, format, lot->getQuantiteDisponible());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionCuve()->set(4,i,item);

			sprintf (szTemp, format, lot->getQuantiteAllouee());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionCuve()->set(5,i,item);

			if (lot->getDatePeremption() != NULL)
			{
				char* wChDate = lot->getDatePeremption()->dateToChar(first,
															   middle,
															   last,
															   separator);
				item = new IlvLabelMatrixItem(wChDate);
			}
			else
			{
				item = new IlvLabelMatrixItem("");// faut il une date par défaut?
			}
			getlisteSelectionCuve()->set(6,i,item);
			
			sprintf (szTemp, "%.2f", lot->getTitre());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionCuve()->set(7,i,item);

			item = new IlvLabelMatrixItem(lot->getStatut());
			getlisteSelectionCuve()->set(8,i,item);
		}
		getlisteSelectionCuve()->deSelect();
		for(IlvUShort wni = 0;wni<getlisteSelectionCuve()->columns();wni++)
		{
			// On boucle sur tous les rows de la colonne pour connaitre le plus long
			IlvDim maxColWidth = getlisteSelectionCuve()->getColumnFittingSize(wni);
			getlisteSelectionCuve()->setColumnSize(wni,maxColWidth+10);
		}
	}
	else
	{
		// On recré les row 
		getlisteSelectionLot()->insertRow(1,wnNbLots);
		IlvRect matrixBBox;

		getlisteSelectionLot()->boundingBox(matrixBBox,this->getTransformer());
		rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
		getlisteSelectionLot()->sameHeight(IlvTrue);
		getlisteSelectionLot()->setYgrid(rowHeight);

		for ( int i = 1; i <= wnNbLots; i++)
		{
			// pour compenser le fait que la première ligne de la liste est
			// une ligne de libellé.
			wnj = i-1;
			//--------
			AdxLot* lot = (AdxLot*)(*lotList)[wnj];

			item = new IlvLabelMatrixItem(lot->getLot());
			getlisteSelectionLot()->set(0,i,item);

			item = new IlvLabelMatrixItem(lot->getSlo());
			getlisteSelectionLot()->set(1,i,item);

			item = new IlvLabelMatrixItem(lot->getEmplacement());
			getlisteSelectionLot()->set(2,i,item);

			sprintf (szTemp, format, lot->getQuantiteDisponible());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionLot()->set(3,i,item);

			sprintf (szTemp, format, lot->getQuantiteAllouee());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionLot()->set(4,i,item);

			if (lot->getDatePeremption() != NULL)
			{
				char* wChDate = lot->getDatePeremption()->dateToChar(first,
															   middle,
															   last,
															   separator);
				item = new IlvLabelMatrixItem(wChDate);
			}
			else
			{
				item = new IlvLabelMatrixItem("");// faut il une date par défaut?
			}
			getlisteSelectionLot()->set(5,i,item);

			sprintf (szTemp, "%.2f", lot->getTitre());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionLot()->set(6,i,item);

			item = new IlvLabelMatrixItem(lot->getStatut());
			getlisteSelectionLot()->set(7,i,item);

		}
		getlisteSelectionLot()->deSelect();
		for(IlvUShort wni = 0;wni<getlisteSelectionLot()->columns();wni++)
		{
			// On boucle sur tous les rows de la colonne pour connaitre le plus long
			IlvDim maxColWidth = getlisteSelectionLot()->getColumnFittingSize(wni);
			getlisteSelectionLot()->setColumnSize(wni,maxColWidth+10);
		}
	}
	delete [] szTemp;
}

//---------------------------------------------------------------------------
void AdxSelection_LOT::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));


	//IlvDim dim = getlisteSelectionLot()->getColumnWidth(1);
	//getlisteSelectionLot()->resizeColumn(1,dim + 60);		
	//getlisteSelectionLot()->resizeColumn(2,dim - 20);		
	//getlisteSelectionLot()->resizeColumn(6,dim - 30);
	//getlisteSelectionLot()->resizeColumn(7,dim - 30);

	getlisteSelectionLot()->showScrollBar(IlvHorizontal);
	getlisteSelectionLot()->showScrollBar(IlvVertical);
	getlisteSelectionCuve()->showScrollBar(IlvHorizontal);
	getlisteSelectionCuve()->showScrollBar(IlvVertical);

	_nbDsiplayRows = 9;

	
	_lotListSvg = new IlList;			

	char szFileIcons[_MAX_PATH];

	// bouton valider
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	IlvBitmap* bitmap = getDisplay()->readBitmap(szFileIcons);
	getvalider()->setBitmap(bitmap);

	// bouton allouer
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\lock.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getallouer()->setBitmap(bitmap);

	// bouton desallouer
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\unlock.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);	
	getdesallouer()->setBitmap(bitmap);
	
	// bouton consultation stock détaillé - mm 04.10 (050)
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\detailstock.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getconsultationStockDetaille()->setBitmap(bitmap);

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

	// bouton imprimer
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\local_printer.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getimprimer()->setBitmap(bitmap);

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
void AdxSelection_LOT::setListeSelectionLot(int index)
{

// affichage de la matrice
	if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
	{
		setVisible(getlisteSelectionLot(), IlvFalse, IlvFalse);
		setVisible(getlisteSelectionCuve(), IlvTrue, IlvFalse);
		setMatriceCourante(getlisteSelectionCuve());
	}
	else
	{
		setVisible(getlisteSelectionCuve(), IlvFalse, IlvFalse);
		setVisible(getlisteSelectionLot(), IlvTrue, IlvFalse);
		setMatriceCourante(getlisteSelectionLot());
	}
	_n1 = index;
	if(index <0)
	{
		_n1 = 0;
	}

	// purge de la matrice
	this->clearMatrix();
	// chargement de la matrice 
	this->loadMatrix();
	getMatriceCourante()->scrollToRow(index);
}

// affichage des 3 zones de l'ecran autre que la matrice
//---------------------------------------------------------------------------
void AdxSelection_LOT::setField()
{
	AdxData*  m_data = getInterface()->getDonnees();
	getAffComposant()->setLabel(m_data->getCurrentComposant()->getComposant());
	double quantite;
	if (m_data->getCurrentComposant()->getGestionStock() == 3			// composant a titre
		&& m_data->getCurrentComposant()->getTitreTheo() != 0)
	{
		quantite = m_data->getCurrentComposant()->getQuantiteTheorique();
		AdxLot* lot;
		IlList* lotList = m_data->getLotList();
		for (int i = 0; i < m_data->getNbLots(); i++)
		{
			lot = (AdxLot*) (*lotList)[i];
			quantite = quantite - 
				(lot->getQuantiteAllouee() * lot->getTitre() / m_data->getCurrentComposant()->getTitreTheo());
		}
		// sr 01.12 APCPRD-731 Si quantité = quantité du besoin, on n'y touche pas
        // à cause des problèmes de conversions
        //if ((fabs(quantite) < 1) & (m_data->getCurrentComposant()->getGestionStock() == 3))
		if ((quantite != m_data->getCurrentComposant()->getQuantiteTheorique()) & (fabs(quantite) < 1))
        {
            quantite = 0;
        }
	}
	else
	{
		quantite = m_data->getCurrentComposant()->getQuantiteTheorique()	
							-	m_data->getCurrentComposant()->getQuantiteAllouee();
		// sr 01.12 : APCPRD-732 : calcul de la quantité de l'excipient
		if (quantite < 0)
			quantite = 0;
	}
	getAffQuantite()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());
	getAffQuantite()->setValue(quantite);
	getAffUS()->setLabel(m_data->getCurrentComposant()->getUnite());
}

// affichage des boutons valides pour alloc ou selection lot
//---------------------------------------------------------------------------
void AdxSelection_LOT::setButtons()
{
	if (_modifiable)
	{
		setVisible(getallouer(),IlvTrue, IlvFalse);
		setVisible(getdesallouer(),IlvTrue, IlvFalse);
		setVisible(getconsultationStockDetaille(),IlvTrue, IlvFalse); 
		setVisible(getimprimer(),IlvTrue, IlvFalse);
	}
	else
	{
		setVisible(getallouer(),IlvFalse, IlvFalse);
		setVisible(getdesallouer(),IlvFalse, IlvFalse);
		setVisible(getconsultationStockDetaille(),IlvFalse, IlvFalse); 
		setVisible(getimprimer(),IlvFalse, IlvFalse);
	}
}

//---------------------------------------------------------------------------
// preparation du premier chargement de la fenetre
void AdxSelection_LOT::chargement(bool modifiable)
{
	setModifiable(modifiable);
	if (_modifiable)
		saveLotList();
	setListeSelectionLot(0);
	setField();
	setButtons();
}

//---------------------------------------------------------------------------
// copie lot par lot la _lotList de AdxData dans _lotListSvg de AdxSelection_LOT
//		pour restauration eventuelle quand on quitte
void AdxSelection_LOT::saveLotList()
{
	_lotListSvg->empty();
	IlList* lotList = getInterface()->getDonnees()->getLotList();
	for (int i = 0; i < getInterface()->getDonnees()->getNbLots(); i++)
	{
		_lotListSvg->append(((AdxLot*) (*lotList)[i])->copy());
	}
}

//---------------------------------------------------------------------------
bool AdxSelection_LOT::envoieMessage(CString mess, bool OUINON)
{
	AdxInterface* m_interface = getInterface();
	m_interface->getMessage()->setPanneauAppelant(this);
	return (m_interface->envoieMessage(mess, OUINON));
}

void AdxSelection_LOT::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// Si on se trouve sur la matrice, on répercute le mouse wheel
			// et on enregistre le premier élément affiché dans _n1
			Selection_LOT::handleInput(event);
			_n1 = this->getMatriceCourante()->firstRow();
			break;
		case IlvDoubleClick:
			// Si on se trouve sur la matrice, on prends la ligne en cours
			if(getMatriceCourante()->pointToPosition(event.getLocation(),
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
            Selection_LOT::handleInput(event);
			break;
		default:
			Selection_LOT::handleInput(event);
			break;
	}
}
