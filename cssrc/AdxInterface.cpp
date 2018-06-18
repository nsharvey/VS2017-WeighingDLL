// AdxInterface.cpp
// ----------------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
// V124 : MC 2000.07.07
//--------------------------------------------------------------
//
#include "stdafx.h"
#include <ilviews/base/message.h>
#include "AdxInterface.h"
#include "x3centr1.h"
#include "AdxAccueil.h"
#include "Adxchoix_OF.h"
#include "Adxchoix_Balance.h"
#include "AdxPesee_Etalon.h"
#include "AdxClavier_tactile.h"
#include "AdxSelection_OF.h"
#include "AdxSelection_Phase.h"
#include "AdxSelection_MWF.h"
#include "AdxSelection_LOT.h"
#include "AdxSelection_Balance.h"
#include "AdxSelection_Recipient.h"
#include "AdxSelection_EtalonLigne.h"
#include "AdxPesee_OF.h"
#include "AdxPhrase_Secu.h"
#include "AdxRecontrole_OF.h"
#include "AdxMessage.h"
#include "AdxOrder.h"
#include "AdxData.h"
#include "AdxDate.h"
//#include "AdxRow.h"
#include "AdxProfile.h"						// 06.04 TRACE
#include <fstream>							// 06.04 TRACE

#include <ctime>							//X3-67237: Added so we can put the date/time in the trace file

using std::ios;

using std::endl;

#include "AdxWeighingInterface.h"

extern "C" IlvBoolean IlvSetLanguage();

//--------------------------------------------------------------
IlvAny AdxInterface::DllInstance = 0;

// End of Ilog Consulting

//--------------------------------------------------------------
AdxInterface::~AdxInterface()
{
	// on supprime les écrans annexes
	if( _accueil != NULL)
		delete _accueil;
	if( _choix_OF != NULL)
		delete _choix_OF;
	if( _choix_Balance != NULL)
		delete _choix_Balance;
	if( _pesee_Etalon != NULL)
		delete _pesee_Etalon;
	if( _clavier_Tactile != NULL)
		delete _clavier_Tactile;
	if( _selection_OF != NULL)
		delete _selection_OF;
	if( _selection_Phase != NULL)
		delete _selection_Phase;
	if( _selection_MWF != NULL)
		delete _selection_MWF;
	if( _selection_LOT != NULL)
		delete _selection_LOT;
	if( _selection_Balance != NULL)
		delete _selection_Balance;
	if( _selection_Recipient != NULL)
		delete _selection_Recipient;
	if( _selection_Ligne != NULL)
		delete _selection_Ligne;
	if( _pesee_OF != NULL)
		delete _pesee_OF;
	if( _phrase_Secu != NULL)
		delete _phrase_Secu;
	if( _recontrole_OF != NULL)
		delete _recontrole_OF;
	if( _message != NULL)
		delete _message;
	if( _display != NULL)
		delete _display;
	if( _donnees != NULL)
		delete _donnees;
	if( _weighingInterface != NULL)
		delete _weighingInterface;
	AdxCloseTrace();											// 06.04 TRACE
}

