// AdxPesee_OF.cpp
// ---------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------

#include "stdafx.h"
#include <cmath>
#include "AdxPesee_OF.h"
#include "AdxInterface.h"
#include "AdxWeighingInterface.h"

#include "AdxChoix_OF.h"
#include "AdxAccueil.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_Phase.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_LOT.h"
#include "AdxSelection_Balance.h"
#include "AdxSelection_Recipient.h"
#include "AdxOrder.h"
#include "AdxPhase.h"
#include "AdxComposant.h"
#include "AdxFicheISM.h"
#include "AdxFicheISMRecipient.h"
#include "AdxLot.h"
#include "AdxBalance.h"
#include "AdxRecipient.h"
#include "AdxPhrase_Secu.h"
#include "AdxRecontrole_OF.h"
#include "AdxData.h"
#include "AdxDate.h"
#include "AdxMessage.h"
#include "AdxProfile.h"

#include "x3centr1.h"
#include <fstream>							// 06.04 TRACE

using std::endl;							// 06.04 TRACE

/********************************************************************
 * Fonction   : showGraduation
 * But        : Pour afficher/cacher la graduation de la jauge
 * Parametres : 
 * Retour     : Rien
 ********************************************************************
 */
static void showGraduation(IlvGraphic* object, IlvAny )
{
	if (object && object->isSubtypeOf("IlvPopupMenu"))
	{
		IlvPopupMenu* menu = (IlvPopupMenu*)object;
		AdxPesee_OF* peseeOF = (AdxPesee_OF*)menu->getClientData ();
		IlvShort nPos = menu->whichSelected ();
		if (nPos >= 0)
		{
			IlvMenuItem* itemSel = menu->getItem((IlvUShort)nPos);
			IlvBoolean bShowGraduation = !itemSel->isChecked();
			itemSel->setChecked(bShowGraduation);
			peseeOF->_showGraduation = bShowGraduation;
			char szTemp[18] = "";
			sprintf (szTemp, "%01d", bShowGraduation);
			AdxProfile_PutValue (SECTION_ADXPESEE_OF, CLE_SHOW_GRADUATION, szTemp);
			// On affiche ou cache la graduation de la jauge
			peseeOF->getJaugeScale()->setVisible(bShowGraduation);
			peseeOF->getJaugeScale()->reDraw();
		}
	}
}

/********************************************************************
 * Fonction   : showTolerance
 * But        : Pour afficher/cacher la tolérance de la jauge
 * Parametres : 
 * Retour     : Rien
 ********************************************************************
 */
static void showTolerance(IlvGraphic* object, IlvAny )
{
	if (object && object->isSubtypeOf("IlvPopupMenu"))
	{
		IlvPopupMenu* menu = (IlvPopupMenu*)object;
		AdxPesee_OF* peseeOF = (AdxPesee_OF*)menu->getClientData ();
		IlvShort nPos = menu->whichSelected ();
		if (nPos >= 0)
		{
			IlvMenuItem* itemSel = menu->getItem((IlvUShort)nPos);
			IlvBoolean bShowTolerance = !itemSel->isChecked();
			itemSel->setChecked(bShowTolerance);
			peseeOF->_showTolerance = bShowTolerance;
			char szTemp[18] = "";
			sprintf (szTemp, "%01d", bShowTolerance);
			AdxProfile_PutValue (SECTION_ADXPESEE_OF, CLE_SHOW_TOLERANCE, szTemp);
			// On redessine l'écran 
			peseeOF->reDraw();
		}
	}
}

//--------------------------------------------------------------
AdxPesee_OF::~AdxPesee_OF()
{
	for (int i = 0; i < 10; i++)
	{
		delete _lignes[i];
	}

	delete [] _blanc;
	if (_popupJauge)
		delete _popupJauge;

}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------

// Ajout popup menu sur jauge
void AdxPesee_OF::RclicJauge(IlvGraphic* g)
{
	IlvPoint pMenu;
	IlvPos x;
	IlvPos y;
	IlUShort modifiers;
	this->getDisplay()->queryPointer(x,y,modifiers);
	pMenu.x(x);
	pMenu.y(y);
	_popupJauge->setClientData(this);
	_popupJauge->show(pMenu);
}


//---------------------------------------------------------------------------
void AdxPesee_OF::secu1CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxData* m_data = getInterface()->getDonnees();
	AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu1()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getPrecaution1()));

	// 06.07 mm - Forcer la lecture d'un message
	if (_balanceChoisie != NULL)
	{
		if (m_data->getCurrentFicheISM()->getMessageObligatoire() == 2 && _messageLu == false)
		{
			_messageLu = true ;
			suiteChoixBalance();		
		}
	}

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu2CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu2()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getPrecaution2()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu3CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu3()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getPrecaution3()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu4CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu4()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getPrecaution4()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu5CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu5()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getPrecaution5()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu6CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu6()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getPrecaution6()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu7CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxData* m_data = getInterface()->getDonnees();
	AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu7()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getCodeToxicite1()));

		// 06.07 mm - Forcer la lecture d'un message
	if (_balanceChoisie != NULL)
	{
		if (m_data->getCurrentFicheISM()->getMessageObligatoire() == 2 && _messageLu == false)
		{
			_messageLu = true ;
			suiteChoixBalance();		
		}
	}

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu8CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu8()->getBitmap());

	chargeTexte(IlvGetMessage(getDisplay(),
		_ficheISM->getCodeToxicite2()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu9CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu9()->getBitmap());

	if (_occup[8] == 1)
		chargeTexte(IlvGetMessage(getDisplay(),
			_ficheISM->getCodeToxicite3()));
	else
		chargeTexte(IlvGetMessage(getDisplay(),
			_ficheISM->getPrecaution8()));

	m_interface->getPhrase_Secu()->show();
	hide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::secu10CB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getPhrase_Secu()->setPanneauAppelant(this);

	m_interface->getPhrase_Secu()->getsecu()
		->setBitmap(getsecu10()->getBitmap());

	if (_occup[9] == 1)
		chargeTexte(IlvGetMessage(getDisplay(),
			_ficheISM->getCodeToxicite4()));
	else
		chargeTexte(IlvGetMessage(getDisplay(),
			_ficheISM->getPrecaution7()));

	m_interface->getPhrase_Secu()->show();
	hide();
}
//---------------------------------------------------------------------------
// Pesée multi-article exclusivement : 
// conversion du poids de la tare dans l'unité de l'article pesée
void AdxPesee_OF::setUnitePoidsMat1( const char* unit)
{
	if( _UPMat1 != 0) {
		delete [] _UPMat1;
	}
	_UPMat1 = new char[ strlen( unit) +1];
	strcpy( _UPMat1, unit);

}
//---------------------------------------------------------------------------
// Pesée multi-article  : conserver le nom de la première pesée
void AdxPesee_OF::setMat1( const char* str)
{
	if( _mat1 != 0) {
		delete [] _mat1;
	}
	_mat1 = new char[ strlen( str) +1];
	strcpy( _mat1, str);
}
//---------------------------------------------------------------------------
// constitution du bandeau des messages
void AdxPesee_OF::EntreeTextFieldCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true && _balanceChoisie->getConnecte())
	{
		// on est en pesée on sort
		return;
	}

	gettactile()->setSensitive(true);

	_champAppelant = (IlvTextField*) g;	
	CString string(IlvGetMessage(getDisplay(), "&Saisir"));
	string += " ";
	if (_champAppelant == getSaisieLot())
		string += IlvGetMessage(getDisplay(),"&Lot1");
	if (_champAppelant == getSaisieSousLot())
		string += IlvGetMessage(getDisplay(),"&SousLot1");
	if (_champAppelant == getSaisieEmplacement())
		string += IlvGetMessage(getDisplay(),"&Emplacement1");
	if (_champAppelant == getSaisieCuve())
		string += IlvGetMessage(getDisplay(),"&Cuve1");
	if (_champAppelant == getSaisieVanne())
		string += IlvGetMessage(getDisplay(),"&Vanne1");
	if (_champAppelant == getSaisieRecipient())
		string += IlvGetMessage(getDisplay(),"&Recipient1");
	if (_champAppelant == getSaisieBalance())
		string += IlvGetMessage(getDisplay(),"&Balance1");
	getmessage()->setLabel(string);
	bufferedDraw(getmessage()); 
}
				  
//---------------------------------------------------------------------------
void AdxPesee_OF::EntreeNumberFieldCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true && _balanceChoisie->getConnecte())
	{
		// on est en pesée on sort
		return;
	}

	gettactile()->setSensitive(true);

	_champAppelant = (IlvNumberField*) g;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::FocusOutLotCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}
}
//---------------------------------------------------------------------------
void AdxPesee_OF::FocusOutSousLotCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}
	AdxLot* lot = getInterface()->getDonnees()->getCurrentLot();
	// sr 01.03 ne pas afficher les quantités sinon on perd le bénéfice
	// du calcul fait dans SuiteChoixLot sur la quantité à proposer
	// sur le dernier lot
	afficherLot(lot,false);

}

//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieSousLotCB(IlvGraphic* g)
{
	AdxData* m_data = getInterface()->getDonnees();
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	if (m_data->getCurrentLot() != NULL)
		if ((strcmp(	getSaisieLot()->getLabel(), m_data->getCurrentLot()->getLot()) == 0)&&
			(strcmp( getSaisieSousLot()->getLabel(),m_data->getCurrentLot()->getSlo())== 0))
		{
			// contrôle lot
			if (controleLot())
			{	
				afficherLot(m_data->getCurrentLot());	
				// mm 10.11 - Pesée multi-article
				if (_enPeseeMultiArticle == true)
					suiteChoixLotMulti();
				else
					suiteChoixLot();
				setFocus(getSaisieEmplacement());
			}
			else
			{
				envoieMessage("&Valeur incorrecte",false);
				setFocus(getSaisieLot());
			}
			return;
		}

	int indexLotSvg = m_data->getCurrentLotIndex();
// verification lot existante et allouee
    int i = 0;
	for (i = 0; i < m_data->getNbLots(); i++)
	{ 		
		if ((strcmp(getSaisieLot()->getLabel(), m_data->getLot(i)->getLot()) == 0) &&
			(strcmp( getSaisieSousLot()->getLabel(),m_data->getLot(i)->getSlo() ) == 0))
		{
			m_data->setCurrentLotIndex(i);
			if (controleLot())
			{				
				afficherLot(m_data->getCurrentLot());	
				if (_enPeseeMultiArticle == true)
					suiteChoixLotMulti();
				else
					suiteChoixLot();
				setFocus(getSaisieVanne());
				break;
			}
		}
	}
// si on a pas trouve de cuve on retablit la situation anterieure
	if (i == m_data->getNbLots())
	{
		envoieMessage("&Valeur incorrecte",false);
		m_data->setCurrentLotIndex(indexLotSvg);	
		afficherLot(m_data->getCurrentLot());
		setFocus(getSaisieEmplacement());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieLotCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	//AdxLot* lot = getInterface()->getDonnees()->getCurrentLot();
	// APCPDR-2755 mm 01.2013 
	AdxData* m_data = getInterface()->getDonnees();
  	
	if (m_data->getCurrentLot() != NULL)
	{
		if (strcmp(getSaisieLot()->getLabel(),m_data->getCurrentLot()->getLot()) != 0)
		{
			getSaisieSousLot()->setLabel("");
			bufferedDraw(getSaisieSousLot());
			setFocus(getSaisieSousLot());
		}
	}
}
//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieCuveCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	AdxData* m_data = getInterface()->getDonnees();

	if (m_data->getCurrentLot() != NULL)
		if (strcmp(	getSaisieCuve()->getLabel(), 
					m_data->getCurrentLot()->getCuve()) == 0)
		{
			// contrôle lot
			if (controleLot())
			{						
				afficherLot(m_data->getCurrentLot());
				suiteChoixLot();
				setFocus(getSaisieVanne());
			}
			else
			{
				setFocus(getSaisieCuve());
			}
			return;
		}

	int indexLotSvg = m_data->getCurrentLotIndex();
// verification cuve existante et allouee
	int i = 0;
	for (i = 0; i < m_data->getNbLots(); i++)
	{ 
		if (strcmp(	getSaisieCuve()->getLabel(), 
					m_data->getLot(i)->getCuve()) == 0)
		{
			m_data->setCurrentLotIndex(i);
			if (controleLot())
			{				
				afficherLot(m_data->getCurrentLot());
				suiteChoixLot();
				setFocus(getSaisieVanne());
				break;
			}
		}
	}
// si on a pas trouve de cuve on retablit la situation anterieure
	if (i == m_data->getNbLots())
	{
		envoieMessage("&Valeur incorrecte",false);
		m_data->setCurrentLotIndex(indexLotSvg);	
		afficherLot(m_data->getCurrentLot());
		setFocus(getSaisieCuve());
	}
}
//---------------------------------------------------------------------------
void AdxPesee_OF::ListeLotCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

    AdxInterface* m_interface = getInterface();
	m_interface->getSelection_LOT()->setPanneauAppelant(this);
	AdxData* m_data = m_interface->getDonnees();
	IlvRect m_rect = 0;
	boundingBox (m_rect);
	// demande de mise a jour du fichier lot
	if (m_data->getComposantAlloue() == false)
	{
		IlvBoolean err;
		m_interface->setPanneauAppelant(this);
		bool dataOK = m_data->acquisitionLots(getAffTotalAPeser()->getFloatValue(err));
	}


	// mm 02.11 - magasin avancé 
	// priorité aux allocations de l'OF : le tableau de sélection des lots est exclusivement consultable 
	//(pas de sélection possible)
	if ( m_data->getPrioriteAllocationCode() == 1
		&& m_data->getCurrentComposant()->getQuantiteAlloueeDpOF()!=0)
	{	
		if (m_data->getCurrentComposant()->getQuantiteAlloueeRestante()!=0)
		{
			// pas de possibilité de modifier les champs lot, sous-lot, etc
			// 91927 mm 08.2013
			// setChampsAlphaEditable(false);
			// sinon tableaux de sélection récipient et balance sont exclusivement consultables...
			getSaisieRecipient()->setEditable(true);
			getSaisieBalance()->setEditable(true);
			m_interface->getSelection_LOT()->chargement(false);
		}
		else
			m_interface->getSelection_LOT()->chargement(_stockReelInfInfo);   
	}
	else
	// chargement de la matrice avec premiere ligne = premier Lot
	// si stock est inf a zero on charge SelectionLot pour que les allocs soient modifiables
	//  sinon on les charge juste pour qu'elles soient liste de selections
	// SR 12.11 APCPRD-724
	{
		if ((_modifAllocations == true) && (getSaisieLot()->isEditable())&(m_data->getComposantBegin()==false))
		{
			m_interface->getSelection_LOT()->chargement(_modifAllocations);   
		}
		else
		{			
			m_interface->getSelection_LOT()->chargement(_stockReelInfInfo);   
		}	
	}
	CString string;
	if (getSaisieLot()->isEditable())
	{
		m_interface->setPanneauAppelant(this);
		string += IlvGetMessage(getDisplay(), "&Choisir");
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Lot1");
	}
	else
	{
		string += IlvGetMessage(getDisplay(), "&ConsultationSansSelection");
	}
	
	m_interface->getSelection_LOT()->getmessage()->setLabel(string);
	m_interface->getSelection_LOT()->show();
	hide();
	string.Empty();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::FocusOutEmplacementCB(IlvGraphic* g)
{	
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	AdxLot* lot = getInterface()->getDonnees()->getCurrentLot();
	afficherLot(lot,false);
}

//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieEmplacementCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	AdxData* m_data = getInterface()->getDonnees();

	if (m_data->getCurrentLot() != NULL)
		if (strcmp(	getSaisieEmplacement()->getLabel(), 
					m_data->getCurrentLot()->getEmplacement()) == 0)
		{
			// contrôle lot
			if (controleLot())
			{
				getLibSaisieEmplacement()->setLabel(m_data->getCurrentLot()->getLibEmplacement());
				// mm 10.11 - Pesée multi-article
				if (_enPeseeMultiArticle == true)
					suiteChoixLotMulti();
				else
					suiteChoixLot();
			}
			else
			{
				envoieMessage("&Valeur incorrecte",false);
				setFocus(getSaisieEmplacement());
			}
			return;
		}
	int indexLotSvg;
// verification lot/emplacement existant
	int i=0;
	indexLotSvg = m_data->getCurrentLotIndex();
	while (i < m_data->getNbLots())
	{
		if (strcmp (getSaisieLot()->getLabel(), m_data->getLot(i)->getLot()) == 0
			&& strcmp (getSaisieEmplacement()->getLabel(), m_data->getLot(i)->getEmplacement()) == 0)
		{
			m_data->setCurrentLotIndex(i);
			if (controleLot())
			{
				getLibSaisieEmplacement()->setLabel( m_data->getLot(i)->getLibEmplacement());
		        // mm 10.11 - Pesée multi-article
				if (_enPeseeMultiArticle == true)
					suiteChoixLotMulti();
				else
					suiteChoixLot();
				break;
			}
		}
		i++;
	}

	if (i == m_data->getNbLots())
	{
		m_data->setCurrentLotIndex(indexLotSvg);	
		afficherLot(m_data->getCurrentLot());
		setFocus(getSaisieEmplacement());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieVanneCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	AdxData* m_data = getInterface()->getDonnees();

	if (m_data->getCurrentLot() != NULL)
		if (strcmp(	getSaisieVanne()->getLabel(), 
					m_data->getCurrentLot()->getVanne()) == 0)
		{
			// contrôle lot
			if (controleLot())
			{
				suiteChoixLot();
			}
			else
			{
				envoieMessage("&Valeur incorrecte",false);
				setFocus(getSaisieVanne());
			}
			return;
		}
	int indexLotSvg = m_data->getCurrentLotIndex();
// verification lot/emplacement existant
	int i=0;
	while (i < m_data->getNbLots())
	{
		if (strcmp (getSaisieCuve()->getLabel(), m_data->getLot(i)->getCuve()) == 0
			&& strcmp (getSaisieVanne()->getLabel(), m_data->getLot(i)->getVanne()) == 0)
		{
			m_data->setCurrentLotIndex(i);
			if (controleLot())
			{
				afficherLot(m_data->getCurrentLot());
				suiteChoixLot();
				break;
			}
		}
		i++;
	}

	if (i == m_data->getNbLots())
	{ 
		m_data->setCurrentLotIndex(indexLotSvg);
		afficherLot(m_data->getCurrentLot());
		setFocus(getSaisieVanne());
		return;
	}
}
//---------------------------------------------------------------------------
void AdxPesee_OF::ListeEmplacementCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

// utilité ? masqué pour l'instant
    const char* className = g->className();
    IlvPrint(" %s : ListeEmplacementCB method ...",className);
}

//---------------------------------------------------------------------------
void AdxPesee_OF::FocusOutRecipientCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	if (_recipientChoisi != NULL)
	{
		getSaisieRecipient()->setLabel(_recipientChoisi->getRecipient());
		getLibSaisieRecipient()->setLabel(_recipientChoisi->getLibRecipient());// mm libellé
	}
	else
	{
		getSaisieRecipient()->setLabel("");	
		getLibSaisieRecipient()->setLabel("");// mm libellé
	}

}

//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieRecipientCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	AdxData* m_data = getInterface()->getDonnees();
	if (strcmp(getSaisieRecipient()->getLabel(), "") == 0)
		return;


	if (_recipientChoisi != NULL)
		if (strcmp(getSaisieRecipient()->getLabel(),
			_recipientChoisi->getRecipient()) == 0)
		{
			// contrôle recipient
			if (controleRecipient())
			{
				suiteChoixRecipient();
			}
			else
			{
				erreurRecipient();
			}
			return;
		}
// verification recipient existant
	IlList* recipientList = m_data->getRecipientList();
	AdxRecipient* recipientSvg;
	int i = 0;
	for ( i = 0; i < m_data->getNbRecipients() ; i++)
	{
		AdxRecipient* recipient = (AdxRecipient*)(*recipientList)[i];
		if (strcmp(recipient->getRecipient(),getSaisieRecipient()->getLabel()) == 0)
		{
			recipientSvg = _recipientChoisi;
			setRecipientChoisi(recipient);
			break;
		}
	}
// pas de recipient trouve
	if (i >=  m_data->getNbRecipients())
	{
		if (_recipientChoisi != NULL)
		{
			getSaisieRecipient()->setLabel(_recipientChoisi->getRecipient());	
		}
		else
		{
			getSaisieRecipient()->setLabel("");
		}
		erreurRecipient();
		return;
	}
// contrôle recipient
	if (controleRecipient())
	{
		suiteChoixRecipient();
	}
	else
	{
		setRecipientChoisi(recipientSvg);
		if (recipientSvg == NULL)
			_recipientOK = false;
		else
			_recipientOK = true;
		    erreurRecipient();
	}
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::erreurRecipient()
{
 	AdxInterface* m_interface = getInterface();
	envoieMessage("&Valeur incorrecte",false);
    setFocus(getSaisieRecipient());
	return _recipientOK;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::ListeRecipientCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

 	AdxInterface* m_interface = getInterface();

	if (!_lotOK)
	{
		attenteSaisieLot();
		return;
	}

	m_interface->getSelection_Recipient()->setPanneauAppelant(this);
	IlvRect m_rect = 0;
	boundingBox (m_rect);
	m_interface->getSelection_Recipient()
		->setListeSelectionRecipient(0);

	if (getSaisieRecipient()->isEditable())
	{
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Recipient1");
		m_interface->getSelection_Recipient()->getmessage()->setLabel(string);
	}
	else
	{
		CString string(IlvGetMessage(getDisplay(), "&ConsultationSansSelection"));
		m_interface->getSelection_Recipient()->getmessage()->setLabel(string);
	}

	hide();
	m_interface->getSelection_Recipient()->show();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::FocusOutBalanceCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	if (_balanceChoisie != NULL)
		getSaisieBalance()->setLabel(_balanceChoisie->getBalance());
	else
		getSaisieBalance()->setLabel("");
}

//---------------------------------------------------------------------------
void AdxPesee_OF::SaisieBalanceCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	AdxData* m_data = getInterface()->getDonnees();
	if (strcmp (getSaisieBalance()->getLabel(), "") == 0)
		return;

	if (_balanceChoisie != NULL)
		if (strcmp(getSaisieBalance()->getLabel(),
			_balanceChoisie->getBalance()) == 0)
		{
			// mc : vérifier si c'est ce qu'il faut faire
			// contrôle balance
			if (controleBalance(false))
			{
				suiteChoixBalance();
			}
			else
			{
				envoieMessage("&Valeur incorrecte",false);
				setFocus(getSaisieBalance());
			}
			return;
		}
// verification balance existante
	IlList* balanceList = m_data->getBalanceList();
	AdxBalance* balanceSvg;
	int i = 0;
	for ( i = 0; i < m_data->getNbBalances() ; i++)
	{
		AdxBalance* balance = (AdxBalance*)(*balanceList)[i];
		if (strcmp(balance->getBalance(),getSaisieBalance()->getLabel()) == 0)
		{
			balanceSvg = _balanceChoisie;
			setBalanceChoisie(balance);
			_balanceBegin = false;
			break;
		}
	}
// pas de balance trouvee
	if (i >=  m_data->getNbBalances())
	{
		envoieMessage("&Valeur incorrecte",false);
		if (_balanceChoisie != NULL)
			getSaisieBalance()->setLabel(_balanceChoisie->getBalance());	
		else
			getSaisieBalance()->setLabel("");
		setFocus(getSaisieBalance());
		return;
	}
// contrôle balance
	if (controleBalance(true))
	{
		suiteChoixBalance();
	}
	else
	{
		envoieMessage("&Valeur incorrecte",false);
	    setBalanceChoisie(balanceSvg);
		setFocus(getSaisieBalance());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::ListeBalanceCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

 	AdxInterface* m_interface = getInterface();

	if (!_lotOK)
	{
		attenteSaisieLot();
		return;
	}

	if (!_recipientOK)
	{
		setFocus(getSaisieRecipient());
		return;
	}

	m_interface->getSelection_Balance()->setPanneauAppelant(this);
	IlvRect m_rect = 0;
	boundingBox (m_rect);
// chargement de la matrice avec première ligne = Balance en cours
	m_interface->getSelection_Balance()->setListeSelectionBalance(0);

	
	if (getSaisieBalance()->isEditable())
	{
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Balance1");
		m_interface->getSelection_Balance()->getmessage()->setLabel(string);
	}
	else
	{
		CString string(IlvGetMessage(getDisplay(), "&ConsultationSansSelection"));
		m_interface->getSelection_Balance()->getmessage()->setLabel(string);
	}
	

	m_interface->getSelection_Balance()->show();
	hide();
}

/*	
//---------------------------------------------------------------------------
void AdxPesee_OF::EnterPoidsPeseCB(IlvGraphic* g)
{

	_saisieFaite = true;

	SaisiePoidsPeseCB(g);

}
*/
//---------------------------------------------------------------------------
void AdxPesee_OF::SaisiePoidsPeseCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true && _balanceChoisie->getConnecte())
	{
		// on est en pesée on sort
		return;
	}

	bool error;
	AdxData* m_data = getInterface() ->getDonnees();		// mm 10.08

// saisie de la valeur de tarage
	if (_attenteTarage == true)
	{
		_poidsTare = getSaisiePoidsPese()->getFloatValue(error);
//		if (_poidsTare == 0) return; // autoriser tare nulle ?
//		if (_saisieFaite == false) return;
///////////////////////////////////////////////////////////
// test mc : conversion d'un poids de tare saisi manuellement
//           de l'unité de la balance vers celle du composant
// ep: probleme de la pese degradee quand la balance n'est pas dans l'unite composant
//     pour le moment l'utilisateur doit faire la conversion dans sa tête
//		_poidsTare = getInterface()->getDonnees()->convertir(
//			_poidsTare,
//			_balanceChoisie->getUnite(),
//			getUnitePoidsPese()->getLabel());
////////////////////////////////////////////////////////////
		
		if (_recipientChoisi->getTypeRecipient() ==	1)
		{
			_tarageOK = true;

			gettactile()->setSensitive(false);
			gettarer()->setSensitive(false);		
			getpeser()->setSensitive(true);
			getAffTare()->setValue(_poidsTare);
			getSaisiePoidsPese()->setValue(_poidsPese);
			bufferedDraw(getAffTare());
			bufferedDraw(getSaisiePoidsPese());
			AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
			weighingInterface->setWeight(_poidsAPeser);
			weighingInterface->setResNetWeight(_poidsPese);
			weighingInterface->setTotWeight(_totalAPeserInitial);
			weighingInterface->setTotResWeight(_poidsPese);
//			evolutionPoids();
			_attenteTarage = false;
			_attentePesee = true;
	
//			edition message
			getmessage()->setLabel(formatMessage("&TarageEffectuePeser"));
			bufferedDraw(getmessage());
			setFocus(getpeser());
			return;
		}
		else 
		{
			// 04.07 gestion d'une tare modifiable en cas d'emballage fournisseur
			if ( _recipientChoisi->getTareModifiable() ==2)
			{
				// mm 06.09 - conversion du poids de la tare dans l'unité du récipient
				_recipientChoisi->setTareTheo(m_data->convertir(_poidsTare,
					m_data->getCurrentComposant()->getUnite(),
					_recipientChoisi->getUnitePoids()));

				getAffTare()->setValue(_poidsTare);
				bufferedDraw(getAffTare());		

				// 02.09 mm -  en cas de pesée limitée par balance 
				// recalcul du poids à peser en fonction de la tare saisie
				double PorteeMaxi = m_data->convertir( _balanceChoisie->getPorteeMaxi(),
					_balanceChoisie->getUnite(),m_data->getCurrentComposant()->getUnite());
				if (PorteeMaxi < ((1 +_recipientChoisi->getTolerance()/100) *_poidsTare) + _poidsAPeser)
				{
	
					_poidsAPeser = PorteeMaxi - ((1 +_recipientChoisi->getTolerance()/100) * _poidsTare ) ;
					getAffPoidsAPeser()->setValue(_poidsAPeser);
					bufferedDraw(getAffPoidsAPeser());
				}

				// rafraichissement de l'affichage
				getSaisiePoidsPese()->setValue(0.0); // mm 10.08
				bufferedDraw(getSaisiePoidsPese());
				gettarer()->setSensitive(false);
				
				// mm 10.08
				_attenteTarage = false;	
				_tarageOK = true;
				_attentePesee = true;

				// mm 06.09 - balance connectée
				if (_balanceChoisie->getConnecte() == 1)
				{
					getmessage()->setLabel(formatMessage("&FaireRemiseAZero"));
					bufferedDraw(getmessage());
					getmettreAZero()->setSensitive(true);
					getpeser()->setSensitive(false);
					setFocus(getmettreAZero());
				}
				else
				{
					//	edition message
					getmessage()->setLabel(formatMessage("&TarageEffectuePeser"));
					bufferedDraw(getmessage());
					getpeser()->setSensitive(true);
					setFocus(getpeser());
				}
				return;
			}
		}
	}

