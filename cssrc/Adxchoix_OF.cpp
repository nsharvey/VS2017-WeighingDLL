// AdxChoix_OF.cpp
// ---------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
// cet ecran permet de gerer tous les choix composant pour les selections, par OF
// par Article ou en Fabrication 
// les rubriques ecrans sont activees differemment selon l'ordre de selection
// les donnees sont triees selon l'ordre des selections
//		-> Pesee par OF et Pesee en Fabrication
//		   on choisit l'OF, la Phase puis le composant
//		   zones ecrans getEtiquetteComposant(), getSaisieComposant(),
//		   getAffLibComposant(), getBoutonListeComposant(),
//		   getEtiquettePhase(), getSaisiePhase(), getBoutonListePhase()
//		   m_data->getPhaseList() et m_data->getCurrentPhase()->getComposantList
//		-> Pesee par Article
//		   on choisit le composant, l'OF puis la Phase
//		   zones ecrans getEtiquetteComposant_Art(), getSaisieComposant_Art(),
//		   getAffLibComposant_Art(), getBoutonListeComposant_Art(),
//		   getEtiquettePhase_Art(), getSaisiePhase_Art(), getBoutonListePhase_Art()
//		   m_data->getComposantList_Art() et m_data->getCurrentComposant()->getPhaseList_Art()
//--------------------------------------------------------------
#include "stdafx.h"
#include "Adxchoix_OF.h"
#include "AdxInterface.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_Phase.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_LOT.h"
#include "AdxMessage.h"
#include "AdxPesee_OF.h"
#include "AdxOrder.h"
#include "AdxPhase.h"
#include "AdxComposant.h"
#include "AdxData.h"
#include "AdxDate.h"

#include "x3centr1.h"
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
// appel de l'ecran AdxSelection_OF
void AdxChoix_OF::listeOFCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	m_interface->getSelection_OF()->setPanneauAppelant(this);
	IlvRect m_rect = 0;
	boundingBox (m_rect); 
	_champAppelant = (IlvTextField*) g;	

	// pesée par aticle : il est inderdit de choisir un n° d'OF si on n'a pas choisi de matière au préalable
	// on vérifie avant de charger l'écran de sélection des OFs
	if (m_interface->getFonctionEnCours() == 2 )
	{
		if ( strcmp(getSaisieComposant_Art()->getValue(),"")== 0 )
		{
			getInterface()->envoieMessage("&MatiereNonRenseignee" , false);
			return;
		}
	}

	// chargement de la matrice avec premiere ligne = OF en cours
	bool _wretour = m_interface->getSelection_OF()->
		setListeSelectionOF(m_interface->getDonnees()->getCurrentOrderIndex());
	if  (_wretour )
	{
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));	string += " ";
		string += IlvGetMessage(getDisplay(),"&NumeroOF1");
		
		// SMO : STD-PR-OO1 : Pesee Matiere : 03/06/2010 : ajout de l'affichage du composant dans le bordereau.
		if (m_interface->getFonctionEnCours() != 1
		&&  m_interface->getFonctionEnCours() != 3){
			string += "         - ";
			string += m_interface->getDonnees()->getPseMatCurrentMat();
			string += " - ";
			string += m_interface->getDonnees()->getPseMatCurrentMatLib();
		}

		m_interface->getSelection_OF()->getmessage()->setLabel(string);
		m_interface->getSelection_OF()->show();
		hide();
	}
}

//---------------------------------------------------------------------------
// controle de l'existence de la valeur saisie pour phase
// passage en phase courante si existe et est autorisee
// lancement de la procedure de vide de box fin de phase si obligatoire
void AdxChoix_OF::SaisiePhaseCB(IlvGraphic* g)
{
	AdxData* m_data = getInterface()->getDonnees();
	IlvBoolean error;
	int NumPhase;
    // 86892 mm 02.2013
	//AdxComposant*	currentComposant ;

	//fonctionnement totalement different quand choix_art ou choix OF
	// en premier choix_OF et Choix_Fab
	if (getInterface()->getFonctionEnCours() == 1 
	||  getInterface()->getFonctionEnCours() == 3)
	{
		NumPhase = getSaisiePhase()->getIntValue(error);
		if (NumPhase != m_data->getCurrentPhase()->getNumPhase())
		{
			// verif que NumPhase existe et changement currentPhase 
			int i = m_data->getIndexPhase(NumPhase);
			if (i < m_data->getNbPhases())
			{
				if (controleChangementPhase(i))
				{
					m_data->setCurrentPhaseIndex(i);
					m_data->setCurrentComposantIndex(0);
					// 86892 mm 02.2013 - Pas de fiche ISM liée à l'article 
					/*if (strcmp ((currentComposant = 
						m_data-> getCurrentPhase()->getComposant(0))->getFicheISM(),"")==0)
					{
						CString string(IlvGetMessage(getDisplay(), "&Choisir"));
						string += " ";
						string += IlvGetMessage(getDisplay(),"&NOF");
						getInterface()->getSelection_OF()->getmessage()->setLabel(string);
						getInterface()->getSelection_OF()->show();
						this->hide();
						return;
					}
					else
					{*/
						afficherOrdre(m_data->getCurrentOrderIndex(),
									  m_data->getCurrentPhaseIndex(),
									  m_data->getCurrentComposantIndex());
						m_data->lanceProcedureEnAttente();
						return;
					//}
				}
			}
			// sinon remise de NumOF a valeur courante 

			getSaisiePhase()->setValue((IlvInt)m_data->getCurrentPhase()->getNumPhase());
			bufferedDraw(getSaisiePhase());
			envoieMessage("&Valeur incorrecte",false);
		}
	}
	else
	{
		// il est interdit de choisir une phase si on n'a pas choisi une matière et un OF au préalable
		if ( strcmp(getSaisieComposant_Art()->getValue(),"") == 0  ||  strcmp(getSaisieNOF_Art()->getValue(),"") == 0)
		{
			getInterface()->envoieMessage("&MatiereOuOFNonRenseignee" , false);
			return;
		}

		// verif que NumPhase existe
		NumPhase = getSaisiePhase_Art()->getIntValue(error);
		if (NumPhase != 0)
		{
			for (int i = 0 ; i < m_data->getNbPhases(); i ++ )
			{
				if (NumPhase == m_data->getPhase(i)->getNumPhase() )
				{
					m_data->setCurrentPhaseIndex(i); 
					afficherOrdre(m_data->getCurrentOrderIndex(),
						  m_data->getCurrentPhaseIndex(),
						  m_data->getCurrentComposantIndex());
					return;	
				}
			}
		}
		// sinon remise de NumPhase à la valeur courante 
		if (m_data->getCurrentPhase()!= NULL)
			getSaisiePhase_Art()->setValue((IlvInt)m_data->getCurrentPhase()->getNumPhase());
		else
		{
			m_data->setCurrentPhaseIndex(0); 
			afficherOrdre(m_data->getCurrentOrderIndex(),
								  m_data->getCurrentPhaseIndex(),
								  m_data->getCurrentComposantIndex());
		}
		bufferedDraw(getSaisiePhase_Art());
		envoieMessage("&Valeur incorrecte",false);
	}
}

//---------------------------------------------------------------------------
// constitution du bandeau des messages
void AdxChoix_OF::EntreeTextFieldCB(IlvGraphic* g)
{
	_champAppelant = (IlvTextField*) g;	
	CString string(IlvGetMessage(getDisplay(), "&Saisir"));
	string += " ";
	if (_champAppelant == getSaisieNOF() || _champAppelant == getSaisieNOF_Art())
		string += IlvGetMessage(getDisplay(),"&NumeroOF1");
	if (_champAppelant == getSaisieComposant() || _champAppelant == getSaisieComposant_Art())
		string += IlvGetMessage(getDisplay(),"&Composant1");
	getmessage()->setLabel(string);
	bufferedDraw(getmessage());
	
	if (_champAppelant == getSaisieNOF_Art())
	{
		// si aucune matière saisie, on chaîne vers le tableau de sélection article pour empêcher de saisir un n° d'OF
		if (strcmp(getSaisieComposant_Art()->getLabel(), "")==0) 
		{
			listeComposantCB(g);
			getInterface()->envoieMessage("&MatiereNonRenseignee" , false);
			return;
		}
	}
}

//---------------------------------------------------------------------------	
// constitution du bandeau des messages
void AdxChoix_OF::EntreeNumberFieldCB(IlvGraphic* g)
{
	_champAppelant = (IlvNumberField*) g;
	CString string(IlvGetMessage(getDisplay(), "&Saisir"));
	string += " ";
	if (_champAppelant == getSaisiePhase() || _champAppelant == getSaisiePhase_Art())
		string += IlvGetMessage(getDisplay(),"&Phase1");
	getmessage()->setLabel(string);
	bufferedDraw(getmessage());

	if (_champAppelant == getSaisiePhase_Art())
	{
		// si aucune matière saisie , on chaîne vers le tableau de sélection article pour empêcher de saisir un n° d'opération
		if (strcmp(getSaisieComposant_Art()->getLabel(), "")==0) 
		{
			listeComposantCB(g);
			return;
		}
		// idem avec le n° d'OF
		if (strcmp(getSaisieNOF_Art()->getLabel(),"")==0)
		{
			listeOFCB(g);
			return;
		}
	}
}

