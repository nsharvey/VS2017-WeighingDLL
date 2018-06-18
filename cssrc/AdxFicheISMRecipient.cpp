// AdxFicheISMRecipient.cpp
// ------------------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les fiches ISM récipient

#include "stdafx.h"
#include "AdxFicheISMRecipient.h"
#include <string.h>

AdxFicheISMRecipient::~AdxFicheISMRecipient()
{
	if( _ficheISMRecipient != 0)
		delete [] _ficheISMRecipient;
	if( _recipient != 0)
		delete [] _recipient;
	if( _unitePoids != 0)
		delete [] _unitePoids;
	if( _libRecipient != 0)
		delete [] _libRecipient;
	if( _libTypeRecipient != 0)
		delete [] _libTypeRecipient;
	if( _unite2 != 0)
		delete [] _unite2;
	if( _guideOperateur != 0)
		delete [] _guideOperateur;
	if( _formatEtiquette != 0)
		delete [] _formatEtiquette;
}

void AdxFicheISMRecipient::setFicheISMRecipient( const char* str)
{ 
		if( _ficheISMRecipient != 0) {
			delete [] _ficheISMRecipient;
		}
		_ficheISMRecipient = new char[ strlen( str) +1];
		strcpy( _ficheISMRecipient, str);
}

void AdxFicheISMRecipient::setRecipient( const char* str)
{ 
		if( _recipient != 0) {
			delete [] _recipient;
		}
		_recipient = new char[ strlen( str) +1];
		strcpy( _recipient, str);
}

void AdxFicheISMRecipient::setUnitePoids( const char* str)
{ 
		if( _unitePoids != 0) {
			delete [] _unitePoids;
		}
		_unitePoids = new char[ strlen( str) +1];
		strcpy( _unitePoids, str);
}

void AdxFicheISMRecipient::setPoidsMaxi( const double& value)
{
		_poidsMaxi = value;
}

void AdxFicheISMRecipient::setLibRecipient( const char* str)
{ 
		if( _libRecipient != 0) {
			delete [] _libRecipient;
		}
		_libRecipient = new char[ strlen( str) +1];
		strcpy( _libRecipient, str);
}

void AdxFicheISMRecipient::setTypeRecipient( const int& value)
{
		_typeRecipient = value;
}

void AdxFicheISMRecipient::setLibTypeRecipient( const char* str)
{ 
		if( _libTypeRecipient != 0) {
			delete [] _libTypeRecipient;
		}
		_libTypeRecipient = new char[ strlen( str) +1];
		strcpy( _libTypeRecipient, str);
}

void AdxFicheISMRecipient::setTareTheo( const double& value)
{
		_tareTheo = value;
}

void AdxFicheISMRecipient::setToleranceTare( const double& value)
{
		_toleranceTare = value;
}

void AdxFicheISMRecipient::setUnite2( const char* str)
{ 
		if( _unite2 != 0) {
			delete [] _unite2;
		}
		_unite2 = new char[ strlen( str) +1];
		strcpy( _unite2, str);
}

void AdxFicheISMRecipient::setGuideOperateur( const char* str)
{ 
		if( _guideOperateur != 0) {
			delete [] _guideOperateur;
		}
		_guideOperateur = new char[ strlen( str) +1];
		strcpy( _guideOperateur, str);
}

void AdxFicheISMRecipient::setFormatEtiquette( const char* str)
{ 
		if( _formatEtiquette != 0) {
			delete [] _formatEtiquette;
		}
		_formatEtiquette = new char[ strlen( str) +1];
		strcpy( _formatEtiquette, str);
}

void AdxFicheISMRecipient::setTareModifiable( const int& value ) 
{
		_tareModifiable = value;
}

void AdxFicheISMRecipient::setSaisiePoids( const int& value ) 
{
		_saisiePoids = value;		
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxFicheISMRecipient::init()
{
	_ficheISMRecipient = NULL;
	_recipient = NULL;
	_unitePoids = NULL;
	_poidsMaxi = 0.0;
	_libRecipient = NULL;
	_typeRecipient = 0;
	_libTypeRecipient = NULL;
	_tareTheo = 0.0;
	_toleranceTare = 0.0;
	_unite2 = NULL;
	_guideOperateur = NULL;
	_formatEtiquette = NULL;
	_tareModifiable = 0 ;	// 04.07 gestion d'une tare modifiable 
	_saisiePoids = 0 ;	// 10.07 pesee en mode degrade selon la valeur de saisie Poids
}