// saisie de la valeur de pesee
	if (_attentePesee == true)
	{
		_poidsPese = getSaisiePoidsPese()->getFloatValue(error);
// sr 22/04 laisser peser 0 pour redressement emballage
//		if (_poidsPese == 0) return;

///////////////////////////////////////////////////////////
// test mc : conversion d'un poids pesé saisi manuellement
//           de l'unité de la balance vers celle du composant
// ep: probleme de la pese degradee quand la balance n'est pas dans l'unite composant
//     pour le moment l'utilisateur doit faire la conversion dans sa tête
//		_poidsPese = getInterface()->getDonnees()->convertir(
//			_poidsPese,
//			_balanceChoisie->getUnite(),
//			getUnitePoidsPese()->getLabel());
//		getSaisiePoidsPese()->setValue(_poidsPese);
////////////////////////////////////////////////////////////

		_peseeOK = true;
		gettactile()->setSensitive(false);
		getpeser()->setSensitive(false);
		getvalider()->setSensitive(true);

		// adaptation echelle en fonction du poids à peser
		// positionnement de la jauge en fonction du poids pesé	
		AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
		weighingInterface->setWeight(_poidsAPeser);
		weighingInterface->setResNetWeight(_poidsPese);
		weighingInterface->setTotWeight(_totalAPeserInitial);
		weighingInterface->setTotResWeight(_poidsPeseTotal);
		evolutionPoids();
		_poidsEncours = _poidsPese;

		// 116324 mm08.2016 - 
  		if (m_data->getCurrentComposant()->getGestionStock() != 3) 
		{
			_poidsPeseTheo  = _poidsPese;
		}
		else
		{
			_poidsPeseTheo  = _poidsPese * m_data->getCurrentLot()->getTitre()
				/ m_data->getCurrentComposant()->getTitreTheo();
		}	

	    // mm 09.11 - Pesée multi-article
		// la première matière doit être totalement  pesée pour que le Bt V+ soit actif 
		// (la 1ere matiere ne peut pas être partiellement pesée puis être cumulée à la seconde)
		//  APCPRD-727 : il faudrait faire la même chose quelque soit la matière
		if ( _poidsPeseTheo + _poidsPeseTotal <= getWeightMax())
		{
			if (_poidsPeseTheo + _poidsPeseTotal >= getWeightMin())
				getvaliderPlus()->setSensitive(true);
			else
				getvaliderPlus()->setSensitive(false);	
		}
		else
		{
			//116324  mm 08.2016 - authorization to exceed tolerance+
			if  ( m_data->getExceedingTolerancePos()==2 )
				getvaliderPlus()->setSensitive(true);
			else
				getvaliderPlus()->setSensitive(false);	
		}
		if (getvaliderPlus()->isSensitive() == true)
		{
			boutonValiderPlus();
			if (getBoutonValidation() == 2)
			{
				setBoutonValidation(1);
				getmessage()->setLabel(formatMessage("&BoutonValiderPlus"));
				setFocus(getvaliderPlus());
			}
			else if (getBoutonValidation() == 1)
			{	
				// premier composant pesé en cumulé multi-articles
				if (getvaliderPlus()->isSensitive()== true)
					getmessage()->setLabel(formatMessage("&PeseeEffectueePlus"));	
				else
				{
					// réoriente vers la validation std
					getmessage()->setLabel(formatMessage("&PeseeEffectuee"));
					setFocus(getvalider());
				}
			}
			bufferedDraw(getmessage());
		}
		else
		{
			// edition message : pesée partielle std ou lors de pesées multi-articles
			getmessage()->setLabel(formatMessage("&PeseeEffectuee"));
			bufferedDraw(getmessage());
			setFocus(getvalider());
		}
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::tactileCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true && _balanceChoisie->getConnecte())
	{
		// on est en pesée on sort
		return;
	}

	if (_champAppelant->isEditable() == false)
		return;
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
void AdxPesee_OF::mettreAZeroCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxPesee_OF::mettreAZeroCB Entree" << endl;
    }


	// 48084 mm 08.09
	getmessage()->setLabel(formatMessage("&FaireRemiseAZero1"));
	bufferedDraw(getmessage());

	setChampsAlphaEditable(false);
// remise à zéro pour une balance connectee
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	WeighingOrder order;

	order = RAZ_M;
	weighingInterface->setWeighingOrder(order);
	// GBE 16/09/08 mise à zéro des flags
	weighingInterface->setStopPesee(false);
	weighingInterface->setCancel(false);
	weighingInterface->setValid(false);
	// gbe 10.08
	_enPesee = true;

	weighingInterface->setPanneauAppelant(this);
	weighingInterface->weighingOrderTreatment();
	// gbe 10.08
	_enPesee = false;

	if (weighingInterface->getResWeighingMessage() != NULL)
	{
		if (weighingInterface->getWeighingStatus() == OK_STA)
		{
			_miseAZeroOK = true;
			getmettreAZero()->setSensitive(false);
			// sr 11.02 si tare = 0 on va directement demander de peser
			if (_recipientChoisi->getTypeRecipient() != 2 
				&& _recipientChoisi->getTareTheo() != 0 )
			{
				getmessage()->setLabel(formatMessage("&RemiseAZeroEffectuee1  "));
				gettarer()->setSensitive(true);
      			_poidsTare = 0;
    			getAffTare()->setValue(_poidsTare);
	    		bufferedDraw(getAffTare());

				setFocus(gettarer());
			}
			else
			{
                if(_recipientChoisi->getTareTheo() == 0 )
                {
                 	_poidsTare = 0;
    			    getAffTare()->setValue(_poidsTare);
	    		    bufferedDraw(getAffTare());
                }
				getmessage()->setLabel(formatMessage("&RemiseAZeroEffectuee2  "));
				gettarer()->setSensitive(false);
				getpeser()->setSensitive(true);
				setFocus(getpeser());
			}
		}
		else
		{
			getmessage()->setLabel(formatMessage(weighingInterface->getResWeighingMessage()));
		}
		bufferedDraw(getmessage());
	}
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxPesee_OF::mettreAZeroCB sortie" << endl;
    }
}

//---------------------------------------------------------------------------
void AdxPesee_OF::tarerCB(IlvGraphic* g)
{
	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxPesee_OF::tarerCB Entree" << endl;
    }

	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	// 03.10 mm - modification du recontrole OF 
	// si pesée en fabrication, le code recontrôle cuve doit être = cuve ou
	// si peséee par OF ou article, le code recontrôle article doit être différent de non

	 if(_recontroleFait == false)
	{
		if ((m_interface->getFonctionEnCours() == 3 && m_data->getRecontroleCuveCode() == 2) ||
 			 ( m_interface->getFonctionEnCours() != 3 &&
			(!m_data->getRecontroleArticleCode() || m_data->getRecontroleArticleCode() !=1)))
		{
			_boutonAppelant = (IlvZoomableTransparentIcon*) g;	
			recontroleOF();
			return;
		}
	}
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxPesee_OF::tarerCB Recontrole fait" << endl;
    }


	setChampsAlphaEditable(false);

	// sr 12.02 pour ne pas faire n'importe quoi
	getpeser()->setSensitive(false);	
	gettarer()->setSensitive(false);	
	
	if (affecteBalance() == false) 
	{
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::tarerCB affecteBalance() == false" << endl;
		}
		_attentePesee = false;
		_attenteTarage = true;

		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Tare1");
		getmessage()->setLabel(string);
		bufferedDraw(getmessage());

		setFocus(getSaisiePoidsPese());
		return;
	}


	if (_miseAZeroOK == false)
	{
		setFocus(getSaisiePoidsPese());
		getmessage()->setLabel(formatMessage("&FaireRemiseAZero"));
		bufferedDraw(getmessage());
		gettactile()->setSensitive(false);
		getmettreAZero()->setSensitive(true);
		gettarer()->setSensitive(false);
		getpeser()->setSensitive(false);
		return;
	}
	
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	WeighingOrder order;
	// GBE 16/09/08 mise à zéro des flags
	weighingInterface->setStopPesee(false);
	weighingInterface->setCancel(false);
	weighingInterface->setValid(false);
	// gbe 10.08
	_enPesee = true;
	
	// mm 02.09 - 2 messages distincts , avant et après avoir appuyé sur bt Tarer, pour savoir où on en est !
	getmessage()->setLabel(formatMessage("&ResteATarer"));
	bufferedDraw(getmessage());

// pour ne pas pouvoir y acceder par le champs tactile
//	getSaisiePoidsPese()->setEditable(false);
// tarage manuel sur balance connectee

	order = TAR_M;  
	weighingInterface->setWeighingOrder(order);

// llc 03.02 pour la gestion de la couleur de jauge en tarage, il faut passer le poids 
//	de référence sinon c'est tout rouge ...
//	weighingInterface->setWeight(_poidsPese);
	weighingInterface->setWeight(_recipientChoisi->getTareTheo());
	weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
	weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

	weighingInterface->setPanneauAppelant(this);
	weighingInterface->weighingOrderTreatment();
	// gbe 10.08
	_enPesee = false;


//	_balanceChoisie->setUnite(weighingInterface->getResWeightUnit());

	if (weighingInterface->getResTare() != NULL)
	{
		_poidsTare = weighingInterface->getResTare();
		getAffTare()->setValue(_poidsTare);
		bufferedDraw(getAffTare());
	}

    if (weighingInterface->getResWeighingMessage() != NULL)
	{
		if (weighingInterface->getWeighingStatus() == OK_STA)
		{
			getmessage()->setLabel(formatMessage("&TarageEffectue         "));
			bufferedDraw(getmessage());
			getSaisiePoidsPese()->setValue(_poidsPese);
			bufferedDraw(getSaisiePoidsPese());
// sr 16.04
//			getJaugePesee()->setValue(_poidsPese);
//			bufferedDraw(getJaugePesee());
			_tarageOK = true;
			gettactile()->setSensitive(false);
			gettarer()->setSensitive(false);
			getpeser()->setSensitive(true);
			setFocus(getpeser());
		}
		else
		{
			getmessage()->setLabel(formatMessage(weighingInterface->getResWeighingMessage()));
			gettarer()->setSensitive(true);
		}
		bufferedDraw(getmessage());
	}
// pour retablir l'acces a la zone
//	getSaisiePoidsPese()->setEditable(true);
	if (getInterface()->getTraceMode() == 1)
    {
		getInterface()->_traceFile << "AdxPesee_OF::tarerCB sortie" << endl;
    }
}

//---------------------------------------------------------------------------
void AdxPesee_OF::peserCB(IlvGraphic* g)
{

	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	// SR 03.12 APCPRD-729
	WeighingOrder order;
	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxPesee_OF::peserCB Enter"<< endl;
	}

	// gbe 10.08
	if(_enPesee == true)
	{
		// on est en pesée on sort
		return;
	}

	// recontrole OF 
	// si pesée en fabrication, le code recontrôle cuve doit être = cuve ou
	// si peséee par OF ou article, le code recontrôle article doit être différent de non
    if (_recontroleFait == false)
	{
		// APCPRD-2636 mm 08.2013 - 
		// si tare récipient = 0, emballage interne, mode déconnecté
		// bt peser doit rester actif tant que recontrole non fait
		if ((_recipientChoisi->getTypeRecipient() == 1) &&( _recipientChoisi->getTareTheo() ==0 ) &&
	    ( ! _balanceChoisie->getConnecte())) 
			getpeser()->setSensitive(true);

		if ((m_interface->getFonctionEnCours() == 3 && m_data->getRecontroleCuveCode() == 2) ||
 			 ( m_interface->getFonctionEnCours() != 3 &&
			(!m_data->getRecontroleArticleCode() || m_data->getRecontroleArticleCode() !=1)))
		{
			_boutonAppelant = (IlvZoomableTransparentIcon*) g;	
			recontroleOF();
			return;
		}
	}

	// sr 11.02 pour ne pas pouvoir faire n'importe quoi !!
	gettarer()->setSensitive(false);
	getpeser()->setSensitive(false);

//	sr 03.12 APCPRD-729 : APCPRD-2426 : a faire plus tard 
/*	if (_balanceChoisie->getConnecte()==1)
	{
		order = CLAV_BAL_LOCK;
		weighingInterface->setWeighingOrder(order);
		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();
	}
*/
	// désactivation du bouton Valider+ 
	getvaliderPlus()->setSensitive(false);
	// Ré-initialisation du flag
	if (_balanceChoisie->getConnecte() == 1)
	   setBoutonValidation(1);
	

	if (_recipientChoisi->getTypeRecipient() != 2 && controleTare() == false) 
	{
		_poidsTare = 0;
		getSaisiePoidsPese()->setValue(_poidsTare);
		bufferedDraw(getSaisiePoidsPese());
		getAffTare()->setValue(_poidsTare);
		bufferedDraw(getAffTare());
		envoieMessage("&TareInvalide",false);
		if (affecteBalance())
        {
		    envoieMessage("&ViderPlateau",false);
			annuleTarage();
		    getmessage()->setLabel(formatMessage("&Tarage"));
		    bufferedDraw(getmessage());
        }

		gettarer()->setSensitive(true);
		tarerCB(gettarer());
		return;
	}
	//  SR 05/11/12 JIRA 2426 on lock à ce moment là seulement
	if (_balanceChoisie->getConnecte()==1)
	{
		order = CLAV_BAL_LOCK;
		weighingInterface->setWeighingOrder(order);
		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();
	}
	setChampsAlphaEditable(false);

// sr 20/04
    if (_peseeParConsigne)
    {
        getJaugePesee()->setValue(-_totalAPeserInitial +_poidsPeseTotal);	
    }
    else
    {
        getJaugePesee()->setValue(_poidsPeseTotal);
    }
	bufferedDraw(getJaugePesee());
	drawScaleLines();

	if (affecteBalance() == false)
	{
		_attentePesee = true;
		_attenteTarage = false;
		CString string;
		if (_peseeParEcart)
			string = IlvGetMessage(getDisplay(), "&PeseeParEcart");
		else
			string = IlvGetMessage(getDisplay(), "&PeseeCumulee");
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Saisir");
		string += " ";
		string += IlvGetMessage(getDisplay(),"&PoidsPese1");
		getmessage()->setLabel(string);
		bufferedDraw(getmessage());
		setFocus(getSaisiePoidsPese());
		return;
	}

	// GBE 16/09/08 mise à zéro des flags
	weighingInterface->setStopPesee(false);
	weighingInterface->setCancel(false);
	weighingInterface->setValid(false);
	// gbe 10.08
	_enPesee = true;

