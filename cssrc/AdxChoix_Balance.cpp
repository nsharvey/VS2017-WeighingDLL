// -------------------------------------------------------------- -*- C++ -*-
// File: D:\X3SOURCES\X3Centr3\cssrc\AdxChoix_Balance.cpp
// --------------------------------------------------------------------------
#include "stdafx.h"
#include "AdxChoix_Balance.h"

#include "AdxInterface.h"
#include "AdxAccueil.h"
#include "AdxData.h"
#include "AdxBalance.h"
#include "AdxEtalon.h"
#include "AdxPesee_Etalon.h"
#include "AdxMessage.h"
// gbe 01.09 
#include "AdxWeighingInterface.h"

#include "x3centr1.h"
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
void
AdxChoix_Balance::BalanceCB(IlvGraphic* g)
{
	IlvButton* curButton = (IlvButton*)g;
	int curIndex = 9;
	AdxInterface* m_interface = getInterface();
	AdxData* m_data = getInterface()->getDonnees();
	AdxWeighingInterface* weighingInterface = getInterface()->getWeighingInterface();

	if(curButton->getLabel() == getBalance1()->getLabel())
	{
		curIndex = 0;
	}
	if(curButton->getLabel() == getBalance2()->getLabel())
	{
		curIndex = 1;
	}
	if(curButton->getLabel() == getBalance3()->getLabel())
	{
		curIndex = 2;
	}
	if(curButton->getLabel() == getBalance4()->getLabel())
	{
		curIndex = 3;
	}
	if(curButton->getLabel() == getBalance5()->getLabel())
	{
		curIndex = 4;
	}
	if(curButton->getLabel() == getBalance6()->getLabel())
	{
		curIndex = 5;
	}
	if(curButton->getLabel() == getBalance7()->getLabel())
	{
		curIndex = 6;
	}
	if(curButton->getLabel() == getBalance8()->getLabel())
	{
		curIndex = 7;
	}
	if (curIndex == 9)
	{
		getInterface()->getMessage()->setPanneauAppelant(NULL);
		char* message = new char[60];
		sprintf(message,"%s",
		IlvGetMessage(getInterface()->getDisplay(),"&NoBalanceInconnu       "));
		getInterface()->envoieMessage(message,false);
		delete [] message;
	}
	else
	{
		AdxBalance* balance = m_data->getBalance(curIndex);
		if (m_data->getIndexEtalon(balance->getGuideCalibrage ()) == m_data->getNbEtalons())
		{
			getInterface()->getMessage()->setPanneauAppelant(NULL);
			char* message = new char[60];
			sprintf(message,"%s",
			IlvGetMessage(getInterface()->getDisplay(),"&ErrorGuideInexistant"));
			getInterface()->envoieMessage(message,false);
			delete [] message;//erreur
		}
		else
		{
			m_data->setCurrentBalanceIndex(curIndex);
			m_data->setCurrentEtalonIndex(m_data->getIndexEtalon(balance->getGuideCalibrage ()));

			// gbe 01.09 Il faut indiquer dans AdxWeighingInterface la balance choisie
			m_interface->getWeighingInterface()->setBalance(balance);

			// Gestion multi plateaux 
			// si la balance est en mode multi plateaux on positionne le bon
			if(balance->IsMultiPlate() == true)
			{
				WeighingOrder order;

				order = CHGT_P;
				weighingInterface->setWeighingOrder(order);
				weighingInterface->setPanneauAppelant(this);
				weighingInterface->weighingOrderTreatment();
				if (weighingInterface->getWeighingStatus() != OK_STA)
				{
					// Mettre un message indiquant que le changement de plateau a échoué
					return;
				}
			}


			AdxPesee_Etalon* PeseeEtalon =  m_interface->getPesee_Etalon();
			IlvRect m_rect = 0;
			boundingBox (m_rect);
			PeseeEtalon->chargement();

			if (getInterface()->getDisplay()->hasEvents())
			{
				getInterface()->getDisplay()->readAndDispatchEvents();
			}

			PeseeEtalon->show();
			hide();			
		}
	}
    
}

void
AdxChoix_Balance::quitterCB(IlvGraphic* g)
{
 	quitter();
}


