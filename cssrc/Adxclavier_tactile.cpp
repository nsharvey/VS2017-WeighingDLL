// AdxClavier_tactile.cpp
// ----------------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#include "stdafx.h"
#include "Adxclavier_tactile.h"

#include "AdxInterface.h"
#include "AdxChoix_OF.h"
#include "AdxPesee_OF.h"
#include "AdxPesee_Etalon.h"
#include "AdxRecontrole_OF.h"
// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------
//---------------------------------------------------------------------------
AdxClavier_Tactile::~AdxClavier_Tactile()
{
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::arriereCB(IlvGraphic* g)
{
	int i = _saisie.GetLength();
	if (_alpha == IlvFalse)
	{
		if (_saisie[i-1] == '0')
			moins(0);
		if (_saisie[i-1] == '1')
			moins(1);
		if (_saisie[i-1] == '2')
			moins(2);
		if (_saisie[i-1] == '3')
			moins(3);
		if (_saisie[i-1] == '4')
			moins(4);
		if (_saisie[i-1] == '5')
			moins(5);
		if (_saisie[i-1] == '6')
			moins(6);
		if (_saisie[i-1] == '7')
			moins(7);
		if (_saisie[i-1] == '8')
			moins(8);
		if (_saisie[i-1] == '9')
			moins(9);
		if (_saisie[i-1] == '.')
			_nbSepar--;
	}
	_saisie.Delete(i-1,1);
	getchampSaisie()->setLabel(_saisie);
	reDrawObj(getchampSaisie());
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::validationCB(IlvGraphic* g)
{
//	rafraichissement panneau appelant
// pour Choix_OF
	if (_panneauAppelant == getInterface()->getChoix_OF())
	{
		if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getChoix_OF()->getSaisieNOF()||
			_panneauAppelant->getChampAppelant() == 
					getInterface()->getChoix_OF()->getSaisieNOF_Art()
					)
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getChoix_OF()->SaisieNOFCB(_panneauAppelant
														->getChampAppelant());
			if (getInterface()->getFonctionEnCours() == 1 || getInterface()->getFonctionEnCours() == 3)
				getInterface()->getChoix_OF()->setFocus
					(getInterface()->getChoix_OF()->getSaisiePhase(), IlvTrue);
			else
				getInterface()->getChoix_OF()->setFocus
					(getInterface()->getChoix_OF()->getSaisiePhase_Art(), IlvTrue);

			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getChoix_OF()->getSaisiePhase() ||
				 _panneauAppelant->getChampAppelant() == 
					getInterface()->getChoix_OF()->getSaisiePhase_Art() )
		{
			IlvNumberField* numberField = (IlvNumberField*)_panneauAppelant
															->getChampAppelant();
			numberField->setValue((IlvInt)_saisieNum);
			_saisie = "";
			quitter();
			getInterface()->getChoix_OF()->SaisiePhaseCB(_panneauAppelant
														   ->getChampAppelant());
			if (getInterface()->getFonctionEnCours() == 1 || getInterface()->getFonctionEnCours() == 3)
				getInterface()->getChoix_OF()->setFocus
					(getInterface()->getChoix_OF()->getSaisieComposant(), IlvTrue);
			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getChoix_OF()->getSaisieComposant() ||
				 _panneauAppelant->getChampAppelant() == 
					getInterface()->getChoix_OF()->getSaisieComposant_Art())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getChoix_OF()->SaisieComposantCB(_panneauAppelant
															  ->getChampAppelant());
			
			if (getInterface()->getFonctionEnCours() == 2) 
				getInterface()->getChoix_OF()->setFocus
					(getInterface()->getChoix_OF()->getSaisieNOF_Art(), IlvTrue);

			return;
		}
	}

// pour Pesee_OF
	if (_panneauAppelant == getInterface()->getPesee_OF())
	{
		if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisiePoidsPese())
		{
			IlvNumberField* numberField = (IlvNumberField*)_panneauAppelant
															->getChampAppelant();
			numberField->setValue((IlvDouble)_saisieNum);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisiePoidsPeseCB(_panneauAppelant
															  ->getChampAppelant());
			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisieLot())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisieLotCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}

		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisieEmplacement())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisieEmplacementCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisieCuve())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisieCuveCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}

		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisieVanne())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisieVanneCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisieRecipient())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisieRecipientCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_OF()->getSaisieBalance())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getPesee_OF()->SaisieBalanceCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
	}