//--------------------------------------------------------------
// Initialisation interface : partie 1
// sr 02.04 on ne passe plus l'adresse m_pszPathX3 venant du client (car en 1.4.0 on la perd)
//mais l'adresse de pilog->szPatchX3 qui est à nous et qu'on est sûr de ne pas perdre
IlvBoolean AdxInterface::initInterface(	IlvAny instance,
										const char* appName,
										const char* language,
										const char* szPathX3,
										const char* szPathIni,
										const char* szPathCSV,
										const char* szPathCACHE,
										const char* pStructX3)
{
//	IlvSetLanguage();
	if (!IlvSetLocale())
	printf("Falling back to the C locale\n");



//	MessageBox(NULL,"Initialisation interface 1","test",MB_OK);
	//  llc 03.02 
//	si le séparateur décimal dans les Paramètres régionaux n'est pas le point,
//  comme en France où c'est la virgule, la fonction getDouble (via atof) ne reconnait 
//	pas la partie décimale !
//  Alors faisons comme si nous étions anglo-saxons en ce qui concerne les décimales ...
    setlocale(LC_NUMERIC, "English");

	_instance = (IlvAny)instance;
	_appName = (char *)appName;
	_pszPathX3 = (char *)&szPathX3[0];
	_pszPathIni = (char *)&szPathIni[0];		// chemin du .ini - mm 05.07
	_pszPathCSV = (char *)&szPathCSV[0];
	_pszPathCACHE = (char*)&szPathCACHE[0];
	_pStructX3 = (char *)pStructX3;

	// lecture dictionnaire langue par défaut

	if (!lectureDictionnaire(0))
		return false;

	// création du panel message dans la langue par défaut pour les
	// erreurs détectées avant la lecture du fichier paramètres

	_message = new AdxMessage(_display,
							  "Message",
							  IlvGetMessage(_display, "&Message"),
							  this);

	// 05.07 chemin du .ini
	setPathIni(_pszPathIni);	

	// 06.04 TRACE
	char* pszTrace;
	AdxProfile_GiveValue (SECTION_GENERAL, CLE_GENERAL_TRACE, &pszTrace);

//NSH	if (pszTrace)
//NSH	{
//NSH		setTraceMode(atoi(pszTrace));
//NSH		free (pszTrace);
//NSH	}
//NSH	else
//NSH		setTraceMode(0);

	setTraceMode(1);			//NSH - force tracefile
	free (pszTrace);			//NSH

	if (getTraceMode() == 1)
	{
		time_t now = time(0);												//X3-67237: Get current time
		char* dt = ctime(&now);												//X3-67237: convert time to string

		AdxOpenTrace();
//		sprintf(mess, "X3 Weighing module trace system");
//		AdxWriteTrace(mess);
		_traceFile << "X3 Weighing module trace system 140" << endl;
		_traceFile << "-----------------------------------" << endl;		//X3-67237: add break line
		_traceFile << "Log Created: " << dt << endl;						//X3-67237: Write the date/time the log was created
		_traceFile << "Interface initialized (part 1)" << endl;
	}

    	// 12.04 MESSAGE
	char* pszMsg;
	AdxProfile_GiveValue (SECTION_GENERAL, CLE_GENERAL_MSG, &pszMsg);
	if (pszMsg)
	{
		setMsgMode(atoi(pszMsg));
		free (pszMsg);
	}
	else
		setMsgMode(0);

		// 01.12 APCPRD-511 : Message long ou court sur l'afficheur de la balance
	char* pszScaMsg;
	AdxProfile_GiveValue (SECTION_GENERAL, CLE_GENERAL_SCAMSG, &pszScaMsg);
	if (pszScaMsg)
	{
		setScaMsgMode(atoi(pszScaMsg));
		free (pszScaMsg);
	}
	else
		setScaMsgMode(0);
	// Gestion de la purge du buffer
	IlvUShort nClearBuffer;
	char* pszClearBuffer;
	AdxProfile_GiveValue (SECTION_COMMUNICATION, CLE_CLEAR_BUFFER,
		&pszClearBuffer);
	if (pszClearBuffer)
	{
		nClearBuffer = atoi(pszClearBuffer);
		_ClearBuffer = (bool) nClearBuffer;
		free (pszClearBuffer);
	}
	else
	{
		_ClearBuffer = false;
		char szTemp[18] = "";
		sprintf (szTemp, "%d", _ClearBuffer);
		AdxProfile_PutValue (SECTION_COMMUNICATION, CLE_CLEAR_BUFFER, szTemp);

	}

	return true;
}