// PESEE SANS CONSIGNE
	if (!_peseeParConsigne)

	{
		// llc 04.02 pour mettre la jauge dans le bon mode avant la première pesée de la MP
        //adaptationEchelle();
	// pour les recipients fournisseur  tarage automatique
		if (_recipientChoisi->getTypeRecipient() == 2)
		{
			_poidsTare = m_data->convertir(
				_recipientChoisi->getTareTheo(), 
				_recipientChoisi->getUnitePoids(), 
				m_data->getCurrentComposant()->getUnite());
			getAffTare()->setValue(_poidsTare);
			bufferedDraw(getAffTare());
			_tarageOK = true;
	// envoie des info de tarage a la balance
			order = CONS_TAR_M;
			weighingInterface->setWeighingOrder(order);

			weighingInterface->setTare(_poidsTare);
			weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
			weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

			weighingInterface->setPanneauAppelant(this);
			weighingInterface->weighingOrderTreatment();
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 1 getValid("<<weighingInterface->getValid()
					<<") getCancel("<<weighingInterface->getCancel()
					<<") setStopPesee("<<weighingInterface->getStopPesee()<<")"<< endl;
				getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 1 getResWeighingMessage("<<weighingInterface->getResWeighingMessage()
					<<") getWeighingStatus("<<weighingInterface->getWeighingStatus()<<")"<< endl;
			}

	//		_balanceChoisie->setUnite(weighingInterface->getResWeightUnit());

			weighingInterface->setResTare(_poidsTare);
			/*if (weighingInterface->getResTare() != NULL)	
			{*/												
				getAffTare()->setValue(_poidsTare);
				bufferedDraw(getAffTare());
	   		/*}													
			if (weighingInterface->getResWeighingMessage() != NULL)	
			{*/													
				getSaisiePoidsPese()->setValue(0.0);
				bufferedDraw(getSaisiePoidsPese());
// sr 16.04
			  /*getJaugePesee()->setValue(0);						
				bufferedDraw(getJaugePesee());						
			}													
			return;*/									

			// mm 11.08
			if (_peseeParEcart)
			{
				// mm 10.08 - Sartorius ne sait pas gerer les consignes de tare
				// alors on part de 0 pour aller jusqu'à _poidsAPeser + _poidsTare
				if ((weighingInterface->getBalance()->getNoDriver() ==5))
				{
					_poidsAPeser += _poidsTare;
					getAffPoidsAPeser()->setValue(_poidsAPeser);
					bufferedDraw(getAffPoidsAPeser());
				}
			}
			
		}

	// pour ne pas pouvoir y acceder par le champs tactile
	//	getSaisiePoidsPese()->setEditable(false);
	// demande de poids stable
   		weighingInterface->setWeight(_poidsAPeser);
       	weighingInterface->setResNetWeight(_poidsPese);
	    weighingInterface->setTotWeight(_totalAPeserInitial);
	    weighingInterface->setTotResWeight(_poidsPese);

		order = POIDS_STAB_M;
		weighingInterface->setWeighingOrder(order);

		bool error;

		_poidsPese = getAffPoidsAPeser()->getFloatValue(error);

		
		weighingInterface->setWeight(_poidsPese);
		weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
		weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 2 getValid("<<weighingInterface->getValid()
				<<") getCancel("<<weighingInterface->getCancel()
				<<") setStopPesee("<<weighingInterface->getStopPesee()<<")"<< endl;
			getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 2 getResWeighingMessage("<<weighingInterface->getResWeighingMessage()
				<<") getWeighingStatus("<<weighingInterface->getWeighingStatus()<<")"<< endl;
		}

	//	_balanceChoisie->setUnite(weighingInterface->getResWeightUnit());

		if (weighingInterface->getResWeighingMessage() != NULL)
		{
			if (weighingInterface->getWeighingStatus() == OK_STA)
			{
				getmessage()->setLabel(formatMessage("&PeseeEffectuee         "));
				getvalider()->setSensitive(true);
				setFocus(getvalider());
				_peseeOK = true;
				if (getBoutonValidation() == 2){ boutonValiderPlus();}
			}
			else if (weighingInterface->getWeighingStatus() == CHG_PDS_UNIT)
			{
				char* message = new char[100];
				sprintf(message,"%s : %s",
						IlvGetMessage(getInterface()->getDisplay(),
						"&PeseeEffectuee         "),
						weighingInterface->getResWeighingMessage()); 
				getmessage()->setLabel(formatMessage(message));
				delete [] message;
				getvalider()->setSensitive(true);
				setFocus(getvalider());
				_peseeOK = true;
				if (getBoutonValidation() == 2) { boutonValiderPlus();}
			}
			else
			{
				getmessage()->setLabel(formatMessage(weighingInterface->getResWeighingMessage()));
				getpeser()->setSensitive(true);
			}
			bufferedDraw(getmessage());
		}
		else
		{
			getpeser()->setSensitive(true);
		}
	// pour retablir l'acces a la zone
	//	getSaisiePoidsPese()->setEditable(true);
	}
	else
// PESEE AVEC CONSIGNE
	{
		// llc 04.02 pour mettre la jauge dans le bon mode
//           adaptationEchelle();
		// pour les recipients fournisseur  on tare au poids à peser + poids théo de la tare
		// rq il n'existe pas de pesee cumulee en emb fournisseur
		if (_recipientChoisi->getTypeRecipient() == 2)
		{
			_poidsTare = m_data->convertir(
				_recipientChoisi->getTareTheo(), 
				_recipientChoisi->getUnitePoids(), 
				m_data->getCurrentComposant()->getUnite());
			getAffTare()->setValue(_poidsTare);
			bufferedDraw(getAffTare());
			_tarageOK = true;
	// envoie des info de tarage a la balance
			order = CONS_TAR_M;
			weighingInterface->setWeighingOrder(order);

			weighingInterface->setTare(_poidsAPeser + _poidsTare);
			weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
			weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

			weighingInterface->setPanneauAppelant(this);
			weighingInterface->weighingOrderTreatment();
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 3 getValid("<<weighingInterface->getValid()
					<<") getCancel("<<weighingInterface->getCancel()
					<<") setStopPesee("<<weighingInterface->getStopPesee()<<")"<< endl;
				getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 3 getResWeighingMessage("<<weighingInterface->getResWeighingMessage()
					<<") getWeighingStatus("<<weighingInterface->getWeighingStatus()<<")"<< endl;
			}
	
			getAffTare()->setValue(_poidsTare);
			bufferedDraw(getAffTare());
//			getSaisiePoidsPese()->setValue(- _poidsAPeser - _poidsTare);
// sr 20/04
			getSaisiePoidsPese()->setValue(- _totalAPeserInitial);
//			getSaisiePoidsPese()->setValue(- _poidsAPeser);
            bufferedDraw(getSaisiePoidsPese());
//			getJaugePesee()->setValue(- _poidsAPeser - _poidsTare);
// sr 16.04
//			getJaugePesee()->setValue(- _totalAPeserInitial);
//			bufferedDraw(getJaugePesee());
		}
		else
		{
// envoie des info de tarage a la balance
			order = CONS_TAR_M;
			weighingInterface->setWeighingOrder(order);
			
			if (!_peseeParEcart)
				weighingInterface->setTare(_poidsAPeser + _poidsTare + _poidsCumule);
			else
// llc 02.04 en emballage usine, le poids à peser ne doit pas inclure la tare 
// sr 11.02  remis comme avant pour tests
			weighingInterface->setTare(_poidsAPeser + _poidsTare);
//			weighingInterface->setTare(_poidsAPeser);
			weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
			weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

    		weighingInterface->setWeight(_poidsAPeser);
	    	weighingInterface->setResNetWeight(_poidsPese);
		    weighingInterface->setTotWeight(_totalAPeserInitial);
		    weighingInterface->setTotResWeight(_poidsPese);


			weighingInterface->setPanneauAppelant(this);
			weighingInterface->weighingOrderTreatment();
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 4 getValid("<<weighingInterface->getValid()
				<<") getCancel("<<weighingInterface->getCancel()
				<<") setStopPesee("<<weighingInterface->getStopPesee()<<")"<< endl;
			getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 4 getResWeighingMessage("<<weighingInterface->getResWeighingMessage()
				<<") getWeighingStatus("<<weighingInterface->getWeighingStatus()<<")"<< endl;
		}

			getSaisiePoidsPese()->setValue(_totalAPeserInitial);
			bufferedDraw(getSaisiePoidsPese());
// sr 16.04
//			getJaugePesee()->setValue(- _poidsAPeser);
//			bufferedDraw(getJaugePesee());
		}

	// demande de poids stable

		order = POIDS_STAB_M;
		weighingInterface->setWeighingOrder(order);

		bool error;

		_poidsPese = getAffPoidsAPeser()->getFloatValue(error);
		weighingInterface->setWeight(_poidsPese);

		weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
		weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 5 getValid("<<weighingInterface->getValid()
				<<") getCancel("<<weighingInterface->getCancel()
				<<") setStopPesee("<<weighingInterface->getStopPesee()<<")"<< endl;
			getInterface()->_traceFile << "AdxPesee_OF::peserCB After weighingOrderTreatment 5 getResWeighingMessage("<<weighingInterface->getResWeighingMessage()
				<<") getWeighingStatus("<<weighingInterface->getWeighingStatus()<<")"<< endl;
		}

		if (weighingInterface->getResWeighingMessage() != NULL)
		{
			if (weighingInterface->getWeighingStatus() == OK_STA)
			{
				getmessage()->setLabel(formatMessage("&PeseeEffectuee         "));
				getvalider()->setSensitive(true);
				setFocus(getvalider());
				_peseeOK = true;
				if (getBoutonValidation() == 2) { boutonValiderPlus();}
			}
			else if (weighingInterface->getWeighingStatus() == CHG_PDS_UNIT)
			{
				char* message = new char[100];
				sprintf(message,"%s : %s",
						IlvGetMessage(getInterface()->getDisplay(),
						"&PeseeEffectuee         "),
						weighingInterface->getResWeighingMessage()); 
				getmessage()->setLabel(formatMessage(message));
				delete [] message;
				getvalider()->setSensitive(true);
				setFocus(getvalider());
				_peseeOK = true;
				if(getBoutonValidation() == 2) { boutonValiderPlus();}
			}
			else
			{
				getmessage()->setLabel(formatMessage(weighingInterface->getResWeighingMessage()));
				getpeser()->setSensitive(true);
			}
			bufferedDraw(getmessage());
		}
		else
		{
			getpeser()->setSensitive(true);
		}
	}

	if(_peseeOK == true && weighingInterface->getValid() == true)
	{
		switch (getBoutonValidation())
		{
			case 1 :// on a cliqué sur le bouton valider pendant la pesée
					// comme on est maintenant sortie de la boucle il faut
					// rappeler le bouton valider pour acomplir son action
					_btV = true;
					validerCB(this->getvalider());
					break;
			case 2: if (getvaliderPlus()-> isSensitive() == true)
					{
					   // APCPRD-2787 mm 01.2013
					   _btVPlus = true;
					   validerPlusCB(this->getvaliderPlus());
					   break;
					}
		}		
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::validerCB(IlvGraphic* g)
{
	// mm - 06.09
	char* message = new char[100];
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	AdxData* m_data = getInterface()->getDonnees();
	this->setCursor(_display->getCursor("wait"));

	m_data->setX3Ver(11);		//NSH - temporary - for testing

	if (m_data->getX3Ver() == 11 && m_data->getUsrWei())											//X3-67237
	{						
		if ( ! (m_data->SendX3_CheckCredentials(true, true) ) )				//X3-67237
		{																	//X3-67237
//			getInterface()->getMessage()->setPanneauAppelant(NULL);			//X3-67237
//			getInterface()->envoieMessage("&UserPwd",false);				//X3-67237
			this->setCursor(_display->getCursor("default"));				//X3-67237

			return;															//X3-67237
		}																	//X3-67237
	}																		//X3-67237

	// 41440 mm 03.08 - bug en cas de redressement positif 
	_redressementPositif = false ;

	// 113445 mm 06.2016
	double _qtebesoinPrevue = 0.0;	
	double _qteAppTolerance = 0.0;
	
	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxPesee_OF::validerCB Enter _btV=("<<_btV<<")"<< endl;
	}
	if (_btV == false)
	{
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::validerCB direct exit! _btV=("<<_btV<<")"<< endl;
		}
		return;
	}

	// GBE 16/09/08 mise à vrai du flag
	if(weighingInterface->getBalance()->getTempo() == 0 && weighingInterface->getStopPesee() == false)
	{
		// pesée avec une balance connectée
		if (_balanceChoisie->getConnecte() == 1)
		{
			setBoutonValidation(1);
			_btV = false;
			// on positionne les flags et on sort
			// la fonction sera rappelée plustard par peserCB
			// et on ne repassera pas par ici
			// En fait ce bout de code permet simplement de mettre fin à la boucle
			// qui récupère le poids
			weighingInterface->setStopPesee(true);
			weighingInterface->setValid(true);
			// on a positionné le flag, on peut sortir car la fonction
			// sera apelée plus tard une fois la boucle terminée

			// ne pas remettre le cursor à default !!!
			//this->setCursor(_display->getCursor("default"));
			return;
		}
	}
	// gbe 10.08
	_enPesee = false;

	_recontroleFait  = false;
	_soldeEmballage  = false;
	_redressement    = false;
	_redressementFin = false;    
 	_redressementDesactive = false;    


	// mm 10.08 - Sartorius ne sait pas gerer les consignes de tare
	// alors on retranche _poidsTare du _poidsPese parce que pour le moment, ils sont additionnés
	if (_peseeParEcart && (weighingInterface->getBalance()->getNoDriver() ==5) 
		&& (_balanceChoisie->getConnecte() == 1)
		&&	(_recipientChoisi->getTypeRecipient() == 2))
	{
		_poidsPese		-= _poidsTare ;
		_poidsAPeser	-= _poidsTare;
	}

	if ((_peseeOK == false) | (_poidsPese <= 0))
    {
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::validerCB _peseeOK=("<<_peseeOK<<") _poidsPese=("<<_poidsPese<<")"<< endl;
		}
/*
    A réactiver plus tard mais soumis à un paramètre général 
    (peut-on redresser un emballage dans la centrale ou non)
    car l'Oréal n'en veut pas
    mais cela peut être interssant pour d'autres

        if (_poidsPese <= 0)
        {
            if (envoieMessage("&SoldeEmballage", true) == true)
            {

               	m_data->sendX3_MajEmballage(5);
            }
        }
        else
        { 
               	envoieMessage("&PeseeInvalide0", false);
        }
*/

       	envoieMessage("&PeseeInvalide0", false);

        _poidsPese = 0;
        _tarageOK  = false;
 
		getvalider()->setSensitive(false);
		setChampsAlphaEditable(true);
		if (_peseeParEcart == false)
		{
			getSaisieRecipient()->setEditable(false);
			getSaisieBalance()->setEditable(false);
		}
 		if (propositionLot())
		{
			afficherLot(m_data->getCurrentLot(), false);
            setFocus(getvalider());
			suiteChoixLot();
		}
		else
		{
			if (_stockReelInfInfo)
			{
				m_data->getCurrentLot()->setQuantiteAllouee(0);
					// le lot courant passe a NULL
				m_data->setCurrentLotIndex(m_data->getNbLots());
				afficherLot(m_data->getCurrentLot());
				// pour rendre accessible la modification et la sélection des lots 
				if (getInterface()->getFonctionEnCours() == 3
					&& getInterface()->getPeseeEnCuve())
				{
					getSaisieCuve()->setEditable(true);
					getSaisieVanne()->setEditable(true);
				}
				else
				{
					getSaisieLot()->setEditable(true);
					getSaisieSousLot()->setEditable(true); // mm
					getSaisieEmplacement()->setEditable(true);
				}
				attenteSaisieLot();
			}
			else
			{
				attenteSaisieLot();
			}
		}
		this->setCursor(_display->getCursor("default"));
        return;
    }

	// 06.07 mm - Differenciation des tolerances article +/-
	double toleranceArticlePositive = 0.0;
	double toleranceArticleNegative = 0.0;
	double toleranceBalance = 0.0;

	// mm 05.10 - % de tolérance article au niveau de la nomenclature
	if (m_data->getCurrentComposant()!= NULL)
	{
		toleranceArticlePositive = m_data->getCurrentComposant()->getToleranceArticlePositive();
		toleranceArticleNegative = m_data->getCurrentComposant()->getToleranceArticleNegative();
	}

	if (getBalanceChoisie() != NULL)
	{
		toleranceBalance = getBalanceChoisie()->getTolerance();
		if (toleranceArticlePositive == 0 && toleranceArticleNegative ==0)
		{
			toleranceArticlePositive = toleranceBalance ;
			toleranceArticleNegative = toleranceBalance ;
		}
	}
    // sr 10.04 maintenant les matières de rectifs sont gérées comme les autres mais pas
    // de notion de tolerance
    if ((m_data->getCurrentComposant()->getCodeAServir()==8)
    ||  (m_data->getCurrentComposant()->getCodeAServir()==9))
    {
		toleranceArticlePositive = 0.0 ;
		toleranceArticleNegative = 0.0;
    }
    double soldeEmb = 0.0;
   	if (_ficheISM != NULL)
	soldeEmb = _ficheISM->getSoldeEmballage(); 

	// sr 12.02 pour ne pas faire n'importe quoi
	getvalider()->setSensitive(false);

/// cas ou le poids a peser est determine par la balance NONTESTE
	if (_peseeLimiteeParBalance)
	{	
	// depassement de la portee de la balance
		if(_poidsPese > _poidsAPeser * (1 + toleranceBalance/100))
		{
		    // mm 02.2013 - enrichissement de la trace 
		    if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << " Dépassement portée de la balance" << endl;
			}
			envoieMessage("&PorteeBalanceDepassee", false);
			annulePesee();
			getpeser()->setSensitive(true);
			peserCB(getpeser());
			this->setCursor(_display->getCursor("default"));
			return;
		}
// pesee incomplete
// sr 05.02 Solde emballage y compris dans tolérance fiche incident n° 11
/* sr 06/05 on n'a plus besoin de tout cela
		if (_poidsPese  < _poidsAPeser)
		{
			if (_poidsPese < _poidsAPeser * (1 - tolerance/100))
			{
				if (envoieMessage("&PoidsPeseDifferentPoidsAPeser", true) == false)
				{
					annulePesee();
					getpeser()->setSensitive(true);
					peserCB(getpeser());
					return;
				}
			}
			if (m_data->getCurrentLot()->getQuantiteTotale()-m_data->getCurrentLot()->getQuantiteAllouee() <= 0)
			{
				if (envoieMessage("&SoldeEmballage", true) == true)
				{
					_soldeEmballage = true;
				}
			} 
		}
*/
        // mm 02.2013 - enrichissement de la trace
		if (getInterface()->getTraceMode() == 1)
		{
				getInterface()->_traceFile << " pesée limitée par balance balance" << endl;
		}

		// APCPRD 2074 - mm 11.12
		// Stockage du poids pesé total en unité physique (valeur idem à l'afficheur balance)
		_poidsPeseTotalPhysique =  	_poidsPeseTotalPhysique + _poidsPese;

        if (m_data->getCurrentComposant()->getGestionStock() != 3) 
    	{
	    	_poidsPeseTheo  = _poidsPese;
	    }
	    else
	    {
		    _poidsPeseTheo  = _poidsPese * m_data->getCurrentLot()->getTitre()
    			/ m_data->getCurrentComposant()->getTitreTheo();
	    }
        _poidsPeseTotal = _poidsPeseTotal + _poidsPeseTheo;
        envoiPeseePartielle();
		// 08.10 mm - pesée par matière
		if ( !m_data->getPseMatMatiereBegin()&&  getInterface()->getFonctionEnCours() == 2)
			m_data->setPseMatMatiereBegin(true);	

		// mm 06.09 - gestion déconditionnement/rompu
		// pour ne pas rester bloqué en consultation récipient
		setChampsAlphaEditable(true);
		if (_peseeParEcart == false)
		{
			getSaisieRecipient()->setEditable(false);
			getSaisieBalance()->setEditable(false);
		}

		_totalAPeser = m_data->getCurrentComposant()->getQuantiteTheorique();
		getAffTotalAPeser()->setValue(_totalAPeser);
		
        // les allocs ont changé côté X3 : on demande donc la ré-exctraction des lots
    	getInterface()->setPanneauAppelant(this);
		bool dataOK = m_data->ReloadAll();

		// controle Balance, calcule reste a peser et met a jour _peseeLimiteeParBalance
		_poidsAPeser = m_data->getCurrentLot()->getQuantiteAllouee();
		controleBalance(false);
		suiteChoixBalance();

		// rafraichissement de l'affichage des zones numeriques
		bufferedDraw(getAffTotalAPeser());
		_poidsPese = 0;
		getSaisiePoidsPese()->setValue(_poidsPese);
		bufferedDraw(getSaisiePoidsPese());
		getAffPoidsAPeser()->setValue(_poidsAPeser);
		bufferedDraw(getAffPoidsAPeser());
//		adaptationEchelle();
//		getJaugePesee()->setValue(_poidsPese);
//		bufferedDraw(getJaugePesee());
		if (_tarageOK == false)
			_poidsTare = 0;
		getAffTare()->setValue(_poidsTare);
		bufferedDraw(getAffTare());
		this->setCursor(_display->getCursor("default"));
		return;
	}
    

	// APCPRD 2074 - mm 11.12
   // incrémentation du poids total pesé total en unité physique 
	_poidsPeseTotalPhysique =  	_poidsPeseTotalPhysique + _poidsPese;

    if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile 
			<<"Poids pesé ("<< _poidsPese <<") " << "_poidsPeseTotalPhysique ("<<_poidsPeseTotalPhysique <<")" << endl;
	}
    //nouvelle méthode de validation de pesée spécifique redressement emballage sr 03.04
    // calcul de la quantité pesée si article titré ou non
    // quel est le poids pesé ?
	if (m_data->getCurrentComposant()->getGestionStock() != 3) 
	{
		_poidsPeseTheo  = _poidsPese;
	}
	else
	{
		_poidsPeseTheo  = _poidsPese * m_data->getCurrentLot()->getTitre()
			/ m_data->getCurrentComposant()->getTitreTheo();
	}
 

	// 111908 mm 01.2016 
	// autorisation de travailler avec des tolérances nulles seulement en cas de pesée mono-article
	if (getBoutonValidation() == 1)	
	{
		// 111908 mm 01.2016 -> pour les clients qui travaillent sans utiliser de tolérance
		if ( !toleranceArticlePositive && !toleranceArticleNegative )
		{
			// Si on est sur la dernière pesée (poids pesé supéreiur au poids total mini)
			// sr 10.04 maintenant les matières de rectifs sont gérées comme les autres
	   		if ((_poidsPeseTotal + _poidsPeseTheo) > ( _totalAPeserInitial )
			 &&  (m_data->getCurrentComposant()->getCodeAServir() < 10))
			{
				if (envoieMessage("&ConfirmationpeseeValide",true)== true)
				{ 
					validerPeseeFinale(toleranceArticleNegative,soldeEmb);
					envoiFinXxx();
					quitter();
				}
				else
				{
					annulePesee();	
					getpeser()->setSensitive(true);
					peserCB(getpeser());
					this->setCursor(_display->getCursor("default"));
				}
				return;	
			}
		}
	}

    // 113445 mm 06.2016
	if ( !m_data->getCurrentComposant()->getTitreTheo())
		_qtebesoinPrevue	= m_data->getCurrentComposant()->getQuantitePrevue();
	else
		_qtebesoinPrevue	= m_data->getCurrentComposant()->getQuantitePrevue()
							/ (m_data->getCurrentComposant()->getTitreTheo()/100);

	if (m_data ->getApplicationTolerance()== 1)
		_qteAppTolerance = _totalAPeserInitial;
	else
		_qteAppTolerance = _qtebesoinPrevue;

    // Si le poids total à peser est dépassé hors tolérance --> erreur sauf pour rectif et QSP  
    // 01.06 la comparaison des delta ne fonctionne pas sur des petites quantites
    // if ((((_poidsPeseTotal + _poidsPeseTheo) - _totalAPeserInitial) > _totalAPeserInitial * (tolerance/100))
    if (((_poidsPeseTotal + _poidsPeseTheo) >  _totalAPeserInitial + (_qteAppTolerance * toleranceArticlePositive/100))
		    &&  (m_data->getCurrentComposant()->getCodeAServir() < 8))
    {
		// 116324 mm 08.2016 - exceed tolerance+ is allowed
		if ( m_data->getExceedingTolerancePos()==2)
		{
			sprintf(message,"%s . %s ",
				IlvGetMessage(getInterface()->getDisplay(),"&ExcesPoidsMaxAutorise"),
				IlvGetMessage(getInterface()->getDisplay(),"&ConfirmationpeseeValide"));
			if (envoieMessage(message,true)== true)
			{
				setDepassementPoidsMax((_poidsPeseTotal + _poidsPeseTheo)-
					( _totalAPeserInitial + (_qteAppTolerance * toleranceArticlePositive/100)));
				validerPeseeFinale(toleranceArticleNegative,soldeEmb);
				envoiFinXxx();
				if (getBoutonValidation() == 1)		
					quitter();
			}
			else
			{
				annulePesee();	
				getpeser()->setSensitive(true);
				peserCB(getpeser());
				this->setCursor(_display->getCursor("default"));
			}
			delete [] message;
			return;	
		}
		else
		{
			envoieMessage("&PoidsPeseSuperieurPoidsAPeser", false);
			annulePesee();	
			getpeser()->setSensitive(true);
			peserCB(getpeser());
			this->setCursor(_display->getCursor("default"));
			return;	
		}
	}
    else
    {
        // incrémentation du poids total pesé
	    _poidsPeseTotal = _poidsPeseTotal + _poidsPeseTheo;

       // Si on est sur la dernière pesée (poids pesé supéreiur au poids total mini)
        // sr 10.04 maintenant les matières de rectifs sont gérées comme les autres
		//  113445 mm 06.2016
        //if ((_poidsPeseTotal >= (_totalAPeserInitial * (1 - toleranceArticleNegative/100)))
		if ((_poidsPeseTotal >= _totalAPeserInitial - (_qteAppTolerance * (toleranceArticleNegative/100)))
          &&  (m_data->getCurrentComposant()->getCodeAServir() < 10))
        {
			validerPeseeFinale(toleranceArticleNegative,soldeEmb);
        }
        // Si pesée intermédiaire  
        // voir si besoin de faire un redressement en moins après consommation (on n'a pas pris tout le dispo)
        // on ne peut pas le faire avant car la qté en trop est encore allouée
        // après la pesée, cette quantité ne sera plus allouée et on pourra la supprimer
        // sr 10.04 on ne redresse pas en - pour mat de rectif car on peut peser petit bout par petit bout
        // sr 02.05 si on a pesé moins que le disponible :
        // si quantité dose<> 0: si qté pesée  = qté dose alors OK, dans tous les autres cas 
        //(plus ou moins que la quantité dose) c'est le fonctionnement standard qui doit prendre la main
        // voir si besoin de gérer une tolérance pour la quantite dose
        else
        {
           if ((((m_data->getCurrentComposant()->getRedMod() == 1) & (_poidsPese <  m_data->getCurrentLot()->getQuantiteDisponible()))
            ||  ((m_data->getCurrentComposant()->getRedMod() == 2) & (_poidsPese <  m_data->getCurrentLot()->getQuantiteAllouee())))
               &&  (m_data->getCurrentComposant()->getCodeAServir() < 8))
		    {
			   // mm 02.2013 - enrichissement de la trace             	
			   if (getInterface()->getTraceMode() == 1)
			   {
				  getInterface()->_traceFile << "Pesée partielle matière"<< endl;
			   }
			   if  (m_data->getRedressementNegatif()==2)
			   {
				   if((m_data->getCurrentComposant()->getQuantiteDose() == 0)
					 || (_poidsPese != m_data->getCurrentComposant()->getQuantiteDose()))
				   {

					   // mm 06.09 -  Préparation du message + 03.10 - paramétrage redressement négatif
					  if (m_data->getCurrentComposant()->getRedMod() == 1) // redressement au lot
					  {
						  double _quantiteRedressee =  m_data->getCurrentLot()->getQuantiteDisponible() - _poidsPese ;
						  sprintf(message,"%s : %s = %6.3f  %s",
							  IlvGetMessage(getInterface()->getDisplay(),"&FindeContenant"),
							  IlvGetMessage(getInterface()->getDisplay(),"&QuantiteRedressee"),
							  _quantiteRedressee ,
							  m_data->getCurrentComposant()->getUnite());
					  }
					  else
					  {
						  if (m_data->getCurrentComposant()->getRedMod() == 2) // redressement à l'allocation
						  {
							 double _quantiteRedressee =  m_data->getCurrentLot()->getQuantiteAllouee() - _poidsPese ;
							 sprintf(message,"%s: %s = %6.3f  %s",
								 IlvGetMessage(getInterface()->getDisplay(),"&Redressement"),
								 IlvGetMessage(getInterface()->getDisplay(),"&QuantiteRedressee"),
								 _quantiteRedressee ,
								 m_data->getCurrentComposant()->getUnite());
						  }
					  }

					  // 113322 mm 02.2016
					  if (_ficheISM != NULL)
					  {
						 switch (_ficheISM->getRedressementManuel())
						 {	
							case 1 : // automatique     
									 // sr 12.04 Avertir l'utilisateur qu'un mouvement de redressement va être fait ?
									 if(getInterface()->getMsgMode() == 1)
									 {
										 envoieMessage(message ,false);
									 }
        							 _redressement = true;
									 break;
							case 2 : // manuel
                           			 if (envoieMessage(message, true) == true)
									 {	
        								 _redressement = true;
										 // mm 02.2013 - enrichissement de la trace             	
										if (getInterface()->getTraceMode() == 1)
										{
											getInterface()->_traceFile << "_redressement = true;"<< endl;
										}
									 }
									 else
									 {
										_redressementDesactive = true;
										// mm 02.2013 - enrichissement de la trace             	
										 if (getInterface()->getTraceMode() == 1)
										{
											  getInterface()->_traceFile << "_redressementDesactive= true;"<< endl;
										}
									 }
									 break;
                    		case 3 : // non   
									 _redressementDesactive = true;
									 break;
						  } 
					  }
				  }
			  }
			  else
			  {
					  // mm 11.10 - Redressement négatif = non. Inhiber message + mvt de redressement<0
					  _redressement = true;	
					  // mm 02.2013 - enrichissement de la trace             	
					  if (getInterface()->getTraceMode() == 1)
					  {
						  getInterface()->_traceFile
							  << "_redressement = true; // Inhiber message + mvt de redressement<0"<< endl;
					  }
			    }
            }
        }
	}	
	delete [] message;
	_poidsEncours=0;	
    // mise à jour de la base 
    // sr 10.04 maintenant les matières de rectifs sont gérées comme les autres
//    if (m_data->getCurrentComposant()->getCodeAServir() < 8)
    if (m_data->getCurrentComposant()->getCodeAServir() < 10)    
    {
	 // 113445 mm 06.2016
     // if((_poidsPeseTotal < _totalAPeserInitial * (1 - toleranceArticleNegative/100)))
	 if((_poidsPeseTotal < _totalAPeserInitial - (_qteAppTolerance * toleranceArticleNegative/100)))
     // la pesee est incomplete
	  {
			// 12.08 mm -  Réinitialiser le poidsTare en cas de pls pesées en emb. fournisseur avec tare modifiable 
			if (_recipientChoisi->getTypeRecipient()==2 && _recipientChoisi->getTareModifiable() ==2 
					&& _peseeParEcart && (_balanceChoisie->getConnecte() == 1))		
				_razTare = false;

          // sr si on n'a pas pesé tout ce qui restait mais pas de redressement on ne solde pas le lot
          // pour la gestion des doses et gestion redressement manuel
            if(((_poidsPese < m_data->getCurrentLot()->getQuantiteDisponible()) & (_redressement == false))
            ||(_redressementDesactive == true))
                envoiPeseePartielle();
            else
			    envoiFinLot();	
            getvalider()->setSensitive(false);
			setChampsAlphaEditable(true);
			// 08.10 mm - pesée par matière
			if ( !m_data->getPseMatMatiereBegin()&&  getInterface()->getFonctionEnCours() == 2)
				m_data->setPseMatMatiereBegin(true);	

			if (_peseeParEcart == false)
			{
				getSaisieRecipient()->setEditable(false);
				getSaisieBalance()->setEditable(false);
			}
			_totalAPeser = m_data->getCurrentComposant()->getQuantiteTheorique();
			// mm 06.09 - gestion déconditionnement/rompu
			getAffTotalAPeser()->setValue(_totalAPeser);

            // les allocs ont changé côté X3 : on demande donc la ré-exctraction des lots
    		getInterface()->setPanneauAppelant(this);
		    bool dataOK = m_data->ReloadAll();

			// en cas de redressement <0
			if (_redressement == true)
			{	
			
				// correction des quantités du lot courant
				if (m_data->getCurrentComposant()->getRedMod() == 1)	// redressement au lot
				{

					// mm 10.09 - correction des quantités du composant courant
					m_data->getCurrentComposant()->setQuantiteDisponible(
						m_data->getCurrentComposant()->getQuantiteDisponible() - m_data->getCurrentLot()->getQuantiteDisponible());
					m_data->getCurrentComposant()->setQuantiteAllouee(
						m_data->getCurrentComposant()->getQuantiteAllouee() - m_data->getCurrentLot()->getQuantiteAllouee());
					// correction des quantités du lot courant
	   				m_data->getCurrentLot()->setQuantiteDisponible(0);
					m_data->getCurrentLot()->setQuantiteTotale(0); 
					m_data->getCurrentLot()->setQuantiteAllouee(0);
				}
				else													// redressement à l'allocation
				{
					// mm 10.09 - correction des quantités du composant courant
					m_data->getCurrentComposant()->setQuantiteDisponible(
						m_data->getCurrentComposant()->getQuantiteDisponible() - m_data->getCurrentLot()->getQuantiteAllouee());
					m_data->getCurrentComposant()->setQuantiteAllouee(
						m_data->getCurrentComposant()->getQuantiteAllouee() - m_data->getCurrentLot()->getQuantiteAllouee());
					  // correction des quantités du lot courant
					m_data->getCurrentLot()->setQuantiteDisponible(
						m_data->getCurrentLot()->getQuantiteDisponible() - m_data->getCurrentLot()->getQuantiteAllouee());
					m_data->getCurrentLot()->setQuantiteTotale(
						m_data->getCurrentLot()->getQuantiteTotale() - m_data->getCurrentLot()->getQuantiteAllouee());
					m_data->getCurrentLot()->setQuantiteAllouee(0);
				}				
			}

			if (propositionLot())
			{
				afficherLot(m_data->getCurrentLot(), false);
                setFocus(getvalider());
				suiteChoixLot();
			}
			else
			{
				if (_stockReelInfInfo)
				{
//					m_data->getCurrentLot()->setQuantiteAllouee(0);
 					// le lot courant passe a NULL
					m_data->setCurrentLotIndex(m_data->getNbLots());
					afficherLot(m_data->getCurrentLot());
					// pour rendre accessible la modification et la sélection des lots 
					if (getInterface()->getFonctionEnCours() == 3
						&& getInterface()->getPeseeEnCuve())
					{
						getSaisieCuve()->setEditable(true);
						getSaisieVanne()->setEditable(true);
					}
					else
					{
						getSaisieLot()->setEditable(true);
						getSaisieSousLot()->setEditable(true); // mm
						getSaisieEmplacement()->setEditable(true);
					}
					attenteSaisieLot();
				}
				else
				{
					attenteSaisieLot();
				}
			}
			this->setCursor(_display->getCursor("default"));
			 // mm 02.2013 - enrichissement de la trace              	
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile << "Fin de pesée partielle. Sortie de AdxPesee_OF::validerCB()"<< endl;
			}
			return;
      }
	}
// fin de pesée
// correspond a une fin de phase ?
	if ( getInterface()->getFonctionEnCours() == 1 || getInterface()->getFonctionEnCours() == 3)
	{
  		if (m_data->getCurrentPhase()->getNbComposantsPeses() + 1
		>= m_data->getCurrentPhase()->getNbComposants())
		{
			if (m_data->getNbPhasesPesees() + 1 >= m_data->getNbPhases())

			{
	// impression document fin d OF 
				envoiFinOF();
			}
			else
	// impression document fin de phase
				envoiFinPhase();
		}
		else
	// impression document fin de composant
		{
			envoiFinComposant();
		}
	}
	else
	{
		// cas de la pesée par article : fin composant choisi systématiquement, 
		// on est peut-être en fin de phase ou d'OF, mais on a perdu le contexte en pesée par article
		envoiFinComposant_Art();		
		if ( !m_data->getPseMatMatiereBegin())
			m_data->setPseMatMatiereBegin(true);
	}

	if 	(_redressementPositif == true )
		m_data->sendX3_MajEmballage(3);

	this->setCursor(_display->getCursor("default"));


	 // mm 02.2013 - enrichissement de la trace              	
    if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "Fin de pesée complète. Sortie de AdxPesee_OF::validerCB()"<< endl;
	}

	// mm 08.11 -  on sort de l'écran de pesée seulement si on a appuyé sur le bouton Valider.
	// si on a appuyé sur Valider + , on ne sort pas de l'écran car on doit enchaîner sur la matière suivante.
	if (getBoutonValidation() == 1)		
		quitter();
}
//---------------------------------------------------------------------------
// 111908 mm 01.2016
//---------------------------------------------------------------------------
void  AdxPesee_OF::validerPeseeFinale(double toleranceArticleNegative,double soldeEmb)
{
  AdxData* m_data = getInterface()->getDonnees();
  char* message = new char[80];


 // mm 02.2013 - enrichissement de la trace             	
 if (getInterface()->getTraceMode() == 1)
 {
	getInterface()->_traceFile << "Pesée complète matière"<< endl;
 }
// emballage interne
 if( _recipientChoisi->getTypeRecipient() == 1) 
 {
   //  Proposition solde emballage  si :
   //  La quantité totale est égale au disponible (donc pas allouée ailleurs)
   //  et, après cette pesée, sera inférieure ou égale 
   //  à qté initiale * %solde emballage
   // cette quantité restante peut être égale à 0 : on pose la question quand même
	if ((m_data->getCurrentLot()->getQuantiteTotale() == m_data->getCurrentLot()->getQuantiteDisponible()) 
    &&  (m_data->getCurrentLot()->getQuantiteTotale() - _poidsPese <= m_data->getCurrentLot()->getQuantiteInitiale() * (soldeEmb/ 100)))
	{
      if (envoieMessage("&SoldeEmballage", true) == true)
      // on répond oui au solde emballage
      {
		// si la qté restante est <> 0 on solde
        if (m_data->getCurrentLot()->getQuantiteTotale() - _poidsPese > 0)
    		_soldeEmballage = true;
			// mm 02.2013 - enrichissement de la trace             	
			if (getInterface()->getTraceMode() == 1)
			{
				getInterface()->_traceFile <<"_soldeEmballage = true"<< endl;
			}
       }
       else
        // on répond non au solde emballage
       {                        
			// si qté restante <= 0 on fait un redressement positif
			if (m_data->getCurrentLot()->getQuantiteTotale() - _poidsPese <= 0)
				_redressementPositif = true ;
				// mm 02.2013 - enrichissement de la trace             	
				if (getInterface()->getTraceMode() == 1)
				{
					getInterface()->_traceFile <<"_redressementPositif = true"<< endl;
				}
			}
		}
	}
    // emballage fournisseur
    else
     {
		// si pesée inférieure au poids à peser
        // redressement négatif pour le delta entre poids à peser et poids pesé
		if ((_poidsPese < _poidsAPeser))
		{
			if (m_data->getRedressementNegatif()==2)
			{
				// sr 12.04 Avertir l'utilisateur qu'un mouvement de redressement va être fait ?
				if (getInterface()->getMsgMode() == 1)
				{
					double _quantiteRedressee = _poidsAPeser - _poidsPese ;
					// mm 03.10 - paramétrage redressement négatif
					sprintf(message,"%s : %s = %6.3f  %s",
					IlvGetMessage(getInterface()->getDisplay(),"&FindeContenant"),
					IlvGetMessage(getInterface()->getDisplay(),"&QuantiteRedressee"),
					_quantiteRedressee,
					m_data->getCurrentComposant()->getUnite());
					getInterface()->envoieMessage(message,false);
				}
				_redressementFin = true;
			 }
			 else
				_redressementFin = true;
		  }
    }  
  	delete [] message;
}
//---------------------------------------------------------------------------
// 116324 mm 08.2016
//---------------------------------------------------------------------------
void  AdxPesee_OF::envoiFinXxx()
{
     AdxData* m_data = getInterface()->getDonnees();
  	// fin de pesée -> correspond a une fin de phase ?
	if ( getInterface()->getFonctionEnCours() == 1 || getInterface()->getFonctionEnCours() == 3)
	{
		if (m_data->getCurrentPhase()->getNbComposantsPeses() + 1
			>= m_data->getCurrentPhase()->getNbComposants())
		{
			if (m_data->getNbPhasesPesees() + 1 >= m_data->getNbPhases())
				// impression document fin d OF 
				envoiFinOF();
			else
				// impression document fin de phase
				envoiFinPhase();
		}
		else
			// impression document fin de composant
			envoiFinComposant();
	}
	else
	{
		// cas de la pesée par article : fin composant choisi systématiquement, 
		// on est peut-être en fin de phase ou d'OF, mais on a perdu le contexte en pesée par article
		envoiFinComposant_Art();		
		if ( !m_data->getPseMatMatiereBegin())
			m_data->setPseMatMatiereBegin(true);
	}
}