// pour Recontrole_OF
	if (_panneauAppelant == getInterface()->getRecontrole_OF())
	{
		if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getRecontrole_OF()->getSaisieComposant())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getRecontrole_OF()->SaisieComposantCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getRecontrole_OF()->getSaisieLot())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getRecontrole_OF()->SaisieLotCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
		// 03.10 mm - modification du recontrole OF
		else if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getRecontrole_OF()->getSaisieSousLot())
		{
			IlvTextField* textField = _panneauAppelant->getChampAppelant();
			textField->setLabel(_saisie);
			_saisie = "";
			quitter();
			getInterface()->getRecontrole_OF()->SaisieSousLotCB(_panneauAppelant
													    ->getChampAppelant());
			return;
		}
	}
// pour Pesee_Etalon
	if (_panneauAppelant == getInterface()->getPesee_Etalon())
	{

		if (_panneauAppelant->getChampAppelant() == 
					getInterface()->getPesee_Etalon()->getPoidsPese())
		{
			IlvNumberField* numberField = (IlvNumberField*)_panneauAppelant
															->getChampAppelant();
			numberField->setValue((IlvDouble)_saisieNum);
			_saisie = "";
			quitter();
			getInterface()->getPesee_Etalon()->poidsPeseCB(_panneauAppelant
															  ->getChampAppelant());
			return;

		}
	}


	// pour les panneaux suivants...

}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::toucheCB(IlvGraphic* g)
{
	const char* name = g->getName();
	if (strcmp(name,"A1") == 0)
	{
		name = "1";
		if (_alpha == IlvFalse)
			plus(1);
	}
	else if (strcmp(name,"A2") == 0)
	{
		name = "2";
		if (_alpha == IlvFalse)
			plus(2);
	}
	 else if (strcmp(name,"A3") == 0)
	{
		name = "3";
		if (_alpha == IlvFalse)
			plus(3);
	}
    else if (strcmp(name,"A4") == 0)
	{
		name = "4";
		if (_alpha == IlvFalse)
			plus(4);
	}
    else if (strcmp(name,"A5") == 0)
	{
		name = "5";
		if (_alpha == IlvFalse)
			plus(5);
	}
	else if (strcmp(name,"A6") == 0)
	{
		name = "6";
		if (_alpha == IlvFalse)
			plus(6);
	}
	else if (strcmp(name,"A7") == 0)
	{
		name = "7";
		if (_alpha == IlvFalse)
			plus(7);
	}
	else if (strcmp(name,"A8") == 0)
	{
		name = "8";
		if (_alpha == IlvFalse)
			plus(8);
	}
	else if (strcmp(name,"A9") == 0)
	{
		name = "9";
		if (_alpha == IlvFalse)
			plus(9);
	}
	else if (strcmp(name,"A0") == 0)
	{
		name = "0";
		if (_alpha == IlvFalse)
			plus(0);
	}
	else if (strcmp(name,"A11") == 0)
	{
		if (_alpha == IlvFalse)	
		{
			if ((_nbSepar == 0) && (_saisie.GetLength() != 0))
			{
				_posSepar = _saisie.GetLength();
				name = ".";
				_nbSepar++;
			}
			else
			{
				_name = "";
			}
		}
		else
		{
			name = ".";
		}	
	}
    else if (strcmp(name,"A12") == 0)
    {
        name = "-";
    }
	_saisie += name;
    	getchampSaisie()->setLabel(_saisie);
	reDrawObj(getchampSaisie());
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::retourCB(IlvGraphic* g)
{
	this->quitter();
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::setAlpha(const IlvBoolean b)
{ 
// activation ou desactivation des lettres
	getA()->setSensitive(b);
	getB()->setSensitive(b);
	getC()->setSensitive(b);
	getD()->setSensitive(b);
	getE()->setSensitive(b);
	getF()->setSensitive(b);
	getG()->setSensitive(b);
	getH()->setSensitive(b);
	getI()->setSensitive(b);
	getJ()->setSensitive(b);
	getK()->setSensitive(b);
	getL()->setSensitive(b);
	getM()->setSensitive(b);
	getN()->setSensitive(b);	
	getO()->setSensitive(b);
	getP()->setSensitive(b);
	getQ()->setSensitive(b);
	getR()->setSensitive(b);
	getS()->setSensitive(b);
	getT()->setSensitive(b);
	getU()->setSensitive(b);
	getV()->setSensitive(b);
	getW()->setSensitive(b);
	getX()->setSensitive(b);
	getY()->setSensitive(b);
	getZ()->setSensitive(b);
	_alpha = b;
	_nbSepar = 0;
	_saisieNum = 0;
	_diviseur = 10;
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::quitter()
{
 	hide();
	_panneauAppelant->show();
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::plus(int i)
{
	if (_nbSepar == 0)
	{
		_saisieNum = _saisieNum * 10;
		_saisieNum += i;
	}
	else
	{
		_saisieNum += (double)i/_diviseur;
		_diviseur = _diviseur * 10;
	}
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::moins(int i)
{
	if (_nbSepar == 0)
	{
		_saisieNum -= i;
		_saisieNum = _saisieNum / 10;
		
	}
	else
	{
		_saisieNum -= (double)i/_diviseur;
		_diviseur = _diviseur / 10;
	}
}

//---------------------------------------------------------------------------
void AdxClavier_Tactile::init(AdxInterface* m_interface)
{
	_interface = m_interface;
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	// fond ecran
	//setBackgroundBitmap(_interface->LoadBackgroundBitmap(getDisplay()));


	char szFileIcons[_MAX_PATH];
	// bouton A1
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key1.png",
		_interface->getPathX3());
	IlvBitmap* bitmap =	getDisplay()->readBitmap(szFileIcons);
	getA1()->setBitmap(bitmap);

	// bouton A2
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key2.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA2()->setBitmap(bitmap);

	// bouton A3
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key3.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA3()->setBitmap(bitmap);

	// bouton A4
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key4.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA4()->setBitmap(bitmap);

	// bouton A5
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key5.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA5()->setBitmap(bitmap);

	// bouton A6
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key6.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA6()->setBitmap(bitmap);

	// bouton A7
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key7.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA7()->setBitmap(bitmap);

	// bouton A8
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key8.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA8()->setBitmap(bitmap);

	// bouton A9
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key9.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA9()->setBitmap(bitmap);

	// bouton A0
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_key0.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA0()->setBitmap(bitmap);

	// bouton A11
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyDot.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA11()->setBitmap(bitmap);

	// bouton A
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyA.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getA()->setBitmap(bitmap);

	// bouton B
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyB.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getB()->setBitmap(bitmap);

	// bouton C
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyC.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getC()->setBitmap(bitmap);

	// bouton D
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyD.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getD()->setBitmap(bitmap);

	// bouton E
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyE.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getE()->setBitmap(bitmap);

	// bouton F
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyF.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getF()->setBitmap(bitmap);

	// bouton G
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyG.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getG()->setBitmap(bitmap);

	// bouton H
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyH.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getH()->setBitmap(bitmap);

	// bouton I
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyI.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getI()->setBitmap(bitmap);

	// bouton J
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyJ.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getJ()->setBitmap(bitmap);

	// bouton K
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyK.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getK()->setBitmap(bitmap);

	// bouton L
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyL.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getL()->setBitmap(bitmap);

	// bouton M
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyM.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getM()->setBitmap(bitmap);

	// bouton N
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyN.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getN()->setBitmap(bitmap);

	// bouton O
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyO.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getO()->setBitmap(bitmap);

	// bouton P
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyP.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getP()->setBitmap(bitmap);

	// bouton Q
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyQ.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getQ()->setBitmap(bitmap);

	// bouton R
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyR.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getR()->setBitmap(bitmap);

	// bouton S
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyS.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getS()->setBitmap(bitmap);

	// bouton T
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyT.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getT()->setBitmap(bitmap);

	// bouton U
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyU.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getU()->setBitmap(bitmap);

	// bouton V
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyV.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getV()->setBitmap(bitmap);

	// bouton W
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyW.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getW()->setBitmap(bitmap);

	// bouton X
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyX.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getX()->setBitmap(bitmap);

	// bouton Y
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyY.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getY()->setBitmap(bitmap);

	// bouton Z
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyZ.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getZ()->setBitmap(bitmap);

	// bouton toucheArriere
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_keyBack.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	gettoucheArriere()->setBitmap(bitmap);

	// bouton tiret
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\white_Dashkey.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	gettiret()->setBitmap(bitmap);

    // bouton validation
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\thumb_up.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getvalidation()->setBitmap(bitmap);

	// bouton retour
	sprintf (szFileIcons, "%sIcons\\Boutons_jpg\\exit.png",
		_interface->getPathX3());
	bitmap = getDisplay()->readBitmap(szFileIcons);
	getretour()->setBitmap(bitmap);

	IlvRect monecran;
	IlvRect boundingBox;
	this->boundingBox(boundingBox);

	getDisplay()->screenBBox(monecran,true,&boundingBox);

	IlvDim sizeScreenW = monecran.w();
	IlvDim sizeScreenH = monecran.h();
	setMinimumSize (sizeScreenW, sizeScreenH);
	//setMaximumSize (sizeScreenW, sizeScreenH);
}