//--------------------------------------------------------------
// Initialisation interface : suite
IlvBoolean AdxInterface::completeInitInterface(	IlvAny instance, 
												const char* appName,
												const char* language,
												const char* pszPathX3,
												const char* pStructX3)
{

	_weighingInterface = new AdxWeighingInterface(this);

	if (!_weighingInterface->initWeighingInterface())
	{
		delete _weighingInterface;
		_weighingInterface = NULL;
		return IlvFalse;
	};
 	if (getTraceMode() == 1)
		_traceFile << "Interface initialized (part 2)" << endl;

	return IlvTrue;
}

//--------------------------------------------------------------
// Chargement de l'image de fond
IlvBitmap* AdxInterface::LoadBackgroundBitmap(IlvDisplay* Display,AdxGadgetContainer* wnd)
{

	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	char szFileIcons[_MAX_PATH];
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\scale.png",
		_pszPathX3);

	IlvRect monecran;
	IlvRect boundingBox;
	wnd->boundingBox(boundingBox);
	getDisplay()->screenBBox(monecran,true,&boundingBox);
	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();


	IlvRGBBitmapData* _srcdata;
    _srcdata = (IlvRGBBitmapData*)(Display->readBitmapData(szFileIcons));	
	IlvRGBBitmapData* _destdata = new IlvRGBBitmapData(sizeScreenW,
													   sizeScreenH);

	IlvRect _srcRect(0, 0, _srcdata->getWidth(), _srcdata->getHeight());
	IlvRect _destRect(0, 0, sizeScreenW, sizeScreenH);
	_destdata->stretchSmooth(_srcdata, _srcRect, _destRect);

	IlvBitmap* BitmapReturn = new IlvBitmap(Display, _destdata);

	return BitmapReturn;
}

// API
//--------------------------------------------------------------
//  fonction de creation de toutes les fenetres
void AdxInterface::showWindow(IlvSystemView parent,
							  IlvRect* bbox
							 )
{
	showAccueilWindow(parent, bbox, IlvTrue);
	_font = getDisplay()->defaultFont();
	showChoix_OFWindow(parent, bbox, IlvFalse);
	showSelection_OFWindow(parent, bbox, IlvFalse);
	showChoix_BalanceWindow(parent, bbox, IlvFalse);
	showPesee_EtalonWindow(parent, bbox, IlvFalse);
	showSelection_PhaseWindow(parent, bbox, IlvFalse);
	showSelection_MWFWindow(parent, bbox, IlvFalse);
	showSelection_LOTWindow(parent, bbox, IlvFalse);
	showSelection_BalanceWindow(parent, bbox, IlvFalse);
	showSelection_RecipientWindow(parent, bbox, IlvFalse);
	showSelection_EtalonLigneWindow(parent, bbox, IlvFalse);
	showPesee_OFWindow(parent, bbox,IlvFalse);
	showPhrase_SecuWindow(parent, bbox,IlvFalse);
	showRecontrole_OFWindow(parent, bbox,IlvFalse);
	showMessageWindow(parent, bbox,IlvFalse);
	showClavier_TactileWindow(parent, bbox, IlvFalse);

}

//--------------------------------------------------------------
void AdxInterface::showAccueilWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if (_accueil == NULL)
	{
		_accueil = new AdxAccueil( this->getDisplay(), parent, this);
		CString string(IlvGetMessage(getDisplay(), "&Choisir"));
		string += " ";
		string += IlvGetMessage(getDisplay(),"&Fonction");
		_accueil->getmessage()->setLabel(string);
		const char* pTittle = IlvGetMessage(getDisplay(),"&CentralesDePesees");
		X3Ilog_ChangeTitle(getStructX3(),pTittle);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_accueil->disableTitleBarButtons();

		_accueil->initReDraw();
	}

	if (_accueil) 
	{
		_accueil->afficherPoste();
	}
	if (visible == IlvTrue)
	{
		_accueil->moveToScreen(IlvTopLeft);
		_accueil->show();
	}
	else
		_accueil->hide();
}

