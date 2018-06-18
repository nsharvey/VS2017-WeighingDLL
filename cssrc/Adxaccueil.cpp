// AdxAccueil.cpp
// --------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#include "stdafx.h"
#include "AdxInterface.h"
#include "X3Centr1.h"

#include "Adxaccueil.h"

#include "AdxGadgetContainer.h"
#include "Adxchoix_OF.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_Phase.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_LOT.h"
#include "AdxSelection_Balance.h"
#include "AdxSelection_Recipient.h"
#include "AdxPesee_OF.h"
#include "AdxMessage.h"
#include "AdxOrder.h"
#include "AdxData.h"
#include "AdxBalance.h"
#include "AdxDate.h"
#include "AdxChoix_Balance.h"

static void Quitter(IlvView* view, IlvAny arg)
{
	((AdxAccueil*)arg)->quitter();
}

// gbe 18/11/08
// Cette fonction permet de dessiner un rectangle autour des boutons de l'écran principal car
// ce dernier ne se comporte pas comme les autres et n'affiche pas le focus sur les boutons où
// on clique
static void drawButtonRect(IlvGadgetContainer* container,IlvGraphic* g)
{
	IlvRect Rect;
	IlvUInt DeltaX = 2;
	IlvUInt DeltaY = 2;
	IlvPalette* palette = NULL;

	g->boundingBox(Rect);

	Rect.setX((Rect.getX() - DeltaX));
	Rect.setY((Rect.getY() - DeltaY));
	Rect.setW((Rect.getW() + 2*DeltaX));
	Rect.setH((Rect.getH() + 2*DeltaY));
	palette = container->getDisplay()->getPalette(container->getDisplay()->getColor("black"),//background 
											 container->getDisplay()->getColor("black"),//foreground 
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
	container->drawRectangle(palette,Rect);
	palette->unLock();

}
// gbe 18/11/08
// Surcharge de la fonction show pour faire un redraw et effacer le derniers rectangle dessiné
void AdxAccueil::show()
{
	IlvGadgetContainer::show();
	this->reDraw();
}
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------

//--------------------------------------------------------------
// sr 11.02 si demande de rafraichissement des données: 
// Nouvel ordre refreh envoyé au serveur pour rapatrier le nouveau 
// plan de pesée  incident n° 27
void AdxAccueil::refreshCB(IlvGraphic* g)
{
	// mm 12.12 - pas de _currentOrder chargé si _fonctionEnCours = 2 => provoque un plantage dans le loadPhase()
	// on affecte arbitrairement 1 à _fonctionEnCours pour l'éviter
	if (getInterface()->getFonctionEnCours() == 2)
		getInterface()->setFonctionEnCours(1);	
    if (envoieMessage("&Réactualiser les données ?", true) == true)
	{
		getInterface()->getDonnees()->SendX3_Refresh();	
	}
}
//--------------------------------------------------------------
void AdxAccueil::quitterCB(IlvGraphic* g)
{
	drawButtonRect((IlvGadgetContainer*)this,g);
	quitter();
}

//--------------------------------------------------------------
void AdxAccueil::peserOFCB(IlvGraphic* g)
{
	drawButtonRect((IlvGadgetContainer*)this,g);

	// passage pesée par article à pesée par OF - mm 09.10
	if (getInterface()->getFonctionEnCours() == 2)
	{
		getInterface()->setFonctionEnCours(1);	
		getInterface()->getDonnees()->SendX3_Refresh();	
	}
	else
		getInterface()->setFonctionEnCours(1);	
	lancerPesee();
}

//--------------------------------------------------------------
void AdxAccueil::peserFabricationCB(IlvGraphic* g)
{
	drawButtonRect((IlvGadgetContainer*)this,g);
	// passage pesée par article à pesée par OF - mm 09.10
	if (getInterface()->getFonctionEnCours() == 2)
	{
		getInterface()->setFonctionEnCours(3);
		getInterface()->getDonnees()->SendX3_Refresh();	
	}
	else
		getInterface()->setFonctionEnCours(3);
	lancerPesee();
}

//--------------------------------------------------------------
void AdxAccueil::testerBalanceCB(IlvGraphic* g)
{
	drawButtonRect((IlvGadgetContainer*)this,g);
	AdxInterface* m_interface = getInterface();
	AdxChoix_Balance* ChoixBalance = m_interface->getChoix_Balance();    
	ChoixBalance->chargement();
	setSensitive(false);
	ChoixBalance->show();
}

//--------------------------------------------------------------
void AdxAccueil::aideCB(IlvGraphic* g)
{
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Aide();
}

//--------------------------------------------------------------
void AdxAccueil::peserArticleCB(IlvGraphic* g)
{
    AdxData* m_data = getInterface()->getDonnees();

	drawButtonRect((IlvGadgetContainer*)this,g);
	getInterface()->setFonctionEnCours(2);
	m_data->setPeseeLancee(false);
	lancerPesee();
}

//--------------------------------------------------------------
void AdxAccueil::reconcilierCB(IlvGraphic* g)
{
	drawButtonRect((IlvGadgetContainer*)this,g);
	getInterface()->setPanneauAppelant((AdxGadgetContainer*)this);
    AdxData* m_data = getInterface()->getDonnees();
	m_data->SendX3_Reconciliation();
	this->reDraw();
}

//--------------------------------------------------------------
void AdxAccueil::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	setDestroyCallback(Quitter, this);

	// fond ecran
	char szFileIcons[_MAX_PATH];
	/*sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\scale.png",
		_interface->getPathX3());

	IlvRGBBitmapData* _srcdata;
    _srcdata = (IlvRGBBitmapData*)(getDisplay()->readBitmapData(szFileIcons));	
	IlvRGBBitmapData* _destdata = new IlvRGBBitmapData(getDisplay()->screenWidth(),
													getDisplay()->screenHeight());

	IlvRect _srcRect(0, 0, _srcdata->getWidth(), _srcdata->getHeight());
	IlvRect _destRect(0, 0, getDisplay()->screenWidth(), getDisplay()->screenHeight());
	_destdata->stretchSmooth(_srcdata, _srcRect, _destRect);

	IlvBitmap* bitmapBackground = new IlvBitmap(getDisplay(), _destdata);*/

	//setBackgroundBitmap(bitmapBackground);

	// Voir pourquoi l'image de fond est unique 

	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay(),this));

	IlvBitmap* bitmapIcon = new IlvBitmap(getDisplay(), 270, 270, getDisplay()->screenDepth());

	// bouton raffraichir
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\refresh.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);

	IlvZoomableTransparentIcon* BitmapRefresh = getrefresh();

	BitmapRefresh->setBitmap(bitmapIcon);
	

	// bouton testerBalance
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\scale_control.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	gettesterBalance()->setBitmap(bitmapIcon);
	// sr 08.02 si pas de guide etalonnage transféré alors pas de bouton
	if (_interface->getDonnees()->getNbEtalons() == 0)
	{
	   setVisible(gettesterBalance(),IlvFalse, IlvFalse);
	}

	// bouton peserOF
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\order_choice.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	getpeserOF()->setBitmap(bitmapIcon);

	// bouton reconcilier
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\handshake.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	getreconcilier()->setBitmap(bitmapIcon);

	// bouton peseeArticle
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\product_choice.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	getpeseeArticle()->setBitmap(bitmapIcon);

	// bouton peserFabrication
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\water.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	getpeserFabrication()->setBitmap(bitmapIcon);

	// bouton aide
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\question_mark.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	getaide()->setBitmap(bitmapIcon);

	// bouton quitter
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmapIcon = getDisplay()->readBitmap(szFileIcons);
	bitmapIcon->setAntialiasingMode(IlvNoAntialiasingMode);

	getquitter()->setBitmap(bitmapIcon);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
	//setMaximumSize (sizeScreenW, sizeScreenH);

	allowFocus(IlvFalse);

	setNbConnecte(0) ;	// 11.07 mm
	
}

