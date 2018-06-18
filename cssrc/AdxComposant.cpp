// AdxComposant.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		11/06/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant un composant

#include "stdafx.h"
#include "AdxComposant.h"
#include "AdxData.h"
#include "AdxLot.h"
#include "AdxPhase.h"
#include "AdxDate.h"
#include <string.h>

AdxComposant::~AdxComposant()
{
	if( _composant != 0)
		delete [] _composant;
	if( _libComposant != 0)
		delete  [] _libComposant;
	if( _unite != 0)
		delete [] _unite;
	if( _uniteStock != 0)
		delete [] _uniteStock;
	if( _libCodeAServir != 0)
		delete [] _libCodeAServir;
	if( _libGestionStock != 0)
		delete [] _libGestionStock;
	if( _libStockInfZero != 0)
		delete [] _libStockInfZero;
	if( _libLancementSiRupture != 0)
		delete [] _libLancementSiRupture;
	if( _ficheISM != 0)
		delete [] _ficheISM;
	if( _format != 0)
		delete [] _format;
	if(_phaseList_Art != NULL)
	{
		_phaseList_Art->empty();
		delete _phaseList_Art;
	}
}

void AdxComposant::setComposant( const char* str) 
{ 
	if( _composant != 0) {
		delete [] _composant;
	}
	_composant = new char[ strlen( str) +1];
	strcpy( _composant, str);
}

void AdxComposant::setLibComposant( const char* str) 
{
	if( _libComposant != 0) {
		delete [] _libComposant;
	}
	_libComposant = new char[ strlen( str) +1];
	strcpy( _libComposant, str);
}

void AdxComposant::setQuantitePrevue (const double& quantite)
{
	_quantitePrevue = quantite;
}

void AdxComposant::setQuantiteRestante (const double& quantite)
{
	_quantiteRestante = quantite;
}

void AdxComposant::setQuantiteTheorique (const double& quantite)
{
	_quantiteTheorique = quantite;
}

void AdxComposant::setQuantiteAllouee (const double& quantite)
{
	_quantiteAllouee = quantite;
}

void AdxComposant::setQuantiteConsommee (const double& quantite)
{
	_quantiteConsommee = quantite;
}

void AdxComposant::setQuantiteDisponible (const double& quantite)
{
	_quantiteDisponible = quantite;
}

void AdxComposant::setQuantiteDose (const double& quantite)
{
	_quantiteDose = quantite;
}

void AdxComposant::setToleranceArticlePositive( const double& value)
{
		_toleranceArticlePositive = value;
}

void AdxComposant::setToleranceArticleNegative( const double& value)
{
		_toleranceArticleNegative = value;
}

void AdxComposant::setUnite( const char* str)
{
	if( _unite != 0) {
		delete [] _unite;
	}
	_unite = new char[ strlen( str) +1];
	strcpy( _unite, str);
}

void AdxComposant::setUniteStock( const char* str)
{
	if( _uniteStock != 0) {
		delete [] _uniteStock;
	}
	_uniteStock = new char[ strlen( str) +1];
	strcpy( _uniteStock, str);
}

void AdxComposant::setCodeAServir( const int s)
{
	_codeAServir = s;
}

void AdxComposant::setLibCodeAServir( const char* str) 
{
	if( _libCodeAServir != 0) {
		delete [] _libCodeAServir;
	}
	_libCodeAServir = new char[ strlen( str) +1];
	strcpy( _libCodeAServir, str);
}

void AdxComposant::setGestionStock( const int s)
{
	_gestionStock = s;
}

void AdxComposant::setLibGestionStock( const char* str) 
{
	if( _libGestionStock != 0) {
		delete [] _libGestionStock;
	}
	_libGestionStock = new char[ strlen( str) +1];
	strcpy( _libGestionStock, str);
}

void AdxComposant::setTitreTheo (const double& titre)
{
	_titreTheo = titre;
}

void AdxComposant::setStockInfZero( const int s)
{
	_stockInfZero = s;
}

void AdxComposant::setLibStockInfZero( const char* str) 
{
	if( _libStockInfZero != 0) {
		delete [] _libStockInfZero;
	}
	_libStockInfZero = new char[ strlen( str) +1];
	strcpy( _libStockInfZero, str);
}

void AdxComposant::setLancementSiRupture( const int s)
{
	_lancementSiRupture = s;
}

void AdxComposant::setLibLancementSiRupture( const char* str) 
{
	if( _libLancementSiRupture != 0) {
		delete [] _libLancementSiRupture;
	}
	_libLancementSiRupture = new char[ strlen( str) +1];
	strcpy( _libLancementSiRupture, str);
}