//--------------------------------------------------------------
void AdxInterface::showChoix_OFWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_choix_OF == NULL)
	{
		_choix_OF = new AdxChoix_OF( getDisplay(),
			"&ChoixOF", "&ChoixOF", 
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_choix_OF->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_choix_OF->moveToScreen(IlvTopLeft);
		_choix_OF->show();
	}
	else 
		_choix_OF->hide();
}

//--------------------------------------------------------------
void AdxInterface::showChoix_BalanceWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_choix_Balance == NULL)
	{
		_choix_Balance = new AdxChoix_Balance( getDisplay(),
			"&ChoixBalance", "&ChoixBalance", 
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_choix_Balance->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_choix_Balance->moveToScreen(IlvTopLeft);
		_choix_Balance->show();
	}
	else 
		_choix_Balance->hide();
}

//--------------------------------------------------------------
void AdxInterface::showPesee_EtalonWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_pesee_Etalon == NULL)
	{
		_pesee_Etalon = new AdxPesee_Etalon( getDisplay(),
			"&PeseeEtalon", "&PeseeEtalon", 
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_pesee_Etalon->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_pesee_Etalon->moveToScreen(IlvTopLeft);
		_pesee_Etalon->show();
	}
	else 
		_pesee_Etalon->hide();
}

//--------------------------------------------------------------
void AdxInterface::showClavier_TactileWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_clavier_Tactile == NULL)
	{
		_clavier_Tactile = new AdxClavier_Tactile( getDisplay(),
			"&ClavierTactile", "&ClavierTactile",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_clavier_Tactile->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_clavier_Tactile->moveToScreen(IlvTopLeft);
		_clavier_Tactile->show();
	}
	else 
		_clavier_Tactile->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_OFWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_OF == NULL)
	{
		_selection_OF = new AdxSelection_OF( getDisplay(),
			"&SelectionOF", "&SelectionOF",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_OF->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_OF->moveToScreen(IlvTopLeft);
		_selection_OF->show();
	}
	else 
		_selection_OF->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_PhaseWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_Phase == NULL)
	{
		_selection_Phase = new AdxSelection_Phase( getDisplay(),
			"&SelectionPhase", "&SelectionPhase",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_Phase->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_Phase->moveToScreen(IlvTopLeft);
		_selection_Phase->show();
	}
	else 
		_selection_Phase->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_MWFWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_MWF == NULL)
	{
		_selection_MWF = new AdxSelection_MWF( getDisplay(),
			"&SelectionMWF", "&SelectionMWF",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_MWF->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_MWF->moveToScreen(IlvTopLeft);
		_selection_MWF->show();
	}
	else 
		_selection_MWF->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_LOTWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_LOT == NULL)
	{
		_selection_LOT = new AdxSelection_LOT( getDisplay(),
			"&SelectionLOT", "&SelectionLOT",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_LOT->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_LOT->moveToScreen(IlvTopLeft);
		_selection_LOT->show();
	}
	else 
		_selection_LOT->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_BalanceWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_Balance == NULL)
	{
		_selection_Balance = new AdxSelection_Balance( getDisplay(),
			"&SelectionBalance", "&SelectionBalance", this,
			bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_Balance->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_Balance->moveToScreen(IlvTopLeft);
		_selection_Balance->show();
	}
	else 
		_selection_Balance->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_RecipientWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_Recipient == NULL)
	{
		_selection_Recipient = new AdxSelection_Recipient( getDisplay(),
			"&SelectionRecipient", "&SelectionRecipient", this,
			bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_Recipient->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_Recipient->moveToScreen(IlvTopLeft);
		_selection_Recipient->show();
	}
	else 
		_selection_Recipient->hide();
}

