// AdxPesee_Etalon.cpp
// Weighing Standard
// -------------------
// project : Adonix X3 Scales
// author : SR
// V130 : SR 2001.11.27
//--------------------------------------------------------------

#include "stdafx.h"
#include <cmath>
#include "AdxPesee_Etalon.h"
#include "AdxInterface.h"
#include "AdxAccueil.h"
#include "AdxData.h"
#include "AdxBalance.h"
#include "AdxEtalon.h"
#include "AdxMessage.h"
#include "AdxWeighingInterface.h"
#include "AdxClavier_tactile.h"
#include "AdxChoix_Balance.h"
#include "AdxSelection_EtalonLigne.h"

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
// 
// We validate a weight of a calibration guide line
// if last weight of the last line we validate everything and we leave
void AdxPesee_Etalon::validerCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();

	// GBE 16/09/08 mise à vrai du flag
	if(weighingInterface->getBalance()->getTempo() == 0 && weighingInterface->getStopPesee() == false)
	{
		// mm 05.11 - commented for test
		//weighing with a connected scale
		if (m_data->getCurrentBalance()->getConnecte() == 1)
		{	
			// We position the flags and we go out
			// the function will be recalled later by peserCB (weighCB)
			// and we will not go back here
			// In fact this piece of code simply allows to end the loop
			// who gets the weight back

			weighingInterface->setStopPesee(true);
			weighingInterface->setValid(true);
			// we have positioned the flag we can go out of the function
			return;
		}
	}
// poids pese hors tolerance ou non 
	//if (fabs(_poidsPese - _poidsAPeser)  > fabs(_poidsAPeser * (_tolerance/100))) 
	// 104515 mm 03.2015 - _poidsAPeser : Conversion problem between a char * -> double
	// to solve it : cast double -> float
	if (fabs (_ecartPoids)> fabs((float)(_poidsAPeser * (_tolerance/100)))) 
	{
			if (envoieMessage("&PeseeInvalide", true) == false)
			{
				peserCB(getpeser());
				return;
			}	
			else
			{
				m_data->getCurrentEtalon()->
				getCurrentEtalonLigne()->setArrPoidsPese(m_data->getCurrentEtalon()->
				getCurrentEtalonLigne()->getNbPeseesEffectuees(), _poidsPese);
			}
	}
	else
	{
			m_data->getCurrentEtalon()->getCurrentEtalonLigne()->
			setNbPeseesOk(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPeseesOk()+ 1);
			m_data->getCurrentEtalon()->
			getCurrentEtalonLigne()->setArrPoidsPese(m_data->getCurrentEtalon()->
			getCurrentEtalonLigne()->getNbPeseesEffectuees(), _poidsPese);

	}
	

// On incremente le nombre de pesees effectuees sur la ligne etalon
	m_data->getCurrentEtalon()->getCurrentEtalonLigne()->
	setNbPeseesEffectuees(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPeseesEffectuees()+ 1);

