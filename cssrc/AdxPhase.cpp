// AdxPhase.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		11/05/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant une Phase
#include "stdafx.h"
#include "AdxPhase.h"
#include "AdxComposant.h"
#include <string.h>

//---------------------------------------------------------------------------
AdxPhase::~AdxPhase()
{
	if( _numOF != 0)
		delete [] _numOF;
	if( _libStatut != 0)
		delete [] _libStatut;
	if( _libPriorite != 0)
		delete [] _libPriorite;
	if( _date != 0)
		delete _date;
	if(_composantList != NULL)
	{
		if (_composantList->length() > 0)
		{
			for (int i = 0; i < _composantList->length(); i++)
			{
				delete (AdxComposant*)(*_composantList)[i];
			}
		}
		_composantList->empty();
		delete _composantList;
	}
}

//---------------------------------------------------------------------------
void AdxPhase::setNumOF( const char* str) 
{ 
	if( _numOF != 0) {
		delete [] _numOF;
	}
	_numOF = new char[ strlen( str) +1];
	strcpy( _numOF, str);
}

//---------------------------------------------------------------------------
void AdxPhase::setNumPhase( const int p) 
{
	_numPhase = p;
}

//---------------------------------------------------------------------------
void AdxPhase::setStatut( const int s)
{
	_statut = s;
}

//---------------------------------------------------------------------------
void AdxPhase::setLibStatut( const char* str)
{
	if( _libStatut != 0) {
		delete [] _libStatut;
	}
	_libStatut = new char[ strlen( str) +1];
	strcpy( _libStatut, str);
}

//---------------------------------------------------------------------------
void AdxPhase::setDate(AdxDate* date)
{
	_date = date;
}

//---------------------------------------------------------------------------
void AdxPhase::setPriorite( const int p)
{
	_priorite = p;
}

//---------------------------------------------------------------------------
void AdxPhase::setLibPriorite( const char* str)
{
	if( _libPriorite != 0) {
		delete [] _libPriorite;
	}
	_libPriorite = new char[ strlen( str) +1];
	strcpy( _libPriorite, str);
}

//---------------------------------------------------------------------------
void AdxPhase::setNbComposants( const int nb)
{
	_nbComposants = nb;
}

//---------------------------------------------------------------------------
void AdxPhase::setNbComposantsPeses( const int nb)
{
	_nbComposantsPeses = nb;
}

//---------------------------------------------------------------------------
void AdxPhase::setTotalementPese( const bool b)
{
	_totalementPese = b;
}

//---------------------------------------------------------------------------
int AdxPhase::getIndexComposant(const char* composant)
{
	int i=0;
	while (i < getNbComposants())
	{
		if (strcmp ( composant, getComposant(i)->getComposant()) == 0)
			return i;
		i++;
	}
	return _nbComposants;
}

//---------------------------------------------------------------------------
void AdxPhase::setRectif( const int nb)
{
	_rectif = nb;
}

// SMO : 18/08/2010 ---------------------------------------------------------
void AdxPhase::setQteRestaPeser(const double qte){	_qteRestaPeser = qte;
}
// SMO : 18/08/2010 ---------------------------------------------------------
void AdxPhase::setQteAllouee(const double qte){
	_qteAllouee = qte;
}
// SMO : 18/08/2010 ---------------------------------------------------------
void AdxPhase::setUnite(const char* str){
	if( _unite != 0) {
		delete [] _unite;
	}
	_unite = new char[ strlen( str) +1];
	strcpy( _unite, str);
}


//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxPhase::init()
{
	_numOF				= NULL;
	_libStatut			= NULL;
	_date				= NULL;
	_libPriorite		= NULL;

	_composantList		= new IlList;
	_nbComposants		= 0;
	_rectif				= 0;
    _totalementPese		= false;
	// SMO : 18/08/2010
	_qteRestaPeser		= NULL;
	_qteAllouee			= NULL;
	_unite				= NULL;
}