//--------------------------------------------------------------
void AdxInterface::showSelection_EtalonLigneWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_selection_Ligne == NULL)
	{
		_selection_Ligne = new AdxSelection_EtalonLigne( getDisplay(),
			"&SelectionLigne", "&SelectionLigne", this,
			bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_selection_Ligne->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_selection_Ligne->moveToScreen(IlvTopLeft);
		_selection_Ligne->show();
	}
	else 
		_selection_Ligne->hide();
}

//--------------------------------------------------------------
void AdxInterface::showPesee_OFWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_pesee_OF == NULL)
	{
		_pesee_OF = new AdxPesee_OF( getDisplay(),
			"&PeseeOF","&PeseeOF", this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_pesee_OF->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_pesee_OF->moveToScreen(IlvTopLeft);
		_pesee_OF->show();
	}
	else 
		_pesee_OF->hide();
}

//--------------------------------------------------------------
void AdxInterface::showPhrase_SecuWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_phrase_Secu == NULL)
	{
		_phrase_Secu = new AdxPhrase_Secu( getDisplay(),
			"&PhraseSecu","&PhraseSecu",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_phrase_Secu->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_phrase_Secu->moveToScreen(IlvTopLeft);
		_phrase_Secu->show();
	}
	else 
		_phrase_Secu->hide();
}

//--------------------------------------------------------------
void AdxInterface::showRecontrole_OFWindow(IlvSystemView parent,
										   IlvRect* bbox,
										   IlvBoolean visible)
{
	if(_recontrole_OF == NULL)
	{
		_recontrole_OF = new AdxRecontrole_OF( getDisplay(),
			"&RecontroleOF","&RecontroleOF",
			this, bbox,0,IlvFalse,IlvFalse,parent);
		// GBE 19/04/2013 Suppression des boutons dans la title bar
		_recontrole_OF->disableTitleBarButtons();
	}
	if (visible == IlvTrue)
	{
		_recontrole_OF->moveToScreen(IlvTopLeft);
		_recontrole_OF->show();
	}
	else 
		_recontrole_OF->hide();
}

//--------------------------------------------------------------
void AdxInterface::showMessageWindow(IlvSystemView parent,
								   IlvRect* bbox,
								   IlvBoolean visible)
{
	if(_message == NULL)
	{
		_message = new AdxMessage( getDisplay(),
			"&Message","&Message", this, bbox,0,IlvFalse,IlvFalse,parent);
	}
	if (visible == IlvTrue)
	{
		_message->moveToScreen(IlvTopLeft);
		_message->show();
	}
	else 
		_message->hide();
}

//---------------------------------------------------------------------------
bool AdxInterface::envoieMessage(CString mess, bool OUINON)
{
		AdxMessage* m_message = getMessage();
		char szFileIcons[_MAX_PATH];
		CString string(IlvGetMessage(getDisplay(), mess));
		m_message->getMessage()->setLabel(string);

		// boutons OUI, OK, NON
		if (OUINON)
		{
			sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\warning.png",
				_pszPathX3);
			IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
			m_message->getsecu()->setBitmap(bitmap);
			m_message->setVisible(m_message->getsecu(),IlvTrue, IlvFalse);
			m_message->setVisible(m_message->getBoutonOK(),IlvFalse, IlvFalse);
			m_message->setVisible(m_message->getBoutonOui(),IlvTrue, IlvFalse);
			m_message->setVisible(m_message->getBoutonNon(),IlvTrue, IlvFalse);
		}
		else
		{
			sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\stop.png",
				_pszPathX3);
			IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
			m_message->getsecu()->setBitmap(bitmap);
			m_message->getsecu()->resize(65, 65);
			m_message->setVisible(m_message->getsecu(),IlvTrue, IlvFalse);
			m_message->setVisible(m_message->getBoutonOK(),IlvTrue, IlvFalse);
			m_message->setVisible(m_message->getBoutonOui(),IlvFalse, IlvFalse);
			m_message->setVisible(m_message->getBoutonNon(),IlvFalse, IlvFalse);
		}
		m_message->setSensitive(true);
		m_message->showModal(true);
		// GBE 20/12/12 Ajout Trace pour les échanges avec X3
		if(this->getTraceMode() == 1)
		{
			this->_traceFile<< "AdxInterface::envoieMessage message("<<string<<") OUINON ("<<OUINON<<") reponse("<<m_message->getReponse()<<")" << endl;
		}

		return m_message->getReponse();
}