//---------------------------------------------------------------------------
// controle de l'existence de la valeur saisie pour composant
// passage en composant courant si existe et est autorise
void AdxChoix_OF::SaisieComposantCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = getInterface()->getDonnees();
	AdxChoix_OF* m_choix_OF = m_interface->getChoix_OF();
	const char* Composant;
	
	//fonctionnement totalement different quand choix_art ou choix OF
	// en premier choix_OF et Choix_Fab
	if (getInterface()->getFonctionEnCours() == 1
	||  getInterface()->getFonctionEnCours() == 3)
	{
		Composant = getSaisieComposant()->getLabel();
		if (strcmp(Composant,m_data->getCurrentComposant()->getComposant())){
			// verif que Composant existe et changement currentComposant 
			int i = m_data->getCurrentPhase()->getIndexComposant(Composant);
			if (i < m_data->getCurrentPhase()->getNbComposants())
			{
				if (controleChangementComposant(i))
				{
					m_data->setCurrentComposantIndex(i);
					afficherOrdre(m_data->getCurrentOrderIndex(),
								  m_data->getCurrentPhaseIndex(),
								  m_data->getCurrentComposantIndex());
					return;
				}
			}
			
			// sinon remise du composant a la valeur courante	
			getSaisieComposant()->setLabel(m_data->getCurrentComposant()->getComposant());
			bufferedDraw(getSaisieComposant());
			envoieMessage("&Valeur incorrecte",false);
		}
	} 
	// pesée par article
	else if (getInterface()->getFonctionEnCours() == 2)
	{
		Composant = getSaisieComposant_Art()->getLabel();
		//controle du composant en cas de pesée par matière : seul le composant est alimenté à ce stade( pas de n° OF, pas de phase)
		// il faut contrôler que le composant choisi appartient à la liste des composants, sinon valeur incorrecte.
		if (strcmp(Composant, "") !=0)
		{
			// Avant de recharger la liste, on remet l'OF courant dans le plan de pesée si necessaire
			if (( m_data->getCurrentOrder() != NULL ) &&  ( m_data->getCurrentComposant()->getQuantiteRestante() != 0))
			{
				m_choix_OF ->changementOF_Art();
			}

			// 06.2013 mm 90456 
			if (m_data->getChargementListMat() == 2)
			{
				// chargement de la liste de sélection des matieres 
				// APCPRD 2372 - mm 10.12 - ajout du composant en paramètre
			 	this->setCursor(_display->getCursor("wait"));
				m_data->sendX3_GetMatMat(Composant);
				this->setCursor(_display->getCursor("default"));
			}

			int index = m_data->getIndexComposant_Art(Composant);
			if (index != m_data->getNbComposants_Art())
			{
  				// 86887 mm 02.2013 -> pas de fiche ISM renseignée, on ne va pas plus loin
				if ( strcmp( m_data->getComposant_Art(index)->getFicheISM() , "") == 0) 
				{
					envoieMessage("&ArticleSansFicheISM",false);	
					return;
				}
				changementComposant_Art();

				// mm 08.10 - affichage procédure vide box fin matière
				if ( m_data->getPseMatMatiereBegin() == true)
				{
					m_data->setPseMatMatiereBegin(false);
					m_data->PositionneProcedureComposantAttente();	
					m_data->lanceProcedureEnAttente();
				}

				//récupération du libellé composant
				const char* _composant =  m_data->getComposant_Art(index)->getComposant();
				const char* _libComposant  =   m_data->getComposant_Art(index)->getLibComposant();
				// sauvegarde du composant + libellé
				m_data->setCurrentComposantIndexPseMat(_composant,_libComposant,0);

				//on vide la liste des fiches ISM, celle des OFs, celle des phases.
				m_data->razListeFicheISM();							
				m_data->razListeOF();																			
				m_data->razListePhase();
				// 90456 mm 06.2013 - Ne vider la liste des composants que dans le cas
				// où on recharge le .csv à ch. fois
				if (m_data->getChargementListMat() == 2)
					m_data->razListeComposant();

				m_choix_OF->afficherOrdre(
					getInterface()->getDonnees()->getCurrentOrderIndex(),
					getInterface()->getDonnees()->getCurrentPhaseIndex(),
					getInterface()->getDonnees()->getCurrentComposantIndex());
				return;
			}
			// 86887 mm 02.2013 
			envoieMessage("&Valeur incorrecte",false);
			
			//  remise du composant a la valeur courante	
			if ( strcmp (m_data->getPseMatCurrentMat(),"") != 0) 
			{
				getSaisieComposant_Art()->setLabel(m_data->getPseMatCurrentMat());
				getAffLibComposant_Art()->setLabel(m_data->getPseMatCurrentMatLib());
				bufferedDraw(getSaisieComposant_Art());
				bufferedDraw(getAffLibComposant_Art());
			}
			// si aucun composant, on chaîne vers le tableau de sélection des composants
			else	
			{
				listeComposantCB(g);
			}			
		}
		
	}
}

//---------------------------------------------------------------------------
void AdxChoix_OF::quitterCB(IlvGraphic* g)
{
	quitter();
}

//---------------------------------------------------------------------------
// appel de l'ecran AdxClavier_Tactile
void AdxChoix_OF::TactileCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	IlvRect m_rect = 0;
	boundingBox (m_rect);
	initClavier_Tactile();
	m_interface->getClavier_Tactile()->show();
	this->hide();
}

//---------------------------------------------------------------------------
// controle de l'existence de la valeur saisie pour OF
// passage en OF courant si existe et est autorise
// lancement de la procedure de vide de box fin d'OF si obligatoire
void AdxChoix_OF::SaisieNOFCB(IlvGraphic* g)
{
	AdxData* m_data = getInterface()->getDonnees();
	// 86892 mm 02.2013
	//AdxComposant*	currentComposant ;

	if (getInterface()->getFonctionEnCours() == 1 ||  getInterface()->getFonctionEnCours() == 3)
	{
		const char* NOF = getSaisieNOF()->getLabel();
		if (strcmp(NOF,m_data->getCurrentOrder()->getNumOF()))
		{
			// verif que NOF existe et changement currentOrder 
			int i = m_data->getIndexNumOF(NOF);
			if (i<m_data->getNbOrders())
			{
				if (controleChangementOF(i))
				{
					m_data->setCurrentOrderIndex(i);
					m_data->setCurrentPhaseIndex(0);
					m_data->setCurrentComposantIndex(0);
					// 86892 mm 02.2013 - Pas de fiche ISM liée à l'article 
					/*if (strcmp ((currentComposant = 
						m_data-> getCurrentPhase()->getComposant(0))->getFicheISM(),"")==0)
					{
						CString string(IlvGetMessage(getDisplay(), "&Choisir"));
						string += " ";
						string += IlvGetMessage(getDisplay(),"&NOF");
						getInterface()->getSelection_OF()->getmessage()->setLabel(string);
						getInterface()->getSelection_OF()->show();
						this->hide();
						return;
					}
					else
					{*/
						afficherOrdre(m_data->getCurrentOrderIndex(),
									  m_data->getCurrentPhaseIndex(),
									  m_data->getCurrentComposantIndex());
						m_data->lanceProcedureEnAttente(); 
						return;
					//}
				}
			}
			// sinon remise de NumOF a valeur courante 
			
			getSaisieNOF()->setLabel(m_data->getCurrentOrder()->getNumOF());
			bufferedDraw(getSaisieNOF());
			envoieMessage("&Valeur incorrecte",false);
		}
	} 
	else if (getInterface()->getFonctionEnCours() == 2)
	{
		// verif que NOF existe.
		const char* NOF = getSaisieNOF_Art()->getLabel();
		if (strcmp(NOF, "") !=0)
		{	
			// Avant de recharger la liste, on remet l'OF courant dans le plan de pesée
			if (( m_data->getCurrentOrder() != NULL ) && ( m_data->getCurrentComposant()->getQuantiteRestante() != 0))
				changementOF_Art();
			//on vide la liste des fiches ISM, celle des OFs, celle des phases.
			m_data->razListeFicheISM();							
			m_data->razListeOF();																			
			m_data->razListePhase();	
			// 90456 mm 06.2013 - Ne vider la liste des composants que dans le cas
			// où on recharge le .csv à ch. fois
			if (m_data->getChargementListMat() == 2)
				m_data->razListeComposant();

			// chargement de la liste de sélection des OFs 
			m_data->sendX3_GetMatOF();
			for (int i = 0 ; i < m_data->getNbOrders(); i ++ )
			{
				if (strcmp(NOF ,   m_data->getOrder(i)->getNumOF())==0)
				{
					m_data->setCurrentOrderIndex(i);
					if ( m_data->getNbPhases() == 1 && m_data->getNbComposants_Art()==1 )
					{
						// si une seule phase on la selectionne automatiquement et on revient au menu OF
						m_data->setCurrentPhaseIndex(0); 
						m_data->setCurrentComposantIndex(0); 
						afficherOrdre(m_data->getCurrentOrderIndex(),
								  m_data->getCurrentPhaseIndex(),
								  m_data->getCurrentComposantIndex());
					}
					else
					{
						AdxSelection_OF* m_selection_OF = getInterface()->getSelection_OF();
						m_selection_OF->selectionSuivante();
					}
					return;
		}
			}
			// la saisie du n° of est KO : ouverture du tableau de sélection des n° OF
			if ( strcmp(getSaisieComposant_Art()->getValue(),"")!= 0)
			{
				envoieMessage("&Valeur incorrecte",false);
				listeOFCB(g);
			}
			
		}
	}
}

