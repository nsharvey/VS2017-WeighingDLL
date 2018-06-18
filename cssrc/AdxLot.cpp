// AdxLot.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		18/06/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant un Lot pour les allocations 

#include "stdafx.h"
#include "AdxLot.h"
#include <string.h>

AdxLot::~AdxLot()
{
	if( _lot != 0)
		delete [] _lot;
	if( _slo != 0)
		delete [] _slo;
	if( _emplacement != 0)
		delete  [] _emplacement;
	if( _unite != 0)
		delete [] _unite;
	if( _datePeremption != 0)
		delete _datePeremption;
	if( _libStatut != 0)
		delete [] _libStatut;
	if( _statut != 0)
		delete [] _statut;
	if( _cuve != 0)
		delete [] _cuve;
	if( _vanne != 0)
		delete [] _vanne;
}

void AdxLot::setLot( const char* str) 
{ 
	if( _lot != 0) {
		delete [] _lot;
	}
	_lot = new char[ strlen( str) +1];
	strcpy( _lot, str);
}

void AdxLot::setSlo( const char* str) 
{ 
	if( _slo != 0) {
		delete [] _slo;
	}
	_slo = new char[ strlen( str) +1];
	strcpy( _slo, str);
}

void AdxLot::setEmplacement( const char* str) 
{
	if( _emplacement != 0) {
		delete [] _emplacement;
	}
	_emplacement = new char[ strlen( str) +1];
	strcpy( _emplacement, str);
}

void AdxLot::setLibEmplacement( const char* str) 
{
	if( _libEmplacement != 0) {
		delete [] _libEmplacement;
	}
	_libEmplacement = new char[ strlen( str) +1];
	strcpy( _libEmplacement, str);
}
void AdxLot::setQuantiteDisponible (const double& quantite)
{
	_quantiteDisponible = quantite;
}

void AdxLot::setQuantiteAllouee (const double& quantite)
{
	_quantiteAllouee = quantite;
}

void AdxLot::setQuantiteTotale (const double& quantite)
{
	_quantiteTotale = quantite;
}
void AdxLot::setUnite( const char* str)
{
	if( _unite != 0) {
		delete [] _unite;
	}
	_unite = new char[ strlen( str) +1];
	strcpy( _unite, str);
}

void AdxLot::setDatePeremption(AdxDate* date)
{
	_datePeremption = date;
}

void AdxLot::setStatut( const char* str)
{
	if( _statut != 0) {
		delete [] _statut;
	}
	_statut = new char[ strlen( str) +1];
	strcpy( _statut, str);
}

void AdxLot::setLibStatut( const char* str)
{
	if( _libStatut != 0) {
		delete [] _libStatut;
	}
	_libStatut = new char[ strlen( str) +1];
	strcpy( _libStatut, str);
}

void AdxLot::setTitre( const double& t)
{
	_titre = t;
}

void AdxLot::setCuve( const char* str)
{
	if( _cuve != 0) {
		delete [] _cuve;
	}
	_cuve = new char[ strlen( str) +1];
	strcpy( _cuve, str);
}

void AdxLot::setLibSaisieCuve( const char* str)
{
	if( _libCuve != 0) {
		delete [] _libCuve;
	}
	_libCuve = new char[ strlen( str) +1];
	strcpy( _libCuve, str);
}

void AdxLot::setVanne( const char* str)
{
	if( _vanne != 0) {
		delete [] _vanne;
	}
	_vanne = new char[ strlen( str) +1];
	strcpy( _vanne, str);
}

void AdxLot::setChrono( const int t)
{
	_chrono = t;
}

void AdxLot::setSequence( const int t)
{
	_sequence = t;
}

void AdxLot::setQuantiteReelDispo (const double& quantite)
{
	_quantiteReelDispo = quantite;
}

void AdxLot::setQuantiteInitiale (const double& quantite)
{
	_quantiteInitiale = quantite;
}



//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxLot::init()
{

  _lot	= NULL;
  _slo	= NULL;
  _emplacement = NULL;
  _libEmplacement = NULL;
  _unite = NULL;
  _datePeremption = NULL;
  _statut = NULL;
  _libStatut = NULL;
  _cuve = NULL;
  _libCuve = NULL ;
  _vanne = NULL;

}

//--------------------------------------------------------------
AdxLot* AdxLot::copy()
{
  AdxLot* lotRetour = new AdxLot;

  lotRetour->setLot (_lot);
  lotRetour->setSlo (_slo);
  lotRetour->setEmplacement(_emplacement);
  lotRetour->setQuantiteDisponible(_quantiteDisponible);
  lotRetour->setQuantiteAllouee(_quantiteAllouee);
  lotRetour->setQuantiteTotale(_quantiteTotale);
  lotRetour->setUnite(_unite);
  lotRetour->setDatePeremption(new AdxDate(_datePeremption));
  lotRetour->setStatut(_statut);
  lotRetour->setLibStatut(_libStatut);
  lotRetour->setTitre(_titre);
  lotRetour->setCuve(_cuve);
  lotRetour->setVanne(_vanne);
  lotRetour->setChrono(_chrono);
  lotRetour->setSequence(_sequence);
  lotRetour->setQuantiteReelDispo(_quantiteReelDispo);
  lotRetour->setQuantiteInitiale(_quantiteInitiale);
  return lotRetour;
}