//--------------------------------------------------------------
bool AdxInterface::lectureDictionnaire(bool appel)
{
	if(_display)
	{
		delete _display;
		_display = NULL;
	}

	_display = new IlvDisplay(_instance, _appName);
	if (!_display || _display->isBad()) 
	{
		if (_display) 
			delete _display;
		return false;
	}


	// lecture dictionnaire dans la langue

	char szFileMessage[_MAX_PATH];
	sprintf (szFileMessage, "%slan\\X3Sca%s.dbm",
		_pszPathX3, getDonnees()->getLanguage());
	if ( !_display->getDatabase()->read(szFileMessage, _display))
	{
		char* message = new char[60];
		sprintf(message,"Erreur lecture %s",
			szFileMessage); 
		MessageBox(NULL,message,"Erreur",MB_OK);
		delete [] message;
		// force le panneau message à NULL
		// pour éviter un plantage dans le delete final
		_message = NULL;
		return false;
	}

	if(appel)
	{
		// Delete le panel message initialisé dans la langue par défaut
		// pour le recréer dans la langue choisie après lecture de
		// X3ScalesBox.csv

		if( _message != NULL)
		{
//			delete _message;   // le delete plante : pourquoi ?
							   // il semble qu'il ne reste plus rien en
							   // mémoire à la fin sans ce delete	
			_message = new AdxMessage(_display,
					                  "Message",
									  IlvGetMessage(_display, "&Message"),
									  this);
		}

		// lecture dictionnaire phrases sécurité (au deuxiàme appel)

		sprintf (szFileMessage, "%slan\\X3Sec%s.dbm",
			_pszPathX3,  getDonnees()->getLanguage());
		if (!_display->getDatabase()->read(szFileMessage, _display))
		{
			getMessage()->setPanneauAppelant(NULL);
			char* message = new char[60];
			sprintf(message,"%s : %s",
				IlvGetMessage(_display,"&ErrorRead"),
				szFileMessage);
			envoieMessage(message,false);
			delete [] message;
			return false;
		}
	}
	return true;
}