/*
 s'agit-il de la derniere pesee pour cette ligne ?
	 si OUI on positionne l'indicateur ligne peseeEffectuee
	on incrémente le nombre de lignes effectuees dans l'entete etalon
	Si toutes les pesée de la ligne sont OK
		on position l'indicateur ligne pesee validée
		on incrémente le nombre de lignes validees dans l'entete etalon

*/

	if 	(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPeseesEffectuees() ==
		m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPesees())	
	{
		m_data->getCurrentEtalon()->getCurrentEtalonLigne()->setPeseeEffectuee(true);

		m_data->getCurrentEtalon()->
		setNbLignesEffectuees(m_data->getCurrentEtalon()->getNbLignesEffectuees()+ 1);

		if 	(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPeseesOk() ==
			m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPesees())
		{
			m_data->getCurrentEtalon()->getCurrentEtalonLigne()->setPeseeValidee(true);

			m_data->getCurrentEtalon()->
			setNbLignesValidees(m_data->getCurrentEtalon()->getNbLignesValidees()+ 1);
		}
		else
		{
			m_data->getCurrentEtalon()->getCurrentEtalonLigne()->setPeseeValidee(false);
		}			

		// s'agit-il de la derniere ligne du guide etalonnage ?
		if (m_data->getCurrentEtalon()->getNbLignesEffectuees() ==
			m_data->getCurrentEtalon()->getNbLignes())
		{
			if(m_data->getCurrentEtalon()->getNbLignesValidees() ==
			m_data->getCurrentEtalon()->getNbLignes()) 
			{
			    m_data->getCurrentEtalon()->setTotalementEtalonne(true);
	
			}
			else
			{
			    m_data->getCurrentEtalon()->setTotalementEtalonne(false);
			}
			quitter();
		}
		else
		{
			afficherPesee();
			bufferedDraw(getAffCompteur());
			reaffichage();
//			getPoidsPese()->setEditable(false);	
			setFocus(getpeser());
		}
	}
	else
	{
		afficherEtalonLigne();
		reaffichage();
//		getPoidsPese()->setEditable(false);
		setFocus(getpeser());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::reaffichage()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	bufferedDraw(getLabelUnAPeser());
	bufferedDraw(getLabelUnPesee());
	bufferedDraw(getLabelUnEcart());
	bufferedDraw(getPoidsEtalon());
	bufferedDraw(getPoidsAPeser());
	bufferedDraw(getPoidsPese());
	bufferedDraw(getEcartPoids());
	bufferedDraw(getLibTypPesee());
	bufferedDraw(getPctTolerance());
	bufferedDraw(getAffCompteurPesees());
	bufferedDraw(getJaugeScale());
	bufferedDraw(getJaugePesee());
	bufferedDraw(getMessage());
}

