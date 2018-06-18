// AdxEtalonLigne.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : SR		30/11/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les guides etalonnage

#include "stdafx.h"
#include "AdxetalonLigne.h"
#include <string.h>


AdxEtalonLigne::~AdxEtalonLigne()
{
	if( _unite != 0)
		delete [] _unite;
	if( _libTypPesee != 0)
		delete [] _libTypPesee;
	if( _format != 0)
		delete [] _format;
	//if( _arrPoidsPese != NULL)	// mm 09.12 - commenté car _arrPoidsPese est un double et non un tableau
	//	delete  _arrPoidsPese;	
}

void AdxEtalonLigne::setEtalon( AdxEtalon* etalon)
{ 
	_etalon = etalon;
}

void AdxEtalonLigne::setLigne( const long& value)
{
	_ligne = value;
}

void AdxEtalonLigne::setPoids( const double& value)
{
	_poids = value;	
}

void AdxEtalonLigne::setUnite( const char* str)
{ 
	if( _unite != 0) {
		delete [] _unite;
	}
	_unite = new char[ strlen( str) +1];
	strcpy( _unite, str);
}

void AdxEtalonLigne::setNbPesees( const long& value)
{
	_nbPesees = value;
}

void AdxEtalonLigne::setTypPesee( const long& value)
{
	_typPesee = value;
}

void AdxEtalonLigne::setLibTypPesee( const char* str)
{ 
	if( _libTypPesee != 0) {
		delete [] _libTypPesee;
	}
	_libTypPesee = new char[ strlen( str) +1];
	strcpy( _libTypPesee, str);
}


void AdxEtalonLigne::setTolerance( const double& value)
{
	_tolerance = value;
}

void AdxEtalonLigne::setEcartMaxi( const double& value)
{
	_ecartMaxi = value;
}
void AdxEtalonLigne::setPoidsPese( const double& value)
{
	_poidsPese = value;
}

void AdxEtalonLigne::setDecimalePoids( const int value)
{
	_decimalePoids = value;
}

void AdxEtalonLigne::setNbPeseesOk( const long& value)
{
	_nbPeseesOk = value;
}

void AdxEtalonLigne::setNbPeseesEffectuees( const long& value)
{
	_nbPeseesEffectuees = value;
}

void AdxEtalonLigne::setArrPoidsPese(const int Index, const double& value)
{
	_arrPoidsPese[Index] = value;
}


void AdxEtalonLigne::setFormat( const char* str)
{
	if( _format != 0) {
		delete [] _format;
	}
	_format = new char[ strlen( str) +1];
	strcpy( _format, str);
}


//---------------------------------------------------------------------------
void AdxEtalonLigne::setPeseeEffectuee( const bool be)
{
	_peseeEffectuee = be;
}

//---------------------------------------------------------------------------
void AdxEtalonLigne::setPeseeValidee( const bool bv)
{
	_peseeValidee = bv;
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxEtalonLigne::init()
{
	_etalon = NULL;
	_unite = NULL;
	_libTypPesee = NULL;
	_format = NULL;
	_peseeEffectuee = false;
	_peseeValidee = false;	
	_arrPoidsPese = NULL;
}