//---------------------------------------------------------------------------
void  AdxPesee_OF::boutonValiderPlus()
{
    AdxData* m_data = getInterface()->getDonnees();

	if (getvalider()->isSensitive() == true)
	{
	   getvaliderPlus()->setSensitive(false);
	   // activation du bouton Valider+ seulement si la matière en cours de pesée a le flag "Pesée multi-article" à oui
	   // et s'il existe une autre matière cumulable dans la phase ( la suivante ou une plus loin)
	   if ((m_data->getCurrentFicheISM()->getPeseeMultiArticle() == 2 )
			&& ( m_data->getCurrentFicheISM()->getCodeEmballage() == 3 ||	 //emb mixte
			 m_data->getCurrentFicheISM()->getCodeEmballage() == 1 )		 //emb interne
			&& (_peseeParEcart == false )									 //pesée cumulée
			&& ( _peseeCumuleeForcee == false))
	   {
		   int _index = m_data->getCurrentComposantIndex();
		   IlList*	composantList 	= m_data->getCurrentPhase()->getComposantList();
		   int j = 1 ;
		   // il reste des composants à peser dans la phase 
		   if  ( j + _index < m_data->getCurrentPhase()->getNbComposants())
		   {
			// Bt valider+ doit être actif 
			getvaliderPlus()->setSensitive(true);
			// On doit garder le même indice entre currentcomposant et composantsuivantmulti
				 // on est en pesée finale du composant courant : recherche du composant suivant
				if ( getPoidsDejaPese() >= getWeightMin())	
				{
				   while (j + _index < m_data->getCurrentPhase()->getNbComposants())
				   {
   						 _composantSuivant =   (AdxComposant*)(*composantList)[_index +j] ;
						// on ne retient que les composants pas totalement pesés et dont le PKC = 2 
						if  ((!_composantSuivant->getTotalementPese()) && (_composantSuivant->getCodeAServir() == 2))
						{
							for (long i = 0; i <  m_data->getNbFichesISM(); i++) 
							{
								_ficheISM = (AdxFicheISM*)(*m_data->getFicheISMList())[i];
								if (strcmp(_ficheISM->getFicheISM(),_composantSuivant->getFicheISM())==0)
								{
									if (_ficheISM->getPeseeMultiArticle() == 2)
									{
										// sauvegarde du prochain composant pouvant faire l'objet d'une pesée cumulée
										setIndexComposantSuivantMulti(_index+j);
										char* message = new char[LengthMaxMessage];
										sprintf(message,"%s ",IlvGetMessage(getInterface()->getDisplay(), 
											"&BoutonValiderPlus")); 
										getmessage()->setLabel(formatMessage(message));
										bufferedDraw(getmessage());
										delete [] message;
										setFocus(getvaliderPlus());
										// mm 02.2013 - enrichissement de la trace 
										if (getInterface()->getTraceMode() == 1)
										{
											getInterface()->_traceFile << "AdxWPesee_OF::boutonValiderPlus() : Prochain composant trouvé"<< endl;
										}
										return;
									}
								}
							}
						}
						j ++;
					  }
				      // sr 12.11 APCPRD-732 Pas trouve de composant : y a t il des excipients fin de phase ?
					  j = 1;
					  while (j + _index < m_data->getCurrentPhase()->getNbComposants())
				      {
						_composantSuivant =   (AdxComposant*)(*composantList)[_index +j] ;
						// on ne retient que les composants pas totalement pesés et dont le PKC = 4 
						if  ((!_composantSuivant->getTotalementPese()) && (_composantSuivant->getCodeAServir() == 4))
						{
							for (long i = 0; i <  m_data->getNbFichesISM(); i++) 
							{
								_ficheISM = (AdxFicheISM*)(*m_data->getFicheISMList())[i];
								if (strcmp(_ficheISM->getFicheISM(),_composantSuivant->getFicheISM())==0)
								{
									if (_ficheISM->getPeseeMultiArticle() == 2)
									{
										// sauvegarde du prochain composant pouvant faire l'objet d'une pesée cumulée
										setIndexComposantSuivantMulti(_index+j);
										char* message = new char[LengthMaxMessage];
										sprintf(message,"%s ",IlvGetMessage(getInterface()->getDisplay(), 
											"&BoutonValiderPlus")); 
										getmessage()->setLabel(formatMessage(message));
										bufferedDraw(getmessage());
										delete [] message;
										setFocus(getvaliderPlus());
										// mm 02.2013 - enrichissement de la trace 
										if (getInterface()->getTraceMode() == 1)
										{
											getInterface()->_traceFile << "AdxWPesee_OF::boutonValiderPlus() : Excipient de fin de phase trouvé"<< endl;
										}
										return;
									}
								}
							}
						}
						j++;
					  }
			     }
				 //on n'a pas trouvé de composant suivant pouvant faire l'objet d'une pesée
				 // cumulée multi-article : validation std du composant en cours de pesée
				 setBoutonValidation(1);
				 if (! _balanceChoisie->getConnecte())
				 {
					 getvaliderPlus()->setSensitive(false); 
					// mm 02.2013 - enrichissement de la trace 
					if (getInterface()->getTraceMode() == 1)
					{
						getInterface()->_traceFile 
						<< "AdxWPesee_OF::boutonValiderPlus() : mode dégradé, Pas de nv composant trouvé->V "<< endl;
					}
				 }
				 //sr 02.12 APCPRD-723 si balance connectée envoyer un message d'avertissement
				 else
				 {
					// mm 02.2013 - enrichissement de la trace 
					if (getInterface()->getTraceMode() == 1)
				    {
						getInterface()->_traceFile 
							<< "AdxWPesee_OF::boutonValiderPlus() : mode connecté, Pas de nv composant trouvé->V "<< endl;
					}
	 		   		char* message = new char[LengthMaxMessage];
					sprintf(message," %s ",
					IlvGetMessage(getInterface()->getDisplay(),"&PeseeMultiArticleImpossible2"));
					getInterface()->envoieMessage(message,false);	
					delete [] message;
				 }
		   }

		   else if  (j + _index == m_data->getCurrentPhase()->getNbComposants())
		   {
			   // mm 02.2013 - enrichissement de la trace 
				if (getInterface()->getTraceMode() == 1)
			    {
					getInterface()->_traceFile 
						<< "AdxWPesee_OF::boutonValiderPlus(): pesée finale du dernier composant de la phase "<< endl;
				}
			    // Pesée finale du dernier composant de la phase
				setBoutonValidation(1);
		 		if (! _balanceChoisie->getConnecte())
					 getvaliderPlus()->setSensitive(false); 
		   } 
	   }
	   else
	   {
		  // mm 02.2013 - enrichissement de la trace 
		  if (getInterface()->getTraceMode() == 1)
		  {
					getInterface()->_traceFile 
						<< "AdxWPesee_OF::boutonValiderPlus():pesée multi-article impossible dans ce contexte "<< endl;
		  }
		   // envoyer un message d'explication :pesée multi-article impossible dans ce contexte 
		   // sr 01.12 APCPRD-723: on ne vient plus là en mode connecté 
		   // et en mode déconnecté, le message ne sert à rien car le bouton n'est pas activé et c'est tout
		   setBoutonValidation(1);
		   getvaliderPlus()->setSensitive(false); 

	   }
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::validerPlusCB(IlvGraphic* g)
{
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	AdxChoix_OF* m_choix_OF = getInterface()->getChoix_OF();
	AdxData* m_data = getInterface()->getDonnees();
	this->setCursor(_display->getCursor("wait"));


	if (getInterface()->getTraceMode() == 1)
	{
		getInterface()->_traceFile << "AdxPesee_OF::validerPlusCB Enter _btVPlus=("<<_btVPlus<<")"<< endl;
	}
	// APCPRD-2787 mm 01.2013
	// GBE 31/01/13 Au début de la fonction c'est mieux
	if (_btVPlus == false)
	{
		if (getInterface()->getTraceMode() == 1)
		{
			getInterface()->_traceFile << "AdxPesee_OF::validerPlusCB direct exit! _btVPlus=("<<_btVPlus<<")"<< endl;
		}
		return;
	}


	//sr 12.11 APCPRD-729
	WeighingOrder order;
	getmettreAZero()->setSensitive(false);
	gettarer()->setSensitive(false);
	// sr 12.11 APCPRD-732
	AdxComposant* composantPourCalcul;
	IlList* composantList = m_data->getCurrentPhase()->getComposantList();
	double quantiteCalcul;

	// GBE 16/09/08 mise à vrai du flag
	if(weighingInterface->getBalance()->getTempo() == 0 && weighingInterface->getStopPesee() == false)
	{
		// pesée avec une balance connectée
		if (_balanceChoisie->getConnecte() == 1)
		{	
			setBoutonValidation(2);
			// APCPRD-2787 mm 01.2013
			//getvaliderPlus()->setSensitive(false);
			// GBE 31/01/13 Il faut faire cette action AVANT la mise à jour des flags 
			_btVPlus = false;
			// on positionne les flags et on sort
			// la fonction sera rappelée plus tard par peserCB
			weighingInterface->setStopPesee(true);
			weighingInterface->setValid(true);
			return;
		}
		else
		{
			setBoutonValidation(2);
			// APCPRD-2787 mm 01.2013 - Pour être homogène avec le mode connecté
			//getvaliderPlus()->setSensitive(false);
			_btVPlus = false;
		}
	}

	//	sr 03.12 APCPRD-729
	if (_balanceChoisie->getConnecte()==1)
	{
		order = CLAV_BAL_LOCK;
		weighingInterface->setWeighingOrder(order);
		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();
	}

	// envoyer un message : Pesée multi-article oui/non ?
	char* message = new char[LengthMaxMessage];
	sprintf(message," %s ", IlvGetMessage(getInterface()->getDisplay(), "&Peseemultiarticle" ));
	// si on répond non, retour à l'écran de pesée sans validation
	if (envoieMessage(message, true) == false)
	{
		for (int i=0 ; i<strlen(message+1); i++)
		{
			message[i] =' ';
		}
		sprintf(message,"%s ", IlvGetMessage(getInterface()->getDisplay(), "&PeseeEffectueePlus")); 
		getmessage()->setLabel(formatMessage(message));
		bufferedDraw(getmessage());
		setBoutonValidation(1);
		delete [] message;	
		this->setCursor(_display->getCursor("default"));
		return;
	}

	_enPeseeMultiArticle = true;	
	delete [] message;	

	// sauvegarde du contexte	
	if (! weighingInterface->getMatiere1Pesee())
	{	
	    weighingInterface-> setMatiere1Pesee(true) ;	
		// Sauvegarde du récipient choisi
		_recipientMulti = new AdxRecipient;
		_recipientMulti->setRecipient( _recipientChoisi->getRecipient());
		_recipientMulti->setLibRecipient( _recipientChoisi->getLibRecipient());
		_recipientMulti->setUnitePoids( _recipientChoisi->getUnitePoids());
		_recipientMulti->setPoidsMaxi( _recipientChoisi->getPoidsMaxi());
		_recipientMulti->setTypeRecipient( _recipientChoisi->getTypeRecipient());
		_recipientMulti->setLibTypeRecipient( _recipientChoisi->getLibTypeRecipient());
		_recipientMulti->setTareTheo( _recipientChoisi->getTareTheo());
		_recipientMulti->setTareTheoSvg(  _recipientChoisi->getTareTheo());
		_recipientMulti->setTolerance(  _recipientChoisi->getTolerance());
		_recipientMulti->setGuideOperateur(  _recipientChoisi->getGuideOperateur());
		_recipientMulti->setFormatEtiquette(  _recipientChoisi->getFormatEtiquette());
		_recipientMulti->setTareModifiable(  _recipientChoisi->getTareModifiable());
		_recipientMulti->setSaisiePoids( _recipientChoisi->getSaisiePoids());
		// sauvegarde de la balance chosie
		_balanceMulti	    	= _balanceChoisie;
		// sauvegarde de l'UP de la première matière pesée exclusivement : pour conversion 
		// éventuelle de quantité , si autres matières ont une UP différente 
		setUnitePoidsMat1( m_data->getCurrentComposant()->getUnite());
		setMat1( m_data->getCurrentComposant()->getComposant());
	}

	// 2 Cumuls de poids distincts : 
	// _poidsMatDejaPese = somme des quantités des matières totalement pesées
	// _poidsPeseMatEncours = somme des sous_lot pesés de la matière en cours		
	// Pour rappel, _poidsCumuleMulti : valeur = à celle affichée sur la balance ( à l'unité près )
	// _poidsTareMulti : poids de la tare du récipient.
	// => ces poids sont sauvegardés dans l'UP mat1 
	if ( strcmp (m_data->getCurrentComposant()->getUnite() ,getUnitePoidsMat1()) != 0) 
	{
		if (m_data->getCurrentComposantIndex() != getIndexComposantSuivantMulti())
		{
			_poidsMatDejaPese   = m_data->convertir(_poidsCumuleMulti,
				 m_data->getCurrentComposant()->getUnite(),getUnitePoidsMat1());

		}
		_poidsCumuleMulti =  m_data->convertir(_poidsCumuleMulti,
				 m_data->getCurrentComposant()->getUnite(), getUnitePoidsMat1());
		_poidsPeseMatEncours = _poidsCumuleMulti - _poidsMatDejaPese;
		_poidsTareMulti  =  m_data->convertir( _poidsTare,
				 m_data->getCurrentComposant()->getUnite(), getUnitePoidsMat1());
	}
	else
	{
		if (m_data->getCurrentComposantIndex() != getIndexComposantSuivantMulti())
			_poidsMatDejaPese   = _poidsCumuleMulti; 
		_poidsPeseMatEncours = _poidsCumuleMulti - _poidsMatDejaPese;
		_poidsTareMulti  = _poidsTare;
	}

	// Valider+ : c'est une validation classique avec sauvegarde du contexte en +.
	validerCB(g);
	// récupération du nouveau composant 
	//On devrait avoir le même index si pesée intermédiaire du Xieme composant
	if (m_data->getCurrentComposantIndex() != getIndexComposantSuivantMulti())
	{
		m_data->setCurrentComposantIndex(getIndexComposantSuivantMulti());
		AdxComposant* composant = m_data->getCurrentComposant();
		// calcul de la quantité théorique 
		// sr 12.11 APCPRD-732
		// on ne cumule que des articles de PKC = 2 ou 4
		if (composant->getCodeAServir() ==4)
		{
			composant->setQuantiteTheorique(composant->getQuantiteRestante());
			// sr 12.11 APCPRD-732
			bool okForExp = true ;
			//toutes les matières titrées ont-elles été pesées ?
			for (int k = 0; k < m_data->getCurrentPhase()->getNbComposants(); k++) 
			{
				AdxComposant* _composantControle = (AdxComposant*)(*composantList)[k];
				if (_composantControle->getCodeAServir() < 4				// doivent etre peses avant
				&& _composantControle->getGestionStock() == 3		// composant a titre
				&& _composantControle->getTotalementPese() == false)	// non pese
				{
					okForExp = false;
					break;
				}
			}
			if (okForExp == false) 
			{							
				quitter();
				this->setCursor(_display->getCursor("default"));
				return; 
			}
			for (int i = 0; i < m_data->getCurrentPhase()->getNbComposants(); i++) 
			{
				composantPourCalcul = (AdxComposant*)(*composantList)[i];
				if (composantPourCalcul->getCodeAServir() < 4				// doivent etre peses avant
					&& composantPourCalcul->getGestionStock() == 3			// composant a titre
					&& composantPourCalcul->getTotalementPese() == true)	//  pese
				{
					quantiteCalcul = (composantPourCalcul->getQuantitePrevue() 
										/ composantPourCalcul->getTitreTheo() * 100)
										- composantPourCalcul->getQuantiteConsommee();
					composant->setQuantiteTheorique(composant->getQuantiteTheorique() 
										+ m_data->convertir(quantiteCalcul,
															composantPourCalcul->getUnite(),
															composant->getUnite()));
				}
			}
			if ( composant->getQuantiteAllouee())
			{
				composant->setQuantiteAlloueeTheorique(composant->getQuantiteAllouee());
				composant->setQuantiteAlloueeRestante(composant->getQuantiteTheorique());
			}
			if (composant->getQuantiteTheorique() <= 0)
			{
		 		m_choix_OF->validationPeseeAutomatique();
				envoieMessage("&SoldeAutomatiqueExcipient", false);
				quitter();
				this->setCursor(_display->getCursor("default"));
			return;
			}
		}
		else if (composant->getCodeAServir() == 2) 
		{
			if (composant->getGestionStock() == 3			// composant a titre
					&& composant->getTitreTheo() != 0)
			{
				composant->setQuantiteTheorique(
					composant->getQuantiteRestante() / composant->getTitreTheo() * 100);
			}
			else											// composant sans titre
				composant->setQuantiteTheorique(composant->getQuantiteRestante());
		}
	}

	// alimentation de _poidsCumuleMulti et _poidsCumuleCible
	// Ces poids doivent être convertis dans l'UP  de la matière en cours si elle est différente de l'UP de Mat1.
	double	_poidsMatDejaPeseUP2 = 0.0 ;
	double	_poidsPeseMatEncoursUP2 = 0.0 ;
    if ( strcmp (m_data->getCurrentComposant()->getUnite(), getUnitePoidsMat1()) !=0)

	{
		_poidsMatDejaPeseUP2 = m_data->convertir( getPoidsMatDejaPese(),
			getUnitePoidsMat1() ,m_data->getCurrentComposant()->getUnite());
		_poidsPeseMatEncoursUP2  = m_data->convertir( getPoidsPeseMatEncours(),
			getUnitePoidsMat1(),m_data->getCurrentComposant()->getUnite());
	}
	else
	{
		_poidsMatDejaPeseUP2 = _poidsMatDejaPese;
		_poidsPeseMatEncoursUP2 = _poidsPeseMatEncours;
	}
	_poidsCumuleCible =  m_data->getCurrentComposant()->getQuantiteTheorique() 
						 + _poidsMatDejaPeseUP2 + _poidsPeseMatEncoursUP2 ; 
	_poidsCumuleMulti = _poidsMatDejaPeseUP2 + _poidsPeseMatEncoursUP2 ;
	getAffPoidsCumuleCible()->setValue(_poidsCumuleCible);
	getAffPoidsCumule()->setValue(_poidsCumuleMulti);
	bufferedDraw(getAffPoidsCumuleCible());	
	bufferedDraw(getAffPoidsCumule());	
	// SR 12.11 APCPRD-724 
	_modifAllocations = false;
	// pesée nouvelle matière pas commencée
	if  ( m_data->getComposantBegin()== false)
	{
		// SR 03.12 APCPRD-988 : si erreur on sort de l'écran de pesée 
		m_data->setOkToContinue(true);
		// SR 04.12 APCPRD-986 : Renseigner la quantité à peser et la quantité allouée
		m_choix_OF->getAffQuantiteAPeser()->setValue(m_data->getCurrentComposant()->getQuantiteTheorique());	
		m_choix_OF->getAffQuantite()->setValue(m_data->getCurrentComposant()->getQuantiteAlloueeTheorique());	
		m_choix_OF->ValidationCB(g);
		if(m_data->getOkToContinue() == false)
		{
			quitter();
			this->setCursor(_display->getCursor("default"));
			return;
		}
		// SR 12.11 APCPRD-724 
		if( m_data->getPrioriteAllocationCode() != 1
		|| m_data->getCurrentComposant()->getQuantiteAlloueeDpOF()==0 
		|| m_data->getCurrentComposant()->getQuantiteAlloueeRestante()==0)
		{
			_modifAllocations = true;
		}
	}

	//sr 12.11 APCPRD-728
	getSaisieRecipient()->setEditable(false);
	getSaisieBalance()->setEditable(false);
	if (_lotOK != false)
		suiteChoixLotMulti();
	else
	{
		attenteSaisieLot();
		this->setCursor(_display->getCursor("default"));
		return;
	}
	this->setCursor(_display->getCursor("default"));
}
//---------------------------------------------------------------------------
void AdxPesee_OF::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::quitterCB(IlvGraphic* g)
{

	_recontroleFait = false;
	// gbe 10.08
	_enPesee = false;

 	// GBE 16/09/08 mise à vrai du flag
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	weighingInterface->setCancel(true);

    quitter();
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::initClavier_Tactile()
{
	bool retour = false;
	AdxClavier_Tactile* tactile = getInterface()->getClavier_Tactile();
	tactile->setPanneauAppelant(this);
// 8 appels possibles du clavier dans Pesee_OF
	if (_balanceChoisie != NULL)
	{
		if (_champAppelant == getSaisiePoidsPese()
			&& _attenteTarage == true
			&& !affecteBalance())
		{
			tactile->setSaisie("");
			tactile->setAlpha(IlvFalse);
			CString string(IlvGetMessage(getDisplay(), "&Saisir"));
			string += " ";
			string += IlvGetMessage(getDisplay(),"&Tare1");
			tactile->getchampMessage()->setLabel(string);
			retour = true;
		}

		if (_champAppelant == getSaisiePoidsPese()
			&& _attentePesee == true
			&& !affecteBalance())
		{
			tactile->setSaisie("");
			tactile->setAlpha(IlvFalse);
			CString string(IlvGetMessage(getDisplay(), "&Saisir"));
			string += " ";
			string += IlvGetMessage(getDisplay(),"&PoidsPese1");
			tactile->getchampMessage()->setLabel(string);
			retour = true;
		}
	}
	if (_champAppelant == (IlvTextField*)getSaisieLot())
	{
		tactile->setSaisie(getSaisieLot()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Lot1");
		tactile->getchampMessage()->setLabel(string);
		retour = true;
	}

	// mm 05.10 - Distinction lot/sous-lot
		if (_champAppelant == (IlvTextField*)getSaisieSousLot())
	{
		tactile->setSaisie(getSaisieLot()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&SousLot1");
		tactile->getchampMessage()->setLabel(string);
		retour = true;
	}

	if (_champAppelant == (IlvTextField*)getSaisieEmplacement())
	{
		tactile->setSaisie(getSaisieEmplacement()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Emplacement1");
		tactile->getchampMessage()->setLabel(string);
		retour = true;
	}

	if (_champAppelant == (IlvTextField*)getSaisieCuve())
	{
		tactile->setSaisie(getSaisieCuve()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Cuve1");
		tactile->getchampMessage()->setLabel(string);
		retour = true;
	}

	if (_champAppelant == (IlvTextField*)getSaisieVanne())
	{
		tactile->setSaisie(getSaisieVanne()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Vanne1");
		tactile->getchampMessage()->setLabel(string);
		retour = true;
	}

	if (_champAppelant == (IlvTextField*)getSaisieRecipient())
	{
		tactile->setSaisie(getSaisieRecipient()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Recipient1");
		tactile->getchampMessage()->setLabel(string);			
		retour = true;
	}

	if (_champAppelant == (IlvTextField*)getSaisieBalance())
	{
		tactile->setSaisie(getSaisieBalance()->getLabel());
		tactile->setAlpha(IlvTrue);
		CString string(IlvGetMessage(getDisplay(), "&Saisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Balance1");
		tactile->getchampMessage()->setLabel(string);
		retour = true;
	}

	tactile->getchampSaisie()->setLabel(tactile->getSaisie());
	tactile->reDrawObj(tactile->getchampSaisie());
	return retour;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::quitter()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	AdxPesee_OF* m_Pesee_OF = m_interface->getPesee_OF();
	AdxChoix_OF* m_choix_OF = m_interface->getChoix_OF();
	AdxWeighingInterface* weighingInterface =  m_interface->getWeighingInterface();
	// SR 03.12 APCPRD-729
	WeighingOrder order;

	// sr 12.02 pour ne pas faire n'importe quoi
	getquitter()->setSensitive(false);

	// mm 09.11 - Pesée multi-article
	setBoutonValidation(1);
	if ( _enPeseeMultiArticle == true)
	{
		delete _recipientMulti;
		_recipientMulti = NULL;
		_balanceMulti = NULL;
	    weighingInterface-> setMatiere1Pesee(false) ;
		if ( !m_data->getComposantBegin())
			_enPeseeMultiArticle = false;
	}

	if (m_data->getComposantBegin())
	{
// ici on controle que la pesee du composant est finie
/*		double tolerance = 0.0;
		if (_ficheISM != NULL)
			tolerance = _ficheISM->getToleranceArticle();
		if (tolerance == 0)
		tolerance = getBalanceChoisie()->getTolerance();

		if (m_data->getCurrentComposant()->getQuantiteAllouee()
			> m_data->getCurrentComposant()->getQuantitePrevue() * tolerance/100)
// pesee partielle		
		{*/
			if (m_data->getPeseePartielleCode() == 1)	// mm 09.07
			{
				envoieMessage("&PeseePartielleInterdite",false);
				getquitter()->setSensitive(true);
				return;
			}
			else
			{
				// mm 09.11 - pesée cumulé multi-article en contexte pesée partielle de la matière cumulée
				if (_enPeseeMultiArticle == true)
				{
					_enPeseeMultiArticle = false;
					m_interface->getChoix_OF()->interruptionComposant();
				}
				else
				{
					if (envoieMessage("&PeseePartielleComposant?",true))
					{
						// envoie fin composant mais pas fin pesee composant
						m_interface->getChoix_OF()->interruptionComposant();
					}
					else
					{
						getquitter()->setSensitive(true);
						if (propositionLot())
							suiteChoixLot();
						else
							attenteSaisieLot();
						return;
					}
				}
// si non on revient au choix lot:  return
// si oui on continue les controles
			}
//		}
	}
	else
	{
		// mm 10.10 - Pesée par article
		if (getInterface()->getFonctionEnCours() == 2) 
		{
			// article alloué, non pesé
			if (m_data->getComposantAlloue())
				m_choix_OF->interruptionComposant();
			else
			{
				// article totalement pesé
				m_data->setPhaseBegin(false);
				m_data->SendX3_InterruptionOF();
				m_data->setOrderBegin(false);
			}
		}
	}

	// mm 10.10 - Pesée par article, article totalement pesé
	if ((getInterface()->getFonctionEnCours() == 2) && (m_data->getCurrentComposant()->getTotalementPese()))
	{
		// réinitialisation des zones de l'écran
		m_choix_OF->chargementZonesAVide();
		//on vide la liste des fiches ISM, celle des OFs et celle des phases.
		m_data->razListeFicheISM();							
		m_data->razListeOF();																			
		m_data->razListePhase();		
      	// 90456 mm 06.2013 - Ne vider la liste des composants que dans le cas
		// où on recharge le .csv à ch. fois
		if (m_data->getChargementListMat() == 2)
			m_data->razListeComposant(); 
	}
	//	sr 03.12 APCPRD-729
	if (_balanceChoisie != NULL)
	{
		if (_balanceChoisie->getConnecte()==1)
		{
			order = CLAV_BAL_UNLOCK;
			weighingInterface->setWeighingOrder(order);
			weighingInterface->setPanneauAppelant(this);
			weighingInterface->weighingOrderTreatment();
		}
	}

	m_choix_OF->afficherOrdre(m_data->getCurrentOrderIndex(),
							  m_data->getCurrentPhaseIndex(),
							  m_data->getCurrentComposantIndex());
 	m_Pesee_OF->hide();
	m_choix_OF->show();
	m_choix_OF->setFocus(m_choix_OF->getSaisieComposant());

}

//---------------------------------------------------------------------------
void AdxPesee_OF::afficherOrdre(long numo,long nump,long numc)
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxOrder* order = m_data->getOrder(numo);
	getAffNOF()->setLabel(order->getNumOF());
	
	AdxPhase* phase = m_data->getPhase(nump);
	getAffNPhase()->setValue((IlvDouble)phase->getNumPhase());

	AdxComposant* composant = phase->getComposant(numc);
	getAffComposant()->setLabel(composant->getComposant());
// mm 06.10 - ajout libellé
	getLibAffComposant()->setLabel(composant->getLibComposant());
// recherche la fiche ISM du composant

	_ficheISM = m_data->getCurrentFicheISM();

// mise en place des logos sécurité en fonction de la fiche ISM du composant

	for (long o = 0; o < 10; o++)
	{
		_occup[o] = 0;
	}

	if (_ficheISM->getPictogramme1() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme1());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu1()->setBitmap(bitmap);
		getsecu1()->setSensitive(IlvTrue);
	    setVisible(getsecu1(),IlvTrue, IlvFalse);
		_occup[0] = 1;
	}
	else
	{
	    setVisible(getsecu1(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu1());

	if (_ficheISM->getPictogramme2() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme2());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu2()->setBitmap(bitmap);
		getsecu2()->setSensitive(IlvTrue);
	    setVisible(getsecu2(),IlvTrue, IlvFalse);
		_occup[1] = 1;
	}
	else
	{
	    setVisible(getsecu2(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu2());

	if (_ficheISM->getPictogramme3() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme3());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu3()->setBitmap(bitmap);
		getsecu3()->setSensitive(IlvTrue);
	    setVisible(getsecu3(),IlvTrue, IlvFalse);
		_occup[2] = 1;
	}
	else
	{
	    setVisible(getsecu3(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu3());

	if (_ficheISM->getPictogramme4() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme4());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu4()->setBitmap(bitmap);
		getsecu4()->setSensitive(IlvTrue);
	    setVisible(getsecu4(),IlvTrue, IlvFalse);
		_occup[3] = 1;
	}
	else
	{
	    setVisible(getsecu4(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu4());

	if (_ficheISM->getPictogramme5() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme5());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu5()->setBitmap(bitmap);
		getsecu5()->setSensitive(IlvTrue);
	    setVisible(getsecu5(),IlvTrue, IlvFalse);
		_occup[4] = 1;
	}
	else
	{
	    setVisible(getsecu5(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu5());

	if (_ficheISM->getPictogramme6() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme6());
		IlvBitmap* bitmap = 
		getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu6()->setBitmap(bitmap);
		getsecu6()->setSensitive(IlvTrue);
	    setVisible(getsecu6(),IlvTrue, IlvFalse);
		_occup[5] = 1;
	}
	else
	{
	    setVisible(getsecu6(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu6());

	if (_ficheISM->getPictogramme9() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme9());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu7()->setBitmap(bitmap);
		getsecu7()->setSensitive(IlvTrue);
	    setVisible(getsecu7(),IlvTrue, IlvFalse);
		_occup[6] = 1;
	}
	else
	{
	    setVisible(getsecu7(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu7());

	if (_ficheISM->getPictogramme10() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme10());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu8()->setBitmap(bitmap);
		getsecu8()->setSensitive(IlvTrue);
	    setVisible(getsecu8(),IlvTrue, IlvFalse);
		_occup[7] = 1;
	}
	else
	{
	    setVisible(getsecu8(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu8());

	if (_ficheISM->getPictogramme11() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme11());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu9()->setBitmap(bitmap);
		getsecu9()->setSensitive(IlvTrue);
	    setVisible(getsecu9(),IlvTrue, IlvFalse);
		_occup[8] = 1;
	}
	else
	{
	    setVisible(getsecu9(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu9());

	if (_ficheISM->getPictogramme12() != NULL)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme12());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu10()->setBitmap(bitmap);
		getsecu10()->setSensitive(IlvTrue);
	    setVisible(getsecu10(),IlvTrue, IlvFalse);
		_occup[9] = 1;
	}
	else
	{
	    setVisible(getsecu10(),IlvFalse, IlvFalse);
	}
	bufferedDraw(getsecu10());

// pour cas des précautions 7 et 8 (à mettre en secu 10 et 9 si libres)

	if (_ficheISM->getPictogramme7() != NULL && _occup[9] == 0)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme7());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu10()->setBitmap(bitmap);
		getsecu10()->setSensitive(IlvTrue);
	    setVisible(getsecu10(),IlvTrue, IlvFalse);
		_occup[9] = 2;
		bufferedDraw(getsecu10());
	}

	if (_ficheISM->getPictogramme8() != NULL && _occup[8] == 0)
	{
		char szFileIcons[_MAX_PATH];
		char* pszFileIcons = &szFileIcons[0];
		sprintf (szFileIcons, "%s\\%s.jpg",
			_interface->getPathCACHE(),
			_ficheISM->getPictogramme8());
		IlvBitmap* bitmap = 
			getDisplay()->readBitmap(szFileIcons);
        if (!bitmap || bitmap->isBad())
		{
			bitmap = erreurBitmap(pszFileIcons);
		}
		getsecu9()->setBitmap(bitmap);
		getsecu9()->setSensitive(IlvTrue);
	    setVisible(getsecu9(),IlvTrue, IlvFalse);
		_occup[8] = 2;
		bufferedDraw(getsecu9());
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::afficherLot(AdxLot* lot, bool afficheQuantite)
{
	if (lot != NULL)
	{
		if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
		{
			getSaisieCuve()->setLabel(lot->getCuve());
			getLibSaisieCuve()->setLabel(lot->getLibSaisieCuve());		// mm 06.10 - ajout libellé
			getSaisieVanne()->setLabel(lot->getVanne());
			bufferedDraw(getSaisieCuve());
			bufferedDraw(getLibSaisieCuve());	
			bufferedDraw(getSaisieVanne());
		}
		else
		{
			// mm 05.10 - lot et sous-lot ne sont plus concaténés
			getSaisieLot()->setLabel(lot->getLot());	
			getSaisieSousLot()->setLabel(lot->getSlo());	
			getSaisieEmplacement()->setLabel(lot->getEmplacement());
			getLibSaisieEmplacement()->setLabel(lot->getLibEmplacement());// mm
			bufferedDraw(getSaisieLot());
			bufferedDraw(getSaisieSousLot());
			bufferedDraw(getSaisieEmplacement());
			bufferedDraw(getLibSaisieEmplacement());// mm
		}
		// llc 04.02 ne pas afficher si limite balance
		if ((afficheQuantite) & (_peseeLimiteeParBalance == false))
		{
			getAffPoidsAPeser()->setValue((IlvDouble) lot->getQuantiteAllouee());
			bufferedDraw(getAffPoidsAPeser());
		}
	}
	else
	{
		if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
		{
			getSaisieCuve()->setLabel("");
			getSaisieVanne()->setLabel("");
			bufferedDraw(getSaisieCuve());
			bufferedDraw(getSaisieVanne());
		}
		else
		{
			// mm 05.10 - lot et sous-lot ne sont plus concaténés
			getSaisieLot()->setLabel("");
			getSaisieSousLot()->setLabel("");
			getSaisieEmplacement()->setLabel("");
			getLibSaisieEmplacement()->setLabel("");// mm
			bufferedDraw(getSaisieLot());	
			bufferedDraw(getSaisieSousLot());
			bufferedDraw(getSaisieEmplacement());
			bufferedDraw(getLibSaisieEmplacement());// mm
		}
		if (afficheQuantite)
		{
			IlvDouble val = 0;
			getAffPoidsAPeser()->setValue(val);
			bufferedDraw(getAffPoidsAPeser());
		}
	}

	
}
//---------------------------------------------------------------------------
void AdxPesee_OF::chargement()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();

	double toleranceArticleNegative = 0.0;
	double toleranceArticlePositive = 0.0;
	double _qtebesoinPrevue = 0.0;		// 113445 mm 06.2016


	// mm 05.10 - % de tolérance article au niveau de la nomenclature
	if (m_data->getCurrentComposant() != NULL)
	{
		toleranceArticleNegative = m_data->getCurrentComposant()->getToleranceArticleNegative();
		toleranceArticlePositive = m_data->getCurrentComposant()->getToleranceArticlePositive();
	}

	if (toleranceArticleNegative == 0 && toleranceArticlePositive ==0 && 
		getBalanceChoisie() != NULL)
	{
		toleranceArticleNegative = getBalanceChoisie()->getTolerance();
		toleranceArticlePositive = getBalanceChoisie()->getTolerance();
	}

	chargementAffichage();

// definition du type de pesee a faire
	if (m_data->getCurrentFicheISM()->getCodeEmballage() == 2 || //emb fournisseur
		m_data->getCurrentFicheISM()->getModePeseeCode() == 1)   //pesee par ecart
		_peseeParEcart = true;
	else
		_peseeParEcart = false;
	_peseeParConsigne = false;

// mise en place des decimales d'affichage
	getAffPoidsAPeser()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());
	getAffTare()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());
	getAffTotalAPeser()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());
	getSaisiePoidsPese()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());
	getAffPoidsCumuleCible()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());
	getAffPoidsCumule()->setPrecision(m_data->getCurrentComposant()->getDecimalePoids());

	const char* format = m_data->getCurrentComposant()->getFormat();
	getJaugeScale()->setFormat(format);

	afficherOrdre(m_data->getCurrentOrderIndex(),
				  m_data->getCurrentPhaseIndex(),
				  m_data->getCurrentComposantIndex());

	chargementRecipient();

// initialise la sensibilité des boutons
	getvalider()->setSensitive(false);
	getvaliderPlus()->setSensitive(false);
	gettactile()->setSensitive(true);
	getquitter()->setSensitive(true);
	gettarer()->setSensitive(false);
	getmettreAZero()->setSensitive(false);
	getpeser()->setSensitive(false);
	setVisible(getAffConnection(),IlvFalse, IlvFalse);
// possibilite modif lot ou pas	
	setChampsAlphaEditable(true);
	// mm 01.2013 APCPRD-2787
	_btVPlus = true;
	_btV = true;


	_lotOK = false;
	_recipientOK = false;
	_balanceOK = false;

	_miseAZeroOK = false;
	_tarageOK = false;
	_peseeOK = false;
	_stockReelInfInfo = false;
	_modifAllocations = false; // Sr 12.11 APCPRD-724
	_peseeLimiteeParBalance = false;
	_attenteTarage = false;
	_messageLu = false ;		// 06.07 mm - Forcer la lecture d'une icone
	_attentePesee = false;
	_balanceBegin = false;
	_razTare = false;				// 12.08 mm - Réinitialisation de la tare en cas d'emb. fournisseur avec tare modifiable
	_peseeCumuleeForcee = false ;	// 11.07 mm - modif mode de pesee en emb.mixte
	m_data->setComposantBegin(false);

// initialisation des valeurs de la pesee future
	m_data->setCurrentLotIndex(m_data->getNbLots());
	setBalanceChoisie(NULL);
	setRecipientChoisi(NULL);
	_balancePrevue      = NULL;
	_recipientPrevu     = NULL;
	_totalAPeser	    = m_data->getCurrentComposant()->getQuantiteTheorique();
	_totalAPeserInitial	= m_data->getCurrentComposant()->getQuantiteTheorique();
	// 113445 mm 06.2016
	if (m_data->getCurrentComposant()->getGestionStock() == 3 && m_data->getCurrentComposant()->getTitreTheo()) // component with potency
		_qtebesoinPrevue	= m_data->getCurrentComposant()->getQuantitePrevue()
							/ (m_data->getCurrentComposant()->getTitreTheo()/100);
	else	
		_qtebesoinPrevue	= m_data->getCurrentComposant()->getQuantitePrevue();
	
	
	// mm 09.11 - pesée multi-article - initialisation des variables de travail pr stockage du contexte
	if (_enPeseeMultiArticle == false)
	{
		_poidsCumuleCible   = m_data->getCurrentComposant()->getQuantiteTheorique();	
		_poidsCumuleMulti   = 0;
		_indexComposantSuivantMulti	 = 0;
		_poidsTareMulti				 = 0;
		_poidsPeseMatEncours		 = 0;
		_poidsMatDejaPese			 = 0;
		setBoutonValidation(1);
	}
    // sr 03.04 on adapte l'échelle une fois pour toutes à ce moment là
    // sauf si la balance choisie est en consigne
     adaptationEchelle();
	_poidsCumule	    = 0;
	_poidsTare		    = 0;
	_poidsPese		    = 0;
	_poidsPeseTheo	    = 0;
	_poidsPeseTotal	    = 0;
	_poidsAPeser	    = 0;
	_poidsPeseParEcart	= 0;	// 09.09 mm - modif mode de pesee en emb.mixte
	_weightMin			= 0;	// mm 08.10
    _weightMax			= 0;	// mm 08.10	
	_poidsDejaPese		= 0;	// gbe 09/11
	_poidsPeseTotalPhysique = 0;	// mm 09.12
	_depassementPoidsMax = 0;		// 116324 mm 08.2016
	const char* unit =  m_interface->getDonnees()->getCurrentComposant()
		->getUnite();

// affichage des zones a l initialisation

// initialise unités par l'unité du composant
	getUnitePoidsPese()->setLabel(unit);
	getUnitePoidsAPeser()->setLabel(unit);
	getUniteTare()->setLabel(unit);
	getUniteTotalAPeser()->setLabel(unit);
	getUnitePoidsCumuleCible()->setLabel(unit);
	getUnitePoidsCumule()->setLabel(unit);

// réinitialisation champs 
	getAffTotalAPeser()->setValue(_totalAPeser);	
	getSaisiePoidsPese()->setValue(_poidsPese);
	getAffPoidsAPeser()->setValue(_poidsAPeser);
	getAffTare()->setValue(_poidsTare);
	getJaugePesee()->setValue(-_totalAPeserInitial);
	getAffPoidsCumuleCible()->setValue(_poidsCumuleCible);
	getAffPoidsCumule()->setValue(_poidsCumuleMulti);
	if(toleranceArticleNegative != 0.0)
	{
		// 113445 mm 06.2016
		if (m_data ->getApplicationTolerance()== 1)
			_weightMin = _totalAPeserInitial - _totalAPeserInitial * toleranceArticleNegative/100;
		else	
			_weightMin =  _totalAPeserInitial - _qtebesoinPrevue * toleranceArticleNegative/100;
	}
	else
	{
		_weightMin = 0.0;
	}
	if(toleranceArticlePositive != 0.0)
	{
		// 113445 mm 06.2016
		if (m_data ->getApplicationTolerance()== 1)	
			_weightMax = _totalAPeserInitial + _totalAPeserInitial * toleranceArticlePositive/100;
		else
			_weightMax = _totalAPeserInitial + _qtebesoinPrevue* toleranceArticlePositive/100;
	}	
	else
	{
		_weightMax = 0.0;
	}
	//113445 mm 06.2016 - use of setter
	setWeightMin( _weightMin);
	setWeightMax( _weightMax);

    afficherLot(NULL);
	getSaisieRecipient()->setLabel("");
	getSaisieBalance()->setLabel("");

// proposition automatique du lot (si possible)
    propositionLot();
	if (_lotOK)
	{
		afficherLot(m_data->getCurrentLot());
		setFocus(getvalider());	
	}
	else
	{
		attenteSaisieLot();
		return;
	}

 // 09.11 mm - on court-circuite la suite choixLot si on vient de Valider+
	if (_enPeseeMultiArticle == false)
		suiteChoixLot();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::chargementRecipient()
{	
	AdxData* m_data = getInterface()->getDonnees();
// construit la liste des récipients à partir des fiches ISM récipient du composant
	IlList* ficheISMRecipientList = m_data->getFicheISMRecipientList();
	IlList* recipientList = m_data->getRecipientList();
	if (m_data->getNbRecipients() > 0)
	{
		for (int i = 0; i < m_data->getNbRecipients(); i++)
		{
			delete (AdxRecipient*)(*recipientList)[i];
		}
	}
	recipientList->empty();
	int nbRecipients = 0;
	for (int i = 0; i < m_data->getNbFichesISMRecipient(); i++) 
	{
		AdxFicheISMRecipient* ficheISMRecipient
			= (AdxFicheISMRecipient*)(*ficheISMRecipientList)[i];
		if (strcmp(ficheISMRecipient->getFicheISMRecipient(),
			m_data->getCurrentComposant()->getFicheISM()) == 0)
		{
			// construction le la liste par ajouts successifs
			
			AdxRecipient* recipient = new AdxRecipient;
		
			recipient->setRecipient( ficheISMRecipient->getRecipient());
			recipient->setLibRecipient( ficheISMRecipient->getLibRecipient());
			recipient->setUnitePoids( ficheISMRecipient->getUnitePoids());
			recipient->setPoidsMaxi( ficheISMRecipient->getPoidsMaxi());
			recipient->setTypeRecipient( ficheISMRecipient->getTypeRecipient());
			recipient->setLibTypeRecipient( ficheISMRecipient->getLibTypeRecipient());
			recipient->setTareTheo( ficheISMRecipient->getTareTheo());
			recipient->setTareTheoSvg( ficheISMRecipient->getTareTheo());		// 02.09 Sauvegarde Tare théo, sinon écrasé en cas de tare saisie
			recipient->setTolerance( ficheISMRecipient->getToleranceTare());
			recipient->setGuideOperateur( ficheISMRecipient->getGuideOperateur());
			recipient->setFormatEtiquette( ficheISMRecipient->getFormatEtiquette());
			recipient->setTareModifiable( ficheISMRecipient->getTareModifiable());	// 04.07 gestion d'une tare modifiable
			recipient->setSaisiePoids(ficheISMRecipient->getSaisiePoids());	// 10.07 saisie du poids
			
			chargementBalance(recipient);

			m_data->getRecipientList()->append(recipient);
			nbRecipients +=1;
		}
	}
	m_data->setNbRecipients(nbRecipients);
}

//---------------------------------------------------------------------------
void AdxPesee_OF::chargementBalance(AdxRecipient* recipient)
{	
// construit la liste des balances convenant au recipient
//	balanceList est la liste des 8 balances du poste
//  _balanceList est la liste des balances du recipient
	IlList* balanceListGene = getInterface()->getDonnees()->getBalanceList();
	IlList* balanceListRecipient = recipient->getBalanceList();
	for (int i = 0; i < balanceListRecipient->length(); i++)
	{
		delete (AdxBalance*)(*balanceListRecipient)[i];
	}
	balanceListRecipient->empty();
	double porteeMini;
	double tareMaxi;
	int nbBalances = 0;
	for (int i = 0; i < getInterface()->getDonnees()->getNbBalances(); i++) 
	{
		AdxBalance* balance
			= (AdxBalance*)(*balanceListGene)[i];
		porteeMini = getInterface()->getDonnees()->convertir(
			balance->getPorteeMini(),
			balance->getUnite(),
			recipient->getUnitePoids());
		
		tareMaxi = getInterface()->getDonnees()->convertir(
			balance->getTareMaxi(),
			balance->getUnite(),
			recipient->getUnitePoids());
		if (porteeMini <= recipient->getTareTheo() &&
		recipient->getTareTheo() <= tareMaxi)
		{
			// construction la liste par ajouts successifs
			balanceListRecipient->append(balance);
			nbBalances +=1;
		}
	}
	recipient->setNbBalances(nbBalances);
}

//---------------------------------------------------------------------------
// affichage different s'il y a des cuves disponibles en pesee en fabrication
void AdxPesee_OF::chargementAffichage()
{
	if ((getInterface()->getFonctionEnCours() == 1)
	||	(getInterface()->getFonctionEnCours() == 3))
	{
			setTitle(IlvGetMessage(getDisplay(),"&PeseeOF"));
	}
	else
	{
			setTitle(IlvGetMessage(getDisplay(),"&PeseeArt"));
	}

	if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
	{
//	ces champs sont actifs en pesee en cuve
		setVisible(getEtiquetteCuve(),IlvTrue,IlvFalse);
		setVisible(getSaisieCuve(),IlvTrue,IlvFalse);
		setVisible(getLibSaisieCuve(),IlvTrue,IlvFalse);// gbe
		setVisible(getBoutonListeCuve(),IlvTrue,IlvFalse);
		setVisible(getEtiquetteVanne(),IlvTrue,IlvFalse);
		setVisible(getSaisieVanne(),IlvTrue,IlvFalse);
//	ces champs sont actifs en pesee par lot emplacement
		setVisible(getEtiquetteLot(),IlvFalse,IlvFalse);
		setVisible(getSaisieLot(),IlvFalse,IlvFalse);
		setVisible(getEtiquetteSousLot(),IlvFalse,IlvFalse);// mm
		setVisible(getSaisieSousLot(),IlvFalse,IlvFalse);// mm
		setVisible(getBoutonListeLot(),IlvFalse,IlvFalse);
		setVisible(getEtiquetteEmplacement(),IlvFalse,IlvFalse);
		setVisible(getSaisieEmplacement(),IlvFalse,IlvFalse);
		setVisible(getLibSaisieEmplacement(),IlvFalse,IlvFalse);// mm
		setVisible(getBoutonListeEmplacement(),IlvFalse,IlvFalse); 
	}
	else
	{
//	ces champs sont actifs en pesee en cuve
		setVisible(getEtiquetteCuve(),IlvFalse,IlvFalse);
		setVisible(getSaisieCuve(),IlvFalse,IlvFalse);
		setVisible(getLibSaisieCuve(),IlvFalse,IlvFalse);// gbe
		setVisible(getBoutonListeCuve(),IlvFalse,IlvFalse);
		setVisible(getEtiquetteVanne(),IlvFalse,IlvFalse);
		setVisible(getSaisieVanne(),IlvFalse,IlvFalse);
//	ces champs sont actifs en pesee par lot emplacement
		setVisible(getEtiquetteLot(),IlvTrue,IlvFalse);
		setVisible(getSaisieLot(),IlvTrue,IlvFalse);
		setVisible(getEtiquetteSousLot(),IlvTrue,IlvFalse);// mm
		setVisible(getSaisieSousLot(),IlvTrue,IlvFalse);// mm
		setVisible(getBoutonListeLot(),IlvTrue,IlvFalse);
		setVisible(getEtiquetteEmplacement(),IlvTrue,IlvFalse);
		setVisible(getSaisieEmplacement(),IlvTrue,IlvFalse);
		setVisible(getBoutonListeEmplacement(),IlvTrue,IlvFalse);// mm
		setVisible(getBoutonListeEmplacement(),IlvFalse,IlvFalse);
	}

	// 08.11 mm - Pesée multi-article : ajout du bouton Valider+ en pesée par OF
	if (getInterface()->getFonctionEnCours() == 1)
	{
		setVisible(getAide(),IlvFalse,IlvFalse);
		// nouveaux champs liés à la pesée multi-article actifs
		setVisible(getvaliderPlus(),IlvTrue,IlvFalse);
		setVisible(getEtiquettePoidsCumule(),IlvTrue,IlvFalse);
		setVisible(getAffPoidsCumule(),IlvTrue,IlvFalse);
		setVisible(getEtiquettePoidsCumuleCible(),IlvTrue,IlvFalse);
		setVisible(getAffPoidsCumuleCible(),IlvTrue,IlvFalse);
		setVisible(getUnitePoidsCumuleCible(),IlvTrue,IlvFalse);
		setVisible(getUnitePoidsCumule(),IlvTrue,IlvFalse);
	}
	else
	{
		setVisible(getAide(),IlvTrue,IlvFalse);
		// nouveaux champs liés à la pesée multi-article inactifs
		setVisible(getvaliderPlus(),IlvFalse,IlvFalse);
		setVisible(getEtiquettePoidsCumule(),IlvFalse,IlvFalse);
		setVisible(getAffPoidsCumule(),IlvFalse,IlvFalse);
		setVisible(getEtiquettePoidsCumuleCible(),IlvFalse,IlvFalse);
		setVisible(getAffPoidsCumuleCible(),IlvFalse,IlvFalse);
		setVisible(getUnitePoidsCumuleCible(),IlvFalse,IlvFalse);
		setVisible(getUnitePoidsCumule(),IlvFalse,IlvFalse);
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::alimentationZonesNumeriques()
{
	AdxData* m_data = getInterface()->getDonnees();

	// pour corriger les ecarts de tolerance sur le dernier lot
	if (m_data->getCurrentComposant()->getGestionStock() == 3			// composant a titre
			&& m_data->getCurrentComposant()->getTitreTheo() != 0)
	{
		// 86060 mm 12.12 : _poidsAPeser d'une matière titrée décrémenté à chaque passage dans l'écran 
		// de sélection des lots
		if (_totalAPeser != _poidsAPeser)
		{
			if (_totalAPeser * m_data->getCurrentComposant()->getTitreTheo() <=
					m_data->getCurrentLot()->getQuantiteAllouee() * m_data->getCurrentLot()->getTitre())
			{
				_poidsAPeser = _totalAPeser * m_data->getCurrentComposant()->getTitreTheo()
        											/ m_data->getCurrentLot()->getTitre();
			}
			else
			{
				_poidsAPeser = m_data->getCurrentLot()->getQuantiteAllouee();
			}
		}
		// 93539 mm 02.14 - MAJ du champ _poidsAPeser
		else
		{
			_poidsAPeser = m_data->getCurrentLot()->getQuantiteAllouee();
		}
		//sr 01.12 APCPRD-516 Si dernier lot, la total à peser = poids à peser
		// 11516 mm 10.2015 - seulement si un seul lot alloué pour peser la totalité de quantité à peser
		if ( (lookLot())&&( m_data->getCurrentComposant()->getQuantitePrevue()== m_data->getCurrentComposant()->getQuantiteRestante()))
			_totalAPeser = _poidsAPeser;
	}
	else
	{
		if (_totalAPeser < m_data->getCurrentLot()->getQuantiteAllouee())
			_poidsAPeser = _totalAPeser;
		else
			_poidsAPeser = m_data->getCurrentLot()->getQuantiteAllouee();
	}

		

// affichage des zones numeriques a zero
	getAffPoidsAPeser()->setValue(_poidsAPeser);
	bufferedDraw(getAffPoidsAPeser());
//    adaptationEchelle();
//sr 01.12 APCPRD-516
//	_totalAPeser = getInterface()->getDonnees()->getCurrentComposant()->getQuantiteTheorique();
	
	getAffTotalAPeser()->setValue(_totalAPeser);
	// mm spéficique FAREVA 10.2015 - Ajouter un paramètre pour choisir 
	// en fonction de quel titre on veut exprimer ce champ.
	//getAffTotalAPeser()->setValue(_totalAPeser *(m_data->getCurrentComposant()->getTitreTheo()/
	//	m_data->getCurrentLot()->getTitre()));
	bufferedDraw(getAffTotalAPeser());
	_poidsPese = 0;
	getSaisiePoidsPese()->setValue(_poidsPese);
	bufferedDraw(getSaisiePoidsPese());
	_poidsEncours = 0;
}
//---------------------------------------------------------------------------
void AdxPesee_OF::suiteChoixLot()
{	
	AdxData* m_data = getInterface()->getDonnees();

	alimentationZonesNumeriques();
// sr 20/04
//	getJaugePesee()->setValue(_poidsPeseTotal);
//	bufferedDraw(getJaugePesee());
	if (_tarageOK == false)
		_poidsTare = 0;
	getAffTare()->setValue(_poidsTare);
	bufferedDraw(getAffTare());

// 11.07 mm - modif mode de pesee en emb.mixte
// Possibilite de peser par ecart ou en cumule selon la categorie du récipient
if (m_data->getCurrentFicheISM()->getCodeEmballage() == 3 &&  //emb mixte
		m_data->getCurrentFicheISM()->getModePeseeCode() == 2 && //mode de pesee cumulee
		_peseeParEcart )	// type de pesee
{
	_peseeParEcart = false;
	_peseeCumuleeForcee = true ;
	setBalanceChoisie(NULL);
	setRecipientChoisi(NULL);
	_poidsTare = 0;
	getAffTare()->setValue(_poidsTare);
	bufferedDraw(getAffTare());
	_poidsPeseParEcart = _poidsPeseTotal ;		// 09.09 mm - modif mode de pesee en emb.mixte
	attenteSaisieRecipient();
	return ;
}

/////////////////////
// pesee par ecart //
/////////////////////
	if (_peseeParEcart)
	{
//prevoir de recalculer recipient et essayer de conserver la balance
		if (m_data->getComposantBegin())
		{
			_balanceBegin = false;	
			propositionRecipient();
			if (_recipientOK == true)
			{
				suiteChoixRecipient();
			}
			else
			{
				setBalanceChoisie(NULL);
				setRecipientChoisi(NULL);
				attenteSaisieRecipient();
			}
		}
		else
	// proposition automatique du récipient 
		{
			_balanceBegin = false;
			propositionRecipient();
			if (_recipientOK == true)
			{
				suiteChoixRecipient();
			}
			else
			{
				_balanceOK = false;
				setBalanceChoisie(NULL);
				setRecipientChoisi(NULL);
				attenteSaisieRecipient();
			}
		}
	}
	else
/////////////////////
// pesee cumulee   //
/////////////////////
	{
		// mm 11.09 - emb mixte + mode de pesee cumulee, le composant a déjà été pesé en partie en
		// emballage fournisseur.
		if (m_data->getCurrentFicheISM()->getCodeEmballage() == 3 &&
			m_data->getCurrentFicheISM()->getModePeseeCode() == 2 &&
			_balanceChoisie == NULL && _recipientChoisi == NULL )
		{
			attenteSaisieRecipient();
		}
		else if (m_data->getComposantBegin())
		{
// inutile de controler recipient et balance ils sont ok et non modifiables
			suiteChoixBalance();
		}
		else
		{
			propositionRecipient();
			if (_recipientOK)
			{
				suiteChoixRecipient();
			}
			else
			{
				setBalanceChoisie(NULL);
				setRecipientChoisi(NULL);
				attenteSaisieRecipient();
			}
		}
	}
}


//---------------------------------------------------------------------------
void AdxPesee_OF::suiteChoixLotMulti()
{
	AdxData* m_data = getInterface()->getDonnees();

	alimentationZonesNumeriques();
	//APCPRD-728 Le recipient utilise fait-il partie de la liste des recipients pour cet article ?
	if (controleRecipientPrevu() == true)
	{
		if (controleRecipientMulti()== true)
		{
			setRecipientChoisi(	_recipientMulti);
			_tarageOK = true ;
			// conversion du _poidsTare si besoin
			if (strcmp (m_data->getCurrentComposant()->getUnite(),getUnitePoidsMat1())!= 0)
			{
				_poidsTare =  m_data->convertir(
					getPoidsTareMulti(),getUnitePoidsMat1(),m_data->getCurrentComposant()->getUnite());
		
			}
			else
				_poidsTare =  getPoidsTareMulti();
				getAffTare()->setValue(_poidsTare);
				bufferedDraw(getAffTare());	
				suiteChoixRecipientMulti();
		}
		// Pas assez de place ds le récipient : la pesée cumulée s'arrête là
		else
		{
			char* message = new char[LengthMaxMessage];
			sprintf(message," %s : %s ",
			IlvGetMessage(getInterface()->getDisplay(),"&PeseeMultiArticleImpossible"),
			IlvGetMessage(getInterface()->getDisplay(),"&CapaciteInsuffisante  "));
			getInterface()->envoieMessage(message,false);	
			delete [] message;
			m_data->sendX3_InterruptionPeseeMulti();
			quitter();
			return;
		}
	}
	// Récipient non prévu  : la pesée cumulée s'arrête là
	else
	{
		char* message = new char[LengthMaxMessage];
		sprintf(message," %s : %s ",
		IlvGetMessage(getInterface()->getDisplay(),"&PeseeMultiArticleImpossible2"),
		IlvGetMessage(getInterface()->getDisplay(),"&RecipientNonPrevu"));
		getInterface()->envoieMessage(message,false);	
		delete [] message;
		quitter();
	}
			return;
}
//---------------------------------------------------------------------------
void AdxPesee_OF::suiteChoixRecipientMulti()
{
	AdxData* m_data = getInterface()->getDonnees();

	controleBalanceMulti();
	if (_balanceOK == false)
	{
		//Portée balance insuffisante : la pesée cumulée s'arrête là
		char* message = new char[LengthMaxMessage];
		sprintf(message," %s : %s ", 
			IlvGetMessage(getInterface()->getDisplay(),"&PeseeMultiArticleImpossible"),
			IlvGetMessage(getInterface()->getDisplay(),"&PorteeBalance "));
		getInterface()->envoieMessage(message,false);	
		delete [] message;
		m_data->sendX3_InterruptionPeseeMulti();
		quitter();
		return;
	}
	else
	{
		setBalanceChoisie(_balanceMulti);
		_balanceBegin = false;
		suiteChoixBalanceMulti();
	}
}
//---------------------------------------------------------------------------
// Sommes-nous sur le dernier lot ou y a t il un lot derrière ?
// on regarde si il y a un lot autre que le courant qui a des allocs
bool AdxPesee_OF::lookLot()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
    _dernierLot = true;
    
	IlList* lotList = m_data->getLotList();
	AdxLot* lot;
	//double tolerance = 0.0;
	//if (_ficheISM != NULL)
	//	tolerance = _ficheISM->getToleranceArticle();

	int i = 0;
	while ( i < m_data->getNbLots())
	{
		lot = (AdxLot*)(*lotList)[i];
		if (((strcmp(lot->getLot(),m_data->getCurrentLot()->getLot())!= 0) 
            || (strcmp(lot->getSlo(),m_data->getCurrentLot()->getSlo())!= 0))
            && lot->getQuantiteAllouee() > 0)
		{
            // on a trouvé un autre lot/sous-lot alloué
            // on n'est donc pas sur le dernier lot
			_dernierLot = false;
			return _dernierLot;
		}
		i++;
	}
	return _dernierLot;
}


//---------------------------------------------------------------------------
void AdxPesee_OF::suiteChoixRecipient()
{
// proposition automatique de la balance (si possible)
	propositionBalance();
	if (_balanceOK == false)
	{
		if (_peseeParEcart == false)
		{
//			envoieMessage("&AucuneBalanceSuffisantePourPeseeCumulee",false);
			_peseeParEcart = true;
			propositionRecipient();
			suiteChoixRecipient();
			return;
		}
		attenteSaisieBalance();
		return;
	}
	
		
	suiteChoixBalance();
}

//---------------------------------------------------------------------------
void AdxPesee_OF::suiteChoixBalance()
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	// 06.07 mm - Forcer la lecture d'une icone
	if (m_data->getCurrentFicheISM()->getMessageObligatoire() == 2 && _messageLu == false)
	{	
		CString string;
		string = IlvGetMessage(getDisplay(), "&Icone");	
		getmessage()->setLabel(string);
		bufferedDraw(getmessage());	
		gettactile()->setSensitive(false);
		getmettreAZero()->setSensitive(false);
		gettarer()->setSensitive(false);
		getpeser()->setSensitive(false);
		if (m_data->getCurrentFicheISM()->getPictogramme1() != NULL)
			setFocus(getsecu1());
		else
			setFocus(getsecu7());
		return;
	}

	

// balance non connectee pas de mise zero via l'interface
//	setFocus(getSaisiePoidsPese());

	_recontroleFait = false;

	bool bContinue = false;

	bContinue = affecteBalance();
	if (bContinue == true)
	{
		// Evolution multi plateaux
		// ICI nous sommes en présence d'une balance qui a été affectée dans la
		// weighingInterface et qui est connectée, alors on positionne le bon plateau

		if(_balanceChoisie->IsMultiPlate() == true)
		{
			WeighingOrder order;

			order = CHGT_P;
			weighingInterface->setWeighingOrder(order);
			weighingInterface->setPanneauAppelant(this);
			weighingInterface->weighingOrderTreatment();
			if (weighingInterface->getWeighingStatus() != OK_STA)
			{
				// Mettre un message indiquant que le changement de plateau a échoué
				bContinue = false;
			}
		}
	}
	if (bContinue == false)
	{
		// 10.07 mm - deplace depuis qu'on modifie la valeur de connecte dans 
		// affecteBalance()
		if (_balanceBegin == false)
		{	
			setVisible(getAffConnection(),IlvFalse, IlvFalse);
			_peseeParConsigne = false;
   			adaptationEchelle();
		}

		
		/////////////////////////////////////////////////////
		// nieme pesee de pesee cumulee -> pas de retarage //
		/////////////////////////////////////////////////////
		if (_peseeParEcart == false && m_data->getComposantBegin() 
			&& _peseeCumuleeForcee == 0)
		{
// sr 20/04
//			getJaugePesee()->setValue(_poidsPeseTotal);
//			bufferedDraw(getJaugePesee());
			getSaisiePoidsPese()->setValue(_poidsPese);
			bufferedDraw(getSaisiePoidsPese());
			// APCPRD-2636 mm 09.2013
			if (m_data->getRecontroleArticleCode() !=1)
			 getSaisiePoidsPese()->setEditable(false);
			getmessage()->setLabel(formatMessage("&Peser1"));
			bufferedDraw(getmessage());
//			adaptationEchelle();
			_tarageOK = true;
			_attenteTarage = false;
			_attentePesee = true;
			getmettreAZero()->setSensitive(false);
			gettarer()->setSensitive(false);
			getpeser()->setSensitive(true);
			setFocus(getpeser());
		}
		//////////////////////////////////////////////////////
		// pesee par ecart  ou 1iere pesee de pesee cumulee //
		//////////////////////////////////////////////////////
		else
		{
// affichage de la mise a zero
			// sr 02.02 remise à 0 de la tare entre deux récipients
			_poidsTare = 0;
// sr20/04
//			getJaugePesee()->setValue(_poidsPeseTotal);
//			bufferedDraw(getJaugePesee());
			getAffTare()->setValue(_poidsTare);
			bufferedDraw(getAffTare());
			getSaisiePoidsPese()->setValue(_poidsPese);
			bufferedDraw(getSaisiePoidsPese());

			// sr 12.02 si pas de tare alors on pèse directement
			if ((_recipientChoisi->getTypeRecipient() == 2)
			|| (_recipientChoisi->getTareTheo() == 0))
			{
				
				// 06.09 gestion d'une tare modifiable
				// récipient fournisseur + tare modifiable
				if (_recipientChoisi->getTypeRecipient()==2 && _recipientChoisi->getTareModifiable() ==2 )		
				{		
					_tarageOK =  false ;
					_attentePesee = false;
					_attenteTarage = true;
					CString string(IlvGetMessage(getDisplay(), "&Saisir"));
					string += " ";
					string += IlvGetMessage(getDisplay(),"&Tare2");
					getmessage()->setLabel(string);
					bufferedDraw(getmessage());
					gettactile()->setSensitive(false);
					getmettreAZero()->setSensitive(false);
					gettarer()->setSensitive(false);
					getpeser()->setSensitive(true);
					setFocus(getSaisiePoidsPese());	
				}
				else
				{
					_poidsTare = m_data->convertir(
							_recipientChoisi->getTareTheo(), 
							_recipientChoisi->getUnitePoids(), 
							m_data->getCurrentComposant()->getUnite());
					getAffTare()->setValue(_poidsTare);
					bufferedDraw(getAffTare());
					getmessage()->setLabel(formatMessage("&Peser1"));
					bufferedDraw(getmessage());
					_tarageOK = true;
					_attenteTarage = false;
					_attentePesee = true;
					gettactile()->setSensitive(false);
					getmettreAZero()->setSensitive(false);
					gettarer()->setSensitive(false);
					getpeser()->setSensitive(true);
					setFocus(getpeser());
					// sr 02.02 si récipient fournisseur pas de saisie possible
					// sr 01.03 tester si récipient fournisseur car ce peut être
					// un récipient interne avec tare à 0 et alors là on doit
					// pouvoir choisir
					if (_recipientChoisi->getTypeRecipient() == 2)
					{
						getSaisieRecipient()->setEditable(false);
					}
					// APCPRD-2636 mm 08.2013
					else
					{
						if((_recipientChoisi->getTareTheo() ==0 ) &&
						(!_balanceChoisie->getConnecte()) ) 
						  getSaisiePoidsPese()->setEditable(false);
					}
				}
			}
			else
			{
				getmessage()->setLabel(formatMessage("&Tarer"));
				bufferedDraw(getmessage());
				_attenteTarage = false;
				_attentePesee = false;
				gettactile()->setSensitive(false);
				getmettreAZero()->setSensitive(false);
				gettarer()->setSensitive(true);
				getpeser()->setSensitive(false);
				setFocus(gettarer());
			}
		}
		_miseAZeroOK = true;
		return;
	}

	// 10.07 pesee en mode degrade selon la valeur de saisie Poids -
	// deplace depuis qu'on modifie la valeur de connecte dans affecteBalance() 
	if (_balanceBegin == false)
    {
		setVisible(getAffConnection(),IlvTrue, IlvFalse);
		_peseeParConsigne = _balanceChoisie->getConsigne();
   		adaptationEchelle();
    }

// on peut commencer la pesee
	if (_peseeParEcart == false && m_data->getComposantBegin()
		 && _peseeCumuleeForcee == 0)
	{
// sr 20/04
//		getJaugePesee()->setValue(_poidsPeseTotal);
//		bufferedDraw(getJaugePesee());
		getSaisiePoidsPese()->setValue(_poidsPese);
		bufferedDraw(getSaisiePoidsPese());
		getmessage()->setLabel(formatMessage("&TarageEffectuePeser"));
		bufferedDraw(getmessage());
		_miseAZeroOK = true;
		_tarageOK = true;
		_attenteTarage = false;
		_attentePesee = true;
		gettactile()->setSensitive(false);
		getmettreAZero()->setSensitive(false);
		gettarer()->setSensitive(false);
		getpeser()->setSensitive(true);
		setFocus(getpeser());
	}
	else
	{
        if (!m_data->getComposantBegin())
        {
        	getJaugePesee()->setValue(-_totalAPeserInitial);
			bufferedDraw(getJaugePesee());
        }
		// 04.07 gestion d'une tare modifiable
		// récipient fournisseur + tare modifiable
	
		if (_recipientChoisi->getTypeRecipient()==2 && _recipientChoisi->getTareModifiable() ==2 )		
		{
			// mm 12.08 -  Réinitialiser le poidsTare en cas de pls pesées en emb. fournisseur avec tare modifiable 
			// ou  emballage mixte
			if ((m_data->getComposantBegin() && !_attenteTarage && _poidsTare !=0 && !_razTare ) ||
				(m_data->getCurrentFicheISM()->getCodeEmballage() == 3 ))
			{
				_poidsTare =0 ;
				_razTare = true;
			}

			if (!_poidsTare )		// mm 12.08
			{
				getAffTare()->setValue(_poidsTare);
				bufferedDraw(getAffTare());
				// fin mm 10.08
				_tarageOK =  false ;
				_attentePesee = false;
				_attenteTarage = true;
				CString string(IlvGetMessage(getDisplay(), "&Saisir"));
				string += " ";
				string += IlvGetMessage(getDisplay(),"&Tare2");
				getmessage()->setLabel(string);
				bufferedDraw(getmessage());
				gettactile()->setSensitive(false);
				getmettreAZero()->setSensitive(false);
				gettarer()->setSensitive(false);
				getpeser()->setSensitive(true);
				setFocus(getSaisiePoidsPese());	
			}
			else					// mm 12.08 - si on s'est raté sur le recontrôle OF
			{
				getmessage()->setLabel(formatMessage("&RemiseAZeroEffectuee2  "));
				bufferedDraw(getmessage());
				gettactile()->setSensitive(false);
				getmettreAZero()->setSensitive(false);
				gettarer()->setSensitive(false);
				getpeser()->setSensitive(true);
				setFocus(getpeser());
			}
		}
		else
		{
			// 02.09 mm - emb. fournisseur, tare non modifiable
			if (_recipientChoisi->getTypeRecipient()==2 && _recipientChoisi->getTareModifiable() ==1)
			{
				// changement de balance : réinitialisation des flags
				if (_poidsTare == 0 && _tarageOK == true)
				{
					_tarageOK = false;
					_attenteTarage = false;
					_attentePesee = false ;
					getAffTare()->setValue(_poidsTare);
					bufferedDraw(getAffTare());
				}
			}
			getmettreAZero()->setSensitive(true);
			gettarer()->setSensitive(false);
			getpeser()->setSensitive(false);
			setFocus(getmettreAZero());
			getmessage()->setLabel(formatMessage("&FaireRemiseAZero"));
			bufferedDraw(getmessage());
		}

	}
}


//---------------------------------------------------------------------------	
void AdxPesee_OF::suiteChoixBalanceMulti()
{
	if (affecteBalance())
	{
		if (_balanceBegin == false)
		{
			setVisible(getAffConnection(),IlvTrue,IlvTrue);
			_peseeParConsigne = _balanceChoisie->getConsigne();
   			adaptationEchelle();
		}
	}

	getSaisiePoidsPese()->setValue(_poidsPese);   
	bufferedDraw(getSaisiePoidsPese());
	_tarageOK = true;
	_attenteTarage = false;
	_attentePesee = true;
	getmettreAZero()->setSensitive(false);
	gettarer()->setSensitive(false);
	getpeser()->setSensitive(true);
	setFocus(getpeser());
	getmessage()->setLabel(formatMessage("&TarageEffectuePeser"));
	bufferedDraw(getmessage());
}
//---------------------------------------------------------------------------
// sr 16/04 à revoir complètement pour la pesée en consigne
//---------------------------------------------------------------------------
void AdxPesee_OF::evolutionPoids()
{
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	AdxData* m_data = getInterface()->getDonnees();
    double weightMin;
    double weightMax;
    double _wpoidsEnPesee;
    double _wpoidsPeseJauge;
	double _delta = 0.0;


    _poidsPese = weighingInterface->getResNetWeight();

	
    //sr 10.04 recalculer le poids pesé au titre de cette pesée si pesée cumulée et balance connectée
    if ((_peseeParEcart == false) & (_balanceChoisie->getConnecte() != 0))
    {
		// 09.11 mm - Pesée multi-article
		if ( _enPeseeMultiArticle == true ) 
		{
			double _poidsMatDejaPeseUP2 = 0.0 ;
			if (strcmp(m_data->getCurrentComposant()->getUnite(),getUnitePoidsMat1())!=0)
				_poidsMatDejaPeseUP2  = m_data->convertir(getPoidsMatDejaPese(),
					getUnitePoidsMat1(),m_data->getCurrentComposant()->getUnite());
			else
				_poidsMatDejaPeseUP2  = _poidsMatDejaPese;
			// les poids sont tous exprimés en UP mat2
			_poidsCumuleMulti = _poidsPese ;	 // même poids affiché sur la balance et dans la zone _poidsCumule
			_poidsPese = _poidsPese - _poidsMatDejaPeseUP2 ;	// on retranche le poidsDejaPese du poidsPese, 
														// pour n'avoir que le poids de la matière en cours	
		
		}
		// 09.09 mm - modif mode de pesee en emb.mixte
	    else if (m_data->getCurrentFicheISM()->getCodeEmballage() == 3 &&	//emb mixte
			m_data->getCurrentFicheISM()->getModePeseeCode() == 2)	//mode de pesee cumulee
		{
			weighingInterface->setResNetWeight(_poidsPeseParEcart + _poidsPese);
			_poidsPese = weighingInterface->getResNetWeight();
			// reconverti le poids pesé
			weighingInterface->setResWeight(getInterface()->getDonnees()->convertir(
				weighingInterface->getResNetWeight(),
				weighingInterface->getWeightUnit(),
				weighingInterface->getResWeightUnit()));
		}

		// APCPRD 2074 - mm 11.12 
		// composant courant
		if (_poidsPeseTotalPhysique)
				_poidsPese = _poidsPese - _poidsPeseTotalPhysique;
		if ( _enPeseeMultiArticle == false ) 
				_poidsCumuleMulti = _poidsPeseTotalPhysique + _poidsPese ;		// 09.11 mm - Multi-articles 
	
    } 
	else  if ((_peseeParEcart == false) & (_balanceChoisie->getConnecte() == 0))
	{
		// sr 01.12 si balance non connectée, on enlève l'ancien poids pesé
			_poidsCumuleMulti -= _poidsEncours ;
			_poidsCumuleMulti += _poidsPese ;
	}

    
     // PESEE AVEC CONSIGNE:  _poidsPese mis à jour par la balance connecte est l'ecart a zero
    if (_peseeParConsigne)
    {   
    	_poidsPese = _poidsAPeser + _poidsPese;
        _wpoidsPeseJauge = -_totalAPeserInitial + _poidsPese;
    }     
    else
    {
        _wpoidsPeseJauge = _poidsPese;
		// mm 10.08 - Sartorius ne sait pas gerer les consignes de tare
		// alors on retranche le _poidsTare au poids pesé - seulement en cas d'emb. Fournisseur
		if ( _peseeParEcart && (weighingInterface->getBalance()->getNoDriver() ==5) 
			&&  (_balanceChoisie->getConnecte() == 1)
			&&  (_recipientChoisi->getTypeRecipient() == 2))
		{
			_wpoidsPeseJauge -=_poidsTare ;
			if (_wpoidsPeseJauge < 0)
				_wpoidsPeseJauge = 0;
		
		}
    }
  
  	getSaisiePoidsPese()->setValue(_poidsPese);
	bufferedDraw(getSaisiePoidsPese());  
	getAffPoidsCumule()->setValue(	_poidsCumuleMulti);
	// sr 01.12 Afficher après coloration
	bufferedDraw(getAffPoidsCumule());  


    // sr 03.04 en pesée,la jauge doit tenir compte du poids pesé plus du poids déjà pesée
    // tout ça en unité active si article titré !!!
    // en tarage, on ne change rien
    if (_attenteTarage == true)
    {
	    getJaugePesee()->setValue(weighingInterface->getResNetWeight());
       _poidsDejaPese =  weighingInterface->getResNetWeight();
    }
    else
    {
    	if (m_data->getCurrentComposant()->getGestionStock() != 3) 
    	{
	    	_wpoidsEnPesee  = _wpoidsPeseJauge;
	    }
	    else
	    {
		    _wpoidsEnPesee  = (_wpoidsPeseJauge * m_data->getCurrentLot()->getTitre())
    			/ m_data->getCurrentComposant()->getTitreTheo();
	    }
         _poidsDejaPese  = _poidsPeseTotal + _wpoidsEnPesee;
		
		
        getJaugePesee()->setValue(_poidsDejaPese);
    }


	// 06.07 mm - Differenciation des tolerances article +/-
	double toleranceArticleNegative = 0.0;
	double toleranceArticlePositive = 0.0;

	// mm 05.10 - % de tolérance article au niveau de la nomenclature
	if (m_data->getCurrentComposant() != NULL)
	{
		toleranceArticleNegative = m_data->getCurrentComposant()->getToleranceArticleNegative();
		toleranceArticlePositive = m_data->getCurrentComposant()->getToleranceArticlePositive();
	}

	if (toleranceArticleNegative == 0 && toleranceArticlePositive ==0 && 
		getBalanceChoisie() != NULL)
	{
		toleranceArticleNegative = getBalanceChoisie()->getTolerance();
		toleranceArticlePositive = getBalanceChoisie()->getTolerance();
	}


    // sr 10.04 maintenant les matières de rectifs sont gérées comme les autres mais pas
    // de notion de tolerance
    if ((m_data->getCurrentComposant()->getCodeAServir()==8)
    ||  (m_data->getCurrentComposant()->getCodeAServir()==9))
    {
        toleranceArticleNegative = 0.0;
		toleranceArticlePositive = 0.0;
    }



	double origine ;
	// 113445 mm 06.2016
	double _qtebesoinPrevue = 0.0;	
	if ( m_data->getCurrentComposant()->getGestionStock() == 3 && m_data->getCurrentComposant()->getTitreTheo())	// component with potency
		_qtebesoinPrevue	= m_data->getCurrentComposant()->getQuantitePrevue()
							/ (m_data->getCurrentComposant()->getTitreTheo()/100);
	else
		_qtebesoinPrevue	= m_data->getCurrentComposant()->getQuantitePrevue();

		
	if (_peseeParConsigne)
    { 
		origine = 0;
	    weightMin = origine - _totalAPeserInitial * toleranceArticleNegative/100;
	    weightMax = origine + _totalAPeserInitial * toleranceArticlePositive/100;
    }
	else
    {
       getJaugePesee()->setValue(_poidsDejaPese);
       if (_attenteTarage == true)
       {
		    origine	= weighingInterface->getWeight(); 
			// 113445 mm 06.2016
			if (m_data ->getApplicationTolerance()== 1)
			{
				weightMin = origine - weighingInterface->getWeight() * toleranceArticleNegative/100;
				weightMax = origine + weighingInterface->getWeight() * toleranceArticlePositive/100;
			}
			else
			{
				weightMin = origine - _qtebesoinPrevue * toleranceArticleNegative/100;
				weightMax = origine + _qtebesoinPrevue * toleranceArticlePositive/100;
			}
       }
       else
       { 
			origine	= _totalAPeserInitial;	
		    if (m_data ->getApplicationTolerance()== 1)
			{
				weightMin = origine - _totalAPeserInitial * toleranceArticleNegative/100;
				weightMax = origine + _totalAPeserInitial * toleranceArticlePositive/100;
			}
			else
			{
				weightMin = origine - _qtebesoinPrevue * toleranceArticleNegative/100;
				weightMax = origine + _qtebesoinPrevue * toleranceArticlePositive/100;
			}
       } 
    }
	//113445 mm 06.2016 - use of setter
	setWeightMin( weightMin);
	setWeightMax( weightMax);

	IlvPalette* palette = getJaugePesee()->getPalette();
	IlvColor* foreground;
	//113445 mm 06.2016 - use of getter
	//if (_poidsDejaPese < weightMin)
	if (_poidsDejaPese < getWeightMin())
	{
		foreground = getDisplay()->getColor("yellow");
	}
    else
    {
       // Pour les matières de rectif des que le poids prevu est atteint on est dans le vert
       if ((m_data->getCurrentComposant()->getCodeAServir()==8)
       ||  (m_data->getCurrentComposant()->getCodeAServir()==9))
       {
		    foreground = getDisplay()->getColor("green");
       }
       // Pour les autres on est soit en rouge soit en vert
       else
       { 
        	//if (_poidsDejaPese > weightMax) 
		    if (_poidsDejaPese > getWeightMax()) 
    	    {
                foreground = getDisplay()->getColor("red");
	        }
	        else
	        {
		        foreground = getDisplay()->getColor("green");
	        }
       }
    }   
	// gbe On colore le texte de poids
	getSaisiePoidsPese()->getPalette()->setForeground(foreground);
	// gbe le poids cumulé évolue aussi avec la coloration
	this->getAffPoidsCumule()->getPalette()->setForeground(foreground);
	//sr 01.12 afficher après coloration
	bufferedDraw(getAffPoidsCumule());
	// fin gbe
	palette->setForeground(foreground);
	getJaugePesee()->setPalette(palette);
	bufferedDraw(getJaugePesee());
	//113445 mm 06.2016 - Already done with setter
	//_weightMin = weightMin;
	//_weightMax = weightMax;
	drawScaleLines();
}

void AdxPesee_OF::drawScaleLines()
{
	IlvRectangularGauge* jauge = getJaugePesee();
	IlvRect jaugeBBox;
	IlvPoint start;
	IlvPoint stop;
	char wChLabel[30];
	const char* format;
	IlvDim rectW = 70;
	IlvDim rectH = 13;
	IlvRect drawRectMax;
	IlvRect drawRectInitial;
	IlvRect drawRectMin;

	jauge->boundingBox(jaugeBBox,this->getTransformer());
	if(_totalAPeserInitial > 0)
	{
		// on dessine la bare du poids
		IlvDim lineY = jaugeBBox.getH()-(jaugeBBox.getH()/1.25) + jaugeBBox.getY();
		start.setX(jaugeBBox.getX());
		start.setY(lineY);
		stop.setX(jaugeBBox.getX()+jaugeBBox.getW()+10);
		stop.setY(lineY);
		IlvColor* color = getDisplay()->getColor("black");
		IlvPalette* palette = NULL;
	    palette = getDisplay()->getPalette(color,//background 
										 color,//foreground 
										 0,//pattern 
										 0,//colorPattern 
										 0,//font 
										 0,//lineStyle 
										 2,//lineWidth 
										 IlvFillPattern,//fillStyle 
										 IlvArcPie,//arcMode 
										 IlvEvenOddRule,//fillRule 
										 50);//alpha

		palette->lock();
		this->drawLine(palette,start,stop);
		if(_showTolerance == true)
		{
			drawRectInitial.setX(stop.getX() +1);
			drawRectInitial.setY(lineY-6);
			drawRectInitial.setH(rectH);
			drawRectInitial.setW(rectW);
			format = this->getJaugeScale()->getFormat();
			sprintf(wChLabel,format,_totalAPeserInitial);
			this->drawLabel(palette,wChLabel,-1,drawRectInitial,0,IlvLeft);
		}
		palette->unLock();
	}

	// 113445 mm 07.2016
	// if(_weightMax > 0)
	if (getWeightMax() > 0)
	{
		// on dessine la bare du poids
		IlvDim lineY = jaugeBBox.getH() - ((jaugeBBox.getH() * getWeightMax())/(_totalAPeserInitial * 1.25)) + jaugeBBox.getY();
		start.setX(jaugeBBox.getX());
		start.setY(lineY);
		stop.setX(jaugeBBox.getX()+jaugeBBox.getW()+10);
		stop.setY(lineY);
		IlvColor* color = getDisplay()->getColor("red");
		IlvPalette* palette = NULL;
	    palette = getDisplay()->getPalette(color,//background 
										 color,//foreground 
										 0,//pattern 
										 0,//colorPattern 
										 0,//font 
										 0,//lineStyle 
										 2,//lineWidth 
										 IlvFillPattern,//fillStyle 
										 IlvArcPie,//arcMode 
										 IlvEvenOddRule,//fillRule 
										 50);//alpha

		palette->lock();
		this->drawLine(palette,start,stop);
		if(_showTolerance == true)
		{
			drawRectMax.setX(stop.getX() +1);
			// Les libellés ne doivent pas se superposer 
			if(lineY-6+rectH > drawRectInitial.y())
			{
				//On décale le libellé
				drawRectMax.setY(drawRectInitial.y() - rectH);
			}
			else
			{
				drawRectMax.setY(lineY-6);
			}
			drawRectMax.setH(rectH);
			drawRectMax.setW(rectW);
			format = this->getJaugeScale()->getFormat();
			sprintf(wChLabel,format,getWeightMax());
			this->drawLabel(palette,wChLabel,-1,drawRectMax,0,IlvLeft);
		}
		palette->unLock();

	}
	// 113445 mm 07.2016
	//if(_weightMin > 0)
	if (getWeightMin()> 0)
	{
		// on dessine la bare du poids
		IlvDim lineY = jaugeBBox.getH() - ((jaugeBBox.getH() * getWeightMin())/(_totalAPeserInitial * 1.25)) + jaugeBBox.getY();
		start.setX(jaugeBBox.getX());
		start.setY(lineY);
		stop.setX(jaugeBBox.getX()+jaugeBBox.getW()+10);
		stop.setY(lineY);
		IlvColor* color = getDisplay()->getColor("yellow");
		IlvPalette* palette = NULL;
	    palette = getDisplay()->getPalette(color,//background 
										 color,//foreground 
										 0,//pattern 
										 0,//colorPattern 
										 0,//font 
										 0,//lineStyle 
										 2,//lineWidth 
										 IlvFillPattern,//fillStyle 
										 IlvArcPie,//arcMode 
										 IlvEvenOddRule,//fillRule 
										 50);//alpha

		palette->lock();
		this->drawLine(palette,start,stop);
		if(_showTolerance == true)
		{
			drawRectMin.setX(stop.getX() +1);
			// Les libellés ne doivent pas se superposer 
			if(lineY-6 < drawRectInitial.y() + rectH)
			{
				//On décale le libellé
				drawRectMin.setY(drawRectInitial.y() + rectH);
			}
			else
			{
				drawRectMin.setY(lineY-6);
			}
			drawRectMin.setH(rectH);
			drawRectMin.setW(rectW);
			format = this->getJaugeScale()->getFormat();
			sprintf(wChLabel,format,getWeightMin());
			this->drawLabel(palette,wChLabel,-1,drawRectMin,0,IlvLeft);
		}
		palette->unLock();

	}
}
void AdxPesee_OF::draw(const IlvRegion* region)
{
	IlvContainer::draw(region);
}
void AdxPesee_OF::draw(IlvPort* dst,
					  const IlvTransformer* t ,
					  const IlvRegion* clip)
{
	IlvContainer::draw(dst,t,clip);
}
void AdxPesee_OF::reDraw(const IlvRegion* region)
{
	IlvContainer::reDraw(region);
	drawScaleLines();
}
void AdxPesee_OF::reDraw(const IlvRect* rect)
{
	IlvContainer::reDraw(rect);
	drawScaleLines();
}

//---------------------------------------------------------------------------
// sr 03.04 revu pour initialiser l'échelle par rapport au poids total à peser
void AdxPesee_OF::adaptationEchelle()
{
	if (_peseeParConsigne)
	{
		getJaugePesee()->setMin(- _totalAPeserInitial);
		getJaugePesee()->setMax(_totalAPeserInitial * 0.25);
		getJaugeScale()->setMin(- _totalAPeserInitial);
		getJaugeScale()->setMax(_totalAPeserInitial * 0.25);
	}
		else
	{
		getJaugePesee()->setMin(0);
		getJaugePesee()->setMax(_totalAPeserInitial * 1.25);
		getJaugeScale()->setMin(0);
		getJaugeScale()->setMax(_totalAPeserInitial * 1.25);
	}

	bufferedDraw(getJaugeScale());
	drawScaleLines();

}

//---------------------------------------------------------------------------
bool AdxPesee_OF::propositionLot()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	// SR 07.07
    //double _totalAPeserUs;
    _lotOK = IlvFalse;
    
	IlList* lotList = m_data->getLotList();
	AdxLot* lot;

// La proposition des lots doit se faire dans l'ordre d'extraction	
	int i = 0;
	while ( i < m_data->getNbLots())
	{
		lot = m_data->getLot(i);
        if (lot->getQuantiteAllouee() > 0) 
		{
			if ( !m_data->getComposantBegin() )
				setTitreSlo(lot->getTitre());
           	int indexLotSvg = m_data->getCurrentLotIndex();
			m_data->setCurrentLotIndex(i);
			/*  SR 07.07 à valider par RCA : ne pas laissser le lot a blanc
            //poids à peser > au poids alloué
            // si dernier lot alloué on ne porpose pas le lot pour obliger l'utilisateur
            // à aller allouer
            if (lookLot()) 
            {

               if (m_data->getCurrentComposant()->getGestionStock() == 3			// composant a titre
			   && m_data->getCurrentComposant()->getTitreTheo() != 0)
               {
	    		    _totalAPeserUs = _totalAPeser * m_data->getCurrentComposant()->getTitreTheo()
        					/ m_data->getCurrentLot()->getTitre();
               }
               else 
               {
                    _totalAPeserUs = _totalAPeser;
               }
               if ((_totalAPeserUs > m_data->getCurrentLot()->getQuantiteAllouee())
                && (m_data->getCurrentLot()->getQuantiteDisponible() > m_data->getCurrentLot()->getQuantiteAllouee())) 
               {       
		        m_data->setCurrentLotIndex(indexLotSvg);                   
                _stockReelInfInfo = true;
                return _lotOK;
               }
            }
			Fin SR 07.07
			*/
   			m_data->getLotBegin();
			//91927 mm 08.13 - changer d'allocation doit rester possible dans ce contexte
			if (m_data->getAllocationAutoCode() == 2 
				&& m_data->getPrioriteAllocationCode()== 1
				&& ! m_data->getCurrentComposant()->getQuantiteAlloueeDpOF() ) 
				 _stockReelInfInfo = true;

			_lotOK = true;
			return _lotOK;
		}
		i++;
	}
    // on n'a pas trouve de lot alloué et il reste une quantité à peser
    // positionnement de_stockReelInfInfo afin de pouvoir aller allouer sur un autre lot    
    _stockReelInfInfo = true;
	// mm 04.11 - modif liée au magasin avancé  
	// on a pesé tous les lots alloués dp l'OF, _quantiteAlloueeDpOF passe donc à 0
	if ( m_data->getCurrentComposant()->getQuantiteAlloueeDpOF() !=0 )
	{
		 m_data->getCurrentComposant()->setQuantiteAlloueeDpOF(0); 
		 m_data->getCurrentComposant()->setQuantiteAlloueeRestante(0); 
		 m_data->getCurrentComposant()->setQuantiteAlloueeTheorique(0); 
	}
    return _lotOK;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::attenteSaisieLot()
{
//	setRecipientChoisi(NULL);
//	setBalanceChoisie(NULL);
	if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
	{
		getSaisieCuve()->setEditable(true);
		getSaisieVanne()->setEditable(true);
		setFocus(getSaisieCuve());
	}
	else
	{
		getSaisieLot()->setEditable(true);
		getSaisieEmplacement()->setEditable(true);
		setFocus(getSaisieLot());
	}
	getmettreAZero()->setSensitive(false);
	gettarer()->setSensitive(false);
	// APCPRD-2636 mm 08.2013 - bt peser doit rester actif tant que recontrole non fait
	// si tare récipient = 0, emballage interne, mode déconnecté
	if ((_recontroleFait == false)&&
		( _recipientChoisi != NULL) &&
		(_recipientChoisi->getTypeRecipient() == 1) &&
		( _recipientChoisi->getTareTheo() ==0 ) &&
	    ( ! _balanceChoisie->getConnecte())) 
	{
		getpeser()->setSensitive(true);
	}
	else
		getpeser()->setSensitive(false);
	getvalider()->setSensitive(false);


// affichage des zones numeriques a zero
	_totalAPeser = getInterface()->getDonnees()->getCurrentComposant()->getQuantiteTheorique();
	getAffTotalAPeser()->setValue(_totalAPeser);
	bufferedDraw(getAffTotalAPeser());
	_poidsPese = 0;
	getSaisiePoidsPese()->setValue(_poidsPese);
	bufferedDraw(getSaisiePoidsPese());
	_poidsEncours = 0;
// sr 20/04
//	getJaugePesee()->setValue(_poidsPeseTotal);
//	bufferedDraw(getJaugePesee());
	if (_tarageOK == false)
		_poidsTare = 0;
	getAffTare()->setValue(_poidsTare);
	bufferedDraw(getAffTare());
}

//---------------------------------------------------------------------------
void AdxPesee_OF::attenteSaisieRecipient()
{
	setRecipientChoisi(NULL);
	setBalanceChoisie(NULL);
	setFocus(getSaisieRecipient());
	getmettreAZero()->setSensitive(false);
	gettarer()->setSensitive(false);
	getpeser()->setSensitive(false);
	getvalider()->setSensitive(false);
}

//---------------------------------------------------------------------------
void AdxPesee_OF::attenteSaisieBalance()
{
	setBalanceChoisie(NULL);
	setFocus(getSaisieBalance());
	getmettreAZero()->setSensitive(false);
	gettarer()->setSensitive(false);
	getpeser()->setSensitive(false);
	getvalider()->setSensitive(false);
}

//---------------------------------------------------------------------------
void AdxPesee_OF::setChampsAlphaEditable(bool editable)
{
	if (editable == false)
	{
		getSaisieCuve()->setEditable(editable);
		getSaisieVanne()->setEditable(editable);
		getSaisieLot()->setEditable(editable);
		getSaisieSousLot()->setEditable(editable);		// mm 05.10 - distinction lot/slo
		getSaisieEmplacement()->setEditable(editable);
	}
	else
		if (getInterface()->getDonnees()->getModifLigneStockCode() != 1)  // modifiable
		{
			if (getInterface()->getFonctionEnCours() == 3
			&& getInterface()->getPeseeEnCuve())
			{
				getSaisieCuve()->setEditable(editable);
				getSaisieVanne()->setEditable(editable);
			}
			else
			{
				getSaisieLot()->setEditable(editable);
				getSaisieSousLot()->setEditable(editable);		// mm 05.10 - distinction lot/slo
				getSaisieEmplacement()->setEditable(editable);
			}
		}
		else
		{	
			if (getInterface()->getFonctionEnCours() == 3
			&& getInterface()->getPeseeEnCuve())
			{
				getSaisieCuve()->setEditable(false);
				getSaisieVanne()->setEditable(false);
			}
			else
			{
				getSaisieLot()->setEditable(false);
				getSaisieSousLot()->setEditable(false);		// mm 05.10 - distinction lot/slo
				getSaisieEmplacement()->setEditable(false);
			}
		}
	getSaisieRecipient()->setEditable(editable);
	getSaisieBalance()->setEditable(editable);
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::propositionRecipient()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();


// 02.09 mm - Restauration de la valeur de la tareThéo du _recipientChoisi
	if (_recipientChoisi !=	NULL)
	{
		if ((_recipientChoisi->getTypeRecipient() == 2) && (_recipientChoisi->getTareModifiable()==2 ))
			_recipientChoisi->setTareTheo(_recipientChoisi->getTareTheoSvg());
	}

// capacite demandee au recipient selon pesee pas ecart ou cumulee
	double PoidsAPeser;
	if (_peseeParEcart)
		PoidsAPeser = _poidsAPeser;
	else
		PoidsAPeser = _totalAPeser;
	_recipientOK = IlvFalse;
// pas de proposition automatique de recipient pour recipient mixte
	if (m_data->getCurrentFicheISM()->getCodeEmballage() == 1 ||
		m_data->getCurrentFicheISM()->getCodeEmballage() == 2 )
	{
		//capacite du dernier recipient retenu exprimee en unite composant
		double capaciteOK = 0;
		double capaciteRecipient;
		AdxRecipient* recipient;
		IlList* recipientList = m_data->getRecipientList();
		for (int i = 0; i < m_data->getNbRecipients(); i++) 
		{
			recipient = (AdxRecipient*)(*recipientList)[i];
// controle du type de recipient
			if (recipient->getTypeRecipient() ==  
				m_data->getCurrentFicheISM()->getCodeEmballage())
			{
//controle de la capacite du recipient
				capaciteRecipient = m_data->convertir(
					recipient->getPoidsMaxi(),
					recipient->getUnitePoids(),
					m_data->getCurrentComposant()->getUnite());
				if (capaciteRecipient >= PoidsAPeser)
					if (capaciteOK == 0)
					{
						capaciteOK = capaciteRecipient;
						setRecipientChoisi(recipient);
						_recipientPrevu = _recipientChoisi;
					}
					else
					{
						// sr 02.02
						// si plusieurs récipients peuvent convenir et que
						// récipient fournisseur on remet à 0 et on va voir après
						if ((capaciteRecipient == capaciteOK) & 
						   (recipient->getTypeRecipient() == 2))
						{
							// sr 04.02 Fiche incident n 18
//							capaciteOK = 0;
							setRecipientChoisi(NULL);
						}
						else
						{
							if (capaciteRecipient < capaciteOK)
							{
							capaciteOK = capaciteRecipient;
							setRecipientChoisi(recipient);
							_recipientPrevu = _recipientChoisi;
							}
						}
					}
			}
		}
		// sr 04.02 Fiche incident n 18
		if ( (capaciteOK != 0) & (getRecipientChoisi() != NULL) )
			_recipientOK = true;
	}
	return _recipientOK;
}

//---------------------------------------------------------------------------
// quelques soit le mode de peser la balance est proposee pour qu elle puisse peser 
// le besoin composant (_totalAPeser)  seulement si pesée cumulée
// sr 02.02 Si pesée cumulée on travaille avec _totalAPeser
//			Si pesée par écart on travaille avec _poidsAPeser
//			On passe par une variable de travail PoidsAPeser
// sinon il est ensuite controle qu'elle peut peser le lot en cours (_poidsAPeser) en
//  une seule fois pour recalculer eventuellement _poidsAPeser de pesee partielle
//---------------------------------------------------------------------------
bool AdxPesee_OF::propositionBalance()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
	_balanceOK = false;


	if (_recipientChoisi->getNbBalances() == 0)
	{
		setBalanceChoisie(NULL);
		return _balanceOK;
	}
// il y a des balance dans la liste verifiant porteMini<=tareTheo<=tareMaxi

	IlList* balanceList = _recipientChoisi->getBalanceList();
	AdxBalance* balance;
	const char* uniteComposant = m_data->getCurrentComposant()
		->getUnite();
	const char* uniteRecipient = _recipientChoisi->getUnitePoids();
	double PorteeMaxi;
	double TareTheoRecipient = m_data->convertir(
		_recipientChoisi->getTareTheo(),
		uniteRecipient,
		uniteComposant);
	double ToleranceRecipient = _recipientChoisi->getTolerance();

// sr 02.02 Selon le mode de pesée on travaille avec totalAPeser ou PoidsAPeser
	double PoidsAPeser;
	if (_peseeParEcart == false)
	{
		PoidsAPeser = _totalAPeser;
	}
	else
	{
		PoidsAPeser = _poidsAPeser;
	}
 
// recherche de la premiere balance non a etalonner disponible
	int i = 0;
	for ( i = 0; i < _recipientChoisi->getNbBalances() ; i++)
	{
	setBalanceChoisie((AdxBalance*)(*balanceList)[i]);
	if (_balanceChoisie->getEtalonnee() == true)
		break;
	}
// aucune balance non a etalonner trouvee
	if (i == _recipientChoisi->getNbBalances())
		return _balanceOK;

	_balancePrevue = _balanceChoisie;
	_balanceOK = true;
	double PorteeMaxiOK = m_data->convertir(
		_balanceChoisie->getPorteeMaxi(),
		_balanceChoisie->getUnite(),
		uniteComposant);

	i++;
// recherche la balance active la mieux adaptee au poids à peser 
//	les balances avant i ne peuvent etre selectionnees car a etalonner
	for (i ; i < _recipientChoisi->getNbBalances() ; i++)
	{
		balance = (AdxBalance*)(*balanceList)[i];
		if (balance->getEtalonnee() == true)
		{
			PorteeMaxi = m_data->convertir(
				balance->getPorteeMaxi(),
				balance->getUnite(),
				uniteComposant);
			if (PorteeMaxi >= (((1 + ToleranceRecipient/100) * TareTheoRecipient) + PoidsAPeser))
			{
				if (PorteeMaxiOK >=  (((1 + ToleranceRecipient/100) * TareTheoRecipient) + PoidsAPeser))
				{
					if (PorteeMaxiOK >= PorteeMaxi)
					{
						setBalanceChoisie(balance);
						_balancePrevue = _balanceChoisie;
						PorteeMaxiOK = PorteeMaxi;
					}
				}
				else
				{
					setBalanceChoisie(balance);
					_balancePrevue = _balanceChoisie;
					PorteeMaxiOK = PorteeMaxi;
				}
			}
			else
			{
				if (PorteeMaxi > PorteeMaxiOK )
				{
					setBalanceChoisie(balance);
					_balancePrevue = _balanceChoisie;
					PorteeMaxiOK = PorteeMaxi;
				}
			}
		}
	}

	getSaisieBalance()->setLabel(_balanceChoisie->getBalance());

// pour une pesee cumulee la portee doit être suffisante pour la totalite
	if (_peseeParEcart == false)
	{
		if (PorteeMaxiOK < (((1 + ToleranceRecipient/100) * TareTheoRecipient) + _totalAPeser))
		{
			_peseeParEcart = true;
			if (propositionRecipient())
			{
				suiteChoixRecipient();
				return _balanceOK;
			}
		 	else
			{
				setBalanceChoisie(NULL);
				PorteeMaxiOK = 0;
				_balanceOK = false;
				return _balanceOK;
			}
		}
		else
			return _balanceOK;
	}

// la balance peut-elle peser le poids du lot en une seule fois?
	if (PorteeMaxiOK < (((1 + ToleranceRecipient/100) * TareTheoRecipient) + _poidsAPeser))
// le poids sera pese en plusieurs fois : calcul du poids a peser
	{
		_poidsAPeser = PorteeMaxiOK - ((1 + ToleranceRecipient/100) * TareTheoRecipient);
		getAffPoidsAPeser()->setValue(_poidsAPeser);
		bufferedDraw(getAffPoidsAPeser());
//         adaptationEchelle();
		_peseeLimiteeParBalance = true;
	}
	return _balanceOK;
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::controleLot()
{


// mettre a jour _lotOK
	_lotOK = false;
	AdxInterface* m_interface = getInterface();

// Contrôle que le lot est alloué
	if (m_interface->getDonnees()->getCurrentLot()->getQuantiteAllouee() == 0)
		return _lotOK;
// sr 03.04 si le paramètre dit modif lot avec controle ET lot choisi n'est pas complètement 
// alloué pour cette MP, on controle qu'il ne reste pas des lots complètement alloués à peser
// si oui alors message d'erreur
    if(m_interface->getDonnees()->getModifLigneStockCode() == 2 
    && m_interface->getDonnees()->getCurrentLot()->getQuantiteReelDispo() != 0)
    {
    	IlList* lotList = m_interface->getDonnees()->getLotList();
        AdxLot* lot2;
	    for (int i = 0; i < m_interface->getDonnees()->getNbLots(); i++)
	    {
	    	lot2 = (AdxLot*)(*lotList)[i];
		    if ((lot2->getQuantiteReelDispo() == 0) &(lot2->getQuantiteAllouee() != 0))
		    {
    		    envoieMessage("&LotPartiellementAlloue", false);
			    return _lotOK;
		    }
	    }

    }

	
    _lotOK = true;
    return _lotOK;
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::controleEmplacement()
{
/*
	AdxInterface* m_interface = getInterface();*/
	return true;
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::controleRecipient()
{	
	_recipientOK = false;
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
//inutile de choisir le recipient si le lot n'est pas valide
	if (_lotOK == false)
		return _recipientOK;
// controle du type de recipient
	if (_recipientChoisi->getTypeRecipient() == 2 && 
		m_data->getCurrentFicheISM()->getCodeEmballage() == 1)
		return _recipientOK;
	if (_recipientChoisi->getTypeRecipient() == 1 && 
		m_data->getCurrentFicheISM()->getCodeEmballage() == 2)
		return _recipientOK;

// 11.07 mm - modif mode de pesee en emb.mixte	
/*	if (m_data->getCurrentFicheISM()->getCodeEmballage() == 3	 &&	// emballage mixte
		m_data->getCurrentFicheISM()->getModePeseeCode() == 2	 &&	// mode de pesee = cumulee
		_recipientChoisi->getTypeRecipient() == 2 )			// type recipient = fournisseur		
			_peseeParEcart = true;
*/
//  10.11 mm - le flag _peseeParEcart reste à true même si on remplace l'emb. fournisseur
// par un emb. interne
	if (m_data->getCurrentFicheISM()->getCodeEmballage() == 3	 &&	// emballage mixte
		m_data->getCurrentFicheISM()->getModePeseeCode() == 2)
	{
		if (_recipientChoisi->getTypeRecipient() == 2 )	
			_peseeParEcart = true;
		else 
		{
			_peseeParEcart = false;
			_attenteTarage = false;
		}
	}

// controle de la capacite du recipient
	// capacite demandee au recipient selon pesee pas ecart ou cumulee
	double	poidsAPeserConverti;
	if (_peseeParEcart)
		poidsAPeserConverti = getInterface()->getDonnees()->convertir(
			_poidsAPeser,
			m_data->getCurrentComposant()->getUnite(),
			_recipientChoisi->getUnitePoids());
	else
		poidsAPeserConverti = getInterface()->getDonnees()->convertir(
			_totalAPeser,
			m_data->getCurrentComposant()->getUnite(),
			_recipientChoisi->getUnitePoids());
	if (_recipientChoisi->getPoidsMaxi() >= poidsAPeserConverti)
		_recipientOK = true;		
	return _recipientOK;
}

//---------------------------------------------------------------------------
// Il faut contrôler qu'il y a assez de place dans le récipient pour pouvoir 
// y ajouter une matiere de plus.
bool AdxPesee_OF::controleRecipientMulti()
{
	AdxData* m_data = getInterface()->getDonnees();
	_recipientOK = false;
	//inutile de choisir le recipient si le lot n'est pas valide
	if (_lotOK == false)
		return _recipientOK;
	// contrôle capacité récipient suffisante
	// capacité du récipient > _poidsMatDejaPese + _poidsMaxTolere nouveau composant
	double wpoidsMaxTolere = 0.0;
	// conversion de _weightMax  en UP Mat1 si besoin
	if (strcmp (m_data->getCurrentComposant()->getUnite(), getUnitePoidsMat1())!= 0)
		wpoidsMaxTolere = m_data->convertir(_weightMax,
			m_data->getCurrentComposant()->getUnite(),getUnitePoidsMat1());
	else
		wpoidsMaxTolere = _weightMax;  

	// conversion du _poidsMaxi du récipient si son unité est != de  UP Mat1
	double wcapaciteRecipient = 0.0 ;
	if (strcmp(_recipientMulti->getUnitePoids(), getUnitePoidsMat1())!= 0)
		wcapaciteRecipient = m_data->convertir( _recipientMulti->getPoidsMaxi(),
			_recipientMulti->getUnitePoids(),getUnitePoidsMat1());
	else
		wcapaciteRecipient = _recipientMulti->getPoidsMaxi();

	// maintenant, tous les poids st exprimés en UP de Mat1
	if	( wcapaciteRecipient >= getPoidsMatDejaPese() + wpoidsMaxTolere)
		 _recipientOK = true ;

	return _recipientOK;
}


//---------------------------------------------------------------------------
// sr 01.12 APCPRD-728 Il faut contrôler que le récipient utilise
// est prevu pour la matiere a peser suivante
bool AdxPesee_OF::controleRecipientPrevu()
{
	AdxData* m_data = getInterface()->getDonnees();
	IlList* ficheISMRecipientList = m_data->getFicheISMRecipientList();
	_recipientOK = false;

	for (int i = 0; i < m_data->getNbFichesISMRecipient(); i++) 
	{
		AdxFicheISMRecipient* ficheISMRecipient
			= (AdxFicheISMRecipient*)(*ficheISMRecipientList)[i];
		// le recipient choisi est-il associé a la fiche ISM de l'article suivant
		if ((strcmp(ficheISMRecipient->getFicheISMRecipient(),m_data->getCurrentComposant()->getFicheISM()) == 0)
		&& (strcmp(ficheISMRecipient->getRecipient(),_recipientMulti->getRecipient()) == 0))
		{
			_recipientOK = true ;
			return _recipientOK;
		}
	}
	return _recipientOK;
}
//---------------------------------------------------------------------------
// la balance est controlee par rapport au poids du lot (_poidsAPeser) pour limiter 
// les risques de changement de balance.
// il ne doit pas etre controle que la balance est a etalonne quand on ne fait 
// qu'essayer de la maintenir, cad si pourChangement == false
//---------------------------------------------------------------------------
bool AdxPesee_OF::controleBalance(bool pourChangement)
{
// mettre a jour _balanceOK
	AdxInterface* m_interface = getInterface();

	_balanceOK = IlvFalse;

//inutile de choisir balance si le lot ou recipient pas valides
	if (_lotOK == false || _recipientOK == false)
		return _balanceOK;

// 02.09 mm - en cas de récipient fournisseur + tare modifiable, réinitialiser la tareTheo
	if ((_recipientChoisi->getTypeRecipient() == 2) && (_recipientChoisi->getTareModifiable()==2 ))
		_recipientChoisi->setTareTheo(_recipientChoisi->getTareTheoSvg());
	
// Controle de la balance par rapport au recipient choisi
	if (_recipientChoisi->getNbBalances() == 0)
	{
		setBalanceChoisie(NULL);
		getSaisieBalance()->setLabel("");
		envoieMessage("&AucuneBalanceValide", false);
		return _balanceOK;
	}
// il y a des balances dans la liste verifiant porteMini<=tareTheo<=tareMaxi

// verif que la balance active est dans la liste des balances du recipient
	IlList* balanceList = _recipientChoisi->getBalanceList();
	AdxBalance* balance;
	int i = 0;
	for ( i = 0; i < _recipientChoisi->getNbBalances() ; i++)
	{
		balance = (AdxBalance*)(*balanceList)[i];
		if (strcmp (balance->getBalance(), _balanceChoisie->getBalance()) == 0)
			break;
	}
	if (i >= _recipientChoisi->getNbBalances())
		return _balanceOK;

// quand on essaie une nouvelle balance on ne propose pas une qui est en attente d'etalonnage
	if (pourChangement && balance->getEtalonnee() == false)
	{
		// mm 02.09 - Avertir que la balance est indisponible car à étalonner
		char* message = new char[80];		
		sprintf(message,"%s   %s" ,
			balance->getBalance(),
			IlvGetMessage(m_interface->getDisplay(), "&BalanceAEtalonner")) ;
		envoieMessage(message,false);
		delete [] message;	// mm 06.09
		return _balanceOK;
	}

// la balance choisie est acceptable
	_balanceOK = true;
// la balance peut peser le poids du lot en une seule fois
	const char* uniteComposant = getInterface()->getDonnees()->getCurrentComposant()
		->getUnite();
	const char* uniteRecipient = _recipientChoisi->getUnitePoids();
	double PorteeMaxi = getInterface()->getDonnees()->convertir(
		_balanceChoisie->getPorteeMaxi(),
		_balanceChoisie->getUnite(),
		uniteComposant);
	double TareTheoRecipient = getInterface()->getDonnees()->convertir(
		_recipientChoisi->getTareTheo(),
		uniteRecipient,
		uniteComposant);
	double ToleranceRecipient = //getInterface()->getDonnees()->convertir(
		_recipientChoisi->getTolerance();
		//uniteRecipient,
		//uniteComposant);
	_peseeLimiteeParBalance = false;
	if (_peseeParEcart)
	{
		if (PorteeMaxi < (((1 + ToleranceRecipient/100) * TareTheoRecipient) + _poidsAPeser))
// le poids sera pese en plusieurs fois : calcul du poids a peser
		{
			_poidsAPeser = PorteeMaxi - ((1 + ToleranceRecipient/100) * TareTheoRecipient);
			getAffPoidsAPeser()->setValue(_poidsAPeser);
			bufferedDraw(getAffPoidsAPeser());
			_peseeLimiteeParBalance = true;
		}
		// 02.09 mm - Problème de recalcul du poids à peser en cas de changement de balance
		if (getInterface()->getDonnees()->getLotBegin() == false  &&	_peseeLimiteeParBalance == false)
		{
			if (getInterface()->getDonnees()->getCurrentComposant()->getGestionStock() == 3			// composant a titre
				&& getInterface()->getDonnees()->getCurrentComposant()->getTitreTheo() != 0)
			{
				if (_totalAPeser * getInterface()->getDonnees()->getCurrentComposant()->getTitreTheo() <=
				getInterface()->getDonnees()->getCurrentLot()->getQuantiteAllouee() * 
				getInterface()->getDonnees()->getCurrentLot()->getTitre())
					_poidsAPeser = _totalAPeser * getInterface()->getDonnees()->getCurrentComposant()->getTitreTheo()
					/ getInterface()->getDonnees()->getCurrentLot()->getTitre();
				else
					_poidsAPeser = getInterface()->getDonnees()->getCurrentLot()->getQuantiteAllouee() ;
			}
			else
			{
				if (_totalAPeser <  getInterface()->getDonnees()->getCurrentLot()->getQuantiteAllouee())
					_poidsAPeser = _totalAPeser;
				else
					_poidsAPeser = getInterface()->getDonnees()->getCurrentLot()->getQuantiteAllouee() ;
			}
			getAffPoidsAPeser()->setValue(_poidsAPeser);
			bufferedDraw(getAffPoidsAPeser());
		}

	}
	else
	{
// pour une pesee cumulee la balance doit pouvoir peser le total
		if (PorteeMaxi < (((1 + ToleranceRecipient/100) * TareTheoRecipient) + _totalAPeser))
		{
			_balanceOK = false;
		}	
	}

	return _balanceOK;
}
//---------------------------------------------------------------------------
// En pesée multi-article, vérification que la balance utilisée lors de 
// la pesée du 1er article a une portée suffisante pour peser le cumul des poids = 
// _poidsTare + cumul des poidsDejaPeses + _poidsMaxTolere nouveau composant 

bool AdxPesee_OF::controleBalanceMulti()
{	
	AdxData* m_data = getInterface()->getDonnees();
	_balanceOK = false ;
	//inutile de choisir balance si le lot ou recipient pas valides
	if (_lotOK == false || _recipientOK == false)
		return _balanceOK;

	// contrôle portée balance suffisante
	//_poidsTare + cumul des poidsDejaPeses + _poidsMaxTolere nouveau composant
	// conversion portée maxi en UP de mat1
	double PorteeMaxi;				
	PorteeMaxi = m_data->convertir(
			_balanceMulti->getPorteeMaxi(),
			_balanceMulti->getUnite(),
			_UPMat1);

	// conversion de _weightMax  en UP Mat1 si besoin
	double _poidsMaxTolere = 0.0;
	if (strcmp(m_data->getCurrentComposant()->getUnite(),getUnitePoidsMat1()) != 0)
		_poidsMaxTolere = m_data->convertir(_weightMax,
			m_data->getCurrentComposant()->getUnite(),getUnitePoidsMat1());
	else
		_poidsMaxTolere = _weightMax;

	// maintenant, tous les poids st exprimés en UP de Mat1
	// pour une pesee cumulee la balance doit pouvoir peser le total
	// PorteeMaxi  <  TareTheoRecipient + _poidsMatDejaPese + _totalAPeserMax
	if (PorteeMaxi >=  _poidsTareMulti +_poidsMatDejaPese + _poidsMaxTolere)
	{
		_balanceOK = true;
	}

	return _balanceOK ;
}
//---------------------------------------------------------------------------
bool AdxPesee_OF::controleTare()
{
	AdxData* m_data = getInterface()->getDonnees();
	bool tareOK = false;
	double toleranceTare = _recipientChoisi->getTolerance();
	double tareTheo = m_data->convertir(_recipientChoisi->getTareTheo(),
				_recipientChoisi->getUnitePoids(),
				m_data->getCurrentComposant()->getUnite());
	// sr 11.02 si tare = 0 on ne demande pas de tarer et on continue
	if (tareTheo == 0)
	{
		tareOK = true;
		return tareOK;
	}
	if (_poidsTare > (tareTheo * (1 + toleranceTare/100)) ||
		_poidsTare < (tareTheo * (1 - toleranceTare/100)))
		return tareOK;
	tareOK = true;
	return tareOK;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::setRecipientChoisi(AdxRecipient* recipient)
{
	_recipientChoisi = recipient;
	// mm 06.10 - ajout libellé
	if (recipient == NULL)
	{
		getSaisieRecipient()->setLabel("");
		getLibSaisieRecipient()->setLabel("");
	}
	else
	{
		getSaisieRecipient()->setLabel(_recipientChoisi->getRecipient());
		getLibSaisieRecipient()->setLabel(_recipientChoisi->getLibRecipient());
	}
	bufferedDraw(getSaisieRecipient());
	bufferedDraw(getLibSaisieRecipient());
}

//---------------------------------------------------------------------------
void AdxPesee_OF::setBalanceChoisie(AdxBalance* balance)
{
	_balanceChoisie = balance;

	// mm 06.10 - ajout libellé
	if (balance == NULL)
	{
		getSaisieBalance()->setLabel("");
		getLibSaisieBalance()->setLabel("");
	}
	else
	{
		getSaisieBalance()->setLabel(_balanceChoisie->getBalance());
		getLibSaisieBalance()->setLabel(_balanceChoisie->getLibBalance());
	}
	bufferedDraw(getSaisieBalance());
	bufferedDraw(getLibSaisieBalance());
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::affecteBalance()
{
	AdxInterface* m_interface = getInterface();
	AdxAccueil* m_accueil = m_interface->getAccueil();
	AdxData* m_data = m_interface->getDonnees();
	AdxComposant* m_composant = m_data->getCurrentComposant();

	// 10.07 pesee en mode degrade selon la valeur de saisie Poids -
	// pesee en mode degrade, seulement en cas d'emballage fournisseur
	// et si le flag "saisie poids" a la valeur oui
	// ou si matiere geree en fabrication
	if ((_recipientChoisi->getTypeRecipient() == 2
		&& _recipientChoisi->getSaisiePoids() == 2 )
		|| m_composant->getCodeAServir() == 3	
		|| m_composant->getCodeAServir() == 5
		|| m_composant->getCodeAServir() == 7
		|| m_composant->getCodeAServir() == 9
		|| (m_composant->getCodeAServir() == 10 && m_interface->getFonctionEnCours() == 3))
		_balanceChoisie->setConnecte(0);

	else
		// si aucune balance connectée, on s'épargne le test de connexion
		if (m_accueil->getNbConnecte() == 0)
			_balanceChoisie->setConnecte(0);
		else 
			_balanceChoisie->setConnecte(1);


	m_interface->getWeighingInterface()->setBalance(_balanceChoisie);

	if (_balanceChoisie->getConnecte() == 1)
	{
		// recontrole connexion toujours active
		m_interface->getWeighingInterface()->connectionTest(_balanceChoisie, true);
		if (_balanceChoisie->getConnecte() == 1)
			return true;
		else
			return false;
	}
	else
		return false;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::recontroleOF()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = m_interface->getDonnees();
    char* szTemp = new char[40];
	int j = 0;


	m_interface->getRecontrole_OF()->setPanneauAppelant(this);

	m_interface->getRecontrole_OF()->getAffNOF()
		->setLabel(m_data->getCurrentOrder()->getNumOF());
	m_interface->getRecontrole_OF()->getAffNPhase()
		->setValue((IlvDouble)m_data->getCurrentPhase()->getNumPhase());
	m_interface->getRecontrole_OF()->getAffNOF()->setTransparent(true);
	m_interface->getRecontrole_OF()->getAffNPhase()->setTransparent(true);

	// Si récupération du contenu du CAB dans une zone pour redécoupage - 103422 mm 01.2015
	if (m_data->getDecoupageCAB() == 1)
		setVisible(m_interface->getRecontrole_OF()->getSaisiContenuCab(), IlvFalse, IlvFalse);
	else
	{
		setVisible(m_interface->getRecontrole_OF()->getSaisiContenuCab(), IlvTrue, IlvFalse);
		// 114389 mm 02.2016
		m_interface->getRecontrole_OF()->getSaisiContenuCab()->setLabel("");
	}


	if (getInterface()->getFonctionEnCours() == 3
		&& getInterface()->getPeseeEnCuve())
	{
		// Si pesée en fabrication en cuve, la zone SaisiContenuCAB ne doit pas être visible - 108165 mm 05.2015
		setVisible(m_interface->getRecontrole_OF()->getSaisiContenuCab(), IlvFalse, IlvFalse);
		m_interface->getRecontrole_OF()->getSaisiContenuCab()->setActive(false);

		setVisible(m_interface->getRecontrole_OF()->getLibelleComposant(),IlvFalse, IlvFalse);
		setVisible(m_interface->getRecontrole_OF()->getSaisieComposant(),IlvFalse, IlvFalse);
		m_interface->getRecontrole_OF()->getSaisieComposant()->setActive(false);
		//m_interface->getRecontrole_OF()->setComposantOK(true);

		m_interface->getRecontrole_OF()->getLibelleLot()->setLabel(IlvGetMessage(getDisplay(), "&Cuve"));
		m_interface->getRecontrole_OF()
			->setFocus(m_interface->getRecontrole_OF()->getSaisieLot());
		// 03.10 mm - modification du recontrôle
		m_interface->getRecontrole_OF()->getSaisieLot()
			->setLabel("");
		m_interface->getRecontrole_OF()->setLotOK(false);

		setVisible(m_interface->getRecontrole_OF()->getLibelleSousLot(),IlvFalse, IlvFalse);
		setVisible(m_interface->getRecontrole_OF()->getSaisieSousLot(),IlvFalse, IlvFalse);	
		m_interface->getRecontrole_OF()->getSaisieSousLot()->setActive(false);
	}
	else
	{
		setVisible(m_interface->getRecontrole_OF()->getLibelleComposant(),IlvTrue, IlvFalse);
		setVisible(m_interface->getRecontrole_OF()->getSaisieComposant(),IlvTrue, IlvFalse);
		m_interface->getRecontrole_OF()->getSaisieComposant()->setActive(true);
		m_interface->getRecontrole_OF()->getSaisieComposant()
			->setLabel("");
		m_interface->getRecontrole_OF()->setComposantOK(false);

		m_interface->getRecontrole_OF()->getLibelleLot()->setLabel(IlvGetMessage(getDisplay(), "&Lot"));	
		m_interface->getRecontrole_OF()->getSaisieLot()
			->setLabel("");
		m_interface->getRecontrole_OF()->setLotOK(false);

		setVisible(m_interface->getRecontrole_OF()->getLibelleSousLot(),IlvTrue, IlvFalse);
		setVisible(m_interface->getRecontrole_OF()->getSaisieSousLot(),IlvTrue, IlvFalse);	
		m_interface->getRecontrole_OF()->getSaisieSousLot()->setActive(true);
		m_interface->getRecontrole_OF()->getSaisieSousLot()
			->setLabel("");
		m_interface->getRecontrole_OF()->setSousLotOK(false);
		// mm 03.10 - modification du recontrôle
		switch (m_data->getRecontroleArticleCode())
		{	
			case 2:	// recontrole seulement du lot
					m_interface->getRecontrole_OF()->getSaisieComposant()->setEditable(false);
					m_interface->getRecontrole_OF()->getSaisieSousLot()->setEditable(false);
					m_interface->getRecontrole_OF()->getSaisieComposant()->setActive(false);
					m_interface->getRecontrole_OF()->getSaisieSousLot()->setActive(false);
					m_interface->getRecontrole_OF()->getSaisieComposant()->setSensitive(false);
					m_interface->getRecontrole_OF()->getSaisieSousLot()->setSensitive(false);
					if (m_data->getDecoupageCAB() == 1)
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisieLot());
					else
						// mm 06.2015
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisiContenuCab());

					break;
			case 3: // recontrole du composant + lot
					m_interface->getRecontrole_OF()->getSaisieSousLot()->setEditable(false);
					m_interface->getRecontrole_OF()->getSaisieSousLot()->setActive(false);
					m_interface->getRecontrole_OF()->getSaisieSousLot()->setSensitive(false);
					if (m_data->getDecoupageCAB() == 1)
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisieComposant());
					else
						// mm 06.2015
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisiContenuCab());

					break;
			case 4: // recontrole lot + sous-lot
					m_interface->getRecontrole_OF()->getSaisieComposant()->setEditable(false);
					m_interface->getRecontrole_OF()->getSaisieComposant()->setActive(false);
					m_interface->getRecontrole_OF()->getSaisieComposant()->setSensitive(false);
					if (m_data->getDecoupageCAB() == 1)
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisieLot());
					else
					// mm 06.2015
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisiContenuCab());

					break;
			case 5: // recontrole du composant + lot + sous-lot
					if (m_data->getDecoupageCAB() == 1)
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisieComposant());
					else
						// mm 06.2015
						m_interface->getRecontrole_OF()
							->setFocus(m_interface->getRecontrole_OF()->getSaisiContenuCab());
					
					break;
		}
	}

	hide();
	m_interface->getRecontrole_OF()->show();

	return;
}

//---------------------------------------------------------------------------
bool AdxPesee_OF::envoieMessage(CString mess, bool OUINON)
{
	AdxInterface* m_interface = getInterface();
	m_interface->getMessage()->setPanneauAppelant(this);
	return (m_interface->envoieMessage(mess, OUINON));
}

//---------------------------------------------------------------------------
void AdxPesee_OF::consommationQuantite(bool finLot)
{
	AdxData* m_data = getInterface()->getDonnees();
// mm 05.10 - % de tolérance article au niveau de la nomenclature
	double tolerance = m_data->getCurrentComposant()->getToleranceArticleNegative();
    int _savLotIndex =  m_data->getCurrentLotIndex();
//envoie message solde emballage si besoin
	if(_soldeEmballage == true)
	{
		m_data->sendX3_SoldeEmballage();
	}

//envoie message mouvement d'inventaire en moins
    if (_redressement == true)
    {
      	m_data->sendX3_MajEmballage(2);
    }
//envoie message mouvement d'inventaire en moins sur dernière pesée en emballage fournisseur
    if (_redressementFin == true)
    {
      	m_data->sendX3_MajEmballage(4);
    }
// calcul du poids cumule pour la pesee en cours
	_poidsCumule = _poidsCumule + _poidsPese;

      // calcul des quantites du lot en cours
     // sr 07.05 tests Lyocentre même si redressement le stock n'est pas nul pour autant
    if((_redressement == true) & (m_data->getCurrentComposant()->getRedMod() == 1))
    {
	   		m_data->getCurrentLot()->setQuantiteDisponible(0);
		    m_data->getCurrentLot()->setQuantiteAllouee(0);
    }
    else
    {
			m_data->getCurrentLot()->setQuantiteDisponible(
    			m_data->getCurrentLot()->getQuantiteDisponible() - m_data->getCurrentLot()->getQuantiteAllouee());    	
		    m_data->getCurrentLot()->setQuantiteAllouee(0);	    
    }
    m_data->getCurrentLot()->setQuantiteTotale(m_data->getCurrentLot()->getQuantiteTotale() - _poidsPese);

    // calcul des quantites du composant en cours


	// qte prevue		non modifiee
	// qte restante		- qte act
	// qte theorique    - qte reelle au titre composant
	// qte allouee		- qte reelle
	// qte dispo		- qte reelle
	// qte consommee	+ qte reelle

	double quantiteActive;
	if (m_data->getCurrentComposant()->getGestionStock() == 3)
		quantiteActive = _poidsPese * m_data->getCurrentLot()->getTitre() / 100;
	else
		quantiteActive = _poidsPese;
	
	if (m_data->getCurrentComposant()->getQuantiteRestante() * (1 - tolerance/100)> quantiteActive)
		m_data->getCurrentComposant()->setQuantiteRestante(
			m_data->getCurrentComposant()->getQuantiteRestante() - quantiteActive);
	else
		m_data->getCurrentComposant()->setQuantiteRestante(0);
//-----
	double quantiteTheorique;
	if (m_data->getCurrentComposant()->getGestionStock() == 3)
		quantiteTheorique = quantiteActive / (m_data->getCurrentComposant()->getTitreTheo() / 100);
	else
		quantiteTheorique = quantiteActive;

	if (m_data->getCurrentComposant()->getQuantiteTheorique() * (1 - tolerance/100)> quantiteTheorique)
		m_data->getCurrentComposant()->setQuantiteTheorique(
			m_data->getCurrentComposant()->getQuantiteTheorique() - quantiteTheorique);
	else
		m_data->getCurrentComposant()->setQuantiteTheorique(0);
    
 //-----	
/*	if (m_data->getCurrentComposant()->getQuantiteAllouee() > _poidsPese)
		m_data->getCurrentComposant()->setQuantiteAllouee(
			m_data->getCurrentComposant()->getQuantiteAllouee() - _poidsPese);
	else
		m_data->getCurrentComposant()->setQuantiteAllouee(0);
//-----	
	if (m_data->getCurrentComposant()->getQuantiteDisponible() > _poidsPese)
		m_data->getCurrentComposant()->setQuantiteDisponible(
			m_data->getCurrentComposant()->getQuantiteDisponible() - _poidsPese);
	else
		m_data->getCurrentComposant()->setQuantiteDisponible(0);	*/
// il faut les recalculer a chaque fois pour gere les ecart avec stock info
	m_data->getCurrentComposant()->recalculeAlloueEtDisponible(m_data);
//-----
	// mm 02.11 - mise à jour de la quantité allouée théorique
	m_data->getCurrentComposant()->setQuantiteAlloueeTheorique(m_data->getCurrentComposant()->getQuantiteAllouee());
//-----
	m_data->getCurrentComposant()->setQuantiteConsommee(
		m_data->getCurrentComposant()->getQuantiteConsommee() + _poidsPese);
//-----
	// 93535 mm 10.2013 - maj de la QuantitePEC
	m_data->getCurrentComposant()->setQuantitePEC(m_data->getCurrentComposant()->getQuantitePEC()+ _poidsPese);

// avancement du compteur de pesees de la balance
	if (_balanceChoisie->getCodeCalibrage() > 2 )
	{
		_balanceChoisie->setNbPeseesCalibrage(_balanceChoisie->getNbPeseesCalibrage() + 1);
		if (((_balanceChoisie->getCodeCalibrage() == 3) 
					&& (_balanceChoisie->getNbPeseesCalibrage() == _balanceChoisie->getNbPesees()))
			|| ((_balanceChoisie->getCodeCalibrage() == 4) 
					&& (_balanceChoisie->getNbPeseesCalibrage() == _balanceChoisie->getNbPesees()))
			|| _balanceChoisie->getCodeCalibrage() == 5 )
		{
			if (_balanceChoisie->getEtalonnee() == true)
				m_data->setNbBalancesAEtalonner(m_data->getNbBalancesAEtalonner() + 1);
			_balanceChoisie->setEtalonnee(false);
		}

	}
}

//---------------------------------------------------------------------------
// si on n'annule pas la pesee vis a vis de la balance, la derniere pesee est consideree
// comme un tarage par le materiel
//---------------------------------------------------------------------------
void AdxPesee_OF::annulePesee()
{

	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
	WeighingOrder order;
	double tare = - _poidsPese;
// envoie des info de tarage a la balance pour remettre en place tare d'avant annulation
		order = CONS_TAR_M;
		weighingInterface->setWeighingOrder(order);

		weighingInterface->setTare(tare);
		weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
		weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();

//		_balanceChoisie->setUnite(weighingInterface->getResWeightUnit());

		weighingInterface->setResTare(tare);
	/*	if (weighingInterface->getResTare() != NULL)
		{
			getAffTare()->setValue(weighingInterface->getResTare());
			bufferedDraw(getAffTare());
		}*/
	/*	if (weighingInterface->getResWeighingMessage() != NULL)
		{*/
			getSaisiePoidsPese()->setValue(0.0);
			bufferedDraw(getSaisiePoidsPese());
			getJaugePesee()->setValue(_poidsPeseTotal);
			bufferedDraw(getJaugePesee());
			drawScaleLines();
	/*	}*/
//		peserCB(getpeser());
}


//---------------------------------------------------------------------------
// Annulation d'une tare invalide
//---------------------------------------------------------------------------
void AdxPesee_OF::annuleTarage()
{

	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();
//	WeighingOrder order;
//    double tare = 0;
         weighingInterface->initEcranBalance(_balanceChoisie);
/*
    // envoie des info de tarage a la balance pour remettre en place le RAZ
		order = CONS_TAR_M;
		weighingInterface->setWeighingOrder(order);

		weighingInterface->setTare(tare);
		weighingInterface->setWeightUnit(getUnitePoidsAPeser()->getLabel());
		weighingInterface->setResWeightUnit(_balanceChoisie->getUnite());

		weighingInterface->setPanneauAppelant(this);
		weighingInterface->weighingOrderTreatment();

//		_balanceChoisie->setUnite(weighingInterface->getResWeightUnit());

		weighingInterface->setResTare(tare);
	/*	if (weighingInterface->getResTare() != NULL)
		{
			getAffTare()->setValue(weighingInterface->getResTare());
			bufferedDraw(getAffTare());
		}*/
	/*	if (weighingInterface->getResWeighingMessage() != NULL)
		{
  */
  

			getSaisiePoidsPese()->setValue(0.0);
			bufferedDraw(getSaisiePoidsPese());
			getJaugePesee()->setValue(_poidsPeseTotal);
			bufferedDraw(getJaugePesee());
			drawScaleLines();
	/*	}*/
//		peserCB(getpeser());
}


//---------------------------------------------------------------------------
void AdxPesee_OF::envoiPeseePartielle()
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxComposant* composant;
	m_data->sendX3_PeseePartielle();
// calcul des quantites du lot en cours

// mm 06.09 - gestion déconditionnement/rompu, paramètre false passé à true
	consommationQuantite(true);					
	m_data->setOrderBegin(true);
	m_data->setPhaseBegin(true);
	m_data->getCurrentPhase()->setStatut(m_data->getCodeMatEnCoursPesee());
	m_data->getCurrentPhase()->setLibStatut(m_data->getLibMatEnCoursPesee());
	m_data->getCurrentOrder()->setStatut(m_data->getCodeOFEnCoursPesee());
	m_data->getCurrentOrder()->setLibStatut(m_data->getLibOFEnCoursPesee());
	m_data->setComposantBegin(true);
	m_data->setLotBegin(true);
	_balanceBegin = true;
	_peseeCumuleeForcee = false; // 11.07 mm - modif mode de pesee en emb.mixte

	// Performances, mm 04.2013 - en cas de pesée par article, la quantité restante doit être modifiée
    // 06.2013 mm 90456 - Maj de la qté restante  qd on charge une seule fois la liste
	if ((getInterface()->getFonctionEnCours() == 2 ) && (m_data->getChargementListMat() == 1))
	{
		int index = m_data->getIndexComposant_Art(m_data->getCurrentComposant()->getComposant());
		while (strcmp
			( m_data->getComposant_Art(index)->getComposant(),m_data->getCurrentComposant()->getComposant())==0 )
		{
			composant = m_data->getComposant_Art(index);
			if ((strcmp (composant->getNumOF(),m_data->getCurrentComposant()->getNumOF())==0)&&
				(composant->getPhase() == m_data->getCurrentComposant()->getPhase()))
			{
				composant->setQuantiteRestante(
					 m_data->getCurrentComposant()->getQuantiteRestante());
				break;
			}
			index++;
		}
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::envoiFinLot()
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxComposant* composant;
    m_data->sendX3_FinLot();

	consommationQuantite(true);
	m_data->setOrderBegin(true);
	m_data->setPhaseBegin(true);
	m_data->getCurrentPhase()->setStatut(m_data->getCodeMatEnCoursPesee());
	m_data->getCurrentPhase()->setLibStatut(m_data->getLibMatEnCoursPesee());
	m_data->getCurrentOrder()->setStatut(m_data->getCodeOFEnCoursPesee());
	m_data->getCurrentOrder()->setLibStatut(m_data->getLibOFEnCoursPesee());
	m_data->setComposantBegin(true);
	m_data->setLotBegin(false);
	_balanceBegin = true;
	_peseeCumuleeForcee = false; // 11.07 mm - modif mode de pesee en emb.mixte 

	// Performances, mm 04.2013 - en cas de pesée par article, la quantité restante doit être modifiée
	// 06.2013 mm 90456 - Maj de la qté restante  qd on charge une seule fois la liste
	if ((getInterface()->getFonctionEnCours() == 2 ) && (m_data->getChargementListMat() == 1))
	{
		int index = m_data->getIndexComposant_Art(m_data->getCurrentComposant()->getComposant());
		while (strcmp
			( m_data->getComposant_Art(index)->getComposant(),m_data->getCurrentComposant()->getComposant())==0 )
		{
			composant = m_data->getComposant_Art(index);
			if ((strcmp (composant->getNumOF(),m_data->getCurrentComposant()->getNumOF())==0 )&&
				(composant->getPhase() == m_data->getCurrentComposant()->getPhase()))
			{
				composant->setQuantiteRestante(
					 m_data->getCurrentComposant()->getQuantiteRestante());
				break;
			}
			index++;
		}
	}
}

//---------------------------------------------------------------------------
void AdxPesee_OF::envoiFinComposant()
{
	AdxData* m_data = getInterface()->getDonnees();
  	AdxComposant* composant;
	AdxPhase* phase;
	IlList* composantList = m_data->getCurrentPhase()->getComposantList();
	IlList* phaseList = m_data->getPhaseList();

	m_data->sendX3_FinComposant();

	consommationQuantite(true);
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
	_balanceBegin = true;
	_peseeCumuleeForcee = false; // 11.07 mm - modif mode de pesee en emb.mixte


// l'utilisateur a change depuis trop lgt de phase ou d'OF pour pouvoir 
//	faire des vides de box facultatifs
	m_data->setIndicateurProcedure(0);

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
                            if (m_data->getNbPhasesPesees() + 1 >= m_data->getNbPhases())
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
void AdxPesee_OF::envoiFinComposant_Art()
{
	AdxData* m_data = getInterface()->getDonnees();
  	AdxComposant* composant;
	//AdxPhase* phase;

	m_data->sendX3_FinComposant_Art();

	consommationQuantite(true);
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
	_balanceBegin = true;
	_peseeCumuleeForcee = false; // 11.07 mm - modif mode de pesee en emb.mixte

	// mise à jour de la liste Composant_Art : MAJ flag TotalementPese
	// 06.2013 mm 90456  - seulement si on charge une seule fois la liste
	if (m_data->getChargementListMat() == 1)
	{
		int index = m_data->getIndexComposant_Art(m_data->getCurrentComposant()->getComposant());
		while (strcmp( m_data->getComposant_Art(index)->getComposant(),m_data->getCurrentComposant()->getComposant())==0 )
		{
			composant = m_data->getComposant_Art(index);
			if ((strcmp (composant->getNumOF(),m_data->getCurrentComposant()->getNumOF())==0) &&
				(composant->getPhase() == m_data->getCurrentComposant()->getPhase()) &&
				( !composant->getTotalementPese()))
			{
				composant->setTotalementPese(true);
				break;
			}
			index++;
		}
	}
}
//---------------------------------------------------------------------------
void AdxPesee_OF::envoiFinPhase()
{
	AdxData* m_data = getInterface()->getDonnees();
	AdxComposant* composant;
	AdxPhase* phase;
	IlList* composantList = m_data->getCurrentPhase()->getComposantList();
	IlList* phaseList = m_data->getPhaseList();

	m_data->sendX3_FinPhase();
	consommationQuantite(true);
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
	_balanceBegin = true;
	_peseeCumuleeForcee = false; // 11.07 mm - modif mode de pesee en emb.mixte

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
                            if (m_data->getNbPhasesPesees()  >= m_data->getNbPhases())
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
// on donne la possibilite a l'utilisateur de faire le vide de box fin de phase 
//	quand facultatif ou obligatoire 
//	m_data->PositionneProcedurePhaseAttente();

}

//---------------------------------------------------------------------------
void AdxPesee_OF::envoiFinOF()
{
	AdxData* m_data = getInterface()->getDonnees();
	m_data->sendX3_FinOF();
	consommationQuantite(true);
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
	_balanceBegin = true;
	_peseeCumuleeForcee = false; // 11.07 mm - modif mode de pesee en emb.mixte

// on donne la possibilite a l'utilisateur de faire le vide de box fin d'OF 
//	quand facultatif, quand obligatoire : fait automatiquement dans SendX3_FinOF
// si pas de vide de box fin OF on propose Vide fin Phase car fin OF est toujours une fin phase
	
//	m_data->PositionneProcedureOFAttente();

}

//---------------------------------------------------------------------------
void AdxPesee_OF::chargeTexte(const char* texte)
{
	AdxInterface* m_interface = getInterface();

	for (int i = 0; i < 10; i++)
	{
		strncpy(_lignes[i], _blanc, 160);
	}

	long size = strlen(texte);
// astuce pour adapter la mise en page à des écrans autres que 17 pouces
	int largeur = m_interface->getPhrase_Secu()->getPhraseSecu()->w();
	int nbMaxLig = (largeur * 64) / 869;
	IlvUShort nbLignes = (size / nbMaxLig) + 5;
	if (nbLignes > 10) nbLignes = 10;

	long d = 0;
	for (int i = 0; i < nbLignes; i++)
	{
		if (d < size)
		{
			int nbCar = 0;
			long j;
			int max = d + nbMaxLig;
			if (max > size)
			{
				max = size;
				nbCar = max - d;
				j = size;
			}
			else
			{
				for (j = max; j > d; j--)
				{
					if (strncmp (texte + j, " ", 1) == 0)
					{
						nbCar = j - d;
						break;
					}
				}
			}
			strncpy(_lignes[i], texte + d, nbCar);
			d = j;
		}
	}

	m_interface->getPhrase_Secu()->getPhraseSecu()
		->setLines(_lignes, nbLignes, IlvTrue);
}

//---------------------------------------------------------------------------
CString AdxPesee_OF::formatMessage(CString texte)
{
	CString string;
	if (_peseeParEcart)
		string = IlvGetMessage(getDisplay(), "&PeseeParEcart");
	else
		string = IlvGetMessage(getDisplay(), "&PeseeCumulee");
	string += " ";
	string += IlvGetMessage(getDisplay(),texte);
	return string;
}

//---------------------------------------------------------------------------
IlvBitmap* AdxPesee_OF::erreurBitmap(char* pszFileIcons)
{
	char* message = new char[100];
	sprintf(message,"%s : %s",
		IlvGetMessage(getDisplay(),"&ErrorRead"),
		pszFileIcons);
	envoieMessage(message,false);
	delete [] message;

	char szDefFileIcons[_MAX_PATH];
	sprintf (szDefFileIcons, "%s\\defaut.jpg",
		getInterface()->getPathCACHE());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szDefFileIcons);
	return bitmap;
}

//---------------------------------------------------------------------------
void AdxPesee_OF::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	_balanceChoisie = NULL;

// initialisation des lignes de texte pour consignes de sécurité

	_blanc = new char[161];

	for (int i = 0; i < 160; i++)
	{
		_blanc[i] = ' ';
	}

	for (int i = 0; i < 10; i++)
	{
		_lignes[i] = new char[161];
		strncpy(_lignes[i], _blanc, 160);
		//GBE il faut marquer la fin de la chaine
		_lignes[i][160] ='\0';
	}

	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

// chargement des boutons

	char szFileIcons[_MAX_PATH];

	// boutons sécurité
	sprintf (szFileIcons, "%s\\defaut.jpg",
		_interface->getPathCACHE());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	getsecu1()->setBitmap(bitmap);
	getsecu2()->setBitmap(bitmap);
	getsecu3()->setBitmap(bitmap);
	getsecu4()->setBitmap(bitmap);
	getsecu5()->setBitmap(bitmap);
	getsecu6()->setBitmap(bitmap);
	getsecu7()->setBitmap(bitmap);
	getsecu8()->setBitmap(bitmap);
	getsecu9()->setBitmap(bitmap);
	getsecu10()->setBitmap(bitmap);

	// bouton BoutonListeLot
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\book.png",
		_interface->getPathX3());
	bitmap =	getDisplay()->readBitmap(szFileIcons);
	getBoutonListeLot()->setBitmap(bitmap);

	// bouton BoutonListeEmplacement
	getBoutonListeEmplacement()->setBitmap(bitmap);

	// bouton BoutonListeRecipient
	getBoutonListeRecipient()->setBitmap(bitmap);

	// bouton BoutonListeCuve
	getBoutonListeCuve()->setBitmap(bitmap);

	// bouton BoutonListeBalance
	getBoutonListeBalance()->setBitmap(bitmap);

	// bouton valider
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getvalider()->setBitmap(bitmap);

	// bouton tactile
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\keyboard.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	gettactile()->setBitmap(bitmap);

	// bouton mettreAZero
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\reset.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getmettreAZero()->setBitmap(bitmap);

	// bouton tarer
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\tare.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	gettarer()->setBitmap(bitmap);

	// bouton peser
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\scale1.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getpeser()->setBitmap(bitmap);

	// bouton aide -> supprimé pour faire de la place au bouton Valider+
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\question_mark.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getAide()->setBitmap(bitmap);

	// bouton Valider+
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\validationpesee.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getvaliderPlus()->setBitmap(bitmap);
	
	// bouton quitter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getquitter()->setBitmap(bitmap);

	// bouton AffConnection
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\light_on.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getAffConnection()->setBitmap(bitmap);

// retaillage dimensions écran

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
	//setMaximumSize (sizeScreenW, sizeScreenH);

// masquages

	// masque boutons consignes sécurité
    setVisible(getsecu1(),IlvFalse, IlvFalse);
    setVisible(getsecu2(),IlvFalse, IlvFalse);
    setVisible(getsecu3(),IlvFalse, IlvFalse);
    setVisible(getsecu4(),IlvFalse, IlvFalse);
    setVisible(getsecu5(),IlvFalse, IlvFalse);
    setVisible(getsecu6(),IlvFalse, IlvFalse);
    setVisible(getsecu7(),IlvFalse, IlvFalse);
    setVisible(getsecu8(),IlvFalse, IlvFalse);
    setVisible(getsecu9(),IlvFalse, IlvFalse);
    setVisible(getsecu10(),IlvFalse, IlvFalse);

	// gbe 10.08
	_enPesee = false;
	// mm 12.08
	_razTare = false;
	// mm 05.11
	_stockReelInfInfo = false;
	// mm 08.11
	_boutonValidation =0;
	// SR 12.11 APCPRD-724
	_modifAllocations = false;
	// mm 01.2013 APCPRD-2787
	_btVPlus = false;
	_btV = false;

	// mm 08.11 - Pesée multi-article
	_enPeseeMultiArticle	     = false ;
	//Initialisation des variables de stockage 
	_recipientMulti          = NULL ;
	_balanceMulti            = NULL ;
	_indexComposantSuivantMulti = 0;
	_poidsTareMulti          = 0.0;
	_poidsMatDejaPese 	     = 0.0;
	_poidsPeseMatEncours	 = 0.0;
	_UPMat1					 = NULL;
	_poidsCumuleMulti		 = 0.0;
	_poidsCumuleCible	     = 0.0;
	_poidsPeseTotalPhysique  = 0.0;
	_titreSlo				 = 0.0;		
	_mat1				     = NULL;
	_depassementPoidsMax	 = 0.0;

	// gbe
	_weightMin = .0;
	_weightMax = .0;

	// affichage de la graduation
	IlvBoolean bShowGraduation;
	char* pszShowGraduation;
	AdxProfile_GiveValue (SECTION_ADXPESEE_OF, CLE_SHOW_GRADUATION,
		&pszShowGraduation);
	if (pszShowGraduation)
	{
		bShowGraduation = atoi(pszShowGraduation);
		_showGraduation = bShowGraduation;
		free (pszShowGraduation);
	}
	else
	{
		_showGraduation = true;
	}
	this->getJaugeScale()->setVisible(_showGraduation);

	// affichage de la tolérance
	IlvBoolean bShowTolerance;
	char* pszShowTolerance;
	AdxProfile_GiveValue (SECTION_ADXPESEE_OF, CLE_SHOW_TOLERANCE,
		&pszShowTolerance);
	if (pszShowTolerance)
	{
		bShowTolerance = atoi(pszShowTolerance);
		_showTolerance = bShowTolerance;
		free (pszShowTolerance);
	}
	else
	{
		_showTolerance = true;
	}
	// Gestion de la taille de la police du poids
	IlvUShort nWeightFontHeight;
	char* pszWeightFontHeight;
	AdxProfile_GiveValue (SECTION_ADXPESEE_OF, CLE_WEIGHT_FONT_HEIGHT,
		&pszWeightFontHeight);
	if (pszWeightFontHeight)
	{
		nWeightFontHeight = atoi(pszWeightFontHeight);
		_weightFontHeight = nWeightFontHeight;
		free (pszWeightFontHeight);
	}
	else
	{
		_weightFontHeight = 50;
		char szTemp[18] = "";
		sprintf (szTemp, "%d", _weightFontHeight);
		AdxProfile_PutValue (SECTION_ADXPESEE_OF, CLE_WEIGHT_FONT_HEIGHT, szTemp);

	}
	// Ajout d'un popup menu sur la jauge
	_popupJauge = new IlvPopupMenu (this->getDisplay(), 0);
	_popupJauge->hide ();

	IlvMenuItem menuCol1(IlvGetMessage(this->getDisplay(), "&ShowGraduation"));
	menuCol1.setCallback (showGraduation);
	menuCol1.setChecked(_showGraduation);
	_popupJauge->addItem (menuCol1);

	IlvMenuItem menuCol2(IlvGetMessage(this->getDisplay(), "&ShowTolerance"));
	menuCol2.setCallback (showTolerance);
	menuCol2.setChecked(_showTolerance);
	_popupJauge->addItem (menuCol2);

	IlvLookFeelHandler* lookFeelHandler = getDisplay()->getLookFeelHandler(IlGetSymbol("win95"));
	// gbe On passe en look Win95 pour pouvoir mettre le fond noir au champ de poids
	if(lookFeelHandler != NULL)
	{
		this->getSaisiePoidsPese()->setLookFeelHandler(lookFeelHandler);
		this->getAffPoidsCumule()->setLookFeelHandler(lookFeelHandler);
	}
	// Il faut créer deux palettes différentes car on doit gérer deux taille de font différentes
	IlvPalette* paletteTextSaisiePoidsPese = this->getSaisiePoidsPese()->getPalette();
	IlvPalette* paletteTextAffPoidsAPeser = this->getAffPoidsAPeser()->getPalette();
	IlvPalette* paletteTextAffPoidsCumule = this->getAffPoidsCumule()->getPalette();
	IlvFont* myBigFont = this->getDisplay()->getFont(paletteTextSaisiePoidsPese->getFont()->getFamily(),
		                                             _weightFontHeight,
													 paletteTextSaisiePoidsPese->getFont()->getStyle(),
													 paletteTextSaisiePoidsPese->getFont()->getFoundry());
	IlvPalette* paletteTextYellow1 = this->getDisplay()->getPalette(paletteTextSaisiePoidsPese->getBackground(),
																   getDisplay()->getColor("yellow"),
																   paletteTextSaisiePoidsPese->getPattern(),
																   paletteTextSaisiePoidsPese->getColorPattern(),
																   myBigFont,
																   paletteTextSaisiePoidsPese->getLineStyle(),
																   paletteTextSaisiePoidsPese->getLineWidth(),
																   paletteTextSaisiePoidsPese->getFillStyle(),
																   paletteTextSaisiePoidsPese->getArcMode(),
																   paletteTextSaisiePoidsPese->getFillRule(),
																   paletteTextSaisiePoidsPese->getAlpha(),
																   paletteTextSaisiePoidsPese->getAntialiasingMode());
	IlvPalette* paletteBigText = this->getDisplay()->getPalette(paletteTextAffPoidsAPeser->getBackground(),
																   paletteTextSaisiePoidsPese->getForeground(),
																   paletteTextAffPoidsAPeser->getPattern(),
																   paletteTextAffPoidsAPeser->getColorPattern(),
																   myBigFont,
																   paletteTextAffPoidsAPeser->getLineStyle(),
																   paletteTextAffPoidsAPeser->getLineWidth(),
																   paletteTextAffPoidsAPeser->getFillStyle(),
																   paletteTextAffPoidsAPeser->getArcMode(),
																   paletteTextAffPoidsAPeser->getFillRule(),
																   paletteTextAffPoidsAPeser->getAlpha(),
																   paletteTextAffPoidsAPeser->getAntialiasingMode());
	IlvPalette* paletteTextYellow2 = this->getDisplay()->getPalette(paletteTextAffPoidsCumule->getBackground(),
																   getDisplay()->getColor("yellow"),
																   paletteTextAffPoidsCumule->getPattern(),
																   paletteTextAffPoidsCumule->getColorPattern(),
																   paletteTextAffPoidsCumule->getFont(),
																   paletteTextAffPoidsCumule->getLineStyle(),
																   paletteTextAffPoidsCumule->getLineWidth(),
																   paletteTextAffPoidsCumule->getFillStyle(),
																   paletteTextAffPoidsCumule->getArcMode(),
																   paletteTextAffPoidsCumule->getFillRule(),
																   paletteTextAffPoidsCumule->getAlpha(),
																   paletteTextAffPoidsCumule->getAntialiasingMode());
	//paletteTextYellow->setForeground(getDisplay()->getColor("yellow"));
	this->getSaisiePoidsPese()->setPalette(paletteTextYellow1);
	this->getAffPoidsCumule()->setPalette(paletteTextYellow2);
	this->getAffPoidsAPeser()->setPalette(paletteBigText);
	this->getSaisiePoidsPese()->setBackground(getDisplay()->getColor("black"));
	this->getAffPoidsCumule()->setBackground(getDisplay()->getColor("black"));

}

void AdxPesee_OF::handleInput(IlvEvent& event)
{
	// En attendant de savoir si on prend en compte les combinaisons de touches
	// il suffira de supprimer les 2 lignes suivantes

	// Si on est sur la jauge et qu'on a cliqué avec le bouton gauche ou droit
	// On affiche le popup menu de la jauge
	
	IlvRect tempoRect;
	tempoRect.setX(event.getGx());
	tempoRect.setY(event.getGy());
	if(event.type() == IlvButtonUp && event.button() == IlvRightButton)
	{
		if(tempoRect.inside(this->getJaugePesee()->bbox()))
		//if(this->getJaugePesee()->inside(tempoRect))
		{
			this->RclicJauge(this->getJaugePesee());
		}
	}
	Pesee_OF::handleInput(event); // à supprimer
	if(tempoRect.inside(this->getJaugePesee()->bbox()))
	{
		// Au cas où on redessine les traits
		this->drawScaleLines();
	}
	return;						  // à supprimer
	// Fin du code à supprimer 

	switch (event.type())
	{
		case IlvKeyUp:
			if(event.getModifiers()==IlvCtrlModifier)
			{
				switch(event.getKey())
				{
				case IlvF1Key:
					{
						this->mettreAZeroCB(NULL);
					}
					break;
				case IlvF2Key:
					{
						this->tarerCB(NULL);
					}
					break;
				case IlvF3Key:
					{
						this->peserCB(NULL);
					}
					break;
				}
			}
		default:
			Pesee_OF::handleInput(event);
	}
}