//---------------------------------------------------------------------------
// dernier controle que le composant en cours  peut etre pese
// allocation des stocks si elle n'a pas ete faite par le bouton allocation
// affichage de l'ecran de pesee
void AdxChoix_OF::ValidationCB(IlvGraphic* g)
{	 
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	AdxChoix_OF* choixOF = m_interface->getChoix_OF();
	
    // mm 02.2013 - enrichissement de la trace       	
    if (getInterface()->getTraceMode() == 1)
	{
		switch( getInterface()->getFonctionEnCours() )
		{
			case 1: // pesée par OF
					getInterface()->_traceFile << "Pesée par OF:"<< endl;
					break;
			case 2: // pesée par article
					getInterface()->_traceFile << "Pesée par article:"<<endl;
					break;
			case 3: // pesée en fabrication
					getInterface()->_traceFile << "Pesée en fabrication:"<<endl;
					break;
		}
	}
	// si pesée par article, on vérifie qu'une matière, un n° d'OF et une phase aient été renseignés
	if ( getInterface()->getFonctionEnCours() ==  2 )
	{
		if ( strcmp(getSaisieNOF_Art()->getValue(),"")== 0 ||
			strcmp(getSaisiePhase_Art()->getValue(),"")== 0 ||
			strcmp(getSaisieComposant_Art()->getValue(),"")== 0 )
		{
			envoieMessage("&ChampsOFPhaseMatiereNonRenseignes"  , false);
			show();
			return;
		}
	}

	// 115769 mm 04.2016 
	if ( getInterface()->getFonctionEnCours() !=  2 )
	{
		if (m_data->getLockedOrder() != NULL)
		{
			if (strcmp(m_data->getLockedOrder()->getNumOF(), getSaisieNOF()->getValue()) ==0)
			{
				envoieMessage("&NouvelOF",false);
				return;
			}
		}
	}

	if (m_data->getCurrentComposant()->getTotalementPese()) 
	{
		envoieMessage("&ComposantTotalementPese", false);
		return;
	}

	if (controleNouveauComposant(m_data->getCurrentComposantIndex()) == false)
	{
		envoieMessage("&ComposantDeCodeAServirInvalide", false);
		return;
	}
	// sr 02.02 Si excipient ou QSP et quantité à peser = 0
	// il faut  en automatique envoyer le message pour solder la matière à l'OF 
	if ((m_data->getCurrentComposant()->getQuantiteTheorique() == 0)
		&&(m_data->getCurrentComposant()->getCodeAServir() >= 4))
	{
		validationPeseeAutomatique();
		envoieMessage("&SoldeAutomatiqueEffectue", false);
		return;
	}
	//verification allocations ont ete faites ou les lancer en auto.
	// pour les excipients et QSP on redemande systématiquement l'allocation avec la nouvelle qté calculée
	// 89316 mm 04.2013 - Ne pas renvoyer systématiquement vers allocations auto en cas de matière type excipients
	// ou QS : provoque la perte des allocations manuelles
	AdxPesee_OF* peseeOF = m_interface->getPesee_OF();
	IlvRect m_rect = 0;

	if (m_data->getComposantAlloue() == false) 
    {
		IlvBoolean err;
		m_interface->setPanneauAppelant(this);
		bool dataOK = m_data->acquisitionLots(getAffQuantiteAPeser()->getFloatValue(err));
		m_data->setComposantAlloue(dataOK);
		if (m_data->getCurrentComposant()->getQuantiteAllouee() == 0)
		{	
			// APCPRD-2438 mm 09.2013
			if (( m_data->getPrioriteAllocationCode() == 1 )
				&& (m_data->getCurrentComposant()->getLotAlloueInvalide()!= 0)
				&& (m_data->getAllocationAutoCode() == 2))
			{
				m_data->setComposantAlloue(true);
				// 92824 mm 02.2014 - construction du message dans une variable
				char* message = new char[80];
				switch (m_data->getCurrentComposant()->getLotAlloueInvalide())
				{
					case 1 :
						sprintf(message,"%s : %s ",
								IlvGetMessage(m_interface->getDisplay(),"&AllocationInvalide"),
								IlvGetMessage(m_interface->getDisplay(),"&LotAllouePerime"));
						break;
					case 2 :
						sprintf(message,"%s : %s ",
								IlvGetMessage(m_interface->getDisplay(),"&AllocationInvalide"),
								IlvGetMessage(m_interface->getDisplay(),"&melangeLotsInterdit"));
						break;
					case 3 :
						sprintf(message,"%s : %s ",
								IlvGetMessage(m_interface->getDisplay(),"&AllocationInvalide"),
								IlvGetMessage(m_interface->getDisplay(),"&lotNonconsommable"));
						break;
					
				}
				m_interface->envoieMessage(message,false);
				delete [] message;
				boundingBox (m_rect);
				peseeOF->chargement(); 
				peseeOF->show();
				hide();
				return;
			}
			// mm 02.11 - magasin avancé : on peut arriver dans l'écran de pesée sans avoir alloué
			m_data->setComposantAlloue(false);
			if (m_data->getAllocationAutoCode() == 2)
			{
				// SR 03.12 APCPRD-988 Positionner la variable pour tests dans Pesee_OF
				m_data->setOkToContinue(false);
				m_interface->getMessage()->setPanneauAppelant(NULL);
				m_interface->envoieMessage("&AllocationInvalide",false);
				return;
			}
		}
		if (dataOK == false)
		{
			// SR 03.12 APCPRD-988 Positionner la variable pour tests dans Pesee_OF
			m_data->setOkToContinue(false);
			envoieMessage("&EchecLots", false);
			return;
		}
	}

	boundingBox (m_rect);
	peseeOF->chargement(); 
	peseeOF->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxChoix_OF::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
// appel de l'ecran AdxSelection_Phase
void AdxChoix_OF::listePhaseCB(IlvGraphic* g)
{
 	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	m_interface->getSelection_Phase()->setPanneauAppelant(this);
	IlvRect m_rect = 0;
	boundingBox (m_rect);

	// chargement de la matrice avec premiere ligne = Phase en cours
	if (m_interface->getFonctionEnCours() == 1 ||  m_interface->getFonctionEnCours() == 3)
	{
		m_interface->getSelection_Phase()->setListeSelectionPhase(m_data->getCurrentPhaseIndex());
	} 
	else
	{
		// il est inderdit de choisir une phase si on n'a pas choisi une matière et un OF au préalable
		if ( strcmp(getSaisieComposant_Art()->getValue(),"")== 0 || strcmp(getSaisieNOF_Art()->getValue(),"") == 0 )
		{
			m_interface->envoieMessage("&MatiereOuOFNonRenseignee" , false);
			return;
		}
		m_interface->getSelection_Phase()->setListeSelectionPhase(m_data->getCurrentComposant()->getIndexPhase_Art(m_data->getCurrentPhase()));
	}

	CString string(IlvGetMessage(getDisplay(), "&Choisir"));
	string += " ";
	string += IlvGetMessage(getDisplay(),"&Phase1");
	
	// SMO : STD-PR-OO1 : Pesee Matiere : 03/06/2010 : ajout de l'affichage du composant dans le bordereau.
	if (m_interface->getFonctionEnCours() != 1
	&&  m_interface->getFonctionEnCours() != 3){	
		string += "         - ";
		string += m_interface->getDonnees()->getPseMatCurrentMat(); 
		string += " - ";
		string += m_interface->getDonnees()->getPseMatCurrentMatLib(); 
	}

	m_interface->getSelection_Phase()->getmessage()->setLabel(string);
	m_interface->getSelection_Phase()->show();
	hide();
}

//---------------------------------------------------------------------------
// appel a l'effet tunnel vers les fiches techniques de X3 avec la derniere procedure facultative retenue
void AdxChoix_OF::VideBoxCB(IlvGraphic* g)
{
	AdxData* m_data = getInterface()->getDonnees();
	if (m_data->getIndicateurProcedure() != 0)
	{
		getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
		m_data->SendX3_Procedure(m_data->getIndicateurProcedure());
	}
}

//---------------------------------------------------------------------------
// controle que le composant courant peut etre pese
// allocation si ca n'a pas ete deja fait
// appel de l'ecran AdxSelection_LOT
void AdxChoix_OF::AllouerCB(IlvGraphic* g)
{
    AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();

	// si pesée par article, on vérifie qu'une matière, un n° d'OF et une phase aient été renseignées
	if ( m_interface->getFonctionEnCours() ==  2 )
	{
		if ( strcmp(getSaisieNOF_Art()->getValue(),"")== 0 ||
			strcmp(getSaisiePhase_Art()->getValue(),"")== 0 ||
			strcmp(getSaisieComposant_Art()->getValue(),"")== 0 )
		{
			envoieMessage("&ChampsOFPhaseMatiereNonRenseignes"  , false);
			show();
			return;
		}
	}

	if (m_data->getCurrentComposant()->getTotalementPese())
	{
		envoieMessage("&ComposantTotalementPese", false);
		return;
	}

	if (controleNouveauComposant(m_data->getCurrentComposantIndex()) == false)
	{
		envoieMessage("&ComposantDeCodeAServirInvalide", false);
		return;
	}

	m_interface->getSelection_LOT()->setPanneauAppelant(this);
	
	IlvRect m_rect = 0;
	boundingBox (m_rect);

	// demande de mise a jour du fichier lot
	if (m_data->getComposantAlloue() == false) 
	{
		IlvBoolean err;
		m_interface->setPanneauAppelant(this);
		bool dataOK = m_data->acquisitionLots(getAffQuantiteAPeser()->getFloatValue(err));
		m_data->setComposantAlloue(true);	// même si echec pour sortie correcte
	}

	// mm 02.11 - magasin avancé 
	// priorité aux allocations de l'OF
	CString string;
	if ( m_data->getPrioriteAllocationCode() == 1
		&& m_data->getCurrentComposant()->getQuantiteAlloueeDpOF() !=0 )
	{
		if (m_data->getCurrentComposant()->getQuantiteAlloueeRestante()!=0)
		{
			m_interface->getSelection_LOT()->chargement(false);
			string+= IlvGetMessage(getDisplay(), "&ConsultationSansSelection");
		}
		else
			// chargement de la matrice avec premiere ligne = premier Lot
			m_interface->getSelection_LOT()->chargement(true);
	}
	else
	{
		// chargement de la matrice avec premiere ligne = premier Lot
		m_interface->getSelection_LOT()->chargement(true);
	}
	// permet de remettre à vide le label s'il avait été valorisé dp AdxPesee_OF::ListeLotCB()
	m_interface->getSelection_LOT()->getmessage()->setLabel(string);
	bufferedDraw(getmessage());
	//
	m_interface->getSelection_LOT()->show();
	hide();
	string.Empty();
	if(m_data->getCurrentComposant()->getQuantiteAllouee() == 0)
	{
		m_data->setComposantAlloue(false);	
	}
}
 
//---------------------------------------------------------------------------
// appel de l'ecran AdxSelection_MWF
void AdxChoix_OF::listeComposantCB(IlvGraphic* g)
{	
    AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	m_interface->getSelection_MWF()->setPanneauAppelant(this);
	IlvRect m_rect = 0;
	boundingBox (m_rect);

// chargement de la matrice avec premiere ligne = Composant en cours
	if (m_interface->getFonctionEnCours() == 1 || m_interface->getFonctionEnCours() == 3)
		m_interface->getSelection_MWF()->
			setListeSelectionMWF(m_data->getCurrentComposantIndex());
	else
	{
		// changement de matière
		if (m_data->getCurrentComposant()!= NULL)
			m_data->setPseMatCurrentMatIndexComposant(0);
		// cas où l'indice de la ligne courante est supérieur au nb max de lignes du tableau : ré-initialiser à zéro l'indice
		if  ( m_data->getPseMatCurrentMatIndexComposant() > m_interface->getSelection_MWF()->getlisteSelectionMWF()->rows())
			m_interface->getSelection_MWF()->setListeSelectionMWF(0);
		else
			m_interface->getSelection_MWF()
				->setListeSelectionMWF( m_data->getPseMatCurrentMatIndexComposant());
	}
	CString string(IlvGetMessage(getDisplay(), "&Choisir"));
	string += " ";
	string += IlvGetMessage(getDisplay(),"&Composant1");
	m_interface->getSelection_MWF()->getmessage()->setLabel(string);
	m_interface->getSelection_MWF()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxChoix_OF::initClavier_Tactile()
{
	AdxClavier_Tactile* tactile = getInterface()->getClavier_Tactile();
	tactile->setPanneauAppelant(this);
// 4 appels possibles du clavier dans Choix_OF
	if (_champAppelant == getSaisieNOF() || _champAppelant == getSaisieNOF_Art() )
	{
		tactile->setSaisie(getSaisieNOF()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&NumeroOF1");
		tactile->getchampMessage()->setLabel(string);
	}
	if (_champAppelant == getSaisiePhase() || _champAppelant == getSaisiePhase_Art())
	{
		tactile->setSaisie("");
		tactile->setAlpha(IlvFalse);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Phase1");
		tactile->getchampMessage()->setLabel(string);
	}
	if (_champAppelant == getSaisieComposant())
	{
		tactile->setSaisie(getSaisieComposant()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Composant1");
		tactile->getchampMessage()->setLabel(string);
	}
	if (_champAppelant == getSaisieComposant_Art())
	{
		tactile->setSaisie(getSaisieComposant_Art()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Composant1");
		tactile->getchampMessage()->setLabel(string);
	}
	tactile->getchampSaisie()->setLabel(tactile->getSaisie());
	tactile->reDrawObj(tactile->getchampSaisie());
}

//---------------------------------------------------------------------------
bool AdxChoix_OF::envoieMessage(CString mess, bool OUINON)
{
	AdxInterface* m_interface = getInterface();
	m_interface->getMessage()->setPanneauAppelant(this);
	return (m_interface->envoieMessage(mess, OUINON));
}

//---------------------------------------------------------------------------
// les controles de nouvelIndex 
// nouvelIndex > nbOrders correspond a la sortie de la fonction => pas d'OF suivant
bool AdxChoix_OF::controleChangementOF(int nouvelIndex)
{
	bool retour = IlvFalse;
// ici on controle que l'OF est fini pour lancer les impressionsfin OF et vide Box
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();

// on ne peut se positionner sur un OF qui est deja totalement pese
// sr 06.02 mis en commentaire suite à FI n° 27
// On se positionne malgré tout des fois qu'une pesée ait été annulées
// sur un autre poste	
/*
	if (nouvelIndex < m_data->getNbOrders())	
		if (m_data->getOrder(nouvelIndex)->getTotalementPese())
		{
			envoieMessage("&OFTotalementPese", false);
			return retour;
		}
*/

	if (m_data->getOrderBegin() == true)
// pesee partielle de l'OF	
	{
		if(envoieMessage("&PeseePartielleOF", true))
// si oui impression pesee partielle d OF 
// procedure vide de Box fin d OF
		{
			interruptionOF();
			retour = true;
		}
// sinon on maintiendra l OF en cours
	}
	else
// pesee normale ou pas de pesee du tout
// sr 05.02 FI n° 17
// Si on sort de la centrale (nouvelIndex > NbOrders)
// et que l'OF courant est "en cours" il faut le remettre dans le plan de pesée
	{
		retour = IlvTrue;
		if (m_data->getComposantAlloue())
			if (m_data->getCurrentOrder()->getTotalementPese() == true)
				interruptionComposant();
			else
			{
				if (nouvelIndex < m_data->getNbOrders())
					changementOFNonPese(m_data->getOrder(nouvelIndex));
				else
				{
					changementOFNonPese(NULL);
				}
			}
		else
		{
			if (m_data->getCurrentOrder()->getTotalementPese() == false)	// 47764 mm 07.08 - Statut OF KO
			{
				if (nouvelIndex < m_data->getNbOrders())
					changementOFNonPese(m_data->getOrder(nouvelIndex));
				else
						changementOFNonPese(NULL);
			}
		}
	}
		
	return retour;
}

//---------------------------------------------------------------------------
// controle utilise pour Choix_OF, Choix_Fab => index dans m_data->getPhaseList()
bool AdxChoix_OF::controleChangementPhase(int nouvelIndex)
{
	bool retour = IlvFalse;
	AdxData* m_data = getInterface()->getDonnees();
	AdxComposant* composantCentrale;
	AdxPhase* phaseControlee = m_data->getPhase(nouvelIndex);

// en pesee en fabrication on ne peut peser une phase tant que tous ces composants 
//	a peser en centrales ne sont pas peses
	if (getInterface()->getFonctionEnCours() == 3)
	{
		for (int i = 0; i < phaseControlee->getNbComposants(); i++)
		{
			composantCentrale = phaseControlee->getComposant(i);
			if (composantCentrale->getCodeAServir() == 2
				|| composantCentrale->getCodeAServir() == 4
				|| composantCentrale->getCodeAServir() == 6
				|| composantCentrale->getCodeAServir() == 8)
				if (!composantCentrale->getTotalementPese())
					return retour;
		}
	}

// on ne peut se positionner sur une phase qui est deja totalement pesee
	if (phaseControlee->getTotalementPese())
	{
		envoieMessage("&PhaseTotalementPesee", false);
		setFocus(getSaisiePhase());
		return retour;
	}
	
// ici on controle que la phase est finie pour lancer les impressions fin phase et vide Box
	if ( m_data->getPhaseBegin() == true)
// pesee partielle de la phase	
	{
		if (envoieMessage("&PeseePartiellePhase",true))
// si oui impression pesee partielle de la phase 
// procedure vide de Box fin de phase
		{
			interruptionPhase();
			retour = IlvTrue;
		}
// sinon on maintiendra la phase en cours
	}
	else
// la phase a ete entierement pesee ou pas pesee du tout
	{
		retour = IlvTrue;
		if (m_data->getComposantAlloue())
			interruptionComposant();
	}
	return retour;
}
//---------------------------------------------------------------------------
// controle utilise pour Choix_OF, Choix_Fab => index dans m_data->getCurrentPhase()->getComposantList()
bool AdxChoix_OF::controleChangementComposant(int nouvelIndex)
{
	bool retour = IlvFalse;
	// ici on controle que l'OF est fini pour lancer les impressions fin phase et vide Box
	AdxData* m_data = getInterface()->getDonnees();

	// on ne peut se positionner sur un composant qui est deja totalement pese
	if (m_data->getCurrentPhase()->getComposant(nouvelIndex)->getTotalementPese())
	{
		envoieMessage("&ComposantTotalementPese", false);
		return retour;
	}

	// pesee partielle du composant	
	if ( m_data->getComposantBegin() == true)
	{
		// si oui desallocation du composant
		if (envoieMessage("&PeseePartielleComposant?",true))
		{
			interruptionComposant();
			retour = IlvTrue;
		}
		// sinon on maintiendra la phase en cours
	}
	else 
	{
		// composant non pese -> changement autorise
		retour = IlvTrue;
		if (m_data->getComposantAlloue())
			interruptionComposant();
	}

	if (retour == true)
		retour = controleNouveauComposant(nouvelIndex);
	return retour;
}
//---------------------------------------------------------------------------
void AdxChoix_OF::changementComposant_Art()
{
	AdxData* m_data = getInterface()->getDonnees();

	if ( m_data->getCurrentOrder() != NULL)
	{
		changementOF_Art();
		// réinitialisation des zones de l'écran
		chargementZonesAVide();
	}
}
//---------------------------------------------------------------------------
void AdxChoix_OF::changementOF_Art()
{	
	AdxData* m_data = getInterface()->getDonnees();

	if (m_data->getOrderBegin() == true)
	{
		// pesée partielle du composant
		m_data->setPhaseBegin(false);
		m_data->SendX3_InterruptionOF();
		m_data->setOrderBegin(false);
	}
	// composant non pesé mais OF en cours de pesée
	else 
	{
	 	if (m_data->getCurrentOrder()->getTotalementPese() == false)
			changementOFNonPese(NULL);  
	}
}

//---------------------------------------------------------------------------
// controle utilise pour Choix_OF, Choix_Fab => index dans m_data->getCurrentPhase()->getComposantList()
bool AdxChoix_OF::controleNouveauComposant(int nouvelIndex)
{
	bool retour = IlvTrue;
	AdxData* m_data = getInterface()->getDonnees();
	IlList* composantList = m_data->getCurrentPhase()->getComposantList();
	IlList* phaseList = m_data->getPhaseList();
	AdxComposant* composantControle = (AdxComposant*)(*composantList)[nouvelIndex];
	AdxComposant* composant;
	AdxPhase* phase;

// differenciation des compsoants pesee en centrale ou en fabrication
	if (getInterface()->getFonctionEnCours() == 3)	// pesee en fabrication
	{
		if (composantControle->getCodeAServir() == 2
			|| composantControle->getCodeAServir() == 4
			|| composantControle->getCodeAServir() == 6
			|| composantControle->getCodeAServir() == 8)
			retour = IlvFalse;
	}
	else	// pesee OF ou Pesee Article
	{
		if (composantControle->getCodeAServir() == 3
			|| composantControle->getCodeAServir() == 5
			|| composantControle->getCodeAServir() == 7
			|| composantControle->getCodeAServir() == 9)
			retour = IlvFalse;
	}
	if (retour == IlvFalse)
	{	
		return retour;
	}
	retour = IlvFalse;

	if (composantControle->getCodeAServir() < 4)
	{
		retour = true;
		return retour;
	}
	
// excipient fin de phase => toutes les matieres a titre de la phase doivent avoir ete pesees	
	if (composantControle->getCodeAServir() == 4 || composantControle->getCodeAServir() == 5)
	{
		retour = true;
		for (int i = 0; i < m_data->getCurrentPhase()->getNbComposants(); i++) 
		{
			composant = (AdxComposant*)(*composantList)[i];
			if (composant->getCodeAServir() < 4				// doivent etre peses avant
				&& composant->getGestionStock() == 3		// composant a titre
				&& composant->getTotalementPese() == false)	// non pese
			{
				retour = false;
				break;
			}
		}
		return retour;
	}

// excipient fin de fabrication	
	if (composantControle->getCodeAServir() == 6 || composantControle->getCodeAServir() == 7)
	{
		retour = true;
// pour toutes les phases
		for (int j = 0; j < m_data->getNbPhases(); j++) 
		{
			phase = (AdxPhase*)(*phaseList)[j];
			composantList = phase->getComposantList();
// pour tous les composants de chaque phase
			for (int i = 0; i < phase->getNbComposants(); i++) 
			{
				composant = (AdxComposant*)(*composantList)[i];
				if (composant->getCodeAServir() < 4				// doivent etre peses avant
					&& composant->getGestionStock() == 3		// composant a titre
					&& composant->getTotalementPese() == false)	// non pese
				{
					retour = false;
					return retour;
				}
				if (composant->getCodeAServir() == 3				// doivent etre peses avant
					&& composant->getTotalementPese() == false)		// non pese
				{
					retour = false;
					return retour;
				}
			}
		}
		return retour;
	}

// matieres de rectification
    if ((composantControle->getCodeAServir() == 8) | (composantControle->getCodeAServir() == 9))
    {
        // matiere de rectification sur phase 900
        if (composantControle->getPhase() == 900)
        {
	        retour = true;
            // pour toutes les phases
	    	for (int j = 0; j < m_data->getNbPhases(); j++) 
		    {
    			phase = (AdxPhase*)(*phaseList)[j];
	    		composantList = phase->getComposantList();
    // pour tous les composants de chaque phase
	    		for (int i = 0; i < phase->getNbComposants(); i++) 
		    	{
			    	composant = (AdxComposant*)(*composantList)[i];
                    // toutes les MP sauf rectifs doivent être pesées
    		        if (((composant->getCodeAServir() < 8) | (composant->getCodeAServir() == 10))
	                && composant->getTotalementPese() == false)	// non pese
			        {
				        retour = false;
				        return retour;
			        }
                }
            }
        }
        else
        {
        // matiere de rectification en fabrication sur phase autre que 900
            if (composantControle->getCodeAServir() == 9)
	        {
    		    retour = true;
        // pour toutes les phases
	        	for (int j = 0; j < m_data->getNbPhases(); j++) 
		        {
    			    phase = (AdxPhase*)(*phaseList)[j];
	    		    composantList = phase->getComposantList();
        // pour tous les composants pesés en centrale de chaque phase
	        		for (int i = 0; i < phase->getNbComposants(); i++) 
		        	{
    			    	composant = (AdxComposant*)(*composantList)[i];
                        // toutes les MP pesées en centrale doivent être pesées
    		            if ((composant->getCodeAServir() == 2
	       		        || composant->getCodeAServir() == 4
	        	        || composant->getCodeAServir() == 6)
    			        && composant->getTotalementPese() == false)	// non pese
	   			        {
		    			        retour = false;
			    		        return retour;
			            }
	                }
                }
	    	}
            else
            {
        // matiere de rectification en centrale sur phase autre que 900
	    	    retour = true;
    // pour la phase
	        	composantList = m_data->getCurrentPhase()->getComposantList();
    // pour tous les composants pesés en centrale de la phase
        		for (int i = 0; i < m_data->getCurrentPhase()->getNbComposants(); i++) 
	        	{
		        	composant = (AdxComposant*)(*composantList)[i];
                    // toutes les MP pesées en centrale doivent être pesées
               	    if ((composant->getCodeAServir() == 2
               		|| composant->getCodeAServir() == 4
	               	|| composant->getCodeAServir() == 6)
		            && composant->getTotalementPese() == false)	// non pese
		            {
			            retour = false;
			            return retour;
		            }
                }
            }
		    return retour;
	    }
    }
     
    // QSP
	if (composantControle->getCodeAServir() == 10 )
	{
		retour = true;
// pour toutes les phases
		for (int j = 0; j < m_data->getNbPhases(); j++) 
		{
			phase = (AdxPhase*)(*phaseList)[j];
// sr 03.04 les matières de la phase 900 ne sont pas prises en compte pour le QSP
            if (phase->getNumPhase()!= 900)
            {
			    composantList = phase->getComposantList();
// pour tous les composants de chaque phase
			    for (int i = 0; i < phase->getNbComposants(); i++) 
			    {
				    composant = (AdxComposant*)(*composantList)[i];
				    if (composant->getCodeAServir() < 8  // doivent etre peses avant sauf rectif
					    && composant->getTotalementPese() == false)
				    {
					    retour = false;
					    return retour;
				    }
			    }
            }
		}
		return retour;
	}
	return retour;
}
//---------------------------------------------------------------------------
void AdxChoix_OF::interruptionOF()
{
	AdxInterface*	m_interface		= getInterface();
	AdxData*		m_data			= m_interface->getDonnees();

	if (m_data->getPhaseBegin()){
		interruptionPhase();
	}
	m_data->SendX3_InterruptionOF();	
	m_data->PositionneProcedureOFAttente();

	m_data->setOrderBegin(false);
}

//---------------------------------------------------------------------------
void AdxChoix_OF::interruptionPhase()
{
	AdxInterface*	m_interface		= getInterface();
	AdxData*		m_data			= m_interface->getDonnees();

	if (m_data->getComposantBegin() || m_data->getComposantAlloue()){
		interruptionComposant();
	}
	m_data->SendX3_InterruptionPhase();
	m_data->PositionneProcedurePhaseAttente();

	m_data->setPhaseBegin(false);
}

//---------------------------------------------------------------------------
void AdxChoix_OF::interruptionComposant()
{
	AdxInterface*	m_interface		= getInterface();
	AdxData*		m_data			= m_interface->getDonnees();

	if (m_data->getComposantBegin())
	{
		m_data->SendX3_InterruptionComposant();
	} 
	else
	{
		if (m_data->getComposantAlloue())
		{
			m_data->SendX3_ChangementComposant();
		}
	}

	m_data->setComposantBegin(false);
	m_data->setComposantAlloue(false);
}


//---------------------------------------------------------------------------
void AdxChoix_OF::changementOFNonPese(AdxOrder* newOrder)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();

	m_data->SendX3_ChangementOFNonPese(newOrder);
	if (m_data->getComposantAlloue())
	{
//		m_data->SendX3_ChangementOFNonPese(newOrder);
		m_data->setComposantAlloue(false);
	}
}

//---------------------------------------------------------------------------
void AdxChoix_OF::quitter()
{
	AdxInterface*	m_interface = getInterface();
	AdxAccueil*		m_accueil	= m_interface->getAccueil();
	AdxChoix_OF*	m_choix_OF	= m_interface->getChoix_OF();
	AdxData*		m_data		= m_interface->getDonnees();


	if  (getInterface()->getFonctionEnCours() == 2)
	{
		// si n° OF alimenté mais pas  n° phase , il faut empêcher de quitter(), sinon on plante
		if ( strcmp(m_choix_OF->getSaisieNOF_Art()->getValue(),"")!= 0 && strcmp(m_choix_OF->getSaisiePhase_Art()->getValue(),"")== 0)
		{
			envoieMessage("&PhaseNonRenseignee", false);
			show();
			return;
		}	
	}
	// si tous les champs sont alimentés,on peut envoyer vers controleChangementOF()
	if  ( strcmp(m_choix_OF->getSaisieNOF()->getValue(),"")!= 0  &&
			strcmp(m_choix_OF->getSaisiePhase()->getValue(),"") != 0 &&
				strcmp(m_choix_OF->getSaisieComposant()->getValue(),"") != 0 )
	{
		if (controleChangementOF(m_data->getNbOrders()) == false) // nbOrders n'est pas un index valide
			return;
	}
	m_accueil->setSensitive(true);
	m_accueil->show();
 	m_choix_OF->hide();
	m_interface->getDonnees()->lanceProcedureEnAttente();
}

//---------------------------------------------------------------------------
// index exprimes dans les tables m_data->getOrderList(), m_data->getPhaseList(), m_data->getPhase(nump)->getComposantList()
void AdxChoix_OF::afficherOrdre(long numo,long nump,long numc)
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxOrder* order = m_data->getOrder(numo);
	AdxPhase* phase ;
	if  (m_data->getNbOrders())
	{
		getSaisieNOF()->setLabel(order->getNumOF());
		getSaisieNOF_Art()->setLabel(order->getNumOF());
		getAffArticle()->setLabel(order->getArticle());
		getAffLibArticle()->setLabel(order->getLibArticle());
		getAffLot()->setLabel(order->getLotLance());	
	}
	if  (m_data->getNbPhases())	
	{
		phase = m_data->getPhase(nump);
		getSaisiePhase()->setValue((IlvInt)phase->getNumPhase());
		getSaisiePhase_Art()->setValue((IlvInt)phase->getNumPhase());
	}

	//  Pesee Matiere : pour eviter le plantage lorsque la phase n'est pas selectionnee
	AdxComposant* composant ;
	if ((m_data->getNbPhases()))
	{
		composant = phase->getComposant(numc);
		getSaisieComposant()->setLabel(composant->getComposant());
		getSaisieComposant_Art()->setLabel(composant->getComposant());
		getAffLibComposant()->setLabel(composant->getLibComposant());
		getAffLibComposant_Art()->setLabel(composant->getLibComposant());
	}
	else 
	{
		getSaisieComposant()->setLabel(m_data->getPseMatCurrentMat());
		getSaisieComposant_Art()->setLabel(m_data->getPseMatCurrentMat());
		getAffLibComposant()->setLabel(m_data->getPseMatCurrentMatLib());
		getAffLibComposant_Art()->setLabel(m_data->getPseMatCurrentMatLib());
		reDraw();
		return;
	}
// affichage des quantite en tenant compte des titres et des codes a servir
	double quantitePhase;
	AdxComposant* composantPourCalcul;
	AdxPhase* phaseCalcul;
	IlList* composantList = phase->getComposantList();
	IlList* phaseList = m_data->getPhaseList();
	double quantiteCalcul;

    // mm 02.2013 - enrichissement de la trace 
	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile<< "Composant =("<<composant->getComposant()<<") - titre = ("<<composant->getTitreTheo()<<")"<< endl;
	}

	// _quantiteAlloueeTheorique = affichée dans le champs quantité allouée de l'écran AdxChoix_OF
	// _quantiteAlloueeRestante = affiché dans le tableau de sélection Matière
	if (composant->getCodeAServir() < 4)
	{
		if (composant->getGestionStock() == 3			// composant a titre
				&& composant->getTitreTheo() != 0)
		{
			composant->setQuantiteTheorique(
				composant->getQuantiteRestante() / composant->getTitreTheo() * 100);
			// mm 11.10 
			if ( !composant->getQuantiteAllouee())	
				composant->setQuantiteAlloueeTheorique(
					composant->getQuantiteAlloueeRestante() /composant->getTitreTheo() * 100);
		}
		else											// composant sans titre
		{
			composant->setQuantiteTheorique(composant->getQuantiteRestante());
			if ( !composant->getQuantiteAllouee())	
				composant->setQuantiteAlloueeTheorique(composant->getQuantiteAlloueeRestante());	
		}
		if ( composant->getQuantiteAllouee())
		{
			composant->setQuantiteAlloueeTheorique(composant->getQuantiteAllouee());
			composant->setQuantiteAlloueeRestante(composant->getQuantiteRestante());
		}
	}
	
// excipient fin de phase => toutes les matieres a titre de la phase doivent avoir ete pesees	
	if (composant->getCodeAServir() == 4 || composant->getCodeAServir() == 5)
	{
		composant->setQuantiteTheorique(composant->getQuantiteRestante());
		for (int i = 0; i < m_data->getCurrentPhase()->getNbComposants(); i++) 
		{
			composantPourCalcul = (AdxComposant*)(*composantList)[i];
			if (composantPourCalcul->getCodeAServir() < 4				// doivent etre peses avant
				&& composantPourCalcul->getGestionStock() == 3			// composant a titre
				&& composantPourCalcul->getTotalementPese() == true		// pese
				&& composantPourCalcul->getQuantitePEC() != 0)			// pesée annulée sans réintégration :
																		 //ne doit pas être comptabilisée
			{
				// 93535 mm 10.2013 
				quantiteCalcul = ( composantPourCalcul->getQuantitePrevue()
									/ composantPourCalcul->getTitreTheo() * 100)
									- composantPourCalcul->getQuantitePEC();
				composant->setQuantiteTheorique(composant->getQuantiteTheorique() 
									+ m_data->convertir(quantiteCalcul,
														composantPourCalcul->getUnite(),
														composant->getUnite()));
			}
		}
		// mm 02.11
		if ( composant->getQuantiteAllouee())
		{
			composant->setQuantiteAlloueeTheorique(composant->getQuantiteAllouee());
			composant->setQuantiteAlloueeRestante(composant->getQuantiteTheorique());
		}
	}

// excipient fin de fabrication	
	if (composant->getCodeAServir() == 6 || composant->getCodeAServir() == 7)
	{
		composant->setQuantiteTheorique(composant->getQuantiteRestante());
// pour toutes les phases
		for (int j = 0; j < m_data->getNbPhases(); j++) 
		{
			phaseCalcul = (AdxPhase*)(*phaseList)[j];
			composantList = phaseCalcul->getComposantList();
			quantitePhase = 0;
// pour tous les composants de chaque phase
			for (int i = 0; i < phaseCalcul->getNbComposants(); i++) 
			{
				composantPourCalcul = (AdxComposant*)(*composantList)[i];
				if (composantPourCalcul->getCodeAServir() < 4				// doivent etre peses avant
					&& composantPourCalcul->getGestionStock() == 3			// composant a titre
					&& composantPourCalcul->getTotalementPese() == true)	//  pese
				{
					quantiteCalcul = (composantPourCalcul->getQuantitePrevue() 
									/ composantPourCalcul->getTitreTheo() * 100)
									- composantPourCalcul->getQuantiteConsommee();
					quantitePhase = quantitePhase 
						+ m_data->convertir(quantiteCalcul,
											composantPourCalcul->getUnite(),
											composant->getUnite());
				}
				if (composantPourCalcul->getCodeAServir() == 4 || composantPourCalcul->getCodeAServir() == 5)
// s'il y a un excipient de phase les composants a titre de cette phase ont ete compenses
				{
					quantitePhase = 0;
					break;
				}
			}
			composant->setQuantiteTheorique(composant->getQuantiteTheorique() 
					+ quantitePhase);
			// mm 02.11
			if ( composant->getQuantiteAllouee())
			{
				composant->setQuantiteAlloueeTheorique(composant->getQuantiteAllouee());
				composant->setQuantiteAlloueeRestante(composant->getQuantiteTheorique());
			}
		}
	}

// matieres de rectification
	if (composant->getCodeAServir() == 8 || composant->getCodeAServir() == 9)
	{
		if (composant->getGestionStock() == 3			// composant a titre
				&& composant->getTitreTheo() != 0)
		{
			composant->setQuantiteTheorique(
				composant->getQuantiteRestante() / composant->getTitreTheo() * 100);
			// mm 11.10 
			if ( !composant->getQuantiteAllouee())	
				composant->setQuantiteAlloueeTheorique(
					composant->getQuantiteAlloueeRestante() /composant->getTitreTheo() * 100);
		}
		else											// composant sans titre
		{
			composant->setQuantiteTheorique(composant->getQuantiteRestante());
				if ( !composant->getQuantiteAllouee())	
				composant->setQuantiteAlloueeTheorique(composant->getQuantiteAlloueeRestante());	
		}
		if ( composant->getQuantiteAllouee())
		{
			composant->setQuantiteAlloueeTheorique(composant->getQuantiteAllouee());
			composant->setQuantiteAlloueeRestante(composant->getQuantiteRestante());
		}
			
	}

// QSP quantite pour atteindre le poids prevu ==>
// quantite lancee - somme des quantites consommees pour tous les autres articles
	if (composant->getCodeAServir() == 10)
	{
		composant->setQuantiteTheorique(
			m_data->convertir(m_data->getCurrentOrder()->getQuantiteLanceeEnPoids(),
							  m_data->getCurrentOrder()->getUnitePoids(),
							  composant->getUnite()));
// pour toutes les phases
		for (int j = 0; j < m_data->getNbPhases(); j++) 
		{
			phaseCalcul = (AdxPhase*)(*phaseList)[j];
			composantList = phaseCalcul->getComposantList();
// pour tous les composants de chaque phase
			for (int i = 0; i < phaseCalcul->getNbComposants(); i++) 
			{
				composantPourCalcul = (AdxComposant*)(*composantList)[i];
				if (composantPourCalcul->getCodeAServir() < 10				// doivent etre peses avant
					&& composantPourCalcul->getQuantiteConsommee() != 0)	//  pese
				{
					composant->setQuantiteTheorique(composant->getQuantiteTheorique() 
						- m_data->convertir(composantPourCalcul->getQuantiteConsommee(),
											composantPourCalcul->getUnite(),
											composant->getUnite()));
				}
			}
		}
		// mm 02.11
		if ( composant->getQuantiteAllouee())
		{
			composant->setQuantiteAlloueeTheorique(composant->getQuantiteAllouee());
			composant->setQuantiteAlloueeRestante(composant->getQuantiteTheorique());
		}
	}
	// sr 02.02 pas de quantité négative
	if (composant->getQuantiteTheorique() < 0)
	{
		composant->setQuantiteTheorique(0);
	}
	getAffQuantiteAPeser()->setPrecision(composant->getDecimalePoids());
	if (composant->getTotalementPese())
	{
		double z = 0;
		getAffQuantiteAPeser()->setValue(z);
		getAffQuantite()->setValue(z);				// mm 02.11- nouveau champ quantité allouée
	}
	else
	{
		getAffQuantiteAPeser()->setValue(composant->getQuantiteTheorique());	
		getAffQuantite()->setValue(composant->getQuantiteAlloueeTheorique());	
	}
	getAffUniteComp()->setLabel(composant->getUnite());	
	getAffUniteComposant()->setLabel(composant->getUnite());
	reDraw();
}


//---------------------------------------------------------------------------
void AdxChoix_OF::chargement()
{
	if (getInterface()->getFonctionEnCours() == 1
	||  getInterface()->getFonctionEnCours() == 3)
	{
		setTitle(IlvGetMessage(getDisplay(),"&PeseeOF"));

		setVisible(getEtiquetteNoOF(),IlvTrue,IlvFalse);
		setVisible(getSaisieNOF(),IlvTrue,IlvFalse);
		setVisible(getBoutonListeOF(),IlvTrue,IlvFalse);
		//	ces champs sont actifs en pesee par OF et en fabrication
		setVisible(getEtiquetteComposant(),IlvTrue,IlvFalse);
		setVisible(getSaisieComposant(),IlvTrue,IlvFalse);
		setVisible(getAffLibComposant(),IlvTrue,IlvFalse);
		setVisible(getBoutonListeComposant(),IlvTrue,IlvFalse);
		setVisible(getEtiquettePhase(),IlvTrue,IlvFalse);
		setVisible(getSaisiePhase(),IlvTrue,IlvFalse);
		setVisible(getBoutonListePhase(),IlvTrue,IlvFalse);
		//	ces champs sont actifs en pesee par Article
		setVisible(getEtiquetteNoOF_Art(),IlvFalse,IlvFalse);
		setVisible(getSaisieNOF_Art(),IlvFalse,IlvFalse);
		setVisible(getBoutonListeOF_Art(),IlvFalse,IlvFalse);
		setVisible(getEtiquetteComposant_Art(),IlvFalse,IlvFalse);
		setVisible(getSaisieComposant_Art(),IlvFalse,IlvFalse);
		setVisible(getAffLibComposant_Art(),IlvFalse,IlvFalse);
		setVisible(getBoutonListeComposant_Art(),IlvFalse,IlvFalse);
		setVisible(getEtiquettePhase_Art(),IlvFalse,IlvFalse);
		setVisible(getSaisiePhase_Art(),IlvFalse,IlvFalse);
		setVisible(getBoutonListePhase_Art(),IlvFalse,IlvFalse);
	}
	else
	{
		setTitle(IlvGetMessage(getDisplay(),"&PeseeArt"));
		setVisible(getEtiquetteNoOF(),IlvFalse,IlvFalse);
		setVisible(getSaisieNOF(),IlvFalse,IlvFalse);
		setVisible(getBoutonListeOF(),IlvFalse,IlvFalse);
		//	et vice versa
		setVisible(getEtiquetteComposant(),IlvFalse,IlvFalse);
		setVisible(getSaisieComposant(),IlvFalse,IlvFalse);
		setVisible(getAffLibComposant(),IlvFalse,IlvFalse);
		setVisible(getBoutonListeComposant(),IlvFalse,IlvFalse);
		setVisible(getEtiquettePhase(),IlvFalse,IlvFalse);
		setVisible(getSaisiePhase(),IlvFalse,IlvFalse);
		setVisible(getBoutonListePhase(),IlvFalse,IlvFalse);
	
		setVisible(getEtiquetteNoOF_Art(),IlvTrue,IlvFalse);
		setVisible(getSaisieNOF_Art(),IlvTrue,IlvFalse);
		setVisible(getBoutonListeOF_Art(),IlvTrue,IlvFalse);
		setVisible(getEtiquetteComposant_Art(),IlvTrue,IlvFalse);
		setVisible(getSaisieComposant_Art(),IlvTrue,IlvFalse);
		setVisible(getAffLibComposant_Art(),IlvTrue,IlvFalse);
		setVisible(getBoutonListeComposant_Art(),IlvTrue,IlvFalse);
		setVisible(getEtiquettePhase_Art(),IlvTrue,IlvFalse);
		setVisible(getSaisiePhase_Art(),IlvTrue,IlvFalse);
		setVisible(getBoutonListePhase_Art(),IlvTrue,IlvFalse);
	}
	
	AdxData* m_data = getInterface()->getDonnees();

	// #########################################################################################
	// SMO : STD-PR-OO1 : Pesee Matiere : repositionne les champs dans l'ecran choix_OF : DEBUT
	// #########################################################################################
	if (getInterface()->getFonctionEnCours() == 1
	||  getInterface()->getFonctionEnCours() == 3)
	{
		setChampAppelant(getSaisieNOF());
		setFocus(getSaisieNOF());
		afficherOrdre(m_data->getCurrentOrderIndex(),
					  m_data->getCurrentPhaseIndex(),
					  m_data->getCurrentComposantIndex());
	}
	else
	{
		setChampAppelant(getSaisieComposant_Art());
		setFocus(getSaisieComposant_Art());
		chargementZonesAVide();
	}
}

//---------------------------------------------------------------------------
void AdxChoix_OF::chargementZonesAVide()
{
	getSaisieNOF()					->setLabel(""); // L1 : ligne No OF
	getSaisieNOF_Art()				->setLabel(""); // L1 : ligne No OF
	getAffArticle()					->setLabel(""); // L2 : ligne Article Lance
	getAffLibArticle()				->setLabel(""); // L2 : ligne Article Lance
	getAffLot()						->setLabel(""); // L3 : ligne Lot Lance
	getAffQuantite()				->setLabel(""); // L4 : ligne Qte Lancee
	getAffUniteComp()				->setLabel(""); // L4 : ligne Qte Lancee
	getSaisiePhase()				->setLabel(""); // L5 : ligne Composant
	getSaisieComposant_Art()        ->setLabel(""); // L5 : ligne Composant
	getAffLibComposant_Art()		->setLabel(""); // L5 : ligne Composant
	getSaisiePhase_Art()			->setLabel(""); // L6 : ligne Operation
	getSaisieComposant()			->setLabel(""); // L6 : ligne Operation
	getAffLibComposant()			->setLabel(""); // L6 : ligne Operation
	getAffQuantiteAPeser()			->setLabel(""); // L7 : ligne Qte a peser
	getAffUniteComposant()			->setLabel(""); // L7 : ligne Qte a peser
}
//---------------------------------------------------------------------------
void AdxChoix_OF::validationPeseeAutomatique()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
   	AdxComposant* composant;
	AdxPhase* phase;
	IlList* composantList = m_data->getCurrentPhase()->getComposantList();
	IlList* phaseList = m_data->getPhaseList();
    // correspond a une fin de phase ?
	if (m_data->getCurrentPhase()->getNbComposantsPeses() + 1
		>= m_data->getCurrentPhase()->getNbComposants())
	{
		if (m_data->getNbPhasesPesees() + 1 >= m_data->getNbPhases())
		{
// impression document fin d OF 
			m_data->sendX3_FinOFBis();
			m_data->getCurrentComposant()->setTotalementPese(true);
			m_data->getCurrentPhase()->setNbComposantsPeses
				(m_data->getCurrentPhase()->getNbComposantsPeses() + 1);
			m_data->getCurrentPhase()->setTotalementPese(true);
			m_data->getCurrentPhase()->setStatut(m_data->getCodeMatPese());
			m_data->getCurrentPhase()->setLibStatut(m_data->getLibMatPese());
			m_data->setNbPhasesPesees(m_data->getNbPhasesPesees() + 1);
			m_data->getCurrentOrder()->setTotalementPese(true);
			m_data->getCurrentOrder()->setStatut(m_data->getCodeOFPeseBox());
			m_data->getCurrentOrder()->setLibStatut(m_data->getLibOFPeseBox());
			m_data->setOrderBegin(false);
			m_data->setPhaseBegin(false);
			m_data->setComposantBegin(false);
			m_data->setComposantAlloue(false);
			m_data->setLotBegin(false);
		}
		else
		{
// impression document fin de phase
			m_data->sendX3_FinPhaseBis();

			m_data->getCurrentComposant()->setTotalementPese(true);
			m_data->getCurrentPhase()->setNbComposantsPeses
				(m_data->getCurrentPhase()->getNbComposantsPeses() + 1);
			m_data->getCurrentPhase()->setTotalementPese(true);
			m_data->getCurrentPhase()->setStatut(m_data->getCodeMatPese());
			m_data->getCurrentPhase()->setLibStatut(m_data->getLibMatPese());
			m_data->setNbPhasesPesees(m_data->getNbPhasesPesees() + 1);
			m_data->setOrderBegin(true);
			m_data->setPhaseBegin(false);
			m_data->setComposantBegin(false);
			m_data->setComposantAlloue(false);
			m_data->setLotBegin(false);
		}
	}
	else
// impression document fin de composant
	{
			m_data->sendX3_soldeMatiereSansQuantite();

			m_data->getCurrentComposant()->setTotalementPese(true);
			m_data->getCurrentPhase()->setStatut(m_data->getCodeMatEnCoursPesee());
			m_data->getCurrentPhase()->setLibStatut(m_data->getLibMatEnCoursPesee());
			m_data->getCurrentOrder()->setStatut(m_data->getCodeOFEnCoursPesee());
			m_data->getCurrentOrder()->setLibStatut(m_data->getLibOFEnCoursPesee());
			m_data->getCurrentPhase()->setNbComposantsPeses
				(m_data->getCurrentPhase()->getNbComposantsPeses() + 1);
			m_data->setOrderBegin(true);
			m_data->setPhaseBegin(true);
			m_data->setComposantBegin(false);
			m_data->setComposantAlloue(false);
			m_data->setLotBegin(false);
	}
   // Si solde du QSP, voir si il ne faut pas, en même temps, solder
    // des matières de rectif se situant en amont
    if (m_data->getCurrentComposant()->getCodeAServir() == 10)
    {
    // pour toutes les phases
		for (int j = 0; j < m_data->getNbPhases(); j++) 
		{
			phase = (AdxPhase*)(*phaseList)[j];
    // sr 03.04 les matières de la phase 900 ne sont pas prises en compte pour le QSP
            if (phase->getNumPhase()!= 900)
            {
			    composantList = phase->getComposantList();
    // pour tous les composants de chaque phase
			    for (int i = 0; i < phase->getNbComposants(); i++) 
			    {
				    composant = (AdxComposant*)(*composantList)[i];
				    if ((composant->getCodeAServir() ==8) |(composant->getCodeAServir() == 9)  
					    && composant->getTotalementPese() == false)
				    {
					    composant->setTotalementPese(true);
                        if(phase->getNbComposantsPeses() +1 >= phase->getNbComposants())
                        {
                           	phase->setNbComposantsPeses
    	        	        (phase->getNbComposantsPeses() + 1);
                            phase->setTotalementPese(true);
	                        phase->setStatut(m_data->getCodeMatPese());
                            phase->setLibStatut(m_data->getLibMatPese());
                            m_data->setNbPhasesPesees(m_data->getNbPhasesPesees() + 1); 
                           if (m_data->getNbPhasesPesees() >= m_data->getNbPhases())
                            {
                            	m_data->getCurrentOrder()->setTotalementPese(true);
                            	m_data->getCurrentOrder()->setStatut(m_data->getCodeOFPeseBox());
	                            m_data->getCurrentOrder()->setLibStatut(m_data->getLibOFPeseBox());
	                            m_data->setOrderBegin(false);
	                            m_data->setPhaseBegin(false);
	                            m_data->setComposantBegin(false);
	                            m_data->setComposantAlloue(false);
	                            m_data->setLotBegin(false);
                            }
 
                        }
                    }
                }
            }
        }
    }

}
//---------------------------------------------------------------------------
void AdxChoix_OF::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));


	char szFileIcons[_MAX_PATH];
	// bouton BoutonListeOF
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\book.png",
		_interface->getPathX3());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	getBoutonListeOF()->setBitmap(bitmap);
	getBoutonListeOF_Art()->setBitmap(bitmap);

	// bouton BoutonListePhase
	getBoutonListePhase()->setBitmap(bitmap);
	getBoutonListePhase_Art()->setBitmap(bitmap);

	// bouton BoutonListeComposant
	getBoutonListeComposant()->setBitmap(bitmap);
	getBoutonListeComposant_Art()->setBitmap(bitmap);

	// bouton Valider
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getValider()->setBitmap(bitmap);

	// bouton Tactile
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\keyboard.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getTactile()->setBitmap(bitmap);

	// bouton VideBox
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\cleanbox.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getVideBox()->setBitmap(bitmap);

	// bouton Allouer
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\inventory.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getAllouer()->setBitmap(bitmap);

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


 