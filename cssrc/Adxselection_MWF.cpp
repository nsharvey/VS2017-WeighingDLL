// ===============================================================================================================
//		Project: Sage Enterprise Management Weighing Module
//		Program: AdxSelection_MWF.cpp
//	Description: This program handles the processing needed to display the list of components to the user that 
//				 still need to be weighed
// ===============================================================================================================
//
//	DLL			Date Last		
//	Version		Modified		By						Change#		Description
//	=======		==========		====================	========	==============================================
//	6.4.2.1		03/29/2018		Neil Harvey				X3-71102	Force full component list to always be shown
//	6.4.2.0		05/28/2001		EP						V130		Original development of program

// ===============================================================================================================


#include "stdafx.h"
#include "Adxselection_MWF.h"
#include "AdxInterface.h"
#include "AdxMessage.h"
#include "AdxChoix_OF.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_Phase.h"
#include "AdxSelection_OF.h"
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
void AdxSelection_MWF::monterCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionMWF()->firstRow();
// ENG: if first-order index of the matrix <9 first-order positioning
// FRA: si index premier ordre de la matrice < 9 positionnement sur premier ordre
	if (_n1 < 10)
		setListeSelectionMWF(0);
	else
// ENG: if not go up 9
// FRA: sinon remonter de 9
		setListeSelectionMWF(_n1 - 9);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::descendreCB(IlvGraphic* g)
{
	_n1 = this->getlisteSelectionMWF()->firstRow();
	int nbComposants;
	if (getInterface()->getFonctionEnCours() == 1
		|| getInterface()->getFonctionEnCours() == 3)
		nbComposants = getInterface()->getDonnees()->getCurrentPhase()->getNbComposants();
	else
		nbComposants = getInterface()->getDonnees()->getNbComposants_Art();
// ENG: if there are orders on the next screen
// FRA: s'il y a des ordres sur l'ecran suivant
	if (_n1 < (nbComposants - 9))
		setListeSelectionMWF(_n1 + 9);
	reDraw();
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::validerCB(IlvGraphic* g)
{
	IlvUShort c;
	IlvUShort r;
	AdxData* m_data = getInterface()->getDonnees();
	AdxInterface* m_interface = getInterface();
	AdxChoix_OF* m_choix_OF = getInterface()->getChoix_OF();

// ENG: if we choose OF or fab we run on the table m_data-> getCurrentPhase () -> getcomposantList ()
// FRA: si on vient de choix par OF ou en fab on tourne sur la table m_data->getCurrentPhase()->getcomposantList()
	if (getInterface()->getFonctionEnCours() == 1 || getInterface()->getFonctionEnCours() == 3)
	{
		if (getlisteSelectionMWF()->getFirstSelected(c,r))
		{
			// ENG: _n1 (number of the first component of the table)
			// ENG: + r (selected line number starts at 1) - 1
			// FRA: _n1 (numero du premier composant du tableau) 
			// FRA: + r (numero de ligne selectionnee commence a 1) - 1
			if (r-1 < m_data->getCurrentPhase()->getNbComposants())
			{
			if (getInterface()->getChoix_OF()->controleChangementComposant(r-1))
						m_data->setCurrentComposantIndex(r-1);
            else
            {
	                    m_interface->getMessage()->setPanneauAppelant(this);
	                    m_interface->envoieMessage("&Valeur incorrecte", false);
                        return;
            } 

				quitter();
			}
		}
	}
	else if (getInterface()->getFonctionEnCours() == 2)
	{
		// ENG: SMO : STD-PR-001 : Material Weighing
		// FRA: SMO : STD-PR-OO1 : Pesee Matiere
		if (getlisteSelectionMWF()->getFirstSelected(c,r))
		{
			// ENG: r (selected line number starts at 1) - 1
			// FRA: r (numero de ligne selectionnee commence a 1) - 1
			if (r-1 < getlisteSelectionMWF()->rows())	
			{
				
				// ENG: The lines are aggregated
				// FRA: Les lignes sont agregees 
				const char* _composantSelect = getlisteSelectionMWF()->getItem(0,r)->getLabel();	// ENG: name of the selected component
																									// FRA: nom du composant selectionne

				if ( strcmp(_composantSelect, "") != 0 )
				{
					m_choix_OF ->changementComposant_Art();

					// ENG: mm 08.10 - display procedure empty box end material
					// FRA: mm 08.10 - affichage procédure vide box fin matière
					if ( m_data->getPseMatMatiereBegin() == true)
					{
						m_data->setPseMatMatiereBegin(false);
						m_data->PositionneProcedureComposantAttente();	
						m_data->lanceProcedureEnAttente();
					}

					// ENG: save component label
					// FRA: sauvegarde du libellé composant
					const char* _libComposant  = getlisteSelectionMWF()->getItem(1,r)-> getLabel();
					m_data->setCurrentComposantIndexPseMat(_composantSelect,_libComposant,r);

					// ENG: we empty the list of ISM records, that of the OFs and that of the phases.
					// FRA: on vide la liste des fiches ISM, celle des OFs et celle des phases.
					m_data->razListeFicheISM();							
					m_data->razListeOF();																			
					m_data->razListePhase();	

				 	// ENG: 90456 mm 06.2013 - Empty the list of components only in the case
					// ENG: where we recharge the .csv to ch. time
					// FRA: 90456 mm 06.2013 - Ne vider la liste des composants que dans le cas
					// FRA: où on recharge le .csv à ch. fois
					if (m_data->getChargementListMat() == 2)
						m_data->razListeComposant();
				} 	
			}
			quitter();
		}
	}
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxSelection_MWF* m_selection_MWF = m_interface->getSelection_MWF();
	AdxChoix_OF* m_choix_OF = m_interface->getChoix_OF();

	m_choix_OF->afficherOrdre(
			getInterface()->getDonnees()->getCurrentOrderIndex(),
			getInterface()->getDonnees()->getCurrentPhaseIndex(),
			getInterface()->getDonnees()->getCurrentComposantIndex());
 	m_selection_MWF->hide();
	m_choix_OF->show();
}
//---------------------------------------------------------------------------
void AdxSelection_MWF::clearMatrix()
{
	// ENG: We empty the matrix if necessary
	// FRA: On vide la matrice si besoin
	IlvUShort wnNbRow = this->getlisteSelectionMWF()->rows();
	if(wnNbRow>0)
	{
		// ENG: deleting rows
		// FRA: suppression des rows
		IlvUShort wni = wnNbRow;
		for(;wni>0;wni--)
		{
			this->getlisteSelectionMWF()->removeRow(wni);
		}
	}
}
//---------------------------------------------------------------------------
void AdxSelection_MWF::loadMatrix()
{
	if (getInterface()->getFonctionEnCours() == 1
	||  getInterface()->getFonctionEnCours() == 3)
	{
		char*					szTemp			= new char[40];
		IlvUShort				indexMax		= 0;
		IlvLabelMatrixItem*		item			= NULL;
		IlvUShort				wnj				= 0;	// ENG: index of orders!
														// FRA: index des ordres !
		IlvDim					rowHeight		= 0;
		AdxInterface*			m_interface		= getInterface();
		AdxData*				m_data			= m_interface->getDonnees();
		IlList*					composantList;
		
		composantList	= m_data->getCurrentPhase()->getComposantList();
		indexMax		= m_data->getCurrentPhase()->getNbComposants();
		
		if  ((getlisteSelectionMWF()->columns()) == 6 )
		{
			IlvLabelMatrixItem*  item = NULL;
			getlisteSelectionMWF()->reinitialize(7,1);
			item = new IlvLabelMatrixItem("");
			getlisteSelectionMWF()->set(6,0,item);
		}
		
		// ENG: SMO : 19/08/2010 : change fields according to context
		// FRA: SMO : 19/08/2010 : modification des champs en fonction du contexte
		getlisteSelectionMWF()->getItem(0,0)->setLabel("&Composant");
		getlisteSelectionMWF()->getItem(1,0)->setLabel("&Designation");
		getlisteSelectionMWF()->getItem(2,0)->setLabel("&QuantiteAPeser");
		getlisteSelectionMWF()->getItem(3,0)->setLabel("&QteRest");
		getlisteSelectionMWF()->getItem(4,0)->setLabel("&QteAllou");
		getlisteSelectionMWF()->getItem(5,0)->setLabel("&QuantiteDisponible");
		getlisteSelectionMWF()->getItem(6,0)->setLabel("&Unite");
		getlisteSelectionMWF()->setItemFillingBackground(6,1);

		// ENG: We recreate the row
		// FRA: On recré les row 
		getlisteSelectionMWF()->insertRow(1,indexMax);
		IlvRect matrixBBox;

		getlisteSelectionMWF()->boundingBox(matrixBBox,this->getTransformer());
		rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
		getlisteSelectionMWF()->sameHeight(IlvTrue);
		getlisteSelectionMWF()->setYgrid(rowHeight);

		for ( int i = 1; i <= indexMax; i++)
		{
			// ENG: to make up for the fact that the first line of the list is
			// ENG: a line of wording.
			// FRA: pour compenser le fait que la première ligne de la liste est
			// FRA: une ligne de libellé.
			wnj = i-1;
			//--------

			AdxComposant* composant = (AdxComposant*)(*composantList)[wnj];

			item = new IlvLabelMatrixItem(composant->getComposant());
			getlisteSelectionMWF()->set(0,i,item);

			item = new IlvLabelMatrixItem(composant->getLibComposant());
			getlisteSelectionMWF()->set(1,i,item);

			sprintf (szTemp, composant->getFormat(), composant->getQuantitePrevue());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionMWF()->set(2,i,item);

			sprintf (szTemp, composant->getFormat(), composant->getQuantiteRestante());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionMWF()->set(3,i,item);

			sprintf (szTemp, composant->getFormat(), composant->getQuantiteAlloueeRestante());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionMWF()->set(4,i,item);

			sprintf(szTemp, composant->getFormat(),composant->getQteDispoCompo());
			item = new IlvLabelMatrixItem(szTemp);
			getlisteSelectionMWF()->set(5,i,item);

			item = new IlvLabelMatrixItem(composant->getUnite());
			getlisteSelectionMWF()->set(6,i,item);

			// ENG: 86892 mm 02.2012   ||(strcmp (composant->getFicheISM(),"")==0)) 
			// ENG: graying or degreasing OFs totally weighed or not
			// FRA: 86892 mm 02.2013   ||(strcmp (composant->getFicheISM(),"")==0)) 
			// FRA: grisage ou degrisage des OFs totalement pesés ou non
			if (composant->getTotalementPese())
			{
				for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
				{
					getlisteSelectionMWF()->setItemSensitive(wni,i,IlvFalse);
				}
			}
			else
			{
				// ENG: Differentiation of components weighed in plants or in manufacturing
				// FRA: differenciation des compsoants pesee en centrale ou en fabrication
				if (getInterface()->getFonctionEnCours() == 3)	// ENG: weighing in manufacturing
																// FRA: pesee en fabrication
					                                            
				{
					if (composant->getCodeAServir() == 2
						|| composant->getCodeAServir() == 4
						|| composant->getCodeAServir() == 6
						|| composant->getCodeAServir() == 8)
					{
						for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
						{
							getlisteSelectionMWF()->setItemSensitive(wni,i,IlvFalse);
						}
					}
					else
					{
						for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
						{
							getlisteSelectionMWF()->setItemSensitive(wni,i,IlvTrue);
						}
					}
				}
				else	// ENG: weighed by OF
						// FRA: pesee par OF 
				{
					if (composant->getCodeAServir() == 3
						|| composant->getCodeAServir() == 5
						|| composant->getCodeAServir() == 7
						|| composant->getCodeAServir() == 9)
					{
						for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
						{
							getlisteSelectionMWF()->setItemSensitive(wni,i,IlvFalse);
						}
					}
					else
					{
						for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
						{
							getlisteSelectionMWF()->setItemSensitive(wni,i,IlvTrue);
						}
					}
				}
			}
		}
		getlisteSelectionMWF()->deSelect();
		for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
		{
			// ENG: We loop on all the rows of the column to know the longest
			// FRA: On boucle sur tous les rows de la colonne pour connaitre le plus long
			IlvDim maxColWidth = getlisteSelectionMWF()->getColumnFittingSize(wni);
			getlisteSelectionMWF()->setColumnSize(wni,maxColWidth+10);
		}
		delete [] szTemp;
	}
	else
	{
		AdxInterface*			m_interface		= getInterface();
		AdxData*				m_data			= m_interface->getDonnees();
		AdxChoix_OF*		    m_choix_OF = getInterface()->getChoix_OF();
		int						premiereLigne	= 1;
		int						nbJump          = 0;	// ENG: number of lines not taken into account
														// FRA: nombre de lignes non prises en compte
		double					NbPesee		    = 0;
		double					TotalaPeser		= 0;
		double					TotalDispo		= 0;
		int						indicetmp		= 0;

		// ENG: Before reloading the list, put the current OF in the weighing plan if necessary
		// FRA: Avant de recharger la liste, on remet l'OF courant dans le plan de pesée si necessaire
		if (( m_data->getCurrentOrder() != NULL ) &&  ( m_data->getCurrentComposant()->getQuantiteRestante() != 0))
		{
			m_choix_OF ->changementOF_Art();
		}
	    // 06.2013 mm 90456 
		if (m_data->getChargementListMat() == 2)
		{	// ENG: SMO : loading the material file for the material weighing
			// FRA: SMO : chargement du fichier des matieres pour la pesee matiere
			this->setCursor(_display->getCursor("wait"));
			m_data->sendX3_GetMatMat("");
			this->setCursor(_display->getCursor("default"));
		}
		
		char*					szTemp			= new char[40];
		IlvUShort				indexMax		= 0;
		IlvLabelMatrixItem*		item			= NULL;
		IlvUShort				wnj				= 0;	// ENG: index of orders!
														// FRA: index des ordres !
		IlvDim					rowHeight		= 0;
		IlList*					composantList;

		composantList	= m_data->getComposantList_Art();
		indexMax		= m_data->getNbComposants_Art();
		IlvRect matrixBBox;
		if  ((getlisteSelectionMWF()->columns()) == 7 )
		{
			getlisteSelectionMWF()->reinitialize(6,1);
		}

		// ENG: SMO : 19/08/2010 : change fields according to context
		// FRA: SMO : 19/08/2010 : modification des champs en fonction du contexte
		getlisteSelectionMWF()->getItem(0,0)->setLabel("&Composant");
		getlisteSelectionMWF()->getItem(1,0)->setLabel("&Designation");
		getlisteSelectionMWF()->getItem(2,0)->setLabel("&NbPesee");
		getlisteSelectionMWF()->getItem(3,0)->setLabel("&TotPesee");
		getlisteSelectionMWF()->getItem(4,0)->setLabel("&QteDispo");
		getlisteSelectionMWF()->getItem(5,0)->setLabel("&Unite");

		getlisteSelectionMWF()->boundingBox(matrixBBox,this->getTransformer());
		rowHeight = matrixBBox.h() /(this->_nbDsiplayRows + 1);
		getlisteSelectionMWF()->sameHeight(IlvTrue);
		getlisteSelectionMWF()->setYgrid(rowHeight);

		const char*  composantChoisi = m_choix_OF->getSaisieComposant_Art()->getLabel();    // ENG: screen area  
																							// FRA: zone de l'écran
	
		// ENG: sort according to the material entered
		// FRA: trier en fonction de la matière saisie

//X3-71102	=====================================================================================================
//X3-71102	Commented out below section in order to always force the full list of componenets to be displayed.
//X3-71102  Issue reported was that when choosing the last component in the lookup list; if you then clicked on
//X3-71102	the component lookup icon again, the DLL crashed.  Seems this is related to the fact that C++ holds
//X3-71102	arrays from 0 but the program is counting the actual number of components which is for example 2; the 
//X3-71102	below loop was trying to use array[2] when there wasn't any.  Decided to force all components to be
//X3-71102	displayed, thereby improving the user experience.
//X3-71102	=====================================================================================================
//X3-71102		if ( strcmp (composantChoisi ,"")!=0)
//X3-71102		{
//X3-71102			int index = m_data->getIndexComposant_Art(composantChoisi);
//X3-71102			if (index <  m_data->getNbComposants_Art())
//X3-71102			{
//X3-71102				while ( strcmp (m_data->getComposant_Art(index)->getComposant(),composantChoisi)==0)
//X3-71102				{
//X3-71102					AdxComposant* composant = (AdxComposant*)(*composantList)[index];
//X3-71102					if (!composant->getTotalementPese())
//X3-71102					{
//X3-71102						if ( premiereLigne == 1 )
//X3-71102						{
//X3-71102							indicetmp = 1;
//X3-71102							getlisteSelectionMWF()->insertRow(indicetmp,1);
//X3-71102							TotalaPeser	 = composant->getQuantiteRestante();
//X3-71102							TotalDispo	 = composant->getQteDispoCompo();
//X3-71102							NbPesee    = 1;
//X3-71102							premiereLigne = 0;
//X3-71102						}
//X3-71102						else
//X3-71102						{
//X3-71102							TotalaPeser	+= composant->getQuantiteRestante();
//X3-71102							TotalDispo  = composant->getQteDispoCompo();
//X3-71102							NbPesee++;
//X3-71102						}

//X3-71102						item = new IlvLabelMatrixItem(composant->getComposant());
//X3-71102						getlisteSelectionMWF()->set(0,indicetmp,item);
//X3-71102
//X3-71102						item = new IlvLabelMatrixItem(composant->getLibComposant());
//X3-71102						getlisteSelectionMWF()->set(1,indicetmp,item);

//X3-71102						sprintf (szTemp, "%.0f", NbPesee);
//X3-71102						item = new IlvLabelMatrixItem(szTemp);
//X3-71102						getlisteSelectionMWF()->set(2,indicetmp,item);

//X3-71102						sprintf (szTemp, composant->getFormat(), TotalaPeser);
//X3-71102						item = new IlvLabelMatrixItem(szTemp);
//X3-71102						getlisteSelectionMWF()->set(3,indicetmp,item);

//X3-71102						sprintf (szTemp, composant->getFormat(), TotalDispo);
//X3-71102						item = new IlvLabelMatrixItem(szTemp);
//X3-71102						getlisteSelectionMWF()->set(4,indicetmp,item);

//X3-71102						item = new IlvLabelMatrixItem(composant->getUnite());
//X3-71102						getlisteSelectionMWF()->set(5,indicetmp,item);
//X3-71102					}
//X3-71102					index ++;
//X3-71102				}
//X3-71102			}
			
//X3-71102		}
//X3-71102		else
//X3-71102		{

			// ENG: bring back info from all materials
			// FRA: ramener les info de l'ensemble des matières
			for ( int i = 1; i <= indexMax; i++)
			{
				// ENG: to make up for the fact that the first line of the list is
				// ENG: a line of wording.
				// FRA: pour compenser le fait que la première ligne de la liste est
				// FRA: une ligne de libellé.
				wnj = i-1;
				AdxComposant* composant = (AdxComposant*)(*composantList)[wnj];
					
				// ENG: if OF totally weighed, the component is not taken into account
				// FRA: si OF totalement pesé, le composant n'est pas pris en compte
				if (composant->getTotalementPese() == false)
				{
					if ( premiereLigne != 1 )
					{
						AdxComposant* composantprv = (AdxComposant*)(*composantList)[wnj-1-nbJump];

						// ENG: Aggregation of components to the display (cumulative OFs)
						// FRA: agregation des composants a l'affichage ( cumule des OF )
						if ( strcmp(composantprv->getComposant(), composant->getComposant()) != 0 )
						{
							// ENG:	different component, new line 
							// FRA: composant different, nouvelle ligne
							indicetmp++;
							getlisteSelectionMWF()->insertRow(indicetmp,1);
							TotalaPeser	= composant->getQuantiteRestante();
							TotalDispo	= composant->getQteDispoCompo();
							NbPesee   = 1;
						} 
						else
						{
							// ENG: same component (but OF and / or operation! =)
							// ENG: ==> aggregation of lines
							// FRA: meme composant ( mais OF et/ou operation != )
							// FRA: ==> aggregation des lignes
							TotalaPeser	+= composant->getQuantiteRestante();
							TotalDispo  = composant->getQteDispoCompo();
							NbPesee++;
						}
						nbJump = 0;
					}
					else
					{
						indicetmp = 1;
						getlisteSelectionMWF()->insertRow(indicetmp,1);
						TotalaPeser	 = composant->getQuantiteRestante();
						TotalDispo	 = composant->getQteDispoCompo();
						NbPesee    = 1;
						premiereLigne = 0;
					}

					item = new IlvLabelMatrixItem(composant->getComposant());
					getlisteSelectionMWF()->set(0,indicetmp,item);

					item = new IlvLabelMatrixItem(composant->getLibComposant());
					getlisteSelectionMWF()->set(1,indicetmp,item);

					sprintf (szTemp, "%.0f", NbPesee);
					item = new IlvLabelMatrixItem(szTemp);
					getlisteSelectionMWF()->set(2,indicetmp,item);

					sprintf (szTemp, composant->getFormat(), TotalaPeser);
					item = new IlvLabelMatrixItem(szTemp);
					getlisteSelectionMWF()->set(3,indicetmp,item);

					sprintf (szTemp, composant->getFormat(), TotalDispo);
					item = new IlvLabelMatrixItem(szTemp);
					getlisteSelectionMWF()->set(4,indicetmp,item);

					item = new IlvLabelMatrixItem(composant->getUnite());
					getlisteSelectionMWF()->set(5,indicetmp,item);

					// ENG: 86887 mm 02.2013 - if the component does not have an ISM form, is not taken into account
					// FRA: 86887 mm 02.2013 - si le composant n'a pas de fiche ISM, n'est pas pris en compte 
					if (strcmp (composant->getFicheISM(),"")==0)
					{
   						for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
   						{
							getlisteSelectionMWF()->setItemSensitive(wni,indicetmp,IlvFalse);
						}	
					}
				} 
				
				else
				{
					nbJump += 1;	// ENG: +1 line not taken into account
									// FRA: +1 ligne non prise en compte
				}
			
			}
//X3-71102		}

		getlisteSelectionMWF()->deSelect();
		for(IlvUShort wni = 0;wni<getlisteSelectionMWF()->columns();wni++)
		{
			// ENG: We loop on all the rows of the column to know the longest
			// FRA: On boucle sur tous les rows de la colonne pour connaitre le plus long
			IlvDim maxColWidth = getlisteSelectionMWF()->getColumnFittingSize(wni);
			getlisteSelectionMWF()->setColumnSize(wni,maxColWidth+10);
		}
		delete [] szTemp;
	}
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	// ENG: Evolution Chart PNG
	// ENG: Adding the background image for all windows
	// ENG: wallpaper
	// FRA: Evolution Graphique PNG
	// FRA: Ajout de l'image de fond pour toutes les fenêtres
	// FRA: fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));
	AdxData* m_data = m_interface->getDonnees();

	getlisteSelectionMWF()->showScrollBar(IlvHorizontal);
	getlisteSelectionMWF()->showScrollBar(IlvVertical);

	_nbDsiplayRows = 9;

	// ENG: SMO OK : STD-PR-OO1 : Material Weighing
	// FRA: SMO OK : STD-PR-OO1 : Pesee Matiere
	IlvDim dim = getlisteSelectionMWF()->getColumnWidth(1);
	getlisteSelectionMWF()->resizeColumn(1,dim - 25);
	getlisteSelectionMWF()->resizeColumn(2,dim + 75);
	getlisteSelectionMWF()->resizeColumn(7,dim - 50);
	getlisteSelectionMWF()->setItemSensitive(0,0,IlvFalse);
	getlisteSelectionMWF()->setItemSensitive(1,0,IlvFalse);
	getlisteSelectionMWF()->setItemSensitive(2,0,IlvFalse);
	getlisteSelectionMWF()->setItemSensitive(3,0,IlvFalse);
	getlisteSelectionMWF()->setItemSensitive(4,0,IlvFalse);
	getlisteSelectionMWF()->setItemSensitive(5,0,IlvFalse);
	getlisteSelectionMWF()->setItemSensitive(6,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(0,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(1,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(2,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(3,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(4,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(5,0,IlvFalse);
	getlisteSelectionMWF()->setItemGrayed(6,0,IlvFalse);
	
	char szFileIcons[_MAX_PATH];

	// ENG: validate button
	// FRA: bouton valider
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	IlvBitmap* bitmap = getDisplay()->readBitmap(szFileIcons);
	getvalider()->setBitmap(bitmap);

	// ENG: button go down
	// FRA: bouton descendre
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowdown.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getdescendre()->setBitmap(bitmap);

	// ENG: button up
	// FRA: bouton monter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\green_arrowup.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getmonter()->setBitmap(bitmap);

	// ENG: help button
	// FRA: bouton aide
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\question_mark.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getaide()->setBitmap(bitmap);

	// ENG: exit button
	// FRA: bouton quitter
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
void AdxSelection_MWF::selectionSuivante()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	AdxSelection_MWF* m_selection_MWF = m_interface->getSelection_MWF();

	if (m_interface->getFonctionEnCours() == 1 ||  m_interface->getFonctionEnCours() == 3)
	{	
		AdxSelection_Phase* m_selection_Phase = m_interface->getSelection_Phase();
		m_selection_Phase->setListeSelectionPhase(m_data
			->getCurrentComposant()->getIndexPhase_Art(m_data->getCurrentPhase()));
		setPanneauAppelant(this);
		m_selection_Phase->show();
 		m_selection_MWF->hide();
	} 
	else
	{
		// ENG: Weighing by material
		// ENG: we have just chosen by Art so we go on the selection screen OF
		// FRA: Pesée par matière
		// FRA: on vient de choix par Art donc on enchaine sur l'ecran de selection OF
		AdxSelection_OF* m_selection_OF = m_interface->getSelection_OF();

		// ENG: Message at the bottom of the screen
		// FRA: Message en bas d'écran
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));						string += " ";
		string += IlvGetMessage(getDisplay(), "&NOF");									string += "         - ";
		string += m_interface->getDonnees()->getCurrentComposant()->getComposant();		string += " - ";
		string += m_interface->getDonnees()->getCurrentComposant()->getLibComposant();
		m_selection_OF->getmessage()->setLabel(string);

		setPanneauAppelant(this);
 		m_selection_MWF->hide();
	}
}

//---------------------------------------------------------------------------
void AdxSelection_MWF::setListeSelectionMWF(int index)
{
	_n1 = index;
	if(index <0)
	{
		_n1 = 0;
	}

	// ENG: purge of the matrix
	// FRA: purge de la matrice
	this->clearMatrix();
	// ENG: loading the matrix
	// FRA: chargement de la matrice 
	this->loadMatrix();
	getlisteSelectionMWF()->scrollToRow(index);
}
//---------------------------------------------------------------------------
void AdxSelection_MWF::handleInput(IlvEvent& event)
{
	IlvUShort row=0,col=0;
	switch (event.type())
	{
		case IlvMouseWheel:
			// ENG: If we are on the matrix, we echo the mouse wheel
			// ENG: and we save the first element displayed in _n1
			// FRA: Si on se trouve sur la matrice, on répercute le mouse wheel
			// FRA: et on enregistre le premier élément affiché dans _n1
			Selection_MWF::handleInput(event);
			_n1 = this->getlisteSelectionMWF()->firstRow();
			break;
		case IlvDoubleClick:
			// ENG: If we are on the matrix, we take the current line
			// FRA: Si on se trouve sur la matrice, on prends la ligne en cours
			if(getlisteSelectionMWF()->pointToPosition(event.getLocation(),
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
            Selection_MWF::handleInput(event);
			break;
		default:
			Selection_MWF::handleInput(event);
			break;
	}
}