//------------------------------ sr 11.01 -----------------------------------
//---------------------------------------------------------------------------
void AdxChoix_Balance::quitter()
{
	AdxInterface* m_interface = getInterface();	
	AdxAccueil* m_accueil = m_interface->getAccueil();

	AdxChoix_Balance* m_choix_Balance = m_interface->getChoix_Balance();

	m_accueil->setSensitive(true);
	m_accueil->reafficherBalances(); 
	m_accueil->show();
 	m_choix_Balance->hide();
}
//---------------------------------------------------------------------------
void AdxChoix_Balance::afficherBalances()
{

	AdxData* m_data = getInterface()->getDonnees();
	for(int i=1;i<9; i++)
	{
		if(i < m_data->getNbBalances()+1)
		{
		    IlvColor*  foreground  = getDisplay()->getColor("black");
			AdxBalance* balance = m_data->getBalance(i-1);
			// APCPDR-2423 mm 09.2013
			CString codeNomBalance;
			codeNomBalance += balance->getBalance();
			codeNomBalance +=  "\n";
			codeNomBalance += balance->getLibBalance();
				switch (i) 
				{
					case 1 : 	
						
						getBalance1()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton1(),IlvFalse, IlvFalse);
						    setVisible(getEtalon1(),IlvFalse, IlvFalse);
						    setVisible(getBalance1(),IlvFalse, IlvFalse);
							setVisible(getDiamond1(),IlvFalse, IlvFalse);
							setVisible(getDiamond1G(),IlvFalse, IlvFalse);
							setVisible(getDiamond1D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							    setVisible(getLighton1(),IlvFalse, IlvFalse);
							}
							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon1()->setForeground(foreground);
						}
							break;
					case 2 : 	
						getBalance2()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton2(),IlvFalse, IlvFalse);
						    setVisible(getEtalon2(),IlvFalse, IlvFalse);
						    setVisible(getBalance2(),IlvFalse, IlvFalse);
							setVisible(getDiamond2(),IlvFalse, IlvFalse);
							setVisible(getDiamond2G(),IlvFalse, IlvFalse);
							setVisible(getDiamond2D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							   setVisible(getLighton2(),IlvFalse, IlvFalse);
							}

							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon2()->setForeground(foreground);
						}
						break;
					case 3 : 	
						getBalance3()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton3(),IlvFalse, IlvFalse);
						    setVisible(getEtalon3(),IlvFalse, IlvFalse);
						    setVisible(getBalance3(),IlvFalse, IlvFalse);
							setVisible(getDiamond3(),IlvFalse, IlvFalse);
							setVisible(getDiamond3G(),IlvFalse, IlvFalse);
							setVisible(getDiamond3D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							    setVisible(getLighton3(),IlvFalse, IlvFalse);
			
							}
							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon3()->setForeground(foreground);
						}
						break;
					case 4 : 	
						getBalance4()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton4(),IlvFalse, IlvFalse);
						    setVisible(getEtalon4(),IlvFalse, IlvFalse);
						    setVisible(getBalance4(),IlvFalse, IlvFalse);
							setVisible(getDiamond4(),IlvFalse, IlvFalse);
							setVisible(getDiamond4G(),IlvFalse, IlvFalse);
							setVisible(getDiamond4D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							    setVisible(getLighton4(),IlvFalse, IlvFalse);
		
							}
							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon4()->setForeground(foreground);
						}
						break;
					case 5 : 	
						getBalance5()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton5(),IlvFalse, IlvFalse);
						    setVisible(getEtalon5(),IlvFalse, IlvFalse);
						    setVisible(getBalance5(),IlvFalse, IlvFalse);
							setVisible(getDiamond5(),IlvFalse, IlvFalse);
							setVisible(getDiamond5G(),IlvFalse, IlvFalse);
							setVisible(getDiamond5D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							    setVisible(getLighton5(),IlvFalse, IlvFalse);
		
							}
							if(balance->getEtalonnee() == 0)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon5()->setForeground(foreground);
						}								
						break;
					case 6 : 	
						getBalance6()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton6(),IlvFalse, IlvFalse);
						    setVisible(getEtalon6(),IlvFalse, IlvFalse);
						    setVisible(getBalance6(),IlvFalse, IlvFalse);
							setVisible(getDiamond6(),IlvFalse, IlvFalse);
							setVisible(getDiamond6G(),IlvFalse, IlvFalse);
							setVisible(getDiamond6D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							    setVisible(getLighton6(),IlvFalse, IlvFalse);

							}
							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon6()->setForeground(foreground);
						}
						break;
					case 7 : 	
						getBalance7()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton7(),IlvFalse, IlvFalse);
						    setVisible(getEtalon7(),IlvFalse, IlvFalse);
						    setVisible(getBalance7(),IlvFalse, IlvFalse);
							setVisible(getDiamond7(),IlvFalse, IlvFalse);
							setVisible(getDiamond7G(),IlvFalse, IlvFalse);
							setVisible(getDiamond7D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
							    setVisible(getLighton7(),IlvFalse, IlvFalse);
							}
							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon7()->setForeground(foreground);
						}
						break;
					case 8 : 	
						getBalance8()->setLabel(codeNomBalance, IlvTrue);
						if (balance->getCodeCalibrage()== 1)
						{
						    setVisible(getLighton8(),IlvFalse, IlvFalse);
						    setVisible(getEtalon8(),IlvFalse, IlvFalse);
						    setVisible(getBalance8(),IlvFalse, IlvFalse);
							setVisible(getDiamond8(),IlvFalse, IlvFalse);
							setVisible(getDiamond8G(),IlvFalse, IlvFalse);
							setVisible(getDiamond8D(),IlvFalse, IlvFalse);
						}
						else
						{
							if (balance->getConnecte()== 0)
							{
								setVisible(getLighton8(),IlvFalse, IlvFalse);

							}
							if(balance->getEtalonnee() == false)
							{
								foreground = getDisplay()->getColor("red");
							}
							getEtalon8()->setForeground(foreground);
						}
						break;
				}
		}
		else
		{
			switch (i)
			{
				case 1 : 	
				    setVisible(getLighton1(),IlvFalse, IlvFalse);
				    setVisible(getEtalon1(),IlvFalse, IlvFalse);
				    setVisible(getBalance1(),IlvFalse, IlvFalse);
				    setVisible(getDiamond1(),IlvFalse, IlvFalse);
					setVisible(getDiamond1G(),IlvFalse, IlvFalse);
					setVisible(getDiamond1D(),IlvFalse, IlvFalse);
					break;
				case 2 :
				    setVisible(getLighton2(),IlvFalse, IlvFalse);
				    setVisible(getEtalon2(),IlvFalse, IlvFalse);
				    setVisible(getBalance2(),IlvFalse, IlvFalse);
				    setVisible(getDiamond2(),IlvFalse, IlvFalse);
					setVisible(getDiamond2G(),IlvFalse, IlvFalse);
					setVisible(getDiamond2D(),IlvFalse, IlvFalse);
					break;
				case 3 :
				    setVisible(getLighton3(),IlvFalse, IlvFalse);
				    setVisible(getEtalon3(),IlvFalse, IlvFalse);
				    setVisible(getBalance3(),IlvFalse, IlvFalse);
				    setVisible(getDiamond3(),IlvFalse, IlvFalse);
					setVisible(getDiamond3G(),IlvFalse, IlvFalse);
					setVisible(getDiamond3D(),IlvFalse, IlvFalse);
					break;
				case 4 :
				    setVisible(getLighton4(),IlvFalse, IlvFalse);
				    setVisible(getEtalon4(),IlvFalse, IlvFalse);
				    setVisible(getBalance4(),IlvFalse, IlvFalse);
				    setVisible(getDiamond4(),IlvFalse, IlvFalse);
					setVisible(getDiamond4G(),IlvFalse, IlvFalse);
					setVisible(getDiamond4D(),IlvFalse, IlvFalse);
					break;
				case 5 :
				    setVisible(getLighton5(),IlvFalse, IlvFalse);
				    setVisible(getEtalon5(),IlvFalse, IlvFalse);
				    setVisible(getBalance5(),IlvFalse, IlvFalse);
				    setVisible(getDiamond5(),IlvFalse, IlvFalse);
					setVisible(getDiamond5G(),IlvFalse, IlvFalse);
					setVisible(getDiamond5D(),IlvFalse, IlvFalse);
					break;
				case 6 :
				    setVisible(getLighton6(),IlvFalse, IlvFalse);
				    setVisible(getEtalon6(),IlvFalse, IlvFalse);
				    setVisible(getBalance6(),IlvFalse, IlvFalse);
				    setVisible(getDiamond6(),IlvFalse, IlvFalse);
					setVisible(getDiamond6G(),IlvFalse, IlvFalse);
					setVisible(getDiamond6D(),IlvFalse, IlvFalse);
					break;
				case 7 :
				    setVisible(getLighton7(),IlvFalse, IlvFalse);
				    setVisible(getEtalon7(),IlvFalse, IlvFalse);
				    setVisible(getBalance7(),IlvFalse, IlvFalse);
				    setVisible(getDiamond7(),IlvFalse, IlvFalse);
					setVisible(getDiamond7G(),IlvFalse, IlvFalse);
					setVisible(getDiamond7D(),IlvFalse, IlvFalse);
					break;
				case 8 :
				    setVisible(getLighton8(),IlvFalse, IlvFalse);
				    setVisible(getEtalon8(),IlvFalse, IlvFalse);
				    setVisible(getBalance8(),IlvFalse, IlvFalse);
				    setVisible(getDiamond8(),IlvFalse, IlvFalse);
					setVisible(getDiamond8G(),IlvFalse, IlvFalse);
					setVisible(getDiamond8D(),IlvFalse, IlvFalse);
					break;
			}

		}
	}

}					
//---------------------------------------------------------------------------
void AdxChoix_Balance::chargement()
{
	afficherBalances();
}

//---------------------------------------------------------------------------

void AdxChoix_Balance::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));

	char szFileIcons[_MAX_PATH];
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\light_on.png",
			_interface->getPathX3());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	// bouton lighton1 à Lighton8 
	getLighton1()->setBitmap(bitmap);
	getLighton2()->setBitmap(bitmap);
	getLighton3()->setBitmap(bitmap);
	getLighton4()->setBitmap(bitmap);
	getLighton5()->setBitmap(bitmap);
	getLighton6()->setBitmap(bitmap);
	getLighton7()->setBitmap(bitmap);
	getLighton8()->setBitmap(bitmap);

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


void AdxChoix_Balance::show()
{
	HWND hwndWindow;
	BOOL bRetour = false;
	
	//IlvGadgetContainer::show();

	hwndWindow = (HWND)getSystemView();
	// on show en maximized
	bRetour = ShowWindow(hwndWindow,SW_MAXIMIZE);
}
 