//---------------------------------------------------------------------------
//Weigh Button
void AdxPesee_Etalon::peserCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
//	getPoidsPese()->setEditable(false);
	getTactile()->setSensitive(false);
	// GBE 16/09/08 on active le bouton car on doit pouvoir arrêter la pesee
	// si on le souhaite
	getValider()->setSensitive(true);

	if (m_data->getCurrentBalance()->getConnecte() == false)
	{
		CString string;
		string = IlvGetMessage(getDisplay(), "&Etalonnage");
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Saisir");
		string += " ";
		string += IlvGetMessage(getDisplay(),"&PoidsPese");
		getMessage()->setLabel(string);
		bufferedDraw(getMessage());
		getTactile()->setSensitive(true);
		getPoidsPese()->setEditable(true);
		setFocus(getPoidsPese());
		return;
	}
	
	AdxWeighingInterface* weighingInterface = m_interface->getWeighingInterface();

	// GBE 16/09/08 mise à zéro des flags
	weighingInterface->setStopPesee(false);
	weighingInterface->setCancel(false);
	weighingInterface->setValid(false);

	WeighingOrder order;
	order = POIDS_STAB_M;

	weighingInterface->setPanneauAppelant(this);
	weighingInterface->setWeighingOrder(order);

	bool error;
	_poidsPese = getPoidsAPeser()->getFloatValue(error);
	weighingInterface->setWeight(_poidsPese);
	weighingInterface->setTotWeight(_poidsPese);

	weighingInterface->setWeightUnit(getLabelUnAPeser()->getLabel());
	weighingInterface->setResWeightUnit(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getUnite());

	weighingInterface->setPanneauAppelant(this);
	weighingInterface->weighingOrderTreatment();


	if (weighingInterface->getResWeighingMessage() != NULL)
	{
		if (weighingInterface->getWeighingStatus() == OK_STA)
		{
			getMessage()->setLabel(formatMessage("&PeseeEffectuee         "));
			getValider()->setSensitive(true);
			setFocus(getValider());
			_peseeOK = true;
		}
		else if (weighingInterface->getWeighingStatus() == CHG_PDS_UNIT)
		{
			char* message = new char[100];
			sprintf(message,"%s : %s",
					IlvGetMessage(getInterface()->getDisplay(),
					"&PeseeEffectuee         "),
					weighingInterface->getResWeighingMessage()); 
			getMessage()->setLabel(formatMessage(message));
			delete [] message;
			getValider()->setSensitive(true);
			setFocus(getValider());
			_peseeOK = true;
		}
		else
		{
			getMessage()->setLabel(formatMessage(weighingInterface->getResWeighingMessage()));
		}
		bufferedDraw(getMessage());
	}
	if(_peseeOK == true && weighingInterface->getValid() == true)
	{
		// on a cliqué sur le bouton valider pendant la pesée
		// comme on est maintenant sortie de la boucle il faut
		// rappeler le bouton valider pour acomplir son action
		validerCB(this->getValider());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::poidsPeseCB(IlvGraphic* g)
{
	bool error;
	_poidsPese = getPoidsPese()->getFloatValue(error);
	if (_poidsPese == 0) return;
	_peseeOK = true;
	getTactile()->setSensitive(false);
	getpeser()->setSensitive(false);
	getValider()->setSensitive(true);

// scale adaptation according to the weight to be weighed
// positioning of the gauge according to the weighed weight	
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	weighingInterface->setWeight(_poidsAPeser);
	weighingInterface->setResNetWeight(_poidsPese);
	weighingInterface->setTotWeight(_poidsAPeser);
	weighingInterface->setTotResWeight(_poidsPese);
    evolutionPoids();

// edition message
	getMessage()->setLabel(formatMessage("&PeseeEffectuee"));
	bufferedDraw(getMessage());
	setFocus(getValider());
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::mettreAZeroCB(IlvGraphic* g)
{
	// 48084 mm 08.09
	getMessage()->setLabel(formatMessage("&FaireRemiseAZero1"));
	bufferedDraw(getMessage());

	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	WeighingOrder order;

	order = RAZ_M;
	// GBE 16/09/08 mise à zéro des flags
	weighingInterface->setStopPesee(false);
	weighingInterface->setCancel(false);
	weighingInterface->setValid(false);

	weighingInterface->setPanneauAppelant(this);
	weighingInterface->setWeighingOrder(order);

	weighingInterface->setPanneauAppelant(this);
	weighingInterface->weighingOrderTreatment();

	if (weighingInterface->getResWeighingMessage() != NULL)
	{
		if (weighingInterface->getWeighingStatus() == OK_STA)
		{
			_miseAZeroOK = true;
			getmettreAZero()->setSensitive(false);
			getMessage()->setLabel("&RemiseAZeroEffectuee2  ");
//			getPoidsPese()->setSensitive(true);
			getpeser()->setSensitive(true);
			setFocus(getpeser());
		}
		else
		{
			getMessage()->setLabel(weighingInterface->getResWeighingMessage());
		}
		bufferedDraw(getMessage());
	}
}

//---------------------------------------------------------------------------
// Clavier = Keyboard
void AdxPesee_Etalon::tactileCB(IlvGraphic* g)
{
	AdxInterface* m_interface = getInterface();
	IlvRect m_rect = 0;
	boundingBox (m_rect);
	if (initClavier_Tactile())
	{
		m_interface->getClavier_Tactile()->show();
		this->hide();
	}
}

//---------------------------------------------------------------------------
bool AdxPesee_Etalon::initClavier_Tactile()
{
	bool retour = false;
	AdxClavier_Tactile* tactile = getInterface()->getClavier_Tactile();
	tactile->setPanneauAppelant(this);
// 1 appel possible du clavier dans Pesee_Etalon
	if (_champAppelant == getPoidsPese())
	{
			tactile->setSaisie("");
			tactile->setAlpha(IlvFalse);
			CString string(IlvGetMessage(getDisplay(), "&Saisir"));
			string += " ";
			string += IlvGetMessage(getDisplay(),"&PoidsPese");
			tactile->getchampMessage()->setLabel(string);
			retour = true;
	}

	tactile->getchampSaisie()->setLabel(tactile->getSaisie());
	tactile->reDrawObj(tactile->getchampSaisie());
	return retour;
}

//---------------------------------------------------------------------------
// on sort de l'etalonnage 
void AdxPesee_Etalon::quitterCB(IlvGraphic* g)
{
 	// GBE 16/09/08 mise à vrai du flag
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	weighingInterface->setCancel(true);

    quitter();
}

//---------------------------------------------------------------------------
// on choisit une des lignes du guide etalonnage par selection
void AdxPesee_Etalon::listerEtalonCB(IlvGraphic* g)
{
 	AdxInterface* m_interface = getInterface();

	m_interface->getSelection_EtalonLigne()->setPanneauAppelant(this);
	IlvRect m_rect = 0;
	boundingBox (m_rect);
	m_interface->getSelection_EtalonLigne()
		->setListeSelectionEtalonLigne(0);

	CString string(IlvGetMessage(getDisplay(), "&Choisir"));
	string += " ";
	string += IlvGetMessage(getDisplay(),"&Ligne1");
	m_interface->getSelection_EtalonLigne()->getMessage()->setLabel(string);

	hide();
	m_interface->getSelection_EtalonLigne()->show();
	afficherEtalonLigne();
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	if (m_data->getCurrentEtalon()->getNbLignesEffectuees() != 0)
	{
	// il faut mettre à jour la balance selon les resultats de l'etalonnage
	// envoyer et fermer le fichier des messages X3
		if (m_data->getCurrentEtalon()->getTotalementEtalonne() == true)
		{
			if (m_data->getCurrentBalance()->getEtalonnee() == false)
			{
				m_data->setNbBalancesAEtalonner(m_data->getNbBalancesAEtalonner() -1);
			}
			m_data->getCurrentBalance()->setEtalonnee(true);
			m_data->getCurrentBalance()->setNbPesees(0);
			m_data->getCurrentBalance()->setDateDernierCalibrage(m_data->getDateJour());
			m_data->sendX3_Etalonnage(3);
		}
		else
		{
			if (m_data->getCurrentBalance()->getEtalonnee()== true)
			{
				m_data->getCurrentBalance()->setEtalonnee(false);
				m_data->setNbBalancesAEtalonner(m_data->getNbBalancesAEtalonner() +1);
				m_data->sendX3_Etalonnage(2);
			}
			else
			{
				m_data->sendX3_Etalonnage(1);
			}
		}
	}
	
	AdxPesee_Etalon* m_Pesee_Etalon = m_interface->getPesee_Etalon();
	AdxChoix_Balance* m_choix_Balance = m_interface->getChoix_Balance();
	m_choix_Balance->afficherBalances();
 	m_Pesee_Etalon->hide();
	m_choix_Balance->show();
}

//---------------------------------------------------------------------------
bool AdxPesee_Etalon::envoieMessage(CString mess, bool OUINON)
{
	AdxInterface* m_interface = getInterface();
	m_interface->getMessage()->setPanneauAppelant(this);
	return (m_interface->envoieMessage(mess, OUINON));
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::afficherPesee()
{
	AdxData* m_data = getInterface()->getDonnees();

	char* string = new char[4];
	char* string2 = new char[2];

	itoa(m_data->getCurrentEtalon()->getNbLignesEffectuees(),string,10);
	itoa(m_data->getCurrentEtalon()->getNbLignes(),string2,10);
	strcat(string,"/");
	strcat(string,string2);
	getAffCompteur()->setLabel(string);
	delete [] string;
	delete [] string2;

    m_data->getCurrentEtalon()->setCurrentEtalonLigneIndex(0);
	for(int i = 0; i<m_data->getCurrentEtalon()->getNbLignes();i++)
	{
		if (m_data->getCurrentEtalon()->getEtalonLigne(i)->getPeseeEffectuee() == false)
		{
	    	 m_data->getCurrentEtalon()->setCurrentEtalonLigneIndex(i);			
			break;
		}
	}
	// on réinitialise les données de pesees de la ligne à traiter
	m_data->getCurrentEtalon()->getCurrentEtalonLigne()->setNbPeseesEffectuees(0);
	m_data->getCurrentEtalon()->getCurrentEtalonLigne()->setNbPeseesOk(0);
	for (int j =0; j<m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPesees();j++)
	{
		m_data->getCurrentEtalon()->getCurrentEtalonLigne()->setArrPoidsPese(j,0);
	}
	afficherEtalonLigne();
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::afficherEtalonLigne()
{
	AdxData* m_data = getInterface()->getDonnees();


	getLabelUnPesee()->setLabel(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getUnite());
	getLabelUnAPeser()->setLabel(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getUnite());
	getLabelUnEcart()->setLabel(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getUnite());

	getPoidsEtalon()->setPrecision(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getDecimalePoids());	
	getPoidsAPeser()->setPrecision(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getDecimalePoids());	
	getEcartPoids()->setPrecision(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getDecimalePoids());	
	getPoidsPese()->setPrecision(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getDecimalePoids());	

	getPoidsEtalon()->setValue(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getPoids());
	getLibTypPesee()->setLabel(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getLibTypPesee());
	getPctTolerance()->setValue(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getTolerance());
	getPoidsAPeser()->setValue(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getPoids());
	getPoidsPese()->setValue(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getPoidsPese());
	getEcartPoids()->setValue(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getPoids());	
	_poidsPese = 0;
	_poidsAPeser  = 0;		//  104515 mm 03.2015
	bool error;
	_poidsAPeser = getPoidsAPeser()->getFloatValue(error);
	_tolerance   = getPctTolerance()->getFloatValue(error);

	adaptationEchelle();

	char* string = new char[4];
	char* string2 = new char[2];
	itoa(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPeseesEffectuees(),string,10);
	itoa(m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getNbPesees(),string2,10);
	strcat(string,"/");
	strcat(string,string2);
	getAffCompteurPesees()->setLabel(string);
	delete [] string;
	delete [] string2;

	const char* format = m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getFormat();
	getJaugeScale()->setFormat(format);
	getJaugePesee()->setValue(_poidsPese);

	getValider()->setSensitive(false);
	getTactile()->setSensitive(false);
//----------------------------------------------------------------------------------------
//MC : le fait de mettre la zone "non éditable" entraine sa traduction par le fichier .dbm
// évènement signalé au SAV Ilog (dossier 67115)
// nb: le champ "champSaisie" de l'écran clavier tactile a lui aussi été positionné
//    à "editable" dans Studio
// Ce comportement est voulu par Ilog, pour le contrarier il faudrait dériver
// IlvTextField et surcharger la méthode getMessage pour forcer à setLabel( que le champ
// soit éditable ou non) : très lourd, j'ai donc laissé tous les champs IlvTextField
// et IlvNumberField à "éditable"
//
//	getPoidsPese()->setEditable(false);
//----------------------------------------------------------------------------------------

	if (m_data->getCurrentBalance()->getConnecte() == 0)
	{
		getMessage()->setLabel(formatMessage("&Peser1"));
		bufferedDraw(getMessage());
		getmettreAZero()->setSensitive(false);
		getpeser()->setSensitive(true);
		setFocus(getpeser());
	}
	else
	{
//		getMessage()->setLabel(formatMessage("&Peser2"));
		getMessage()->setLabel(formatMessage("&FaireRemiseAZero"));
		bufferedDraw(getMessage());
		getmettreAZero()->setSensitive(true);
		getpeser()->setSensitive(false);
		setFocus(getmettreAZero());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::chargement()
{
	AdxData* m_data = getInterface()->getDonnees();
	getAffBalance()->setLabel(m_data->getCurrentBalance()->getBalance(), IlvTrue);
	// APCPDR-2423 mm 09.2013
	getAffLibBalance()->setLabel(m_data->getCurrentBalance()->getLibBalance(), IlvTrue);
	if (m_data->getCurrentBalance()->getConnecte() == 0)
	{
	    setVisible(getLighton(),IlvFalse, IlvFalse);
		getmettreAZero()->setSensitive(false);
	}
	else
	{
		getMessage()->setLabel(formatMessage("&FaireRemiseAZero"));
		bufferedDraw(getMessage());
		getmettreAZero()->setSensitive(true);
		getpeser()->setSensitive(false);
		setFocus(getmettreAZero());
	}

	getAffFicheEtalon()->setLabel(m_data->getCurrentEtalon()->getEtalon());
	getAffDesFiche()->setLabel(m_data->getCurrentEtalon()->getLibEtalon());

//  on réinitialise les données de pesees de l'etalon à traiter
	m_data->getCurrentEtalon()->setNbLignesEffectuees(0);
	m_data->getCurrentEtalon()->setNbLignesValidees(0);

//  on réinitialise les données de pesees de toutes les lignes de 
//	l'etalon à traiter
	for(int i = 0; i<m_data->getCurrentEtalon()->getNbLignes();i++)
	{
		m_data->getCurrentEtalon()->getEtalonLigne(i)->setPeseeEffectuee(false);
		m_data->getCurrentEtalon()->getEtalonLigne(i)->setPeseeValidee(false);
		for (int j =0; j<m_data->getCurrentEtalon()->getEtalonLigne(i)->getNbPesees();j++)
		{
			m_data->getCurrentEtalon()->getEtalonLigne(i)->setArrPoidsPese(j,0);
		}
	}
	afficherPesee();

}
			  
//---------------------------------------------------------------------------
void AdxPesee_Etalon::EntreeNumberFieldCB(IlvGraphic* g)
{
//	getTactile()->setSensitive(true);

	_champAppelant = (IlvNumberField*) g;
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::evolutionPoids()
{
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
    AdxData* m_data = getInterface()->getDonnees();

	_poidsPese = weighingInterface->getResNetWeight();
	getPoidsPese()->setValue(_poidsPese);
	bufferedDraw(getPoidsPese());

	getJaugePesee()->setValue(weighingInterface->getResNetWeight());

	double tolerance = 0.0;
	if (tolerance == 0)
		tolerance = m_data->getCurrentEtalon()->getCurrentEtalonLigne()->getTolerance();

	double weightMin = weighingInterface->getWeight() * 
						(1 - tolerance/100);
	double weightMax = weighingInterface->getWeight() *
						(1 + tolerance/100);

	IlvPalette* palette = getJaugePesee()->getPalette();
	IlvColor* foreground;
	if (weighingInterface->getResNetWeight() < weightMin)
	{
		foreground = getDisplay()->getColor("yellow");
	}
	if (weighingInterface->getResNetWeight() > weightMax)
	{
		foreground = getDisplay()->getColor("red");
	}
	if (weighingInterface->getResNetWeight() >= weightMin
		&& weighingInterface->getResNetWeight() <= weightMax)
	{
		foreground = getDisplay()->getColor("darkgreen");
	}
	palette->setForeground(foreground);
	getJaugePesee()->setPalette(palette);
	bufferedDraw(getJaugePesee());

// Calcul de l'ecart de poids et affichage
	bool error;
    // 104515 mm 03.2015 - _poidsAPeser : Conversion problem between a char * -> double
	// to solve it : cast double -> float
	_ecartPoids = fabs(weighingInterface->getResNetWeight()
//		- weighingInterface->getWeight());
		- (float) getPoidsAPeser()->getFloatValue(error));	
	getEcartPoids()->setValue(_ecartPoids);		
	bufferedDraw(getEcartPoids());
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::adaptationEchelle()
{
	// llc 03.02 changement 1.3333 par 1.25 pour avoir des résultats + ronds
	getJaugePesee()->setMin(0);
	getJaugePesee()->setMax(_poidsAPeser * 1.25);

	getJaugeScale()->setMin(0);
	getJaugeScale()->setMax(_poidsAPeser * 1.25);

	bufferedDraw(getJaugeScale());
}


//---------------------------------------------------------------------------
CString AdxPesee_Etalon::formatMessage(CString texte)
{
	CString string;
	string = IlvGetMessage(getDisplay(),texte);
	return string;
}

//---------------------------------------------------------------------------
void AdxPesee_Etalon::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	char szFileIcons[_MAX_PATH];
	// bouton BoutonListeEtalonLignes
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\book.png",
		_interface->getPathX3());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	getlisterEtalonLignes()->setBitmap(bitmap);
	setVisible(getlisterEtalonLignes(),IlvFalse, IlvFalse);	


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

	// bouton peser
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\scale1.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getpeser()->setBitmap(bitmap);

	// bouton mettreAZero
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\reset.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getmettreAZero()->setBitmap(bitmap);

	// bouton lighton
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\light_on.png",
			_interface->getPathX3());
	bitmap =	getDisplay()->readBitmap(szFileIcons);
	getLighton()->setBitmap(bitmap);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
	//setMaximumSize (sizeScreenW, sizeScreenH);
}
