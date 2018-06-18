// AdxSelection_Phase.cpp
// ----------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
//
#include "stdafx.h"
#include "AdxSelection_Phase.h"
#include "AdxPhase.h"
#include "AdxInterface.h"
#include "AdxChoix_OF.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_LOT.h"
#include "AdxPesee_OF.h"
#include "AdxOrder.h"
#include "AdxComposant.h"
#include "AdxData.h"
#include "AdxDate.h"
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxSelection_Phase::monterCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionPhase()->firstRow();
// si index premier ordre de la matrice < 9 positionnement sur premier ordre
	if (_n1 < 10)
		setListeSelectionPhase(0);
	else
// sinon remonter de 9
		setListeSelectionPhase(_n1 - 9);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::descendreCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionPhase()->firstRow();
// s'il y a des ordres sur l'ecran suivant
	int nbPhases;
	if (getInterface()->getFonctionEnCours() == 1
		|| getInterface()->getFonctionEnCours() == 3)
		nbPhases = getInterface()->getDonnees()->getNbPhases();
	else
		nbPhases = getInterface()->getDonnees()->getCurrentComposant()->getNbPhases_Art();
	if (_n1 < (nbPhases - 9))
		setListeSelectionPhase(_n1 + 9);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::validerCB(IlvGraphic* g)
{
	IlvUShort c;
	IlvUShort r;
	AdxData* m_data = getInterface()->getDonnees();
	IlList* composantList =  m_data ->getComposantList_Art();
	AdxComposant* composant ;
	AdxChoix_OF* m_choix_OF = getInterface()->getChoix_OF();
    // 86892 mm 02.2013
	//AdxComposant*	currentComposant ; 
	
	// si on vient de choix par OF ou en fabrication on tourne sur la table m_data->getPhaseList()
	if (getInterface()->getFonctionEnCours() == 1
	||  getInterface()->getFonctionEnCours() == 3)
	{
		if (getlisteSelectionPhase()->getFirstSelected(c,r))
		{
			// _n1 (numero de la premiere phase du tableau) 
			// + r (numero de ligne selectionnee commence a 1) - 1
			if (r-1 < m_data->getNbPhases())
			{
				if (r-1 != m_data->getCurrentPhaseIndex())
				{
					if (getInterface()->getChoix_OF()->
							controleChangementPhase(r-1))
					{
						m_data->setCurrentPhaseIndex(r-1);
						m_data->setCurrentComposantIndex(0);
						// 86892 mm 02.2013 - Pas de fiche ISM liée à l'article 
						/*if (strcmp ((currentComposant = m_data-> getCurrentPhase()->getComposant(0))->getFicheISM(),"")==0)
						{
							//setListeSelectionPhase(getInterface()->getDonnees()->getCurrentPhaseIndex());
							CString string(IlvGetMessage(getDisplay(), "&Choisir"));
							string += " ";
							string += IlvGetMessage(getDisplay(),"&NOF");
							getInterface()->getSelection_OF()->getmessage()->setLabel(string);
							setPanneauAppelant(this);
							getInterface()->getSelection_OF()->show();
							this->hide();
							return;
						}*/
					}
					else
					{
						quitter();
						return;
					}
				}
				selectionSuivante();
				m_data->lanceProcedureEnAttente();
			}
		}
	} 
	else
	{		
		// il est interdit de choisir une phase si on n'a pas choisi une matière et un OF au préalable
		if ( strcmp(m_choix_OF->getSaisieComposant_Art()->getValue(),"") == 0  ||  strcmp(m_choix_OF->getSaisieNOF_Art()->getValue(),"") == 0)
		{
			getInterface()->envoieMessage("&MatiereOuOFNonRenseignee" , false);
			return;
		}
		// SMO : Pesee matiere
		if (getlisteSelectionPhase()->getFirstSelected(c,r))
		{
			if (r-1 < m_data->getNbPhases())
			{
				m_data->setCurrentPhaseIndex(r-1);
				m_data->setCurrentComposantIndex(0);
				m_data->sendX3_ChangePhase();
				quitter();
			}
		}
	}
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::quitter()
{
	AdxInterface*		m_interface			= getInterface();
	AdxSelection_Phase* m_selection_Phase	= m_interface->getSelection_Phase();
	AdxData*			m_data				= m_interface->getDonnees();

	AdxChoix_OF* m_choix_OF = m_interface->getChoix_OF();

	// si aucune phase choisie, il est temps de le faire...
	if ( m_data->getCurrentPhase()== NULL)
	{
		m_interface->envoieMessage("&PhaseNonRenseignee", false);
		setFocus(getvalider(), IlvTrue);
	 	show();
	}
	else
	{
		getInterface()->getChoix_OF()->afficherOrdre(
			m_data->getCurrentOrderIndex(),
			m_data->getCurrentPhaseIndex(),
			m_data->getCurrentComposantIndex());

		m_selection_Phase->hide();
		m_choix_OF->show();
	}
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::selectionSuivante()
{
	AdxInterface* m_interface = getInterface();
	AdxSelection_OF* m_selection_OF = m_interface->getSelection_OF();
	AdxSelection_MWF* m_selection_MWF = m_interface->getSelection_MWF();
	AdxSelection_Phase* m_selection_Phase = m_interface->getSelection_Phase();

	// SMO OK : STD-PR-OO1 : Pesee Matiere
	if (m_interface->getFonctionEnCours() == 1||  m_interface->getFonctionEnCours() == 3)
	{
		m_selection_MWF->setListeSelectionMWF(getInterface()->getDonnees()->getCurrentComposantIndex());
		
		// sr 06.02 Message de bas d'écran
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Composant1");
		m_interface->getSelection_MWF()->getmessage()->setLabel(string);
		setPanneauAppelant(this);
		m_selection_MWF->show();
 		m_selection_Phase->hide();
	}
	else 
	{
		// choix par matiere : selection composant => OF => phase
		m_selection_OF->setListeSelectionOF(getInterface()->getDonnees()->getCurrentPhaseIndex());
		
		// sr 06.02 Message de bas d'écran
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Phase1");
		m_interface->getSelection_OF()->getmessage()->setLabel(string);
		setPanneauAppelant(this);
		m_selection_OF->show();
 		m_selection_Phase->hide();
	}
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::clearMatrix()
{
	// On vide la matrice si besoin
	IlvUShort wnNbRow = this->getlisteSelectionPhase()->rows();
	if(wnNbRow>0)
	{
		// suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getlisteSelectionPhase()->removeRow(wni);
		}
	}
}
//---------------------------------------------------------------------------
void AdxSelection_Phase::loadMatrix()
{
	char* szTemp   = new char[40];
	AdxInterface*	m_interface = getInterface();
	AdxData*		m_data		= m_interface->getDonnees();
	AdxChoix_OF* m_choix_OF = getInterface()->getChoix_OF();
	IlvUShort		wnNbOrders	= m_data->getNbOrders();
	IlvDateField::IlvDateFieldFormat first;
	IlvDateField::IlvDateFieldFormat middle;
	IlvDateField::IlvDateFieldFormat last;
	char separator;
	IlvLabelMatrixItem* item = NULL;
	getInterface()->getAccueil()->getChampDate()->getFormat(first,middle,last,separator);
	//getDateField()->getFormat(first,middle,last,separator);
	IlList* phaseList;
	IlvUShort wnj = 0; // index des ordres !
	IlvDim rowHeight = 0;
	int indexMax;

	phaseList = m_data->getPhaseList();
	indexMax  = m_data->getNbPhases();

	if (m_interface->getFonctionEnCours() == 1||  m_interface->getFonctionEnCours() == 3)
	{
		// SMO : STD-PR-OO1 : 19/08/2010 : modification des champs en fonction du contexte
		getlisteSelectionPhase()->getItem(0,0)->setLabel("&NOF");
		getlisteSelectionPhase()->getItem(1,0)->setLabel("&NPoste");
		getlisteSelectionPhase()->getItem(2,0)->setLabel("&Statut");
		getlisteSelectionPhase()->getItem(3,0)->setLabel("&Date");
		getlisteSelectionPhase()->getItem(4,0)->setLabel("&NbPeseeRest");
		getlisteSelectionPhase()->getItem(5,0)->setLabel("&NbPeseeTot");
		getlisteSelectionPhase()->getItem(6,0)->setLabel("&Priorite");
	}
	else
	{
		// SMO : STD-PR-OO1 : 19/08/2010 : modification des champs en fonction du contexte
		getlisteSelectionPhase()->getItem(0,0)->setLabel("&NOF");
		getlisteSelectionPhase()->getItem(1,0)->setLabel("&NPoste");
		getlisteSelectionPhase()->getItem(2,0)->setLabel("&Statut");
		getlisteSelectionPhase()->getItem(3,0)->setLabel("&Date");
		getlisteSelectionPhase()->getItem(4,0)->setLabel("&QteRest");
		getlisteSelectionPhase()->getItem(5,0)->setLabel("&QteAllou");
		getlisteSelectionPhase()->getItem(6,0)->setLabel("&Unite");
	}

	// On recré les row 
	getlisteSelectionPhase()->insertRow(1,indexMax);
	IlvRect matrixBBox;

	getlisteSelectionPhase()->boundingBox(matrixBBox,this->getTransformer());
	rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
    getlisteSelectionPhase()->sameHeight(IlvTrue);
	getlisteSelectionPhase()->setYgrid(rowHeight);

	for ( int i = 1; i <= indexMax; i++)
	{
		// pour compenser le fait que la première ligne de la liste est
		// une ligne de libellé.
		wnj = i-1;
		//--------

		AdxPhase* phase = (AdxPhase*)(*phaseList)[wnj];

		item = new IlvLabelMatrixItem(phase->getNumOF());
		getlisteSelectionPhase()->set(0,i,item);

		sprintf (szTemp, "%d", phase->getNumPhase());
		item = new IlvLabelMatrixItem(szTemp);
		getlisteSelectionPhase()->set(1,i,item);

		item = new IlvLabelMatrixItem(phase->getLibStatut());
		getlisteSelectionPhase()->set(2,i,item);

        if (phase->getDate() != NULL)
		{
			char* wChDate = phase->getDate()->dateToChar(first, middle, last, separator);
			item = new IlvLabelMatrixItem(wChDate);
		} 
		else
		{
			item = new IlvLabelMatrixItem("");// faut il une date par défaut?
		}
		getlisteSelectionPhase()->set(3,i,item);

		// affichage different selon la pesee
		if (m_interface->getFonctionEnCours() == 1||  m_interface->getFonctionEnCours() == 3)
		{
			sprintf (szTemp, "%d", (phase->getNbComposants()- phase->getNbComposantsPeses()));
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionPhase()->set(4,i,item);

			sprintf (szTemp, "%d", phase->getNbComposants());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionPhase()->set(5,i,item);
			
			item = new IlvLabelMatrixItem(phase->getLibPriorite());
			getlisteSelectionPhase()->set(6,i,item);
		} 
		else 
		{
			sprintf (szTemp, "%.3f", phase->getQteRestaPeser());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionPhase()->set(4,i,item);

			sprintf (szTemp, "%.3f", phase->getQteAllouee());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionPhase()->set(5,i,item);

			item = new IlvLabelMatrixItem(phase->getUnite());
			getlisteSelectionPhase()->set(6,i,item);
		}


		// grisage ou degrisage des OF totalement pesees ou non
		if (phase->getTotalementPese()) 
		{
			for(IlvUShort wni = 0;wni<getlisteSelectionPhase()->columns();wni++)
			{
				getlisteSelectionPhase()->setItemSensitive(wni,i,IlvFalse);
			}
		}
		else
		{
			for(IlvUShort wni = 0;wni<getlisteSelectionPhase()->columns();wni++)
			{
				getlisteSelectionPhase()->setItemSensitive(wni,i,IlvTrue);
			}
		}
	}
	getlisteSelectionPhase()->deSelect();
	for(IlvUShort wni = 0;wni<getlisteSelectionPhase()->columns();wni++)
	{
		// On boucle sur tous les rows de la colonne pour connaitre le plus long
		IlvDim maxColWidth = getlisteSelectionPhase()->getColumnFittingSize(wni);
		getlisteSelectionPhase()->setColumnSize(wni,maxColWidth+10);
	}
	delete [] szTemp;
}

//---------------------------------------------------------------------------
void AdxSelection_Phase::init(AdxInterface* m_interface)
{
	_interface = m_interface;

	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));


	getlisteSelectionPhase()->showScrollBar(IlvHorizontal);
	getlisteSelectionPhase()->showScrollBar(IlvVertical);

	_nbDsiplayRows = 9;

	// SMO OK : STD-PR-OO1 : Pesee Matiere
	IlvDim dim = getlisteSelectionPhase()->getColumnWidth(1);
	getlisteSelectionPhase()->resizeColumn(1,dim + 80);
	getlisteSelectionPhase()->resizeColumn(2,dim - 60);
	getlisteSelectionPhase()->resizeColumn(3,dim - 30);
	getlisteSelectionPhase()->resizeColumn(4,dim - 30);
    getlisteSelectionPhase()->resizeColumn(5,dim + 40);
	getlisteSelectionPhase()->resizeColumn(6,dim + 40);	
    getlisteSelectionPhase()->resizeColumn(7,dim - 40);
	getlisteSelectionPhase()->setItemSensitive(0,0,IlvFalse);
	getlisteSelectionPhase()->setItemSensitive(1,0,IlvFalse);
	getlisteSelectionPhase()->setItemSensitive(2,0,IlvFalse);
	getlisteSelectionPhase()->setItemSensitive(3,0,IlvFalse);
	getlisteSelectionPhase()->setItemSensitive(4,0,IlvFalse);
	getlisteSelectionPhase()->setItemSensitive(5,0,IlvFalse);
	getlisteSelectionPhase()->setItemSensitive(6,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(0,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(1,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(2,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(3,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(4,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(5,0,IlvFalse);
	getlisteSelectionPhase()->setItemGrayed(6,0,IlvFalse);



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
void AdxSelection_Phase::setListeSelectionPhase(int index)
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
	getlisteSelectionPhase()->scrollToRow(index);
}
//---------------------------------------------------------------------------
void AdxSelection_Phase::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// Si on se trouve sur la matrice, on répercute le mouse wheel
			// et on enregistre le premier élément affiché dans _n1
			Selection_phase::handleInput(event);
			_n1 = this->getlisteSelectionPhase()->firstRow();
			break;
		case IlvDoubleClick:
			// Si on se trouve sur la matrice, on prends la ligne en cours
			if(getlisteSelectionPhase()->pointToPosition(event.getLocation(),
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
            Selection_phase::handleInput(event);
			break;
		default:
			Selection_phase::handleInput(event);
			break;
	}
}