//--------------------------------------------------------------
void AdxAccueil::quitter()
{
 //   AdxData* m_data = getInterface()->getDonnees();

	//if ((m_data->getCurrentOrderIndex() == 0) && (m_data->getPeseeLancee() == false))
	//	m_data->SendX3_ChangementOFNonPese(NULL);
	HWND hPere = X3Ilog_GetWindowHandle (_interface->getStructX3());
	if (hPere)   
		PostMessage (hPere, WM_CLOSE, 0,0);
}


//---------------------------------------------------------------------------
bool AdxAccueil::envoieMessage(CString mess, bool OUINON)
{
	AdxInterface* m_interface = getInterface();
	m_interface->getMessage()->setPanneauAppelant((AdxGadgetContainer*)this);
	return (m_interface->envoieMessage(mess, OUINON));
}
//--------------------------------------------------------------
void AdxAccueil::afficherPoste()
{
	AdxData* data = getInterface()->getDonnees();
	getChampUtilisateur()->setLabel(data->getUtilisateur());
	getChampApplication()->setLabel(data->getApplication());
	getChampDate()->setValue(data->getDateJour()->getDay(),
							 data->getDateJour()->getMonth(),
							 data->getDateJour()->getYear());
	getChampLieu()->setLabel(data->getLieu());
	getChampBox()->setLabel(data->getBox());
	reafficherBalances();
}
//--------------------------------------------------------------
// affiche dans l'ecran accueil les nombres de balances a etalonner et de balances connectees
void AdxAccueil::reafficherBalances()
{
	AdxData* data = getInterface()->getDonnees();
	char* string = new char[4];
	char* string2 = new char[2];
	itoa(data->getNbBalancesAEtalonner(),string,10);
	itoa(data->getNbBalances(),string2,10);
	strcat(string,"/");
	strcat(string,string2);
	getChampEtalonnage()->setLabel(string);
	int nbConnecte = 0;
	IlList* balanceList = data->getBalanceList();
	for ( int i = 0; i < data->getNbBalances() ; i++)
	{
		AdxBalance* balance = (AdxBalance*)(*balanceList)[i];
		if (balance->getConnecte() != 0) nbConnecte += 1;
	}
	setNbConnecte(nbConnecte);	// 11.07 mm
	itoa(nbConnecte,string,10);
	strcat(string,"/");
	strcat(string,string2);
	getChampConnection()->setLabel(string);
	delete [] string;
	delete [] string2;
}

