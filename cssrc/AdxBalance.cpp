// AdxBalance.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les balances

#include "stdafx.h"
#include "AdxBalance.h"
#include "AdxDate.h"
#include <string.h>

class AdxDate;

AdxBalance::~AdxBalance()
{
	if( _balance != 0)
		delete [] _balance;
	if( _libBalance != 0)
		delete [] _libBalance;
	if( _pilote != 0)
		delete [] _pilote;
	if( _separateur != 0)
		delete [] _separateur;
	if( _libSeparateur != 0)
		delete [] _libSeparateur;
	if( _unite != 0)
		delete [] _unite;
	if( _libCalibrage != 0)
		delete [] _libCalibrage;
	if( _guideCalibrage != 0)
		delete [] _guideCalibrage;
	if( _dateDernierCalibrage != NULL)
		delete _dateDernierCalibrage;
	if( _libCodeDispo != 0)
		delete [] _libCodeDispo;
	if( _etiquetteCalibrage != 0)
		delete [] _etiquetteCalibrage;
	if( _serialNumber != 0)
		delete [] _serialNumber;
}

void AdxBalance::setBalance( const char* str)
{ 
	if( _balance != 0) {
		delete [] _balance;
	}
	_balance = new char[ strlen( str) +1];
	strcpy( _balance, str);
}

void AdxBalance::setLibBalance( const char* str)
{ 
	if( _libBalance != 0) {
		delete [] _libBalance;
	}
	_libBalance = new char[ strlen( str) +1];
	strcpy( _libBalance, str);
}

void AdxBalance::setPort( const long& value)
{
	_port = value;
}

void AdxBalance::setPilote( const char* str)
{ 
	if( _pilote != 0) {
		delete [] _pilote;
	}
	_pilote = new char[ strlen( str) +1];
	strcpy( _pilote, str);
}

void AdxBalance::setNbEntiers( const long& value)
{
	_nbEntiers = value;
}

void AdxBalance::setNbDecimales( const long& value)
{
	_nbDecimales = value;
}

void AdxBalance::setSeparateur( const char* str)
{ 
	if( _separateur != 0) {
		delete [] _separateur;
	}
	_separateur = new char[ strlen( str) +1];
	strcpy( _separateur, str);
}

void AdxBalance::setLibSeparateur( const char* str)
{ 
	if( _libSeparateur != 0) {
		delete [] _libSeparateur;
	}
	_libSeparateur = new char[ strlen( str) +1];
	strcpy( _libSeparateur, str);
}

void AdxBalance::setConsigne (const bool value)
{
	_consigne = value;
}

void AdxBalance::setUnite( const char* str)
{ 
	if( _unite != 0) {
		delete [] _unite;
	}
	_unite = new char[ strlen( str) +1];
	strcpy( _unite, str);
}

void AdxBalance::setPorteeMini( const double& value)
{
	_porteeMini = value;
}

void AdxBalance::setPorteeMaxi( const double& value)
{
	_porteeMaxi = value;
}

void AdxBalance::setTareMaxi( const double& value)
{
	_tareMaxi = value;
}

void AdxBalance::setTolerance( const double& value)
{
	_tolerance = value;
}

void AdxBalance::setCodeCalibrage( const long& value)
{ 
	_codeCalibrage = value;
}

void AdxBalance::setLibCalibrage( const char* str)
{ 
	if( _libCalibrage != 0) {
		delete [] _libCalibrage;
	}
	_libCalibrage = new char[ strlen( str) +1];
	strcpy( _libCalibrage, str);
}

void AdxBalance::setGuideCalibrage( const char* str)
{ 
	if( _guideCalibrage != 0) {
		delete [] _guideCalibrage;
	}
	_guideCalibrage = new char[ strlen( str) +1];
	strcpy( _guideCalibrage, str);
}

void AdxBalance::setNbJours( const long& value)
{
	_nbJours = value;
}

void AdxBalance::setNbPesees( const long& value)
{
	_nbPesees = value;
}

void AdxBalance::setCodeDispo( const long& value)
{
	_codeDispo = value;
}

void AdxBalance::setLibCodeDispo( const char* str)
{ 
	if( _libCodeDispo != 0) {
		delete [] _libCodeDispo;
	}
	_libCodeDispo = new char[ strlen( str) +1];
	strcpy( _libCodeDispo, str);
}

void AdxBalance::setDateDernierCalibrage( AdxDate* date)
{
//	_dateDernierCalibrage = date;
	if (_dateDernierCalibrage != NULL)
		delete _dateDernierCalibrage;
	_dateDernierCalibrage = new AdxDate(date);
}

void AdxBalance::setNbPeseesCalibrage( const long& value)
{
	_nbPeseesCalibrage = value;
}

void AdxBalance::setEtiquetteCalibrage( const char* str)
{ 
	if( _etiquetteCalibrage != 0) {
		delete [] _etiquetteCalibrage;
	}
	_etiquetteCalibrage = new char[ strlen( str) +1];
	strcpy( _etiquetteCalibrage, str);
}

void AdxBalance::setSerialNumber( const char* str)
{ 
	if( _serialNumber != 0) {
		delete [] _serialNumber;
	}
	_serialNumber = new char[ strlen( str) +1];
	strcpy( _serialNumber, str);
}

void AdxBalance::setKeyRazSca(const char* str)
{
	if( _keyRazSca != 0) {
		delete [] _keyRazSca;
	}
	_keyRazSca = new char[strlen( str) +1];
	strcpy( _keyRazSca, str);
}

void AdxBalance::setKeyTarSca(const char* str)
{
	if( _keyTarSca != 0) {
		delete [] _keyTarSca;
	}
	_keyTarSca =  new char[strlen( str) +1];
	strcpy( _keyTarSca, str);
}


void AdxBalance::setVitesse(const int& value)
{
	_vitesse = value;
}

void AdxBalance::setParite(const int& value)
{
	_parite = value;
}

void AdxBalance::setStopBit(const int& value)
{
	_stopBit = value;
}

void AdxBalance::setFormat(const int& value)
{
	_format = value;
}

void AdxBalance::setTempo( const long& value)
{
	_tempo = value;
}


void AdxBalance::setEtalonnee( const bool b)
{
	_etalonnee = b;
}

void AdxBalance::setConnecte( const long& value)
{
	_connecte = value;
}

void AdxBalance::setNoDriver( const long& value)
{
	_noDriver = value;
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxBalance::init()
{
	_balance = NULL;
	_libBalance = NULL;
	_pilote = NULL;
	_separateur = NULL;
	_libSeparateur = NULL;
	_unite = NULL;
	_libCalibrage = NULL;
	_guideCalibrage = NULL;
	_dateDernierCalibrage = NULL;
	_libCodeDispo = NULL;
	_etiquetteCalibrage = NULL;
	_serialNumber = NULL;
	_keyRazSca = NULL;		//114545 mm 09.2016
	_keyTarSca = NULL;		//114545 mm 09.2016

	// Gestion du multi plateau
	_bMultiPlate = false;
	_plateIndex = 0;
	_bMultiPlateOK = true;
}

void AdxBalance::setMultiPlate(bool value)
{
	_bMultiPlate = value;
}

bool AdxBalance::IsMultiPlate()
{
	return _bMultiPlate;
}
void AdxBalance::setPlateIndex(short value)
{
	_plateIndex = value;
}
short AdxBalance::getPlateIndex()
{
	return _plateIndex;
}