void AdxComposant::setFicheISM( const char* str) 
{
	if( _ficheISM != 0) {
		delete [] _ficheISM;
	}
	_ficheISM = new char[ strlen( str) +1];
	strcpy( _ficheISM, str);
}

void AdxComposant::setNumeroLigne( const int s)
{
	_numeroLigne = s;
}

void AdxComposant::setSequenceNomenclature( const int s)
{
	_sequenceNomenclature = s;
}

void AdxComposant::setDecimalePoids( const int s)
{
	_decimalePoids = s;
}

void AdxComposant::setTotalementPese( const bool b)
{
	_totalementPese = b;
}

void AdxComposant::setFormat( const char* str) 
{
	if( _format != 0) {
		delete [] _format;
	}
	_format = new char[ strlen( str) +1];
	strcpy( _format, str);
}

void AdxComposant::setRedMod( const int s)
{
	_redMod = s;
}

// SMO : 19/08/2010
void AdxComposant::setQteDispoCompo(const double& qteDispo)
{
	_qteDispoCompo = qteDispo;
}

// mm 11.10 
void  AdxComposant::setQuantiteAlloueeRestante(const double& qteAllouee)
{
	_quantiteAlloueeRestante = qteAllouee;
}

void   AdxComposant::setQuantiteAlloueeTheorique (const double& qteAllouee)
{
	_quantiteAlloueeTheorique = qteAllouee;
}

void  AdxComposant::setQuantiteAlloueeDpOF(const double& qteAllouee)
{
	_quantiteAlloueeDpOF = qteAllouee;
}

void  AdxComposant::setQuantitePEC(const double& qtePEC)
{
	_quantitePEC = qtePEC;
}

// mm 03.13 - Performances
void AdxComposant::setNumOF( const char* str) 
{ 
	if( _numOF != 0) {
		delete [] _numOF;
	}
	_numOF = new char[ strlen( str) +1];
	strcpy( _numOF, str);
}
//--------------------------------------------------------------
// renvoie l'index precis de la phase dans la table this->getPhaseList_Art()
int AdxComposant::getIndexPhase_Art(const AdxPhase* phase)
{
	int i=0;
	while (i < getNbPhases_Art())
	{
		if (phase == getPhase_Art(i))
			return i;
		i++;
	}
	return _nbPhases_Art;
}

//--------------------------------------------------------------
// renvoie l'index de le premiere phase dans la table this->getPhaseList_Art()
int AdxComposant::getIndexPhase_Art(const int phase)
{
	int i=0;
	while (i < getNbPhases_Art())
	{
		if (phase == getPhase_Art(i)->getNumPhase())
			return i;
		i++;
	}
	return _nbPhases_Art;
}

//--------------------------------------------------------------
// s'applique au composant en cours, les lots charges en memoire doivent être ceux de ce composant
void AdxComposant::recalculeAlloueEtDisponible(AdxData* data)
{
	setQuantiteAllouee(0);
	setQuantiteDisponible(0);
	AdxLot* lot = data->getLot(0);
	for (int i = 0; i < data->getNbLots(); i++)
	{
		lot = data->getLot(i);
		setQuantiteAllouee(getQuantiteAllouee() + lot->getQuantiteAllouee());
		setQuantiteDisponible(getQuantiteDisponible() + lot->getQuantiteDisponible());
	}
}
//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxComposant::init()
{

  _composant				= NULL;
  _libComposant				= NULL;
  _quantiteAllouee			= 0;
  _unite					= NULL;
  _uniteStock				= NULL;
  _libCodeAServir			= NULL;
  _libGestionStock			= NULL;
  _libStockInfZero			= NULL;
  _libLancementSiRupture	= NULL;
  _ficheISM					= NULL;
  _totalementPese			= false;
  _format					= NULL;
  _phaseList_Art			= new IlList;
  _nbPhases_Art				= 0;
  _redMod					= 1;
  _toleranceArticlePositive = 0.0;	// 05.10 mm - % tolerances +/-
  _toleranceArticleNegative = 0.0;	// 05.10 mm - % tolerances +/-
  _qteDispoCompo			= 0;
  _quantiteAlloueeRestante	= 0;
  _quantiteAlloueeTheorique = 0;
  _quantiteAlloueeDpOF		= 0;
  _numOF					= NULL;	// 03.13 mm - Performances
  _quantitePEC				= 0;	// 91035 mm 10.2013
  _lotAlloueInvalide		= 0;	// mm 02.2012
}
