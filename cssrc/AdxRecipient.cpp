// AdxRecipient.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les recipients

#include "stdafx.h"
#include "AdxRecipient.h"
#include "AdxBalance.h"
#include "AdxDate.h"
#include <string.h>

class AdxDate;

AdxRecipient::~AdxRecipient()
{
	if( _recipient != 0)
		delete [] _recipient;
	if( _libRecipient != 0)
		delete _libRecipient;
	if( _unitePoids != 0)
		delete [] _unitePoids;
	if( _libTypeRecipient != 0)
		delete [] _libTypeRecipient;
	if( _guideOperateur != 0)
		delete [] _guideOperateur;
	if( _formatEtiquette != 0)
		delete [] _formatEtiquette;
	if(_balanceList != NULL)
	{
		if (_balanceList->length() < 0)
		{
			for (int i = 0; i < _balanceList->length(); i++)
			{
				delete (AdxBalance*)(*_balanceList)[i];
			}
		}
		_balanceList->empty();
		delete _balanceList;
	}
}

void AdxRecipient::setRecipient( const char* str)
{ 
		if( _recipient != 0) {
			delete [] _recipient;
		}
		_recipient = new char[ strlen( str) +1];
		strcpy( _recipient, str);
}

void AdxRecipient::setLibRecipient( const char* str)
{ 
		if( _libRecipient != 0) {
			delete [] _libRecipient;
		}
		_libRecipient = new char[ strlen( str) +1];
		strcpy( _libRecipient, str);
}

void AdxRecipient::setUnitePoids( const char* str)
{ 
		if( _unitePoids != 0) {
			delete [] _unitePoids;
		}
		_unitePoids = new char[ strlen( str) +1];
		strcpy( _unitePoids, str);
}

void AdxRecipient::setPoidsMaxi( const double& value)
{
		_poidsMaxi = value;
}

void AdxRecipient::setTypeRecipient( const int& value)
{
		_typeRecipient = value;
}

void AdxRecipient::setLibTypeRecipient( const char* str)
{ 
		if( _libTypeRecipient != 0) {
			delete [] _libTypeRecipient;
		}
		_libTypeRecipient = new char[ strlen( str) +1];
		strcpy( _libTypeRecipient, str);
}

void AdxRecipient::setTareTheo( const double& value)
{
		_tareTheo = value;
}

void AdxRecipient::setTareTheoSvg( const double& value)
{
		_tareTheoSvg = value;
}

void AdxRecipient::setTolerance( const double& value)
{
		_tolerance = value;
}

void AdxRecipient::setGuideOperateur( const char* str)
{ 
		if( _guideOperateur != 0) {
			delete [] _guideOperateur;
		}
		_guideOperateur = new char[ strlen( str) +1];
		strcpy( _guideOperateur, str);
}

void AdxRecipient::setFormatEtiquette( const char* str)
{ 
		if( _formatEtiquette != 0) {
			delete [] _formatEtiquette;
		}
		_formatEtiquette = new char[ strlen( str) +1];
		strcpy( _formatEtiquette, str);
}


void AdxRecipient::setNbBalances( const int value)
{
		_nbBalances = value;
}

void AdxRecipient::setTareModifiable( const int& value) 
{
	_tareModifiable = value;
}


void AdxRecipient::setSaisiePoids( const int& value) 
{
	_saisiePoids = value;
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxRecipient::init()
{
	_recipient = NULL;
	_libRecipient = NULL;
	_unitePoids = NULL;
	_poidsMaxi = 0.0;
	_typeRecipient = 0;
	_libTypeRecipient = NULL;
	_tareTheo = 0.0;
	_tareTheoSvg = 0.0;		// 02.09 Sauvegarde de la tare theo, sinon écrasée par tare saisie
	_tolerance = 0.0;
	_guideOperateur = NULL;
	_formatEtiquette = NULL;
	_tareModifiable = 0;	// 04.07 gestion d'une tare modifiable
	_saisiePoids = 0;	// 10.07 pesee en mode degrade selon la valeur de saisie Poids
	_balanceList = new IlList;
}
