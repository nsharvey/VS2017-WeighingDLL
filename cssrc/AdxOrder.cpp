// AdxOrder.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		30/04/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant un OF et une liste d'OF

#include "stdafx.h"
#include "AdxOrder.h"
#include <string.h>

//---------------------------------------------------------------------------
AdxOrder::~AdxOrder()
{
	if( _numOF != 0)
		delete [] _numOF;
	if( _article != 0)
		delete  [] _article;
	if( _libArticle != 0)
		delete [] _libArticle;
	if( _lotLance != 0)
		delete [] _lotLance;
	if( _unite != 0)
		delete [] _unite;
	if( _libStatut != 0)
		delete [] _libStatut;
	if( _libPriorite != 0)
		delete [] _libPriorite;
	if( _dateFin != 0)
		delete _dateFin;
	if( _unitePoids != 0)
		delete [] _unitePoids;
}

//---------------------------------------------------------------------------
void AdxOrder::setNumOF( const char* str) 
{ 
	if( _numOF != 0) {
		delete [] _numOF;
	}
	_numOF = new char[ strlen( str) +1];
	strcpy( _numOF, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setArticle( const char* str) 
{
	if( _article != 0) {
		delete [] _article;
	}
	_article = new char[ strlen( str) +1];
	strcpy( _article, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setLibArticle( const char* str) 
{
	if( _libArticle != 0) {
		delete [] _libArticle;
	}
	_libArticle = new char[ strlen( str) +1];
	strcpy( _libArticle, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setLotLance( const char* str) 
{
	if( _lotLance != 0) {
		delete [] _lotLance;
	}
	_lotLance = new char[ strlen( str) +1];
	strcpy( _lotLance, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setQuantiteLance (const double& quantiteLance)
{
	_quantiteLance = quantiteLance;
}

//---------------------------------------------------------------------------
void AdxOrder::setUnite( const char* str)
{
	if( _unite != 0) {
		delete [] _unite;
	}
	_unite = new char[ strlen( str) +1];
	strcpy( _unite, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setStatut( const int s)
{
	_statut = s;
}

//---------------------------------------------------------------------------
void AdxOrder::setLibStatut( const char* str)
{
	if( _libStatut != 0) {
		delete [] _libStatut;
	}
	_libStatut = new char[ strlen( str) +1];
	strcpy( _libStatut, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setDateFin(AdxDate* date)
{
	_dateFin = date;
}

//---------------------------------------------------------------------------
void AdxOrder::setPriorite( const int p)
{
	_priorite = p;
}

//---------------------------------------------------------------------------
void AdxOrder::setLibPriorite( const char* str)
{
	if( _libPriorite != 0) {
		delete [] _libPriorite;
	}
	_libPriorite = new char[ strlen( str) +1];
	strcpy( _libPriorite, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setQuantiteLanceeEnPoids (const double& quantite)
{
	_quantiteLanceeEnPoids = quantite;
}

//---------------------------------------------------------------------------
void AdxOrder::setUnitePoids( const char* str)
{
	if( _unitePoids != 0) {
		delete [] _unitePoids;
	}
	_unitePoids = new char[ strlen( str) +1];
	strcpy( _unitePoids, str);
}

//---------------------------------------------------------------------------
void AdxOrder::setTotalementPese( const bool b)
{
	_totalementPese = b;
}


// SMO : 18/08/2010 ---------------------------------------------------------
void AdxOrder::setTotalAPeser(const double& totAPeser){
	_totalAPeser = totAPeser;
}

// SMO : 18/08/2010 ---------------------------------------------------------
void AdxOrder::setUnitePoidsCompo( const char* str){

	if( _unitePoidsCompo != 0) {
		delete [] _unitePoidsCompo;
	}
	_unitePoidsCompo = new char[ strlen( str) +1];
	strcpy( _unitePoidsCompo, str);
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxOrder::init()
{
	_numOF				= NULL;
	_article			= NULL;
	_libArticle			= NULL;
	_lotLance			= NULL;
	_unite				= NULL;
	_libStatut			= NULL;
	_dateFin			= NULL;
	_libPriorite		= NULL;
	_unitePoids			= NULL;
	_totalementPese		= false;
	// SMO : 18/08/2010
	_statutMatiere		= NULL;
	_totalAPeser		= NULL;
	_unitePoidsCompo	= NULL;
}