//--------------------------------------------------------------
// methode commune d'appel a la fonction de pesee (OF, Art ou Fab)
void AdxAccueil::lancerPesee()
{
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = getInterface()->getDonnees();

//X3-67237 - added below block to call user credentials in X3
	if ( m_data->getX3Ver() == 11 && m_data->getBoxPwd() == 2)
	{
		if (!m_data->SendX3_CheckCredentials(true, true))
		{
			return;
		}
	}
//X3-67237 - end of added block

	// 03.09 mm - Bloquer l'entrée en pesée si toutes les balances sont à étalonner 
	_balanceEtalonne = false;	// 03.09 mm
	IlList* balanceList = m_data->getBalanceList();
	int i = 0;
	for (i = 0; i < m_data->getNbBalances() ; i++)
	{
		AdxBalance* balance = (AdxBalance*)(*balanceList)[i];
		if (balance->getEtalonnee() !=0)
		{
			_balanceEtalonne = true;	
			break;
		}
	}
	if ((i == m_data->getNbBalances()) && (_balanceEtalonne == false))
	{
			envoieMessage("&ToutesAEtalonner"  , false);
			show();
			return;
	}


	AdxChoix_OF* choixOF = m_interface->getChoix_OF();
	choixOF->chargement();
	m_data->setOrderBegin(false);
	m_data->setPhaseBegin(false);
	m_data->setComposantBegin(false);

	if (getInterface()->getFonctionEnCours() == 2 && m_data->getCurrentOrder()!= NULL)
	{
		if ((m_data->getCurrentOrderIndex() == 0) && (m_data->getPeseeLancee() == false))
		{
			// si un OF a été chargé dans _currentOrder
			m_data->SendX3_ChangementOFNonPese(NULL);
		}
		//on vide la liste des fiches ISM, celle des OFs, celle des phases et celle des composants.
		m_data->razListeFicheISM();							
		m_data->razListeOF();																			
		m_data->razListePhase();
		m_data->razListeComposant();
		m_data->setCurrentComposantIndexPseMat("","",0);
		// 06.2013 mm 90456 
		if (m_data->getChargementListMat() == 1)
		{
			// SMO : chargement du fichier des matieres pour la pesee matiere
			// mm 30.2013 - Performance : ne charger qu'une seule fois la liste des matières
			this->setCursor(_display->getCursor("wait"));
			m_data->sendX3_GetMatMat("");
			this->setCursor(_display->getCursor("default"));
		}
		
	}
	m_data->setPeseeLancee(true);
	setSensitive(false);
	choixOF->show();
	// 115769 mm 04.2016 
	if (getInterface()->getFonctionEnCours() != 2)
	{
		if (m_data->getCurrentOrderIndex() || m_data->getCurrentPhaseIndex() || m_data->getCurrentComposantIndex())
		{
			bool dataOK = m_data->acquisitionOF(m_data->getCurrentOrderIndex() , m_data->getCurrentOrderIndex());
			if  (!dataOK)
			{
				m_data->setLockedOrder (m_data->getOrder( m_data->getCurrentOrderIndex()));
				getInterface()->getMessage()->setPanneauAppelant(NULL);
				getInterface()->envoieMessage("&NouvelOF",false);
			}
		}
	}

	if (strcmp (m_data->getOuvertureBox(), "") != 0)
	{
		if (m_data->getOuvertureBoxOblig() == 1)
		{ 
			m_data->setIndicateurProcedure(1);
		}
		else
			m_data->setIndicateurProcedure(0);
		if (m_data->getOuvertureBoxOblig() == 2)
		{
			getInterface()->setPanneauAppelant((AdxGadgetContainer*)choixOF);
			m_data->SendX3_Procedure(1);
			m_data->setOuvertureBoxOblig(3);
		}
	}
	else
		m_data->setIndicateurProcedure(0);
}