//--------------------------------------------------------------
void AdxInterface::notify()
{
// non actif pour l'instant: revoir utilité après modifs du "client"
//	bool dataOK;
	int index = 0;

	switch (_sequenceAppelante)
	{
		case 1:
//			dataOK = _donnees->acquisitionOF(index);
//			_donnees->SendX3_ChangeOF(index);
			break;
		case 2:
//			dataOK = _donnees->acquisitionLots();
//			_donnees->SendX3_AllocLots();
			break;
		case 3:
//			_donnees->SendX3_PeseePartielle();
			break;
		case 4:
//			_donnees->SendX3_FinLot();
			break;
		case 5:
//			_donnees->SendX3_FinComposant();
			break;
		case 6:
//			_donnees->SendX3_FinPhase();
			break;
		case 7:
//			_donnees->SendX3_FinOF();
			break;
		case 8:
//			_donnees->SendX3_InterruptionComposant();
			break;
		case 9:
//			_donnees->SendX3_InterruptionPhase();
			break;
		case 10:
//			_donnees->SendX3_InterruptionOF();
			break;
		case 11:
//			_donnees->SendX3_ChangementOFNonPese();
			break;
		case 12:
//			_donnees->SendX3_ChangementComposant();
			break;
		case 13:
//			_donnees->SendX3_SoldeEmballage();
			break;
		case 14:
			_donnees->SendX3_Procedure(index);
			break;
		case 15:
			_donnees->SendX3_Reconciliation();
			break;
		case 16:
//			_donnees->SendX3_Aide();
			break;
		case 17 :
			_donnees->SendX3_ConsultationStockDetaille();
		default:
			break;
	}
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxInterface::init()
{
	_display = NULL;
	_accueil = NULL;
	_choix_OF = NULL;
	_choix_Balance = NULL;
	_pesee_Etalon = NULL;
	_clavier_Tactile = NULL;
	_selection_OF = NULL;
	_selection_Phase = NULL;
	_selection_MWF = NULL;
	_selection_LOT = NULL;
	_selection_Balance = NULL;
	_selection_Recipient = NULL;
	_selection_Ligne = NULL;
	_pesee_OF = NULL;
	_phrase_Secu = NULL;
	_recontrole_OF = NULL;
	_message = NULL;
	_weighingInterface = NULL;
	_donnees = new AdxData(this);
	_sequenceAppelante = 0;
	_ClearBuffer = false;
}

//--------------------------------------------------------------
// 06.04 TRACE
//--------------------------------------------------------------
void AdxInterface::AdxOpenTrace()
{
	const char* traceFileName = "x3scales.log";
	char wChFullPathTrace[_MAX_PATH];

	if(this->_pszPathCSV[strlen(this->_pszPathCSV)-1] == '\\')
	{
		sprintf(wChFullPathTrace,"%s%s",this->_pszPathCSV,traceFileName);
	}
	else
	{
		sprintf(wChFullPathTrace,"%s%c%s",this->_pszPathCSV,'\\',traceFileName);
	}

	_traceFile.open(wChFullPathTrace, ios::out);
}

//--------------------------------------------------------------
// 06.04 TRACE
//--------------------------------------------------------------
void AdxInterface::AdxCloseTrace()
{
	_traceFile.close();
}

//--------------------------------------------------------------
// 06.04 TRACE
//--------------------------------------------------------------
void AdxInterface::AdxWriteTrace(char* message)
{
	_traceFile << message << endl;
}

void AdxInterface::closeAllWindows()
{
	if(getClavier_Tactile()->IsDisplayed())
	{
		getClavier_Tactile()->quitter();
	}
	if(getRecontrole_OF()->IsDisplayed())
	{
		getRecontrole_OF()->QuitterCB(NULL);
	}
	if(getSelection_OF()->IsDisplayed())
	{
		getSelection_OF()->quitterCB(NULL);
	}
	if(getSelection_Phase()->IsDisplayed())
	{
		getSelection_Phase()->quitterCB(NULL);
	}
	if(getSelection_MWF()->IsDisplayed())
	{
		getSelection_MWF()->quitterCB(NULL);
	}
	if(getSelection_LOT()->IsDisplayed())
	{
		getSelection_LOT()->quitterCB(NULL);
	}
	if(getSelection_Balance()->IsDisplayed())
	{
		getSelection_Balance()->quitterCB(NULL);
	}
	if(getSelection_EtalonLigne()->IsDisplayed())
	{
		getSelection_EtalonLigne()->quitterCB(NULL);
	}
	if(getSelection_Recipient()->IsDisplayed())
	{
		getSelection_Recipient()->quitterCB(NULL);
	}
	if(getPhrase_Secu()->IsDisplayed())
	{
		getPhrase_Secu()->quitterCB(NULL);
	}
	if(getPesee_OF()->IsDisplayed())
	{
		getPesee_OF()->quitterCB(NULL);
	}
	if(getPesee_Etalon()->IsDisplayed())
	{
		getPesee_Etalon()->quitterCB(NULL);
	}
	if(getChoix_Balance()->IsDisplayed())
	{
		getChoix_Balance()->quitterCB(NULL);
	}
	if(getChoix_OF()->IsDisplayed())
	{
		getChoix_OF()->quitterCB(NULL);
	}
}