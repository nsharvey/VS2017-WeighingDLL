// AdxSelection_OF.cpp
// -------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "Adxselection_OF.h"
#include "AdxInterface.h"

#include "AdxChoix_OF.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_Phase.h"
#include "AdxSelection_MWF.h"
#include "AdxPesee_OF.h"
#include "AdxOrder.h"
#include "AdxPhase.h"
#include "AdxComposant.h"
#include "AdxData.h"
#include "AdxDate.h"
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxSelection_OF::validerCB(IlvGraphic* g)
{
	IlvUShort c;
	IlvUShort r;
	AdxData* m_data = getInterface()->getDonnees();
	AdxChoix_OF* m_choix_OF = getInterface()->getChoix_OF();

	if (getlisteSelectionOF()->getFirstSelected(c,r))
	{
		// _n1 (numero de la premiere phase du tableau) 
		// + r (numero de ligne selectionnee commence a 1) - 1
		if (r-1 < m_data->getNbOrders())
		{
			// SMO : STD-PR-OO1 : Pesee Matiere
			if (getInterface()->getFonctionEnCours() == 1 ||  getInterface()->getFonctionEnCours() == 3)
			{
				if (r-1 != m_data->getCurrentOrderIndex())
				{
					if (getInterface()->getChoix_OF()->controleChangementOF(r-1) == false)
					{
						quitter();
						return;
					} 
					else 
					{
						m_data->setCurrentOrderIndex(r-1);
					}
				}
				selectionSuivante();
				m_data->lanceProcedureEnAttente();
			}
			else
			{	
				m_data->setCurrentOrderIndex(r-1);
				if (m_data-> getEnCoursDePeseeParArticle()== false)
				{
					if ( m_data->getNbPhases() == 1 && m_data->getNbComposants_Art()==1 )
					{
						// si une seule phase on la selectionne automatiquement et on revient au menu OF
						m_data->setCurrentPhaseIndex(0); 
						m_data->setCurrentComposantIndex(0); 
						m_data->sendX3_ChangePhase();
						quitter(); // retour ecran choix_OF
					}
					else
					{
						// pour ne pas se faire jeter qd on teste si le champ OF est alimenté
						m_choix_OF->getSaisieNOF_Art()->setLabel(m_data->getOrder(r-1)->getNumOF());
						selectionSuivante(); // affichage ecran de selection des phases
					}
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
void AdxSelection_OF::monterCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionOF()->firstRow();
// si index premier ordre de la matrice < 9 positionnement sur premier ordre
	if (_n1 < 10)
		setListeSelectionOF(0);
	else
// sinon remonter de 9
		setListeSelectionOF(_n1 - 9);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_OF::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_OF::descendreCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionOF()->firstRow();
// s'il y a des ordres sur l'ecran suivant
	if (_n1 < (getInterface()->getDonnees()->getNbOrders() - 9))
		setListeSelectionOF(_n1 + 9);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_OF::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_OF::quitter()
{
	AdxInterface*		m_interface		= getInterface();
	AdxSelection_OF*	m_selection_OF	= m_interface->getSelection_OF();
	AdxData*			m_data			= m_interface->getDonnees();
	AdxChoix_OF*        m_choix_OF      = getInterface()->getChoix_OF();
	
	// vérification qu'un OF a bien été choisi avant de l'afficher ...
	if ( m_data->getCurrentOrder()== NULL)
	{
		m_interface->envoieMessage("&OFNonRenseigne", false);
		setFocus(getvalider(), IlvTrue);
	}
	else
	{
		getInterface()->getChoix_OF()->afficherOrdre(
				m_data->getCurrentOrderIndex(),
				m_data->getCurrentPhaseIndex(),
				m_data->getCurrentComposantIndex());
		m_selection_OF->hide();
		_panneauAppelant->show();
	}

}

//---------------------------------------------------------------------------
void AdxSelection_OF::selectionSuivante()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees(); 
	AdxSelection_OF* m_selection_OF = m_interface->getSelection_OF();
	AdxSelection_Phase* m_selection_Phase = m_interface->getSelection_Phase();

	// sr 06.02 Message en bas d'écran
	CString string(IlvGetMessage(getDisplay(), "&Choisir"));
	string += " ";
	string += IlvGetMessage(getDisplay(), "&Phase1");

	// si on vient de choix par OF ou en Fabrication on chaine sur l'ecran de selection Phase
	if (m_interface->getFonctionEnCours() == 1||  m_interface->getFonctionEnCours() == 3)
	{
		m_selection_Phase->setListeSelectionPhase(getInterface()->getDonnees()->getCurrentPhaseIndex());
	}
	else 
	{
		// ajout de l'affichage du composant dans le bordereau.
		string += "         - ";
		string += m_data->getPseMatCurrentMat();
		string += " - ";
		string += m_data->getPseMatCurrentMatLib(); 

		// on chaine sur l'ecran de selection phase
		m_selection_Phase->setListeSelectionPhase(0);
	}

	m_selection_Phase->getmessage()->setLabel(string);
	setPanneauAppelant(this);
	m_selection_Phase->show();
 	m_selection_OF->hide();
}
//---------------------------------------------------------------------------
void AdxSelection_OF::clearMatrix()
{
	// On vide la matrice si besoin
	IlvUShort wnNbRow = this->getlisteSelectionOF()->rows();
	if(wnNbRow>0)
	{
		// suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getlisteSelectionOF()->removeRow(wni);
		}
	}
}
//---------------------------------------------------------------------------
bool AdxSelection_OF::loadMatrix()
{
	AdxChoix_OF* m_choix_OF = getInterface()->getChoix_OF();
	AdxData* m_data = getInterface()->getDonnees();

	// SMO : STD-PR-OO1 : Pesee Matiere
	if (getInterface()->getFonctionEnCours() == 1||  getInterface()->getFonctionEnCours() == 3)
	{
		char* szTemp   = new char[40];
		IlvUShort wnNbOrders = getInterface()->getDonnees()->getNbOrders();
		IlvDateField::IlvDateFieldFormat first;
		IlvDateField::IlvDateFieldFormat middle;
		IlvDateField::IlvDateFieldFormat last;
		char separator;
		IlvLabelMatrixItem* item = NULL;
		getInterface()->getAccueil()->getChampDate()->getFormat(first,middle,last,separator);
		//getDateField()->getFormat(first,middle,last,separator);
		IlList* orderList = getInterface()->getDonnees()->getOrderList();
		IlvUShort wnj = 0; // index des ordres !
		IlvDim rowHeight = 0;

		// SMO : 19/08/2010 : modification des champs en fonction du contexte
		getlisteSelectionOF()->getItem(0,0)->setLabel("&NOF");
		getlisteSelectionOF()->getItem(1,0)->setLabel("&Date");
		getlisteSelectionOF()->getItem(2,0)->setLabel("&ArticleLance");
		getlisteSelectionOF()->getItem(3,0)->setLabel("&Designation");
		getlisteSelectionOF()->getItem(4,0)->setLabel("&QuantiteLancee");
		getlisteSelectionOF()->getItem(5,0)->setLabel("&Unite");
		getlisteSelectionOF()->getItem(6,0)->setLabel("&Priorite");

		// On recré les row 
		getlisteSelectionOF()->insertRow(1,wnNbOrders);
		IlvRect matrixBBox;

		getlisteSelectionOF()->boundingBox(matrixBBox,this->getTransformer());
		rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
		getlisteSelectionOF()->sameHeight(IlvTrue);
		getlisteSelectionOF()->setYgrid(rowHeight);

		for ( int i = 1; i <= wnNbOrders; i++)
		{
			// pour compenser le fait que la première ligne de la liste est
			// une ligne de libellé.
			wnj = i-1;
			//--------

			AdxOrder* order = (AdxOrder*)(*orderList)[wnj];

			item = new IlvLabelMatrixItem(order->getNumOF());
			getlisteSelectionOF()->set(0,i,item);

			if (order->getDateFin() != NULL)
			{
				char* wChDate = order->getDateFin()->dateToChar(first,
															   middle,
															   last,
															   separator);
				item = new IlvLabelMatrixItem(wChDate);
			}
			else
			{
				item = new IlvLabelMatrixItem("");// faut il une date par défaut?
			}
			getlisteSelectionOF()->set(1,i,item);

			item = new IlvLabelMatrixItem(order->getArticle());
			getlisteSelectionOF()->set(2,i,item);

			item = new IlvLabelMatrixItem(order->getLibArticle());
			getlisteSelectionOF()->set(3,i,item);

			sprintf (szTemp, "%.2f", order->getQuantiteLance());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionOF()->set(4,i,item);

			item = new IlvLabelMatrixItem(order->getUnite());
			getlisteSelectionOF()->set(5,i,item);

			item = new IlvLabelMatrixItem(order->getLibPriorite());
			getlisteSelectionOF()->set(6,i,item);


			// 47764 mm 07.08 - situation OF incorrecte
			// grisage ou degrisage des OF totalement pesees ou non
			if (order->getTotalementPese()) 
			{
				for(IlvUShort wni = 0;wni<getlisteSelectionOF()->columns();wni++)
				{
					getlisteSelectionOF()->setItemSensitive(wni,i,IlvFalse);
				}
			}
			else
			{
				for(IlvUShort wni = 0;wni<getlisteSelectionOF()->columns();wni++)
				{
					getlisteSelectionOF()->setItemSensitive(wni,i,IlvTrue);
				}
			}
		}
		getlisteSelectionOF()->deSelect();

		for(IlvUShort wni = 0;wni<getlisteSelectionOF()->columns();wni++)
		{
			// On boucle sur tous les rows de la colonne pour connaitre le plus long
			IlvDim maxColWidth = getlisteSelectionOF()->getColumnFittingSize(wni);
			getlisteSelectionOF()->setColumnSize(wni,maxColWidth+10);
		}

		delete [] szTemp;
		return true;
	}
	else
	{
		// Avant de recharger la liste, on remet l'OF courant dans le plan de pesée si necessaire
		if (( m_data->getCurrentOrder() != NULL ) &&  ( m_data->getCurrentComposant()->getQuantiteRestante() != 0))
			m_choix_OF ->changementOF_Art();
		//on vide la liste des fiches ISM, celle des OFs, celle des phases.
					m_data->razListeFicheISM();							
					m_data->razListeOF();																			
					m_data->razListePhase();
					// 06.2013 mm 90456 
					if (m_data->getChargementListMat() == 2)
						m_data->razListeComposant();
		// APCPRD-2651 mm 12.12 - si la fenêtre de sélection des OFs est vide, on se retrouve bloqué.
		bool _wretour = m_data->sendX3_GetMatOF();
		if (_wretour == true)
		{
			char* szTemp   = new char[40];
			IlvUShort wnNbOrders = getInterface()->getDonnees()->getNbOrders();
			IlvDateField::IlvDateFieldFormat first;
			IlvDateField::IlvDateFieldFormat middle;
			IlvDateField::IlvDateFieldFormat last;
			char separator;
			IlvLabelMatrixItem* item = NULL;
			getInterface()->getAccueil()->getChampDate()->getFormat(first,middle,last,separator);
			IlList* orderList = getInterface()->getDonnees()->getOrderList();
			IlvUShort wnj = 0; // index des ordres !
			IlvDim rowHeight = 0;

			// SMO : 19/08/2010 : modification des champs en fonction du contexte
			getlisteSelectionOF()->getItem(0,0)->setLabel("&NOF");
			getlisteSelectionOF()->getItem(1,0)->setLabel("&Date");
			getlisteSelectionOF()->getItem(2,0)->setLabel("&ArticleLance");
			getlisteSelectionOF()->getItem(3,0)->setLabel("&Designation");
			getlisteSelectionOF()->getItem(4,0)->setLabel("&TotPesee");
			getlisteSelectionOF()->getItem(5,0)->setLabel("&Unite");
			getlisteSelectionOF()->getItem(6,0)->setLabel("&Priorite");

			// On recré les row 
			getlisteSelectionOF()->insertRow(1,wnNbOrders);
			IlvRect matrixBBox;

			getlisteSelectionOF()->boundingBox(matrixBBox,this->getTransformer());
			rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
			getlisteSelectionOF()->sameHeight(IlvTrue);
			getlisteSelectionOF()->setYgrid(rowHeight);

			for ( int i = 1; i <= wnNbOrders; i++)
			{
				// pour compenser le fait que la première ligne de la liste est
				// une ligne de libellé.
				wnj = i-1;
				//--------

				AdxOrder* order = (AdxOrder*)(*orderList)[wnj];

				item = new IlvLabelMatrixItem(order->getNumOF());
				getlisteSelectionOF()->set(0,i,item);

				if (order->getDateFin() != NULL)
				{
					char* wChDate = order->getDateFin()->dateToChar(first,
																   middle,
																   last,
																   separator);
					item = new IlvLabelMatrixItem(wChDate);
				}
				else
				{
					item = new IlvLabelMatrixItem("");// faut il une date par défaut?
				}
				getlisteSelectionOF()->set(1,i,item);

				item = new IlvLabelMatrixItem(order->getArticle());
				getlisteSelectionOF()->set(2,i,item);

				item = new IlvLabelMatrixItem(order->getLibArticle());
				getlisteSelectionOF()->set(3,i,item);

				sprintf (szTemp, "%.2f", order->getTotalAPeser());
				item = new IlvLabelMatrixItem(szTemp);
				getlisteSelectionOF()->set(4,i,item);

				item = new IlvLabelMatrixItem(order->getUnitePoidsCompo());
				getlisteSelectionOF()->set(5,i,item);

				item = new IlvLabelMatrixItem(order->getLibPriorite());
				getlisteSelectionOF()->set(6,i,item);
				
			}
			getlisteSelectionOF()->deSelect();

			for(IlvUShort wni = 0;wni<getlisteSelectionOF()->columns();wni++)
			{
				// On boucle sur tous les rows de la colonne pour connaitre le plus long
				IlvDim maxColWidth = getlisteSelectionOF()->getColumnFittingSize(wni);
				getlisteSelectionOF()->setColumnSize(wni,maxColWidth+10);
			}
			delete [] szTemp;
		}
		return _wretour;
	}
}
//---------------------------------------------------------------------------
void AdxSelection_OF::init(AdxInterface* m_interface)
{
	_interface = m_interface;

	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	getlisteSelectionOF()->showScrollBar(IlvHorizontal);
	getlisteSelectionOF()->showScrollBar(IlvVertical);
	getlisteSelectionOF()->autoFitToSize(IlvTrue);

	_nbDsiplayRows = 9;

	IlvDim dim = getlisteSelectionOF()->getColumnWidth(1);
	getlisteSelectionOF()->resizeColumn(1,dim + 55);		
	getlisteSelectionOF()->resizeColumn(2,dim - 10);
	getlisteSelectionOF()->resizeColumn(3,dim + 30);
	getlisteSelectionOF()->resizeColumn(4,dim + 35);	
    getlisteSelectionOF()->resizeColumn(5,dim - 15);
	getlisteSelectionOF()->resizeColumn(6,dim - 70);	
    getlisteSelectionOF()->resizeColumn(7,dim - 25);
	
	// SMO OK : STD-PR-OO1 : Pesee Matiere
	getlisteSelectionOF()->setItemSensitive(0,0,IlvFalse);
	getlisteSelectionOF()->setItemSensitive(1,0,IlvFalse);
	getlisteSelectionOF()->setItemSensitive(2,0,IlvFalse);
	getlisteSelectionOF()->setItemSensitive(3,0,IlvFalse);
	getlisteSelectionOF()->setItemSensitive(4,0,IlvFalse);
	getlisteSelectionOF()->setItemSensitive(5,0,IlvFalse);
	getlisteSelectionOF()->setItemSensitive(6,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(0,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(1,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(2,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(3,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(4,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(5,0,IlvFalse);
	getlisteSelectionOF()->setItemGrayed(6,0,IlvFalse);
	
	//creation des items dans la matrice
	for (int r = 1;r < 10;r++)
	{
		for (int c = 0;c < 7;c++)
		{
			IlvLabelMatrixItem* item = new IlvLabelMatrixItem("");
			getlisteSelectionOF()->set(c,r,item);
		}
	}

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
bool AdxSelection_OF::setListeSelectionOF(int index)
{
	_n1 = index;
	if(index <0)
	{
		_n1 = 0;
	}

	// purge de la matrice
	this->clearMatrix();
	// chargement de la matrice 
	bool _wretour  = this->loadMatrix();
	if ( _wretour == true )
		getlisteSelectionOF()->scrollToRow(index);
	return _wretour;

}

//---------------------------------------------------------------------------
void AdxSelection_OF::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// Si on se trouve sur la matrice, on répercute le mouse wheel
			// et on enregistre le premier élément affiché dans _n1
			Selection_OF::handleInput(event);
			_n1 = this->getlisteSelectionOF()->firstRow();
			break;
		case IlvDoubleClick:
			// Si on se trouve sur la matrice, on prends la ligne en cours
			if(getlisteSelectionOF()->pointToPosition(event.getLocation(),
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
            Selection_OF::handleInput(event);
			break;
		default:
			Selection_OF::handleInput(event);
			break;
	}
}
